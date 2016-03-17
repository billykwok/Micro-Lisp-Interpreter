/**
 * \file ConsCell.cpp
 *
 * The implementation details of ConsCell class member functions.
 */

#include "ConsCell.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr)
  :Cell(), car_m(my_car), cdr_m(my_cdr)
{
  
}

ConsCell::~ConsCell()
{

}

bool ConsCell::is_cons() const
{
  return true;
}

Cell* ConsCell::get_car() const
{
  return car_m;
}

Cell* ConsCell::get_cdr() const
{
  return cdr_m;
}

void ConsCell::print(ostream& os) const
{
  os << "(";
  const Cell* temp_c = this;
  while (temp_c != nil) {
    temp_c->get_car()->print(os);
    temp_c = temp_c->get_cdr();
    if (temp_c != nil) {
      os << " ";
    }
  }
  
  os << ")";
  
}
