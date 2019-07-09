/**
 * File    : main.cpp
 * Author  : Kazune Takahashi
 * Created : 7/9/2019, 10:47:47 PM
 * Powered by Visual Studio Code
 */

#include "String.h"
#include "String.cpp"

// https://atcoder.jp/contests/abc126/tasks/abc126_a

int main()
{
  int N, K;
  String S;
  std::cin >> N >> K >> S;
  S[K - 1] = tolower(S[K - 1]);
  std::cout << S << std::endl;
}