#include <iostream>
#include <iterator>
#include <map>
using namespace std;
#include	"CodeGenerator.h"

static int Stack_Address=5;
const int MAX = 100;
static bool break_flag = 0;
static int break_counter = 0;
static int breaks_printed = 0;
static int if_counter = 0;
static int if_else_counter = 0;
static int for_counter = 0;
static int while_counter = 0;
static int switch_counter = 0;
static int switch_case_counter = 0;
static int global_number_of_cases = 0;
static int switch_flag = 0;
static int current_switch = 0;
static string array_adress;
static int in_line_dim = 0;
static int rec_counter = 0;
static int struct_flag = 0;
static int leaf_type;
static int pointer_flag = 0;
static string curr_struct_id;
static int comp_decl = 0;
static int struct_inside_struct = 0;
static string struct_inside_struct_str;
static int isOBJ = 0;
static string isOBJ_str;
static int selector_flag = 0;
static string selector_source;


class Variable {

	/* Think! what does a Variable contain? */
	string identifier, type , structName; 
    int address,size; 
    Variable* next; 
	int* dimentions = NULL;
public:

		Variable() 
		{ 
			next = NULL; 
		} 
	
		Variable(string key,  string type, int address,int size) 
		{ 
			this->identifier = key; 
			this->size = size; 
			this->type = type; 
			this->address = address; 
			next = NULL; 
		} 
		Variable(string key, string type, int address, int size, int* dimentions)
		{
			this->identifier = key;
			this->size = size;
			this->type = type;
			this->address = address;
			this->dimentions = dimentions;
			next = NULL;
		}
		Variable(string key, string structName, string type, int address, int size, int* dimentions)
		{
			this->structName = structName;
			this->identifier = key;
			this->size = size;
			this->type = type;
			this->address = address;
			this->dimentions = dimentions;
			next = NULL;

		}
		Variable(string key, string structName, string type, int address, int size)
		{
			this->structName = structName;
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
	int get_dim(string id,int ArrIndex)
	{
		int index = hashf(id);
		Variable* start = head[index];

		if (start == NULL)
			return -1;

		while (start != NULL) {

			if (start->identifier == id) {
				return start->dimentions[ArrIndex];
			}

			start = start->next;
		}

		return -1; // not found 
	}
	string get_struct_name(string id)
	{
		int index = hashf(id);
		Variable* start = head[index];

		if (start == NULL)
			return NULL;

		while (start != NULL) {
			if (start->identifier == id) {
				return start->structName;
			}

			start = start->next;
		}

		return NULL; // not found 
	}
	
	// Function to insert an identifier 
	bool insert(string id,  string type, int address,int size)
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
	// function to insert an array
	bool insert(string id, string type, int address, int size, int* dimentions)
	{
		int index = hashf(id);
		Variable* p = new Variable(id, type, address, size, dimentions);

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
	bool insertStruct(string id, string structName, string type, int address, int size)
	{
		int index = hashf(id);
		Variable* p = new Variable(id, structName, type, address, size);

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
	bool insertStruct(string id, string structName, string type, int address, int size, int* dimentions)
	{
		int index = hashf(id);
		Variable* p = new Variable(id, structName, type, address, size, dimentions);

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
SymbolTable ST ;


class TreeNode{ //base class
public:
	/*you can add another son nodes */
    TreeNode *son1=NULL;
    TreeNode *son2=NULL;
	
    virtual ~TreeNode(){};
    TreeNode(){};
	/*recursive function to make Pcode*/
	virtual void  gencode(string c_type="coder"){  
       if(son1 != NULL) son1->gencode(c_type);
       if(son2 != NULL) son2->gencode(c_type);
       };

};
/*
* you have to add functions/implement of gencode()... of derived classes
*/
class Assign:public TreeNode{ 
public:
virtual void gencode(string c_type){
       if(son1 != NULL) son1->gencode("codel"); //return address 
       if(son2 != NULL) son2->gencode("coder"); // return value
	   cout<< "sto " << endl;
}
};
class Id:public TreeNode{
public:
	string id_name;
	Id(string id_n){
		id_name=id_n;
	}
	virtual void gencode(string c_type){
		if (c_type =="codel"){
			array_adress = id_name;
			cout<< "ldc "<< ST.find(id_name) <<endl;
		}
		else if (c_type == "coder") {
			cout << "ldc " << ST.find(id_name) << endl << "ind" << endl;
			
		}
	} 
};
class Num:public TreeNode{
	int value;
public:
	int getValue(){return value;}
	Num(int number){value=number;}
	virtual void gencode(string c_type){
		cout<< "ldc "<<getValue()<<endl;
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
		printf("ldc %0.2f\n",value);
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
			cout << "dec 1" << endl << "sto" << endl;
		}
		else if (son2 != NULL)
		{
			son2->gencode("codel");
			son2->gencode("coder");
			cout << "dec 1" << endl << "sto" << endl;
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
		cout << "add" << endl << "sto" << endl ;
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
	If_else (int number) { mynumber = number; }
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
	int breaks_before;
	int mynumber;
public:
	TreeNode* son3 = NULL;
	TreeNode* son4 = NULL;
	For(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		breaks_before = break_counter;
		if (son1 != NULL) son1->gencode("coder");

		printf("for_loop%d:\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("fjp for_end_loop%d\n", mynumber);

		if (son3 != NULL) son3->gencode("coder");
		if (son4 != NULL)son4->gencode("coder");
		printf("ujp for_loop%d\n", mynumber);
		printf("for_end_loop%d:\n", mynumber);
		for (int i = break_counter - breaks_printed-1; i >=breaks_before; i--)
		{
			printf("break_%d:\n", i);
		}
		breaks_printed += break_counter - breaks_printed - breaks_before;
	}
};

class While :public TreeNode
{	
	int breaks_before;
	int mynumber;
public:
	While(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		breaks_before = break_counter;
		printf("while_loop%d:\n", mynumber);
		if (son1 != NULL) son1->gencode("coder");
		printf("fjp while_end_loop%d\n", mynumber);
		if (son2 != NULL) son2->gencode("coder");
		printf("ujp while_loop%d\n", mynumber);
		printf("while_end_loop%d:\n", mynumber);
		for (int i = break_counter - breaks_printed-1; i >=breaks_before; i--)
		{
			printf("break_%d:\n", i);
		}
		breaks_printed += break_counter - breaks_printed - breaks_before;
	}
};

class DoWhile :public TreeNode
{
	int breaks_before;
	int mynumber;
public:
	DoWhile(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		breaks_before = break_counter;
		printf("Do_While_%d:\n", mynumber);
		if (son1 != NULL) son2->gencode("coder");
		if (son2 != NULL) son1->gencode("coder");
		printf("fjp Do_while_end_%d\n", mynumber);
		printf("ujp Do_while_%d\n", mynumber);
		printf("Do_while_end_%d:\n", mynumber);
		for (int i = break_counter - breaks_printed-1; i >=breaks_before; i--)
		{
			printf("break_%d:\n", i);
		}
		breaks_printed += break_counter - breaks_printed - breaks_before;
	}
};
class Break :public TreeNode
{
	
public:
	Break() {  }
	virtual void gencode(string c_type) {
		if (switch_flag)
			return;
		if (son1 != NULL) son2->gencode("coder");
		if (son2 != NULL) son1->gencode("coder");
		printf("ujp Break_%d\n", break_counter++);

	}
};
class Switch :public TreeNode
{
	int mynumber;
public:
	int number_of_cases;
	Switch(int number) { mynumber = number; }
	virtual void gencode(string c_type) {
		current_switch = mynumber;
		switch_flag = 1;
		global_number_of_cases = number_of_cases;
		if (son1 != NULL)son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		switch_flag = 0;
		printf("switch_end%d:\n", mynumber);
	}


};
class Label :public TreeNode
{	
	
public:
	Lable() {}
	virtual void gencode(string c_type)
	{
		if (son1 != NULL)son1->gencode("coder");
		if (son2 != NULL) son2->gencode("coder");
		if(switch_flag)
		printf("ujp switch_end%d\n", current_switch);
	}
};
class Case :public TreeNode
{
	int mynumber;
	
public:
	int myswitch;
	Case(int number, int switchnum) { mynumber = number; myswitch = switchnum; }
	virtual void gencode(string c_type) {
		if (mynumber < global_number_of_cases - 1)
		{
			printf("switch%d_case%d:\n", myswitch, mynumber);
			printf("dpl\n");
			if (son2 != NULL)son2->gencode("coder");
			printf("equ\n");
			printf("fjp switch%d_case%d\n", myswitch, mynumber + 1);

		}
		else
		{	
			printf("switch%d_case%d:\n", myswitch, mynumber);
			printf("dpl\n");
			if (son2 != NULL)son2->gencode("coder");
			printf("equ\n");
			printf("fjp switch_end%d\n", myswitch);
		}

	}

};
class PointerDeref :public TreeNode {
public:
	virtual void gencode(string c_type) {
		if (son1 != NULL)son1->gencode(c_type);
		if (son2 != NULL)son2->gencode(c_type);
		printf("ind\n");
	}

};
class Structs :public TreeNode {
public:
	int struct_address = 0;
	int size;
	string id;
	SymbolTable* structTab;
	Structs(string id) {
		structTab = new SymbolTable();
		this->id = id;
	}
	int get_size() {
		return size;
	}

};
map<string, Structs*>struct_recepies;
map < string, Structs*>::iterator global;

class DotSelector : public TreeNode {
public:
	string Id_name;
	string code;
	string source;
	DotSelector(string id, string code) {
		this->Id_name = id;
		this->code = code;
	}
	virtual void gencode(string c_type) {
		Id* id_leaf;
		string struct_name;
		DotSelector* temp;
		map < string, Structs*>::iterator itr;
		if (son1 != NULL)son1->gencode("codel");
		if (code == "code1") {
			struct_name = ST.get_struct_name(Id_name);
			itr = struct_recepies.begin();
			for (itr; itr != struct_recepies.end(); ++itr) {
				if (itr->first == struct_name) {
					break;
				}
			}
			this->source = struct_name;
		}
		if (code == "code2") {
			TreeNode* pson1 = son1;
			while (dynamic_cast<PointerDeref*>(pson1)) {
				pson1 = pson1->son2;
			}
			while (!dynamic_cast<DotSelector*>(pson1)) {			/*in case its array index*/
				pson1 = pson1->son1;
			}
			temp = (DotSelector*)pson1;
			this->source = temp->source;
			itr = struct_recepies.begin();
			for (itr; itr != struct_recepies.end(); ++itr) {
				if (itr->first == source) {
					break;
				}
			}
			struct_name = itr->second->structTab->get_struct_name(Id_name);
			this->source = struct_name;
			itr = struct_recepies.begin();
			for (itr; itr != struct_recepies.end(); ++itr) {
				if (itr->first == struct_name) {
					break;
				}
			}

		}
		id_leaf = (Id*)son2;
		printf("inc %d\n", itr->second->structTab->find(id_leaf->id_name));
		if (c_type == "coder") { printf("ind\n");}
	}
};
class ArrayIndex :public TreeNode {
	
public:
	int type;
	int inLine;
	string dimadress;
	virtual void gencode(string c_type) {
		map < string, Structs*>::iterator itr;
		Id* id_leaf;
		int temp_line;
		int temp_counter;
		
		if (type == TN_DEREF)
		{
			if (son1 != NULL)son1->gencode("codel");
			if (son2 != NULL)son2->gencode("coder");
			cout << "ixa 1" << endl;
			if (c_type == "coder") {cout << "ind" << endl;}
			return;
		}
		if (c_type == "codel") {
			if (dynamic_cast<DotSelector*>(son1))
			{

				string tempo;
				selector_flag = 1;
				rec_counter++;
				if (son1 != NULL)son1->gencode("codel");
				TreeNode* point = son1;
				while (dynamic_cast<PointerDeref*>(point)) {

					point = point->son2;
				}
				id_leaf = ((Id*)point->son2);
				if (son2 != NULL)son2->gencode("coder");
				tempo = ((DotSelector*)son1)->source;
				global = struct_recepies.begin();
				for (global; global != struct_recepies.end(); ++global) {
					if (global->first == tempo) {
						break;
					}
				}
				dimadress = id_leaf->id_name;
				array_adress = id_leaf->id_name;
				inLine = in_line_dim;
				in_line_dim++;
				printf("ixa %d\n", global->second->structTab->get_dim(dimadress, inLine));
				if (rec_counter == in_line_dim) {
					in_line_dim = 0;
					rec_counter = 0;
				}
				selector_flag = 0;
			}
			else {

				rec_counter++;
				if (son1 != NULL)son1->gencode("codel");
				dimadress = array_adress;
				inLine = in_line_dim;
				in_line_dim++;
				if (son2 != NULL)son2->gencode("coder");
				printf("ixa %d\n", ST.get_dim(dimadress, inLine));
				if (rec_counter == in_line_dim) {
					in_line_dim = 0;
					rec_counter = 0;
				}
			}
		}
		else if (c_type == "coder") {
			if (dynamic_cast<DotSelector*>(son1))
			{
				int gg;
				string tempo;
				selector_flag = 1;
				if (rec_counter != 0) {
					dimadress = array_adress;
					temp_line = in_line_dim;
					temp_counter = rec_counter;
					in_line_dim = 0;
					rec_counter = 1;
					gg = 1;
				}
				if (son1 != NULL)son1->gencode("codel");
				TreeNode* point = son1;
				while (dynamic_cast<PointerDeref*>(point)) {
					point = point->son2;
				}
				id_leaf = ((Id*)point->son2);
				if (son2 != NULL)son2->gencode("coder");
				tempo = ((DotSelector*)son1)->source;
				global = struct_recepies.begin();
				for (global; global != struct_recepies.end(); ++global) {
					if (global->first == tempo) {
						break;
					}
				}
				dimadress = id_leaf->id_name;
				array_adress = id_leaf->id_name;
				if (gg) {
					in_line_dim = temp_line;
					rec_counter = temp_counter;
					gg = 0;
				}
				else {
					inLine = in_line_dim;
					in_line_dim++;
				}
				printf("ixa %d\n", global->second->structTab->get_dim(dimadress, inLine));
				if (rec_counter == in_line_dim) {
					in_line_dim = 0;
					rec_counter = 0;
				}
				selector_flag = 0;
			}
			else {
				if (rec_counter != 0) {
					dimadress = array_adress;
					temp_line = in_line_dim;
					temp_counter = rec_counter;
					in_line_dim = 0;
					rec_counter = 1;
					if (son1 != NULL)son1->gencode("codel");
					inLine = in_line_dim;
					in_line_dim++;
					if (son2 != NULL)son2->gencode("coder");
					in_line_dim = temp_line;
					rec_counter = temp_counter;
					printf("ixa %d\n", ST.get_dim(dimadress, inLine));
				}
				else {
					rec_counter++;
					if (son1 != NULL)son1->gencode("codel");
					dimadress = array_adress;
					inLine = in_line_dim;
					in_line_dim++;
					if (rec_counter == in_line_dim) {
						in_line_dim = 0;
						rec_counter = 0;
					}
					if (son2 != NULL)son2->gencode("coder");
					printf("ixa %d\n", ST.get_dim(dimadress, inLine));

				}
			}
			printf("ind\n");

		}
	}
};






TreeNode* obj_tree(treenode *root);

/*
*	Input: Tree of objects 
*	Output: prints the Pcode on the console
*/
int code_recur(treenode *root){
    TreeNode* tree_root= obj_tree(root);
    tree_root->gencode();
    return SUCCESS;

}

/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: Tree of objects 
*/
TreeNode* obj_tree(treenode *root)
{
	if_node  *ifn;
	for_node *forn;
	leafnode *leaf,*Id_leaf;
	TreeNode* dec;
    if (!root)
	{
        return NULL;
	}
    
  switch (root->hdr.which){
		case LEAF_T:
			leaf = (leafnode *) root;
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
			ifn = (if_node *) root;
			switch (ifn->hdr.type) {

			case TN_IF:
			{	if (ifn->else_n == NULL) {
				/* if case (without else)*/
				
				TreeNode* IF_node = new If(if_counter++);
				IF_node->son1=obj_tree(ifn->cond);
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
			forn = (for_node *) root;
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

			case TN_ARRAY_DECL: {
				/* array declaration - for HW2 */
				TreeNode* arr_decl = new TreeNode();
				treenode* temp_root = root;
				map < string, Structs*>::iterator itr;
				map < string, Structs*>::iterator typeItr;
				int dimen_num = 0;
				int j = 0;
				int sum = 1;
				do {

					dimen_num++;
					temp_root = temp_root->lnode;
					Id_leaf = (leafnode*)temp_root;

				} while (temp_root->hdr.type != TN_IDENT);
				temp_root = root;
				int* Arr = new int[dimen_num];
				if (comp_decl) {						/*in case we have an array in a struct to declare in our struct*/
					itr = struct_recepies.begin();
					for (itr; itr != struct_recepies.end(); ++itr) {
						if (itr->first == curr_struct_id) {
							break;
						}
					}
					if (struct_inside_struct) {
						typeItr = struct_recepies.begin();
						for (typeItr; typeItr != struct_recepies.end(); ++typeItr) {
							if (typeItr->first == struct_inside_struct_str) {
								break;
							}
						}
						if (!pointer_flag) { sum *= typeItr->second->get_size(); }
					}
				}
				else if (isOBJ) {
					itr = struct_recepies.begin();
					for (itr; itr != struct_recepies.end(); ++itr) {
						if (itr->first == isOBJ_str) {
							break;
						}
					}
					if (!pointer_flag) { sum = itr->second->size; }
				}
				do {
					j++;
					if (dimen_num >= j) {
						Arr[dimen_num - j] = sum;
					}
					Id_leaf = (leafnode*)temp_root->rnode;
					sum *= Id_leaf->data.ival;
					temp_root = temp_root->lnode;
				} while (temp_root->hdr.type != TN_IDENT);
				if (struct_inside_struct) {
					if (!pointer_flag) {			/*array of struct inside struct*/
						Id_leaf = (leafnode*)temp_root;
						
						itr->second->structTab->insertStruct(Id_leaf->data.sval->str, struct_inside_struct_str, "array", itr->second->struct_address, sum, Arr);
						itr->second->struct_address += sum;
						struct_inside_struct = 0;
						comp_decl = 0;
						return arr_decl;
					}
					else {							/*array of pointers to struct inside struct*/
						Id_leaf = (leafnode*)temp_root;
						itr->second->structTab->insertStruct(Id_leaf->data.sval->str, struct_inside_struct_str, "pointer array ", itr->second->struct_address, sum, Arr);
						itr->second->struct_address += sum;
						struct_inside_struct = 0;
						pointer_flag = 0;
						comp_decl = 0;
						return arr_decl;
					}
				}
				if (isOBJ) {
					Id_leaf = (leafnode*)temp_root;
					ST.insertStruct(Id_leaf->data.sval->str, isOBJ_str, "array", Stack_Address,  sum, Arr);
					Stack_Address += sum;
					isOBJ = 0;
					return arr_decl;
				}
				if (!comp_decl) {
					if (!pointer_flag) {
						Id_leaf = (leafnode*)temp_root;
						ST.insert(Id_leaf->data.sval->str, "array", Stack_Address, sizeof(int) * sum, Arr);
						Stack_Address += sum;
					}
					else {
						pointer_flag = 0;
						Id_leaf = (leafnode*)temp_root;
						ST.insert(Id_leaf->data.sval->str, "array pointer", Stack_Address, 1 * sum, Arr);
						Stack_Address += sum;
					}
				}
				else {

					if (!pointer_flag) {
						Id_leaf = (leafnode*)temp_root;
						itr->second->structTab->insertStruct(Id_leaf->data.sval->str, curr_struct_id, "array", itr->second->struct_address, sum, Arr);
						itr->second->struct_address += sum;
						itr->second->size += sum;
					}
					else {
						pointer_flag = 0;
						Id_leaf = (leafnode*)temp_root;
						itr->second->structTab->insertStruct(Id_leaf->data.sval->str, itr->first, "pointer", itr->second->struct_address, sum, Arr);
						itr->second->struct_address += sum;
						itr->second->size += sum;
					}
				}
				comp_decl = 0;
				return arr_decl; }
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

			case TN_FIELD_LIST: {
				/* Maybe you will use it later */
				TreeNode* field = new TreeNode();
				field->son1 = obj_tree(root->lnode);
				field->son2 = obj_tree(root->rnode);
				return field; }
			
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

			case TN_TYPE_LIST:{
				/* Maybe you will use it later */
				TreeNode* typlist = new TreeNode();
				typlist->son1 = obj_tree(root->lnode);
				typlist->son2 = obj_tree(root->rnode);
				return typlist;
			}
				break;
			case TN_COMP_DECL: {
				/* struct component declaration - for HW2 */
				comp_decl = 1;
				int sizeOf = 1;
				struct_inside_struct = 0;									/********************/
				TreeNode* compDecl = new TreeNode();
				map < string, Structs*>::iterator itr;
				map < string, Structs*>::iterator typeItr;
				Id_leaf = (leafnode*)root->rnode;
				treenode* temp_root_pt = root;

				while ((temp_root_pt->rnode->hdr.type == TN_DECL)) {		/*pointer flag on*/
					pointer_flag = 1;
					temp_root_pt = temp_root_pt->rnode;
				}
				if ((temp_root_pt->rnode->hdr.type == TN_ARRAY_DECL)&&(root->lnode->lnode->hdr.type != TN_OBJ_REF)){	/* normal array (not of struct)*/
					compDecl->son2 = obj_tree(temp_root_pt->rnode);
					return compDecl;
				}
				Id_leaf = (leafnode*)temp_root_pt->rnode;
				itr = struct_recepies.begin();
				for (itr; itr != struct_recepies.end(); ++itr) {
					if (itr->first == curr_struct_id) {
						if (root->lnode->lnode->hdr.type == TN_OBJ_REF)
						{
							leaf = (leafnode*)root->lnode->lnode->lnode;
							struct_inside_struct = 1;
							if (temp_root_pt->rnode->hdr.type == TN_ARRAY_DECL) {			/* array of struct case inside struct*/
								struct_inside_struct_str = leaf->data.sval->str;
								compDecl->son2 = obj_tree(temp_root_pt->rnode);
								struct_inside_struct = 0;
								return compDecl;
							}
							typeItr = struct_recepies.begin();
							for (typeItr; typeItr != struct_recepies.end(); ++typeItr) {
								if (typeItr->first == leaf->data.sval->str) {
									break;
								}
							}
							if (!pointer_flag) {											/*normal struct inside struct case*/
								sizeOf = typeItr->second->get_size();
								itr->second->structTab->insertStruct(Id_leaf->data.sval->str, leaf->data.sval->str, leaf->data.sval->str, itr->second->struct_address, sizeOf);
								itr->second->struct_address += sizeOf;
								itr->second->size += sizeOf;
							}
							else {															/*pointer to struct inside struct case*/
								itr->second->structTab->insertStruct(Id_leaf->data.sval->str, leaf->data.sval->str ,"pointer" , itr->second->struct_address, sizeOf);
								itr->second->struct_address += sizeOf;
								itr->second->size += sizeOf;
							}
						}
						else if (!pointer_flag) {
							leaf = (leafnode*)root->lnode->lnode;
							switch (leaf->hdr.tok)
							{
							case INT:
								itr->second->structTab->insertStruct(Id_leaf->data.sval->str, itr->first, "int", itr->second->struct_address++, sizeOf);
								itr->second->size+= sizeOf;
								break;
							case DOUBLE:
								itr->second->structTab->insertStruct(Id_leaf->data.sval->str, itr->first, "double", itr->second->struct_address++, sizeOf);
								itr->second->size += sizeOf;
								break;
							case FLOAT:
								itr->second->structTab->insertStruct(Id_leaf->data.sval->str, itr->first, "float", itr->second->struct_address++, sizeOf);
								itr->second->size += sizeOf;
								break;
							}
						}
						else {
							pointer_flag = 0;
							if (root->lnode->lnode->hdr.type == TN_OBJ_REF)
							{
								leaf = (leafnode*)root->lnode->lnode->lnode;
							}
							else {
								leaf = (leafnode*)root->lnode->lnode;
							}
							itr->second->structTab->insertStruct(Id_leaf->data.sval->str, itr->first, "pointer", itr->second->struct_address++, sizeOf);
							itr->second->size++;
							break;
						}
					}
				}
				comp_decl = 0;
				struct_inside_struct = 0;
				return compDecl;
				break;
			}
			case TN_DECL: {
				/* structs declaration */
				TreeNode* Declerat = new TreeNode();
				map < string, Structs*>::iterator itr;
				treenode* temp_root = root->rnode;
				treenode* temp_root_pt = root;
				if (root->rnode == NULL) {
					Declerat->son1 = obj_tree(root->lnode->lnode); 
					return Declerat;
				}
				while ((temp_root_pt->rnode->hdr.type == TN_DECL)) {	/* in case its a pointer use flag*/
					pointer_flag = 1;
					temp_root_pt = temp_root_pt->rnode;
				}
				if (root->lnode->lnode->hdr.type == TN_OBJ_REF) {
					if (temp_root_pt->rnode->hdr.type != TN_ARRAY_DECL) {
						leaf = (leafnode*)root->lnode->lnode->lnode;
						itr = struct_recepies.begin();
						for (itr; itr != struct_recepies.end(); ++itr) {
							if (itr->first == leaf->data.sval->str) {break;}
						}
						Id_leaf = (leafnode*)temp_root_pt->rnode;
						if (pointer_flag == 0) {
							ST.insertStruct(Id_leaf->data.sval->str, itr->first, itr->first, Stack_Address, itr->second->size);
							Stack_Address += itr->second->size;
							return Declerat;
						}
						else {
							ST.insertStruct(Id_leaf->data.sval->str, itr->first, itr->first, Stack_Address++,1);
							return Declerat;

						}
					}
					else {
						isOBJ = 1;
						leaf = (leafnode*)root->lnode->lnode->lnode;
						isOBJ_str = leaf->data.sval->str;
						Declerat->son2 = obj_tree(temp_root_pt->rnode);
						isOBJ = 0;
						return Declerat;
					}
				}
				if (temp_root_pt->rnode->hdr.type != TN_ARRAY_DECL) {	
					if (pointer_flag == 0) {	
						leaf = (leafnode*)root->lnode->lnode;			/* the case of normal variable decleration*/
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
					}
					else {

						pointer_flag = 0;
						leaf = (leafnode*)root->lnode->lnode;
						Id_leaf = (leafnode*)temp_root_pt->rnode;
						ST.insert(Id_leaf->data.sval->str, "pointer", Stack_Address++, 1);
					}
				}
				else {
					leaf = (leafnode*)root->lnode->lnode;
					leaf_type = leaf->hdr.tok;
					Declerat->son2 = obj_tree(temp_root_pt->rnode);


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

			case TN_OBJ_DEF: {
				/* Maybe you will use it later */
				TreeNode* struct_def = new TreeNode();
				Id_leaf = (leafnode*)root->lnode;
				curr_struct_id = Id_leaf->data.sval->str;
				Structs* our = new Structs(curr_struct_id);
				struct_recepies.insert(pair<string, Structs*>(curr_struct_id,our));
				struct_def->son2 = obj_tree(root->rnode);
				return struct_def; }
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


					obj_tree(root->lnode);
					obj_tree(root->rnode);
				}
				else if (root->hdr.tok == BREAK) {
					/* break jump - for HW2! */
					Break* BREAK_NODE = new Break();
					BREAK_NODE->son1 = obj_tree(root->lnode);
					BREAK_NODE->son2 = obj_tree(root->rnode);
					return BREAK_NODE;
					
				}
				else if (root->hdr.tok == GOTO) {
					/* GOTO jump - for HW2! */
					obj_tree(root->lnode);
					obj_tree(root->rnode);
				}
				break;

			case TN_SWITCH: {
				/* Switch case - for HW2! */
				Switch* Switch_case = new Switch(switch_counter++);
				Switch_case->son1 = obj_tree(root->lnode);
				Switch_case->son2 = obj_tree(root->rnode);
				Switch_case->number_of_cases = switch_case_counter;
				switch_case_counter = 0;
				return Switch_case; }
				break;

			case TN_INDEX: {
				/* call for array - for HW2! */
				leaf = (leafnode*)root->rnode;
				ArrayIndex* call = new ArrayIndex();
				if (root->lnode->hdr.type == TN_DEREF)
					call->type = TN_DEREF;
				else
					call->type = TN_INDEX;
				call->son1 = obj_tree(root->lnode);
				call->dimadress = array_adress;
				call->son2 = obj_tree(root->rnode);
				return call; }
				break;

			case TN_DEREF: {
				/* pointer derefrence - for HW2! */
				PointerDeref* derefrence = new PointerDeref();
				derefrence->son1 = obj_tree(root->lnode);
				derefrence->son2 = obj_tree(root->rnode);

				return derefrence; 
			}
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
					treenode* temp;
					temp = root->lnode;
					string str = "code1";
					while (temp->hdr.type != TN_IDENT) {
						if (temp->hdr.type == TN_SELECT) {
							temp = temp->rnode;
							str = "code2";
							break;
						}
						else if(temp->hdr.type == TN_DEREF) {
							temp = temp->rnode;
						}
						else if (temp->hdr.type == TN_INDEX) {
							temp = temp->lnode;

						}
					}
					Id_leaf = (leafnode*)temp;
					TreeNode* dot = new DotSelector(Id_leaf->data.sval->str, str);
					dot->son1 = obj_tree(root->lnode);
					dot->son2 = obj_tree(root->rnode);
					return dot;
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
					case CASE:{
						/* you should not get here */
						TreeNode* Case_case = new Case(switch_case_counter++, switch_counter-1);
						Case_case->son1 = obj_tree(root->lnode);
						Case_case->son2 = obj_tree(root->rnode);
						return Case_case;
					}
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
						or_N ->son1 = obj_tree(root->lnode);
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
				{	
					TreeNode* While_node = new While(while_counter++);
					While_node->son1=obj_tree(root->lnode);
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

				case TN_LABEL: {
					TreeNode* label = new Label();
					label->son1 = obj_tree(root->lnode);
					label->son2 = obj_tree(root->rnode);
					return label; }
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


}