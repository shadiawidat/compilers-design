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
 /*   PROGRAM = 258,
      BBEGIN = 259,
      END = 260,
      DECLARE = 261,
      PROCEDURE = 262,
      FUNCTION = 263,
      LABEL = 264,
      INTEGER = 265,
      REAL = 266,
      RECORD = 267,
      BOOLEAN = 268,
      ARRAY = 269,
      OF = 270,
      ASSIGN = 271,
      LC = 272,
      RC = 273,
      IF = 274,
      THEN = 275,
      ELSE = 276,
      WHILE = 277,
      REPEAT = 278,
      FI = 279,
      DO = 280,
      OD = 281,
      READ = 282,
      WRITE = 283,
      TRUE = 284,
      FALSE = 285,
      ADD = 286,
      MIN = 287,
      MUL = 288,
      DIV = 289,
      GOTO = 290,
      MOD = 291,
      LES = 292,
      LEQ = 293,
      EQU = 294,
      NEQ = 295,
      GRE = 296,
      GEQ = 297,
      AND = 298,
      OR = 299,
      NOT = 300,
      CASE = 301,
      FOR = 302,
      FIN = 303,
      IDENTICAL = 304,
      FROM = 305,
      BY = 306,
      TO = 307,
      NEW = 308,
      INTCONST = 309,
      IDE = 310,
      REALCONST = 311,
      STRING = 312,
      DUMMY = 313*/

#ifndef AST_H 
#define AST_H

#include <iomanip>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
const int TableSize = 150;
extern int Stack_Address;
extern int if_count;
extern int if_else_count;
extern int while_count;
extern int switch_count;
extern int case_count;
extern int caselist_count;
extern int current_switch;
extern int current_case;
extern string idhelp;
extern int inc_flag;
extern int dec_flag;
extern int codel_coder_flag;
extern string codel_name_help;
/**
 * classes 
 */
//******************************
static string var_name_temp = "";
static string var_type_temp = "";
static int var_len_temp = 0;
static int var_size_temp = 0;
static int var_size_help = 0;
static int not_assign_flag = 0;
static int if_decliration = 0;
static int if_ldc_print = 1;
static int dim_temp = 1;
static int record_index = 0;
static string record_name = "";
static string addres_name_temp = "";
static int pointer_ind_flag = 0;
static string array_type_temp = "";
//******************************
class ArrayList {
public:
    int low;
    int up;
    int len;
    string type;
    ArrayList* next;
    
    ArrayList() {
        len = 0;
        next=NULL;
    }

};
class RecList {
public:
    string key;
    int index;
    int size;
    RecList* next;

    RecList() {
        next = NULL;
    }

};
class Pointers {
public:
    string key;
    int size;
    string type;
    Pointers() {
        
    }

};
class Base {
public:
    string key;
    string type;
    int address;
    int size;
    ArrayList* dimensions;
    RecList* reclist;
    Pointers* var;
    Base* next;


    Base()
    {
        next = NULL;
    }

    Base(string key, string type, int address, int size)
    {
        this->key = key;
        this->size = size;
        this->type = type;
        this->address = address;
        next = NULL;
    }
    
    void setkey(string id){
        key = id;
    }
    string getkey() {
        return key;
    }
    void settype(string tp) {
        type = tp;
    }
    string gettype() {
        return type;
    }
    void setaddress(int ad) {
        address = ad;
    }
    int getaddress() {
        return address;
    }
    void setsize(int s) {
        size = s;
    }
    int getsize() {
        return size;
    }
    void setnext(Base* n) {
        next = n;
    }
    Base* getnext() {
        return next;
    }

    friend class SymbolTable;

};

class SymbolTable {
   
public:
    Base* table[TableSize];
    SymbolTable()
    {
        for (int i = 0; i < TableSize; i++)
            table[i] = NULL;
    }
    int hashf(string name)
    {
        return (name[0] % TableSize);
    }
    bool insert(string name, string type, int address, int size)
    {
        int i = hashf(name);
        Base* newvar = new Base(name, type, address, size);
        if (table[i] == NULL) {
            table[i] = newvar;
            return true;
        }
        else {
            Base* head = table[i];
            while (head->next != NULL)
                head = head->next;
            head->next = newvar;
            return true;
        }
        return false;
    }
    Base* findBase(string name)
    {
        int i = hashf(name);
        Base* head = table[i];
        if (head == NULL)
            return NULL;
        while (head != NULL) {

            if (head->key == name) {
                return head;
            }
            head = head->next;
        }
        return NULL;
    }
    int find(string name)
    {
        int i = hashf(name);
        Base* head = table[i];
        if (head == NULL)
            return -1;
        while (head != NULL) {

            if (head->key == name) {
                return head->address;
            }
            head = head->next;
        }
        return -1;
    }
    string findType(string name)
    {
        int i = hashf(name);
        Base* head = table[i];
        if (head == NULL)
            return "NotFound";
        while (head != NULL) {

            if (head->key == name) {
                return head->type;
            }
            head = head->next;
        }
        return "NotFound";
    }
    int findSize(string name)
    {
        int i = hashf(name);
        Base* head = table[i];
        if (head == NULL)
            return -1;
        while (head != NULL) {

            if (head->key == name) {
                return head->size;
            }
            head = head->next;
        }
        return -1;
    }

};
static SymbolTable SYT;


// base class for tree nodes
class Object :public Base {
public:
 virtual void print (ostream& os) = 0;
 virtual void pcodegen(ostream& os) = 0;
 virtual Object * clone () const {return NULL;}
 virtual ~Object () {}
 /*codel and code r*/
 void codel(Object* left_, ostream& os) {
     codel_coder_flag = 0;
     left_->pcodegen(os);
     if (if_ldc_print) {
         if (!pointer_ind_flag) {
             os << "ldc " << SYT.find(codel_name_help) << endl;
             pointer_ind_flag = 0;
         }
         else {
             pointer_ind_flag = 0;
         }
     }
     if_ldc_print = 1;
     
 }
 void coder(Object* exp_, ostream& os) {
     codel_coder_flag = 1;
     exp_->pcodegen(os);
 }
 /*codel and code r*/

