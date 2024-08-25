#include <algorithm>
#include "core.hpp"

bool strcomp(std::string a, std::string b) { return a.compare(b) < 0; }

core::core(std::vector<std::vector<std::string>> table) : table(table) {}

static bool find(std::string what, std::list<std::string>& where)
{ for (std::string item : where) { if (what == item) { return true; } }
  return false; }

std::list<std::string> core::targets()
{ std::list<std::string> result;

  for (unsigned int y = 0; y < table.size(); y++)
  { for (unsigned int x = 0; x < table[y].size(); x++)
    { if (table[y][x].empty()) { continue; }
      if (table[y][x].front() == '*') { continue; }
      if (find(table[y][x], result)) { continue; }
      result.push_back(table[y][x]); } }

  result.sort(); return result; }

std::list<std::string> core::files()
{ std::list<std::string> result;

  for (unsigned int y = 0; y < table.size(); y++)
  { for (unsigned int x = 0; x < table[y].size(); x++)
    { if (table[y][x].empty()) { continue; }
      if (table[y][x].front() == '*') { continue; }
      if (table[y][x].front() == '>') { continue; }
      if (find(table[y][x], result)) { continue; }
      result.push_back(table[y][x]); } }

  result.sort(); return result; }
