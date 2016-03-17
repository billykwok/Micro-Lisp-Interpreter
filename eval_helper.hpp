#include "cons.hpp"
#include <string>
#include <stdexcept>

/**
 * \brief Find the size of list starting from c.
 *
 * \return The number of cells.
 */
int size(Cell* const c) throw (runtime_error)
{
  if (!listp(c)) {
    throw runtime_error("passing non-cons cell to size()");
  }
  Cell* temp_c = c;
  int counter = 0;
  
  // loop through the list starting from c
  while (!nullp(temp_c)) {
    ++counter;
    temp_c = cdr(temp_c);
  }
  
  return counter;
}

/**
 * \brief Convert an integer to string.
 *
 * \return The result string.
 */
string to_str(int i) throw (runtime_error)
{
  ostringstream oss;
  oss << i;
  return oss.str();
}
/**
 * \brief Check whether the number of argument(s) matches the given range.
 * Throw a runtime exception if not matched. 
 *
 * \return void.
 */
void check_argn(int min, int max, int actual) throw (runtime_error)
{
  if (actual < min || actual > max) {
    if (min == max) {
      throw runtime_error("bad argument count - expected " + to_str(min) + " but received " + to_str(actual));
    } else {
      throw runtime_error("bad argument count - expected " + to_str(min) + " to " + to_str(max) + " but received " + to_str(actual));
    }
  }
}

void check_argn(int min, int actual) throw (runtime_error)
{
  if (actual < min) {
    throw runtime_error("bad argument count - expected at least" + to_str(min) + " but received " + to_str(actual));
  }
}
