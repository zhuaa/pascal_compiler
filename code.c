#include <stdio.h>
#include <string.h>
#include "code.h"
#include "global.h"

char myreg[MAXREG][4] = {"$v1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", 
					"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7"};

extern TreeNode *savedTree;
extern pro_head_size;
TreeNode *proot;
//struct code_tree *croot;.
int label = -1;
//my_code *code_head;
//my_code *code_tail;
int plevel;
int number;


char* strlink(char *re, char *op, char *rd, char *rs, char *rt);
int factor(TreeNode *smt, reg_table *mytable);
int term(TreeNode *smt, reg_table *mytable);
int expr(TreeNode *smt, reg_table *mytable);
int logic_expr(TreeNode *smt, reg_table *mytable);
int expression(TreeNode *smt, reg_table *mytable);
void ID_AS_expr(TreeNode *smt, reg_table *mytable);
void ID_AS_expr_lb(TreeNode *smt, reg_table *mytable);
void ID_AS_expr_dot(TreeNode *smt, reg_table *mytable);
void parse_if_stmt(TreeNode *smt, reg_table *mytable);
void parse_repeat_stmt(TreeNode *smt, reg_table *mytable);
void parse_while_stmt(TreeNode *smt, reg_table *mytable);
void parse_for_stmt(TreeNode *smt, reg_table *mytable);
int get_const(TreeNode *smt, reg_table *mytable);
int get_ID(TreeNode *smt, reg_table *mytable);
void parse_case_stmt(TreeNode *smt, reg_table *mytable);
void parse_proc_args(TreeNode *smt, reg_table *mytable);
void parse_proc_stmt(TreeNode *smt, reg_table *mytable);
void parse_nonstmt(TreeNode *smt, reg_table *mytable);
void parse_stmt_list(TreeNode *smt, reg_table *mytable);
void parse_com_stmt(TreeNode *smt, reg_table *mytable);
void parse_tree();
int get_reg(reg_table *mytable, int address);
void initial_table(reg_table *mytable);
int find_reg(reg_table *mytable, int address);
void find_access(TreeNode *smt);
//void reg_to_mem_return(reg_table *mytable);
//void reg_to_mem(reg_table *mytable, int index);
//void reg_to_mem_all(reg_table *mytable);
//void get_reg_super(reg_table *mytable, int index);
//void check_table(reg_table *mytable);
//void generate_code(char *sentence, operation type);
//void generate_code_file();


FILE *fp;

void initial_table(reg_table *mytable){
	int i = 0;
	for(; i<MAXREG; i++){
		mytable[i].address = -1;
		mytable[i].is_use = 0;
	}
}

// void reg_to_mem(reg_table *mytable, int index){
// 	if(mytable[index].address < 0 || !mytable[index].is_use)
// 		return;
// 	char offset[10];
// 	fprintf(fp, "sw %s, %d($t8)\n", myreg[index], mytable[index].address);	
// }

// void reg_to_mem_all(reg_table *mytable){
// 	int i = 0;
// 	for(; i < MAXREG; ++i)
// 		reg_to_mem(mytable, i);
// }

// void reg_to_mem_return(reg_table *mytable){
// 	int i = 0;
// 	for(; i<MAXREG; i++){
// 		if(mytable[i].address == 12 && mytable[i].is_use == 1){
// 			fprintf(fp, "sw %s, 12($t8)\n", myreg[i]);
// 			break;
// 		}
// 	}
// }

int get_reg(reg_table *mytable, int address){
	int i = 0;
	for(; i < MAXREG; ++i){
		if(!mytable[i].is_use){
			mytable[i].is_use = 1;
			break;
		}
	}
	if(i == MAXREG){
		i = 0;
		while(mytable[i].address < 0)
			i++;
		mytable[i].address = address;
		//initial_table(mytable);
		//return get_reg(mytable, address);
	}
	//mytable[i].address = address;
	return i;
}

// void get_reg_super(reg_table *mytable, int index){
// 	if(mytable[index].is_use)
// 		reg_to_mem(mytable, index);
// }

int find_reg(reg_table *mytable, int address){
	int i = 0;
	if(address>=0){
		for(; i < MAXREG; ++i){
			if(mytable[i].address == address && mytable[i].is_use == 1)
				break;
		}
	}
	i = (i == MAXREG)?-1:i;
	return i;
}

// void check_table(reg_table *mytable){
// 	int i = 0;
// 	char sentence[30], tmp[20];
// 	for(; i<MAXREG; i++){
// 		if(mytable[i].is_change){
// 			if(mytable[i].address >= 0){
// 				itoa(mytable[i].address, tmp, 10);
// 				strcat(tmp, "($t8)");
// 				fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[i], tmp, NULL));
// 			}
// 			itoa(mytable[i].paddress, tmp, 10);
// 			strcat(tmp, "($t8)");
// 			fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[i], tmp, NULL));
// 			mytable[i].is_change = 0;
// 		}
// 	}
// }

