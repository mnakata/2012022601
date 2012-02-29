#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include <iostream>
#include <cstdlib>


class EllysNumbers {
public:
  long long getSubsets(long long n, std::vector<std::string> special);

private:
  long long search(long long n, int i, long long excl);

private:
  std::vector<long long> integers_;
  
private:
  static bool is_relatively_prime(long long a, long long b);
};

long long EllysNumbers::getSubsets(long long n, std::vector<std::string> special)
{
  std::stringstream ss;

  for (std::vector<std::string>::iterator it = special.begin(); it != special.end(); ++ it)
    ss << *it;

  while (! ss.eof()) {
    long long l;

    ss >> l;

    integers_.push_back(l);
  }

  return search(n, 0, 0);
}

long long EllysNumbers::search(long long n, int i, long long excl)
{
  int size = integers_.size();

  if (n == 1)
    return 1;

  if (i == size)
    return 0;

  long long c = 0;

  if ((excl & static_cast<long long>(1) << i) == 0) {
    long long l = integers_[i];
  
    if (l <= n && n % l == 0) {
      long long e = excl;

      for (int j = i + 1; j < size; j ++)
	if (! is_relatively_prime(l, integers_[j]))
	  e |= static_cast<long long>(1) << j;

      c += search(n / l, i + 1, e);
    }
  }
  
  c += search(n, i + 1, excl);

  return c;
}

bool EllysNumbers::is_relatively_prime(long long a, long long b)
{
  if (a % 2 == 0 && b % 2 == 0)
    return false;
  
  if (a > b)
    std::swap(a, b);

  long long max = std::min(a, static_cast<long long>(sqrt(b) + 0.5));
  
  for (long long i = 3; i <= max; i += 2)
    if (a % i == 0 && b % i == 0)
      return false;

  return true;
}

int main(int argc, char** argv)
{
  long long                n;
  std::vector<std::string> special;
  long long                a;
  long long                b;

  n = 12LL;
  special.clear();
  special.push_back("4 2 5 6 3");
  a = 1LL;

  b = EllysNumbers().getSubsets(n, special);

  std::cerr << b << std::endl;

  if (a != b)
    exit(1);

  n = 42LL;
  special.clear();
  special.push_back("1 2 3 4 5 6 7 13 14 21 42");
  a = 10LL;

  b = EllysNumbers().getSubsets(n, special);

  std::cerr << b << std::endl;

  if (a != b)
    exit(1);

  n = 1337LL;
  special.clear();
  special.push_back("1 13 42 666 2674");
  a = 0LL;

  b = EllysNumbers().getSubsets(n, special);

  std::cerr << b << std::endl;

  if (a != b)
    exit(1);

  n = 1073741824LL;
  special.clear();
  special.push_back("1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1");
  special.push_back("6384 32768 65536 131072 262144 524288 1048576 2097");
  special.push_back("152 4194304 8388608 16777216 33554432 67108864 134");
  special.push_back("217728 268435456 536870912");
  a = 0LL;

  b = EllysNumbers().getSubsets(n, special);

  std::cerr << b << std::endl;

  if (a != b)
    exit(1);

  n = 7420738134810LL;
  special.clear();
  special.push_back("435 625199055 4199 33263 17 222870 284870433 72093");
  special.push_back("2379 7 11 31 247110827 23 1771 81809 851968487 13 ");
  special.push_back("476379795 1001 5 435274114 38264554 7429 239906525");
  special.push_back(" 3 227183706 887045414 606786670 3795 797605175 29");
  special.push_back(" 30 747186719 19 2 562347843 74 2294 588002688 743");
  special.push_back("6429 703 591740547 36657492 37 444178205 1002001 2");
  special.push_back("17626404");
  a = 110LL;

  b = EllysNumbers().getSubsets(n, special);

  std::cerr << b << std::endl;

  if (a != b)
    exit(1);
}
