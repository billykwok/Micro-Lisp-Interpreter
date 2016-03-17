/**
 * \file IntCell.cpp
 *
 * The implementation details of IntCell class member functions.
 */

#include "IntCell.hpp"
#include <iostream>
#include <iomanip>

IntCell::IntCell(const int i)
  :Cell(), int_m(i)
{
  
}

IntCell::~IntCell()
{
  
}

bool IntCell::is_int() const
{
  return true;
}

int IntCell::get_int() const
{
  return int_m;
}

double IntCell::get_double() const
{
  return (double) get_int();
}

void IntCell::add_to(bool& is_int, double& cum_sum) const
{
  cum_sum += get_int();
}

void IntCell::subtract_from(bool& is_int, double& cum_diff) const
{
  cum_diff -= get_int();
}

void IntCell::multiply_to(bool& is_int, double& cum_product) const
{
  cum_product *= get_int();
}

void IntCell::divide_from(bool& is_int, double& cum_quotient) const
{
  if (get_int() == 0) {
    throw std::runtime_error("divided by 0");
  }
  cum_quotient /= get_int();
}

void IntCell::print(std::ostream& os) const
{
  os << get_int();
}