char* strlink(char *re, char *op, char *rd, char *rs, char *rt){
	strcpy(re, op);
	if(rd != NULL){
		strcat(re, " ");
		strcat(re, rd);
	}
	if(rs != 0){
		strcat(re, ", ");
		strcat(re, rs);
	}
	if(rt != NULL){
		strcat(re, ", ");
		strcat(re, rt);
	}
	return re;
}

// void generate_code(char *sentence, int type){
// 	my_code *ptr = (my_code *)malloc(sizeof(my_code));
// 	ptr->next = NULL;
// 	strcpy(code_head->sentence, sentence);
// 	ptr->opcode = type;
// 	if(!code_head){
// 		code_head = code_tail = ptr;
// 	}
// 	else{
// 		code_tail->next = ptr;
// 		code_tail = ptr;
// 	}
// }

// void generate_code_file(){
// 	my_code *ptr = code_head, *free_ptr;
// 	while(ptr){
// 		free_ptr = ptr;
// 		fprintf(fp, "%s\n", ptr->sentence);
// 		ptr = ptr->next;
// 		free(free_ptr);
// 	}
// 	code_head = code_tail = NULL;
// }

void parse_proc_args(TreeNode *smt, reg_table *mytable){
	if(!smt)
		return;
	parse_proc_args(smt->sibling, mytable);
	int rs = expression(smt, mytable);
	char sentence[32];
	fprintf(fp, "%s\n", "addi $sp, $sp, -4");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rs], "0($sp)", NULL));
	number++;
}

void find_access(TreeNode *smt){
	int k = smt->leveltofather;
	if(k == 0){
		// fprintf(fp, "%s\n", "move $t9, $t8");
		return;
	}
	fprintf(fp, "%s\n", "lw $t9, 8($t8)");
	k--;
	while(k--){
		fprintf(fp, "%s\n", "lw $t9, 8($t9)");
	}	
}

int get_ID(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = smt;
	char sentence[30], tmp[16];
	int rs;
	if(!ptr->label){
		if(ptr->nodeKind == integer_const_value_NodeKind){   //枚举类型
			rs = get_reg(mytable, -1);
			fprintf(fp, "li %s, %s\n", myreg[rs], ptr->literal);
			return rs;
		}
		if(ptr->leveltofather){
			rs = get_reg(mytable, -1);
			find_access(ptr);
			itoa(ptr->address, tmp, 10);
			if(ptr->leveltofather)
				strcat(tmp, "($t9)");
			else
				strcat(tmp, "($t8)");
			fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp, NULL));
		}
		else{
			rs = find_reg(mytable, ptr->address);
			if(rs == -1){
				rs = get_reg(mytable, -1);
					//find_access(ptr);
				itoa(ptr->address, tmp, 10);
				strcat(tmp, "($t8)");
				fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp, NULL));					
			}
		}
	}
	else {         //a := CONST
		rs = get_reg(mytable, -1);
		fprintf(fp, "%s\n", strlink(sentence, "la", myreg[rs], ptr->label, NULL));
		if(ptr->Type != _string)
			fprintf(fp, "lw %s, 0(%s)\n", myreg[rs], myreg[rs]);
	}
	return rs;		
}

