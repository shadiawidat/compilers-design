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
#include <map>
#include <iomanip>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
const int TableSize = 150;
//extern int Stack_Address;
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



/// newwww
extern int flag_print;
extern int record_decleration;
extern string id_key;
extern int variable_decleration;
extern string type_of_id;
extern int size_of_id;
extern int dim_count;
extern int index_in_record_list;
extern string record_decliration_name;
extern string record_ref_name;
extern int size_of_record_decliration;
extern int record_ref_flag;
extern string name_of_array_in_record_ref;
extern int pointer_decleration;
extern int pointer_ref;
extern string pointer_decliration_name;
extern string pointer_ref_name;
extern int size_of_pointer_decliration;
extern int pointer_of_array_decleration;
extern int dim_count_temp;
extern string old_record_ref_name;
extern int old_record_ref_name_flag;
extern string record_ref_name_in_array;
extern int record_ref_name_in_array_flag;
extern int ind_flag_ind;
extern int array_ref_flag;
extern int new_flag;

static string current_fp_name = "";
static string father_name_temp = "";
static string father_name_pcodegen_temp = "";
static string current_name_pcodegen_temp = "";
static int sep_counter = 0;
static int sep_counter_max = 0;

static int program_ssp_sep = 0;
static int last_func_ssp = 0;
static int proc_statement_flag = 0;
static int by_value_dec= 0;
static int by_refrence_dec = 0;
static int parameters_order = 0;
static int sending_parameters_order = 0;
static string proc_statement_name="";
//static int parameter_counter=0;
class ArrayList {
public:
    int low;
    int up;
    int len;
    int ixa;
    string type;
    ArrayList* next;
    int flag_new_array_will_start;
    string array_name;
    ArrayList() {
        flag_new_array_will_start = 0;
        len = 0;
        next = NULL;
    }

};
class Pointers {
public:
    string key;
    int size;
    string type;
    int subpart;
    string name_of_var;
    int size_of_var;
    string type_of_var;

    ArrayList* var_dimensions;
    Pointers* var_pointer;

    Pointers() {

    }

};
class RecList {
public:
    string key;
    string record_name;
    int index;
    int size;
    int subpart;
    string type;
    RecList* next;

    ArrayList* dimensions;
    RecList* reclist;
    Pointers* pointer;

    RecList() {
        dimensions = NULL;
        reclist = NULL;
        next = NULL;
    }

};


//end of newwww 




class Base {
public:
    string key;
    string type;
    int address;
    int size;
    int subpart;
    Base* next;
    ArrayList* dimensions;
    RecList* reclist;
    Pointers* pointer;
    string pointer_to;
    int if_func;
    string if_func_name;
    int depth;
    int by_refrence;
    int by_value;
    Base()
    {
        by_refrence = 0;
        by_value = 0;
        if_func_name = "";
        if_func = 0;
        pointer_to = "";
        next = NULL;
    }

