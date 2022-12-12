#include <iostream>

class Subject {
 public:
  Subject() = default;

  void print(int const& a) { std::cout << a << std::endl; }

  int foo(const int a, const int b) {
    std::cout << "first " << a << " second " << b << std::endl;
    return 0;
  }
};

class Subject2 {
 public:
  Subject2() = default;

  void print(int const& a) { std::cout << a << std::endl; }

  int foo2(const int a, const int b, const int c) {
    std::cout << "first " << a << " second " << b << " third " << c
              << std::endl;
    return 0;
  }
};
