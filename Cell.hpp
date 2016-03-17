/**
 * \mainpage COMP151H Programming Assignment 6, Fall 2014
 *
 * \author Kwok Hin Kwan, Billy
 * \author 20188664
 * \author hkkwokaa@stu.ust.hk
 * \author LA1
 *
 * \date 2014.11.26
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: 2014.11.26 at 23:00 by CASS
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdexcept>

/**
 * \class Cell
 * \brief Abstract base class Cell.
 */
// Remark: Derived classes are stored in separate files for the sake of
// potential division of work in the future. Somebody else may collaboratively
// edit the Cell class and its derivative. Separating the implementation would
// help avoiding the conflict among code.
class Cell {
public:
  
  /**
   * \brief Constructor for initialising Cell class.
   */
  Cell();
  
  /**
   * \brief Virtual destructor.
   */
  virtual ~Cell();
  
  /**
   * \brief Check if this is an IntCell.
   * \return True iff this is an IntCell.
   */
  virtual bool is_int() const;
  
  /**
   * \brief Check if this is a DoubleCell.
   * \return True iff this is a DoubleCell.
   */
  virtual bool is_double() const;
  
  /**
   * \brief Check if this is a SymbolCell.
   * \return True iff this is a SymbolCell.
   */
  virtual bool is_symbol() const;
  
  /**
   * \brief Check if this is a ConsCell.
   * \return True iff this is a ConsCell.
   */
  virtual bool is_cons() const;

  /**
   * \brief Check if this is a ProcedureCell.
   * \return True iff this is a ProcedureCell.
   */
  virtual bool is_procedure() const;
  
  /**
   * \brief Accessor (error if this is not an IntCell or DoubleCell).
   * \return The value in this IntCell.
   */
  virtual int get_int() const;
  
  /**
   * \brief Accessor (error if this is not an IntCell or DoubleCell).
   * \return The value in this DoubleCell.
   */
  virtual double get_double() const;
  
  /**
   * \brief Accessor (error if this is not an IntCell, DoubleCell or SymbolCell).
   * \return The symbol name in this SymbolCell.
   */
  virtual std::string get_symbol() const;
  
  /**
   * \brief Accessor (error if this is not a ConsCell).
   * \return First child cell.
   */
  virtual Cell* get_car() const;
  
  /**
   * \brief Accessor (error if this is not a ConsCell).
   * \return Rest child cell.
   */
  virtual Cell* get_cdr() const;
  
  virtual Cell* get_formals() const;
  
  virtual Cell* get_body() const;
  
  /**
   * \brief Add the value stored in the cell to a cummulative sum and set
   * the result type to double if any double is involved in the calculation.
   * (error if this is not an IntCell or DoubleCell)
   * \return void.
   */
  virtual void add_to(bool& is_result_int, double& cum_sum) const;
  
  /**
   * \brief Subtract the value stored in the cell from a cummulative difference
   * and set the result type to double if any double is involved in the calculation.
   * (error if this is not an IntCell or DoubleCell)
   * \return void.
   */
  virtual void subtract_from(bool& is_result_int, double& cum_diff) const;
  
  /**
   * \brief Multiply the value stored in the cell to a cummulative product and set
   * the result type to double if any double is involved in the calculation.
   * (error if this is not an IntCell or DoubleCell)
   * \return void.
   */
  virtual void multiply_to(bool& is_result_int, double& cum_product) const;
  
  /**
   * \brief Divide the value stored in the cell into a cummulative quotient and set
   * the result type to double if any double is involved in the calculation.
   * (error if this is not an IntCell or DoubleCell)
   * \return void.
   */
  virtual void divide_from(bool& is_result_int, double& cum_quotient) const;
  
  /**
   * \brief Find the smallest int larger than the value of this cell.
   * (error if this is not a DoubleCell)
   * \return A pointer to Cell storing the result.
   */
  virtual Cell* ceiling() const;
  
  /**
   * \brief Find the largest int smaller than the value of this cell.
   * (error if this is not a DoubleCell)
   * \return A pointer to Cell storing the result.
   */
  virtual Cell* floor() const;
  
  /**
   * \brief Pure virtual function for printing the subtree rooted at this cell
   * in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const = 0;
  
};

// Reminder: cons.hpp expects nil to be defined somewhere (for this
// implementation, Cell.cpp is the logical place to define it).
// Here we promise this again, just to be safe.
extern Cell* const nil;

#endif // CELL_HPP
