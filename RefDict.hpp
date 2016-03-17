#include "Cell.hpp"
#include "hashtablemap.hpp"
#include <map>
#include <utility>
#include <stdexcept>

/**
 * \class RefDict
 * \brief Class RefDict. A class containing the map storing the defined symbol of the scheme
 * function.
 */
class RefDict {
  
public:

  /**
   * \brief Type definition of map with string key and Cell* value
   */
  typedef hashtablemap<string, Cell*> RefMap;

  /**
   * \brief Type definition of pair with string key and Cell* value
   */
  typedef pair<string, Cell*> RefPair;

  /**
   * \brief Type definition of iterator of RefMap
   */
  typedef RefMap::iterator RefIter;
  
  /**
   * \brief Type definition of the enum tagging whether the map is global or local
   */
  typedef enum e_scope {SCOPE_GLOBAL, SCOPE_LOCAL} Scope;

  /**
   * \brief Constructor of the RefDict. A tag should be provided and default is
   * SCOPE_LOCAL.
   */
  RefDict(Scope scope = SCOPE_LOCAL)
  {
    if (scope == SCOPE_GLOBAL) {
      map_m["+"] = new SymbolCell("+");
      map_m["-"] = new SymbolCell("-");
      map_m["*"] = new SymbolCell("*");
      map_m["/"] = new SymbolCell("/");
      map_m["ceiling"] = new SymbolCell("ceiling");
      map_m["floor"] = new SymbolCell("floor");
      map_m["quote"] = new SymbolCell("quote");
      map_m["if"] = new SymbolCell("if");
      map_m["cons"] = new SymbolCell("cons");
      map_m["car"] = new SymbolCell("car");
      map_m["cdr"] = new SymbolCell("cdr");
      map_m["nullp"] = new SymbolCell("nullp");
      map_m["symbolp"] = new SymbolCell("symbolp");
      map_m["intp"] = new SymbolCell("intp");
      map_m["doublep"] = new SymbolCell("doublep");
      map_m["listp"] = new SymbolCell("listp");
      map_m["procedurep"] = new SymbolCell("procedurep");
      map_m["define"] = new SymbolCell("define");
      map_m["<"] = new SymbolCell("<");
      map_m["not"] = new SymbolCell("not");
      map_m["print"] = new SymbolCell("print");
      map_m["eval"] = new SymbolCell("eval");
      map_m["lambda"] = new SymbolCell("lambda");
      map_m["apply"] = new SymbolCell("apply");
      map_m["let"] = new SymbolCell("let");
    }
  }

  /**
   * \brief Destructor of RefDict.
   */
  ~RefDict() {
    clear();
  }
  
  /**
   * \brief Look up the value stored in a symbol cell as a key in the map.
   * (error if c does not hold well-formed arguments)
   *
   * \return A pointer to the SymbolCell corresponding to the key.
   */
  RefIter lookup(Cell* const c) throw (runtime_error)
  {
    return lookup(c->get_symbol());
  }
  
  /**
   * \brief Look up a string as a key in the map.
   * (error if c does not hold well-formed arguments)
   *
   * \return A pointer to the SymbolCell corresponding to the key.
   */
  RefIter lookup(const string& s) throw (runtime_error)
  {
    return map_m.find(s);
  }

  /** 
   * \brief Get an iterator pointing to the first element of list.
   * \return An iterator of the map.
   */
  RefIter begin()
  {
    return map_m.begin();
  }
  
  /** 
   * \brief Get an iterator pointing to the last element of list.
   * \return An iterator of the map.
   */
  RefIter end()
  {
    return map_m.end();
  }
  
   /** 
   * \brief Insert a string stored in a given symbol cell as key with
   * value v onto the map
   * \return Result of the insertion. True if success, false if failure
   */
  RefIter insert(Cell* const k, Cell* const v)
  {
    return insert(k->get_symbol(), v);
  }

  /**
   * \brief Insert a string as a key with value v onto the map
   * \return Result of the insertion. True if success, false if failure
   */
  RefIter insert(const string s, Cell* const c)
  {
    return insert(make_pair(s, c));
  }

  /**
   * \brief Insert a pair of string and Cell* onto the map
   * \return Result of the insertion. True if success, false if failure
   */
  RefIter insert(RefPair ref_pair)
  {
    pair<RefIter, bool> p = map_m.insert(ref_pair);
    if (!p.second) {
      throw runtime_error("the symbol (\"" + ref_pair.first + "\") is already defined");
    }
    return p.first;
  }

  /**
   * \brief Get the size of map.
   * \return An integer storing the size.
   */
  int size()
  {
    return map_m.size();
  }

  /**
   * \brief Clearing the map.
   * \return Void.
   */
  void clear() {
    map_m.clear();
  }

  /**
   * \brief Print out all data inside the map.
   * \return Void.
   */
  void print()
  {
    for (RefIter it = map_m.begin(); it != map_m.end(); ++it) {
      cout << it->first << ": ";
      if (nullp(it->second)) {
	cout << "()";
      } else {
	it->second->print(cout);
      }
      cout << endl;
    }
  }
  
private:
  RefMap map_m;
  
};
