#include "headers/interpreter.hpp"

//Interpreter::~Interpreter() { destroy_ast(this->ast); this->ast = nullptr; }

void Interpreter::run_cli()
{
  std::string src = "";
  std::cout << "Bienvenue sur l'interpréteur du langage NBasic !" << std::endl;
  std::cout << "besoin d'aide ? -> help" << std::endl;
  
  bool run = true;

  do
  {
    std::cout << "> "; std::getline(std::cin, src);
    
    if (src == "exit") run = false;
    else if (src == "clear") system("clear");
    else if (src == "help")
    {
      std::cout << "NBasic help :" << std::endl;
      std::cout << "  1. clear -> néttoie l'affichage de la console" << std::endl;
      std::cout << "  2. exit  -> permet de quitter la console" << std::endl;
      std::cout << "  3. load  -> permet de charger un programme dans l'interpréteur" << std::endl;
      std::cout << "  4. help  -> affiche ce menu d'aide" << std::endl;
      std::cout << "  5. about -> à propos du langage" << std::endl;
    }
    else if (src == "about")
    {
      std::cout << "A propos du 'Not so Basic' : " << std::endl;
    }
    else if (src == "kijetesantakalu li tawa sike")
    {
      std::cout << std::endl;
      std::cout << "      kkkkkkkk" << std::endl;
      std::cout << "     k        k" << std::endl;
      std::cout << "    k         k" << std::endl;
      std::cout << "    k    k  k k" << std::endl;
      std::cout << "    k    k  k  k" << std::endl;
      std::cout << "    k    k  k   k" << std::endl;
      std::cout << "    k          k" << std::endl;
      std::cout << "    k         k" << std::endl;
      std::cout << "    k         k" << std::endl;
      std::cout << "    k         k" << std::endl;
      std::cout << " kkkk         k" << std::endl;
      std::cout << "k k k  k      k" << std::endl;
      std::cout << "k k k   k  k  k" << std::endl;
      std::cout << "k k k   k  k  k" << std::endl;
      std::cout << " kkkkkkkk  k  k" << std::endl;
      std::cout << std::endl;
    }
    else
    {
      this->tokens = tokenize(src); // On découpe l'entrée en token
      print_token(tokens); // On affiche les tokens de l'entrée
      this->program = parser.parse_program(this->tokens);

      // On traite l'arbre de syntaxe courant
      for (size_t i = 0; i < this->program.body.size(); i++) print_ast(this->program.body[i]);
      
      // On le détruit
      for (size_t i = 0; i < this->program.body.size(); i++) destroy_ast(this->program.body[i]);
    }
  }
	while (run);
}

void Interpreter::run_file(std::string& file_name)
{
  std::string src = "";
	src = read_file(file_name);
  tokens = tokenize(src);
  print_token(tokens);
}

std::string Interpreter::read_file(std::string& file_name)
{
  std::ifstream file(file_name);

  if (file.is_open() == false)
  {
    std::string msg = "impossible d'ouvrir le fichier : " + file_name;
    int line = -1;
    print_error(line, msg);
  }

  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
