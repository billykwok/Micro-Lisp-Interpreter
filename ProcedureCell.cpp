/**
 * \file ProcedureCell.cpp
 *
 * The implementation details of ProcedureCell class member functions.
 */

#include "ProcedureCell.hpp"
#include <iostream>

using namespace std;

ProcedureCell::ProcedureCell(Cell* const my_formals, Cell* const my_body)
  :Cell(), formals_m(my_formals), body_m(my_body)
{
  
}

ProcedureCell::~ProcedureCell()
{

}

bool ProcedureCell::is_procedure() const
{
  return true;
}

Cell* ProcedureCell::get_formals() const
{
  return formals_m;
}

Cell* ProcedureCell::get_body() const
{
  return body_m;
}

void ProcedureCell::print(ostream& os) const
{
  os << "#<function>";
}