 string name;

};

class Expr : public Object {
public :
    
  // Unary operations
  Expr (int op, Object * atom) : op_(op), atom_(atom), left_(NULL), right_(NULL), unary_(true) {}
  // Binary operations
  Expr (int op, Object * left, Object * right) : op_(op), left_(left), right_(right), atom_(NULL), unary_(false) {}

  Expr(const Expr & exp){
    unary_= exp.unary_; 
    op_ = exp.op_;
    left_ = exp.left_->clone();
    right_ = exp.right_->clone();
    atom_ = exp.atom_->clone();
  }
  
  virtual ~Expr(){
    if (left_) delete left_;
    if (right_) delete right_;
    if (atom_) delete atom_;
  }
  
  void print (ostream& os) {
    os<<"Node name : Expr"<<endl;
    assert(op_);
    if (unary_){
      os<<"Unary op is : "<<op_;
      assert(atom_);
      atom_->print(os);
    }else{
      os<<"Binary op is : "<<op_;
      assert(left_ && right_);
      left_->print(os);
      right_->print(os);
    }
  }
 
  void pcodegen(ostream& os) {
      assert(op_);
      if (unary_) {      
          assert(atom_);
          switch (op_)
          {
          case 310://ID
              codel(atom_, os);
              break;
          case 309://INTCONST
              coder(atom_, os);
              break;
          case 311://REALCONST
              coder(atom_, os);
              break;
          case 300://NOT
              coder(atom_, os);
              os << "not" << endl;
              break;
          case 287://NEG
              coder(atom_, os);
              os << "neg" << endl;
              break;
          default:
              break;
          }
               
      }
      else {      
          assert(left_ && right_);
          switch (op_)
          {
          case 286://ADD
              coder(right_,os);
              if (left_->name == "IntConst" || left_->name == "RealConst")
              {
                  inc_flag = 1;
                  coder(left_, os);
              }
              else {
                  coder(left_, os);
                  os << "add" << endl;
              }
              break;
          case 287://SUB   **MIN
              coder(right_, os);
              if (left_->name == "IntConst" || left_->name == "RealConst")
              {
                  dec_flag = 1;
                  coder(left_, os);
              }
              else {
                  coder(left_, os);
                  os << "sub" << endl;
              }
              break;
          case 288://MUL
              coder(right_, os);
              coder(left_, os);
              os << "mul" << endl;
              break;
          case 289://DIV
              coder(right_, os);
              coder(left_, os);
              os << "div" << endl;
              break; 
          case 292://LES
              coder(right_, os);
              coder(left_, os);
              os << "les" << endl;
              break;
          case 293://LEQ
              coder(right_, os);
              coder(left_, os);
              os << "leq" << endl;
              break;
          case 294://EQU
              coder(right_, os);
              coder(left_, os);
              os << "equ" << endl;
              break;
          case 295://NEQ
              coder(right_, os);
              coder(left_, os);
              os << "neq" << endl;
              break;
          case 296://GRE
              coder(right_, os);
              coder(left_, os);
              os << "grt" << endl;
              break;
          case 297://GEQ
              coder(right_, os);
              coder(left_, os);
              os << "geq" << endl;
              break;
          case 298://AND
              coder(right_, os);
              coder(left_, os);
              os << "and" << endl;
              break;
          case 299://OR
              coder(right_, os);
              coder(left_, os);
              os << "or" << endl;
              break;
          default:
              break;
          }
      }
  }
  virtual Object * clone () const { return new Expr(*this);}
  
private:
  bool unary_;
  int op_;
  Object * left_;
  Object * right_;
  Object * atom_;
};

class ExprList : public Object {
public :
  ExprList (Object * expr) : expr_(expr),expr_list_(NULL){assert(expr_);}
  ExprList (Object * expr, Object * expr_list) : expr_(expr),expr_list_(expr_list) {assert(expr_ && expr_list_);}

  ExprList(const ExprList& exp){
    expr_ = exp.expr_->clone();
    expr_list_ = exp.expr_list_->clone();
  }

  virtual ~ExprList(){
    if (expr_) delete expr_;
    if (expr_list_) delete expr_list_;
  }

  void print (ostream& os) {
		os<<"Node name : ExprList";
		assert( expr_);
    expr_->print(os);
    if (expr_list_){
      expr_list_->print(os);
    }
  }
  void pcodegen(ostream& os) {
      assert(expr_);
      expr_->pcodegen(os);
      if (expr_list_) {
          expr_list_->pcodegen(os);
      }
  }
  virtual Object * clone () const { return new ExprList(*this);}
  
private:
  Object * expr_;
	Object * expr_list_;
};

class Dim : public Object {
public:
  Dim (Object * exp) : exp_(exp), dim_(NULL) {assert(exp_);}
  Dim (Object * exp, Object * dim) : exp_(exp),dim_(dim) {assert(exp_ && dim_);}

  Dim(const Dim& d){
    exp_ = d.exp_->clone();
    dim_ = d.dim_->clone();
  }

  virtual ~Dim(){
    if (exp_) delete exp_;
    if (dim_) delete dim_;
  }
  
  void print (ostream& os) {
    os<<"Node name : Dim"<<endl;
    assert(exp_);
    exp_->print(os);
    if (dim_){
      dim_->print(os);
    }
  }
  void pcodegen(ostream& os) {
      assert(exp_);
      exp_->pcodegen(os);

      int dim_num = SYT.findBase(codel_name_help)->dimensions->len;

      int dim = dim_temp;
      dim_temp++;
      int ixa = 1;
      ArrayList* temp = SYT.findBase(codel_name_help)->dimensions;
      for (int i = 0; i < dim; i++) {
          temp = temp->next;
      }
      //os << dim<<"    " <<dim_num<< endl;
      for (int i = dim; i < dim_num; i++) {
          ixa *= (temp->up - temp->low + 1);
          temp = temp->next;
      }
      os << "ixa " << ixa << endl;
      if (dim_) {
          dim_->pcodegen(os);
      }
  }



