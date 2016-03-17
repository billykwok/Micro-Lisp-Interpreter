/**
 * \file ProcedureCell.hpp
 *
 * Interface of derived class ProcedureCell of abstract base class Cell
 */

#ifndef PROCEDURECELL_HPP
#define PROCEDURECELL_HPP

#include "Cell.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \class ProcedureCell
 * \brief Derived class ProcedureCell
 */
class ProcedureCell: public Cell {
public:
  
  /**
   * \brief Proceduretructor for initialising ProcedureCell class.
   */
  ProcedureCell(Cell* const my_formals, Cell* const my_body);
  
  /**
   * \brief Virtual distructor inherited from Cell class.
   */
  virtual ~ProcedureCell();
  
  /**
   * \brief Override the default false return to true.
   * \return True always.
   */
  virtual bool is_procedure() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return Car cell pointer stored in the cell.
   */
  virtual Cell* get_formals() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return Cdr cell pointer stored in the cell.
   */
  virtual Cell* get_body() const;
  
  /**
   * \brief Define the pure virtual print function to print the value stored in the cell.
   * \return void.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  Cell* formals_m;
  Cell* body_m;

};

#endif // PROCEDURECELL_HPP
