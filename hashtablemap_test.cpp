#include "hashtablemap.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

void test(const hashtablemap<string, int>& map) {
  for (hashtablemap<string, int>::const_iterator it = map.begin(); it != map.end(); ++it) {
    cout << it->first << endl;
  }
}

int main() {
  cout << "beginning of test" << endl;
  try {
    hashtablemap<string, int> map;
    map.insert(make_pair(string("bbc"), 1));
    map.insert(make_pair(string("aad"), 1));
    map.insert(make_pair(string("def"), 1));
    map.insert(make_pair(string("again"), 1));
    map.insert(make_pair(string("65535"), 1));
    map.insert(make_pair(string("billy"), 1));
    map.print();
    
    cout << endl << "test: non-const iterator" << endl;
    for (hashtablemap<string, int>::iterator it = map.begin(); it != map.end(); ++it) {
      it->second = 0;
      cout << it->first << endl;
    }
    map.print();
    
    cout << endl << "test: const iterator" << endl;
    test(map);
    map.print();

    cout << endl << "test: erase" << endl;
    map.erase("aad");
    map.print();

    cout << endl << "test: count" << endl
	 << map.count("aad") << endl
	 << map.count("def") << endl;

    cout << endl << "test: copy" << endl;
    hashtablemap<string, int> map2;
    map2 = map;
    map.clear();
    map.print();
    map2.print();
    
    cout << endl << "test: clear" << endl;
    map.clear();
    map.print();
    
  } catch (runtime_error err) {
    cerr << err.what() << endl;
  }
  cout << "end of test" << endl;
  return 0;
}
