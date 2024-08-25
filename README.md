# Make++
A general-purpose file manipulation system, like Make, but much more simple in
use. This system is pretty easy to learn and everybody is able to use it, not
only the software developers.

# Synthax

Anything starts from the \# and ends with newline is a comment.
Any line starts from the '|' character is a table line.
All other places are preprocessor commands.

Generally, the script is a table representation of the build dependency graph.
For example we have some source files and willing to make program.elf:

```
compile : $cxx$ -c $left$ -o $right$
link    : $cxx$ $left$ -o $right$
cxx     : g++

| *file1.hpp  | *file1.cpp | >compile | file1.o | >link | program.elf |
| *common.hpp |            |          |         |       |             |
|-------------|------------|----------|---------|       |             |
| *file2.hpp  | *file2.cpp | >compile | file2.o |       |             |
| *common.hpp |            |          |         |       |             |
|-------------|------------|----------|---------|       |             |
| *file3.hpp  | *file3.cpp | >compile | file2.o |       |             |
| *common.hpp |            |          |         |       |             |
```

Look at the 'program.elf' cell and you may naturally identify what you need
to do to build it.

Cells marked with '*' are source files.
Cells marked with '>' are commands that should be described with preprocessor
statements.
All other cells are just files, that build system may generate.
Empty cells duplicate the cell above, if it exists.
Cells filled with '-' are empty cells and has the same behavior.

Preprocessor substitutes if can anything that placed between '$' characters.
Preprocessor subtitution declaration starts with name and after the ':'
character follows what should be substituted.

'$left$' and '$right$' are special substitutions that indicates containment
of the first file from left and first file from right cells of the table
respectively.