  virtual Object * clone () const { return new Dim(*this);}

private:
  Object * exp_;
  Object * dim_;
};

class Atom : public Object {
};

class IntConst : public Atom {
public:
  IntConst(const int i) : i_(i) {
      name = "IntConst";
  }
  IntConst(const IntConst& in) : i_(in.i_) {} 
  void print (ostream& os) {
    os<<"Node name : IntConst. Value is :"<<i_<<endl;
  }
  virtual void pcodegen(ostream& os) {
      if (inc_flag == 1) {
          os << "inc " << i_ << endl;
          inc_flag = 0;
      }
      else {
          if (dec_flag == 1) {
              os << "dec " << i_ << endl;
              dec_flag = 0;
          }
          else {
              os << "ldc " << i_ << endl;
          }
      }
  }
  virtual Object * clone () const { return new IntConst(*this);}
private:
  const int i_;
};

class RealConst : public Atom {
public:
  RealConst(const double r) : r_(r) {
      name = "RealConst";
  }
  RealConst(const RealConst& in) : r_(in.r_) {}  
  void print (ostream& os) {
    os<<"Node name : RealConst. Value is :"<<r_<<endl;
  }
  void pcodegen(ostream& os) {
      if (inc_flag == 1) {
          os << "inc " << setprecision(1) << fixed<< r_ << endl;
          inc_flag = 0;
      }
      else {
          if (dec_flag == 1) {
              os << "dec " << setprecision(1) << fixed << r_ << endl;
              dec_flag = 0;
          }
          else {
              os << "ldc " << setprecision(1) << fixed << r_ << endl;
          }
      }
  }
  virtual Object * clone () const { return new RealConst(*this);}

private:
  const double r_;
};

class True : public Atom {
public:
  void print (ostream& os) {
    os<<"Node name : trueConst. Value is true"<<endl;
  }
  void pcodegen(ostream& os) {
      os << "ldc " << "1" << endl;

  }
  virtual Object * clone () const { return new True();}

};

class False : public Atom {
public :
  void print (ostream& os) {
    os<<"Node name : trueConst. Value is false"<<endl;
  }
  void pcodegen(ostream& os) {
      os << "ldc " << "0" << endl;

  }
  virtual Object * clone () const { return new False();}
};

class Var : public Atom {
};


class ArrayRef : public Var {
public :
  ArrayRef (Object * var, Object * dim) : var_(var),dim_(dim) {assert(var_ && dim_);}
  ArrayRef(const ArrayRef& arr){
    var_ = arr.var_->clone();
    dim_ = arr.dim_->clone();
  }

  virtual ~ArrayRef(){
    if (var_) delete var_;
    if (dim_) delete dim_;
  }

  void print (ostream& os) {
    os<<"Node name : ArrayRef"<<endl;
    assert(var_ && dim_);
    var_->print(os);
    dim_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(var_ && dim_);
      if_ldc_print = 1;
      codel(var_, os);
      if_ldc_print = 0;
      //var_->pcodegen(os);
      dim_temp = 1;
      dim_->pcodegen(os);
      int subpart = 0;
      int y;
      ArrayList* l = SYT.findBase(codel_name_help)->dimensions;
      for (int i = 0; i < SYT.findBase(codel_name_help)->dimensions->len; i++) {
          if (var_type_temp != "Integer" && var_type_temp != "Real" && var_type_temp != "Bool") {
              if (l->type != "Integer" && l->type != "Real" && l->type != "Bool") {
                  y = l->low * SYT.findBase(l->type)->size;
              }
              else {
                  y = l->low * 1;
              }
          }else{
              y = l->low * 1;
          }

          l = l->next;
          int x = 1;
          ArrayList* l1 = l;
          for (int j = i+1; j < SYT.findBase(codel_name_help)->dimensions->len ; j++) {
              x *= (l1->up - l1->low + 1);
              l1 = l1->next;
          }

          subpart += x * y;
      }
      os << "dec " << subpart << endl;;
  }
  virtual Object * clone () const { return new ArrayRef(*this);}

private:
  Object * var_;
  Object * dim_;
};

class RecordRef : public Var {
public :
  RecordRef (Object * varExt, Object * varIn) : varExt_(varExt),varIn_(varIn) {assert(varExt_ && varIn_);}
  RecordRef(const RecordRef& rec){
    varExt_ = rec.varExt_->clone();
    varIn_ = rec.varIn_->clone();
  }
  
  virtual ~RecordRef(){
    if (varExt_) delete varExt_;
    if (varIn_) delete varIn_;
  }

  void print (ostream& os) {
    os<<"Node name : RecordRef"<<endl;
    assert(varExt_ && varIn_);
    varExt_->print(os);
    varIn_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(varExt_ && varIn_);
      varExt_->pcodegen(os);
      varIn_->pcodegen(os);
  }
  virtual Object * clone () const { return new RecordRef(*this);}

private:
  Object * varExt_;
  Object * varIn_;
};

class AddressRef : public Var {
public :
  AddressRef (Object * var) : var_(var) {assert(var_);}
  AddressRef(const AddressRef& addre){
    var_ = addre.var_->clone();
  }

  virtual ~AddressRef(){
    if (var_) delete var_;
  }

  void print (ostream& os) {
    os<<"Node name : AddressRef"<<endl;
    assert(var_);
    var_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(var_);
      pointer_ind_flag = 1;
      var_->pcodegen(os);
      //os << "ldc " << SYT.findBase(var_name_temp)->address << endl;
      os << "ind" << endl;

  }
  virtual Object * clone () { return new AddressRef(*this);}

private:
  Object * var_;
};

class Statement : public Object {
};

class NewStatement : public Statement {
public :
  NewStatement (Object * var) : var_(var) {assert(var_);}
  NewStatement(const NewStatement& ns){
    var_ = ns.var_->clone();
  }