int factor(TreeNode *smt, reg_table *mytable){
	int rs = 0;
	char tmp[20], sentence[30];
	TreeNode *ptr = smt->child;
	switch(smt->nodeKind){
		case id_factor_NodeKind:   //a := b;
		rs = get_ID(ptr, mytable);
		break;
		case id_lp_args_rp_factor_NodeKind:   //func(a,b)
		itoa(-(ptr->size), tmp, 10);
		fprintf(fp, "%s\n", strlink(sentence, "addi", "$sp", "$sp", tmp));
		number = 0;
		parse_proc_args((ptr->sibling)->child, mytable);
		fprintf(fp, "%s\n", "addi $sp, $sp, -16");    //arg_list
		if(ptr->level==plevel)
			fprintf(fp, "%s\n", "lw $k0, 8($t8)");
		else{
			fprintf(fp, "%s\n", "move $k0, $t8");
		}
		fprintf(fp, "%s\n", "sw $k0, 8($sp)");
		fprintf(fp, "%s\n", "sw $t8, 4($sp)");
		initial_table(mytable);
		rs = get_reg(mytable, -1);
		fprintf(fp, "%s\n", strlink(sentence, "jal", ptr->label, NULL, NULL));
		fprintf(fp, "%s\n", "lw $t8, 4($sp)");
		fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], "12($sp)", NULL));
		itoa(ptr->size+16+number*4, tmp, 10);
		fprintf(fp, "%s\n", strlink(sentence, "addi", "$sp", "$sp", tmp));
		break;
		case sys_func_factor_NodeKind:

		case sys_func_lp_args_rp_factor_NodeKind:
		//printf("%s\n", "ehakdkajsdakdjakd!");
		//exit(1);
		break;
		case const_factor_NodeKind:
		rs = get_reg(mytable, -1);
		if(ptr->nodeKind == char_const_value_NodeKind)
			fprintf(fp, "%s %s, %d\n", "li", myreg[rs], (int)*(ptr->literal));
		else
			fprintf(fp, "%s\n", strlink(sentence, "li", myreg[rs], ptr->literal, NULL));
		break;
		case lp_exp_rp_factor_NodeKind:
		rs = expression(ptr, mytable);
		break;
		case not_factor_factor_NodeKind:
		rs = factor(ptr, mytable);
		fprintf(fp, "%s\n", strlink(sentence, "not", myreg[rs], myreg[rs], NULL));
		break;
		case minus_factor_factor_NodeKind:
		//printf("fdsf\n");
		//exit(0);
		//mytable[rs].is_use = 0;
		rs = factor(ptr, mytable);
		fprintf(fp, "%s\n", strlink(sentence, "neg", myreg[rs], myreg[rs], NULL));
		break;
		case id_lb_exp_rb_factor_NodeKind:
		//address(int)+sp+exp*size
		find_access(ptr);
		rs = expression(ptr->sibling, mytable);
		//itoa(ptr->size, tmp , 10);
		//if(ptr->size == 4)
		fprintf(fp, "%s\n", strlink(sentence, "sll", myreg[rs], myreg[rs], "2"));
		itoa(ptr->address, tmp, 10);
		fprintf(fp, "%s\n", strlink(sentence, "addiu", myreg[rs], myreg[rs], tmp));
		if(ptr->leveltofather)
			fprintf(fp, "%s\n", strlink(sentence, "addu", myreg[rs], myreg[rs], "$t9"));
		else
			fprintf(fp, "%s\n", strlink(sentence, "addu", myreg[rs], myreg[rs], "$t8"));
		strcpy(tmp, "0(");
		strcat(tmp, myreg[rs]);
		strcat(tmp, ")");
		fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp, NULL));
		break;
		case id_dot_id_factor_NodeKind:
		//address+sp+offset
		find_access(ptr);
		rs = get_reg(mytable, -1);
		itoa(ptr->address, tmp, 10);
		if(ptr->leveltofather)
			fprintf(fp, "%s\n", strlink(sentence, "addiu", myreg[rs], "$t9", tmp));
		else
			fprintf(fp, "%s\n", strlink(sentence, "addiu", myreg[rs], "$t8", tmp));
		itoa((ptr->sibling)->address, tmp, 10);
		strcat(tmp, "(");
		strcat(tmp, myreg[rs]);
		strcat(tmp, ")");
		fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp, NULL));
		break;
	}
	return rs;
}

int term(TreeNode *smt, reg_table *mytable){
	char tmp[10], sentence[30];
	int rs, rt, rd;
	if(smt->nodeKind != end_term_NodeKind){
		rs = term(smt->child, mytable);
		rt = factor(((smt->child)->sibling)->sibling, mytable);
		rd = get_reg(mytable, -1);
		switch(((smt->child)->sibling)->nodeKind){
			case mul_term_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "mult", myreg[rs], myreg[rt], NULL));
			fprintf(fp, "%s\n", strlink(sentence, "mflo", myreg[rd], NULL, NULL));
			break;
			case div_term_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "div", myreg[rd], myreg[rs], myreg[rt]));			
			break;
			case and_term_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "and", myreg[rd], myreg[rs], myreg[rt]));
			break;
			case mod_term_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "div", myreg[rs], myreg[rt], NULL));
			fprintf(fp, "%s\n", strlink(sentence, "mfhi", myreg[rd], NULL, NULL));
			break;
		}		
	}
	else
		return factor(smt->child, mytable);
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	if(mytable[rt].address < 0)
		mytable[rt].is_use = 0;
	return rd;
}

int expr(TreeNode *smt, reg_table *mytable){
	char tmp[10], sentence[30];
	int rs, rt, rd;
	if(smt == NULL){
		puts("!!!!!!");
		return -1;
	}
	if(smt->nodeKind != end_expr_NodeKind){
		rs = expr(smt->child, mytable);
		rt = term(((smt->child)->sibling)->sibling, mytable);
		rd = get_reg(mytable, -1);
		switch(((smt->child)->sibling)->nodeKind){
			case plus_expr_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "add", myreg[rd], myreg[rs], myreg[rt]));
			break;
			case minus_expr_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "sub", myreg[rd], myreg[rs], myreg[rt]));			
			break;
			case or_expr_op_NodeKind:
			fprintf(fp, "%s\n", strlink(sentence, "or", myreg[rd], myreg[rs], myreg[rt]));
			break;
		}
	}
	else
		return term(smt->child, mytable);
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	if(mytable[rt].address < 0)
		mytable[rt].is_use = 0;
	return rd;
}