    Base(string key, string type, int address, int size)
    {
        by_refrence = 0;
        by_value = 0;
        if_func_name = "";
        if_func = 0;
        pointer_to = "";
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
    string father;
    int depth;
    string name;
    int Stack_Address;
    int sep;
    int ssp;
    int cup_size;
    Base* table[TableSize];
    map<int, string> parameters;

    SymbolTable()
    {
        Stack_Address = 5;
        cup_size = 0;
        sep=0;
        ssp=5;
        name = "";
        depth = 0;
        father = "";

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
        newvar->depth = depth;
        newvar->next = NULL;


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
    bool insert_copy(Base* b)
    {
        Base* newvar = new Base(b->key, b->type, b->address, b->size);
        newvar->depth = b->depth;
        newvar->dimensions = b->dimensions;
        newvar->if_func = b->if_func;
        newvar->if_func_name = b->if_func_name;
        newvar->next = NULL;
        newvar->pointer = b->pointer;
        newvar->pointer_to = b->pointer_to;
        newvar->reclist = b->reclist;
        newvar->subpart = b->subpart;
        newvar->by_refrence = b->by_refrence;
        newvar->by_value = b->by_value;
        
        int i = hashf(newvar->key);

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
    Base* findbase(string name)
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

};
static SymbolTable* ST;
static map<string, SymbolTable*> m;




//m.insert("F", new(SymbolTable));
//m.find("F")->second->findbase
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
     if (!flag_print) {

         //os << "ldc " <<  (*ST).find(codel_name_help) << endl;
         os << "lda " << (*ST).depth - (*ST).findbase(codel_name_help)->depth << " " << (*ST).findbase(codel_name_help)->address << endl;;

         flag_print = 0;
     }

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


      right_->print(os);
      if (left_->name == "IntConst" || left_->name == "RealConst")
      {
          dec_flag = 1;
      }
      else {
          dec_flag = 0;
      }
      left_->print(os);
      switch (op_) {
      case 286://ADD

          sep_counter -= 1;

          break;
      case 287://SUB   **MIN

          break;
      case 288://MUL
          sep_counter -= 1;

          break;
      case 289://DIV
          sep_counter -= 1;

          break;
      case 292://LES
          sep_counter -= 1;

          break;
      case 293://LEQ
          sep_counter -= 1;

          break;
      case 294://EQU
          sep_counter -= 1;

          break;
      case 295://NEQ
          sep_counter -= 1;

          break;
      case 296://GRE
          sep_counter -= 1;

          break;
      case 297://GEQ
          sep_counter -= 1;

          break;
      case 298://AND
          sep_counter -= 1;

          break;
      case 299://OR
          sep_counter -= 1;

          break;
      default:
          break;
      }
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
              inc_flag = 0;

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
              dec_flag = 0;

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
    sep_counter -= 1;

    if (dim_){
      dim_->print(os);
    }
  }
  void pcodegen(ostream& os) {
      assert(exp_);
      string sss = codel_name_help;//////////////////////////////////////////////////////
      exp_->pcodegen(os);
      codel_name_help = sss;
      dim_count =  dim_count_temp;
      if (!record_ref_flag) {
          ArrayList* temp = (*ST).findbase(codel_name_help)->dimensions;
          for (int i = 0; i < dim_count; i++) {
              if (temp != NULL) {
                  temp = temp->next;
              }
          }
          if (temp != NULL) {

              os << "ixa " << temp->ixa << endl;
          }

          if (temp->flag_new_array_will_start) {
              os << "dec " << (*ST).findbase(temp->array_name)->subpart << endl;
              if (temp->next == NULL) {
                  dim_count_temp = -1;
              }
          }
          dim_count++;
          dim_count_temp++;
      }
      else if(record_ref_flag) {
          RecList* r = (*ST).findbase(record_ref_name)->reclist;
          RecList* r1 = r;

          ArrayList* temp;
          while (r1 != NULL) {
              if (r1->key == name_of_array_in_record_ref) {
                  temp = r1->dimensions;
                  break;
              }
              r1 = r1->next;
          }
          if (r1 == NULL) {
              temp = (*ST).findbase(name_of_array_in_record_ref)->dimensions;
          }
          for (int i = 0; i < dim_count; i++) {
              if (temp != NULL) {
                  temp = temp->next;
              }
          }
          
          if (temp != NULL) {
              os << "ixa " << temp->ixa << endl;
          }
          if (temp->flag_new_array_will_start) {
              if (r1 != NULL) {
                  if (r1->type == "Address") {
                      if (temp->array_name == r1->key) {
                          os << "dec " << r1->subpart << endl;
                      }
                      else {
                          RecList* r2 = (*ST).findbase(record_ref_name)->reclist;
                          while (r2 != NULL && r2->key != temp->array_name) {
                              r2 = r2->next;
                          }
                          if (r2 != NULL) {
                              os << "dec " << r2->subpart << endl;

                          }
                          else {

                              os << "dec " << (*ST).findbase(temp->array_name)->subpart << endl;

                          }

                      }
                  }
                  else {////////////////////////////////was only    os << "dec " << r1->subpart << endl;
                      if (temp->array_name == r1->key) {
                          os << "dec " << r1->subpart << endl;
                      }
                      else {
                          RecList* r2 = (*ST).findbase(record_ref_name)->reclist;
                          while (r2 != NULL && r2->key != temp->array_name) {
                              r2 = r2->next;
                          }
                          if (r2 != NULL) {
                              os << "dec " << r2->subpart << endl;

                          }
                          else {

                              os << "dec " << (*ST).findbase(temp->array_name)->subpart << endl;

                          }

                      }
                  }
              }
              else if(r1==NULL) {
                  os << "dec " << (*ST).findbase(temp->array_name)->subpart << endl;
                  if (temp->next == NULL) {
                      dim_count_temp = -1;
                  }
              }
            
          }
          if (temp->next == NULL) {

              dim_count_temp = -1;
          }
          dim_count++;
          dim_count_temp++;
      }
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
    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
   
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
    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
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

    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
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
    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
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
    if (!record_ref_flag) {
        var_->print(os);
    }
   
    dim_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(var_ && dim_);
      array_ref_flag = 1;
      string aaa = codel_name_help;
      if (!record_ref_flag) {
          flag_print = 0; 
          ind_flag_ind = 0;
          var_->pcodegen(os);
          //os << "ldc " << (*ST).find(codel_name_help) << endl;
          os << "lda " << (*ST).depth - (*ST).findbase(codel_name_help)->depth << " " << (*ST).findbase(codel_name_help)->address << endl;

         
          flag_print = 1;
      }
      else {
          ind_flag_ind = 0;

          var_->pcodegen(os);
      }
      
      dim_count = 0;
      ind_flag_ind = 0;

      dim_->pcodegen(os);
      if (codel_coder_flag && !record_ref_flag ) { ////////////check !ind_flag_ind
          os << "ind" << endl;
          ind_flag_ind = 1;

      }
      array_ref_flag = 0;

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
      if (record_ref_flag != 2) {
          record_ref_flag = 1;
      }
      os<<"Node name : RecordRef"<<endl;
      assert(varExt_ && varIn_);
      varExt_->print(os);
      record_ref_flag = 2;
      varIn_->print(os);
      record_ref_flag = 0;
  }
  void pcodegen(ostream& os) {
      assert(varExt_ && varIn_);
      flag_print = 0;
      if (record_ref_flag != 2) {
          record_ref_flag = 1;
      }
      ind_flag_ind = 0;

      varExt_->pcodegen(os);
      record_ref_flag = 2;
      ind_flag_ind = 0;

      varIn_->pcodegen(os);
      record_ref_flag = 0;
      flag_print = 1;

      if (codel_coder_flag && !record_ref_flag && !ind_flag_ind) {
          os << "ind" << endl;
          ind_flag_ind = 1;
      }
      old_record_ref_name_flag = 0;

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
      pointer_ref = 1;
      ind_flag_ind = 0;

      var_->pcodegen(os);
      os << "ind" << endl;


      pointer_ref = 0;
      if (codel_coder_flag && !record_ref_flag && !ind_flag_ind) {
          os << "ind" << endl;
          ind_flag_ind = 1;

      }
      if (new_flag&&!record_ref_flag) {
          codel_name_help = (*ST).findbase(codel_name_help)->pointer_to;
      }
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
    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
    sep_counter -= 2;

  }
  void pcodegen(ostream& os) {
      new_flag = 1;
      assert(var_);
      //var_->pcodegen(os);
      flag_print = 0;
      codel(var_, os);

      Base* t = (*ST).findbase(codel_name_help);

      if (t == NULL) {
          RecList* r;
              if (!old_record_ref_name_flag) {
                  r = (*ST).findbase(record_ref_name)->reclist;
              }
              else {

                  r = (*ST).findbase(old_record_ref_name)->reclist;
                  old_record_ref_name_flag = 0;
              }

          
          while (r != NULL && r->key != codel_name_help) {
              r = r->next;
          }
          if (r == NULL) {
              r = (*ST).findbase(old_record_ref_name)->reclist;
              old_record_ref_name_flag = 0;
              while (r != NULL && r->key != codel_name_help) {
                  r = r->next;
              }
          }
          if (r == NULL) {
              r = (*ST).findbase(record_ref_name)->reclist;
              old_record_ref_name_flag = 0;
              while (r != NULL && r->key != codel_name_help) {
                  r = r->next;
              }
          }
          os << "ldc " << r->pointer->size_of_var << endl;

            
      }
      else {
          if (t->pointer == NULL) {

              os << "ldc " << t->getsize() << endl;

              //os << "t->pointer_to :" << t->pointer_to << endl;

          }
          else {
              if (codel_name_help != t->pointer->key) {
                  os << "ldc 1"<< endl;

              }
              else {
                  os << "ldc " << t->pointer->size_of_var << endl;

              }
              //os << "codel_name_help : " << codel_name_help << endl;
              //os << "t->pointer . name_of_var : " << t->pointer->name_of_var << endl;
              //os << "t->pointer . key : " << t->pointer->key << endl;
             // os << "t->pointer_to :" << t->pointer_to << endl;
          }
      }
      new_flag = 0;

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
    sep_counter += 1;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }
    sep_counter -= 1;
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

    sep_counter -= 1;
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
    sep_counter += 5;
    if (sep_counter_max <= sep_counter) {
        sep_counter_max = sep_counter;
    }

    if (expr_list_ ){
      expr_list_->print(os);
    }
    sep_counter -= 5;
  }

  void pcodegen(ostream& os) {
      int mst_depth;
      int flag = 0;
      for (map<string, SymbolTable*>::iterator it = m.begin(); it != m.end(); it++) {
          if (it->first == *str_) {
              flag = 1;
          }
      }
      if (flag) {
           mst_depth = m.find(m.find(*str_)->second->father)->second->depth - m.find(current_name_pcodegen_temp)->second->depth;
          //os << "elle ana fiyo " << current_name_pcodegen_temp << " " << parameter_of_fp << endl;

          if (mst_depth < 0) {
              mst_depth *= -1;
          }
          os << "mst " << mst_depth << endl;

      }
      else{

          mst_depth = m.find(m.find(current_name_pcodegen_temp)->second->father)->second->depth - m.find(type_of_id)->second->depth;
          if (mst_depth < 0) {
              mst_depth *= -1;
          }
          os << "mstf " << mst_depth << " " << m.find(current_name_pcodegen_temp)->second->findbase(id_key)->address << endl;
      }
      flag = 0;
      proc_statement_flag = 1;
      sending_parameters_order = 0;
      proc_statement_name = *str_;
      if (expr_list_) {
          expr_list_->pcodegen(os);
      }
      proc_statement_flag = 0;
      for (map<string, SymbolTable*>::iterator it = m.begin(); it != m.end(); it++) {
          if (it->first == *str_) {
              flag = 1;
          }
      }
      if (flag) {
          os << "cup " << m.find(*str_)->second->cup_size << " " << *str_ << endl;
      }
      else {
          //os << "ana asa jay atba3 smp" << endl;
         // os << "current_name_pcodegen_temp " << current_name_pcodegen_temp << endl;
          //os << "*str  " << *str_ << endl;
          //os << "m.find(current_name_pcodegen_temp)->second->findbase(*str_)->type   " << m.find(current_name_pcodegen_temp)->second->findbase(*str_)->type << endl;
          //os << (*ST).findbase(*str_)->if_func_name << endl;
          //os << "*str_ is :" << *str_ << endl;
          //
          string ttybe = m.find(current_name_pcodegen_temp)->second->findbase(*str_)->type;
          os << "smp " << m.find((*ST).findbase(*str_)->if_func_name)->second->cup_size << endl;
          os << "cupi " << mst_depth << " " << m.find(current_name_pcodegen_temp)->second->findbase(id_key)->address << endl;
          //parameter_of_fp = 0;

          //os << "cupi " << m.find(*str_)->second->cup_size << " " << *str_ << endl;

      }
     // proc_stat_flag = 0;


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
        sep_counter -= 1;
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
        sep_counter -= 1;
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
        sep_counter -= 1;

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
        exp_->print(os);
        var_->print(os);

    sep_counter -= 2;

  }
  void pcodegen(ostream& os) {
      dim_count_temp = 0;
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
        

	}
  void pcodegen(ostream& os) {
      type_of_id = "SimpleType";
      idhelp = *name_;
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
    if (record_ref_flag != 2) {
        sep_counter += 1;
        if (sep_counter_max <= sep_counter) {
            sep_counter_max = sep_counter;
        }

    }
  }

