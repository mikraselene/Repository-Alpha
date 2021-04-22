#include <cmath>
#include <iostream>

using namespace std;

using ll = long long;

ll sum;
ll cnt;
ll lb;
ll rb;

void func(ll a) {
  if (cnt > rb) {
    return;
  }
  ll d;
  if (a < 2) {
    d = 1;
  } else {
    ll c = log2(a);
    d = pow(2, c + 1) - 1;
  }
  if (lb > cnt && cnt + d <= lb) {
    cnt += d;
    return;
  }
  if (cnt >= lb && rb - cnt + 1 >= d) {
    sum += a;
    cnt += d;
    return;
  }
  if (a < 2) {
    cnt++;
    if (cnt >= lb && cnt <= rb) {
      sum += a;
    }
    return;
  } else {
    func(a / 2);
    func(a / 2);
    func(a % 2);
  }
}

int main() {
  int k;
  cin >> k;
  while (k--) {
    sum = 0;
    cnt = 1;
    ll s;
    cin >> s >> lb >> rb;
    func(s);
    cout << sum << endl;
  }
  return 0;
}
