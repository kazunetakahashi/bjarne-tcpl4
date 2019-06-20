/*
  binary tree
  to practice using pointers.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
using namespace std;

template <class T>
class Tree
{
public:
  shared_ptr<Tree> left;
  shared_ptr<Tree> right;
  T value;

  Tree() : left(nullptr), right(nullptr), value(){};
};

Tree<int> T;

void init_sub(shared_ptr<Tree<int>> pt, int &N)
{
  int t;
  t = pt->value * 2;
  if (t <= N)
  {
    pt->left = shared_ptr<Tree<int>>{new Tree<int>};
    pt->left->value = t;
    init_sub(pt->left, N);
  }
  t = pt->value * 2 + 1;
  if (t <= N)
  {
    pt->right = shared_ptr<Tree<int>>{new Tree<int>};
    pt->right->value = t;
    init_sub(pt->right, N);
  }
}

Tree<int> init(int N)
{
  if (N < 1)
  {
    exit(1);
  }
  shared_ptr<Tree<int>> pt{new Tree<int>};
  pt->value = 1;
  init_sub(pt, N);
  return *pt;
}

bool search(int x)
{
  Tree<int> *pt = &T;
  int ind = 0;
  for (auto i = 32 - 1; i >= 0; i--)
  {
    if (x >> i & 1)
    {
      ind = i;
      break;
    }
  }
  for (auto i = ind - 1; i >= 0; i--)
  {
    if (x >> i & 1)
    {
      pt = pt->right.get();
    }
    else
    {
      pt = pt->left.get();
    }
    if (!pt)
    {
      return false;
    }
  }
  assert(pt->value == x);
  return true;
}

int maxi()
{
  Tree<int> *pt = &T;
  int x = 3;
  while (pt->right)
  {
    pt = pt->right.get();
    x <<= 1;
    x += 1;
  }
  return x;
}

int size()
{
  int ok = 1;
  int ng = maxi();
  while (abs(ok - ng) > 1)
  {
    int t = (ok + ng) / 2;
    if (search(t))
    {
      ok = t;
    }
    else
    {
      ng = t;
    }
  }
  return ok;
}

void test_size()
{
  int n;
  cin >> n;
  for (auto i = 1; i < n; i++)
  {
    T = init(i);
    cout << "construct " << i << endl;
    cout << "maxi " << maxi() << endl;
    cout << "size " << size() << endl;
  }
}

void test_search()
{
  int n;
  cin >> n;
  for (auto i = 1; i < n; i++)
  {
    T = init(i);
    cout << "construct " << i << endl;
    if (search(i))
    {
      cout << "found " << i << endl;
    }
    if (search(i + 1))
    {
      cout << "found " << i + 1 << endl;
    }
  }
}

int main()
{
  test_size();
}