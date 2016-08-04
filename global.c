#include "global.h"

TreeNode * makeNewNode() {
	TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
	if (t == NULL) {
		fprintf (stderr, "out of memory during parsing\n");
		exit(1);
	}

	t->child = NULL;
	t->sibling = NULL;
	t->line_no = 0;
	t->literal = NULL;
	t->label = NULL;

	t->address = 0;
	t->size = 0;
	t->level = 0;
	t->leveltofather = 0;

	t->computable = 0;
	t->result = 0;
	t->type = 0;
	return t;
}

void releaseNode(TreeNode *t) {
	if (t == NULL) {
		return;
	}

	if (t->literal != NULL) {
		free(t->literal);
	}
	if (t->label != NULL) {
		free(t->label);
	}

	releaseNode(t->sibling);
	releaseNode(t->child);

	free(t);
}

char NodeKindStr[][40] = {
	"program", "program_head", "routine", "routine_head", "sub_routine", "empty_label_part", "const_part",
	"empty_const_part", "const_expr", "integer_const_value", "real_const_value", "char_const_value",
	"string_const_value", "sys_con_const_value", "type_part", "empty_type_part", "type_definition", "array_type_decl",
	"record_type_decl", "field_decl", "name_list", "sys_type_simple_type_decl", "id_simple_type_decl",
	"lp_name_list_rp_simple_type_decl", "const_dotdot_const_simple_type_decl", "m_const_dotdot_const_simple_type_decl",
	"m_const_dotdot_m_const_simple_type_decl", "id_dotdot_id_simple_type_decl", "var_part", "empty_var_part",
	"var_decl", "routine_part", "function_decl", "function_head", "procedure_decl", "procedure_head", "parameters",
	"empty_parameters", "var_para_decl", "non_var_para_decl", "routine_body", "stmt_list", "labeled_stmt",
	"non_labeled_stmt", "id_assign_stmt", "id_lb_exp_rb_assign_stmt", "id_dot_id_assign_stmt", "id_proc_stmt",
	"id_lp_args_rp_proc_stmt", "sys_proc_proc_stmt", "sys_proc_lp_args_rp_proc_stmt", "read_lp_factor_rp_proc_stmt",
	"compound_stmt", "if_stmt", "else_clause", "empty_else_clause", "repeat_stmt", "while_stmt", "for_stmt",
	"to_direction", "down_direction", "case_stmt", "case_expr_list", "const_case_expr", "id_case_expr", "goto_stmt",
	"expression", "end_expression", "ge_expression_op", "gt_expression_op", "le_expression_op",	"lt_expression_op",
	"equal_expression_op", "unequal_expression_op", "expr", "end_expr", "plus_expr_op",	"minus_expr_op", "or_expr_op",
	"term", "end_term", "mul_term_op", "div_term_op", "mod_term_op", "and_term_op",	"id_factor",
	"id_lp_args_rp_factor", "sys_func_factor", "sys_func_lp_args_rp_factor", "const_factor", "lp_exp_rp_factor",
	"not_factor_factor", "minus_factor_factor", "id_lb_exp_rb_factor", "id_dot_id_factor", "args_list", "useless_stmt"
};

int errorOccur = 0;
