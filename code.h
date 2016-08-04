#ifndef _CODE_H_
#define _CODE_H_

#include "global.h"

#define MAXREG 19

typedef char byte;

typedef struct regtable{
	byte is_use, is_change;
	int address, paddress;   //<0 reprsent const
} reg_table;


// enum reg{
// 	//general
// 	$zero, $at, $v0, $v1, $a0, $a1, $a2, $a3, 
// 	$t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7, 
// 	$s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7,
// 	$t8, $t9, $k0, $k1, $gp, $sp, $s8, $fp,
// 	$lo, $hi, 
// 	//float
// 	$f0, $f1, $f2, $f3, $f4, $f5, $f6, $f7,
// 	$f8, $f9, $f10, $f11, $f12, $f13, $f14, $f15,
// 	$f16, $f17, $f18, $f19, $f20, $f21, $f22, $f23,
// 	$f24, $f25, $f26, $f27, $f28, $f29, $f30, $f31
// };

// enum ins_type{
// 	ITYPE, JTYPE, RTYPE
// };

// typedef enum op{
// 	//load
// 	LA, LB, LBU, LH, LHU, 
// 	LW, LWC1,/*FLOAT*/ LWL, LWR, 
// 	LD, ULH, ULHU, ULW, LL,
// 	//store
// 	SB, SH, SW, SWC1, SDC1,/*FLOAT&DOUBLE*/
// 	SWL, SWR, SD, USH, USW, SC,
// 	//data move
// 	MOVE, MFHI, MFLO, MTHI, MTLO, MFC0,
// 	MFC1, MFC1_D, MTC0, MTC1, MOVN, MOVZ,
// 	MOVF, MOVT,
// 	//arithmutic and logical
// 	ABS, ADD, ADDU, ADDI, ADDIU, //add
// 	AND, AND, CLO, CLZ, DIV, DIVU,
// 	MULT, MULTU, MUL, MULO, MULOU,
// 	MADD, MADDU, MSUB, MSUBU, MEGU,
// 	NOR, NOT, OR, ORI, SLL, SLLV,
// 	SRA, SRAV, SRL, SRLV, SUB, SUBU,
// 	XOR, XORIM, LUI, LI, SLT, SLTU, SLTI,
// 	SLTIU, 
// 	//branch
// 	BCLF, BCLT, BEQ, BGEZ, BGEZAL, BGTZ, BLEZ,
// 	BLTZAL, BLTZ, BNE,
// 	//jump
// 	J, JAL, JALR, JR, 
// 	//FLOAT
// 	ABS_D, ABS_S, ADD_D, ADD_S, CEIL_D, CEIL_S,
// 	C_EQ_D, C_EQ_S, C_LE_D, C_LE_S, C_LT_D, C_LT_S,
// 	//trasfer
// 	CVT_D_S, CVT_D_W, CVT_S_D, CVT_S_W,
// 	CVT_W_D, CVT_W_S,
// 	//mul and div
// 	DIV_D, DIV_S, FLOOR_W_D, FLOOR_W_S, L_D, L_S,
// 	MOV_D, MOV_S, MOVF_D, MOVF_S, MOVT_D, MOVT_S,
// 	MOVN_D, MOVN_S, MOVZ_D, MOVZ_S, MUL_D, MUL_S,
// 	NEG_S, NEG_D, ROUND_W_D, ROUND_W_S, SQRT_D, SQRT_S,
// 	SUB_D, SUB_S, 
// 	//syscall
// 	SYSCALL  
// }operation;


// typedef stuct mycode{
// 	int opcode;
// 	char sentence[30];
// 	mycode *next; 
// } my_code;

extern void make_code(char* filename, FILE *fpp);

#endif
