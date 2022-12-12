#include <exception>
#include <iostream>
#include <unordered_map>
#include <vector>

using vectorArgs = std::vector<std::pair<std::string, int>>;

class Arguments {
 public:
  Arguments(vectorArgs vec) {
    for (auto const& item : vec) {
      defaultVal.push_back(item.second);
      argsNames.push_back(item.first);
      argsMap.insert(item);
    }
    argsSize = vec.size();
  }

  int setNewArgs(vectorArgs const& vec) {
    if (!checkUserArgs(vec)) {
      throw std::runtime_error("wrong aruments");
    }
    setDefaultArgs();
    for (auto& i : vec) {
      argsMap[i.first] = i.second;
    }
    return 0;
  };

  std::vector<int> getVals() const {
    std::vector<int> valVec;
    for (auto const& arg : argsMap) {
      valVec.push_back(arg.second);
    }
    return valVec;
  };

  std::vector<int> getDefaultVals() const { return defaultVal; };

 private:
  std::vector<int> defaultVal;
  std::vector<std::string> argsNames;
  vectorArgs userArgs;
  std::unordered_map<std::string, int> argsMap;
  int argsSize = 0;

  std::vector<std::string> getNames() const {
    std::vector<std::string> nameVec;
    for (auto const& arg : argsMap) {
      nameVec.push_back(arg.first);
    }
    return nameVec;
  };

  void setDefaultArgs() {
    for (int i = 0; i < argsSize; ++i) {
      argsMap[argsNames.at(i)] = defaultVal.at(i);
    }
  }

  bool checkUserArgs(vectorArgs const& userArgs) {
    if (userArgs.size() > argsSize) {
      return false;
    }
    for (auto const& arg : userArgs) {
      if (!argsMap.contains(arg.first)) {
        return false;
      }
    }
    return true;
  }
};
