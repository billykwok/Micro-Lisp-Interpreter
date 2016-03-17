/**
 * \file ConsCell.hpp
 *
 * Interface of derived class ConsCell of abstract base class Cell
 */

#ifndef CONSCELL_HPP
#define CONSCELL_HPP

#include "Cell.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \class ConsCell
 * \brief Derived class ConsCell
 */
class ConsCell: public Cell {
public:
  
  /**
   * \brief Constructor for initialising ConsCell class.
   */
  ConsCell(Cell* const my_car, Cell* const my_cdr);
  
  /**
   * \brief Virtual distructor inherited from Cell class.
   */
  virtual ~ConsCell();
  
  /**
   * \brief Override the default false return to true.
   * \return True always.
   */
  virtual bool is_cons() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return Car cell pointer stored in the cell.
   */
  virtual Cell* get_car() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return Cdr cell pointer stored in the cell.
   */
  virtual Cell* get_cdr() const;
  
  /**
   * \brief Define the pure virtual print function to print the value stored in the cell.
   * \return void.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  Cell* car_m;
  Cell* cdr_m;

};

#endif // CONSCELL_HPP
