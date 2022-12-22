/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/

#include "main.h"
int if_count = 1;
int if_else_count = 1;
int while_count = 1;
int switch_count = 1;
int case_count = 1;
int caselist_count = 1;
int current_switch = 1;
int current_case = 1;
string idhelp = "";
int inc_flag = 0;
int dec_flag = 0;
int codel_coder_flag = 0;
string codel_name_help = "";
int Stack_Address = 5;

int flag_print = 0;
int record_decleration = 0;
string id_key = "";
int variable_decleration = 0;
string type_of_id = "";
int size_of_id = 0;
int dim_count = 0;
int index_in_record_list = 0;
string record_decliration_name = "";
string record_ref_name = "";
int size_of_record_decliration = 0;
int record_ref_flag = 0;
string name_of_array_in_record_ref = "";

int pointer_decleration = 0;
int pointer_ref = 0;
string pointer_decliration_name = "";
string pointer_ref_name = "";
int size_of_pointer_decliration = 0;
int pointer_of_array_decleration = 0;
int dim_count_temp = 0;

string old_record_ref_name = "";
int old_record_ref_name_flag = 0;

string record_ref_name_in_array = "";
int record_ref_name_in_array_flag = 0;
int ind_flag_ind = 0;
int array_ref_flag = 0;


extern int yydebug;


void writeAST(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->print(file);
}
void Pcode(Object* r, fstream& file)
{
	//Perform recursive tree print
	r->pcodegen(file);
}

Object* getTree(char* progFile)
{

	yydebug = 1;
	assert(progFile);

	// yyin is an external variable that been used in yyparse as pointer to the source file.
	yyin = fopen(progFile, "r");
	if (!yyin) {
		cerr << "Error: file " << progFile << " does not exst. Aborting ..." << endl;;
		exit(1);
	}
	assert(yyin);

	// yyparse is yacc function that parse the program, checks syntax and builds the program AST.
	yyparse();

	fclose(yyin);

	// root was initialized in yyparse while it was building the tree.
	// root is the pointer of the returning tree.
	assert(root);
	return(root);
}



int main(int argc, char* argv[])
{
	CodeGenerator codeGen;

	//check input arguments.
	if (argc < 2) {
		cerr << endl << "Input file is missing. Aborting ..." << endl;
		exit(1);
	}

	Object* theProgram = getTree(argv[1]);
	assert(theProgram == root);

	fstream treeFile(TREE_OUTPUT_TEXT_FILE, ios::out);
	fstream pcodeFile(OUTPUT_CODE_TEXT, ios::out);
	treeFile << AST_FILE_HEADER << endl;
	pcodeFile << AST_FILE_HEADER << endl;
	writeAST(theProgram, treeFile);
	Pcode(theProgram, pcodeFile);
	treeFile.close();
	return (0);
}


