#include <iostream>
#include <memory>

template <typename T, typename A = std::allocator<T>>
class vector
{
private:
  T *elem;  // 先頭
  T *space; // 拡張用領域の先頭
  T *last;  // 終端
  A alloc;

public:
  using size_type = typename A::size_type; // vector 要素用の型
  explicit vector(size_type n, const T &val = T(), const A &a = A());

  ~vector();

  vector(const vector &a);             // コピーコンストラクタ
  vector &operator=(const vector &a);  // コピー代入演算子

  vector(vector &&a);            // ムーブコンストラクタ
  vector &operator=(vector &&a); // ムーブ代入演算子

  size_type size() const { return space - elem; }
  size_type capacity() const { return last - elem; }
  void reserve(size_type n);                // 容量を n まで増やす
  void resize(size_type n, const T & = {}); // 要素数を n に変更
  void push_back(const T &);                // 末尾に要素を追加
};

/*
template <typename T, typename A>
vector<T, A>::vector(size_type n, const T &val, const A &a) : alloc{a}
{
  elem = alloc.allocate(n); // 要素用のメモリを取得 ここで失敗しても問題ない
  std::iterator<T, A> p;
  try
  {
    std::iterator<T, A> end = elem + n;
    for (p = elem; p != end; ++p)
    {
      a.construct(p, val); // メモリ上に順番に要素を構築
    }
    last = space = p;
  }
  catch (...)
  { // 失敗したら、構築したところまでは確実に解体する
    for (std::iterator<T, A> q = elem; q != p; q++)
    {
      alloc.destroy(q);
    }
    alloc.deallocate(elem, n); // メモリ解放
    throw;
  }
}
*/

template <typename T, typename A>
vector<T, A>::vector(size_type n, const T &val, const A &a) : alloc{a}
{
  elem = alloc.allocate(n);
  std::iterator<T, A> p;
  try
  {
    std::uninitialized_fill(elem, elem + n, val); // 上記のやつの std 版
    space = last = elem + n;
  }
  catch (...)
  {
    alloc.deallocate(elem, n);
    throw;
  }
}

int main()
{

}