#include "String.h"
#include "String.cpp"

// https://atcoder.jp/contests/abc128/tasks/abc128_b

#include <tuple>
#include <vector>
#include <algorithm>

using restaurant = std::tuple<String, int, int>;

int main()
{
  int N;
  std::cin >> N;
  std::vector<restaurant> V;
  for (auto i = 0; i < N; i++)
  {
    String S;
    int P;
    std::cin >> S >> P;
    V.push_back(restaurant(S, -P, i + 1));
  }
  std::sort(V.begin(), V.end());
  for (auto x : V)
  {
    std::cout << std::get<2>(x) << std::endl;
  }
}