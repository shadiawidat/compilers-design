#include <iostream>
using namespace std;
#include	"CodeGenerator.h"

static int Stack_Address = 5;
const int MAX = 100;

static int if_counter = 0;
static int if_else_counter = 0;
static int for_counter = 0;
static int while_counter = 0;
class Variable {

	/* Think! what does a Variable contain? */
	string identifier, type;
	int address, size;
	Variable* next;
public:

	Variable()
	{
		next = NULL;
	}

	Variable(string key, string type, int address, int size)
	{
		this->identifier = key;
		this->size = size;
		this->type = type;
		this->address = address;
		next = NULL;
	}
	friend class SymbolTable;

};

class SymbolTable {
	/* Think! what can you add to  symbol_table */

	Variable* head[MAX];
public:

	SymbolTable()
	{
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	// Function to find an identifier 
	int find(string id)
	{
		int index = hashf(id);
		Variable* start = head[index];

		if (start == NULL)
			return -1;

		while (start != NULL) {

			if (start->identifier == id) {
				return start->address;
			}

			start = start->next;
		}

		return -1; // not found 
	}

	// Function to insert an identifier 
	bool insert(string id, string type, int address, int size)
	{
		int index = hashf(id);
		Variable* p = new Variable(id, type, address, size);

		if (head[index] == NULL) {
			head[index] = p;
			return true;
		}

		else {
			Variable* start = head[index];
			while (start->next != NULL)
				start = start->next;
			start->next = p;
			return true;
		}

		return false;
	}

	int hashf(string id)
	{
		int asciiSum = 0;

		for (int i = 0; i < id.length(); i++) {
			asciiSum = asciiSum + id[i];
		}

		return (asciiSum % MAX);
	}

};
SymbolTable ST;


class TreeNode { //base class
public:
	/*you can add another son nodes */
	TreeNode* son1 = NULL;
	TreeNode* son2 = NULL;

	virtual ~TreeNode() {};
	TreeNode() {};
	/*recursive function to make Pcode*/
	virtual void  gencode(string c_type = "coder") {
		if (son1 != NULL) son1->gencode(c_type);
		if (son2 != NULL) son2->gencode(c_type);
	};

};
/*
* you have to add functions/implement of gencode()... of derived classes
*/
class Assign :public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("codel"); //return address 
		if (son2 != NULL) son2->gencode("coder"); // return value
		cout << "sto " << endl;
	}
};
class Id :public TreeNode {
public:
	string id_name;
	Id(string id_n) {
		id_name = id_n;
	}
	virtual void gencode(string c_type) {
		if (c_type == "codel") {
			cout << "ldc " << ST.find(id_name) << endl;
		}
		else if (c_type == "coder") {
			cout << "ldc " << ST.find(id_name) << endl << "ind" << endl;
		}
	}
};
class Num :public TreeNode {
	int value;
public:
	int getValue() { return value; }
	Num(int number) { value = number; }
	virtual void gencode(string c_type) {
		cout << "ldc " << getValue() << endl;
	}
};
class Float :public TreeNode {
	float value;
public:
	float getValue() { return value; }
	Float(float number) { value = number; }
	virtual void gencode(string c_type) {
		cout << "ldc " << getValue() << endl;
	}
};
class Double :public TreeNode {
	double value;
public:
	double getValue() { return value; }
	Double(double number) { value = number; }
	virtual void gencode(string c_type) {
		printf("ldc %0.2f\n", value);
	}
};
class Add : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "add" << endl;
	}
};
class Sub : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "sub" << endl;
	}
};
class Mull : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "mul" << endl;
	}
};
class Div : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "div" << endl;
	}
};
class Not : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		else if (son2 != NULL) son2->gencode("coder");
		cout << "not" << endl;
	}
};
class Negative : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		else if (son2 != NULL) son2->gencode("coder");
		cout << "neg" << endl;
	}
};
class Or : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "or" << endl;

	}
};
class And : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "and" << endl;
	}
};
class Equal : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "equ" << endl;
	}
};
class NotEqual : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "neq" << endl;
	}
};
class Greater : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "grt" << endl;
	}
};
class GreaterOrEqual : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "geq" << endl;
	}
};
class Lesser : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "les" << endl;
	}
};
class LesserOrEqual : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "leq" << endl;
	}
};
class Increment :public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL)
		{
			son1->gencode("coder");
			son1->gencode("codel");
			son1->gencode("coder");
			cout << "inc 1" << endl << "sto" << endl;
		}
		else if (son2 != NULL)
		{
			son2->gencode("codel");
			son2->gencode("coder");
			cout << "inc 1" << endl << "sto" << endl;
			son2->gencode("coder");

		}
	}
};
class Decrement :public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL)
		{
			son1->gencode("coder");
			son1->gencode("codel");
			son1->gencode("coder");
			cout << "inc -1" << endl << "sto" << endl;
		}
		else if (son2 != NULL)
		{
			son2->gencode("codel");
			son2->gencode("coder");
			cout << "inc -1" << endl << "sto" << endl;
			son2->gencode("coder");

		}
	}
};



