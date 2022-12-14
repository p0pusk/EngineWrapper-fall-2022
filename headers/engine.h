#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "wrapper.h"

class Engine {
 public:
  void RegisterCommand(Wrapper const& wrapper, std::string const& command) {
    if (command == "") {
      throw std::runtime_error("[Engine]: Exception, empty command name");
    }
    if (wrappers_map.contains(command)) {
      throw std::runtime_error("[Engine]: Exception, command already exists");
    }
    wrappers_map.insert({command, wrapper});
  }

  int Execute(std::string const& command,
              std::map<std::string, int> const& args) {
    if (!wrappers_map.contains(command)) {
      throw std::runtime_error("[Engine]: Exception, command not registered");
    }
    return wrappers_map.at(command).Run(args);
  }

  int Execute(std::string const& command) {
    if (!wrappers_map.contains(command)) {
      throw std::runtime_error("[Engine]: Exception, command not registered");
    }
    return wrappers_map.at(command).Run();
  }

 private:
  std::unordered_map<std::string, Wrapper> wrappers_map;
};