  virtual ~NewStatement(){
    if (var_) delete var_;
  }

  void print (ostream& os) {
		os<<"Node name : NewStatement";
		assert(var_);
    var_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(var_);
      codel(var_,os);
      Base* t = SYT.findBase(codel_name_help);
      os << "ldc "<< t->getsize() << endl;
      os << "new" << endl;
  }
  virtual Object * clone () { return new NewStatement(*this);}
  
private:
  Object * var_;
};

class WriteStrStatement : public Statement {
public :
  WriteStrStatement (const char * str) { 
		str_ = new string(str); 
	}
  
  WriteStrStatement(const WriteStrStatement& ns){
    str_ = new string(*ns.str_); 
  }

  virtual ~WriteStrStatement () {
		if (str_) delete str_;
	}
  void print (ostream& os) {
		os<<"Node name : WriteStrStatement";
		assert(str_);
    os<<"Str statement is: "<<str_<<endl;
  }
  void pcodegen(ostream& os) {
      assert(str_);
      os << "ldc " << *str_ << endl;
      os << "print" << endl;

  }
  virtual Object * clone () { return new WriteStrStatement(*this);}
  
private:
  string * str_;
};

class WriteVarStatement : public Statement {
public :
  WriteVarStatement (Object * exp) : exp_(exp) {assert(exp_);}

  WriteVarStatement(const WriteVarStatement& ex){
    exp_ = ex.clone();
  }

  virtual ~WriteVarStatement(){
    if (exp_) delete exp_;
  }

  void print (ostream& os) {
		os<<"Node name : WriteVarStatement";
		assert(exp_);
    exp_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(exp_);
      coder(exp_, os);
      os << "print" << endl;
  }
  virtual Object * clone () const { return new WriteVarStatement(*this);}
  
private:
  Object * exp_;
};

class ProcedureStatement : public Statement {
public :
  ProcedureStatement (const char * str) { 
		str_ = new string(str); 
	}

  ProcedureStatement (Object * expr_list, const char * str) : expr_list_(expr_list) {
    assert(expr_list_);
    str_ = new string(str);
  }

  ProcedureStatement(const ProcedureStatement& ps){
    expr_list_ = ps.expr_list_->clone();
    str_ = new string(*ps.str_);
  }

   virtual ~ProcedureStatement () {
		if (str_) delete str_;
    if (expr_list_) delete expr_list_;
	} 

  void print (ostream& os) {
    os<<"Node name : ProcedureStatement. Proc name : "<<*str_<<endl;
    if (expr_list_ ){
      expr_list_->print(os);
    }
  }
  void pcodegen(ostream& os) {
      if (expr_list_) {
          expr_list_->pcodegen(os);
      }
  }
  virtual Object * clone () const { return new ProcedureStatement(*this);}
  
private:
	Object * expr_list_;
  string * str_;
};

class Case : public Object {
public :
  Case (Object * stat_list, int val) : leafChild_ (NULL), stat_list_(stat_list) {
		// note the special treatment in miny.y for this case (makenode)
		leafChild_ = new IntConst(val);
		assert(stat_list_);
	}

  Case(const Case& c){
    stat_list_ = c.stat_list_->clone();
    leafChild_ = c.leafChild_->clone();
  }

  virtual ~Case () {
    if (stat_list_) delete stat_list_;
    if (leafChild_) delete leafChild_;
	} 
  
  void print (ostream& os) {
		os<<"Node name : Case";
		assert(stat_list_);
	  stat_list_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(stat_list_);
      coder(stat_list_, os);
  }
  virtual Object * clone () const { return new Case(*this);}

private:
  Object * stat_list_;
	Object * leafChild_;
};


class CaseList : public Object {
public :
  CaseList (Object * ccase) : case_(ccase),case_list_(NULL) {assert(case_);}
  CaseList (Object * ccase, Object * case_list) : case_(ccase),case_list_(case_list) {assert(case_ && case_list_);}

  CaseList(const CaseList& cl){
    case_ = cl.case_->clone();
    case_list_ = cl.case_list_->clone();
  }

  virtual ~CaseList () {
    if (case_) delete case_;
    if (case_list_) delete case_list_;
	} 

  void print (ostream& os) {
		os<<"Node name : CaseList";
		assert( case_ );
    case_->print(os);
    if (case_list_){
      case_list_->print(os);
    }
  }
  void pcodegen(ostream& os) {
      assert(case_);
      int switchnum = current_switch;
      int casenum = current_case;
      
      os << "case_" << casenum << "_" << switchnum << ":" << endl;
      coder(case_, os);
      current_case = casenum;
      current_switch = switchnum;

      os << "ujp " << "end_switch_" << switchnum << endl;

      if (case_list_) {
          current_case++;
          coder(case_list_, os);
      }
      else {
          case_count--;
      }
      current_switch = switchnum;
      current_case = casenum;
      current_switch = switchnum;
      os << "ujp case_" << casenum << "_" << switchnum << endl;
  }
  virtual Object * clone () const { return new CaseList(*this);}

private:
  Object * case_;
	Object * case_list_;
};

class CaseStatement : public Statement {
public :
  CaseStatement (Object * exp, Object * case_list) : exp_(exp),case_list_(case_list) {assert(exp_ && case_list_);}

  CaseStatement(const CaseStatement& cs){
    exp_ = cs.exp_->clone();
    case_list_ = cs.case_list_->clone();
  }

  virtual ~CaseStatement () {
    if (exp_) delete exp_;
    if (case_list_) delete case_list_;
	} 

  void print (ostream& os) {
		os<<"Node name : CaseStatement";
		assert( exp_ && case_list_);
        exp_->print(os);
		case_list_->print(os);
  }
  void pcodegen(ostream& os) {
      int switch_number = switch_count++;
      current_case = 1;
      current_switch = switch_number;
      assert(exp_ && case_list_);
      coder(exp_, os);
      os << "neg" << endl;
      os<<"ixj end_switch_" << switch_number << endl;
      current_switch = switch_number;
      coder(case_list_, os);
      current_switch = switch_number;
      os << "end_switch_" << switch_number << ":" << endl;
  }
  virtual Object * clone () const { return new CaseStatement(*this);}
  
private:
  Object * exp_;
	Object * case_list_;
};

