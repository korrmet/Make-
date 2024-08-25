#include "parser.hpp"

static std::string del_trailing_spaces(std::string str)
{ while (str.size() && str.front() <= ' ') { str.erase(0, 1); }
  while (str.size() && str.back()  <= ' ') { str.pop_back(); }
  return str; }

static std::string normalize_field(std::string str)
{ str = del_trailing_spaces(str);
  bool dash_only = true;
  for (char c : str) { if (c != '-') { dash_only = false; return ""; } }
  return str; }

parser::parser(std::string script)
{ if (!script.size()) { return; }
  if (script.back() != '\n') { script.push_back('\n'); }
  
  bool is_comment = false;
  bool nl = true;
  bool is_table = false;
  std::string curr;
  std::string var;

  for (char c : script)
  { if (!is_comment && c == '#') { is_comment = true; continue; }
    if (is_comment && c == '\n') { is_comment = false; nl = true; continue; }
    if (is_comment) { continue; }

    if (c == '\n') { nl = true; }
    else if (nl && c == '|') { is_table = true; nl = false; continue; }
    else if (nl && c != '|') { is_table = false; nl = false; }

    if (is_table)
    { if (!table.size()) { table.push_back(std::vector<std::string>()); }
      
      if      (c == '\n') { table.push_back(std::vector<std::string>());
                            continue; }
      else if (c == '|' ) { table.back().push_back(normalize_field(curr));
                            curr.clear(); continue; } }
    else
    { if (c == ':') { var = del_trailing_spaces(curr); curr.clear(); continue; }
      if (c == '\n')
      { curr = del_trailing_spaces(curr); if (!curr.size()) { continue; }
        expressions.insert(std::pair<std::string, std::string>(var, curr));
        curr.clear(); continue; } }

    curr.push_back(c); } }
