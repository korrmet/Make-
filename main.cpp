#include <cstdio>
#include <string>
#include "Independency/independency.hpp"
#include "parser.hpp"
#include "expressions.hpp"
#include "core.hpp"

#define root independency::path()

class cli_parser
{ public:
  cli_parser(int argc, char** argv)
    : help(false), clean(false), list(false), reset(false)
  { for (int i = 1; i < argc; i++)
    { if (std::string("--help") == argv[i] ||
          std::string("-h") == argv[i]) { help = true; return; } }

    if (argc >= 2) { filename = argv[1]; }
    if (argc >= 3) { command  = argv[2]; }
    
    if      (command == "clean") { clean = true; }
    else if (command == "list")  { list  = true; }
    else if (command == "reset") { reset = true; } }

  std::string filename, command;
  bool help, clean, list, reset; };

const char* help =
"Make++ build system\n"
"Usage: mpp <filename> <command>\n"
"       filename - path to the build script\n"
"       command  - what to do with the file, possible values are:\n"
"                  clean - deletes all the files that not marked as source,\n"
"                  list  - lists the possible targets to build,\n"
"                  reset - perform clean and delete checksum file.\n"
"                  All other commands are interpreted as build target.\n"
;

int main(int argc, char** argv)
{ cli_parser cp(argc, argv);
  
  if (cp.help) { std::printf("%s", help); return 0; }
  
  if (cp.filename.empty())
  { std::printf("Specify build script, use \"-h\" or \"--help\" for help.\n");
    return -1; }

  independency::file file(cp.filename);
  if (!file)
  { std::printf("Can't open \"%s\"\n", cp.filename.c_str());
    return -1; }

  parser p(file.read()); core c(p.table);
  
  if (cp.command.empty())
  { std::printf("Specify what to do, use \"-h\" or \"--help\" for help.\n");
    return -1; }

  if (cp.clean)
  { std::printf("Cleaning the project...\n");
    for (std::string f : c.files())
    { independency::file candidate(f); if (!candidate) { continue; }
      std::printf("- %s\n", f.c_str()); candidate.del(); }
    return 0; }

  if (cp.reset)
  { std::printf("Reset the project...\n");
    for (std::string f : c.files())
    { independency::file candidate(f); if (!candidate) { continue; }
      std::printf("- %s\n", f.c_str()); candidate.del(); }
    std::string cksums = "."; cksums.append(cp.filename).append(".cks");
    if (!!independency::file(cksums)) 
    { std::printf("- %s\n", cksums.c_str()); independency::file(cksums).del(); }
    return 0; }

  if (cp.list)
  { std::printf("Available targets are:\n");
    for (std::string tgt : c.targets()) { std::printf("%s\n", tgt.c_str()); }
    return 0; }

  // The actual build process starts here
  std::string cksums_file = "."; cksums_file.append(cp.filename).append(".cks");
  independency::file cksums(cksums_file);

  independency::storage prev, now;
  
  prev.parse(cksums.read());
  
  for (std::string s : c.sources())
  { now[root / s] = c.ckstr(independency::file(s).read()); }
  if (!cksums.write(now.serialize()))
  { std::printf("Can't write cksum file\n"); }

  std::list<std::string> changed;

  for (std::string s : now.ls(root))
  { if (!prev.chk(root / s)) { changed.push_back(s); continue; }
    if (prev[root / s] != now[root / s]) { changed.push_back(s); continue; } }

  return 0; }
