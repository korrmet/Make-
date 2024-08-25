#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <map>
#include <vector>

class parser
{ public:
  parser(std::string script);
  std::map<std::string, std::string> expressions;
  std::vector<std::vector<std::string>> table; };

#endif // PARSER_HPP
