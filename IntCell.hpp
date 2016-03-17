/**
 * \file IntCell.hpp
 *
 * Interface of derived class IntCell of abstract base class Cell
 */

#ifndef INTCELL_HPP
#define INTCELL_HPP

#include "Cell.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \class IntCell
 * \brief Derived class IntCell
 */
class IntCell: public Cell {
public:
  
  /**
   * \brief Constructor for initialising IntCell class.
   */
  IntCell(const int i);
  
  /**
   * \brief Virtual distructor inherited from Cell class.
   */
  virtual ~IntCell();
  
  /**
   * \brief Override the default false return to true.
   * \return True always.
   */
  virtual bool is_int() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return Integer value stored in the cell.
   */
  virtual int get_int() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * This is implemented for the situation when conversion of IntCell to double is needed.
   * \return Double value casted from the integer stored in the cell.
   */
  virtual double get_double() const;
  
  /**
   * \brief Override the default error output to do the addition operation.
   * \return void.
   */
  virtual void add_to(bool& is_int, double& cum_sum) const;
  
  /**
   * \brief Override the default error output to do the subtraction operation.
   * \return void.
   */
  virtual void subtract_from(bool& is_int, double& cum_diff) const;
  
  /**
   * \brief Override the default error output to do the multiplication operation.
   * \return void.
   */
  virtual void multiply_to(bool& is_int, double& cum_product) const;
  
  /**
   * \brief Override the default error output to do the division operation.
   * \return void.
   */
  virtual void divide_from(bool& is_int, double& cum_quotient) const;
  
  /**
   * \brief Define the pure virtual print function to print the value stored in the cell.
   * \return void.
   */
  virtual void print(std::ostream& os = std::cout) const;
  
private:
  int int_m;

};

#endif // INTCELL_HPP
