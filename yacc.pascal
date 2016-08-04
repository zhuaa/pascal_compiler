%{

#include "global.h"
#include "SymbolTable.h"
#include "typeCheck.h"
#include "code.h"
#define WIDTH (4)
#define HEIGHT (0)

typedef struct stringConstNode {
	struct stringConstNode * next;
	char * name;
	char * value;
} stringConstNode;

void printAncestor(int *uncle, int level);
void printThisTree(TreeNode * t, int *uncle, int level);
extern void openFile(int argc, char** argv);
TreeNode * makeNewConstNode(int type, int value, int line_no);
TreeNode * makeNewFactorNode(int type, int value, int line_no);
TreeNode * makeNewTermNode(int type, int value, int line_no);
TreeNode * makeNewExprNode(int type, int value, int line_no);
TreeNode * makeNewExpressionNode(int type, int value, int line_no);
TreeNode * closeExpression(TreeNode * k);
void itoa(int value, char *buf, int radix);
int checkBool(TreeNode *);
TreeNode * eliminateUselessFromList(TreeNode * t);
TreeNode * getStmtNode(TreeNode * t);
int isUseless(TreeNode * t);
void setStmtNodeToNULL(TreeNode * t);
stringConstNode * insertIntoStringConstTable(TreeNode * t);
stringConstNode * makeNewStringConstNode();
void releaseStringConstNode(stringConstNode * t);
void updateConstPart();
void insertIntoConstPart(stringConstNode * sconst, TreeNode * const_part);
void printStringConstTable();

stringConstNode * stringConstTable = NULL;
int stringConstCount = 0;
int currentline = 0;
TreeNode * savedTree = NULL;
VarTable* MainVarTable = NULL;
ConstTable* MainConstTable = NULL;
TypeTable* MainTypeTable = NULL;
ProcedureTable* MainProcedureTable = NULL;

%}

%token SYS_CON SYS_TYPE
%token DOT PROGRAM ID SEMI CONST EQUAL INTEGER REAL CHAR STRING TYPE
%token ARRAY LB RB OF RECORD END COLON COMMA LP RP DOTDOT MINUS VAR
%token FUNCTION PROCEDURE ASSIGN SYS_PROC READ BEGIN_PASCAL IF THEN ELSE
%token REPEAT UNTIL WHILE DO FOR TO DOWNTO CASE GOTO
%token GE GT LE LT UNEQUAL PLUS OR MUL DIV MOD AND SYS_FUNCT NOT

%%

program : program_head routine DOT {
    $$ = makeNewNode();
    $$->nodeKind = program_NodeKind;
    if ($1 != NULL) {
        $$->child = $1;
        currentline = $$->line_no = $1->line_no;
        $1->sibling = $2;

        releaseNode($3);

        savedTree = $$;
        updateConstPart();
    }
}
| error {
    printf("----missing dot at the end of the file\n");
    $$ = NULL;
}
;

program_head : PROGRAM ID SEMI {
    $$ = makeNewNode();
    $$->nodeKind = program_head_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
    releaseNode($3);
}
| error {
    printf("----program head error\n");
    $$ = NULL;
}
;

routine : routine_head routine_body {
    $$ = makeNewNode();
    $$->nodeKind = routine_NodeKind;
    if ($1 != NULL) {
        $$->child = $1;
        currentline = $$->line_no = $1->line_no;
        $1->sibling = $2;
    } else if ($2 != NULL) {
        $$->child = $2;
        currentline = $$->line_no = $2->line_no;
    } else {
        $$->child = NULL;
    }
}
;

routine_head : label_part const_part type_part var_part routine_part {
    $$ = makeNewNode();
    $$->nodeKind = routine_head_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $2;
    $2->sibling = $3;
    $3->sibling = $4;
    $4->sibling = $5;
}
| error {
    printf("----routine header error detected\n");
    $$ = NULL;
}
;

sub_routine : routine_head routine_body {
    $$ = makeNewNode();
    $$->nodeKind = sub_routine_NodeKind;
    if ($1 != NULL) {
        $$->child = $1;
        currentline = $$->line_no = $1->line_no;
        $1->sibling = $2;
    } else if ($2 != NULL) {
        $$->child = $2;
        currentline = $$->line_no = $2->line_no;
    } else {
        $$->child = NULL;
    }
}
;

label_part : empty {
    $$ = makeNewNode();
    $$->nodeKind = empty_label_part_NodeKind;
    $$->line_no = currentline;
}
;

const_part : CONST const_expr_list {
    $$ = makeNewNode();
    $$->nodeKind = const_part_NodeKind;

    if ($2 == NULL) {
    	$$->nodeKind = empty_const_part_NodeKind;
    }

    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
}
| empty {
    $$ = makeNewNode();
    $$->nodeKind = empty_const_part_NodeKind;
    $$->line_no = currentline;
}
;

const_expr_list : const_expr_list const_expr {
	if ($1 != NULL) {
		TreeNode * temp = $1;
		while (temp->sibling != NULL) {
		    temp = temp->sibling;
		}
		temp->sibling = $2;
    	$$ = $1;
    }
    else {
    	$$ = $2;
    }
}
| const_expr {
    $$ = $1;
}
| const_expr_list error {
    printf("----const declaration error detected\n");
	$$ = $1;
}
| error {
    printf("----const declaration error detected\n");
	$$ = NULL;
}
;

