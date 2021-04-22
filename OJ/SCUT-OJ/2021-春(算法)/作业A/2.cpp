#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int k;
  cin >> k;
  int arr[k];
  for (int i = 0; i < k; i++) {
    int s;
    cin >> s;
    arr[i] = s;
  }
  int as;
  cin >> as;
  while (as--) {
    int x, y;
    cin >> x >> y;
    int maxp = 0;
    for (int i = x - 1; i < y; i++) {
      maxp = max(maxp, arr[i]);
    }
    cout << maxp << endl;
  }
}
