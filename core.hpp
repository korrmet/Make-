#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <string>
#include <list>

class core
{ public:
  core(std::vector<std::vector<std::string>> table);
  std::list<std::string> targets();
  std::list<std::string> files();
  std::list<std::string> sources();
  std::string ckstr(std::string text);

  private:
  std::vector<std::vector<std::string>> table;
};

#endif // CORE_HPP
