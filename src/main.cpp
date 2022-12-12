#include <iostream>

#include "engine.h"
#include "subject.h"

int main() {
  Engine engine;
  Subject* sub = new Subject;
  Wrapper wrapper1(sub, &Subject::foo, {{"first", 1}, {"second", 2}});
  Subject2* sub2 = new Subject2;
  Wrapper wrapper2(sub2, &Subject2::foo2,
                   {{"firstStr", 5}, {"secondStr", 6}, {"thirdStr", 7}});

  // OK
  try {
    engine.registerCommand(wrapper1, "command1");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // ERROR: not correct command name
  try {
    engine.registerCommand(wrapper2, "");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // OK
  try {
    engine.registerCommand(wrapper2, "command2");
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // ERROR: not correct arguments' names
  try {
    engine.execute("command1", {{"secondStr", 66}, {"thirdStr", 77}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // OK: all args are from user
  try {
    engine.execute("command1", {{"first", 15}, {"second", 23}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // ERROR: too many args
  try {
    engine.execute("command1", {{"first", 66}, {"second", 12}, {"third", 77}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  // OK: reverse args order, some args are from users, others by default
  try {
    engine.execute("command2", {{"firstStr", 66}, {"thirdStr", 77}});
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  delete sub;
  delete sub2;
  return 0;
}