class LoopStatement : public Statement {
public :

  LoopStatement (Object * exp, Object * stat_list) : exp_(exp),stat_list_(stat_list) {assert(exp_ && stat_list_);}

  LoopStatement(const LoopStatement& ls){
    exp_ = ls.exp_->clone();
    stat_list_ = ls.stat_list_->clone();
  }

  virtual ~LoopStatement () {
    if (exp_) delete exp_;
    if (stat_list_) delete stat_list_;
	} 

  void print (ostream& os) {
		os<<"Node name : LoopStatement";
		assert( exp_ && stat_list_);
    exp_->print(os);
		stat_list_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(exp_ && stat_list_);
      int loop_num = while_count++;
      os << "loop_" << loop_num << ":" << endl;
      coder(exp_, os);
      os << "fjp end_loop_" << loop_num << endl;
      coder(stat_list_, os);
      os << "ujp loop_" << loop_num << endl;
      os << "end_loop_" << loop_num << ":" << endl;

  }
  virtual Object * clone () const { return new LoopStatement(*this);}

private:
  Object * exp_;
	Object * stat_list_;
};


class ConditionalStatement : public Statement {
public :
  ConditionalStatement (Object * exp, Object * stat_list_if) : exp_(exp),stat_list_if_(stat_list_if), stat_list_else_(NULL) {assert(exp_ && stat_list_if_);}
  ConditionalStatement (Object * exp, Object * stat_list_if, Object * stat_list_else) : exp_(exp),stat_list_if_(stat_list_if), stat_list_else_(stat_list_else) {assert(exp_ && stat_list_if_ && stat_list_else_ );}

  ConditionalStatement(const ConditionalStatement& cs){
    exp_ = cs.exp_->clone();
    stat_list_if_ = cs.stat_list_if_->clone();
    stat_list_else_ = cs.stat_list_else_->clone();
  }

  virtual ~ConditionalStatement () {
    if (exp_) delete exp_;
    if (stat_list_if_) delete stat_list_if_;
    if (stat_list_else_) delete stat_list_else_;
	} 

  void print (ostream& os) {
		os<<"Node name : ConditionalStatement";
		assert( exp_ && stat_list_if_);
    exp_->print(os);
		stat_list_if_->print(os);
		if (stat_list_else_){
			stat_list_else_->print(os);
		}
  }
  void pcodegen(ostream& os) {
      int statement_number = if_count++;

      assert(exp_ && stat_list_if_);
      coder(exp_, os);
      if (stat_list_else_) {
          os << "fjp else_if_" << statement_number << endl;
      }
      else {
          os << "fjp end_if_" << statement_number << endl;
      }
      coder(stat_list_if_, os);
      if (stat_list_else_) {
          os << "ujp end_if_" << statement_number << endl;
          os << "else_if_" << statement_number <<":"<< endl;
          coder(stat_list_else_, os);
      }
      os << "end_if_" << statement_number  <<":" << endl;

  }
  virtual Object * clone () const { return new ConditionalStatement(*this);}
  
private:
  Object * exp_;
	Object * stat_list_if_;
	Object * stat_list_else_;
};


class Assign : public Statement {
public :
  Assign (Object * var, Object * exp) : var_(var), exp_(exp) {assert(var_ && exp_);}
  
  Assign(const Assign& as){
    var_ = as.var_->clone();
    exp_ = as.exp_->clone();
  }

  virtual ~Assign () {
    if (exp_) delete exp_;
    if (var_) delete var_;
	} 

  void print (ostream& os) {
		os<<"Node name : Assign";
		assert(var_ && exp_);
    var_->print(os);
    exp_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(var_ && exp_);
      codel(exp_, os);
      coder(var_, os);
      os << "sto" << endl;
  }
  virtual Object * clone () const { return new Assign(*this);}

private:
  Object * var_;
  Object * exp_;
};

class StatementList : public Object {
public :
  StatementList (Object * stat) : stat_list_(NULL), stat_(stat)  { assert(stat_);}
  StatementList (Object * stat_list, Object * stat) : stat_list_(stat_list),stat_(stat)  {assert(stat_list_ && stat);}

  StatementList (const StatementList& sl){
    stat_ = sl.stat_->clone();
    stat_list_ = sl.stat_list_->clone();
  }

  virtual ~StatementList () {
    if (stat_) delete stat_;
    if (stat_list_) delete stat_list_;
	} 

  void print (ostream& os) {
	  os<<"Node name : StatementList"<<endl;
	  if (stat_list_){
		  stat_list_->print(os);
	  }
	  assert(stat_);
	  stat_->print(os);
  }
  void pcodegen(ostream& os) {
      if (stat_list_) {
          stat_list_->pcodegen(os);
      }
      assert(stat_);
      stat_->pcodegen(os);
  }
  virtual Object * clone () const { return new StatementList(*this);}
  
private:
  Object * stat_;
  Object * stat_list_;
};

class RecordList : public Object {
public :
  RecordList (Object * var_decl) : record_list_(NULL), var_decl_(var_decl)  { assert(var_decl_);}
  RecordList (Object * record_list, Object * var_decl) : record_list_(record_list),var_decl_(var_decl)  {assert(record_list_ && var_decl);}
  
  RecordList(const RecordList& li){
    var_decl_= li.var_decl_->clone();
    record_list_ = li.record_list_->clone();
  }

  virtual ~RecordList () {
    if (var_decl_) delete var_decl_;
    if (record_list_) delete record_list_;
	} 

