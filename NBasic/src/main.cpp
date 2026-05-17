#include "interpreter/interpreter.hpp"
#include <string>

int main(int argc, char *argv[])
{
  Interpreter interpreter;
  
  if (argc == 1) interpreter.run_cli();
  else
  {
    std::string file_name = argv[1];
    interpreter.run_file(file_name);
  }

  return 0;
}
