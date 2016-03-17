/**
 * \file DoubleCell.hpp
 *
 * Interface for derived class DoubleCell of abstract base class Cell
 */

#ifndef DOUBLECELL_HPP
#define DOUBLECELL_HPP

#include "Cell.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \class DoubleCell
 * \brief Derived class DoubleCell
 */
class DoubleCell: public Cell {
public:
  
  /**
   * \brief Constructor for initialising DoubleCell class.
   */
  DoubleCell(const double d);
  
  /**
   * \brief Virtual distructor inherited from Cell class.
   */
  virtual ~DoubleCell();
  
  /**
   * \brief Override the default false return to true.
   * \return True always.
   */
  virtual bool is_double() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * This is implemented for the situation when conversion of DoubleCell to int is needed.
   * \return Integer value rounded from the double stored in the cell.
   */
  virtual int get_int() const;
  
  /**
   * \brief Override the default error output to the value of cell
   * \return Double value stored in the cell.
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
   * \brief Override the default error output to do the ceiling operation.
   * \return A pointer to Cell storing the result.
   */
  virtual Cell* ceiling() const;
  
  /**
   * \brief Override the default error output to do the flooring operation.
   * \return A pointer to Cell storing the result.
   */
  virtual Cell* floor() const;
  
  /**
   * \brief Define the pure virtual print function to print the value stored in the cell.
   * \return void.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  double double_m;

};

#endif // DOUBLECELL_HPP