  void print (ostream& os) {
	  os<<"Node name : RecordList"<<endl;
	  if (record_list_){
		  record_list_->print(os);
	  }

	  assert(var_decl_);
	  var_decl_->print(os);

  }
  void pcodegen(ostream& os) {
      if (record_list_) {
          record_index++;
          record_list_->pcodegen(os);
          
      }

      assert(var_decl_);
      var_decl_->pcodegen(os);

  }
  virtual Object * clone () const { return new RecordList(*this);}
  
private:
  Object * var_decl_;
  Object * record_list_;
};

class Type : public Object {
};
class SimpleType : public Type {
public:
  SimpleType (const char * name) { 
		name_ = new string(name); 
        idhelp = *name_;
        var_type_temp = *name_;
        var_name_temp = *name_;
        var_size_temp = 1;
        
    }

  virtual ~SimpleType () {
		if (name_ )delete name_;
	}

  SimpleType(const SimpleType& s){
    name_ = new string(*s.name_);
  }

  void print (ostream& os) {
		os<<"Node name : SimpleType"<<endl;;
		os<<"Type is : "<< (*name_) <<endl;
        var_type_temp = *name_;
        idhelp = *name_;
        var_size_temp = 1;

	}
  void pcodegen(ostream& os) {
      idhelp = *name_;
      var_type_temp = *name_;
      var_name_temp = *name_;

      var_size_temp = 1;
  }
  virtual Object * clone () const { return new SimpleType(*this);}

private:
  string * name_;
};

class IdeType : public Type {

public:
  IdeType (const char * name) { 
    name_ = new string(name); 
  }

  virtual ~IdeType () {
    if (name_) delete name_;
  }

  IdeType(const IdeType& s){
    name_ = new string(*s.name_);
  }

  void print (ostream& os) {
    os<<"Node name : IdeType"<<endl;
    //os << "name is : " <<(*name_)  << endl;

    var_name_temp = *name_;
  }

  void pcodegen(ostream& os) {
      if (!if_decliration) {
          var_type_temp = *name_;
          codel_name_help = *name_;

          if (codel_coder_flag == 0) {
              //var_name_temp = *name_;
              codel_name_help = *name_;
              if (pointer_ind_flag) {
                  os << "ldc " << SYT.find(codel_name_help) << endl;

                  //os << "ind" << endl;
                  //pointer_ind_flag = 0;
              }
          }
          else {
              os << "ldc " << SYT.find(*name_) << endl << "ind" << endl;
          }
      }
      else {
          var_type_temp = *name_;

          var_size_temp = SYT.findBase(*name_)->size;
          //os << "type is " << var_type_temp << endl;
      }
    

  }
  virtual Object * clone () const { return new IdeType(*this);}

private:
  string * name_;
};

class ArrayType : public Type {
public :
  ArrayType (int l,int u, Object * type) : low_(l),up_(u),type_(type)  { assert(type_);}
  
  ArrayType(const ArrayType& a) : low_(a.low_), up_(a.up_){
    type_ = a.type_->clone();
  }

  virtual ~ArrayType () {
    if (type_) delete type_;
  }

  void print (ostream& os) {
	  os<<"Node name : ArrayType: low bound is: "<<low_<<", up bound is: "<<up_<<endl;
	  assert(type_);
	  type_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(type_);
      type_->pcodegen(os);
      if (addres_name_temp != "") {
          var_name_temp = addres_name_temp;
      }

      if (SYT.find(var_name_temp) == -1|| addres_name_temp != "") {
          ArrayList* l = new ArrayList();
          if (addres_name_temp == "") {
              SYT.insert(var_name_temp, var_type_temp, Stack_Address, 0);      ///////////////////////////////size is zero check in the future
          
          }
          addres_name_temp = "";
          SYT.findBase(var_name_temp)->dimensions = l;
          var_len_temp=1;
          SYT.findBase(var_name_temp)->dimensions->len = var_len_temp;
          SYT.findBase(var_name_temp)->dimensions->low = low_;
          SYT.findBase(var_name_temp)->dimensions->up = up_;
          SYT.findBase(var_name_temp)->dimensions->next = NULL;
          SYT.findBase(var_name_temp)->dimensions->type = var_type_temp;
          //SYT.findBase(var_name_temp)->dimensions->type = "Array";
          var_size_temp = var_size_temp * (up_ - low_ + 1);
          SYT.findBase(var_name_temp)->size = var_size_temp;
          if (var_type_temp != "Integer" && var_type_temp != "Real" && var_type_temp != "Bool") {
              if (SYT.findBase(var_type_temp)->dimensions != NULL) {
                  SYT.findBase(var_name_temp)->dimensions->next = SYT.findBase(var_type_temp)->dimensions;
                  var_len_temp = 1 + SYT.findBase(var_type_temp)->dimensions->len;
                  SYT.findBase(var_name_temp)->dimensions->len = var_len_temp;
                  array_type_temp = SYT.findBase(var_type_temp)->dimensions->type;
                  SYT.findBase(var_name_temp)->dimensions->type = array_type_temp;
              }
          }

      }
      else {
          ArrayList* l = new ArrayList();
          var_len_temp++;
          l->len = var_len_temp;

          l->low = low_;
          l->up = up_;
          l->next = SYT.findBase(var_name_temp)->dimensions;
          SYT.findBase(var_name_temp)->dimensions = l;
          l->type = array_type_temp;   //////////////////////////////////////////////////////////////
          //l->type = "Array";
          //Linkedlist* temp=l;
          //while (temp != NULL) {
          //    temp->len = var_len_temp;
          //}
          var_size_temp = var_size_temp * (up_ - low_ + 1);
          SYT.findBase(var_name_temp)->size = var_size_temp;
      }
      idhelp = "Array";
  }
  virtual Object * clone () const { return new ArrayType(*this);}

private:
  Object * type_;
	int low_,up_;
};

class RecordType : public Type {
public :
  RecordType (Object * record_list) : record_list_(record_list)  { assert(record_list_);}

  RecordType(const RecordType& y){
    record_list_ = y.record_list_->clone();
  }

  virtual ~RecordType () {
    if (record_list_) delete record_list_;
  }
  