int logic_expr(TreeNode *smt, reg_table *mytable){
	int rs, rt, rd;
	char tmp[10], branch[10], sentence[30];
	if(smt == 0){
		puts("!!!!!!!");
		return -1;
	}
	if((smt->child)->nodeKind!=end_expression_NodeKind)
		rs = expression(smt->child, mytable);
	else
		rs = expr((smt->child)->child, mytable);
	rt = expr(((smt->child)->sibling)->sibling, mytable);
	if(rt == -1)
		return rs;
	if(rs == -1)
		return rt;
	rd = get_reg(mytable, -1);
	switch(((smt->child)->sibling)->nodeKind){
		case ge_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "slt", myreg[rd], myreg[rt], myreg[rs]));
		strcpy(tmp,"L");
		itoa(++label, branch, 10);
		strcat(tmp, branch);
		fprintf(fp, "%s\n", strlink(sentence, "bne", myreg[rs], myreg[rt], tmp));
		fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[rd], "$zero", "1"));
		strcat(tmp, ":");
		fprintf(fp, "%s\n", tmp);
		break;
		case gt_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "slt", myreg[rd], myreg[rt], myreg[rs]));
		break;
		case le_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "slt", myreg[rd], myreg[rs], myreg[rt]));
		strcpy(tmp,"L");
		itoa(++label, branch, 10);
		strcat(tmp, branch);
		fprintf(fp, "%s\n", strlink(sentence, "bne", myreg[rs], myreg[rt], tmp));
		fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[rd], "$zero", "1"));
		strcat(tmp, ":");
		fprintf(fp, "%s\n", tmp);		
		break;
		case lt_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "slt", myreg[rd], myreg[rs], myreg[rt]));
		break;
		case equal_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "add", myreg[rd], "$zero", "$zero"));
		strcpy(tmp,"L");
		itoa(++label, branch, 10);
		strcat(tmp, branch);
		fprintf(fp, "%s\n", strlink(sentence, "bne", myreg[rs], myreg[rt], tmp));
		fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[rd], "$zero", "1"));
		strcat(tmp, ":");
		fprintf(fp, "%s\n", tmp);			
		break;
		case unequal_expression_op_NodeKind:
		fprintf(fp, "%s\n", strlink(sentence, "add", myreg[rd], "$zero", "$zero"));
		strcpy(tmp,"L");
		itoa(++label, branch, 10);
		strcat(tmp, branch);
		fprintf(fp, "%s\n", strlink(sentence, "beq", myreg[rs], myreg[rt], tmp));
		fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[rd], "$zero", "1"));
		strcat(tmp, ":");
		fprintf(fp, "%s\n", tmp);		
		break;
	}
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	if(mytable[rt].address < 0)
		mytable[rt].is_use = 0;
	return rd;	
}

int expression(TreeNode *smt, reg_table *mytable){
	if(smt->nodeKind != end_expression_NodeKind)
		return logic_expr(smt, mytable);
	else
		return expr(smt->child, mytable);
}

void ID_AS_expr(TreeNode *smt, reg_table *mytable){
	char tmp[20], sentence[30];  				//address
	int rs = -1, rt;
	// sw rt, k(sp)       rs offset
	TreeNode *ptr1 = smt->child; //ID
	TreeNode *ptr2 = ptr1->sibling; //EXP
	rt = expression(ptr2, mytable);
	// if(rt>18 || rt < 0)
	// 	printf("%d\n", rt);
	if(!(ptr1->leveltofather)){
		rs = find_reg(mytable, ptr1->address);
		//printf("%s:%d:%s:use:%d|%d\n", ptr1->literal, ptr1->address, myreg[rt], mytable[rt].is_use, rs);
	}
	find_access(ptr1);
	itoa(ptr1->address, tmp, 10);
	if(ptr1->leveltofather)
		strcat(tmp, "($t9)");
	else
		strcat(tmp, "($t8)");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rt], tmp, NULL));
	if(rs != -1){
		fprintf(fp, "%s\n", strlink(sentence, "move", myreg[rs], myreg[rt], NULL));
		if(mytable[rt].address < 0){
			mytable[rt].is_use = 0;
			mytable[rt].address = -1;
		}
	}
	else{
		mytable[rt].address = ptr1->address;
	}
}

