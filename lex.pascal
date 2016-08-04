%{

#include "global.h"
#include "y.tab.h"

int line_no = 1;

%}

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]
sl-comment "//".*
ml-comment-a "(*"([^\*]|[\*]+[^\*\)])*[\*]*"*)"
ml-comment-b "{"([^}]|\n)*"}"

%%

{A}{B}{S} return makeThisNode(SYS_FUNCT);
{A}{N}{D} return makeThisNode(AND);
{A}{R}{R}{A}{Y} return makeThisNode(ARRAY);
{B}{E}{G}{I}{N} return makeThisNode(BEGIN_PASCAL);
{B}{O}{O}{L}{E}{A}{N} return makeThisNode(SYS_TYPE);
{C}{A}{S}{E} return makeThisNode(CASE);
{C}{H}{A}{R} return makeThisNode(SYS_TYPE);
{C}{H}{R} return makeThisNode(SYS_FUNCT);
{C}{O}{N}{S}{T} return makeThisNode(CONST);

{D}{O}{W}{N}{T}{O} return makeThisNode(DOWNTO);
{D}{O} return makeThisNode(DO);

{E}{L}{S}{E} return makeThisNode(ELSE);
{E}{N}{D} return makeThisNode(END);
{F}{A}{L}{S}{E} return makeThisNode(SYS_CON);
{F}{O}{R} return makeThisNode(FOR);
{F}{U}{N}{C}{T}{I}{O}{N} return makeThisNode(FUNCTION);
{G}{O}{T}{O} return makeThisNode(GOTO);
{I}{F} return makeThisNode(IF);
{I}{N}{T}{E}{G}{E}{R} return makeThisNode(SYS_TYPE);
{M}{O}{D} return makeThisNode(MOD);
{M}{A}{X}{I}{N}{T} return makeThisNode(SYS_CON);
{N}{O}{T} return makeThisNode(NOT);
{O}{D}{D} return makeThisNode(SYS_FUNCT);
{O}{F} return makeThisNode(OF);

{O}{R}{D} return makeThisNode(SYS_FUNCT);
{O}{R} return makeThisNode(OR);

{P}{R}{E}{D} return makeThisNode(SYS_FUNCT);
{P}{R}{O}{C}{E}{D}{U}{R}{E} return makeThisNode(PROCEDURE);
{P}{R}{O}{G}{R}{A}{M} return makeThisNode(PROGRAM);

{R}{E}{A}{D}{L}{N} return makeThisNode(READ);
{R}{E}{A}{D} return makeThisNode(READ);

{R}{E}{A}{L} return makeThisNode(SYS_TYPE);
{R}{E}{C}{O}{R}{D} return makeThisNode(RECORD);
{R}{E}{P}{E}{A}{T} return makeThisNode(REPEAT);

{S}{Q}{R}{T} return makeThisNode(SYS_FUNCT);
{S}{Q}{R} return makeThisNode(SYS_FUNCT);

{S}{T}{R}{I}{N}{G} return makeThisNode(SYS_TYPE);
{S}{U}{C}{C} return makeThisNode(SYS_FUNCT);
{T}{H}{E}{N} return makeThisNode(THEN);
{T}{O} return makeThisNode(TO);
{T}{R}{U}{E} return makeThisNode(SYS_CON);
{T}{Y}{P}{E} return makeThisNode(TYPE);
{U}{N}{T}{I}{L} return makeThisNode(UNTIL);
{V}{A}{R} return makeThisNode(VAR);
{W}{H}{I}{L}{E} return makeThisNode(WHILE);

{W}{R}{I}{T}{E}{L}{N} return makeThisNode(SYS_PROC);
{W}{R}{I}{T}{E} return makeThisNode(SYS_PROC);

"'"[0-9a-zA-Z]"'" return makeThisNode(CHAR);
"'"([^\']|\'\')*"'" return makeThisNode(STRING);
[0-9]+"."[0-9]+ return makeThisNode(REAL);
[0-9]+ return makeThisNode(INTEGER);
[a-zA-Z]([a-zA-Z0-9])* return makeThisNode(ID);

"(" return makeThisNode(LP);
")" return makeThisNode(RP);
"*" return makeThisNode(MUL);
"+" return makeThisNode(PLUS);
"," return makeThisNode(COMMA);
"-" return makeThisNode(MINUS);

".." return makeThisNode(DOTDOT);
"." return makeThisNode(DOT);

"/" return makeThisNode(DIV);

":=" return makeThisNode(ASSIGN);
":" return makeThisNode(COLON);

";" return makeThisNode(SEMI);

"<=" return makeThisNode(LE);
"<>" return makeThisNode(UNEQUAL);
"<" return makeThisNode(LT);

"=" return makeThisNode(EQUAL);

">=" return makeThisNode(GE);
">" return makeThisNode(GT);

"[" return makeThisNode(LB);
"]" return makeThisNode(RB);

{sl-comment} |
{ml-comment-a} |
{ml-comment-b} {
	int i = 0;
	int length = strlen(yytext);
	for (; i < length; ++i) {
		if (i < length - 1 && yytext[i] == '\r' && yytext[i + 1] == '\n') {
			line_no++;
			i++;
		}
		else if (yytext[i] == '\n') {
			line_no++;
		}
	}
}

[ \t\f] {
	/*whitespace tab page*/
}

\r\n|\n {
	line_no++;
}

. {
	fprintf (stderr, "'%c' (0%o): illegal charcter at line %d\n", yytext[0], yytext[0], line_no);
	exit(0);
}

%%

int yywrap () {
	return (1);
}

int makeThisNode(int type) {
	yylval = makeNewNode();
	yylval->line_no = line_no;

	if (type == STRING || type == CHAR) {
		yylval->literal = (char *)malloc(sizeof(char) * strlen(yytext));
		strcpy(yylval->literal, yytext + 1);
		yylval->literal[strlen(yytext) - 2] = '\0';
	}
	else {
		yylval->literal = (char *)malloc(sizeof(char) * strlen(yytext) + 1);
		strcpy(yylval->literal, yytext);
		int i = 0;
		for (; i < strlen(yytext); i++) {
			char c = yylval->literal[i];
			yylval->literal[i] = (c >= 'A' && c <= 'Z') ? c + 0x20 : c;
		}
	}

	return type;
}

void openFile(int argc, char** argv) {
	if (argc != 2) {
        printf("need one input file and only one\n");
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("open input file failed\n");
        exit(1);
    }
}
