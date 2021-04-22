#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool equ(string l, string m) {
  if (l == m) {
    return true;
  }
  if (l.size() % 2 == 0 && m.size() == l.size()) {
    string l1 = l.substr(0, l.size() / 2);
    string l2 = l.substr(l.size() / 2, l.size());
    string m1 = m.substr(0, m.size() / 2);
    string m2 = m.substr(m.size() / 2, m.size());
    return (equ(l1, m1) && equ(l2, m2)) || (equ(l1, m2) && equ(l2, m1));
  } else {
    return false;
  }
}

int main() {
  string l;
  string m;
  while (cin >> l >> m) {
    cout << (equ(l, m) ? "NepNep!" : "Yinku so sad!") << endl;
  }
}
