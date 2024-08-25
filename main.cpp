#include <cstdio>
#include <string>

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
  
  if (cp.command.empty())
  { std::printf("Specify what to do, use \"-h\" or \"--help\" for help.\n");
    return -1; }

  if (cp.clean) { std::printf("Cleaning the project...\n"); return 0; }
  if (cp.list) { std::printf("Available targets are:\n"); return 0; }
  if (cp.reset) { std::printf("Reset the project...\n"); return 0; }

  return 0; }
