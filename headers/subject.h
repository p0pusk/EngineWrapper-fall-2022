#include <iostream>

class Subject1 {
 public:
  int Foo(const int a, const int b) {
    std::cout << "[Subject1]: " << a << ", " << b << std::endl;
    return 0;
  }
};

class Subject2 {
 public:
  int Foo(const int a, const int b, const int c) {
    std::cout << "[Subject2]: " << a << ", " << b << ", " << c << std::endl;
    return 0;
  }
};
