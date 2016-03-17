/**
 * \file SymbolCell.cpp
 *
 * The implementation details of SymbolCell class member functions.
 */

#include "SymbolCell.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

SymbolCell::SymbolCell(const char* const s)
  :Cell(), symbol_m(strdup(s))
{
  
}

SymbolCell::~SymbolCell()
{

}

bool SymbolCell::is_symbol() const
{
  return true;
}

string SymbolCell::get_symbol() const
{
  return symbol_m;
}

void SymbolCell::print(ostream& os) const
{
  os << get_symbol();
}
