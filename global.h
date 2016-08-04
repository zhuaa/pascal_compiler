#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define YYSTYPE TreeNode *


typedef enum {
	program_NodeKind, program_head_NodeKind, routine_NodeKind, routine_head_NodeKind,
	sub_routine_NodeKind, empty_label_part_NodeKind, const_part_NodeKind, empty_const_part_NodeKind,
	const_expr_NodeKind, integer_const_value_NodeKind, real_const_value_NodeKind, char_const_value_NodeKind,
	string_const_value_NodeKind, sys_con_const_value_NodeKind, type_part_NodeKind, empty_type_part_NodeKind,
	type_definition_NodeKind, array_type_decl_NodeKind, record_type_decl_NodeKind, field_decl_NodeKind,
	name_list_NodeKind, sys_type_simple_type_decl_NodeKind, id_simple_type_decl_NodeKind,
	lp_name_list_rp_simple_type_decl_NodeKind, const_dotdot_const_simple_type_decl_NodeKind,
	m_const_dotdot_const_simple_type_decl_NodeKind, m_const_dotdot_m_const_simple_type_decl_NodeKind,
	id_dotdot_id_simple_type_decl_NodeKind, var_part_NodeKind, empty_var_part_NodeKind, var_decl_NodeKind,
	routine_part_NodeKind, function_decl_NodeKind, function_head_NodeKind, procedure_decl_NodeKind,
	procedure_head_NodeKind, parameters_NodeKind, empty_parameters_NodeKind, var_para_decl_NodeKind,
	non_var_para_decl_NodeKind, routine_body_NodeKind, stmt_list_NodeKind, labeled_stmt_NodeKind,
	non_labeled_stmt_NodeKind, id_assign_stmt_NodeKind, id_lb_exp_rb_assign_stmt_NodeKind,
	id_dot_id_assign_stmt_NodeKind, id_proc_stmt_NodeKind, id_lp_args_rp_proc_stmt_NodeKind,
	sys_proc_proc_stmt_NodeKind, sys_proc_lp_args_rp_proc_stmt_NodeKind, read_lp_factor_rp_proc_stmt_NodeKind,
	compound_stmt_NodeKind, if_stmt_NodeKind, else_clause_NodeKind, empty_else_clause_NodeKind, repeat_stmt_NodeKind,
	while_stmt_NodeKind, for_stmt_NodeKind, to_direction_NodeKind, down_direction_NodeKind, case_stmt_NodeKind,
	case_expr_list_NodeKind, const_case_expr_NodeKind, id_case_expr_NodeKind, goto_stmt_NodeKind,
	expression_NodeKind, end_expression_NodeKind, ge_expression_op_NodeKind, gt_expression_op_NodeKind,
	le_expression_op_NodeKind, lt_expression_op_NodeKind, equal_expression_op_NodeKind,	unequal_expression_op_NodeKind,
	expr_NodeKind, end_expr_NodeKind, plus_expr_op_NodeKind, minus_expr_op_NodeKind, or_expr_op_NodeKind,
	term_NodeKind, end_term_NodeKind, mul_term_op_NodeKind, div_term_op_NodeKind, mod_term_op_NodeKind,
	and_term_op_NodeKind, id_factor_NodeKind, id_lp_args_rp_factor_NodeKind, sys_func_factor_NodeKind,
	sys_func_lp_args_rp_factor_NodeKind, const_factor_NodeKind, lp_exp_rp_factor_NodeKind, not_factor_factor_NodeKind,
	minus_factor_factor_NodeKind, id_lb_exp_rb_factor_NodeKind, id_dot_id_factor_NodeKind, args_list_NodeKind,
	useless_stmt_NodeKind
} NodeKind;

extern char NodeKindStr[][40];
extern int errorOccur;


typedef enum
{
	_integer,_char,_string,_real,_boolean,_array,_record,_range,_mrange,_mmrange,_enum,_none
}TableNodeType;


typedef struct treeNode {
	struct treeNode * child;
	struct treeNode * sibling;
	int line_no;
	char * literal;
	NodeKind nodeKind;

	char * label;
	int address;
	int size;
	int level;
	int leveltofather;

	int computable;
	int result;
	int type;

	TableNodeType Type;

} TreeNode;

TreeNode * makeNewNode();
void releaseNode(TreeNode *t);

#endif