void ID_AS_expr_lb(TreeNode *smt, reg_table *mytable){
	char tmp[20], sentence[30];
	int rs, rt, offset;
	// sw rt, k(sp)
	TreeNode *ptr1 = smt->child; //ID
	offset = expression(ptr1->sibling, mytable); 
	TreeNode *ptr2 = ptr1->sibling->sibling; //EXP
	rt = expression(ptr2, mytable);      //rt
	//itoa(tmp, offset, 10);
	//fprintf(fp, "%s\n", strlink(sentence, "movei", myreg[rs], offset, NULL));
	find_access(ptr1);
	itoa(ptr1->size, tmp, 10);
	//if(ptr1->size==4)
	fprintf(fp, "%s\n", strlink(sentence, "sll", myreg[offset], myreg[offset], "2"));
	itoa(ptr1->address, tmp, 10);
	fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[offset], myreg[offset], tmp));
	if(ptr1->leveltofather)
		fprintf(fp, "%s\n", strlink(sentence, "add", myreg[offset], myreg[offset], "$t9")); //real address
	else
		fprintf(fp, "%s\n", strlink(sentence, "add", myreg[offset], myreg[offset], "$t8"));
	strcpy(tmp, "0(");
	strcat(tmp, myreg[offset]);
	strcat(tmp, ")");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rt], tmp, NULL));
	if(mytable[rt].address < 0)
		mytable[rt].is_use = 0;
	if(mytable[offset].address < 0)
		mytable[offset].is_use = 0;                            
}

void ID_AS_expr_dot(TreeNode *smt, reg_table *mytable){
	char tmp[20], sentence[30]/*, *offset, *rs,*/;
	// sw rt, k(sp)
	int rt, address = 0, offset = 0;
	TreeNode *ptr1 = smt->child; //ID
	find_access(ptr1);
	offset = (ptr1->sibling)->address;
	address = ptr1->address;						//类型判断，store指令和k(sp)
	TreeNode *ptr2 = ptr1->sibling->sibling; 	//EXP
	rt = expression(ptr2, mytable);		//rt
	itoa(address+offset, tmp, 10);
	if(ptr1->leveltofather)
		strcat(tmp, "($t9)");
	else
		strcat(tmp, "($t8)");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rt], tmp, NULL));
	if(mytable[rt].address < 0)
		mytable[rt].is_use = 0;	
}

void parse_if_stmt(TreeNode *smt, reg_table *mytable){
	char tmp[20], if_branch[10], sentence[30];
	int rs = 0;
	rs = expression(smt->child, mytable);
	strcpy(tmp, "IF");
	itoa(++label, if_branch, 10);
	strcat(tmp, if_branch);
	fprintf(fp, "%s\n", strlink(sentence, "beq", myreg[rs], "$zero", tmp));
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	parse_nonstmt((smt->child)->sibling, mytable);
	int tttt = ++label;
	fprintf(fp, "b R%d\n", label);
	strcat(tmp, ":");
	fprintf(fp, "%s\n", tmp);
	TreeNode *ptr = ((smt->child)->sibling)->sibling; 
	if(ptr->nodeKind != empty_else_clause_NodeKind)
		parse_nonstmt(ptr->child, mytable);
	fprintf(fp, "R%d:\n", tttt);

}

void parse_repeat_stmt(TreeNode *smt, reg_table *mytable){
	char tmp[15], loop_branch[10], sentence[30];
	int rs = 0;
	//reg_to_mem_all(mytable);
	initial_table(mytable);
	strcpy(tmp, "REPEAT");
	itoa(++label, loop_branch, 10);
	strcat(tmp, loop_branch);
	strcat(tmp, ":");
	fprintf(fp, "%s\n", tmp);
	parse_stmt_list(smt->child, mytable);
	rs = expression((smt->child)->sibling, mytable);
	tmp[strlen(tmp)-1] = 0;
	fprintf(fp, "%s\n", strlink(sentence, "beq", myreg[rs], "$zero", tmp));
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	//initial_table(mytable);
}

void parse_while_stmt(TreeNode *smt, reg_table *mytable){
	char tmp[15], tmp_r[10], branch[10], sentence[30];
	int rs = 0;
	//reg_to_mem_all(mytable);
	initial_table(mytable);
	strcpy(tmp, "R");
	itoa(++label, branch, 10);
	strcat(tmp, branch);
	fprintf(fp, "%s\n", strlink(sentence, "b", tmp, NULL, NULL));
	strcpy(tmp_r, "WHILE");
	itoa(++label, branch, 10);
	strcat(tmp_r, branch);
	strcat(tmp_r, ":");
	fprintf(fp, "%s\n", tmp_r);
	parse_nonstmt((smt->child)->sibling, mytable);	
	strcat(tmp, ":");
	fprintf(fp, "%s\n", tmp);
	initial_table(mytable);
	rs = expression(smt->child, mytable);
	tmp_r[strlen(tmp_r)-1] = 0;
	fprintf(fp, "%s\n", strlink(sentence, "bne", myreg[rs], "$zero", tmp_r));
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;	
	initial_table(mytable);
}

