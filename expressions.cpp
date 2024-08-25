#include "expressions.hpp"

expressions::expressions(std::map<std::string, std::string> dictionary)
  : dictionary(dictionary) {}

std::string expressions::expand(std::string expression)
{ std::string result;

  std::string exp; bool in_exp = false; bool escape = false;
  for (char c : expression)
  { if (escape) { result.push_back(c); escape = false; continue; }
    if (c == '\\') { escape = true; continue; }

    if (c == '$' && !in_exp) { in_exp = true; continue; }
    if (in_exp)
    { if (c == '$')
      { if (dictionary.count(exp)) { result.append(expand(dictionary[exp])); }
        else { result.append("$").append(exp).append("$"); }
        in_exp = false; exp.clear(); continue; }
      exp.push_back(c); continue; }

    result.push_back(c); }
  
  return result; }