class AssignPlus : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("codel");
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "add" << endl << "sto" << endl;
	}
};
class AssignMinus : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("codel");
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "sub" << endl << "sto" << endl;
	}
};
class AssignStar : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("codel");
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "mul" << endl << "sto" << endl;
	}
};
class AssignDiv : public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("codel");
		if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "div" << endl << "sto" << endl;
	}
};


class Print :public TreeNode
{
public:
	virtual void gencode(string c_type) {
		//if (son1 != NULL) son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		cout << "print" << endl;
		;
	}
};
class If :public TreeNode
{
	int mynumber;
public:
	If(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");
		printf("fjp if_end%d\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("if_end%d:\n", mynumber);
		;
	}
};
class If_else :public TreeNode
{
	int mynumber;
public:
	TreeNode* son3 = NULL;
	If_else(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");

		printf("fjp ifelse_else%d\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("ujp ifelse_end%d\n", mynumber);

		printf("ifelse_else%d:\n", mynumber);
		if (son3 != NULL) son3->gencode("coder");
		printf("ifelse_end%d:\n", mynumber);
		;
	}

};
class For :public TreeNode
{
	int mynumber;
public:
	TreeNode* son3 = NULL;
	TreeNode* son4 = NULL;
	For(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		if (son1 != NULL) son1->gencode("coder");

		printf("for_loop%d:\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("fjp for_end_loop%d\n", mynumber);

		if (son3 != NULL) son3->gencode("coder");
		if (son4 != NULL)son4->gencode("coder");
		printf("ujp for_loop%d\n", mynumber);
		printf("for_end_loop%d:\n", mynumber);

	}
};

class While :public TreeNode
{
	int mynumber;
public:
	While(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		printf("while_loop%d:\n", mynumber);
		if (son1 != NULL) son1->gencode("coder");
		printf("fjp while_end_loop%d\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("ujp while_loop%d\n", mynumber);
		printf("while_end_loop%d:\n", mynumber);

	}
};

class DoWhile :public TreeNode
{
	int mynumber;
public:
	DoWhile(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		printf("Do_While_%d:\n", mynumber);
		if (son1 != NULL) son2->gencode("coder");
		if (son2 != NULL) son1->gencode("coder");
		printf("fjp Do_while_end%d\n", mynumber);
		printf("ujp Do_while_%d\n", mynumber);
		printf("Do_while_end_%d:\n", mynumber);

	}
};
TreeNode* obj_tree(treenode* root);

/*
*	Input: Tree of objects
*	Output: prints the Pcode on the console
*/
int code_recur(treenode* root) {
	TreeNode* tree_root = obj_tree(root);
	tree_root->gencode();
	return SUCCESS;

}

/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: Tree of objects
*/
TreeNode* obj_tree(treenode* root)
{
	if_node* ifn;
	for_node* forn;
	leafnode* leaf, * Id_leaf;
	TreeNode* dec;
	if (!root)
	{
		return NULL;
	}

	switch (root->hdr.which) {
	case LEAF_T:
		leaf = (leafnode*)root;
		switch (leaf->hdr.type) {
		case TN_LABEL:
			/* Maybe you will use it later */
			break;

		case TN_IDENT:
			/* variable case */
			/*
			*	In order to get the identifier name you have to use:
			*	leaf->data.sval->str
			*/
		{
			TreeNode* ident = new Id(leaf->data.sval->str);
			return ident;
		}


		case TN_COMMENT:
			/* Maybe you will use it later */
			break;

		case TN_ELLIPSIS:
			/* Maybe you will use it later */
			break;

		case TN_STRING:
			/* Maybe you will use it later */
			break;

		case TN_TYPE:
			/* Maybe you will use it later */
			break;

		case TN_INT:
			/* Constant case */
			/*
			*	In order to get the int value you have to use:
			*	leaf->data.ival
			*/
		{
			TreeNode* const_number = new Num(leaf->data.ival);
			return const_number;
		}

		case TN_REAL:
			/* Constant case */
			/*
			*	In order to get the real value you have to use:
			*	leaf->data.dval
			*/
			TreeNode* const_number = new Double(leaf->data.dval);
			return const_number;
			break;
		}
		break;

	case IF_T:
		ifn = (if_node*)root;
		switch (ifn->hdr.type) {

		case TN_IF:
		{	if (ifn->else_n == NULL) {
			/* if case (without else)*/

			TreeNode* IF_node = new If(if_counter++);
			IF_node->son1 = obj_tree(ifn->cond);
			IF_node->son2 = obj_tree(ifn->then_n);

			return IF_node;
		}
		else {
			/* if - else case*/
			{If_else* IF_ELSE_node = new If_else(if_else_counter++);
			IF_ELSE_node->son1 = obj_tree(ifn->cond);
			IF_ELSE_node->son2 = obj_tree(ifn->then_n);
			IF_ELSE_node->son3 = obj_tree(ifn->else_n);

			return IF_ELSE_node; }

		}
		break;

		case TN_COND_EXPR:
		{If_else* IF_ELSE_node = new If_else(if_else_counter++);
		IF_ELSE_node->son1 = obj_tree(ifn->cond);
		IF_ELSE_node->son2 = obj_tree(ifn->then_n);
		IF_ELSE_node->son3 = obj_tree(ifn->else_n);

		return IF_ELSE_node; }
		break;

		default:
			/* Maybe you will use it later */

			obj_tree(ifn->cond);
			obj_tree(ifn->then_n);
			obj_tree(ifn->else_n);
		}
		}
		break;

	case FOR_T:
		forn = (for_node*)root;
		switch (forn->hdr.type) {

		case TN_FUNC_DEF:
			/* Function definition */
			/* e.g. int main(...) { ... } */
			/* Look at the output AST structure! */
			obj_tree(forn->init);
			obj_tree(forn->test);
			obj_tree(forn->incr);
			obj_tree(forn->stemnt);
			break;

		case TN_FOR:
			/* For case*/
				/* e.g. for(i=0;i<5;i++) { ... } */
				/* Look at the output AST structure! */
		{
			For* FOR_node = new For(for_counter++);
			FOR_node->son1 = obj_tree(forn->init);
			FOR_node->son2 = obj_tree(forn->test);
			FOR_node->son3 = obj_tree(forn->stemnt);
			FOR_node->son4 = obj_tree(forn->incr);
			return FOR_node;
		}
		break;

		default:
			/* Maybe you will use it later */
			obj_tree(forn->init);
			obj_tree(forn->test);
			obj_tree(forn->stemnt);
			obj_tree(forn->incr);
		}
		break;

	case NODE_T:
		switch (root->hdr.type) {
		case TN_PARBLOCK:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_PARBLOCK_EMPTY:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_TRANS_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_FUNC_DECL:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_FUNC_CALL:
			/* Function call */
			if (strcmp(((leafnode*)root->lnode)->data.sval->str, "printf") == 0) {
				/* printf case */
				/* The expression that you need to print is located in */
				/* the currentNode->right->right sub tree */
				/* Look at the output AST structure! */
				TreeNode* toprint = new Print();
				toprint->son2 = obj_tree(root->rnode->rnode);

				return toprint;


			}
			else {
				/* other function calls - for HW3 */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			break;

		case TN_BLOCK: {
			/* Maybe you will use it later */
			TreeNode* block = new TreeNode();
			block->son1 = obj_tree(root->lnode);
			block->son2 = obj_tree(root->rnode);
			return block; }
					 break;

		case TN_ARRAY_DECL:
			/* array declaration - for HW2 */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_EXPR_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_NAME_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_ENUM_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_FIELD_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_PARAM_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_IDENT_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_TYPE_LIST: {
			/* Maybe you will use it later */
			TreeNode* typlist = new TreeNode();
			typlist->son1 = obj_tree(root->lnode);
			typlist->son2 = obj_tree(root->rnode);
			return typlist;
		}
						 break;
		case TN_COMP_DECL:
			/* struct component declaration - for HW2 */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_DECL: {
			/* structs declaration */
			TreeNode* Declerat = new TreeNode();
			leaf = (leafnode*)root->lnode->lnode;
			Id_leaf = (leafnode*)root->rnode;
			switch (leaf->hdr.tok)
			{
			case INT:
				ST.insert(Id_leaf->data.sval->str, "int", Stack_Address++, sizeof(int));
				break;
			case DOUBLE:
				ST.insert(Id_leaf->data.sval->str, "double", Stack_Address++, sizeof(double));
				break;
			case FLOAT:
				ST.insert(Id_leaf->data.sval->str, "float", Stack_Address++, sizeof(float));
				break;
			}
			return Declerat;
		}


		case TN_DECL_LIST: {
			/* Maybe you will use it later */
			TreeNode* DecList = new TreeNode();

			DecList->son1 = obj_tree(root->lnode);
			DecList->son2 = obj_tree(root->rnode);
			return DecList;
			break; }

		case TN_DECLS:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_STEMNT_LIST: {
			/* Maybe you will use it later */
			TreeNode* StemntList = new TreeNode();

			StemntList->son1 = obj_tree(root->lnode);
			StemntList->son2 = obj_tree(root->rnode);

			return StemntList; }
						   break;

		case TN_STEMNT: {
			/* Maybe you will use it later */
			TreeNode* Stemnt = new TreeNode();

			Stemnt->son1 = obj_tree(root->lnode);    //Node is Null
			Stemnt->son2 = obj_tree(root->rnode);
			return Stemnt; }
					  break;


		case TN_BIT_FIELD:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_PNTR:
			/* pointer - for HW2! */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_TYPE_NME:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_INIT_LIST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_INIT_BLK:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_OBJ_DEF:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_OBJ_REF:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_CAST:
			/* Maybe you will use it later */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_JUMP:
			if (root->hdr.tok == RETURN) {
				/* return jump - for HW2! */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			else if (root->hdr.tok == BREAK) {
				/* break jump - for HW2! */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			else if (root->hdr.tok == GOTO) {
				/* GOTO jump - for HW2! */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			break;

		case TN_SWITCH:
			/* Switch case - for HW2! */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_INDEX:
			/* call for array - for HW2! */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_DEREF:
			/* pointer derefrence - for HW2! */
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		case TN_SELECT:
			/* struct case - for HW2! */
			if (root->hdr.tok == ARROW) {
				/* Struct select case "->" */
				/* e.g. struct_variable->x; */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			else {
				/* Struct select case "." */
				/* e.g. struct_variable.x; */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
			}
			break;

		case TN_ASSIGN: {
			if (root->hdr.tok == EQ) {
				/* Regular assignment "=" */
				/* e.g. x = 5; */
				TreeNode* ass_obj = new Assign();
				ass_obj->son1 = obj_tree(root->lnode);
				ass_obj->son2 = obj_tree(root->rnode);
				return ass_obj;

			}
			else if (root->hdr.tok == PLUS_EQ) {
				/* Plus equal assignment "+=" */
				/* e.g. x += 5; */
				TreeNode* ass_p_obj = new AssignPlus();
				ass_p_obj->son1 = obj_tree(root->lnode);
				ass_p_obj->son2 = obj_tree(root->rnode);
				return ass_p_obj;
			}
			else if (root->hdr.tok == MINUS_EQ) {
				/* Minus equal assignment "-=" */
				/* e.g. x -= 5; */
				TreeNode* ass_m_obj = new AssignMinus();
				ass_m_obj->son1 = obj_tree(root->lnode);
				ass_m_obj->son2 = obj_tree(root->rnode);
				return ass_m_obj;
			}
			else if (root->hdr.tok == STAR_EQ) {
				/* Multiply equal assignment "*=" */
				/* e.g. x *= 5; */
				TreeNode* ass_s_obj = new AssignStar();
				ass_s_obj->son1 = obj_tree(root->lnode);
				ass_s_obj->son2 = obj_tree(root->rnode);
				return ass_s_obj;
			}
			else if (root->hdr.tok == DIV_EQ) {
				/* Divide equal assignment "/=" */
				/* e.g. x /= 5; */
				TreeNode* ass_d_obj = new AssignDiv();
				ass_d_obj->son1 = obj_tree(root->lnode);
				ass_d_obj->son2 = obj_tree(root->rnode);
				return ass_d_obj;
			}}
					  break;

		case TN_EXPR:
			switch (root->hdr.tok) {
			case CASE:
				/* you should not get here */
				obj_tree(root->lnode);
				obj_tree(root->rnode);
				break;

			case INCR:
				/* Increment token "++" */
			{
				TreeNode* INC = new Increment();
				INC->son1 = obj_tree(root->lnode);
				INC->son2 = obj_tree(root->rnode);
				return INC;
			}
			break;

			case DECR:
				/* Decrement token "--" */
			{
				TreeNode* DEC = new Decrement();
				DEC->son1 = obj_tree(root->lnode);
				DEC->son2 = obj_tree(root->rnode);
				return DEC;
			}
			break;

			case PLUS: {
				/* Plus token "+" */
				TreeNode* plus = new Add();
				plus->son1 = obj_tree(root->lnode);
				plus->son2 = obj_tree(root->rnode);
				return plus;
				break; }

			case MINUS: {
				/* Minus token "-" */
				if (root->lnode) {
					TreeNode* minus = new Sub();
					minus->son1 = obj_tree(root->lnode);
					minus->son2 = obj_tree(root->rnode);
					return minus;
				}
				else {
					TreeNode* neg_N = new Negative();
					neg_N->son1 = obj_tree(root->lnode);
					neg_N->son2 = obj_tree(root->rnode);
					return neg_N;
				}
				break; }

			case DIV: {
				/* Divide token "/" */
				TreeNode* slash = new Div();
				slash->son1 = obj_tree(root->lnode);
				slash->son2 = obj_tree(root->rnode);
				return slash;
				break; }

			case STAR: {
				/* multiply token "*" */
				TreeNode* star = new Mull();
				star->son1 = obj_tree(root->lnode);
				star->son2 = obj_tree(root->rnode);
				return star;
				break; }

			case AND: {
				/* And token "&&" */
				TreeNode* and_N = new And();
				and_N->son1 = obj_tree(root->lnode);
				and_N->son2 = obj_tree(root->rnode);
				return and_N;
				break; }

			case OR: {
				/* Or token "||" */
				TreeNode* or_N = new Or();
				or_N->son1 = obj_tree(root->lnode);
				or_N->son2 = obj_tree(root->rnode);
				return or_N;
				break; }

			case NOT: {
				/* Not token "!" */
				TreeNode* not_N = new Not();
				not_N->son1 = obj_tree(root->lnode);
				not_N->son2 = obj_tree(root->rnode);
				return not_N;
				break; }

			case GRTR: {
				/* Greater token ">" */
				TreeNode* grt = new Greater();
				grt->son1 = obj_tree(root->lnode);
				grt->son2 = obj_tree(root->rnode);
				return grt;
				break; }

			case LESS: {
				/* Less token "<" */
				TreeNode* les = new Lesser();
				les->son1 = obj_tree(root->lnode);
				les->son2 = obj_tree(root->rnode);
				return les;
				break; }

			case EQUAL: {
				/* Equal token "==" */
				TreeNode* equ = new Equal();
				equ->son1 = obj_tree(root->lnode);
				equ->son2 = obj_tree(root->rnode);
				return equ;
				break; }

			case NOT_EQ: {
				/* Not equal token "!=" */
				TreeNode* neq = new NotEqual();
				neq->son1 = obj_tree(root->lnode);
				neq->son2 = obj_tree(root->rnode);
				return neq;
				break; }

			case LESS_EQ: {
				/* Less or equal token "<=" */
				TreeNode* leq = new LesserOrEqual();
				leq->son1 = obj_tree(root->lnode);
				leq->son2 = obj_tree(root->rnode);
				return leq;
				break; }

			case GRTR_EQ: {
				/* Greater or equal token ">=" */
				TreeNode* geq = new GreaterOrEqual();
				geq->son1 = obj_tree(root->lnode);
				geq->son2 = obj_tree(root->rnode);
				return geq;
				break; }

			default:
				obj_tree(root->lnode);
				obj_tree(root->rnode);
				break;
			}
			break;

		case TN_WHILE:
			/* While case */
		{//sdfsdfsd
			TreeNode* While_node = new While(while_counter++);
			While_node->son1 = obj_tree(root->lnode);
			While_node->son2 = obj_tree(root->rnode);
			return While_node;
		}
		break;

		case TN_DOWHILE: {
			/* Do-While case */
			TreeNode* doWhile_node = new DoWhile(while_counter++);
			doWhile_node->son1 = obj_tree(root->lnode);
			doWhile_node->son2 = obj_tree(root->rnode);
			return doWhile_node;
		}

		case TN_LABEL:
			obj_tree(root->lnode);
			obj_tree(root->rnode);
			break;

		default:
			obj_tree(root->lnode);
			obj_tree(root->rnode);
		}
		break;

	case NONE_T:
		printf("Error: Unknown node type!\n");
		exit(FAILURE);
	}


}


/*
*	This function prints all the variables on your symbol table with their data
*	Input: treenode (AST)
*	Output: prints the Symbol Table on the console
*/
void print_symbol_table(treenode* root) {

	/*printf("---------------------------------------\n");
	printf("showing the symbol table:\n");
	for (int i = 5; i <= stack_address; i++) {
		cout << st.head[i]->identifier << "||";
		cout << st.head[i]->size << "||";
		cout << st.head[i]->type << "||";
		cout << st.head[i]->address << endl;
	}*/
}