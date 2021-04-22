#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(int a, int b) { return a > b; }

int main() {
  int k;
  cin >> k;
  int arr[k];
  for (int i = 0; i < k; i++) {
    int s;
    cin >> s;
    arr[i] = s;
  }
  sort(arr, arr + k, cmp);
  for (int i = 0; i < k; i++) {
    cout << arr[i] << endl;
  }
}
