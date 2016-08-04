#include "global.h"

struct VarTable;
struct ProcedureTable;
struct EnumListNode;
struct ParaListNode;
typedef struct TypeNode
{
	struct TypeNode* child;
	struct VarTable *fchild;
	struct EnumListNode* elist;
	int lower;
	int upper;
	TableNodeType type;
	int size;
}TypeNode;


typedef struct VarTableNode{
	char* name;
	struct VarTableNode * next;
	char* cur_procedure_name;
	TypeNode* type;
	int address;
	int line_no;
} VarTableNode;



typedef struct VarTable{
	VarTableNode* bucket[50];
}VarTable;


typedef struct ConstTableNode{
	char* name;
	struct ConstTableNode * next;
	char* cur_procedure_name;
	char* label;
	int type;
	int address;
	int size;
	char* value;
	int line_no;
} ConstTableNode;


typedef struct ConstTable{
	ConstTableNode* bucket[50];
}ConstTable;

typedef struct TypeTableNode{
	char* name;
	struct TypeTableNode * next;
	char* cur_procedure_name;
	TypeNode *type;
	int address;
	int line_no;
} TypeTableNode;


typedef struct TypeTable{
	TypeTableNode* bucket[50];
}TypeTable;

typedef struct ProcedureTableNode{
	char* name;
	struct ProcedureTableNode * next;
	TypeNode* returntype;
	int size;
	struct ParaListNode* paralist;
	int paranum;
	int line_no;
} ProcedureTableNode;


typedef struct ProcedureTable{
	ProcedureTableNode* bucket[50];
}ProcedureTable;

typedef struct EnumListNode{
	char* str;
	int num;
	struct EnumListNode* next;
}EnumListNode;

typedef struct ParaListNode{
	char* str;
	int num;
	struct ParaListNode* next;
}ParaListNode;


typedef struct GlobalEnumListNode{
	TypeNode* type;
	struct GlobalEnumListNode* next;
}GlobalEnumListNode;

void makeNewConstTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
void makeNewTypeTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
void makeNewVarTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
void makeNewProcedureTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);

int insertIntoConstTable(ConstTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
int insertIntoTypeTable(TypeTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
int insertIntoVarTable(VarTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
int insertIntoProcedureTable(ProcedureTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
int repeatTest(int line_no, char* name, char* pro_name, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);


VarTableNode* makeNewVarTableNode();
ConstTableNode* makeNewConstTableNode();
TypeTableNode* makeNewTypeTableNode();
ProcedureTableNode* makeNewProcedureTableNode();

void printConstTable(ConstTable* c);
void printTypeTable(TypeTable* t);
void printVarTable(VarTable *v);
void printProcedureTable(ProcedureTable* p);

TypeTableNode* searchTypeTableWithName(char* name,char* cur_procedure_name,TypeTable* MainTypeTable);
ConstTableNode* searchConstTableWithName(char* name,char* cur_procedure_name, ConstTable* MainConstTable);
VarTableNode* searchVarTableWithName(char* name,char* cur_procedure_name, VarTable* MainVarTable);
ProcedureTableNode* searchProcedureTableWithName(char* name,char* cur_procedure_name, ProcedureTable* MainProcedureTable);


TreeNode* getChild(int num, TreeNode * root);

void searchTree(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
void printType(TypeNode* node);
TypeNode* makeNewTypeNode(TreeNode* thisnode, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);//thisnode = type_decl
int doWithSysType(char* literal, int *nodekind);
void popProcedure(char* c1);
void topProcedure(char* c1, char* c2);
int contains(char c, char* str);

TypeNode* getType(char* name, char* pro_name, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
int get_args_list_num(char* name, char* proname, ProcedureTable* MainProcedureTable);
TypeNode* get_args_type(int index, char* name, char* proname, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
void getAddress(char* name, char* proname, int* size, char** labelp, int* address, int* totallevel, int* leveltofather, ConstTable* MainConstTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
TypeNode* get_return_type(char* name, char* proname, ProcedureTable* MainProcedureTable);
int ifExists(char* name, char* proname, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable);
TypeNode* searchEnumList(char* name);
void printEnumList();
void ConvertConstToCode(ConstTable* c, FILE* fp);