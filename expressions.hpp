#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <string>
#include <map>

class expressions
{ public:
  expressions(std::map<std::string, std::string> dictionary);
  std::string expand(std::string expression);

  private:
  std::map<std::string, std::string> dictionary;
};

#endif // EXPRESSIONS_HPP
