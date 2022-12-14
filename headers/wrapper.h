#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Wrapper {
 public:
  Wrapper() = delete;

  template <typename Subject, typename... Args>
  Wrapper(Subject* sub, int (Subject::*func)(Args...),
          std::map<std::string, int> const& args) {
    default_args = args;
    function = [this, sub, func](std::vector<int> const& func_args) {
      return ExecuteFunction(sub, func, func_args,
                             std::make_index_sequence<sizeof...(Args)>{});
    };
  }

  int Run(std::map<std::string, int> const& vec) {
    if (!CheckArguments(vec)) {
      throw std::runtime_error("[Wrapper]: Exception, invalid argument");
      return -1;
    }

    std::vector<int> new_args;
    for (auto const& item : default_args) {
      auto search = vec.find(item.first);
      if (search != vec.end()) {
        new_args.push_back(search->second);
      } else {
        new_args.push_back(item.second);
      }
    }

    return function(new_args);
  }

  int Run() {
    std::vector<int> run_args;
    for (auto const& item : default_args) {
      run_args.push_back(item.second);
    }
    return function(run_args);
  }

 private:
  std::map<std::string, int> default_args;
  std::function<int(std::vector<int> const& args)> function;

  template <typename Subject, typename Function, size_t... I>
  int ExecuteFunction(Subject* sub, Function func, std::vector<int> const& args,
                      std::index_sequence<I...>) {
    return (sub->*func)(args[I]...);
  }

  bool CheckArguments(std::map<std::string, int> args) {
    for (auto const& item : args) {
      if (!default_args.contains(item.first)) return false;
    }
    return true;
  }
};