  void print (ostream& os) {
	  os<<"Node name : RecordType"<<endl;
	  assert(record_list_);
	  record_list_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(record_list_);
      record_name = var_name_temp;
      SYT.insert(var_name_temp, "Record", Stack_Address, 0);
      RecList* l = new RecList();
      SYT.findBase(var_name_temp)->reclist = l;
      SYT.findBase(var_name_temp)->dimensions = NULL;
      record_list_->pcodegen(os);
  }
  virtual Object * clone () const { return new RecordType(*this);}

private:
  Object * record_list_;
};


class AddressType : public Type {
public :
  AddressType (Object * type) : type_(type)  { assert(type_);}

  AddressType(const AddressType& t){
    type_ = t.type_->clone();
  }

  virtual ~AddressType () {
    if (type_) delete type_;
  }
  
  void print (ostream& os) {
		os<<"Node name : AddressType"<<endl;
	  assert(type_);
	  type_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(type_);
      string name = var_name_temp;
      addres_name_temp = name;

      SYT.insert(var_name_temp, "Address", Stack_Address, 1);
      Pointers* p = new Pointers();
      SYT.findBase(name)->var = p;
      type_->pcodegen(os);
      SYT.findBase(name)->var->size = var_size_temp;
      //os <<"size is :" << var_size_temp << endl;

      SYT.findBase(name)->var->key = var_name_temp;
      //os << "name is :" << var_name_temp << endl;

      SYT.findBase(name)->var->type = var_type_temp;
      //os << "type is :" << var_type_temp << endl;
      if (var_type_temp != "Integer" && var_type_temp != "Real" && var_type_temp != "Bool"){
          SYT.findBase(name)->dimensions = SYT.findBase(SYT.findBase(name)->var->key)->dimensions;
      }
      idhelp = "Address";
  }
  virtual Object * clone () const { return new AddressType(*this);}

private:
  Object * type_;
};


class Declaration : public Object {
};

class VariableDeclaration : public Declaration {
public:
  VariableDeclaration (Object * type, const char * str) : type_(type){
    assert(type_);
    name_ = new string(str);
    idhelp = *name_;
    var_name_temp = *name_;
    if_decliration = 1;
  }

  VariableDeclaration(const VariableDeclaration& p){
    type_ = p.type_->clone();
    name_ = new string(*p.name_);
  }

  virtual ~VariableDeclaration () {
    if (type_) delete type_;
		delete name_;
	}

  void print (ostream& os) {
    os<<"Node name : VariableDeclaration. Var name is: "<<*name_<<endl;
		assert(type_);
	  type_->print(os);
  }
  void pcodegen(ostream& os) {
      //os <<"decleration " << *name_ << endl;
      assert(type_);
      if_decliration = 1;
      var_name_temp = *name_;
      type_->pcodegen(os);
      if (idhelp == "Integer") {
          
          SYT.insert(*name_, "Integer", Stack_Address, 1);
          Stack_Address += 1;
      }
      else if (idhelp == "Real") {
          SYT.insert(*name_, "Integer", Stack_Address, 1);
          Stack_Address += 1;
      }else if(idhelp == "Array"){
          SYT.findBase(*name_)->size = var_size_temp;
          Stack_Address += var_size_temp;
      }
      else if (idhelp == "Address") {
          Stack_Address += 1;
          addres_name_temp = "";
      }
      else if (idhelp == "Record") {

      }
      if_decliration = 0;
  }
  virtual Object * clone () const { return new VariableDeclaration(*this);}

private:
  Object * type_;
  string * name_;
};

class Parameter : public Object {
public :
  Parameter (Object * type, const char * name) : type_(type){
    assert(type_);
    name_ = new string(name);
  }
  
  Parameter(const Parameter& p){
    type_ = p.type_->clone();
    name_ = new string(*p.name_);
  }

  virtual ~Parameter () {
    if (type_) delete type_;
		delete name_;
	}
  
  void print (ostream& os) {
		printWayOfPassing(os);
    os<<"Parameter name :" <<name_<<endl;
		assert(type_);
	  type_->print(os);
  }
  void pcodegen(ostream& os) {
      printWayOfPassing(os);
      assert(type_);

      type_->pcodegen(os);
  }
protected:
	virtual void printWayOfPassing (ostream& os) const = 0;
  
private:
  Object * type_;
  string * name_;
};

class ByReferenceParameter : public Parameter {
public :
	ByReferenceParameter (Object * type, const char * name) : Parameter (type,name) {}
  virtual Object * clone () const { return new ByReferenceParameter(*this);}
protected:
  void printWayOfPassing (ostream& os) const{
	  os<<"Node name : ByReferenceParameter ";
	}
};

class ByValueParameter : public Parameter {
public :
	ByValueParameter (Object * type, const char * name) : Parameter(type,name) {}
  virtual Object * clone () const { return new ByValueParameter(*this);}
protected:
  void printWayOfPassing (ostream& os) const{
	  os<<"Node name : ByValueParameter ";
	}
};

class ParameterList : public Object {
public :
  ParameterList (Object * formal) : formal_(formal),  formal_list_(NULL) { assert(formal_);}
  ParameterList (Object * formal, Object * formal_list) : formal_(formal), formal_list_(formal_list) {assert(formal_ && formal_list_);}
  
  ParameterList(const ParameterList& pl){
    formal_ = pl.formal_->clone();
    formal_list_ = pl.formal_list_->clone();
  }
  
  virtual ~ParameterList () {
    if (formal_) delete formal_;
    if (formal_list_) delete formal_list_;
	}

  void print (ostream& os) {
	  os<<"Node name : ParameterList"<<endl;
	  if (formal_list_){
		  formal_list_->print(os);
	  }
	  assert(formal_);
	  formal_->print(os);
  }
  void pcodegen(ostream& os) {
      if (formal_list_) {
          formal_list_->pcodegen(os);
      }
      assert(formal_);
      formal_->pcodegen(os);
  }
  virtual Object * clone () const { return new ParameterList(*this);}
  
private:
  Object * formal_;
  Object * formal_list_;
};

