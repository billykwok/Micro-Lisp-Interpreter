/**
 * \file SymbolCell.hpp
 *
 * Interface of derived class SymbolCell of abstract base class Cell
 */

#ifndef SYMBOLCELL_HPP
#define SYMBOLCELL_HPP

#include "Cell.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

/**
 * \class SymbolCell
 * \brief Derived class SymbolCell
 */
class SymbolCell: public Cell {
public:
  
  /**
   * \brief Constructor for initialising SymbolCell class.
   */
  SymbolCell(const char* const s);
  
  /**
   * \brief Virtual distructor inherited from Cell class.
   */
  virtual ~SymbolCell();
  
  /**
   * \brief Override the default false return to true.
   * \return True always.
   */
  virtual bool is_symbol() const;
  
  /**
   * \brief Override the default error output to the value of cell.
   * \return String stored in the cell.
   */
  virtual std::string get_symbol() const;
  
  /**
   * \brief Define the pure virtual print function to print the value stored in the cell.
   * \return void.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  char* symbol_m;

};

#endif // SYMBOLCELL_HPP
