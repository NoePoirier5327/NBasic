#include "headers/ast.hpp"
#include "headers/token.hpp"
#include "headers/parser.hpp"
#include <fstream>
#include <sstream>

std::string read_file(std::string& file_name);

int main(int argc, char *argv[])
{
  Queue tokens;
  std::string src = "";
  Node* node = nullptr;
  Parser parser;

  // Si on a 1 argument pour le fichier, on lance l'interpréteur
  if (argc == 1) 
  {
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
        tokens = tokenize(src); // On découpe l'entrée en token
        print_token(tokens); // On affiche les tokens de l'entrée
        node = parser.parse_statement(tokens);
        //print_ast(node);
        destroy_ast(node); node = nullptr;
      }
    }
    while (run);
  }
  else // Sinon ça veut dire qu'on a un fichier à interpréter
  {
    std::string file_name = argv[1];
    src = read_file(file_name);
    tokens = tokenize(src);
    print_token(tokens);
    node = parser.parse_statement(tokens);
    //print_ast(node);
    destroy_ast(node); node = nullptr;
  }

  return 0;
}

std::string read_file(std::string& file_name)
{
  std::ifstream file(file_name);

  if (file.is_open() == false)
  {
    std::string msg = "impossible d'ouvrir le fichier : " + file_name;
    print_error(-1, msg);
  }

  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
