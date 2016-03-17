/**
 * \file eval.cpp
 * 
 * The implementation details of the s-expression evaluator. All
 * functions are encapulated except eval().
 * 
 * CHANGES:
 * - Fix a bug that prevent (quote ()) from calling
 * - Support more Scheme functionalities e.g. define, not, print, eval, <
 * - Use STL map to store the symbol definition
 * 
 */

#include "eval.hpp"
#include "eval_helper.hpp"
#include "RefDict.hpp"
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

//////////////////////////// Type Definition ////////////////////////////
// Remark: use typedef to increase convenience when modifying the template arguments


typedef vector<RefDict*> RefStack;

//////////////////////////// Function Declaration ////////////////////////////

/**
 * \brief Initialize a stack of RefDict.
 *
 * \return The resulting stack.
 */
RefStack init_stack() throw (runtime_error);

/**
 * \brief Look up a specific symbol in the whole stack from top to bottom.
 *
 * \return A pointer to the corresponding cell if found, otherwise, exception.
 */
Cell* lookup_stack(string s) throw (runtime_error);

/**
 * \brief Overloaded version of the lookup_stack(string s). Automatically convert
 * SymbolCell in argument to string.
 *
 * \return A pointer to the corresponding cell if found, otherwise, exception.
 */
Cell* lookup_stack(Cell* const c) throw (runtime_error);

/**
 * \brief Get the final value of a given Cell c. The final value can be null.
 *
 * \return A pointer to Cell storing the value evaluated from c.
 */
Cell* get_fval(Cell* const c) throw (runtime_error);

/**
 * \brief Get the non-null final value of a given Cell c. The final value
 * cannot be null (error if the result is null).
 * \return A pointer to Cell storing the value evaluated from c.
 */
Cell* get_nnfval(Cell* const c) throw (runtime_error);

/**
 * \brief Create a IntCell or DoubleCell depending on the value of
 * is_int. The value of Cell is calculated from n.
 *
 * \return A pointer to IntCell if is_int is true, otherwise DoubleCell.
 * Both storing the value of n.
 */
Cell* make_num(bool& is_int, double n) throw (runtime_error);

/**
 * \brief Give the sum of operands starting from c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to cell that contains either int or double value.
 * (int if all numbers to be summed is int, otherwise, double).
 */
Cell* operand_sum(Cell* const c) throw (runtime_error);

/**
 * \brief Give the difference of operands starting from c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to cell resulting from the operation.
 * (IntCell if all numbers to be substracted is int, otherwise, DoubleCell).
 */
Cell* operand_diff(Cell* const c) throw (runtime_error);

/**
 * \brief Give the product of operands starting from c.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to cell resulting from the operation
 * (IntCell if all numbers to be substracted is int, otherwise, DoubleCell).
 */
Cell* operand_product(Cell* const c) throw (runtime_error);

/**
 * \brief Give the quotient of operands starting from c.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell resulting from the operation
 * (IntCell if all numbers to be substracted is int, otherwise, DoubleCell).
 */
Cell* operand_quotient(Cell* const c) throw (runtime_error);

/**
 * \brief Give the ceil value of a DoubleCell c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell resulting from the operation.
 */
Cell* operand_ceiling(Cell* const c) throw (runtime_error);

/**
 * \brief Give the floor value of a DoubleCell c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell resulting from the operation.
 */