void parse_for_stmt(TreeNode *smt, reg_table *mytable){
	char tmp[10], tmp_r[10], tmp_m[10], loop_branch[10], sentence[30], tmp_q[10];
	int rt = 0, rs = 1, address = 0; 
	//reg_to_mem_all(mytable);
	initial_table(mytable);
	rs = expression((smt->child)->sibling, mytable);
	rt = expression((((smt->child)->sibling)->sibling)->sibling, mytable);
	itoa(++label, loop_branch, 10);
	strcpy(tmp_q, "Q");
	strcat(tmp_q, loop_branch);
	//fprintf(fp, "%s\n", strlink(sentence, "add", "$s0", rt, "$zero"));
	find_access(smt->child);
	itoa((smt->child)->address, tmp_m, 10);
	if(smt->child->leveltofather)
		strcat(tmp_m, "($t9)");
	else
		strcat(tmp_m, "($t8)");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rs], tmp_m, NULL));
	if((((smt->child)->sibling)->sibling)->nodeKind == to_direction_NodeKind)
		fprintf(fp, "%s\n", strlink(sentence, "bgt", myreg[rs], myreg[rt], tmp_q));
	else
		fprintf(fp, "%s\n", strlink(sentence, "blt", myreg[rs], myreg[rt], tmp_q));
	fprintf(fp, "%s\n", "addi $sp, $sp, -4");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rt], "0($sp)", NULL));
	mytable[rt].is_use = 0;
	//mytable[rs].is_use = 0;
	if(mytable[rs].address < 0)
		mytable[rs].is_use = 0;
	strcpy(tmp_r, "FOR");
	itoa(++label, loop_branch, 10);
	strcat(tmp_r, loop_branch);
	strcat(tmp_r, ":");
	//rs = get_reg(mytable, address);
	// fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp_m, NULL));
	// mytable[rs].is_use = 0;
	strcpy(tmp, "R");
	itoa(++label, loop_branch, 10);
	strcat(tmp, loop_branch);
	fprintf(fp, "%s\n", strlink(sentence, "b", tmp, NULL, NULL));
	fprintf(fp, "%s\n", tmp_r);
	//fprintf(fp, "%s\n", tmp_r);
	parse_nonstmt(((((smt->child)->sibling)->sibling)->sibling)->sibling, mytable);
	rs = get_reg(mytable, -1);
	fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp_m, NULL));
	if((((smt->child)->sibling)->sibling)->nodeKind == to_direction_NodeKind)
		fprintf(fp, "%s\n", strlink(sentence, "addi", myreg[rs], myreg[rs], "1"));
	else
		fprintf(fp, "%s\n", strlink(sentence, "addiu", myreg[rs], myreg[rs], "-1"));
	find_access(smt->child);
	itoa((smt->child)->address, tmp_m, 10);
	if((smt->child)->leveltofather)
		strcat(tmp_m, "($t9)");
	else
		strcat(tmp_m, "($t8)");
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rs], tmp_m, NULL));
	strcat(tmp, ":");
	fprintf(fp, "%s\n", tmp);
	rt = get_reg(mytable, -1);
	fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rt], "0($sp)", NULL));
	tmp_r[strlen(tmp_r)-1] = 0;
	if((((smt->child)->sibling)->sibling)->nodeKind == to_direction_NodeKind)
		fprintf(fp, "%s\n", strlink(sentence, "ble", myreg[rs], myreg[rt], tmp_r));
	else
		fprintf(fp, "%s\n", strlink(sentence, "bge", myreg[rs], myreg[rt], tmp_r));
	fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rt], tmp_m, NULL));
	//fprintf(fp, "%s\n", strlink(sentence, "lw", myreg[rs], tmp_m, NULL));
	//fprintf(fp, "%s\n", strlink(sentence, "sw", myreg[rs], tmp_m, NULL));
	fprintf(fp, "%s\n", "addi $sp, $sp, 4");
	strcat(tmp_q, ":");
	fprintf(fp, "%s\n", tmp_q);
	initial_table(mytable);
}