class FunctionDeclaration : public Declaration {
public :
  FunctionDeclaration (Object * type, Object * block, const char * name) : type_(type), block_(block), formal_list_(NULL) {
    assert(type_ && block_);
    name_ = new string(name);
  }

  FunctionDeclaration (Object * type, Object * formal_list, Object * block,  const char * name) : type_(type), formal_list_(formal_list),block_(block) {
    assert(type_ && formal_list_ && block_ );
    name_ = new string(name);
  }

  virtual ~FunctionDeclaration () {
    if (type_) delete type_;
    if (block_) delete block_;
    if (formal_list_) delete formal_list_;
    if (name_) delete name_;
  }

  FunctionDeclaration(const FunctionDeclaration& fd){
    type_ = fd.type_->clone();
    block_ = fd.block_->clone();
    formal_list_ = fd.formal_list_->clone();
    name_ = new string(*fd.name_);
  }

  void print (ostream& os) {
    os<<"Node name : FunctionDeclaration. Func name is: "<<*name_<<endl;
	  assert(type_ && block_);
	  type_->print(os);
	  if (formal_list_){
		  formal_list_->print(os);
	  }
	  block_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(type_ && block_);
      type_->pcodegen(os);
      if (formal_list_) {
          formal_list_->pcodegen(os);
      }
      block_->pcodegen(os);
  }
  virtual Object * clone () const { return new FunctionDeclaration(*this);}
  
private:
  Object * type_;
  Object * block_;
  Object * formal_list_;
  string * name_;
};

class ProcedureDeclaration : public Declaration {
public :
  ProcedureDeclaration (Object * block, const char * name) : formal_list_(NULL), block_(block) { 
    assert(block_);
    name_ = new string(name);
  }

  ProcedureDeclaration (Object * formal_list, Object * block, const char * name) : formal_list_(formal_list),block_(block)  {
    assert(formal_list_ && block_);
    name_ = new string(name);
  }

  virtual ~ProcedureDeclaration () {
    if (block_) delete block_;
    if (formal_list_) delete formal_list_;
    if (name_) delete name_;
  }

  ProcedureDeclaration(const ProcedureDeclaration& pd){
    block_ = pd.block_->clone();
    formal_list_ = pd.formal_list_->clone();
    name_ = new string(*pd.name_);
  }

  void print (ostream& os) {
	  os<<"Node name : ProcedureDeclaration. Proc name is: "<<*name_<<endl;
	  assert(block_);
	  if (formal_list_){
		  formal_list_->print(os);
	  }
	  block_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(block_);
      if (formal_list_) {
          formal_list_->pcodegen(os);
      }
      block_->pcodegen(os);
  }
  virtual Object * clone () const { return new ProcedureDeclaration(*this);}
  
private:
  Object * block_;
  Object * formal_list_;
  string * name_;
};

class DeclarationList : public Object {
public :
  DeclarationList (Object * decl) : decl_(decl), decl_list_(NULL) { assert(decl_);}
  DeclarationList (Object * decl_list, Object * decl) : decl_list_(decl_list),decl_(decl)  {assert(decl_list_ && decl);}

  DeclarationList(const DeclarationList& dl){
    decl_ = dl.decl_->clone();
    decl_list_ = dl.decl_list_->clone();
  }

  virtual ~DeclarationList () {
    if (decl_) delete decl_;
    if (decl_list_) delete decl_list_;
  }
  
  void print (ostream& os) {
	  os<<"Node name : DeclarationList"<<endl;
	  if (decl_list_){
		  decl_list_->print(os);
	  }
	  assert(decl_);
	  decl_->print(os);
  }
  void pcodegen(ostream& os) {
      if (decl_list_) {
          decl_list_->pcodegen(os);
      }
      assert(decl_);
      decl_->pcodegen(os);
  }
  virtual Object * clone () const { return new DeclarationList(*this);}

private:
  Object * decl_;
  Object * decl_list_;
};

class Block : public Object {
public :
  Block (Object * stat_seq) : stat_seq_(stat_seq), decl_list_(NULL)  { assert(stat_seq_);}
  Block (Object * decl_list, Object * stat_seq) : decl_list_(decl_list), stat_seq_(stat_seq)  {assert(decl_list_ && stat_seq_);}

  Block(const Block& b){
    decl_list_ = b.decl_list_->clone();
    stat_seq_ = b.stat_seq_->clone();
  }

  virtual ~Block () {
    if (stat_seq_) delete stat_seq_;
    if (decl_list_) delete decl_list_;
  }
  
  void print (ostream& os) {
	  os<<"Node name : Begin"<<endl;
	  if (decl_list_){
		  decl_list_->print(os);
	  }
	  assert(stat_seq_);
	  stat_seq_->print(os);
  }
  void pcodegen(ostream& os) {
      if (decl_list_) {
          decl_list_->pcodegen(os);
      }
      assert(stat_seq_);
      stat_seq_->pcodegen(os);
  }

  virtual Object * clone () const { return new Block(*this);}
  
private:
  Object * decl_list_;
  Object * stat_seq_;
};

class Program : public Object {
public :
  Program (Object * block, const char * str) : block_(NULL) {
    block_ = dynamic_cast<Block *>(block);
    assert(block_);
    name_ = new string(str);
  }

  Program(const Program& prog){
    block_ = dynamic_cast<Block *>(prog.block_->clone());
    assert(block_);
    name_ = new string(*prog.name_);
  }

  virtual ~Program () {
    if (block_) delete block_;
    delete name_;
  }
  
  void print (ostream& os) {
    os<<"Node name : Root/Program. Program name is: "<<*name_<<endl;
	  assert(block_);
    block_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(block_);
      block_->pcodegen(os);
  }
  virtual Object * clone () const { return new Program(*this);}
  
private:
  Block * block_;
  string * name_;
};

#endif //AST_H