  void pcodegen(ostream& os) {
      if (!variable_decleration) {

          codel_name_help = *name_;
          if (!record_ref_flag) {

              if (!pointer_ref) {
                  if (codel_coder_flag == 0) {
                      codel_name_help = *name_;
                      flag_print = 0;
                      if (proc_statement_flag) {
                          int flag = 0;
                          for (map<string, SymbolTable*>::iterator it = m.begin(); it != m.end(); it++) {
                              if (it->first == *name_) {
                                  flag = 1;
                              }
                          }
                          if (flag) {
                              os << "ldc " << *name_ << endl;
                              os << "lda " << m.find(*name_)->second->depth - (*ST).depth +1 <<" 0"<< endl;
                          }
                          else if((*ST).findbase(*name_)->if_func) {
                              os << "lda " << (*ST).findbase(*name_)->depth - (*ST).depth << " " << (*ST).findbase(*name_)->address << endl;
                              os << "movs 2" << endl;
                          }

                          else {
                              os << "lda " << (*ST).depth - (*ST).findbase(*name_)->depth  << " " << (*ST).findbase(*name_)->address << endl;
                              if (m.find((*ST).findbase(proc_statement_name)->if_func_name)->second->parameters.find(sending_parameters_order)->second == "byvalue") {
                                  if ((*ST).findbase(*name_)->by_value == 1 && (*ST).findbase(*name_)->by_refrence == 0) {
                                      os << "ind" << endl;
                                  }
                                  else if ((*ST).findbase(*name_)->by_value == 0 && (*ST).findbase(*name_)->by_refrence == 1) {

                                      os << "ind" << endl;
                                      os << "ind" << endl;
                                  }
                                  else {
                                      os << "ind" << endl;
                                  }
                              }
                              else  if (m.find((*ST).findbase(proc_statement_name)->if_func_name)->second->parameters.find(sending_parameters_order)->second == "byrefrence") {
                                  if ((*ST).findbase(*name_)->by_value == 0 && (*ST).findbase(*name_)->by_refrence == 1) {

                                      os << "ind" << endl;
                                  }
                              }
                              sending_parameters_order++;
                          }
                      }
                  }
                  else {
                      if (!array_ref_flag) {
                          //os << "ldc " << (*ST).find(*name_) << endl << "ind" << endl;
                          os << "lda " << (*ST).depth - (*ST).findbase(*name_)->depth << " " << (*ST).findbase(*name_)->address << endl;;
                          os<< "ind" << endl;

                      }
                  }
              }
              else if(pointer_ref) {
                  if (!array_ref_flag) {
                      //os << "ldc " << (*ST).find(*name_) << endl;
                      os << "lda " << (*ST).depth - (*ST).findbase(*name_)->depth << " " << (*ST).findbase(*name_)->address << endl;;

                  }
                  pointer_ref_name = *name_;
                  flag_print = 1;
              }
              
          }
          else if (record_ref_flag == 1) {

              //os << "ldc " << (*ST).findbase(*name_)->address << endl;
              os << "lda " << (*ST).depth - (*ST).findbase(*name_)->depth << " " << (*ST).findbase(*name_)->address << endl;;

              record_ref_name = *name_;
              name_of_array_in_record_ref = *name_;
          }
          else if (record_ref_flag == 2) {
              if (record_ref_name_in_array_flag) {
                  record_ref_name = record_ref_name_in_array;
                  record_ref_name_in_array_flag = 0;
              }
              RecList* r;
              if ((*ST).findbase(record_ref_name) != NULL) {
                  r = (*ST).findbase(record_ref_name)->reclist;
              }
              else {


                  r = (*ST).findbase((*ST).findbase(record_ref_name)->pointer->name_of_var)->reclist;
                  old_record_ref_name = record_ref_name;

                  record_ref_name = (*ST).findbase(record_ref_name)->pointer->name_of_var;
                  old_record_ref_name_flag = 1;

              }
              //os << "record_ref_name is " << record_ref_name << endl;
              //os << "r->key is : " << r->key << endl;
              //os << "r->key is : " << r->key << endl;

              while (r!=NULL && r->key != *name_) {

                  r = r->next;

              }

              if (r->type == "Address") {

                  if (r->reclist != NULL) {
                      old_record_ref_name = record_ref_name;
                      record_ref_name = r->reclist->record_name;
                      old_record_ref_name_flag = 1;
                  }
                /*  if (r->pointer->type_of_var == "Record") {
                      old_record_ref_name = record_ref_name;

                      record_ref_name = r->pointer->name_of_var;
                      old_record_ref_name_flag = 1;



                  }*/
              }
              else if (r->type == "Record") {
                  record_ref_name = r->reclist->record_name;
                  
              }

              else if(r->type == "ARRAY") {
                  if (r->reclist != NULL) {
                      record_ref_name_in_array =r->reclist->record_name;
                      record_ref_name_in_array_flag = 1;

                  }
              }

              name_of_array_in_record_ref = *name_;
              os << "inc " << r->index << endl;

          }
          
      }
      else {
          type_of_id = *name_;
          idhelp = "decleration_of_var";

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

      if (!record_decleration) { // if we dont have record decleration we will insert it normally
          ArrayList* l = new ArrayList();
          if ((*ST).findbase(id_key) == NULL || pointer_decleration) {               //  A    ARRAY [3:9] OF ARRAY [2:5] OF ARRAY[8:10] OF FIXED;
              if (!pointer_decleration) {
                  (*ST).insert(id_key, "ARRAY", (*ST).Stack_Address, 0);
                  
              }
              else {
                  pointer_of_array_decleration = 1;
                  pointer_decleration = 0;
              }
              l->array_name = id_key;
              l->type = type_of_id;
              l->up = up_;
              l->low = low_;
              l->len = 1;
              if (type_of_id != "SimpleType") {
                  l->ixa= (*ST).findbase(type_of_id)->size;
                  size_of_id = (*ST).findbase(type_of_id)->size;
              }
              else {
                  size_of_id = 1;
                  l->ixa = 1;
              }
              size_of_id *= (up_ - low_ + 1);
              l->next = NULL;
              l->flag_new_array_will_start = 1;
              (*ST).findbase(id_key)->dimensions = l;
              if (type_of_id != "SimpleType") {

                  if ((*ST).findbase(type_of_id)->type == "ARRAY"|| (*ST).findbase(type_of_id)->type == "Address") {

                      if ((*ST).findbase(type_of_id)->dimensions != NULL) {
                          l->next = (*ST).findbase(type_of_id)->dimensions;
                          l->len = (*ST).findbase(type_of_id)->dimensions->len + 1;
                      }

                  }
                  if ((*ST).findbase(type_of_id)->reclist != NULL) {
                      (*ST).findbase(id_key)->reclist = (*ST).findbase(type_of_id)->reclist;
                  }
              }
          }
          else {
              l->flag_new_array_will_start = 0;
              l->array_name = id_key;
              l->up = up_;
              l->low = low_;
              l->len = (*ST).findbase(id_key)->dimensions->len +1;
              l->type = type_of_id;
              size_of_id *= (up_ - low_ + 1);
              l->ixa = (*ST).findbase(id_key)->dimensions->ixa *((*ST).findbase(id_key)->dimensions->up- (*ST).findbase(id_key)->dimensions->low+1);
              l->next = (*ST).findbase(id_key)->dimensions;
              (*ST).findbase(id_key)->dimensions = l;
          }
      }
      else if (record_decleration) {                          // decleration array inside of a record;

          if (pointer_decleration) {
              pointer_of_array_decleration = 1;
          }
          ArrayList* l = new ArrayList();
          RecList* r = (*ST).findbase(record_decliration_name)->reclist;
          RecList* r1 = r;
          RecList* r2 = r;
          RecList* r3 = r;
          RecList* r4 = r;


          while (r1 != NULL) {
              if (r1->key == id_key) {
                  break;
              }
              r1 = r1->next;
          }

          if (r1 == NULL || pointer_decleration) {
              if (!pointer_decleration) {
                  r1 = new RecList();
                  l->array_name = id_key;
                  l->type = type_of_id;
                  l->up = up_;
                  l->low = low_;
                  l->len = 1;
                  if (type_of_id != "SimpleType") {
                      while (r2 != NULL) {
                          if (r2->key == type_of_id) {
                              l->ixa = r2->size;
                              size_of_id = r2->size;
                              break;
                          }
                          r2 = r2->next;
                      }
                      if (r2 == NULL) {
                          l->ixa = (*ST).findbase(type_of_id)->size;
                          size_of_id = (*ST).findbase(type_of_id)->size;
                      }

                  }
                  else {                    //array    ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF a;  =2
                      size_of_id = 1;
                      l->ixa = 1;
                  }

                  size_of_id *= (up_ - low_ + 1);
                  l->next = NULL;
                  l->flag_new_array_will_start = 1;
                  r1->dimensions = l;
                  r1->index = index_in_record_list;
                  r1->key = id_key;
                  r1->next = NULL;
                  r1->record_name = record_decliration_name;
                  r1->type = "ARRAY";

                  if (type_of_id != "SimpleType") {
                      while (r3 != NULL) {
                          if (r3->key == type_of_id) {
                              if (r3->type == "ARRAY"||r3->type=="Adress") {
                                  if (r3->type == "Adress") {///////////////////////////////////////////////
                                      if (r3->dimensions != NULL) {
                                          l->next = r3->dimensions;
                                          l->len = r3->dimensions->len + 1;
                                      }
                                  }
                                  else {
                                      l->next = r3->dimensions;
                                      l->len = r3->dimensions->len + 1;
                                  }

                              }
                              if (r3->reclist != NULL) {
                                  r1->reclist = r3->reclist;

                              }
                              break;
                          }
                          r3 = r3->next;
                      }
                      if (r3 == NULL) {
                          if ((*ST).findbase(type_of_id)->type == "ARRAY" || (*ST).findbase(type_of_id)->type == "Adress") {
                              if ((*ST).findbase(type_of_id)->dimensions != NULL) {
                                  l->next = (*ST).findbase(type_of_id)->dimensions;
                                  l->len = (*ST).findbase(type_of_id)->dimensions->len + 1;
                              }

                          }
                          if ((*ST).findbase(type_of_id)->reclist != NULL) {
                              r1->reclist = (*ST).findbase(type_of_id)->reclist;

                          }
                      }
                  }

                  if (r4 == NULL) {
                      (*ST).findbase(record_decliration_name)->reclist = r1;
                  }
                  else {
                      while (r4->next != NULL) {
                          r4 = r4->next;
                      }
                      r4->next = r1;
                  }
              }
              else if(pointer_decleration) {
                  l->array_name = id_key;
                  l->type = type_of_id;
                  l->up = up_;
                  l->low = low_;
                  l->len = 1;
                  if (type_of_id != "SimpleType") {
                      while (r2 != NULL) {
                          if (r2->key == type_of_id) {
                              l->ixa = r2->size;
                              size_of_id = r2->size;
                              break;
                          }
                          r2 = r2->next;
                      }
                      if (r2 == NULL) {
                          l->ixa = (*ST).findbase(type_of_id)->size;
                          size_of_id = (*ST).findbase(type_of_id)->size;
                      }

                  }
                  else {                    //array    ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF a;  =2
                      size_of_id = 1;
                      l->ixa = 1;
                  }

                  size_of_id *= (up_ - low_ + 1);
                  l->next = NULL;
                  l->flag_new_array_will_start = 1;
                  r1->dimensions = l;
                  r1->next = NULL;
                  r1->record_name = record_decliration_name;
                  
                  if (type_of_id != "SimpleType") {
                      while (r3 != NULL) {
                          if (r3->key == type_of_id) {
                              if (r3->type == "ARRAY") {
                                  l->next = r3->dimensions;
                                  l->len = r3->dimensions->len + 1;
                              }
                              break;
                          }
                          r3 = r3->next;
                      }
                      if (r3 == NULL) {
                          if ((*ST).findbase(type_of_id)->type == "ARRAY") {
                              l->next = (*ST).findbase(type_of_id)->dimensions;
                              l->len = (*ST).findbase(type_of_id)->dimensions->len + 1;
                          }
                      }
                  }

                  pointer_decleration = 0;
              }
          }
          else if(r1 != NULL) {
              l->array_name = id_key;
              l->type = type_of_id;
              l->up = up_;
              l->low = low_;
              l->len = r1->dimensions->len + 1;
              l->ixa = r1->dimensions->ixa * (r1->dimensions->up - r1->dimensions->low + 1);
              size_of_id *= (up_ - low_ + 1);
              l->next = r1->dimensions;
              l->flag_new_array_will_start = 0;
              r1->dimensions = l;

          }
      }
      idhelp = "ARRAY";

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
      record_decliration_name = id_key;
      (*ST).insert(id_key, "Record", (*ST).Stack_Address, 0);
      record_decleration = 1;
      record_list_->pcodegen(os);
      record_decleration = 0;
      idhelp = "Record";
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
      if (!record_decleration) {
          pointer_decleration = 1;
          pointer_decliration_name = id_key;

          Pointers* p = new Pointers();
          (*ST).insert(id_key, "Address", (*ST).Stack_Address, 1);

          type_->pcodegen(os);
          (*ST).findbase(id_key)->pointer_to = type_of_id;
          if (type_of_id != "SimpleType" || pointer_of_array_decleration) {
              if (!pointer_of_array_decleration) {
                  p->key = id_key;
                  p->name_of_var = type_of_id;
                  p->size = 1;
                  p->size_of_var = (*ST).findbase(type_of_id)->size;
                  p->type = "Address";
                  p->type_of_var = (*ST).findbase(type_of_id)->type;

                  p->var_dimensions = (*ST).findbase(type_of_id)->dimensions;
                  p->var_pointer = (*ST).findbase(type_of_id)->pointer;
                //  p->var_reclist = (*ST).findbase(type_of_id)->reclist;
                  (*ST).findbase(id_key)->pointer = p;

                  (*ST).findbase(id_key)->dimensions = (*ST).findbase(type_of_id)->dimensions;
                  (*ST).findbase(id_key)->reclist = (*ST).findbase(type_of_id)->reclist;
                  if ((*ST).findbase(type_of_id)->pointer != NULL) {
                      (*ST).findbase(id_key)->pointer = (*ST).findbase(type_of_id)->pointer;

                  }
              }
              else {
                  p->key = id_key;
                  p->name_of_var = type_of_id;
                  p->size = 1;
                  p->size_of_var = size_of_id;
                  p->type = "Address";
                  p->var_dimensions = (*ST).findbase(id_key)->dimensions;
                  p->var_pointer = NULL;
                 // p->var_reclist = NULL;
                  (*ST).findbase(id_key)->reclist = NULL;
                  if ((*ST).findbase(type_of_id)->reclist != NULL) {
                      (*ST).findbase(id_key)->reclist = (*ST).findbase(type_of_id)->reclist;
                  }
                  (*ST).findbase(id_key)->pointer = p;
                  size_of_id = 0;

                  int subpart = 0;
                  int y;
                  ArrayList* l = (*ST).findbase(id_key)->dimensions;
                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {                       //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  (*ST).findbase(id_key)->subpart = subpart;

              }
          }
          else {
              p->key = id_key;
              p->size = 1;
              p->type = "Address";
              p->name_of_var = type_of_id;
              p->size_of_var = 1;
              p->type_of_var = type_of_id;
              p->var_dimensions = NULL;
              p->var_pointer = NULL;
             // p->var_reclist = NULL;

              (*ST).findbase(id_key)->pointer = p;

          }

          pointer_decleration = 0;
          pointer_of_array_decleration = 0;
          idhelp = "Address";
      }
      else if (record_decleration) {                           //if decleration pointer inside of record

          pointer_decleration = 1;
          pointer_decliration_name = id_key;
          Pointers* p = new Pointers();
          RecList* r = (*ST).findbase(record_decliration_name)->reclist;
          RecList* r1 = r;
          RecList* r2 = r;
          RecList* r3 = r;
          RecList* r4 = r;
          RecList* r5 = r;
          RecList* r6 = r;
          RecList* r7 = r;
          while (r1 != NULL) {
              if (r1->key == id_key) {
                  break;
              }
              r1 = r1->next;
          }

          if (r1 == NULL) {

              r1 = new RecList();
              r1->index = index_in_record_list;
              index_in_record_list += 1;
              size_of_record_decliration += 1;
              (*ST).Stack_Address += 1;
              r1->dimensions = NULL;
              r1->key = id_key;
              r1->reclist = NULL;
              r1->record_name = record_decliration_name;
              r1->size = 1;
              r1->type = "Address";
              if (r5 == NULL) {
                  (*ST).findbase(record_decliration_name)->reclist = r1;
                  
              }
              else {
                  while (r5->next != NULL) {
                      r5 = r5->next;
                  }
                  r5->next = r1;
              }
          }

          type_->pcodegen(os);
          if (type_of_id != "SimpleType" || pointer_of_array_decleration) {
              if (!pointer_of_array_decleration) {
                  while (r2 != NULL) {
                      if (r2->key == type_of_id) {
                          break;
                      }
                      r2 = r2->next;
                  }
                  if (r2 == NULL) {

                      p->key = id_key;
                      p->name_of_var = type_of_id;
                      p->size = 1;
                      p->size_of_var = (*ST).findbase(type_of_id)->size;
                      p->type = "Address";
                      p->type_of_var = (*ST).findbase(type_of_id)->type;

                      p->var_dimensions = (*ST).findbase(type_of_id)->dimensions;

                      p->var_pointer = (*ST).findbase(type_of_id)->pointer;

                //      p->var_reclist = (*ST).findbase(type_of_id)->reclist;
                    
                      if ((*ST).findbase(id_key) == NULL) { ////////////////////////////////////////////////////// we are in record it will not find id_key in find base in line 1911
                          RecList* r8 = (*ST).findbase(record_decliration_name)->reclist;
                          RecList* r9 = r8;
                          while (r8 != NULL && r8->key != id_key) {
                              r8 = r8->next;
                          }
                          r8->pointer = p;
                          while (r9 != NULL && r9->key != type_of_id) {
                              r9 = r9->next;
                          }
                          if (r9 != NULL) {
                              if (r9->dimensions != NULL) {
                                  r8->dimensions = r9->dimensions;
                              }
                              //r8->reclist = r9->reclist;
                              if (r9->pointer != NULL) {
                                 r8->pointer = r9->pointer;
                              }
                              if (r9->reclist != NULL) {
                                  r8->reclist = r9->reclist;
                              }
                          }
                          else {
                              if ((*ST).findbase(type_of_id)->reclist != NULL) {
                                  r8->reclist = (*ST).findbase(type_of_id)->reclist;
                              }
                          }


                      }
                      else {
                          (*ST).findbase(id_key)->pointer = p;

                          (*ST).findbase(id_key)->dimensions = (*ST).findbase(type_of_id)->dimensions;
                          //(*ST).findbase(id_key)->reclist = (*ST).findbase(type_of_id)->reclist;
                          if ((*ST).findbase(type_of_id)->pointer != NULL) {
                              (*ST).findbase(id_key)->pointer = (*ST).findbase(type_of_id)->pointer;

                          }
                          if ((*ST).findbase(type_of_id)->reclist != NULL) {
                              (*ST).findbase(id_key)->reclist = (*ST).findbase(type_of_id)->reclist;
                          }
                      }
                    
                  }
                  else {
                      p->key = id_key;
                      p->name_of_var = type_of_id;
                      p->size = 1;
                      p->size_of_var = r2->size;
                      p->type = "Address";
                      p->type_of_var = r2->type;

                      p->var_dimensions = r2->dimensions;
                      p->var_pointer = r2->pointer;
                     // p->var_reclist = r2->reclist;
                      r1->pointer = p;
                      r1->dimensions = r2->dimensions;
                      r1->subpart = r2->subpart;
                      if (r2->reclist != NULL) {
                          r1->reclist = r2->reclist;
                      }
                   //   r2->reclist = r2->reclist;
                     // r1->pointer = r2->pointer;
                  }

              }
              else {

                  while (r6 != NULL) {
                      if (r6->key == id_key) {
                          break;
                      }
                      r6 = r6->next;
                  }
                  p->key = id_key;
                  p->name_of_var = type_of_id;
                  p->size = 1;
                  p->size_of_var = size_of_id;
                  p->type = "Address";
                  p->var_dimensions = r6->dimensions;
                  p->var_pointer = NULL;
              //    p->var_reclist = NULL;
                  r6->reclist = NULL;
                  if ((*ST).findbase(type_of_id)->reclist != NULL) {
                      r6->reclist = (*ST).findbase(type_of_id)->reclist;

                  }
                  r6->pointer = p;

                  size_of_id = 0;

                  int subpart = 0;
                  int y;

                  ArrayList* l = r6->dimensions;

                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {    //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int

                          r7= (*ST).findbase(record_decliration_name)->reclist;

                          while (r7 != NULL && r7->key != type_of_id) {

                              r7 = r7->next;
                          }
                          if (r7 == NULL) {

                              y = l->low * (*ST).findbase(type_of_id)->size;

                          }
                          else {

                              y = l->low * r7->size;
                          }
                      }
                      else {

                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          r7 = (*ST).findbase(record_decliration_name)->reclist;
                          while (r7 != NULL && r7->key != type_of_id) {
                              r7 = r7->next;
                          }
                          if (r7 == NULL) {
                              y = l->low * (*ST).findbase(type_of_id)->size;

                          }
                          else {
                              y = l->low * r7->size;
                          }
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  r6->subpart = subpart;


              }
          }
          else {

              p->key = id_key;
              p->size = 1;
              p->type = "Address";
              p->name_of_var = type_of_id;
              p->size_of_var = 1;
              p->type_of_var = type_of_id;
              p->var_dimensions = NULL;
              p->var_pointer = NULL;
           //   p->var_reclist = NULL;
              if ((*ST).findbase(id_key) != NULL) {
                  (*ST).findbase(id_key)->pointer = p;
              }
              else {
                  RecList* r11 = (*ST).findbase(record_decliration_name)->reclist;
                  while (r11 != NULL && r11->key != id_key) {
                      r11 = r11->next;
                  }
                  r11->pointer = p;
              }

          }

          pointer_decleration = 0;
          pointer_of_array_decleration = 0;
          idhelp = "Address";
      }
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
      variable_decleration = 1;
      id_key = *name_;
      assert(type_);
      type_->pcodegen(os);
      if (m.find(type_of_id)->first != "") {
          (*ST).insert(*name_, type_of_id, (*ST).Stack_Address, 2);
          (*ST).findbase(*name_)->if_func = 1;
          (*ST).findbase(*name_)->if_func_name = type_of_id;
          (*ST).Stack_Address += 2;
      }
      else if ((*ST).findbase(type_of_id) != NULL) {
          if ((*ST).findbase(type_of_id)->if_func == 1) {
              (*ST).insert(*name_, type_of_id, (*ST).Stack_Address, 2);
              (*ST).findbase(*name_)->if_func = 1;
              (*ST).findbase(*name_)->if_func_name = type_of_id;
              (*ST).Stack_Address += 2;
          }
      }
      else
      {
          if (idhelp == "decleration_of_var") {
              if (!record_decleration) {

                  (*ST).insert(*name_, (*ST).findbase(type_of_id)->type, (*ST).Stack_Address, (*ST).findbase(type_of_id)->size);
                  (*ST).Stack_Address += (*ST).findbase(type_of_id)->size;
                  Base* b = (*ST).findbase(*name_);
                  Base* v = (*ST).findbase(type_of_id);
                  b->dimensions = v->dimensions;
                  b->pointer = v->pointer;
                  b->reclist = v->reclist;
                  b->subpart = v->subpart;
                  b->size = v->size;
                  b->type = v->type;
              }
              else if (record_decleration) {
                  RecList* temp = new RecList();
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  RecList* r1 = r;
                  RecList* r2 = r;
                  while (r1 != NULL && r1->key != type_of_id) {
                      r1 = r1->next;
                  }
                  if (r1 == NULL) {
                      Base* v = (*ST).findbase(type_of_id);
                      temp->dimensions = v->dimensions;
                      temp->key = *name_;
                      temp->next = NULL;
                      temp->pointer = v->pointer;
                      temp->reclist = v->reclist;
                      temp->record_name = record_decliration_name;
                      temp->subpart = v->subpart;
                      temp->type = v->type;
                      temp->size = v->size;
                      temp->index = index_in_record_list;
                      index_in_record_list += temp->size;
                      size_of_record_decliration += temp->size;
                      (*ST).Stack_Address += temp->size;
                      r2 = (*ST).findbase(record_decliration_name)->reclist;
                      if (r2 == NULL) {
                          (*ST).findbase(record_decliration_name)->reclist = temp;
                      }
                      else {
                          while (r2->next != NULL) {
                              r2 = r2->next;
                          }
                          r2->next = temp;
                      }
                  }
                  else if (r1 != NULL) {
                      temp->dimensions = r1->dimensions;
                      temp->key = *name_;
                      temp->next = NULL;
                      temp->pointer = r1->pointer;
                      temp->reclist = r1->reclist;
                      temp->record_name = record_decliration_name;
                      temp->subpart = r1->subpart;
                      temp->type = r1->type;
                      temp->size = r1->size;
                      temp->index = index_in_record_list;
                      index_in_record_list += temp->size;
                      size_of_record_decliration += temp->size;

                      (*ST).Stack_Address += temp->size;
                      while (r2->next != NULL) {
                          r2 = r2->next;
                      }
                      r2->next = temp;
                  }
              }
          }

          if (!record_decleration) {
              if (idhelp == "Integer" || idhelp == "Real" || idhelp == "Boolean") {
                  (*ST).insert(*name_, idhelp, (*ST).Stack_Address, 1);
                  (*ST).Stack_Address += 1;
              }
              if (idhelp == "Address") {
                  (*ST).Stack_Address += 1;
              }
              if (idhelp == "ARRAY") {
                  (*ST).findbase(id_key)->size = size_of_id;
                  if (!pointer_of_array_decleration) {
                      (*ST).Stack_Address += size_of_id;
                      size_of_id = 0;
                  }


                  int subpart = 0;
                  int y;

                  ArrayList* l = (*ST).findbase(id_key)->dimensions;
                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {                       //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  (*ST).findbase(id_key)->subpart = subpart;

              }

              if (idhelp == "Record") {
                  (*ST).findbase(record_decliration_name)->size = size_of_record_decliration;
                  size_of_record_decliration = 0;
                  index_in_record_list = 0;
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  while (r != NULL) {
                      if (r->type == "Address") {
                          if (r->pointer->name_of_var == record_decliration_name) {
                              r->pointer->size_of_var = (*ST).findbase(record_decliration_name)->size;
                          }
                      }
                      r = r->next;
                  }
              }

          }
          else if (record_decleration) {
              if (idhelp == "Integer" || idhelp == "Real" || idhelp == "Boolean") {
                  RecList* r = new RecList();
                  r->index = index_in_record_list;
                  index_in_record_list++;
                  r->key = id_key;
                  r->next = NULL;
                  r->record_name = record_decliration_name;
                  r->size = 1;
                  r->type = idhelp;
                  if ((*ST).findbase(record_decliration_name)->reclist == NULL) {
                      (*ST).findbase(record_decliration_name)->reclist = r;
                  }
                  else {
                      RecList* r1 = (*ST).findbase(record_decliration_name)->reclist;
                      while (r1->next != NULL) {
                          r1 = r1->next;
                      }
                      r1->next = r;
                  }
                  (*ST).Stack_Address += 1;
                  size_of_record_decliration += 1;
              }
              if (idhelp == "ARRAY") {
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  RecList* r1 = r;
                  RecList* r2 = r;

                  while (r != NULL && r->key != id_key) {
                      r = r->next;
                  }
                  r->size = size_of_id;
                  index_in_record_list += size_of_id;
                  size_of_record_decliration += size_of_id;
                  (*ST).Stack_Address += size_of_id;

                  //Stack_Address += size_of_id;
                  size_of_id = 0;

                  int subpart = 0;
                  int y;

                  ArrayList* l = r->dimensions;
                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {     //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int
                          while (r1 != NULL && r1->key != type_of_id) {
                              r1 = r1->next;
                          }
                          if (r1 != NULL) {
                              y = l->low * r1->size;
                          }
                          else {
                              y = l->low * (*ST).findbase(type_of_id)->size;
                          }
                      }
                      else {
                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          while (r2 != NULL && r2->key != type_of_id) {
                              r2 = r2->next;
                          }
                          if (r2 != NULL) {
                              y = l->low * r2->size;
                          }
                          else {
                              y = l->low * (*ST).findbase(type_of_id)->size;
                          }
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  r->subpart = subpart;
              }
          }
      }
      variable_decleration = 0;

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
    os<<"Parameter name :" <<*name_<<endl;
		assert(type_);
	  type_->print(os);
  }
  void pcodegen(ostream& os) {
      printWayOfPassing(os);
      //assert(type_);
      if (by_value_dec) {
          (*ST).parameters.insert((pair<int, string>(parameters_order, "byvalue")));
      }
      else {
          (*ST).parameters.insert((pair<int, string>(parameters_order, "byrefrence")));
      }
      parameters_order++;
      //type_->pcodegen(os);
      variable_decleration = 1;
      id_key = *name_;
      assert(type_);
      type_->pcodegen(os);
      int flag = 0;
      for (map<string, SymbolTable*>::iterator it = m.begin(); it != m.end(); it++) {
          if (it->first == type_of_id) {
              flag = 1;
          }
      }
      if (flag) {
          (*ST).insert(*name_, type_of_id, (*ST).Stack_Address, 2);
          (*ST).findbase(*name_)->if_func = 1;
          (*ST).findbase(*name_)->if_func_name = type_of_id;
          (*ST).Stack_Address += 2;
          if (by_value_dec) {
              (*ST).findbase(*name_)->by_value = 1;
          }
          else {
              (*ST).findbase(*name_)->by_refrence = 1;
          }
      }
      else if ((*ST).findbase(type_of_id)!=NULL) {
          if ((*ST).findbase(type_of_id)->if_func == 1) {
              (*ST).insert(*name_, type_of_id, (*ST).Stack_Address, 2);
              (*ST).findbase(*name_)->if_func = 1;
              (*ST).findbase(*name_)->if_func_name = type_of_id;
              (*ST).Stack_Address += 2;
              if (by_value_dec) {
                  (*ST).findbase(*name_)->by_value = 1;
              }
              else {
                  (*ST).findbase(*name_)->by_refrence = 1;
              }
          }
      }
      else
      {
          if (idhelp == "decleration_of_var") {
              if (!record_decleration) {
                  (*ST).insert(*name_, (*ST).findbase(type_of_id)->type, (*ST).Stack_Address, (*ST).findbase(type_of_id)->size);
                  (*ST).Stack_Address += (*ST).findbase(type_of_id)->size;

                  Base* b = (*ST).findbase(*name_);
                  Base* v = (*ST).findbase(type_of_id);
                  b->dimensions = v->dimensions;
                  b->pointer = v->pointer;
                  b->reclist = v->reclist;
                  b->subpart = v->subpart;
                  b->size = v->size;
                  b->type = v->type;
                  if (by_value_dec) {
                      (*ST).findbase(*name_)->by_value = 1;
                  }
                  else {
                      (*ST).findbase(*name_)->by_refrence = 1;
                  }
              }
              else if (record_decleration) {
                  RecList* temp = new RecList();
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  RecList* r1 = r;
                  RecList* r2 = r;
                  while (r1 != NULL && r1->key != type_of_id) {
                      r1 = r1->next;
                  }
                  if (r1 == NULL) {
                      Base* v = (*ST).findbase(type_of_id);
                      temp->dimensions = v->dimensions;
                      temp->key = *name_;
                      temp->next = NULL;
                      temp->pointer = v->pointer;
                      temp->reclist = v->reclist;
                      temp->record_name = record_decliration_name;
                      temp->subpart = v->subpart;
                      temp->type = v->type;
                      temp->size = v->size;
                      temp->index = index_in_record_list;
                      index_in_record_list += temp->size;
                      size_of_record_decliration += temp->size;
                      (*ST).Stack_Address += temp->size;
                      r2 = (*ST).findbase(record_decliration_name)->reclist;
                      if (r2 == NULL) {
                          (*ST).findbase(record_decliration_name)->reclist = temp;
                      }
                      else {
                          while (r2->next != NULL) {
                              r2 = r2->next;
                          }
                          r2->next = temp;
                      }
                  }
                  else if (r1 != NULL) {
                      temp->dimensions = r1->dimensions;
                      temp->key = *name_;
                      temp->next = NULL;
                      temp->pointer = r1->pointer;
                      temp->reclist = r1->reclist;
                      temp->record_name = record_decliration_name;
                      temp->subpart = r1->subpart;
                      temp->type = r1->type;
                      temp->size = r1->size;
                      temp->index = index_in_record_list;
                      index_in_record_list += temp->size;
                      size_of_record_decliration += temp->size;

                      (*ST).Stack_Address += temp->size;
                      while (r2->next != NULL) {
                          r2 = r2->next;
                      }
                      r2->next = temp;
                  }
              }
          }

          if (!record_decleration) {
              if (idhelp == "Integer" || idhelp == "Real" || idhelp == "Boolean") {
                  (*ST).insert(*name_, idhelp, (*ST).Stack_Address, 1);
                  (*ST).Stack_Address += 1;
                  if (by_value_dec) {
                      (*ST).findbase(*name_)->by_value = 1;
                  }
                  else {
                      (*ST).findbase(*name_)->by_refrence = 1;
                  }
              }
              if (idhelp == "Address") {
                  (*ST).Stack_Address += 1;
                  if (by_value_dec) {
                      (*ST).findbase(*name_)->by_value = 1;
                  }
                  else {
                      (*ST).findbase(*name_)->by_refrence = 1;
                  }
              }
              if (idhelp == "ARRAY") {
                  (*ST).findbase(id_key)->size = size_of_id;
                  if (!pointer_of_array_decleration) {
                      (*ST).Stack_Address += size_of_id;
                      size_of_id = 0;
                  }
                  if (by_value_dec) {
                      (*ST).findbase(*name_)->by_value = 1;
                  }
                  else {
                      (*ST).findbase(*name_)->by_refrence = 1;
                  }

                  int subpart = 0;
                  int y;

                  ArrayList* l = (*ST).findbase(id_key)->dimensions;
                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {                       //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          y = l->low * (*ST).findbase(type_of_id)->size;
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  (*ST).findbase(id_key)->subpart = subpart;

              }

              if (idhelp == "Record") {
                  (*ST).findbase(record_decliration_name)->size = size_of_record_decliration;
                  size_of_record_decliration = 0;
                  index_in_record_list = 0;
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  while (r != NULL) {
                      if (r->type == "Address") {
                          if (r->pointer->name_of_var == record_decliration_name) {
                              r->pointer->size_of_var = (*ST).findbase(record_decliration_name)->size;
                          }
                      }
                      r = r->next;
                  }
                  if (by_value_dec) {
                      (*ST).findbase(*name_)->by_value = 1;
                  }
                  else {
                      (*ST).findbase(*name_)->by_refrence = 1;
                  }
              }

          }
          else if (record_decleration) {
              if (idhelp == "Integer" || idhelp == "Real" || idhelp == "Boolean") {
                  RecList* r = new RecList();
                  r->index = index_in_record_list;
                  index_in_record_list++;
                  r->key = id_key;
                  r->next = NULL;
                  r->record_name = record_decliration_name;
                  r->size = 1;
                  r->type = idhelp;
                  if ((*ST).findbase(record_decliration_name)->reclist == NULL) {
                      (*ST).findbase(record_decliration_name)->reclist = r;
                  }
                  else {
                      RecList* r1 = (*ST).findbase(record_decliration_name)->reclist;
                      while (r1->next != NULL) {
                          r1 = r1->next;
                      }
                      r1->next = r;
                  }
                  (*ST).Stack_Address += 1;
                  size_of_record_decliration += 1;
              }
              if (idhelp == "ARRAY") {
                  RecList* r = (*ST).findbase(record_decliration_name)->reclist;
                  RecList* r1 = r;
                  RecList* r2 = r;

                  while (r != NULL && r->key != id_key) {
                      r = r->next;
                  }
                  r->size = size_of_id;
                  index_in_record_list += size_of_id;
                  size_of_record_decliration += size_of_id;
                  (*ST).Stack_Address += size_of_id;

                  //Stack_Address += size_of_id;
                  size_of_id = 0;

                  int subpart = 0;
                  int y;

                  ArrayList* l = r->dimensions;
                  while (l->flag_new_array_will_start != 1) {
                      if (type_of_id != "SimpleType") {     //a  ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF ARRAY[5:9] OF int
                          while (r1 != NULL && r1->key != type_of_id) {
                              r1 = r1->next;
                          }
                          if (r1 != NULL) {
                              y = l->low * r1->size;
                          }
                          else {
                              y = l->low * (*ST).findbase(type_of_id)->size;
                          }
                      }
                      else {
                          y = l->low * 1;
                      }
                      l = l->next;
                      int x = 1;
                      ArrayList* l1 = l;
                      while (l1->flag_new_array_will_start != 1) {
                          if (l1 != NULL) {
                              x *= (l1->up - l1->low + 1);
                              l1 = l1->next;
                          }
                      }
                      if (l1 != NULL) {
                          x *= (l1->up - l1->low + 1);
                          l1 = l1->next;
                      }
                      subpart += x * y;

                  }
                  if (l != NULL) {
                      if (type_of_id != "SimpleType") {
                          while (r2 != NULL && r2->key != type_of_id) {
                              r2 = r2->next;
                          }
                          if (r2 != NULL) {
                              y = l->low * r2->size;
                          }
                          else {
                              y = l->low * (*ST).findbase(type_of_id)->size;
                          }
                      }
                      else {
                          y = l->low * 1;
                      }
                      subpart += y;
                  }
                  r->subpart = subpart;
              }
          }

      }
      variable_decleration = 0;
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

     // os << "Node name : ByReferenceParameter " << endl;;
      by_refrence_dec = 1;
      by_value_dec = 0;
	}
};

class ByValueParameter : public Parameter {
public :
	ByValueParameter (Object * type, const char * name) : Parameter(type,name) {}
  virtual Object * clone () const { return new ByValueParameter(*this);}
protected:
  void printWayOfPassing (ostream& os) const{
      //os << "Node name : ByValueParameter " << endl;;
      by_refrence_dec = 0;
      by_value_dec = 1;
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
      assert(formal_);
      formal_->pcodegen(os);
      if (formal_list_) {
          formal_list_->pcodegen(os);
      }

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

  void print(ostream& os) {
      os << "Node name : FunctionDeclaration. Func name is: " << *name_ << endl;
      assert(type_ && block_);
      type_->print(os);
      m.insert((pair<string, SymbolTable*>(*name_, new(SymbolTable))));
      m.find(*name_)->second->depth = m.find(father_name_temp)->second->depth + 1;
      m.find(*name_)->second->father = father_name_temp;
      m.find(*name_)->second->name = *name_;
      m.find(*name_)->second->sep = 0;
      m.find(*name_)->second->ssp = 5;
      m.find(*name_)->second->Stack_Address = 5;
      father_name_temp = *name_;

      if (formal_list_) {
          formal_list_->print(os);
      }
      block_->print(os);
  }
  void pcodegen(ostream& os) {
      assert(type_ && block_);
      ST = m.find(*name_)->second;
      type_->pcodegen(os);
      ST = m.find(*name_)->second;
      SymbolTable* father_ST = m.find(father_name_pcodegen_temp)->second;
      SymbolTable* my_ST = m.find(*name_)->second;
      for (int i = 0; i < 150; i++) {
          Base* B;
          Base* head = (*father_ST).table[i];
          while (head != NULL) {
              (*my_ST).insert_copy(head);
              head = head->next;
          }
      }
      if ((m.find((*ST).father)->second->father == "" && program_ssp_sep == 0) || (m.find((*ST).father)->second->father != "")) {
          os << "ssp " << m.find((*ST).father)->second->Stack_Address << endl;
          os << "sep " << " waiting for mariah" << endl;
          program_ssp_sep = 1;
          last_func_ssp = 1;
      }
      os << *name_ << ":" << endl;
      parameters_order = 0;
      if (formal_list_) {
          formal_list_->pcodegen(os);
      }

      ST = m.find(*name_)->second;
      (*ST).cup_size = (*ST).Stack_Address - 5;
      father_name_pcodegen_temp = *name_;
      current_name_pcodegen_temp = *name_;
      block_->pcodegen(os);
      os << "retf" << endl;
      father_name_pcodegen_temp = (*ST).father;
      current_name_pcodegen_temp = (*ST).father;
  }
  virtual Object* clone() const { return new FunctionDeclaration(*this); }

private:
    Object* type_;
    Object* block_;
    Object* formal_list_;
    string* name_;
};

class ProcedureDeclaration : public Declaration {
public:
    ProcedureDeclaration(Object* block, const char* name) : formal_list_(NULL), block_(block) {
        assert(block_);
        name_ = new string(name);
    }

    ProcedureDeclaration(Object* formal_list, Object* block, const char* name) : formal_list_(formal_list), block_(block) {
        assert(formal_list_ && block_);
        name_ = new string(name);
    }

    virtual ~ProcedureDeclaration() {
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    ProcedureDeclaration(const ProcedureDeclaration& pd) {

        block_ = pd.block_->clone();
        formal_list_ = pd.formal_list_->clone();
        name_ = new string(*pd.name_);
    }

    void print(ostream& os) {


        os << "Node name : ProcedureDeclaration. Proc name is: " << *name_ << endl;
        assert(block_);
        m.insert((pair<string, SymbolTable*>(*name_, new(SymbolTable))));
        m.find(*name_)->second->depth = m.find(father_name_temp)->second->depth + 1;
        m.find(*name_)->second->father = father_name_temp;
        m.find(*name_)->second->name = *name_;
        m.find(*name_)->second->sep = 0;
        m.find(*name_)->second->ssp = 5;
        m.find(*name_)->second->Stack_Address = 5;
        father_name_temp = *name_;


        if (formal_list_) {
            formal_list_->print(os);
        }

        //block_->print(os);
        int sep_counter_temp = sep_counter;
        int sep_counter_max_temp = sep_counter_max;
        sep_counter = 0;
        sep_counter_max = 0;


        block_->print(os);
        m.find(*name_)->second->sep = sep_counter_max;
        sep_counter = sep_counter_temp;
        sep_counter_max = sep_counter_max_temp;

    }
    void pcodegen(ostream& os) {
        assert(block_);
        
        //if ((((*ST).father) == "")&& program_ssp_sep==0){
        //     os << "HELLO" << endl;
        //     os << "ssp " << (*ST).Stack_Address << endl;
        //     os << "sep " << " waiting for mariah ... " << endl;
        //     program_ssp_sep = 1;
        //}
        ST = m.find(*name_)->second;
        current_name_pcodegen_temp = *name_;
        SymbolTable* father_ST = m.find(father_name_pcodegen_temp)->second;
        SymbolTable* my_ST = m.find(*name_)->second;
        for (int i = 0; i < 150; i++) {
            Base* B;
            Base* head = (*father_ST).table[i];
            while (head != NULL) {
                (*my_ST).insert_copy(head);
                head = head->next;
            }
        }
        if ((m.find((*ST).father)->second->father == "" && program_ssp_sep == 0)|| (m.find((*ST).father)->second->father != "")) {
            os << "ssp " << m.find((*ST).father)->second->Stack_Address << endl;
            os << "sep " << " waiting for mariah" << endl;
            program_ssp_sep = 1;
            last_func_ssp = 1;
        }
        os << *name_ << ":" << endl;
        parameters_order = 0;

        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
        (*ST).cup_size = (*ST).Stack_Address - 5;
        father_name_pcodegen_temp = *name_;
        current_name_pcodegen_temp = *name_;

        block_->pcodegen(os);
        father_name_pcodegen_temp = (*ST).father;
        current_name_pcodegen_temp = (*ST).father;
        /* int sep_counter_temp = sep_counter;
         int sep_counter_max_temp = sep_counter_max;
         sep_counter = 0;
         sep_counter_max = 0;
         m.find(*name_)->second->sep = sep_counter_max;
         sep_counter = sep_counter_temp;
         sep_counter_max = sep_counter_max_temp;*/
        os << "retp" << endl;



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
  
  void print (ostream& os) {//sep
	  os<<"Node name : Begin"<<endl;
      os << "$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;

	  if (decl_list_){
          string father=father_name_temp;
		  decl_list_->print(os);
          father_name_temp = father;
	  }
      os << "----------------------------" << endl;

	  assert(stat_seq_);

	  stat_seq_->print(os);
      os << "++++++++++++++++++++++++++++" << endl;
  }
  void pcodegen(ostream& os) {
      SymbolTable* STT = ST;

      last_func_ssp = 0;
      if (decl_list_) {

          decl_list_->pcodegen(os);
      } 
      if (!last_func_ssp) {
          os << "ssp " <<(*ST).Stack_Address << endl;
          os << "sep " << " waiting for mariah" << endl;
          last_func_ssp = 1;
      }
      ST = STT;
      assert(stat_seq_);


      os <<current_name_pcodegen_temp<< "_begin:" << endl;

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
    m.insert((pair<string, SymbolTable*>(*name_, new(SymbolTable))));
    m.find(*name_)->second->depth = 0;
    m.find(*name_)->second->father = "";
    m.find(*name_)->second->name = *name_;
    m.find(*name_)->second->sep = 0;
    m.find(*name_)->second->ssp = 5;
    m.find(*name_)->second->Stack_Address = 5;
    father_name_temp = *name_;
    int sep_counter_temp = sep_counter;
    int sep_counter_max_temp = sep_counter_max;
    sep_counter = 0;
    sep_counter_max = 0;
    block_->print(os);
    m.find(*name_)->second->sep = sep_counter_max;
    sep_counter = sep_counter_temp;
    sep_counter_max = sep_counter_max_temp;
  }
  void pcodegen(ostream& os) {
      dec_flag = 0;
      inc_flag = 0;
      assert(block_);
      os << *name_ << ":" << endl;
      ST = m.find(*name_)->second;
     

      father_name_pcodegen_temp = *name_;
      current_name_pcodegen_temp= *name_;
      block_->pcodegen(os);
      ST = m.find(*name_)->second;
      os << "stp" << endl;

  }
  virtual Object * clone () const { return new Program(*this);}
  
private:
  Block * block_;
  string * name_;
};

#endif //AST_H