int get_const(TreeNode *smt, reg_table *mytable){
	int rs = get_reg(mytable, -1);
	char sentence[30];
	if(smt->nodeKind == integer_const_value_NodeKind)
		fprintf(fp, "%s\n", strlink(sentence, "li", myreg[rs], smt->literal, NULL));
	else if(smt->nodeKind == char_const_value_NodeKind)
		fprintf(fp, "li %s, %d\n", myreg[rs], (int)*(smt->literal));
	else if(smt->nodeKind == sys_con_const_value_NodeKind){
		if(!strcmp(smt->literal,"true"))
			fprintf(fp, "%s\n", strlink(sentence, "li", myreg[rs], "1", NULL));
		else if(!strcmp(smt->literal, "false"))
			fprintf(fp, "%s\n", strlink(sentence, "li", myreg[rs], "0", NULL));
	}
	mytable[rs].is_use = 0;
	return rs;
}

void parse_case_stmt(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = smt->child;         //expression
	char tmp[10], end[15], branch[10], sentence[30];
	int rs = 0, rt, rd;
	rs = expression(ptr, mytable);
	ptr = ptr->sibling;
	ptr = ptr->child;
	strcpy(end, "CASE_END");
	itoa(++label, branch, 10);
	strcat(end, branch);
	while(ptr != NULL){
		strcpy(tmp, "CASE");
		itoa(++label, branch, 10);
		strcat(tmp, branch);
		if(ptr->nodeKind == const_case_expr_NodeKind)
			rt = get_const(ptr->child, mytable);
		else{
			rt = get_ID(ptr->child, mytable);
			if(mytable[rt].address < 0)
				mytable[rt].is_use = 0;
		}
		fprintf(fp, "%s\n", strlink(sentence, "bne", myreg[rs], myreg[rt], tmp));
		parse_nonstmt((ptr->child)->sibling, mytable);
		fprintf(fp, "%s\n", strlink(sentence, "b", end, NULL, NULL));
		ptr = ptr->sibling;
		strcat(tmp, ":");
		fprintf(fp, "%s\n", tmp);
	}
	strcat(end, ":");
	fprintf(fp, "%s\n", end);
}

void parse_proc_stmt(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = smt->child;
	char sentence[30], tmp[20];
	//reg_to_mem_all(mytable);
	initial_table(mytable);
	itoa(-(ptr->size), tmp, 10);
	fprintf(fp, "%s\n", strlink(sentence, "addi", "$sp", "$sp", tmp));
	number = 0;
	if(ptr->sibling)
		parse_proc_args((ptr->sibling)->child, mytable);
	fprintf(fp, "%s\n", "addi $sp, $sp, -16");    //arg_list
	if(ptr->level==plevel)
		fprintf(fp, "%s\n", "lw $k0, 8($t8)");
	else{
		fprintf(fp, "%s\n", "move $k0, $t8");
	}
	fprintf(fp, "%s\n", "sw $k0, 8($sp)");
	fprintf(fp, "%s\n", "sw $t8, 4($sp)");
	fprintf(fp, "%s\n", strlink(sentence, "jal", ptr->label, NULL, NULL));
	fprintf(fp, "%s\n", "lw $t8, 4($sp)");
	itoa(ptr->size+12+number*4, tmp, 10);
	fprintf(fp, "%s\n", strlink(sentence, "addi", "$sp", "$sp", tmp));
}

