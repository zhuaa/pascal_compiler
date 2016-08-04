#include "SymbolTable.h"
#include <string.h>
char* current_procedure;
int current_address = 0;
int level = 0;
GlobalEnumListNode* enumlist;
void searchTree(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	enumlist = NULL;
	errorOccur = 0;
	current_procedure = (char*)malloc(100);
	memset(current_procedure, 0, 100);
	strcpy(current_procedure, "main");

	TreeNode *head = root->child->sibling->child;//routine_heads


	TreeNode *const_type = getChild(2, head);
	makeNewConstTable(const_type, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
	
	makeNewTypeTable(getChild(3, head), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
	
	makeNewVarTable((TreeNode*)getChild(4,head), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);

	ProcedureTableNode* mainnode = makeNewProcedureTableNode();
	mainnode->name = "main";
	mainnode->returntype = NULL;
	mainnode->next = NULL;
	mainnode->paranum = mainnode->line_no = mainnode->size = 0;
	mainnode->paralist = NULL;
	int t = insertIntoProcedureTable(mainnode, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
	if(t == -1)
		return;

	makeNewProcedureTable((TreeNode*)getChild(5,head), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);

	//if(getType("days", "main", MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable) != NULL)
	//	printType(getType("days", "main", MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable));
	/*
	printf("\nnum: %d\n", get_args_list_num("testfunc", MainProcedureTable));
	*/
	printType(get_args_type(1, "testfunc", "main", MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable));
	printType(get_return_type("testfunc", "main_testfunc", MainProcedureTable));
	
	int size, address, totallevel, leveltofather;
	char* label = (char*)malloc(100);
	memset(label, 0, 100);
	
	getAddress("k", "main_testfunc", &size, &label, &address, &totallevel, &leveltofather, MainConstTable, MainVarTable, MainProcedureTable);
	printf("size:%d address:%d totallevel:%d leveltofather:%d label:%s\n", size, address, totallevel, leveltofather, label);
	free(label);
	printf("ifexists: %d", ifExists("dt.year", "main_testfunc", MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable));


}

//void makeNewProcedureTable(TreeNode *)

void makeNewVarTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	TreeNode* vardecl = root->child;
	while(vardecl != NULL)
	{
		TreeNode * thisnode = vardecl->child->sibling;
		TreeNode* list = vardecl->child->child; //namelist
		while(list != NULL)
		{
			
			VarTableNode* node = makeNewVarTableNode();
			node->name = (char*)malloc(strlen(list->literal) + 1);
			memset(node->name, 0, strlen(list->literal) + 1);
			strcpy(node->name, list->literal);

			node->line_no = vardecl->line_no;
			node->address = current_address;
			node->type = makeNewTypeNode(thisnode, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
			if(node->type == NULL)
			{
				return;
			}	
			node->cur_procedure_name = (char*)malloc(strlen(current_procedure) + 1);
			memset(node->cur_procedure_name, 0, strlen(current_procedure) + 1);
			strcpy(node->cur_procedure_name, current_procedure);
			int t = insertIntoVarTable(node, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
			if(t == -1)
			{
				return;
			}

			current_address += node->type->size;
			list = list->sibling;
		}

		vardecl = vardecl->sibling;
	}
}

void makeNewConstTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	TreeNode* constexpr = root->child;
	while(constexpr != NULL)
	{
		ConstTableNode* node = makeNewConstTableNode();
		node->name = (char*)malloc(strlen(constexpr->child->literal) + 1);
		memset(node->name, 0, strlen(constexpr->child->literal) + 1);
		strcpy(node->name, constexpr->child->literal);
		//name
		node->line_no = constexpr->line_no;
		if(constexpr->child->sibling != NULL)
		{
			node->value = (char*)malloc(strlen(constexpr->child->sibling->literal) + 1);
			//printf("%d\n",strlen(constexpr->child->sibling->literal));
			memset(node->value, 0, strlen(constexpr->child->sibling->literal) + 1);
			strcpy(node->value, constexpr->child->sibling->literal);
		}
		//value

		switch(constexpr->child->sibling->nodeKind)
		{
			case integer_const_value_NodeKind:
			{
				node->type = _integer;
				node->size = 4;
			}break;
			case char_const_value_NodeKind:
			{
				node->type = _char;
				node->size = 4;
			}break;
			case real_const_value_NodeKind:
			{
				node->type = _real;
				node->size = 4;
			}break;
			case string_const_value_NodeKind:
			{
				node->type = _string;
				node->size = 256;
			}break;
			case sys_con_const_value_NodeKind:
			{
				if(strcmp(constexpr->child->sibling->literal,"maxint") == 0)
				{
					node->type = _integer;
					node->size = 4;
					node->value = (char*)malloc(strlen("2147483647") + 1);
					memset(node->value, 0, strlen("2147483647") + 1);
					strcpy(node->value,"2147483647");
				}
				else
				{
					node->type = _boolean;
					node->size = 4;
				}
			}break;
			default:
			{
				printf("wrong");
				return ;
			}
		}

		//kind

		node->cur_procedure_name = (char*)malloc(strlen(current_procedure) + 1);
		memset(node->cur_procedure_name, 0, strlen(current_procedure) + 1);
		strcpy(node->cur_procedure_name, current_procedure);

		node->label = (char*)malloc(strlen(node->cur_procedure_name) + strlen(node->name) + 3);
		memset(node->label, 0, strlen(node->cur_procedure_name) + strlen(node->name) + 3);
		strcat(node->label, node->cur_procedure_name);
		strcat(node->label, "_");
		strcat(node->label, node->name);
		//procedure
		int t = insertIntoConstTable(node, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		if(t == -1)
		{
			return;
		}
		//address
		node->address = current_address;
		current_address += 0;

		constexpr = constexpr->sibling;
	}
}

void makeNewTypeTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	TreeNode* typedefi = root->child;
	while(typedefi != NULL)
	{
		TypeTableNode* node = makeNewTypeTableNode();
		node->name = (char*)malloc(strlen(typedefi->child->literal) + 1);
		strcpy(node->name, typedefi->child->literal);
		//name

		node->type = makeNewTypeNode(typedefi->child->sibling, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		//kind
		if(node->type == NULL)
		{
			return;
		}	
		node->line_no = typedefi->line_no;
		node->cur_procedure_name = (char*)malloc(strlen(current_procedure) + 1);
		strcpy(node->cur_procedure_name, current_procedure);
		//procedure
		int t = insertIntoTypeTable(node, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		if(t == -1)
		{
			return;
		}

		typedefi = typedefi->sibling;
	}
}


void makeNewProcedureTable(TreeNode* root, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	TreeNode* pro_decl = root->child;

	while(pro_decl != NULL)
	{
		current_address = 16;
		TreeNode* pro_head = pro_decl->child;
		TreeNode* pro_body = pro_decl->child->sibling;
		ProcedureTableNode* node = makeNewProcedureTableNode();
		strcat(current_procedure, "_");
		strcat(current_procedure, pro_head->child->literal);

		if(pro_head->child->sibling->sibling != NULL)
			node->returntype = makeNewTypeNode(pro_head->child->sibling->sibling, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		node->name = (char*)malloc(strlen(current_procedure) + 1);
		strcpy(node->name, current_procedure);
		makeNewVarTable(pro_head->child->sibling, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);

		node->line_no = pro_decl->line_no;

		int count = 0;
		TreeNode* paralist = pro_head->child->sibling->child;
		ParaListNode* thislist = node->paralist;
		while(paralist != NULL)
		{
			TreeNode* sublist = paralist->child->child; //namelist
			while(sublist != NULL)
			{
				ParaListNode* tmp = (ParaListNode* )malloc(sizeof(ParaListNode));
				tmp->str = (char*)malloc(strlen(sublist->literal) + 1);
				strcpy(tmp->str, sublist->literal);
				tmp->num = count;
				if(count == 0)
				{
					node->paralist = tmp;
					thislist = tmp;
				}
				else
				{
					thislist->next = tmp;
					tmp->next = NULL;
					thislist = tmp;
				}
				count++;
				sublist = sublist->sibling;
			}
			paralist = paralist->sibling;
		}
		node->paranum = count;


		//int listsize = current_address;//参数表的大小

		int tmpsize = current_address;
		makeNewConstTable(getChild(2,pro_body->child), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		makeNewTypeTable(getChild(3,pro_body->child), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		makeNewVarTable(getChild(4, pro_body->child), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		//printf("%d\n",current_address);


		makeNewProcedureTable(getChild(5, pro_body->child), MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		//只有一张函数表！
		node->size = current_address - tmpsize;

		/*
		int list_address = 0;
		TreeNode* namelist = pro_head->child->sibling->child->child->child; //namelist的第一个child
		while(namelist != NULL)
		{
			VarTableNode* tmpnode = searchVarTableWithName(namelist->literal, current_procedure, MainVarTable);
			if(tmpnode != NULL)
			{
				tmpnode->address = node->size + list_address;
				list_address += tmpnode->type->size;
			}
			else
				printf("参数找不到啦\n");
			namelist = namelist->sibling;
		}
		*/
		int t = insertIntoProcedureTable(node, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
		if(t == -1)
			return;
		popProcedure(current_procedure);
		pro_decl = pro_decl->sibling;
	}
}
//这个函数不确定是不是危险
void popProcedure(char* c)
{
	int i = 0;
	for(i = strlen(c) - 1; i >=0; i--)
	{
		if(c[i] == '_')
			break;
	}
	c[i] = '\0';
}

void topProcedure(char* pro, char* new_pro)
{

	int i, j;
	for(i = strlen(new_pro) - 1; i >=0; i--)
	{
		if(new_pro[i] == '_')
			break;
	}
	i++;
	for(j = 0; i < strlen(new_pro); j++, i++)
	{
		pro[j] = new_pro[i];
	}
	pro[j] = 0;
}

TypeTableNode* searchTypeTableWithName(char* name,char* cur_procedure_name, TypeTable* MainTypeTable)
{
	if(MainTypeTable == NULL)
		return NULL;
	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(name); i++)
	{
		hashindex += name[i];
	}
	hashindex = hashindex % 50;
	TypeTableNode* head = MainTypeTable->bucket[hashindex];
	while(head != NULL)
	{
		if(strcmp(head->name, name) == 0 && strcmp(head->cur_procedure_name, cur_procedure_name) == 0)
		{
			return head;
		}
		head = head->next;
	}

	char* new_name = (char*)malloc(strlen(cur_procedure_name) + 1);
	memset(new_name, 0, strlen(cur_procedure_name) + 1);
	strcpy(new_name, cur_procedure_name);
	TypeTableNode* new_node = NULL;
	if(contains('_', new_name) == 0)
	{
		popProcedure(new_name);
		new_node = searchTypeTableWithName(name, new_name, MainTypeTable);
	}
	free(new_name);
	if(new_node != NULL)
		return new_node;

	return NULL;
}

ConstTableNode* searchConstTableWithName(char* name,char* cur_procedure_name, ConstTable* MainConstTable)
{
	if(MainConstTable == NULL)
		return NULL;
	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(name); i++)
	{
		hashindex += name[i];
	}
	hashindex = hashindex % 50;
	ConstTableNode* head = MainConstTable->bucket[hashindex];


	while(head != NULL)
	{
		if(strcmp(head->name, name) == 0 && strcmp(head->cur_procedure_name, cur_procedure_name) == 0)
		{
			return head;
		}
		head = head->next;
	}
	char* new_name = (char*)malloc(strlen(cur_procedure_name) + 1);
	memset(new_name, 0, strlen(cur_procedure_name) + 1);
	strcpy(new_name, cur_procedure_name);
	ConstTableNode* new_node = NULL;
	if(contains('_', new_name) == 0)
	{
		popProcedure(new_name);
		level ++;
		new_node = searchConstTableWithName(name, new_name, MainConstTable);
	}

	free(new_name);
	if(new_node != NULL)
		return new_node;


	return NULL;
}

int contains(char c, char* str)
{
	int i = 0;
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] == c)
			return 0;
	}
	return -1;
}

VarTableNode* searchVarTableWithName(char* name,char* cur_procedure_name, VarTable* MainVarTable)
{
	if(MainVarTable == NULL)
		return NULL;
	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(name); i++)
	{
		hashindex += name[i];
	}
	hashindex = hashindex % 50;

	VarTableNode* head = MainVarTable->bucket[hashindex];

	while(head != NULL)
	{
		if(strcmp(head->name, name) == 0 && strcmp(head->cur_procedure_name, cur_procedure_name) == 0)
		{
			return head;
		}
		head = head->next;
	}
	char* new_name = (char*)malloc(strlen(cur_procedure_name) + 1);
	memset(new_name, 0, strlen(cur_procedure_name) + 1);
	strcpy(new_name, cur_procedure_name);
	VarTableNode* new_node = NULL;
	if(contains('_', new_name) == 0)
	{
		popProcedure(new_name);
		level ++;
		new_node = searchVarTableWithName(name, new_name, MainVarTable);
	}
	free(new_name);
	if(new_node != NULL)
		return new_node;

	return NULL;
}

ProcedureTableNode* searchProcedureTableWithName(char* name,char* cur_procedure_name, ProcedureTable* MainProcedureTable)
{
	if(MainProcedureTable == NULL)
		return NULL;

	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(name); i++)
	{
		hashindex += name[i];
	}


	hashindex = hashindex % 50;


	ProcedureTableNode* head = MainProcedureTable->bucket[hashindex];
	char* that_name = (char*)malloc(1024);//函数名不能超过这么长

	memset(that_name, 0, 1024);
	strcpy(that_name, cur_procedure_name);
	strcat(that_name, "_");
	strcat(that_name, name);
	//printf("%s\n", that_name);	
	while(head != NULL)
	{

		if(strcmp(head->name, that_name) == 0)
		{
			free(that_name);
			return head;
		}
		head = head->next;
	}

	free(that_name);
	char* new_name = (char*)malloc(strlen(cur_procedure_name) + 1);
	memset(new_name, 0, strlen(cur_procedure_name) + 1);
	strcpy(new_name, cur_procedure_name);
	ProcedureTableNode* new_node = NULL;
	if(contains('_', new_name) == 0)
	{
		popProcedure(new_name);
		new_node = searchProcedureTableWithName(name, new_name, MainProcedureTable);
	}
	free(new_name);
	if(new_node != NULL)
		return new_node;

	return NULL;
}

/*
ProcedureTableNode* searchProcedureTableWithName(char* name,char* cur_procedure_name, ProcedureTable* MainProcedureTable)
{
	if(MainProcedureTable == NULL)
		return NULL;
	char* this_name = (char*)malloc(strlen(name) + 1);
	memset(this_name, 0, strlen(name) + 1);
	topProcedure(this_name, name);

	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(this_name); i++)
	{
		hashindex += this_name[i];
	}


	hashindex = hashindex % 50;


	ProcedureTableNode* head = MainProcedureTable->bucket[hashindex];
	char* that_name = (char*)malloc(1024);//函数名不能超过这么长

	while(head != NULL)
	{
		memset(that_name, 0, 1024);
		topProcedure(that_name, head->name);
		if(strcmp(this_name, that_name) == 0)
		{
			//printf("%s %s\n", this_name, that_name);
			return head;
		}
		head = head->next;
	}
	//printf("%s %s\n", this_name, that_name);

	free(this_name);
	free(that_name);

	return NULL;
}
*/

TypeNode* makeNewTypeNode(TreeNode* thisnode, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)//thisnode = type_decl
{
	TypeNode* typenode = (TypeNode *)malloc(sizeof(TypeNode));
	memset(typenode, 0, sizeof(TypeNode));
	switch(thisnode->nodeKind)
	{
		case sys_type_simple_type_decl_NodeKind:
		{
			int tmpkind;
			typenode->size = doWithSysType(thisnode->literal, &tmpkind);
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = tmpkind;
			typenode->lower = 0;
			typenode->upper = 0;
			return typenode;
		}
		case id_simple_type_decl_NodeKind:
		{
			TypeTableNode* typetablenode;
			if((typetablenode = searchTypeTableWithName(thisnode->literal,current_procedure, MainTypeTable)) != NULL)
				return typetablenode->type;
			else
			{
				errorOccur ++;
				printf("line %d : 找不到 %s 作为类型的声明\n", thisnode->line_no, thisnode->literal);
				return NULL;
			}
		}break;
		case lp_name_list_rp_simple_type_decl_NodeKind:
		{
			TreeNode* name_list = thisnode->child->child;
			int count = 0;
			EnumListNode* thislist = typenode->elist;

			while(name_list != NULL)
			{
				EnumListNode* tmp = (EnumListNode* )malloc(sizeof(EnumListNode));
				tmp->str = (char*)malloc(strlen(name_list->literal) + 1);
				strcpy(tmp->str, name_list->literal);
				tmp->num = count;
				if(count == 0)
				{
					typenode->elist = tmp;
					thislist = tmp;
				}
				else
				{
					thislist->next = tmp;
					tmp->next = NULL;
					thislist = tmp;
				}
				name_list = name_list->sibling;
				count++;
			}
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = _enum;
			typenode->lower = 0;
			typenode->upper = 0;
			typenode->size = 4;


			GlobalEnumListNode* newlist = (GlobalEnumListNode*)malloc(sizeof(GlobalEnumListNode));
			newlist->type = typenode;
			if(enumlist != NULL)
			{
				newlist->next = enumlist->next;
				enumlist->next = newlist;
			}	
			else
			{
				newlist->next = NULL;
				enumlist = newlist;
			}	


			//insertIntoNameListTable(thisnode->child);//child的所有Sibling
			return typenode;
		}break;
		case const_dotdot_const_simple_type_decl_NodeKind:
		{
			//anigao
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = _range;
			typenode->lower = atoi(thisnode->child->literal);
			typenode->upper = atoi(thisnode->child->sibling->literal);
			typenode->size = 4;
			return typenode;
		}break;
		case m_const_dotdot_const_simple_type_decl_NodeKind:
		{
			//anigao
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = _mrange;
			typenode->lower = atoi(thisnode->child->literal) * -1;
			typenode->upper = atoi(thisnode->child->sibling->literal);
			typenode->size = 4;
			return typenode;
		}
		case m_const_dotdot_m_const_simple_type_decl_NodeKind:
		{
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = _mmrange;
			typenode->lower = atoi(thisnode->child->literal) * -1;
			typenode->upper = atoi(thisnode->child->sibling->literal) * -1;
			typenode->size = 4;
			return typenode;
		}
		case id_dotdot_id_simple_type_decl_NodeKind:
		{
			ConstTableNode* c1 = searchConstTableWithName(thisnode->child->literal, current_procedure, MainConstTable);
			ConstTableNode* c2 = searchConstTableWithName(thisnode->child->sibling->literal, current_procedure, MainConstTable);
			if(c1->type != _integer || c2->type != _integer)
			{
				errorOccur ++;
				printf("line %d : 范围类型必须是常数\n", thisnode->line_no);
				return NULL;
			}
			typenode->child = NULL;
			typenode->fchild = NULL;
			typenode->type = _range;
			typenode->lower = atoi(c1->value);
			typenode->upper = atoi(c2->value);
			typenode->size = (typenode->upper - typenode->lower) * 4;
			return typenode;
		}
		case array_type_decl_NodeKind:
		{
			TreeNode *subthisnode = thisnode->child;
			if(subthisnode->nodeKind == id_dotdot_id_simple_type_decl_NodeKind)
			{

				ConstTableNode* c1 = searchConstTableWithName(subthisnode->child->literal, current_procedure, MainConstTable);
				ConstTableNode* c2 = searchConstTableWithName(subthisnode->child->sibling->literal, current_procedure, MainConstTable);
				if(c1->type != _integer || c2->type != _integer)
				{
					errorOccur ++;
					printf("line %d : 下标类型必须是常数\n", thisnode->line_no);
					return NULL;
				}
				typenode->lower = atoi(c1->value);
				typenode->upper = atoi(c2->value);
			}
			if(subthisnode->nodeKind == const_dotdot_const_simple_type_decl_NodeKind)
			{
				if(subthisnode->child->nodeKind != integer_const_value_NodeKind
				 || subthisnode->child->sibling->nodeKind != integer_const_value_NodeKind) //const_value .. const_value
				{
					errorOccur ++;
					printf("line %d : 下标类型必须是常数\n", thisnode->line_no);
					return NULL;
				}
				else
				{
					typenode->lower = atoi(subthisnode->child->literal);
					typenode->upper = atoi(subthisnode->child->sibling->literal);
				}
			}
			if(typenode->lower > typenode->upper)
			{
				errorOccur ++;
				printf("line %d : 下标类型必须大于上标\n", thisnode->line_no);
				return NULL;
			}
			typenode->child = makeNewTypeNode(subthisnode->sibling, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);//后面的可以任意递归
			typenode->fchild = NULL;
			typenode->size = typenode->child->size * (typenode->upper + 1);
			typenode->type = _array;
			return typenode;
		}break;
		case record_type_decl_NodeKind:
		{
			int tmpaddress = current_address;
			current_address = 0;
			typenode->fchild = (VarTable*)malloc(sizeof(VarTable));
			memset(typenode->fchild, 0, sizeof(VarTable));
			makeNewVarTable(thisnode, NULL, NULL, typenode->fchild, NULL);
			//分别是var_part主节点和建立后的表指针
			typenode->child = NULL;
			typenode->lower = typenode->upper = 0;
			typenode->type = _record;
			typenode->size = current_address;
			current_address = tmpaddress;
			return typenode;
			//typenode->size =
		}break;
		default:
		{

		}
	}
	return NULL;
}

int doWithSysType(char* literal, int *nodekind)
{
	int size = 0;
	if(strcmp(literal,"integer") == 0)
	{
		*nodekind = _integer;
		size = 4;
	}
	else if(strcmp(literal,"char") == 0)
	{
		*nodekind = _char;
		size = 1;
	}
	else if(strcmp(literal,"boolean") == 0)
	{
		*nodekind = _boolean;
		size = 4;
	}
	else if(strcmp(literal,"string") == 0)
	{
		*nodekind = _string;
		size = 256;
	}
	else if(strcmp(literal,"real") == 0)
	{
		*nodekind = _real;
		size = 4;
	}
	else *nodekind = _none;
	return size;
}

int insertIntoConstTable(ConstTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(node->name); i++)
	{
		hashindex += node->name[i];
	}
	hashindex = hashindex % 50;

	if(repeatTest(node->line_no, node->name, node->cur_procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable) == -1)
		return -1;

	ConstTableNode* head = MainConstTable->bucket[hashindex];
	ConstTableNode* father;
	if(head == NULL)
	{
		MainConstTable->bucket[hashindex] = node;
		return 1;
	}
	while(head != NULL)
	{
		father = head;
		head = head->next;
	}
	father->next = node;
	node->next = NULL;
	return 1;
}

int insertIntoTypeTable(TypeTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{

	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(node->name); i++)
	{
		hashindex += node->name[i];
	}
	hashindex = hashindex % 50;

	if(repeatTest(node->line_no, node->name, node->cur_procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable) == -1)
		return -1;
	TypeTableNode* head = MainTypeTable->bucket[hashindex];
	TypeTableNode* father;

	if(head == NULL)
	{
		MainTypeTable->bucket[hashindex] = node;
		return 1;
	}
	while(head != NULL)
	{
		father = head;
		head = head->next;
	}

	father->next = node;
	node->next = NULL;
	return 1;
}

int insertIntoVarTable(VarTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(node->name); i++)
	{
		hashindex += node->name[i];
	}
	hashindex = hashindex % 50;

	if(repeatTest(node->line_no, node->name, node->cur_procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable) == -1)
		return -1;

	VarTableNode* head = MainVarTable->bucket[hashindex];
	VarTableNode* father;
	if(head == NULL)
	{
		MainVarTable->bucket[hashindex] = node;
		return 1;
	}

	while(head != NULL)
	{
		father = head;
		head = head->next;
	}

	father->next = node;
	node->next = NULL;
	return 1;
}



int insertIntoProcedureTable(ProcedureTableNode *node, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	char* this_name = (char*)malloc(strlen(node->name) + 1);
	memset(this_name, 0, strlen(node->name) + 1);
	topProcedure(this_name, node->name);

	int hashindex = 0;
	int i = 0;
 	for( i = 0; i < strlen(this_name); i++)
	{
		hashindex += this_name[i];
	}
	hashindex = hashindex % 50;

	free(this_name);

	//检查有没有和本函数变量及上层变量的冲突
	char* new_name = (char*)malloc(strlen(node->name) + 1);
	memset(new_name, 0, strlen(node->name) + 1);
	strcpy(new_name, node->name);
	topProcedure(new_name, node->name);
	//printf("%s\n", new_name);
	if(repeatTest(node->line_no, new_name, node->name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable) == -1)
	{
		free(new_name);
		return -1;
	}

	free(new_name);
	ProcedureTableNode* head = MainProcedureTable->bucket[hashindex];
	ProcedureTableNode* father;


	if(head == NULL)
	{
		MainProcedureTable->bucket[hashindex] = node;
		return 1;
	}

	while(head != NULL)
	{
		father = head;
		head = head->next;
	}

	father->next = node;
	node->next = NULL;
	return 1;
}

int repeatTest(int line_no, char* name, char* pro_name, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{

	ConstTableNode* testconstnode = searchConstTableWithName(name, pro_name, MainConstTable);
	if(testconstnode != NULL && MainConstTable != NULL)
	{
		errorOccur ++;
		printf("line %d: %s与%s函数中的const %s重复定义\n", line_no, testconstnode->name, testconstnode->cur_procedure_name, testconstnode->name);
		return -1;
	}


	TypeTableNode* testtypenode = searchTypeTableWithName(name, pro_name, MainTypeTable);
	if(testtypenode != NULL && MainTypeTable != NULL)
	{
		errorOccur ++;
		printf("line %d: %s与%s函数中的type %s重复定义\n", line_no, testtypenode->name, testtypenode->cur_procedure_name, testtypenode->name);
		return -1;
	}

	VarTableNode* testvarnode = searchVarTableWithName(name, pro_name, MainVarTable);
	if(testvarnode != NULL && MainVarTable != NULL)
	{
		errorOccur ++;
		printf("line %d: %s与%s函数中的var %s重复定义\n", line_no, testvarnode->name, testvarnode->cur_procedure_name, testvarnode->name);
		return -1;
	}

	ProcedureTableNode* testpronode = searchProcedureTableWithName(name, pro_name, MainProcedureTable);
	if(testpronode != NULL && MainProcedureTable != NULL)
	{
		errorOccur ++;
		printf("line %d: %s与函数%s重复定义\n", line_no, testpronode->name, testpronode->name);
		return -1;
	}
	return 1;

}

TreeNode* getChild(int num, TreeNode * root)
{
	TreeNode *firstchild = root->child;
	while(num > 1)
	{
		firstchild = firstchild->sibling;
		num --;
	}
	return firstchild;
}

VarTableNode* makeNewVarTableNode()
{
	VarTableNode *node = (VarTableNode*)malloc(sizeof(VarTableNode));
	memset(node, 0, sizeof(VarTableNode));
	node->name = NULL;
	node->next = NULL;
	node->cur_procedure_name = NULL;
	TableNodeType* type = NULL;
	node->address = 0;
	node->line_no = 0;
	return node;
}

ConstTableNode* makeNewConstTableNode()
{
	ConstTableNode *node = (ConstTableNode*)malloc(sizeof(ConstTableNode));
	memset(node, 0, sizeof(ConstTableNode));
	node->name = NULL;
	node->next = NULL;
	node->cur_procedure_name = NULL;
	node->type = _none;
	node->address = 0;
	node->size = 0;
	node->line_no = 0;
	return node;
}

TypeTableNode* makeNewTypeTableNode()
{
	TypeTableNode *node = (TypeTableNode*)malloc(sizeof(TypeTableNode));
	memset(node, 0, sizeof(TypeTableNode));
	node->name = NULL;
	node->next = NULL;
	node->cur_procedure_name = NULL;
	node->type = NULL;
	node->line_no = 0;
	return node;
}

ProcedureTableNode* makeNewProcedureTableNode()
{
	ProcedureTableNode *node = (ProcedureTableNode*)malloc(sizeof(ProcedureTableNode));
	memset(node, 0, sizeof(ProcedureTableNode));
	node->name = NULL;
	node->next = NULL;
	node->size = 0;
	node->line_no = 0;
	return node;
}

void printTypeTable(TypeTable * t)
{
	if(t == NULL) return;
	printf("\nTypeTable\n");
	int i = 0;
 for( i = 0; i < 50; i++)
	{
		TypeTableNode* node = t->bucket[i];
		if(node == NULL)
			continue;
		printf("%d | ", i);
		while(node != NULL)
		{
			printType(node->type);
			printf("name:%s size:%d pro:%s ", node->name, node->type->size, node->cur_procedure_name);

			node = node->next;
			printf(" | ");
		}
		printf("\n---------------------------------------------------------------\n");
	}

}

void printVarTable(VarTable * v)
{
	if(v == NULL) return;
	printf("\nVarTable\n");
	int i = 0;
	for(i = 0; i < 50; i++)
	{
		VarTableNode* node = v->bucket[i];
		if(node == NULL)
			continue;
		printf("%d | ", i);
		while(node != NULL)
		{

			printType(node->type);
			printf("name:%s size:%d pro:%s address:%d", node->name, node->type->size, node->cur_procedure_name, node->address);

			node = node->next;
			printf(" | ");
		}
		printf("\n---------------------------------------------------------------\n");
	}

}

void printConstTable(ConstTable * c)
{
	if(c == NULL) return;
	printf("\nConstTable\n");
	char* a[12] = {"integer","char","string","real","boolean","array","record","range","mrange","mmrange","enum", "_none"};
	int i = 0;
 	for( i = 0; i < 50; i++)
	{
		ConstTableNode* node = c->bucket[i];
		if(node == NULL)
			continue;
		printf("%d | ", i);
		while(node != NULL)
		{

			printf("type:%s name:%s size:%d pro:%s address:%d label:%s value: %s", a[node->type], node->name, node->size, node->cur_procedure_name, node->address, node->label, node->value);

			node = node->next;
			printf(" | ");
		}
		printf("\n------------------------------------------------------------------\n");
	}

}

void printProcedureTable(ProcedureTable* p)
{
	if(p == NULL) return;
	printf("\nProcedureTable\n");
	int i = 0;
 	for( i = 0; i < 50; i++)
	{
		ProcedureTableNode* node = p->bucket[i];
		if(node == NULL)
			continue;
		printf("%d | ", i);
		while(node != NULL)
		{
			if(node->returntype != NULL)
				printType(node->returntype);
			else
				printf("type: NO RETURN ");
			printf("name:%s size:%d ", node->name, node->size);
			node = node->next;
			printf(" | ");
		}
		printf("\n------------------------------------------------------------------\n");
	}

}

void printType(TypeNode* node)
{
	if(node == NULL) return;
	char* a[12] = {"integer","char","string","real","boolean","array","record","range","mrange","mmrange", "enum", "_none"};
	if(node->type < 5)
		printf("type: %s ",a[node->type]);
	else if(node->type == 5)
	{
		printf("type: (%s from: %d to %d with ", a[node->type], node->lower,node->upper);
		printType(node->child);
		printf(") ");
	}
	else if(node->type == 6)
	{
		printf("This is a subvartable of record. Totalsize: %d\n ",node->size);
		printVarTable(node->fchild);
	}
	else if(node->type >= 7 && node->type <= 9)
	{
		printf("type: %s from %d to %d ",a[node->type], node->lower, node->upper);
	}
	else if(node->type == 10)
	{
		printf("type: %s :(", a[node->type]);
		EnumListNode* tmp = node->elist;
		while(tmp != NULL)
		{
			printf("%s ", tmp->str);
			tmp = tmp->next;
		}
		printf(")");
	}
}

//不针对函数的情况
TypeNode* getType(char* name, char* pro_name, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{

	if(contains('.', name) == 0)
	{
		char* new_name = (char*)malloc(strlen(name) + 1);
		char* remain_name = (char*)malloc(strlen(name) + 1);
		memset(new_name, 0, strlen(name) + 1);
		memset(remain_name, 0, strlen(name) + 1);
		int i, j;
		for(i = 0; i < strlen(name); i++)
		{
			if(name[i] == '.')
				break;
			new_name[i] = name[i];
		}
		new_name[i] = 0;
		i++;
		for(j = 0; i < strlen(name); j++, i++)
		{
			remain_name[j] = name[i];
		}
		remain_name[j] = 0;

		new_name[i] = 0;
		VarTableNode* vartablenode;
		if((vartablenode = searchVarTableWithName(new_name, pro_name, MainVarTable)) == NULL)
		{
			free(new_name);
			free(remain_name);
			return NULL;
		}
		else
		{
			TypeNode* tmp = getType(remain_name, pro_name, NULL, NULL, vartablenode->type->fchild, NULL);
			free(new_name);
			free(remain_name);
			return tmp;
		}
	}



	ConstTableNode* consttablenode;
	if((consttablenode = searchConstTableWithName(name, pro_name, MainConstTable)) != NULL)
	{
		TypeNode* tmp = (TypeNode*)malloc(sizeof(TypeNode));
		memset(tmp, 0, sizeof(TypeNode));
		tmp->type = consttablenode->type;
		tmp->child = NULL;
		tmp->fchild = NULL;
		tmp->lower = tmp->upper = 0;
		tmp->size = consttablenode->size;
		return tmp;
	}

	TypeTableNode* typetablenode;
	if((typetablenode = searchTypeTableWithName(name, pro_name, MainTypeTable)) != NULL)
		return typetablenode->type;


	VarTableNode* vartablenode;
	//printf("%s %s\n", name, pro_name);
	if((vartablenode = searchVarTableWithName(name, pro_name, MainVarTable)) != NULL)
	{
		return vartablenode->type;
	}

	TypeNode* tmptype = NULL;
	if((tmptype = searchEnumList(name)) != NULL)
		return tmptype;

	return NULL;
}



TypeNode* get_args_type(int index, char* name, char* proname, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	ProcedureTableNode* pronode = searchProcedureTableWithName(name, proname, MainProcedureTable);
	if(pronode == NULL)
	{
		return NULL;
	}
	else
	{
		ParaListNode* tmp = pronode->paralist;
		while(tmp != NULL)
		{
			if(tmp->num == index)
				break;
			tmp = tmp->next;
		}
		VarTableNode* varnode = searchVarTableWithName(tmp->str, pronode->name, MainVarTable);
		if(varnode == NULL)
		{
			printf("系统错误");
			return NULL;
		}
		else
		{
			return varnode->type;
		}
	}
}


int get_args_list_num(char* name, char* proname, ProcedureTable* MainProcedureTable)
{
	ProcedureTableNode* pronode = searchProcedureTableWithName(name, proname, MainProcedureTable);
	if(pronode == NULL)
	{
		return -1;
	}
	else 
	{
		return pronode->paranum;
	}
}


TypeNode* get_return_type(char* name, char* proname, ProcedureTable* MainProcedureTable)
{
	ProcedureTableNode* pronode = searchProcedureTableWithName(name, proname, MainProcedureTable);
	if(pronode == NULL)
	{
		return NULL;
	}
	else return pronode->returntype;
}

void getAddress(char* name, char* proname, int* size, char** labelp, int* address, int* totallevel, int* leveltofather, ConstTable* MainConstTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	if(contains('.', name) == 0)
	{
		char* new_name = (char*)malloc(strlen(name) + 1);
		char* remain_name = (char*)malloc(strlen(name) + 1);
		memset(new_name, 0, strlen(name) + 1);
		memset(remain_name, 0, strlen(name) + 1);
		int i, j;
		for(i = 0; i < strlen(name); i++)
		{
			if(name[i] == '.')
				break;
			new_name[i] = name[i];
		}
		new_name[i] = 0;
		i++;
		for(j = 0; i < strlen(name); j++, i++)
		{
			remain_name[j] = name[i];
		}
		remain_name[j] = 0;

		new_name[i] = 0;
		VarTableNode* vartablenode;
		if((vartablenode = searchVarTableWithName(new_name, proname, MainVarTable)) == NULL)
		{
			free(new_name);
			free(remain_name);
			return ;
		}
		else
		{
			getAddress(remain_name, proname, size, labelp, address, totallevel, leveltofather, MainConstTable, vartablenode->type->fchild, MainProcedureTable);
			*address = *address;
			free(new_name);
			free(remain_name);
			return ;
		}
	}

	level = 0;
	*totallevel = 0;
	VarTableNode* varnode = searchVarTableWithName(name, proname, MainVarTable);
	if(varnode != NULL)
	{
		*leveltofather = level;
		level = 0;
		(*labelp) = NULL;
		*address = varnode->address;
		*size = varnode->type->size;
		return;
	}

	ConstTableNode* constnode = searchConstTableWithName(name, proname, MainConstTable);
	if(constnode != NULL)
	{
		*leveltofather = level;
		level = 0;
		char *label = (char *)malloc(strlen(constnode->label) * sizeof(char) + 1);
		strcpy(label, constnode->label);
		(*labelp) = label;
		*address = constnode->address;
		*size = constnode->size;
	}

	ProcedureTableNode* procedurenode = searchProcedureTableWithName(name, proname, MainProcedureTable);
	if(procedurenode != NULL)
	{
		*leveltofather = level;
		level = 0;
		char *label = (char *)malloc(strlen(procedurenode->name) * sizeof(char) + 1);
		strcpy(label, procedurenode->name);
		(*labelp) = label;
		*address = 0;
		*size = procedurenode->size;
		char* tmp = (char*)malloc(strlen(proname) + 1);
		strcpy(tmp, procedurenode->name);
		while(contains('_', tmp) == 0)
		{
			popProcedure(tmp);
			*totallevel = *totallevel + 1;

		}
		free(tmp);
	}
	return;
}

int ifExists(char* name, char* proname, ConstTable* MainConstTable, TypeTable* MainTypeTable, VarTable* MainVarTable, ProcedureTable* MainProcedureTable)
{
	if(contains('.', name) == 0)
	{
		char* new_name = (char*)malloc(strlen(name) + 1);
		char* remain_name = (char*)malloc(strlen(name) + 1);
		memset(new_name, 0, strlen(name) + 1);
		memset(remain_name, 0, strlen(name) + 1);
		int i, j;
		for(i = 0; i < strlen(name); i++)
		{
			if(name[i] == '.')
				break;
			new_name[i] = name[i];
		}
		new_name[i] = 0;
		i++;
		for(j = 0; i < strlen(name); j++, i++)
		{
			remain_name[j] = name[i];
		}
		remain_name[j] = 0;

		new_name[i] = 0;
		VarTableNode* vartablenode;
		if((vartablenode = searchVarTableWithName(new_name, proname, MainVarTable)) == NULL)
		{
			free(new_name);
			free(remain_name);
			return -1;
		}
		else
		{
			int tmp = ifExists(remain_name, proname, MainConstTable, MainTypeTable, vartablenode->type->fchild, MainProcedureTable);
			free(new_name);
			free(remain_name);
			return tmp;
		}
	}
	ConstTableNode* constnode = searchConstTableWithName(name, proname, MainConstTable);
	if(constnode != NULL)
		return 0;

	TypeTableNode* typenode = searchTypeTableWithName(name, proname, MainTypeTable);
	if(typenode != NULL)
		return 1;

	VarTableNode* varnode = searchVarTableWithName(name, proname, MainVarTable);
	if(varnode != NULL)
		return 2;

	ProcedureTableNode* procedurenode = searchProcedureTableWithName(name, proname, MainProcedureTable);
	if(procedurenode != NULL)
		return 3;

	if(searchEnumList(name) != NULL)
		return 4;

	return -1;

}

void printEnumList()
 {
 	GlobalEnumListNode* tmp = enumlist;

	while(tmp != NULL)
	{
		TypeNode* tmptype = tmp->type;
		EnumListNode* tmpnode = tmptype->elist;
		while(tmpnode != NULL)
		{
			printf("%s ", tmpnode->str);
			tmpnode = tmpnode->next;
		}
		printf("\n");
		tmp = tmp->next;
	}
 }

TypeNode* searchEnumList(char* name)
{
	GlobalEnumListNode* tmp = enumlist;	
	while(tmp != NULL)
	{
		TypeNode* tmptype = tmp->type;
		EnumListNode* tmpnode = tmptype->elist;
		while(tmpnode != NULL)
		{
			if(strcmp(tmpnode->str, name) == 0)
				return tmptype;
			tmpnode = tmpnode->next;
		}
		tmp = tmp->next;
	}
	return NULL;
}

void ConvertConstToCode(ConstTable* c, FILE* fp)
{
	fprintf(fp, ".data\n");
	if(c == NULL) return;
	int i = 0;
 	for( i = 0; i < 50; i++)
	{
		ConstTableNode* node = c->bucket[i];
		if(node == NULL)
			continue;
		while(node != NULL)
		{
			if(node->type == _boolean)
			{
				if(strcmp(node->value, "false") == 0)
					fprintf(fp, "main_%s : .word %d\n", node->name, 0);
				else if(strcmp(node->value, "true") == 0)
					fprintf(fp, "main_%s : .word %d\n", node->name, 1);
			}	
			else if(node->type == _integer)
			{
				fprintf(fp, "main_%s : .word %d\n", node->name, atoi(node->value));
			}
			else if(node->type == _real)
			{
				fprintf(fp, "main_%s : .word %f\n", node->name, atof(node->value));
			}
			else if(node->type == _char)
			{
				fprintf(fp, "main_%s : .ascii \"%c\"\n", node->name, *node->value);
			}
			else if(node->type == _string)
			{
				fprintf(fp, "main_%s : .asciiz \"%s\"\n", node->name, node->value);
			}

			node = node->next;
		}
	}
}

 
