/**
 * \file DoubleCell.cpp
 *
 * The implementation details of DoubleCell class member functions.
 */

#include "DoubleCell.hpp"
#include "IntCell.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

DoubleCell::DoubleCell(const double d)
  :Cell(), double_m(d)
{
  
}

DoubleCell::~DoubleCell()
{

}

bool DoubleCell::is_double() const
{
  return true;
}

int DoubleCell::get_int() const
{
  return (int) round(get_double());
}

double DoubleCell::get_double() const
{
  return double_m;
}

void DoubleCell::add_to(bool& is_int, double& cum_sum) const
{
  if (is_int) {
    is_int = false;
  }
  cum_sum += get_double();
}

void DoubleCell::subtract_from(bool& is_int, double& cum_diff) const
{
  if (is_int) {
    is_int = false;
  }
  cum_diff -= get_double();
}

void DoubleCell::multiply_to(bool& is_int, double& cum_product) const
{
  if (is_int) {
    is_int = false;
  }
  cum_product *= get_double();
}

void DoubleCell::divide_from(bool& is_int, double& cum_quotient) const
{
  if (is_int) {
    is_int = false;
  }
  cum_quotient /= get_double();
}

Cell* DoubleCell::ceiling() const
{
  return new IntCell( (int) std::ceil(get_double()) );
}

Cell* DoubleCell::floor() const
{
  return new IntCell( (int) std::floor(get_double()) );
}

void DoubleCell::print(std::ostream& os) const
{
  if (trunc(get_double()) == get_double()) { // if sth like x.0 is printed
    // print "x.0" instead of "x"
    os << std::fixed << std::setprecision(1);
  } else {
    // print at most 6 sig fig as default
    os << std::resetiosflags(std::ios::fixed) << std::setprecision(6);
  }
  os << get_double();
}