Cell* operand_floor(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is null, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_nullp(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is symbol, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_symbolp(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is int, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_intp(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is double, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_doublep(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is list, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_listp(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether a given Cell c is null.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if c is procedure, otherwise,
 * a pointer to IntCell storing 0.
 */
Cell* operand_procedurep(Cell* const c) throw (runtime_error);

/**
 * \brief Give the result of if function using c as the first argument.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell storing the value evaluating from the 2nd or
 * the 3rd argument (the 2nd if c stores non-zero, the 3rd if c stores 0).
 */
Cell* operand_if(Cell* const c) throw (runtime_error);

/**
 * \brief Give the result of if function using c as the first argument.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell storing the value evaluating from the 2nd or
 * the 3rd argument (the 2nd if c stores non-zero, the 3rd if c stores 0).
 */
Cell* operand_cons(Cell* const c) throw (runtime_error);

/**
 * \brief Give the car cell of a given ConsCell c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell which is the car cell of c.
 */
Cell* operand_car(Cell* const c) throw (runtime_error);

/**
 * \brief Give the cdr cell of a given ConsCell c.
 * Evaluate any branch in the tree.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell which is the cdr cell of c.
 */
Cell* operand_cdr(Cell* const c) throw (runtime_error);

/**
 * \brief Prevent a cell being evaluated once (Directly output the
 * structure without evaluation).
 * (error if c does not hold well-formed arguments).
 *
 * \return null always.
 */
Cell* operand_quote(Cell* const c) throw (runtime_error);

/**
 * \brief Define a given symbol with a number
 * (error if c does not hold well-formed arguments).
 *
 * \return null always.
 */
Cell* operand_define(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether the value of a list of numbers monotonically
 * increases.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if the above condition holds,
 * otherwise, a pointer to IntCell storing 0.
 */
Cell* operand_lessthan(Cell* const c) throw (runtime_error);

/**
 * \brief Check whether the value of a cell equals 0 or 0.0.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to IntCell storing 1 if the above condition holds,
 * otherwise, a pointer to IntCell storing 0.
 */
Cell* operand_not(Cell* const c) throw (runtime_error);

/**
 * \brief Print the evaluation result of c to output stream.
 * (error if c does not hold well-formed arguments).
 *
 * \return null always.
 */
Cell* operand_print(Cell* const c) throw (runtime_error);

/**
 * \brief Evaluate c once (cancelling the effect of quote once).
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell storing the evaluation result.
 */
Cell* operand_eval(Cell* const c) throw (runtime_error);

/**
 * \brief Create a ProcedureCell using c as formals and cdr of c as body.
 * (error if c does not hold well-formed arguments).
 *
 * \return A pointer to Cell storing the resulting ProcedureCell.
 */
Cell* operand_lambda(Cell* const c) throw (runtime_error);

/**
 * \brief Apply c to cdr of c.
 * (error if c does not hold well-formed arguments).
 *
 * \return Result from evaluating the procedure.
 */
Cell* operand_apply(Cell* const c) throw (runtime_error);

/**
 * \brief Use a list of argument-value pairs stored in c to apply the cdr of c.
 * (error if c does not hold well-formed arguments).
 *
 * \return Result from evaluating the procedure.
 */
Cell* operand_let(Cell* const c) throw (runtime_error);

/**
 * \brief Applying a list of arguments to a procedure.
 *
 * \return Result from evaluating the procedure.
 */
Cell* apply(Cell* const procedure, Cell* const argv_list) throw (runtime_error);

/**
 * \brief Evaluate all branches of a tree to form a linear list.
 *
 * \return Head of the resulting list.
 */
Cell* my_list(Cell* const c) throw (runtime_error);

/**
 * \brief Transform a list of pair into a linear list containing the left value.
 * i.e. ((a 1) (b 2) (c 3) ...) into (a b c ...)
 *
 * \return Head of the resulting list.
 */
Cell* pair_left(Cell* const c) throw (runtime_error);

/**
 * \brief Transform a list of pair into a linear list containing the right value.
 * i.e. ((a 1) (b 2) (c 3) ...) into (1 2 3 ...)
 *
 * \return Head of the resulting list.
 */
Cell* pair_right(Cell* const c) throw (runtime_error);

//////////////////////////// Global Variable Initialization ////////////////////////////

RefDict global_ref(RefDict::SCOPE_GLOBAL);
RefStack ref_stack = init_stack();

//////////////////////////// Function Definition ////////////////////////////
// Reminder: Only eval() is not encapsulated
Cell* eval(Cell* const c)
{
  if (nullp(c)) {
    throw runtime_error("trying to evaluate empty or non-cons list");
  } else if (!listp(c)) {
    return symbolp(c) ? lookup_stack(c) : c;
  }
  Cell* temp_c = get_nnfval(c);
  if (symbolp(temp_c)) {
    if (temp_c->get_symbol() == "+") {
      return operand_sum(cdr(c));
  
    } else if (temp_c->get_symbol() == "-") {
      return operand_diff(cdr(c));
  
    } else if (temp_c->get_symbol() == "*") {
      return operand_product(cdr(c));
      
    } else if (temp_c->get_symbol() == "/") {
      return operand_quotient(cdr(c));
  
    } else if (temp_c->get_symbol() == "ceiling") {
      return operand_ceiling(cdr(c));
  
    } else if (temp_c->get_symbol() == "floor") {
      return operand_floor(cdr(c));
  
    } else if (temp_c->get_symbol() == "nullp") {
      return operand_nullp(cdr(c));
  
    } else if (temp_c->get_symbol() == "symbolp") {
      return operand_symbolp(cdr(c));
  
    } else if (temp_c->get_symbol() == "intp") {
      return operand_intp(cdr(c));
  
    } else if (temp_c->get_symbol() == "doublep") {
      return operand_doublep(cdr(c));
      
    } else if (temp_c->get_symbol() == "listp") {
      return operand_listp(cdr(c));
  
    } else if (temp_c->get_symbol() == "procedurep") {
      return operand_procedurep(cdr(c));
  
    } else if (temp_c->get_symbol() == "if") {
      return operand_if(cdr(c));
  
    } else if (temp_c->get_symbol() == "cons") {
      return operand_cons(cdr(c));
  
    } else if (temp_c->get_symbol() == "car") {
      return operand_car(cdr(c));
  
    } else if (temp_c->get_symbol() == "cdr") {
      return operand_cdr(cdr(c));
  
    } else if (temp_c->get_symbol() == "quote") {
      return operand_quote(cdr(c));
  
    } else if (temp_c->get_symbol() == "define") {
      return operand_define(cdr(c));
    
    } else if (temp_c->get_symbol() == "<") {
      return operand_lessthan(cdr(c));
    
    } else if (temp_c->get_symbol() == "not") {
      return operand_not(cdr(c));
    
    } else if (temp_c->get_symbol() == "print") {
      return operand_print(cdr(c));
    
    } else if (temp_c->get_symbol() == "eval") {
      return operand_eval(cdr(c));
    
    } else if (temp_c->get_symbol() == "lambda") {
      return operand_lambda(cdr(c));
    
    } else if (temp_c->get_symbol() == "apply") {
      return operand_apply(cdr(c));
      
    } else if (temp_c->get_symbol() == "let") {
      return operand_let(cdr(c));
      
    }
  
  } else if (procedurep(temp_c)) {
    return apply(temp_c, cdr(c));
    
  }

  throw runtime_error("cannot apply a value that is not a function");
}

RefStack init_stack() throw (runtime_error)
{
  RefStack v;
  v.push_back(&global_ref);
  return v;
}

Cell* lookup_stack(string s) throw (runtime_error)
{
  RefDict::RefIter result;
  for (unsigned i = ref_stack.size(); i-- > 0; ) {
    result = ref_stack[i]->lookup(s);
    if (result != ref_stack[i]->end()) {
      return result->second;
    }
  }
  throw runtime_error("symbol not found (\"" + s + "\")");
}

Cell* lookup_stack(Cell* const c) throw (runtime_error)
{
  if (!symbolp(c)) {
    throw runtime_error("cannot apply a value that is not a function");
  }
  return lookup_stack(c->get_symbol());
}

Cell* apply(Cell* const procedure, Cell* const argv_list) throw (runtime_error)
{
  if (symbolp(procedure)) {
    return eval(cons(procedure, listp(argv_list) ? argv_list : cons(argv_list, nil)));
  }
  
  RefDict* local_ref = new RefDict(RefDict::SCOPE_LOCAL);
  Cell* formals_list = get_formals(procedure);
  Cell* body_list = get_body(procedure);
  
  Cell* args = car(formals_list);
  Cell* argv = argv_list;
  if (symbolp(args)) {
    local_ref->insert(args, my_list(argv));
    
  } else if (listp(args)) {
    int args_size = size(args);
    int argv_size = size(argv);
    check_argn(args_size, args_size, argv_size);
    while (!nullp(args) && !nullp(argv)) {
      local_ref->insert(car(args), get_fval(argv));
      args = cdr(args);
      argv = cdr(argv);
    }
    
  }
  ref_stack.push_back(local_ref);
  
  Cell* func_statement = body_list;
  while (!nullp(cdr(func_statement))) {
    eval(car(func_statement));
    func_statement = cdr(func_statement);
  }
  
  func_statement = eval(car(func_statement));
  local_ref->clear();
  ref_stack.pop_back();
    
  return func_statement;
}

Cell* get_fval(Cell* const c) throw (runtime_error)
{
  if (listp(c)) {
    Cell* c_car = car(c);
    if (listp(c_car)) {
      c_car = eval(c_car); // recursively evaluate the list
    } else if (symbolp(c_car)) {
      c_car = lookup_stack(c_car); // search for a symbol
    }
    return c_car;
  } else {
    return c; // c itself is already the final value
  }
}

Cell* get_nnfval(Cell* const c) throw (runtime_error)
{
  Cell* temp_c = get_fval(c);
  if (nullp(temp_c)) {
    throw runtime_error("operation used cannot be done on a null cell");
  } else {
    return temp_c;
  }
}

Cell* make_num(bool& is_int, double n) throw (runtime_error)
{
  return is_int ? make_int((int) n) : make_double(n);
}

Cell* operand_sum(Cell* const c) throw (runtime_error)
{
  Cell* temp_c = c;
  bool is_result_int = true; // assuming all cells to be summed stores int
  double sum = 0; // accumulative
  
  // loop through the list starting from c
  while (!nullp(temp_c)) {
    // ensure that the temp_c is completely evaluated, then add it to sum
    get_nnfval(temp_c)->add_to(is_result_int, sum);
    temp_c = cdr(temp_c);
  }
  
  return make_num(is_result_int, sum);
}

Cell* operand_diff(Cell* const c) throw (runtime_error)
{
  if (nullp(c)) {
    throw runtime_error("at least one operand should be given for -");
  }
  
  Cell* temp_c = c;
  bool is_result_int = true; // assuming all cells to be substracted stores int
  double diff = 0; // accumulative
  
  if (nullp(cdr(c))) {
    get_nnfval(temp_c)->subtract_from(is_result_int, diff);
  } else {
    get_nnfval(temp_c)->add_to(is_result_int, diff);
    temp_c = cdr(temp_c);
    // loop through the list starting from c
    while (!nullp(temp_c)) {
      // ensure that the temp_c is completely evaluated, then subtract it from diff
      get_nnfval(temp_c)->subtract_from(is_result_int, diff);
      temp_c = cdr(temp_c);
    }
  }
  return make_num(is_result_int, diff);
}

Cell* operand_product(Cell* const c) throw (runtime_error)
{
  Cell* temp_c = c;
  bool is_result_int = true; // assuming all cells to be multiplied stores int
  double product = 1; // accumulative
  
  // loop through the list starting from c
  while (!nullp(temp_c)) {
    // ensure that the temp_c is completely evaluated, then multiply it to product
    get_nnfval(temp_c)->multiply_to(is_result_int, product);
    temp_c = cdr(temp_c);
  }
  
  return make_num(is_result_int, product);
}

Cell* operand_quotient(Cell* const c) throw (runtime_error)
{
  if (nullp(c)) {
    throw runtime_error("at least one operand should be given for /");
  }
  
  Cell* temp_c = c;
  bool is_result_int = true; // assuming all cells to be divided stores int
  double quotient = 1; // accumulative
  
  if (nullp(cdr(c))) {
    get_nnfval(temp_c)->divide_from(is_result_int, quotient);
  } else {
    get_nnfval(temp_c)->multiply_to(is_result_int, quotient);
    temp_c = cdr(temp_c);
    // loop through the list starting from c
    while (!nullp(temp_c)) {
      // ensure that the temp_c is completely evaluated, then divide it into quotient
      get_nnfval(temp_c)->divide_from(is_result_int, quotient);
      temp_c = cdr(temp_c);
    }
  }
  
  return make_num(is_result_int, quotient);
}

Cell* operand_ceiling(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return get_nnfval(c)->ceiling();
}

Cell* operand_floor(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return get_nnfval(c)->floor();
}

Cell* operand_nullp(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return nullp(get_fval(c)) ? make_int(1) : make_int(0);
}

Cell* operand_symbolp(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return symbolp(get_fval(c)) ? make_int(1) : make_int(0);
}

Cell* operand_intp(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return intp(get_fval(c)) ? make_int(1) : make_int(0);
}

Cell* operand_doublep(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return doublep(get_fval(c)) ? make_int(1) : make_int(0);
}

Cell* operand_listp(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return listp(get_fval(c)) ? make_int(1) : make_int(0);
}

Cell* operand_procedurep(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return procedurep(get_fval(c)) ? make_int(1) : make_int(0);
}

// Remark: (if (quote ()) a b) gives error instead of a
Cell* operand_if(Cell* const c) throw (runtime_error)
{
  int num_arg = size(c);
  check_argn(2, 3, num_arg);
  // Remark: Both IntCell and DoubleCell can call get_double()
  // in order to get its value as a double
  if (get_fval(c)->get_double()) {
    return get_fval(cdr(c));
  } else {
    // false value is not defined in this case
    return num_arg == 2 ? nil : get_fval(cdr(cdr(c))); 
  }
}

Cell* operand_cons(Cell* const c) throw (runtime_error)
{
  check_argn(2, 2, size(c));
  return cons(get_fval(c), get_fval(cdr(c)));
}

Cell* operand_car(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return car(get_fval(c));
}

Cell* operand_cdr(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return cdr(get_nnfval(c));
}

Cell* operand_quote(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return car(c);
}

Cell* operand_define(Cell* const c) throw (runtime_error)
{
  check_argn(2, 2, size(c));
  if (nullp(car(c))) {
    throw runtime_error("defining null");
  }
  ref_stack.back()->insert(car(c), get_fval(cdr(c)));
  return nil;
}

Cell* operand_lessthan(Cell* const c) throw (runtime_error)
{
  Cell* temp_c = c; // looper
  Cell* cur; // current cell value
  Cell* next; // next cell value
  bool result = true;
  // Go through the list
  while (!nullp(temp_c)) {
    // Validate the current cell
    cur = get_nnfval(temp_c);
    if(!intp(cur) && !doublep(cur) && !symbolp(cur)) {
      throw runtime_error("only symbol, int or double cell can be compared");
    }
    // Validate the next cell
    if (!nullp(cdr(temp_c))) {
      next = get_nnfval(cdr(temp_c));
      if (!intp(next) && !doublep(next) && !symbolp(next)) {
	throw runtime_error("only symbol, int or double cell can be compared");
      }
      // Both cells are qualified for comparison
      if (symbolp(cur) && symbolp(next)) {
	if (cur->get_symbol() >= next->get_symbol()) {
	  result = false;
	}
      } else if (!symbolp(cur) && !symbolp(next)) {
	if (cur->get_double() >= next->get_double()) {
	  result = false;
	}
      } else {
	throw runtime_error("only the same type of cells can be compared");
      }
    }
    temp_c = cdr(temp_c);
  }
  return result ? make_int(1) : make_int(0);
}

Cell* operand_not(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  Cell* fval = get_fval(c);
  if ((intp(fval) && !fval->get_int()) || (doublep(fval) && !fval->get_double())) {
    return make_int(1);
  } else {
    return make_int(0);
  }
}

Cell* operand_print(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  Cell* temp_c = eval(car(c));
  if (!nullp(temp_c)) {
    temp_c->print(cout);
  } else {
    cout << "()";
  }
  cout << endl;
  return nil;
}

Cell* operand_eval(Cell* const c) throw (runtime_error)
{
  check_argn(1, 1, size(c));
  return eval(get_nnfval(c));
}

Cell* operand_lambda(Cell* const c) throw (runtime_error)
{
  check_argn(2, size(c));
  return lambda(c, cdr(c));
}

Cell* operand_apply(Cell* const c) throw (runtime_error)
{
  check_argn(2, 2, size(c));
  return apply(lookup_stack(car(c)), eval(car(cdr(c))));
}

Cell* operand_let(Cell* const c) throw (runtime_error)
{
  check_argn(2, size(c));
  if (!listp(car(c)) || !listp(car(car(c)))) {
    throw runtime_error("cannot apply a value that is not a function");
  }
  RefDict local_ref = RefDict(RefDict::SCOPE_LOCAL);
  Cell* pair_list = car(c);
  return apply(lambda(cons(pair_left(pair_list), nil), cdr(c)), pair_right(pair_list));
}

Cell* my_list(Cell* const c) throw (runtime_error)
{
  return nullp(c) ? c : cons(get_fval(c), my_list(cdr(c)));
}

Cell* pair_left(Cell* const c) throw (runtime_error)
{
  return nullp(c) ? c : cons(car(car(c)), pair_left(cdr(c)));
}

Cell* pair_right(Cell* const c) throw (runtime_error)
{
  return nullp(c) ? c : cons(get_fval(cdr(car(c))), pair_right(cdr(c)));
}
