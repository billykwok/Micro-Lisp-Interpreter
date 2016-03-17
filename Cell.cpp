/**
 * \file Cell.cpp
 *
 * The implementation details of Cell class member functions.
 */

#include "Cell.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

// Reminder: cons.hpp expects nil to be defined somewhere.  For this
// implementation, this is the logical place to define it.
Cell* const nil = NULL;

using namespace std;

// Cell
Cell::Cell()
{

}

Cell::~Cell()
{

}

bool Cell::is_int() const
{
  return false;
}

bool Cell::is_double() const
{
  return false;
}

bool Cell::is_symbol() const
{
  return false;
}

bool Cell::is_cons() const
{
  return false;
}

bool Cell::is_procedure() const
{
  return false;
}

int Cell::get_int() const
{
  throw runtime_error("trying to get int from a non-numeric cell");
}

double Cell::get_double() const
{
  throw runtime_error("trying to get double from a non-numeric cell");
}

string Cell::get_symbol() const
{
  throw runtime_error("trying to get symbol from a non-symbol cell");
}

Cell* Cell::get_car() const
{
  throw runtime_error("trying to get car from a non-cons cell");
}

Cell* Cell::get_cdr() const
{
  throw runtime_error("trying to get cdr from a non-cons cell");
}

Cell* Cell:: get_formals() const
{
  throw runtime_error("trying to get formals from a non-procedure cell");
}

Cell* Cell:: get_body() const
{
  throw runtime_error("trying to get body from a non-procedure cell");
}

void Cell::add_to(bool& is_int, double& cum_sum) const
{
  throw runtime_error("trying to do addition on a non-numeric cell");
}

void Cell::subtract_from(bool& is_int, double& cum_diff) const
{
  throw runtime_error("trying to do subtraction on a non-numeric cell");
}

void Cell::multiply_to(bool& is_int, double& cum_product) const
{
  throw runtime_error("trying to do multiplication on a non-numeric cell");
}

void Cell::divide_from(bool& is_int, double& cum_quotient) const
{
  throw runtime_error("trying to do division on non-numeric cell");
}

Cell* Cell::ceiling() const
{
  throw runtime_error("trying to do ceiling operation on non-double cell");
}

Cell* Cell::floor() const
{
  throw runtime_error("trying to do flooring operation on non-double cell");
}