const_expr : ID EQUAL const_value SEMI {
    $$ = makeNewNode();
    $$->nodeKind = const_expr_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

const_value : INTEGER {
    $$ = $1;
    $$->nodeKind = integer_const_value_NodeKind;
    currentline = $$->line_no;

    $$->computable = 1;
    $$->result = atoi($$->literal);
    $$->type = 1;
}
| REAL {
    $$ = $1;
    $$->nodeKind = real_const_value_NodeKind;
    currentline = $$->line_no;
}
| CHAR {
    $$ = $1;
    $$->nodeKind = char_const_value_NodeKind;
    currentline = $$->line_no;
}
| STRING {
    $$ = $1;
    $$->nodeKind = string_const_value_NodeKind;
    currentline = $$->line_no;
}
| SYS_CON {
    $$ = $1;
    if ($$->literal[0] == 'm') {
        free($$->literal);

        char buffer[15];
        itoa(2147483647, buffer, 10);
        $$->literal = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
        strcpy($$->literal, buffer);
        $$->nodeKind = integer_const_value_NodeKind;

        $$->result = 2147483647;
            $$->type = 1;
    } else {
        $$->nodeKind = sys_con_const_value_NodeKind;
        $$->result = (($$->literal)[0] == 't') ? 1 : 0;
        $$->type = 0;
    }

    $$->computable = 1;
    currentline = $$->line_no;
}
;

type_part : TYPE type_decl_list {
    $$ = makeNewNode();
    $$->nodeKind = type_part_NodeKind;

    if ($2 == NULL) {
        $$->nodeKind = empty_type_part_NodeKind;
    }

    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
}
| empty {
    $$ = makeNewNode();
    $$->nodeKind = empty_type_part_NodeKind;
    $$->line_no = currentline;
}
;

type_decl_list : type_decl_list type_definition {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| type_definition {
    $$ = $1;
}
| type_decl_list error {
    printf("----type declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----type declaration error detected\n");
    $$ = NULL;
}
;

type_definition : ID EQUAL type_decl SEMI {
    $$ = makeNewNode();
    $$->nodeKind = type_definition_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

type_decl : simple_type_decl {
    $$ = $1;
    currentline = $$->line_no;
}
| array_type_decl {
    $$ = $1;
    currentline = $$->line_no;
}
| record_type_decl {
    $$ = $1;
    currentline = $$->line_no;
}
;

array_type_decl : ARRAY LB simple_type_decl RB OF type_decl {
    $$ = makeNewNode();
    $$->nodeKind = array_type_decl_NodeKind;
    $$->child = $3;
    currentline = $$->line_no = $1->line_no;
    $3->sibling = $6;

    releaseNode($1);
    releaseNode($2);
    releaseNode($4);
    releaseNode($5);
}
;

record_type_decl : RECORD field_decl_list END {
    $$ = makeNewNode();
    $$->nodeKind = record_type_decl_NodeKind;

    if ($2 == NULL) {
        // error detected, no need to process further, exit
    }

    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
    releaseNode($3);
}
;

field_decl_list : field_decl_list field_decl {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| field_decl {
    $$ = $1;
}
| field_decl_list error {
    printf("----record declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----record declaration error detected\n");
    $$ = NULL;
}
;

field_decl : name_list COLON type_decl SEMI {
    $$ = makeNewNode();
    $$->nodeKind = field_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

name_list : name_list_1 {
    $$ = makeNewNode();
    $$->nodeKind = name_list_NodeKind;
    $$->line_no = currentline;
    if ($1 != NULL) {
        $$->child = $1;
        currentline = $$->line_no = $1->line_no;
    }
}
;

name_list_1 : name_list_1 COMMA ID {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $3;
        $$ = $1;
    }
    else {
        $$ = $3;
    }

    releaseNode($2);
}
| ID {
    $$ = $1;
}
| name_list_1 error {
    printf("----name_list error detected\n");
    $$ = $1;
}
| error {
    printf("----name_list error detected\n");
    $$ = NULL;
}
;

simple_type_decl : SYS_TYPE {
    $$ = $1;
    $$->nodeKind = sys_type_simple_type_decl_NodeKind;
    currentline = $$->line_no;
}
| ID {
    $$ = $1;
    $$->nodeKind = id_simple_type_decl_NodeKind;
    currentline = $$->line_no;
}
| LP name_list RP {
    $$ = makeNewNode();
    $$->nodeKind = lp_name_list_rp_simple_type_decl_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
    releaseNode($3);
}
| const_value DOTDOT const_value {
    $$ = makeNewNode();
    $$->nodeKind = const_dotdot_const_simple_type_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
}
| MINUS const_value DOTDOT const_value {
    $$ = makeNewNode();
    $$->nodeKind = m_const_dotdot_const_simple_type_decl_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $4;

    releaseNode($1);
    releaseNode($3);
}
| MINUS const_value DOTDOT MINUS const_value {
    $$ = makeNewNode();
    $$->nodeKind = m_const_dotdot_m_const_simple_type_decl_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $5;

    releaseNode($1);
    releaseNode($3);
    releaseNode($4);
}
| ID DOTDOT ID {
    $$ = makeNewNode();
    $$->nodeKind = id_dotdot_id_simple_type_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
}
;

var_part : VAR var_decl_list {
    $$ = makeNewNode();
    $$->nodeKind = var_part_NodeKind;

    if ($2 == NULL) {
        $$->nodeKind = empty_var_part_NodeKind;
    }

    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
}
| empty {
	$$ = makeNewNode();
    $$->nodeKind = empty_var_part_NodeKind;
    $$->line_no = currentline;
}
;

var_decl_list : var_decl_list var_decl {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| var_decl {
    $$ = $1;
}
| var_decl_list error {
    printf("----var declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----var declaration error detected\n");
    $$ = NULL;
}
;

var_decl : name_list COLON type_decl SEMI {
    $$ = makeNewNode();
    $$->nodeKind = var_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

routine_part : routine_part_1 {
    $$ = makeNewNode();
    $$->nodeKind = routine_part_NodeKind;
    $$->line_no = currentline;
    if ($1 != NULL) {
        currentline = $$->line_no = $1->line_no;
        $$->child = $1;
    }
}
;

routine_part_1 : routine_part_1 function_decl {
    TreeNode * temp = $1;
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| routine_part_1 procedure_decl {
    TreeNode * temp = $1;
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| empty {
    $$ = $1;
}
| routine_part_1 error {
    printf("----routine declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----routine declaration error detected\n");
    $$ = NULL;
}
;

function_decl : function_head SEMI sub_routine SEMI {
    $$ = makeNewNode();
    $$->nodeKind = function_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

function_head : FUNCTION ID parameters COLON simple_type_decl {
    $$ = makeNewNode();
    $$->nodeKind = function_head_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $3;
    $3->sibling = $5;

    releaseNode($1);
    releaseNode($4);
}
;

procedure_decl : procedure_head SEMI sub_routine SEMI {
    $$ = makeNewNode();
    $$->nodeKind = procedure_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

procedure_head : PROCEDURE ID parameters {
    $$ = makeNewNode();
    $$->nodeKind = procedure_head_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $3;

    releaseNode($1);
}
;

parameters : LP para_decl_list RP {
    $$ = makeNewNode();
    $$->nodeKind = parameters_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
    releaseNode($3);
}
| empty {
    $$ = makeNewNode();
    $$->nodeKind = empty_parameters_NodeKind;
    $$->line_no = currentline;
}
;

para_decl_list : para_decl_list SEMI para_decl {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $3;
        $$ = $1;
    }
    else {
        $$ = $3;
    }

    releaseNode($2);
}
| para_decl {
    $$ = $1;
}
| para_decl_list error {
    printf("----parameter list declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----parameter list declaration error detected\n");
    $$ = NULL;
}
;

para_decl : VAR name_list COLON simple_type_decl {
    $$ = makeNewNode();
    $$->nodeKind = var_para_decl_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $4;

    releaseNode($1);
    releaseNode($3);
}
| name_list COLON simple_type_decl {
    $$ = makeNewNode();
    $$->nodeKind = non_var_para_decl_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
}
;

routine_body : compound_stmt {
    $$ = makeNewNode();
    $$->nodeKind = routine_body_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
| error {
    printf("----routine body declaration error detected\n");
    $$ = NULL;
}
;

stmt_list : stmt_list_1 {
    $$ = makeNewNode();
    $$->nodeKind = stmt_list_NodeKind;
    $$->line_no = currentline;
    if ($1 != NULL) {
        currentline = $$->line_no = $1->line_no;
        $$->child = eliminateUselessFromList($1);
    }
}
;

stmt_list_1 : stmt_list_1 stmt SEMI {
    TreeNode * temp = $1;
    if (temp != NULL) {
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }

    releaseNode($3);
}
| empty {
    $$ = $1;
}
| stmt_list_1 error SEMI {
    printf("----statement error detected\n");
    $$ = $1;
}
| error SEMI {
    printf("----statement error detected\n");
    $$ = NULL;
}
| error {
    printf("----statement error detected\n");
    $$ = NULL;
}
;

stmt : INTEGER COLON non_label_stmt {
    $$ = makeNewNode();
    $$->nodeKind = labeled_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
}
| non_label_stmt {
    $$ = makeNewNode();
    $$->nodeKind = non_labeled_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
;

non_label_stmt : assign_stmt {
    $$ = $1;
}
| proc_stmt {
    $$ = $1;
}
| compound_stmt {
    $$ = $1;
}
| if_stmt {
    $$ = $1;
}
| repeat_stmt {
    $$ = $1;
}
| while_stmt {
    $$ = $1;
}
| for_stmt {
    $$ = $1;
}
| case_stmt {
    $$ = $1;
}
| goto_stmt {
    $$ = $1;
}
;

assign_stmt : ID ASSIGN expression {
    $$ = makeNewNode();
    $$->nodeKind = id_assign_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $3 = closeExpression($3);
    $1->sibling = $3;

    releaseNode($2);
}
| ID LB expression RB ASSIGN expression {
    $$ = makeNewNode();
    $$->nodeKind = id_lb_exp_rb_assign_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $3 = closeExpression($3);
    $6 = closeExpression($6);
    $1->sibling = $3;
    $3->sibling = $6;

    releaseNode($2);
    releaseNode($4);
    releaseNode($5);
}
| ID DOT ID ASSIGN expression {
    $$ = makeNewNode();
    $$->nodeKind = id_dot_id_assign_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;
    $5 = closeExpression($5);
    $3->sibling = $5;

    releaseNode($2);
    releaseNode($4);
}
;

proc_stmt : ID {
    $$ = makeNewNode();
    $$->nodeKind = id_proc_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
| ID LP args_list RP {
    $$ = makeNewNode();
    $$->nodeKind = id_lp_args_rp_proc_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| SYS_PROC {
    $$ = makeNewNode();
    $$->nodeKind = sys_proc_proc_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
| SYS_PROC LP args_list RP {
    $$ = makeNewNode();
    $$->nodeKind = sys_proc_lp_args_rp_proc_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| READ LP factor RP {
    $$ = makeNewNode();
    $$->nodeKind = read_lp_factor_rp_proc_stmt_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

compound_stmt : BEGIN_PASCAL stmt_list END {
    $$ = makeNewNode();
    $$->nodeKind = compound_stmt_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
    releaseNode($3);
}
;

if_stmt : IF expression THEN stmt else_clause {
    $2 = closeExpression($2);

    int boolRes = checkBool($2);
    if (boolRes == 0) {        // always false, take else
        if ($5->nodeKind == empty_else_clause_NodeKind) {
    		$$ = makeNewNode();
            $$->nodeKind = useless_stmt_NodeKind;
    		$$->line_no = currentline;
        } else {
            $$ = getStmtNode($5->child);
            setStmtNodeToNULL($5->child);
        }
        releaseNode($2);
        releaseNode($4);
        releaseNode($5);
    }
    else if (boolRes == 1) {    // always true, take if
        $$ = getStmtNode($4);
        setStmtNodeToNULL($4);
        releaseNode($4);
        releaseNode($2);
        releaseNode($5);
    }
    else {
    	$$ = makeNewNode();
    	$$->nodeKind = if_stmt_NodeKind;
	    $$->child = $2;
	    $2->sibling = $4;
	    $4->sibling = $5;
    }

    currentline = $$->line_no = $1->line_no;
    releaseNode($1);
    releaseNode($3);
}
;

else_clause : ELSE stmt {
    $$ = makeNewNode();
    $$->nodeKind = else_clause_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
}
| empty {
    $$ = makeNewNode();
    $$->nodeKind = empty_else_clause_NodeKind;
    $$->line_no = currentline;
}
;

repeat_stmt : REPEAT stmt_list UNTIL expression {
    $$ = makeNewNode();
    $$->nodeKind = repeat_stmt_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $4 = closeExpression($4);
    $2->sibling = $4;

    releaseNode($1);
    releaseNode($3);
}
;

while_stmt : WHILE expression DO stmt {
    $2 = closeExpression($2);

    int boolRes = checkBool($2);
    if (boolRes == 0) {		// always false
	    $$ = makeNewNode();
	    $$->nodeKind = useless_stmt_NodeKind;
	    releaseNode($2);
	    releaseNode($4);
    }
    else {
	    $$ = makeNewNode();
	    $$->nodeKind = while_stmt_NodeKind;
	    $$->child = $2;
	    $2->sibling = $4;
    }

	currentline = $$->line_no = $1->line_no;
    releaseNode($1);
    releaseNode($3);
}
;

for_stmt : FOR ID ASSIGN expression direction expression DO stmt {
    $$ = makeNewNode();
    $$->nodeKind = for_stmt_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $4 = closeExpression($4);
    $6 = closeExpression($6);
    $2->sibling = $4;
    $4->sibling = $5;
    $5->sibling = $6;
    $6->sibling = $8;

    releaseNode($1);
    releaseNode($3);
    releaseNode($7);
}
;

direction : TO {
    $$ = $1;
    $$->nodeKind = to_direction_NodeKind;
    currentline = $$->line_no;
}
| DOWNTO {
    $$ = $1;
    $$->nodeKind = down_direction_NodeKind;
    currentline = $$->line_no;
}
;

case_stmt : CASE expression OF case_expr_list END {
    $$ = makeNewNode();
    $$->nodeKind = case_stmt_NodeKind;
    $2 = closeExpression($2);
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;
    $2->sibling = $4;

    releaseNode($1);
    releaseNode($3);
    releaseNode($5);
}
;

case_expr_list : case_expr_list_1 {
    $$ = makeNewNode();
    $$->nodeKind = case_expr_list_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
;

case_expr_list_1 : case_expr_list_1 case_expr {
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $2;
        $$ = $1;
    }
    else {
        $$ = $2;
    }
}
| case_expr {
    $$ = $1;
}
| case_expr_list_1 error {
    printf("----case declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----case declaration error detected\n");
    $$ = NULL;
}
;

case_expr : const_value COLON stmt SEMI {
    $$ = makeNewNode();
    $$->nodeKind = const_case_expr_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| ID COLON stmt SEMI {
    $$ = makeNewNode();
    $$->nodeKind = id_case_expr_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
;

goto_stmt : GOTO INTEGER {
    $$ = makeNewNode();
    $$->nodeKind = goto_stmt_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    releaseNode($1);
}
;

expression : expression expression_op expr {
    $$ = makeNewNode();
    $$->nodeKind = expression_NodeKind;
    currentline = $$->line_no = $1->line_no;

    if ($1->computable == 1 && $3->computable == 1) {

        $$->computable = 1;
        $$->type = 0;

        switch ($2->nodeKind) {
            case ge_expression_op_NodeKind: {
                $$->result = ($1->result >= $3->result) ? 1 : 0;
            }
                break;
            case gt_expression_op_NodeKind: {
                $$->result = ($1->result > $3->result) ? 1 : 0;
            }
                break;
            case le_expression_op_NodeKind: {
                $$->result = ($1->result <= $3->result) ? 1 : 0;
            }
                break;
            case lt_expression_op_NodeKind: {
                $$->result = ($1->result < $3->result) ? 1 : 0;
            }
                break;
            case equal_expression_op_NodeKind: {
                $$->result = ($1->result == $3->result) ? 1 : 0;
            }
                break;
            case unequal_expression_op_NodeKind: {
                $$->result = ($1->result != $3->result) ? 1 : 0;
            }
                break;
        }
    } else {
        if ($1->computable == 1) {
            TreeNode * temp = makeNewExpressionNode($1->type, $1->result, currentline);
            releaseNode($1);
            $1 = temp;
        } else if ($3->computable == 1) {
            TreeNode * temp = makeNewExprNode($3->type, $3->result, currentline);
            releaseNode($3);
            $3 = temp;
        }
    }

    $$->child = $1;
    $1->sibling = $2;
    $2->sibling = $3;
}
| expr {
    $$ = makeNewNode();
    $$->nodeKind = end_expression_NodeKind;
    $$->child = $1;
    $$->line_no = currentline = $1->line_no;

    if ($1->computable == 1) {
        $$->computable = 1;
        $$->result = $1->result;
        $$->type = $1->type;
    }
}
;

expression_op : GE {
    $$ = $1;
    $$->nodeKind = ge_expression_op_NodeKind;
    currentline = $$->line_no;
}
| GT {
    $$ = $1;
    $$->nodeKind = gt_expression_op_NodeKind;
    currentline = $$->line_no;
}
| LE {
    $$ = $1;
    $$->nodeKind = le_expression_op_NodeKind;
    currentline = $$->line_no;
}
| LT {
    $$ = $1;
    $$->nodeKind = lt_expression_op_NodeKind;
    currentline = $$->line_no;
}
| EQUAL {
    $$ = $1;
    $$->nodeKind = equal_expression_op_NodeKind;
    currentline = $$->line_no;
}
| UNEQUAL {
    $$ = $1;
    $$->nodeKind = unequal_expression_op_NodeKind;
    currentline = $$->line_no;
}
;

expr : expr expr_op term {
    $$ = makeNewNode();
    $$->nodeKind = expr_NodeKind;
    currentline = $$->line_no = $1->line_no;

    if  (
        ($1->computable == 1 && $3->computable == 1 && $1->type == $3->type)
        &&
        (($2->nodeKind == or_expr_op_NodeKind && $1->type == 0) ||
         ($2->nodeKind != or_expr_op_NodeKind && $1->type == 1))
        ) {

        $$->computable = 1;
        $$->type = $1->type;

        switch ($2->nodeKind) {
            case plus_expr_op_NodeKind: {
                $$->result = $1->result + $3->result;
            }
                break;
            case minus_expr_op_NodeKind: {
                $$->result = $1->result - $3->result;
            }
                break;
            case or_expr_op_NodeKind: {
                $$->result = $1->result | $3->result;
            }
                break;
        }
    }
    else {
        if ($1->computable == 1) {
            TreeNode * temp = makeNewExprNode($1->type, $1->result, currentline);
            releaseNode($1);
            $1 = temp;
        } else if ($3->computable == 1) {
            TreeNode * temp = makeNewTermNode($3->type, $3->result, currentline);
            releaseNode($3);
            $3 = temp;
        }
    }

    $$->child = $1;
    $1->sibling = $2;
    $2->sibling = $3;
}
| term {
    $$ = makeNewNode();
    $$->nodeKind = end_expr_NodeKind;
    $$->line_no = currentline = $1->line_no;
    $$->child = $1;

    if ($1->computable == 1) {
        $$->computable = 1;
        $$->result = $1->result;
        $$->type = $1->type;
    }
}
;

expr_op : PLUS {
    $$ = $1;
    $$->nodeKind = plus_expr_op_NodeKind;
    currentline = $$->line_no;
}
| MINUS {
    $$ = $1;
    $$->nodeKind = minus_expr_op_NodeKind;
    currentline = $$->line_no;
}
| OR {
    $$ = $1;
    $$->nodeKind = or_expr_op_NodeKind;
    currentline = $$->line_no;
}
;

term : term term_op factor {
    $$ = makeNewNode();
    $$->nodeKind = term_NodeKind;
    currentline = $$->line_no = $1->line_no;

    if  (
        ($1->computable == 1 && $3->computable == 1 && $1->type == $3->type)
        &&
        (($2->nodeKind == and_term_op_NodeKind && $1->type == 0) ||
         ($2->nodeKind != and_term_op_NodeKind && $1->type == 1))
        ) {

        $$->computable = 1;
        $$->type = $1->type;

        switch ($2->nodeKind) {
            case mul_term_op_NodeKind: {
                $$->result = $1->result * $3->result;
            }
                break;
            case div_term_op_NodeKind: {
                $$->result = $1->result / $3->result;
            }
                break;
            case mod_term_op_NodeKind: {
                $$->result = $1->result % $3->result;
            }
                break;
            case and_term_op_NodeKind: {
                $$->result = $1->result & $3->result;
            }
                break;
        }
    }
    else {
        if ($1->computable == 1) {
            TreeNode * temp = makeNewTermNode($1->type, $1->result, currentline);
            releaseNode($1);
            $1 = temp;
        } else if ($3->computable == 1) {
            TreeNode * temp = makeNewFactorNode($3->type, $3->result, currentline);
            releaseNode($3);
            $3 = temp;
        }
    }

    $$->child = $1;
    $1->sibling = $2;
    $2->sibling = $3;
}
| factor {
    $$ = makeNewNode();
    $$->nodeKind = end_term_NodeKind;
    $$->line_no = currentline = $1->line_no;
    $$->child = $1;

    if ($1->computable == 1) {
        $$->computable = 1;
        $$->result = $1->result;
        $$->type = $1->type;
    }
}
;

term_op : MUL {
    $$ = $1;
    $$->nodeKind = mul_term_op_NodeKind;
    currentline = $$->line_no;
}
| DIV {
    $$ = $1;
    $$->nodeKind = div_term_op_NodeKind;
    currentline = $$->line_no;
}
| MOD {
    $$ = $1;
    $$->nodeKind = mod_term_op_NodeKind;
    currentline = $$->line_no;
}
| AND {
    $$ = $1;
    $$->nodeKind = and_term_op_NodeKind;
    currentline = $$->line_no;
}
;

factor : ID {
    $$ = makeNewNode();
    $$->nodeKind = id_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
| ID LP args_list RP {
    $$ = makeNewNode();
    $$->nodeKind = id_lp_args_rp_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| SYS_FUNCT {
    $$ = makeNewNode();
    $$->nodeKind = sys_func_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
}
| SYS_FUNCT LP args_list RP {
    $$ = makeNewNode();
    $$->nodeKind = sys_func_lp_args_rp_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| const_value {
    $$ = makeNewNode();
    $$->nodeKind = const_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;

    if ($1->computable == 1) {
        $$->computable = 1;
        $$->result = $1->result;
        $$->type = $1->type;
    }

    if ($1->nodeKind == string_const_value_NodeKind) {
            stringConstNode * temp = insertIntoStringConstTable($1);        
            TreeNode * t = makeNewNode();       
            t->literal = (char *)malloc(strlen(temp->name) * sizeof(char) + 1);         
            strcpy(t->literal, temp->name);
            
            t->line_no = $1->line_no;       
            releaseNode($1);
            $$->nodeKind = id_factor_NodeKind;      
            $$->child = t;
  
    }
}
| LP expression RP {
    $$ = makeNewNode();
    $$->nodeKind = lp_exp_rp_factor_NodeKind;
    //$2 = closeExpression($2);
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    if ($2->computable == 1) {
        $$->computable = 1;
        $$->type = $2->type;
        $$->result = $2->result;
    }

    releaseNode($1);
    releaseNode($3);
}
| NOT factor {
    $$ = makeNewNode();
    $$->nodeKind = not_factor_factor_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    if ($2->computable == 1 && $2->type == 0) {
        $$->computable = 1;
        $$->result = 1 - $2->result;
        $$->type = $2->type;
    }

    releaseNode($1);
}
| MINUS factor {
    $$ = makeNewNode();
    $$->nodeKind = minus_factor_factor_NodeKind;
    $$->child = $2;
    currentline = $$->line_no = $1->line_no;

    if ($2->computable == 1 && $2->type == 1) {
        $$->computable = 1;
        $$->result = 0 - $2->result;
        $$->type = $2->type;
    }

    releaseNode($1);
}
| ID LB expression RB {
    $$ = makeNewNode();
    $$->nodeKind = id_lb_exp_rb_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $3 = closeExpression($3);
    $1->sibling = $3;

    releaseNode($2);
    releaseNode($4);
}
| ID DOT ID {
    $$ = makeNewNode();
    $$->nodeKind = id_dot_id_factor_NodeKind;
    $$->child = $1;
    currentline = $$->line_no = $1->line_no;
    $1->sibling = $3;

    releaseNode($2);
}
;

args_list : args_list_1 {
    $$ = makeNewNode();
    $$->nodeKind = args_list_NodeKind;
    $$->line_no = currentline;
    if ($1 != NULL) {
        $$->child = $1;
        currentline = $$->line_no = $1->line_no;
    }
}
;

args_list_1 : args_list_1 COMMA expression {
    $3 = closeExpression($3);
    if ($1 != NULL) {
        TreeNode * temp = $1;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = $3;
        $$ = $1;
    }
    else {
        $$ = $3;
    }

    releaseNode($2);
}
| expression {
    $1 = closeExpression($1);
    $$ = $1;
}
| args_list_1 COMMA error {
    printf("----argument list declaration error detected\n");
    $$ = $1;
}
| error {
    printf("----argument list declaration error detected\n");
    $$ = NULL;
}
;

empty : {
    $$ = NULL;
}
;

%%

int main(int argc, char** argv) {
    openFile(argc, argv);

    errorOccur = 0;
    yyparse();

    int uncle[200] = {0};
    printThisTree(savedTree, uncle, 0);

    if (errorOccur != 0) {
        printf("%d syntax error found, parsing failed.\n", errorOccur);
        exit(0);
    }

    MainVarTable = (VarTable*)malloc(sizeof(VarTable));
    MainConstTable = (ConstTable*)malloc(sizeof(VarTable));
    MainTypeTable = (TypeTable*)malloc(sizeof(TypeTable));
    MainProcedureTable = (ProcedureTable*)malloc(sizeof(ProcedureTable));
    int i = 0;
    for(i = 0; i < 50; i++)
    {
        MainVarTable->bucket[i] = NULL;
        MainConstTable->bucket[i] = NULL;
        MainTypeTable->bucket[i] = NULL;
        MainProcedureTable->bucket[i] = NULL;
    }

    errorOccur = 0;

    searchTree(savedTree, MainConstTable,MainTypeTable,MainVarTable, MainProcedureTable);

    if (errorOccur != 0) {
        printf("%d syntax error found, parsing failed.\n", errorOccur);
        exit(0);
    }

    printConstTable(MainConstTable);
    printTypeTable(MainTypeTable);
    printVarTable(MainVarTable);
    printProcedureTable(MainProcedureTable);

    typeCheck(savedTree,"main");
    int uncle1[200]={0};
    printThisTree(savedTree, uncle1, 0);
    FILE *fp =fopen("test.code","w");
    ConvertConstToCode(MainConstTable, fp);
    make_code("test.code", fp);
   // releaseNode(savedTree);

    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "%s around line %d\n", s, currentline);
    errorOccur++;
    return (0);
}

void printAncestor(int *uncle, int level) {
    int i = 0;
    for (; i < level - 1; ++i) {
        if (uncle[i] == 1) {
            printf("|");
        }
        else {
            printf(" ");
        }
        int j = 0;
        for (; j < WIDTH - 1; ++j)    {
            printf(" ");
        }
    }
}

void printThisTree(TreeNode * t, int *uncle, int level) {
    if (t == NULL)
        return;

    printAncestor(uncle, level);
    if (level != 0) {
        printf("|");
        int i = 0;
        for (; i < WIDTH - 1; ++i) {
            printf("-");
        }
    }

    if (t->literal) {
        printf("%s-(%s-%d-%d-%d-%d)-%s-%d\n", t->literal, t->label,t->address,t->size,t->level,t->leveltofather, NodeKindStr[t->nodeKind], t->Type);
    }
    else {
        if (t->nodeKind >= 0 && t->nodeKind < 97) {
            printf("%s%d\n", NodeKindStr[t->nodeKind], t->line_no);
        }
        else {
            printf("%c%d\n", 0x01, t->nodeKind);
        }
    }

    TreeNode * k = t->child;
    while (k != NULL) {

        if (k->sibling) {
            uncle[level] = 1;
        }
        else {
            uncle[level] = 0;
        }

        int i = 0;
        for (; i < HEIGHT; i++) {
            printAncestor(uncle, level + 1);
            printf("|\n");
        }

        printThisTree(k, uncle, level + 1);

        k = k->sibling;
    }
}

TreeNode * makeNewConstNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->line_no = line_no;

    if (type == 0) {    // boolean
        char trueStr[] = "true";
        char falseStr[] = "false";
        temp->nodeKind = sys_con_const_value_NodeKind;
        if (value > 0) {
            temp->literal = (char *)malloc(strlen(trueStr) * sizeof(char) + 1);
            strcpy(temp->literal, trueStr);
        }
        else {
            temp->literal = (char *)malloc(strlen(falseStr) * sizeof(char) + 1);
            strcpy(temp->literal, falseStr);
        }
    } else {            // int
        temp->nodeKind = integer_const_value_NodeKind;
        char buffer[50];
        itoa(value, buffer, 10);
        temp->literal = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
        strcpy(temp->literal, buffer);
    }

    return temp;
}

TreeNode * makeNewFactorNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->line_no = line_no;

    if (type != 0 && value < 0) {
        temp->nodeKind = minus_factor_factor_NodeKind;
        temp->child = makeNewFactorNode(type, (-1 * value), line_no);
        return temp;
    }

    temp->nodeKind = const_factor_NodeKind;
    temp->child = makeNewConstNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewTermNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_term_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewFactorNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewExprNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_expr_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewTermNode(type, value, line_no);
    return temp;
}

TreeNode * makeNewExpressionNode(int type, int value, int line_no) {
    TreeNode *temp = makeNewNode();
    temp->nodeKind = end_expression_NodeKind;
    temp->line_no = line_no;
    temp->child = makeNewExprNode(type, value, line_no);
    return temp;
}

TreeNode * closeExpression(TreeNode * k) {

    if (k->computable == 1) {
        TreeNode * temp = makeNewExpressionNode(k->type, k->result, currentline);
        releaseNode(k);
        k = temp;
    }

    return k;
}

void itoa(int value, char *buf, int radix) {
    sprintf(buf, "%d", value);
}

int checkBool(TreeNode * t) {
    if (t->nodeKind != end_expression_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != end_expr_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != end_term_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind != const_factor_NodeKind) {
        return -1;
    }
    t = t->child;

    if (t->nodeKind == integer_const_value_NodeKind) {
        return (atoi(t->literal) != 0) ? 1 : 0;
    }
    else if (t->nodeKind == sys_con_const_value_NodeKind) {
        return (t->literal[0] == 't') ? 1 : 0;
    }

    return -1;
}

TreeNode * eliminateUselessFromList(TreeNode * t) {
	TreeNode * head = makeNewNode();
	TreeNode * temp = head;
	while (t != NULL) {
		if (isUseless(t)) {
			TreeNode * tmp = t;
			t = t->sibling;
			tmp->sibling = NULL;
			releaseNode(tmp);
		} else {
			temp->sibling = t;
			temp = t;
			t = t->sibling;
		}
	}
	return head->sibling;
}

int isUseless(TreeNode * t) {
	return (getStmtNode(t)->nodeKind == useless_stmt_NodeKind) ? 1 : 0;
}

TreeNode * getStmtNode(TreeNode * t) {
	if (t->nodeKind == labeled_stmt_NodeKind) {
		return t->child->sibling;
	}
	return t->child;
}

void setStmtNodeToNULL(TreeNode * t) {
	if (t->nodeKind == labeled_stmt_NodeKind) {
		t->child->sibling = NULL;
	} else {
		t->child = NULL;
	}
}

stringConstNode * makeNewStringConstNode() {
	stringConstNode * temp = (stringConstNode *)malloc(sizeof(stringConstNode));
	temp->next = NULL;
	temp->name = NULL;
	temp->value = NULL;

	return temp;
}

void releaseStringConstNode(stringConstNode * t) {
	if (t == NULL) {
		return;
	}

	if (t->name != NULL) {
		free(t->name);
	}

	if (t->value != NULL) {
		free(t->value);
	}

	releaseStringConstNode(t->next);
}

void printStringConstTable() {
	stringConstNode * temp = stringConstTable;
	while (temp != NULL) {
		printf("%s %s\n", temp->name, temp->value);
		temp = temp->next;
	}
}

stringConstNode * insertIntoStringConstTable(TreeNode * t) {
	stringConstCount++;

	stringConstNode * temp = NULL;
	if (stringConstTable == NULL) {
		stringConstTable = makeNewStringConstNode();
		temp = stringConstTable;
	} else {
		temp = stringConstTable;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = makeNewStringConstNode();
		temp = temp->next;
	}
	char buffer[50];
	sprintf(buffer, "stringconst%d", stringConstCount);
	temp->name = (char *)malloc(strlen(buffer) * sizeof(char) + 1);
	strcpy(temp->name, buffer);

	temp->value = (char *)malloc(strlen(t->literal) * sizeof(char) + 1);
	strcpy(temp->value, t->literal);

	return temp;
}

void updateConstPart() {
	//printStringConstTable();
	if (stringConstTable == NULL) {
		return;
	}

	TreeNode *routine = getChild(2, savedTree);
	TreeNode *routine_head = getChild(1, routine);
	TreeNode *const_part = getChild(2, routine_head); //const_part

	if (const_part->nodeKind == empty_const_part_NodeKind) {
		TreeNode * temp = makeNewNode();
		temp->nodeKind = const_part_NodeKind;
		routine_head->child->sibling = temp;
        temp->sibling = const_part->sibling;
        const_part->sibling = NULL;
		releaseNode(const_part);
		const_part = temp;
	}

	stringConstNode * sconst = stringConstTable;
	do {
		//printf("1\n");
		insertIntoConstPart(sconst, const_part);
		sconst = sconst->next;
	} while (sconst != NULL);

    releaseStringConstNode(stringConstTable);
}

void insertIntoConstPart(stringConstNode * sconst, TreeNode * const_part) {
	TreeNode * const_expr = makeNewNode();
	const_expr->nodeKind = const_expr_NodeKind;

	TreeNode * id = makeNewNode();
	id->nodeKind = 0;
	id->literal = (char *)malloc(strlen(sconst->name) * sizeof(char) + 1);
	strcpy(id->literal, sconst->name);

	TreeNode * const_value = makeNewNode();
	const_value->nodeKind = string_const_value_NodeKind;
	const_value->literal = (char *)malloc(strlen(sconst->value) * sizeof(char) + 1);
	strcpy(const_value->literal, sconst->value);

	const_expr->child = id;
	id->sibling = const_value;

	TreeNode * temp = const_part->child;
	const_part->child = const_expr;
	const_expr->sibling = temp;
}
