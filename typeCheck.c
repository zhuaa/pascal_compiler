#include "SymbolTable.h"
//#include <stdio.h>
//#include <stdlib.h>


extern ConstTable* MainConstTable;
extern TypeTable* MainTypeTable;
extern VarTable* MainVarTable;
extern ProcedureTable* MainProcedureTable;

char* invalid_forNode_literal=""; //???????????????????????????????????????????????
int in_this_for=0;

char* itostr(int a){  //int转char*
	char* str = (char *)malloc(10);
	//printf("after malloc\n");
	memset(str, 0, 9);
	//char* str;
	sprintf(str,"%d",a);
	return str;

}


int typeEqual(TypeNode* a,TypeNode* b){
	if(a==0 || b==0){
		return 0;
	}
	if(a->child==NULL)
		if(b->child==NULL)
			if(a->type==_range)
				return(b->type==_integer || b->type==_range);
				
			else
				return(a->type==b->type);
		else 
			return 0;
	else
		if(b->child==NULL)
			return 0;
		else 
			return typeEqual(a->child,b->child);

}



TypeNode* CheckExp(TreeNode* node,char* p_name){
//	printf("in function CheckExp.\n");
	char* procedure_name=p_name;
	switch(node->nodeKind){

		case(expression_NodeKind):{
			//printf("--------------------------It's an expression\n");

			TypeNode* t1;
			TypeNode* t2;
			t1=CheckExp(node->child,procedure_name);
			//printf("back to expression,t1_type:%d\n",t1->type);
			t2=CheckExp(node->child->sibling->sibling,procedure_name);
			if(typeEqual(t1,t2))
				return t1;
			else{
				printf("line %d,the expression's var type are not fit.\n",node->child->line_no);
				return 0;
			}
		}
		case(end_expression_NodeKind):{
			//printf("--------------------------It's an end_expression\n");
			return CheckExp(node->child,procedure_name);
		}
		case(expr_NodeKind):{
			//printf("--------------------------It's an expr\n");
			TypeNode* t1=CheckExp(node->child,procedure_name);
			TypeNode* t2=CheckExp(node->child->sibling->sibling,procedure_name);
			if(typeEqual(t1,t2))
				return t1;
			else{
				printf("line %d,the expr's var type are not fit.\n",node->child->line_no);
				return 0;
			}
		}
		case(end_expr_NodeKind):{
			//printf("--------------------------It's an end_expr\n");
			return CheckExp(node->child,procedure_name);
		}

		case(term_NodeKind):{
			//printf("--------------------------It's an term\n");
			//printf("t1:%s\n",node->child->);
			TypeNode* t1=CheckExp(node->child,procedure_name);
			//printf("back to term,t1_type:%d\n",t1->type);
			//printf("in term,t2_nodeKind:%s\n",NodeKindStr[node->child->sibling->sibling->nodeKind]);
			TypeNode* t2=CheckExp(node->child->sibling->sibling,procedure_name);
			//printf("back to term,t2_type:%d\n",t2->type);
			if(typeEqual(t1,t2))
				return t1;
			else{
				printf("line %d,the term's var type are not fit.\n",node->child->line_no);
				return 0;
			}

		}
		case(end_term_NodeKind):{
			//printf("--------------------------It's an end_term\n");
			return CheckExp(node->child,procedure_name);
		}
		case(const_factor_NodeKind):{
			//printf("---------------------------It's a const_factor\n");
					switch(node->child->nodeKind){
						case(integer_const_value_NodeKind):{
							//printf("------------------------------------It's an integer_const_factor\n");
							//TypeNode* constType;
							//printf("before malloc\n");
							TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							//printf("after malloc\n");
							memset(constType, 0, sizeof(TypeNode));
							//printf("after memset\n");

							constType->child=NULL;
							//printf("1\n");
							constType->fchild=NULL;
							//printf("2\n");
							constType->lower=0;
							//printf("3\n");
							constType->upper=0;
							//printf("4\n");
							constType->type=_integer;
							//printf("5\n");
							constType->size=0;
							//printf("6\n");

							return constType;
						}
						case(real_const_value_NodeKind):{
							//printf("------------------------------------It's a real_const_factor\n");
							//TypeNode* constType;
							TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));

							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_real;
							constType->size=0;
							return constType;
						}
						case(char_const_value_NodeKind):{
							//printf("------------------------------------It's a char_const_factor\n");
							TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));

							//TypeNode* constType;
							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_char;
							constType->size=0;
							return constType;
						}
						case(string_const_value_NodeKind):{
							//printf("------------------------------------It's a string_const_factor\n");
							TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));
							//TypeNode* constType;
							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_string;
							constType->size=0;
							return constType;
						}
						case(sys_con_const_value_NodeKind):{//系统常量
							//printf("------------------------------------It's a sys_con_const_factor\n");
							TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));
							//TypeNode* constType;
							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_boolean ;
							constType->size=0;
							return constType;
						}
						default:{
							printf("line %d,invalid const value.\n",node->child->child->line_no);
							return 0; 
						}
					}
		}
		case(id_factor_NodeKind):{

					//printf("---------------------------It's an id_factor\n");
					TreeNode* leaf_node=node->child;
					char* name=leaf_node->literal;	
					//if((strcmp(name,invalid_forNode_literal)==0) && (in_this_for==1)){          //?????????????????????????????????????
			//	printf("----------------------It's an invalid_forNode_literal\n");
					//	printf("line %d,for_id %s can not be read in for.\n", leaf_node->line_no,id_node->literal);
					//	return 0;
					//}

					if(ifExists(name,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)>=0){

						TypeNode* type=getType(name,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
						leaf_node->Type=type->type;
						
						if(type->type==_enum){
							EnumListNode* element=type->elist;
							while(element!=NULL){  //找到了说明是个枚举的值
								if(strcmp(element->str ,name)==0){
									leaf_node->nodeKind=integer_const_value_NodeKind;
									leaf_node->literal=itostr(element->num);
									return type;
								}
								else{
									element=element->next;
									continue;
							    }
						    }
						}
						if(type->type==_string){
							leaf_node->Type=_string;
						}
							
						
						int size=0;
						char* label;
						int address=0;
						int level=0;
						int leveltofather=0;
						//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
						getAddress(name,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);
						//printf("%s,label:%s,address:%d,size:%d,level:%d,leveltofather:%d\n",leaf_node->literal,label,address,size,level,leveltofather);



						leaf_node->label=label;
						leaf_node->address=address;
						leaf_node->size=size;
						leaf_node->level=level;
						leaf_node->leveltofather=leveltofather;
						return type;
					}
					else{
						printf("line %d,var %s have not been defined.\n",node->child->line_no,node->child->literal);
						return 0;
					}
		}
		case(id_lp_args_rp_factor_NodeKind):{
			// 调用子函数
					//printf("---------------------------It's an id_lp_args_rp_factor\n");
					int flag=0;
					TreeNode* fun_node=node->child;
					if(ifExists(fun_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)>=0){ //检查函数是否存在
						 {
						int size=0;
						char* label;
						int address=0;
						int level=0;
						int leveltofather=0;
					//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
						getAddress(fun_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
						fun_node->label=label;
						fun_node->address=address;
						fun_node->size=size;
						fun_node->level=level;
						fun_node->leveltofather=leveltofather;
				      }
						
						int args_num=get_args_list_num(fun_node->literal,procedure_name, MainProcedureTable);; //得到函数的参数个数&&&&&&&&&&&&&&&&&
						TreeNode* arg=fun_node->sibling->child;
						int i;
						for(i=0;i<args_num;i++){
							TypeNode* type2=CheckExp(arg,procedure_name);
							if(type2==0){   //假如检查到参数返回值为0,即参数表达式有错。flag=1
								flag=1;
								break;
							}
							else{   
								TypeNode* type1=get_args_type(i,fun_node->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);//得到第i个参数的类型&&&&&&&&&&&&&&&&&&&&&
								typeEqual(type1,type2);//比较类型
								arg=arg->sibling;//检查下一个参数
							}

						}
						if(i==args_num){  //遍历完所有函数参数
							if(arg==NULL)//不存在多余的参数
								return(get_return_type(fun_node->literal,procedure_name, MainProcedureTable));  //得到函数返回值类型&&&&&&&&
							else {       //还存在多余参数,说明参数太多
								printf("line %d,%s funtion's agrs are too more.\n",fun_node->line_no,fun_node->literal);
								return 0;
							}
						}
						else { //未遍历完参数
							if(flag!=1){ //参数表达式没错,说明参数太少
								printf("line %d,%s funtion's agrs are too less.\n",fun_node->line_no,fun_node->literal);
								return 0;
							}
							else  //参数表达式有错
								return 0;
						}
					}
					else {//函数不存在 
						printf("line %d,The funtion %s is not exist.\n",fun_node->line_no,fun_node->literal);
						return 0;
					}

				
		}
		//case(sys_func_lp_args_rp_factor_NodeKind)://  系统调用   !!!!!!!!!!!!!!!!!!!!!!1
		case(lp_exp_rp_factor_NodeKind):{

			//printf("---------------------------It's a lp_exp_rp_factor\n");
			TreeNode* exp_node=node->child;
			return CheckExp(exp_node,procedure_name);
		}
		case(not_factor_factor_NodeKind):{

					//printf("---------------------------It's a not_factor_factor\n");
					TreeNode* factor_node=node->child->child;
					if(factor_node->nodeKind==integer_const_value_NodeKind){
						TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));
						//TypeNode* constType;
							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_integer;
							constType->size=0;
							return constType;
					}
					else{
						printf("line %d,the not_factor is not an integer type.\n",factor_node->line_no);
						return 0;
					}	

		}
		case(minus_factor_factor_NodeKind):{

					//printf("---------------------------It's a minus_factor__factor\n");
					TreeNode* factor_node=node->child->child;
					//printf("in minus,%s\n",NodeKindStr[factor_node->nodeKind]);
					if(factor_node->nodeKind==integer_const_value_NodeKind || CheckExp(node->child,procedure_name)->type==_integer ){
						TypeNode* constType = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							memset(constType, 0, sizeof(TypeNode));
						//TypeNode* constType;
							constType->child=NULL;
							constType->fchild=NULL;
							constType->lower=0;
							constType->upper=0;
							constType->type=_integer;
							constType->size=0;
							return constType;
						 
					}
					else{
						printf("line %d,the minus_factor is not an integer type.\n",factor_node->line_no);
						return 0;
					}

		}
		case(id_lb_exp_rb_factor_NodeKind):{

					//printf("---------------------------It's an id_lb_exp_rb_factor\n");
					TreeNode* array_node=node->child;
					int tag=ifExists(array_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
					TypeNode* type=getType(array_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
					if(tag>=0 && type->type==_array){
						  TypeNode* type1=getType(array_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable)->child; //不考虑多维数组
						TypeNode* index_type=CheckExp(array_node->sibling,procedure_name);
						if(index_type==0)//index表达式有错
								return 0;
						if(index_type->type==_integer){  //index表达式没有错 并且 类型匹配
						int size=0;
						char* label;
						int address=0;
						int level=0;
						int leveltofather=0;							//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
							getAddress(array_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);
							array_node->label=label;
							array_node->address=address;
							array_node->size=size;
							array_node->level=level;
							array_node->leveltofather=leveltofather;
							return type1;
						}
			
							else{   //类型不匹配
								printf("line %d,The array %s's index are not integer type.\n",array_node->line_no,array_node->literal);
								return 0;
							}

					}

					else
						if(tag<0){
							printf("line %d,The array %s has not been defined.\n",array_node->line_no,array_node->literal);
							return 0;
						}
						else if(type->type!=_array){
							printf("line %d,var %s is not an array.\n",array_node->line_no,array_node->literal);
							return 0;
						}
		}
		case(id_dot_id_factor_NodeKind):{
			//printf("---------------------------It's an id_dot_id_factor\n");
					TreeNode* record_node=node->child;
					TreeNode* element_node=record_node->sibling;
					int tag=ifExists(record_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
					TypeNode* type=getType(record_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
					if(tag>=0&&(type->type==_record))
					{
						char* record_name=record_node->literal;
						char* element_name=element_node->literal;
						char name[strlen(record_name)+strlen(element_name)+1+1];
							name[strlen(record_name)+strlen(element_name)+1+1]='\0';
							strcpy(name,record_name);
							strcat(name,".");
							strcat(name,element_name);
						if(ifExists(name,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)<0){  
					    	printf("line %d,record %s has no such an element named %s.\n",record_node->line_no,record_node->literal,element_node->literal);
					    	return 0;
					    }
					//	TypeNode* type1=get_element_type(record_node->literal,element_node->literal,procedure_name);  //&&&&&&&&&&&&&&&&&&&
					//	TypeNode* type2=CheckExp(element_node->sibling,procedure_name);
					//	if(type2==0) return 0;
					//	if(typeEqual(type1,type2)){  //index表达式没有错 并且 类型匹配
						TypeNode* element_type=getType(name,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&&&&
							int size=0;
							char* label;
							int address=0;
							int level=0;
							int leveltofather=0;
							//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
							getAddress(record_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);
							record_node->label=label;
							record_node->address=address;
							record_node->size=size;
							record_node->level=level;
							record_node->leveltofather=leveltofather;
					
							getAddress(name,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);
							element_node->label=label;
							element_node->address=address;
							element_node->size=size;
							element_node->level=level;
							element_node->leveltofather=leveltofather;
							return element_type;

				

					}
	
					else{

						if(tag<0){
							printf("line %d,The record %s has not been defined.\n",record_node->line_no,record_node->literal);
							return 0;
						}
						else if(type->type!=_array){
							printf("line %d,variable %s is not a record.\n",record_node->line_no,record_node->literal);
							return 0;
						}

			 		}
		}



		default:
		printf("line %d,It's an unknow expression.\n",node->line_no);
		return 0;

	}

}






int CheckStmt(TreeNode* node,char* p_name){
	//printf("in function CheckStmt\n");
	char* procedure_name=p_name;
	switch(node->nodeKind){
		case(compound_stmt_NodeKind):
			//printf("----------------------It's a compound_stmt\n");
			return CheckStmt(node->child,procedure_name);
		case(stmt_list_NodeKind):{
			//printf("----------------------It's a stmt_list\n");
			TreeNode* stmt=node->child;
			int a=1;
			while(stmt!=NULL){
				a=a & CheckStmt(stmt,procedure_name);
				//printf("back to stmt_list!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				stmt=stmt->sibling;

			}
			return a;
		
		}
		case(non_labeled_stmt_NodeKind):{
			//printf("----------------------It's a non_labeled_stmt\n");
			return CheckStmt(node->child,procedure_name);
		}

		case(id_assign_stmt_NodeKind):{
			//printf("----------------------It's a id_assign_stmt\n");
			TreeNode* id_node=node->child;
			//printf("======================id:%s\n",id_node->literal);
			//printf("in check,invalid_forNode_literal:%s,in_this_for:%d.\n",invalid_forNode_literal,in_this_for);

			if((strcmp(id_node->literal,invalid_forNode_literal)==0) && (in_this_for==1)){          //?????????????????????????????????????
			//	printf("----------------------It's an invalid_forNode_literal\n");
				printf("line %d,for_id %s can not be assigned in for.", id_node->line_no,id_node->literal);
				return 0;
			}

			if(ifExists(id_node->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)<0){
				printf("line %d,The varilable %s has not been defined.\n",id_node->line_no,id_node->literal);
				return 0;
			}
			else if(ifExists(id_node->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)==3){
				//printf("!!!!!!!!!!!!!!!funfun");
				//int len1=strlen(id_node->literal);
				int len2=strlen(procedure_name);
				while (procedure_name[--len2] != '_');
				if (strcmp(id_node->literal, procedure_name + len2 + 1) == 0) {
					id_node->address = 12;
					//printf("!!!!!!!!!!!!!\n");
					return (CheckExp(id_node->sibling,procedure_name)!=0);
				} else {
					printf("line %d,function only can be assigned in itself.\n",id_node->line_no);
					return 0;
				}


			}


			else if(ifExists(id_node->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)!=2){
				printf("line %d,The var %s is not an id.\n",id_node->line_no,id_node->literal);
				return 0;	
			}

			TypeNode* t1=getType(id_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
			//printf("id_type:%d\n",t1->type);

			//printf("p_name:%s\n",p_name);
			//printf("exp_nodeKind:%s\n",NodeKindStr[id_node->sibling->nodeKind]);

			TypeNode* t2=CheckExp(id_node->sibling,p_name);
			{
				int size=0;
				char* label;
				int address=0;
				int level=0;
				int leveltofather=0;
				//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
				getAddress(id_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
				id_node->label=label;
				id_node->address=address;
				id_node->size=size;
				id_node->level=level;
				id_node->leveltofather=leveltofather;
				//printf("label:%s,address:%d,size:%d,level:%d,leveltofather:%d\n",label,address,size,level,leveltofather);
			}

			if(t2==0) return 0;
			//printf("back to id_assign,t1_type:%d,t2_type:%d\n",t1->type,t2->type);
			if(typeEqual(t1,t2)){
		
				return 1;
			}
			else{
				printf("line %d,The var %s's type are not fit by this assignment.\n",id_node->line_no,id_node->literal);
				return 0;

			}
		}
		case(id_lb_exp_rb_assign_stmt_NodeKind):{
			//printf("----------------------It's a id_lb_exp_rb_assign_stmt\n");
			TreeNode* array_node=node->child;
					int tag=ifExists(array_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
					TypeNode* type=getType(array_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
					if(tag==2 && type->type==_array){
						TypeNode* t1=getType(array_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable)->child; //不考虑多维数组
						
						TypeNode* index_type=CheckExp(array_node->sibling,procedure_name);  //index 为int
						if(index_type==0) return 0;
						//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!here\n");
						TypeNode* t2=CheckExp(array_node->sibling->sibling,procedure_name); //被赋值类型

						if(index_type->type==_integer){  //index表达式没有错 并且 类型匹配
							if(typeEqual(t1,t2)){
							int size=0;
							char* label;
							int address=0;
							int level=0;
							int leveltofather=0;
								//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
								getAddress(array_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);
								array_node->label=label;
								array_node->address=address;
								array_node->size=size;
								array_node->level=level;
								array_node->leveltofather=leveltofather;
								return 1;
							}
							else{
								printf("line %d,array %s's element's type are not fit by this assignment.\n",array_node->line_no,array_node->literal);
								return 0;
							}
						}
					
						else{   //类型不匹配
								printf("line %d,The array %s's index are not integer type.\n",array_node->line_no,array_node->literal);
								return 0;
							}

					}

					else
						if(tag<0){
							printf("line %d,The array %s has not been defined.\n",array_node->line_no,array_node->literal);
							return 0;
						}
						else if(type->type!=_array){
							printf("line %d,variable %s is not an array.\n",array_node->line_no,array_node->literal);
							return 0;
						}	
		}

		case(id_dot_id_assign_stmt_NodeKind):{//record
					//printf("----------------------It's a id_dot_id_assign_stmt\n");			//if(getType(node->child->literal,procedure_name,MainVarTable).fchild==CheckExp(node->child->sibling))
			        TreeNode* record_node=node->child;
					TreeNode* element_node=record_node->sibling;
					int tag=ifExists(record_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
					TypeNode* type=getType(record_node->literal,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);
					if(tag>=0&&(type->type==_record))
					{
						char* record_name=record_node->literal;
						char* element_name=element_node->literal;
						char name[strlen(record_name)+strlen(element_name)+1+1];
							name[strlen(record_name)+strlen(element_name)+1+1]='\0';
							strcpy(name,record_name);
							strcat(name,".");
							strcat(name,element_name);
						if(ifExists(name,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)<0){  //&&&&&&&&&&&&&&&&&&&
					    	printf("line %d,record %s has no such an element named %s.\n",record_node->line_no,record_node->literal,element_node->literal);
					    	return 0;
					    }
					    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!record_element_name:%s!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",name);

						TypeNode* type1=getType(name,procedure_name,MainConstTable,MainTypeTable,MainVarTable,MainProcedureTable);  //&&&&&&&&&&&&&&&&&&&
						//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!in a record assign!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
						TypeNode* type2=CheckExp(element_node->sibling,procedure_name);
						if(type1!=NULL && type2!=NULL)
						//printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!type1:%d,type2:%d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",type1->type,type2->type);
						if(type2==0) return 0;
						{
							int size=0;
							char* label;
							int address=0;
							int level=0;
							int leveltofather=0;
							//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
							getAddress(record_name,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
							record_node->label=label;
							record_node->address=address;
							record_node->size=size;
							record_node->level=level;
							record_node->leveltofather=leveltofather;
							getAddress(name,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
							element_node->label=label;
							element_node->address=address;
							element_node->size=size;
							element_node->level=level;
							element_node->leveltofather=leveltofather;
						}
						if(typeEqual(type1,type2)){  //index表达式没有错 并且 类型匹配
	
							return 1;

						}	
						else{
							//类型不匹配
							printf("line %d,The record %s's element %s's type are not fit by this assignment.\n",record_node->line_no,record_node->literal,element_node->literal);
							return 0;
						}

					}
	
					else{

						if(tag<0){
							printf("line %d,The record %s has not been defined.\n",record_node->line_no,record_node->literal);
							return 0;
						}
						else if(type->type!=_array){
							printf("line %d,variable %s is not a record type.\n",record_node->line_no,record_node->literal);
							return 0;
						}

			 		}
		}
	
		//case(id_proc_stmt_NodeKind)://调用函数
		case(id_lp_args_rp_proc_stmt_NodeKind):{//函数引用
					//printf("----------------------It's a id_lp_args_rp_proc_stmt\n");
			//从符号表得到函数参数个数n和类型？？？
			       int flag=0;
					TreeNode* fun_node=node->child;
					if(ifExists(fun_node->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)>=0){ //检查函数是否存在
						
					  {
						int size=0;
						char* label;
						int address=0;
						int level=0;
						int leveltofather=0;
					//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
						getAddress(fun_node->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
						fun_node->label=label;
						fun_node->address=address;
						fun_node->size=size;
						fun_node->level=level;
						fun_node->leveltofather=leveltofather;
				      }

						int args_num=get_args_list_num(fun_node->literal,procedure_name, MainProcedureTable); //得到函数的参数个数&&&&&&&&&&&&&&&&&
						TreeNode* arg=fun_node->sibling->child;
						int i;
						for(i=0;i<args_num;i++){
							TypeNode* type2=CheckExp(arg,procedure_name);
							if(type2==0){   //假如检查到参数返回值为0,即参数表达式有错。flag=1
								flag=1;
								break;
							}
							else{   
								TypeNode* type1=get_args_type(i,fun_node->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);//得到第i个参数的类型&&&&&&&&&&&&&&&&&&&&&
								typeEqual(type1,type2);//比较类型
								arg=arg->sibling;//检查下一个参数
							}

						}
						if(i==args_num){ //遍历完所有函数参数
							if(arg==NULL)//不存在多余的参数
								return 1;
							else{  //还存在多余参数,说明参数太多
								printf("line %d,%s funtion's agrs are too more.\n",fun_node->line_no,fun_node->literal);
								return 0;
							}
						}
						else{ //未遍历完参数
							if(flag!=1){  //参数表达式没错,说明参数太少
								printf("line %d,%s funtion's agrs are too less.\n",fun_node->line_no,fun_node->literal);
								return 0;
							}
							else  //参数表达式有错
								return 0;
						}
					}
					else {//函数不存在 
						printf("line %d,The funtion %s has not been defined.",fun_node->line_no,fun_node->literal);
						return 0;
					}

			

		}
        
		case(sys_proc_lp_args_rp_proc_stmt_NodeKind): {// 系统函数
			//printf("----------------------sys_proc_lp_args_rp_proc_stmt\n");
			char* proc_name=node->child->literal;
			//getType(proc_name,procedure_name,);//得到函数的参数类型
			if(strcmp(proc_name,"write")==0 || strcmp(proc_name,"writeln")==0){
				TreeNode* arg_list=node->child->sibling;
				TreeNode* expression=arg_list->child;
				int a=1;
				while(expression!=NULL){
					a=a & (CheckExp(expression,procedure_name)!=0);
					expression->Type=CheckExp(expression,procedure_name)->type;
					expression=expression->sibling;
				}

				return a;

			}
			else
				return 0;

			
	
		}



		case(read_lp_factor_rp_proc_stmt_NodeKind):{
			//printf("----------------------It's a read_lp_factor_rp_proc_stmt\n");
			if(node->child->sibling->nodeKind==const_factor_NodeKind){
				printf("line %d,read stmt can not have const_type parameter.\n",node->line_no);
				return 0;
			}
			else{
				if((strcmp(node->child->sibling->child->literal,invalid_forNode_literal)==0) && (in_this_for==1)){          //?????????????????????????????????????
			//	printf("----------------------It's an invalid_forNode_literal\n");
				printf("line %d,for_id %s can not be read in for.\n", node->line_no,invalid_forNode_literal);
				return 0;
			}
				return (CheckExp(node->child->sibling,procedure_name)!=0);

			} 
		
			//else CheckExp(node->child,procedure_name);
		}

		case(if_stmt_NodeKind):{
			//printf("----------------------It's a if_stmt\n");
			TypeNode* type=CheckExp(node->child,procedure_name);

			int b=CheckStmt(node->child->sibling,procedure_name);
			int c=CheckStmt(node->child->sibling->sibling,procedure_name);
			//printf("back to if,checkstmt:%d\n",b);
			return(type && b && c);
		}

		case(else_clause_NodeKind):{
			//printf("----------------------It's a else_clause\n");
			return CheckStmt(node->child,procedure_name);
		}
		case(empty_else_clause_NodeKind):{
			//printf("----------------------It's a empty_else_clause\n");
			return 1;
		}

		case(repeat_stmt_NodeKind):{
			//printf("----------------------It's a repeat_stmt\n");
			int a=CheckStmt(node->child,procedure_name);
			TypeNode* b=CheckExp(node->child->sibling,procedure_name);
			return(a && (b!=0));
		}
		case(while_stmt_NodeKind):{
			//printf("----------------------It's a while_stmt\n");
			TypeNode* a=CheckExp(node->child,procedure_name);
			int b=CheckStmt(node->child->sibling,procedure_name);
			return(a && (b!=0));
		}
		case(for_stmt_NodeKind):{
			 //三者类型是否相等：
			//printf("----------------------It's a for_stmt\n");
			TreeNode* id=node->child;


			if(ifExists(id->literal,procedure_name, MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable)<0){
				printf("line %d,var %s has not been defined.\n",id->line_no,id->literal);
				return 0;
			}
			TypeNode* t1=getType(id->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
			//printf("for stmt,id_type:%d\n",t1->type);//printf();
			if(t1==0) return 0;
			TypeNode* t2=CheckExp(id->sibling,procedure_name);
			//printf("for stmt,from_exp_type:%d\n",t2->type);//printf();
			TypeNode* t3=CheckExp(id->sibling->sibling->sibling,procedure_name);
			//printf("for stmt,to_exp_type:%d\n",t3->type);//printf();
			int a=(typeEqual(t1,t2)&& typeEqual(t1,t3));
			//printf("三者是否相等：%d\n",a);
			if(a==0){
				printf("line %d,this for_(down)to_stmt's three element type error\n",id->line_no);
				return 0;
			}
			else{
				invalid_forNode_literal = id->literal;//?????????????????????????????
				in_this_for = 1;
				
				//printf("before check,invalid_forNode_literal:%s,in_this_for:%d.\n",invalid_forNode_literal,in_this_for);
				
				int b=CheckStmt(id->sibling->sibling->sibling->sibling,procedure_name);
				//printf("back to for!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			
				invalid_forNode_literal = "";//?????????????????????????????
				in_this_for = 0;

				//printf("after check,invalid_forNode_literal:%s,in_this_for:%d.\n",invalid_forNode_literal,in_this_for);

				int size=0;
				char* label;
				int address=0;
				int level=0;
				int leveltofather=0;
			//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
			getAddress(id->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
			id->label=label;
			id->address=address;
			id->size=size;
			id->level=level;
			id->leveltofather=leveltofather;
			if(b==0) return 0;
			else {
				//printf("back to for,label:%s,address:%d,size:%d,level:%d,leveltofather:%d\n",label,address,size,level,leveltofather);
				return 1;
			}
			}
		}
		case(to_direction_NodeKind):{
			//printf("----------------------It's a to_direction\n");
			if(CheckExp(node->child,procedure_name)!=0)
				return 1;
			else 
				return 0;
		}

		case(down_direction_NodeKind): {
			//printf("----------------------It's a down_direction\n");
			if(CheckExp(node->child,procedure_name)!=0)
				return 1;
			else 
				return 0;
		}
		case(case_stmt_NodeKind):{
			//printf("----------------------It's a case_stmt\n");
			TreeNode* exp_node=node->child;
			TreeNode* list_node=exp_node->sibling;
			TreeNode* case_expr=list_node->child;

			TypeNode* type=CheckExp(exp_node,procedure_name);

	
			int a=1;
			while(case_expr!=NULL){
				TreeNode* case_val=case_expr->child;
				//printf("%d\n",case_expr);
				TreeNode* stmt=case_val->sibling;

				TypeNode* val_type = (TypeNode *)malloc(sizeof(TypeNode) + 1);
							//printf("after malloc\n");
				memset(val_type, 0, sizeof(TypeNode));
				
				if(case_val->nodeKind==integer_const_value_NodeKind){

					val_type->child=NULL;
							//printf("1\n");
					val_type->fchild=NULL;
							//printf("2\n");
					val_type->lower=0;
							//printf("3\n");
					val_type->upper=0;
							//printf("4\n");
					val_type->type=_integer;
							//printf("5\n");
					val_type->size=0;

				}
				else if(case_val->nodeKind==char_const_value_NodeKind){
					val_type->child=NULL;
							//printf("1\n");
					val_type->fchild=NULL;
							//printf("2\n");
					val_type->lower=0;
							//printf("3\n");
					val_type->upper=0;
							//printf("4\n");
					val_type->type=_char;
							//printf("5\n");
					val_type->size=0;
				}
				else if(case_val->nodeKind==id_factor_NodeKind){
					val_type = CheckExp(case_val,procedure_name);

				}

				//TypeNode* val_type=getType(case_val->literal,procedure_name,MainConstTable, MainTypeTable, MainVarTable, MainProcedureTable);
				if(typeEqual(type,val_type)) {
					a=a & CheckStmt(stmt,procedure_name);
					case_expr=case_expr->sibling;
					continue;
				}
				else{
					printf("line %d,case type mismatch.\n",case_val->line_no);
					case_expr=case_expr->sibling;
					continue;
				}

			}
			return a;
		}
			//CheckStmt(exp_node->sibling);
		// case(case_expr_list_NodeKind):{
		// 	TreeNode* case_expr=node->child;
		// 	int a=0;
		// 	while(stmt!=NULL){
		// 		a=a & CheckStmt(case_expr,procedure_name);
		// 		case_expr=case_expr->sibling;

		// 	}
		// }
		//case(const_case_expr_NodeKind):
		//case(id_case_expr_NodeKind):
		//case(goto_stmt_NodeKind)://不要
		
		default:
			return 0;

	}
}





int typeCheck(TreeNode* root,char* procedure_name){
	
	//printf("in function typeCheck\n");
	//printf("%s\n",procedure_name);

	int flag=0;
	char* current_procedure_name="";

	if(root==NULL) {  
		return 0;
	}  //空
	else {

		if(root->nodeKind==function_head_NodeKind || root->nodeKind==procedure_head_NodeKind){ //如果node进入新的procedure

			//if(root->nodeKind==program_head_NodeKind)	
			//	root->child->label="main";
			//else{

			//printf("It's a head node\n");
			flag=1;
			
			  {
				int size=0;
				char* label;
				int address=0;
				int level=0;
				int leveltofather=0;
			//getAddress(char*name, char* procedure_name,int* size,char** label,int* address,int* level,int* leveltofather); 
				getAddress(root->child->literal,procedure_name,&size,&label,&address,&level,&leveltofather,MainConstTable, MainVarTable,MainProcedureTable);//&&&&&&&&&&&&&&&&&&&&&
				root->child->label=label;
				root->child->address=address;
				root->child->size=size;
				root->child->level=level;
				root->child->leveltofather=leveltofather;
			   }

			current_procedure_name=root->child->literal;
			//printf("current_procedure_name:%s\n",current_procedure_name);

			char p_name[strlen(procedure_name)+strlen(current_procedure_name)+1+1];
			p_name[strlen(procedure_name)+strlen(current_procedure_name)+1+1]='\0';
			strcpy(p_name,procedure_name);
			strcat(p_name,"_");
			strcat(p_name,current_procedure_name);
			procedure_name=p_name;

			//}


			typeCheck(root->child,procedure_name);  //主函数只用来加 procedure_name
			typeCheck(root->sibling,procedure_name);

		}
		else if(root->nodeKind==compound_stmt_NodeKind){  //如果是stmt语句
			//printf("It's a stmt node\n");
			//printf("%s\n",root->nodeKind);
		    return CheckStmt(root,procedure_name); //检查语句下面的变量类型是否被定义过了,类型是否不对应,并将变量的地址填入label

		}
		else {
			if(root->nodeKind==program_head_NodeKind)	root->child->label="main";
			typeCheck(root->child,procedure_name);  //主函数只用来加 procedure_name
			typeCheck(root->sibling,procedure_name);
		}


		if(flag==1){
			int n=strlen(procedure_name)-strlen(current_procedure_name)-1;
			procedure_name[n]='\0';
		}
		return 1;
	}
}


