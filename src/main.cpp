#include <iostream>

#include "engine.h"
#include "subject.h"

int main() {
  Engine engine;
  Subject1* sub = new Subject1;
  Wrapper wrapper1(sub, &Subject1::Foo, {{"first", 1}, {"second", 2}});
  Subject2* sub2 = new Subject2;
  Wrapper wrapper2(sub2, &Subject2::Foo,
                   {{"one", 5}, {"two", 6}, {"three", 7}});

  // OK
  try {
    engine.RegisterCommand(wrapper1, "command1");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\nRegistering existing command:\n";
  try {
    engine.RegisterCommand(wrapper2, "command1");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // OK
  try {
    engine.RegisterCommand(wrapper2, "command2");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\nInvalid command name:\n";
  try {
    engine.Execute("command1", {{"something_else", 66}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\nExecuting with default args:\n";
  try {
    engine.Execute("command1");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\nExecuting with custom args:\n";
  try {
    engine.Execute("command1", {{"first", 15}, {"second", 23}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "\nExecuting with partial custom args:\n";
  try {
    engine.Execute("command2", {{"one", 66}, {"two", 77}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  delete sub;
  delete sub2;
  return 0;
}