void parse_nonstmt(TreeNode *smt, reg_table *mytable){
	fprintf(fp, "#%d\n", smt->line_no);
	TreeNode *ptr = smt->child;
	TreeNode* tmp;
	switch(ptr->nodeKind){
		case id_assign_stmt_NodeKind:
		ID_AS_expr(ptr, mytable);
		break;
		case id_lb_exp_rb_assign_stmt_NodeKind:
		ID_AS_expr_lb(ptr, mytable);
		break;
		case id_dot_id_assign_stmt_NodeKind:
		ID_AS_expr_dot(ptr, mytable);
		break;
		case id_proc_stmt_NodeKind:
		case id_lp_args_rp_proc_stmt_NodeKind:
		parse_proc_stmt(ptr, mytable);
		break;
		case sys_proc_proc_stmt_NodeKind:
		case sys_proc_lp_args_rp_proc_stmt_NodeKind:
		tmp = ((ptr->child)->sibling)->child;
		while(tmp != NULL)
		{
			TreeNode* labelnode = tmp;
			int rs = expression(tmp, mytable);
			//printf("%s\n", myreg[rs]);
			// int uncle[200] = {0};
			// printThisTree(tmp, uncle, 0);
			fprintf(fp, "move $a0, %s\n", myreg[rs]);
			if(labelnode->Type == _string)
				fprintf(fp, "%s\n", "li $v0, 4");
			else if(labelnode->Type == _char)
				fprintf(fp, "%s\n", "li $v0, 11");
			else fprintf(fp, "%s\n", "li $v0, 1");
			fprintf(fp, "%s\n", "syscall");
			tmp = tmp->sibling;
			if(mytable[rs].address < 0)
				mytable[rs].is_use = 0;
		}
		break;
		case read_lp_factor_rp_proc_stmt_NodeKind:
		fprintf(fp, "%s\n", "li $v0, 5");
		fprintf(fp, "%s\n", "syscall");
		tmp = (ptr->child)->sibling->child;
		find_access(tmp);
		int offset = 0, rt = 0;
		switch(ptr->child->sibling->nodeKind){
			case id_factor_NodeKind:
			if(tmp->leveltofather)
				fprintf(fp, "%s $v0, %d($t9)\n", "sw", tmp->address);
			else
				fprintf(fp, "%s $v0, %d($t8)\n", "sw", tmp->address);
			break;
			case id_lb_exp_rb_factor_NodeKind:
			offset = expression(tmp->sibling, mytable);
			rt = get_reg(mytable, -1);
			fprintf(fp, "sll %s, %s, 2\n", myreg[rt], myreg[offset]);
			fprintf(fp, "addiu %s, %s, %d\n", myreg[rt], myreg[rt], tmp->address);
			if(tmp->leveltofather)
				fprintf(fp, "add %s, %s, $t9\n", myreg[rt], myreg[rt]);
			else
				fprintf(fp, "add %s, %s, $t8\n", myreg[rt], myreg[rt]);
			fprintf(fp, "sw $v0, 0(%s)\n", myreg[rt]);
			if(mytable[offset].address < 0)
				mytable[offset].is_use = 0;
			mytable[rt].is_use = 0;
			break;
			case id_dot_id_factor_NodeKind:
			if(tmp->leveltofather)
				fprintf(fp, "%s $v0, %d($t9)\n", "sw", tmp->address+tmp->sibling->address);
			else
				fprintf(fp, "%s $v0, %d($t8)\n", "sw", tmp->address+tmp->sibling->address);
			break;
		}
		break;
		case compound_stmt_NodeKind:
		parse_com_stmt(ptr, mytable);
		break;
		case if_stmt_NodeKind:
		parse_if_stmt(ptr, mytable);
		break;
		case repeat_stmt_NodeKind:
		parse_repeat_stmt(ptr, mytable);
		break;
		case while_stmt_NodeKind:
		parse_while_stmt(ptr, mytable);
		break;
		case for_stmt_NodeKind:
		parse_for_stmt(ptr, mytable);
		break;
		case case_stmt_NodeKind:
		parse_case_stmt(ptr, mytable);
		break;
		default:
		break;
	}
	//check_table(mytable);
}

void parse_com_stmt(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = smt->child; //list
	ptr = ptr->child;
	while(ptr!=NULL){
		parse_nonstmt(ptr, mytable);
		ptr = ptr->sibling;
	}
}

void parse_stmt_list(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = smt->child;
	while(ptr != NULL){
		parse_nonstmt(ptr, mytable);
		ptr = ptr->sibling;
	}
}

void parse_part(TreeNode *smt, reg_table *mytable){
	TreeNode *ptr = (((smt->child)->sibling)->child)->child;
	while(ptr->sibling)
		ptr = ptr->sibling;    //route part
	ptr = ptr->child;
	while(ptr){
		parse_part(ptr, mytable);
		ptr = ptr->sibling;
	}                 //堆栈操作部分
	fprintf(fp, "%s:\n", ((smt->child)->child)->label);
	plevel = ((smt->child)->child)->level;
	fprintf(fp, "%s\n", "sw $ra, 0($sp)");
	fprintf(fp, "%s\n", "move $t8, $sp"); 
	initial_table(mytable);
	ptr = smt;
	TreeNode *tmp = (ptr->child)->sibling; //sub route
	tmp = (tmp->child)->sibling;   //route body
	parse_com_stmt(tmp->child, mytable);
	//reg_to_mem_return(mytable);
	//reg_to_mem_all(mytable);
		//if(mytable)
		//	free_table(mytable);								 //释放堆栈
		//fprintf(fp, "%s\n", "pop $t8");  //过程结束，把父亲的堆栈返回。
	fprintf(fp, "%s\n", "move $sp, $t8");
	fprintf(fp, "%s\n", "lw $ra, 0($t8)"); //减堆栈退出
	fprintf(fp, "%s\n", "jr $ra");	
}

void parse_tree(){
	int k = pro_head_size;
	//printf("%d", k);
	k += 300; // 300 safe space
	TreeNode *ptr = proot;
	reg_table mytable[MAXREG];
	fprintf(fp, ".text\naddiu $sp, $sp, %d\njal main\naddiu $sp, $sp, %d\nj main_end\n", -k, k);
	parse_part(ptr, mytable);
	fprintf(fp, "%s\n", "main_end:");
	//free_table(mytable);
}

void make_code(char* filename, FILE *fpp){
	proot = savedTree;
	//fp = fopen(filename, "w");
	fp = fpp;
	parse_tree();
	fclose(fp);
}

