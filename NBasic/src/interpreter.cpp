#include "headers/interpreter.hpp"
#include "headers/ast.hpp"
#include "headers/global.hpp"
#include <string>

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
      //print_token(tokens); // On affiche les tokens de l'entrée
      this->program = this->parser.parse_program(this->tokens);

      // On traite l'arbre de syntaxe courant
      print_ast(this->program);
      this->run_ast();
      //print_debug("b = " + std::to_string(this->vars_int["b"]));
      
      // On le détruit
      destroy_ast(this->program);
    }
  }
	while (run);
  //destroy_ast(this->program);
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
    int line = -1;
    print_error(line, "impossible d'ouvrir le fichier : " + file_name);
  }

  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void Interpreter::run_ast()
{
  if (this->program.body.size() <= 0) return;

  for (size_t i = 0; i < this->program.body.size(); i++)
  {
    // On l'interprète
    // On déclare une variable
    if (auto* var_decl = dynamic_cast<VarDeclNode*>(this->program.body[i]))
    {
      // On vérifie si la variable existe déjà en mémoire, si oui, on affiche une erreur sinon on la déclare
      if (is_in_map(this->vars_int, var_decl->name) == false) this->vars_int.insert({var_decl->name, 0});
      else
      {
        print_error(var_decl->line, "la variable '" + var_decl->name + "' ne peut pas être déclarer une nouvelle fois.");
        return; // On arrête d'interpréter car il y a une erreur
      }
    }
    else if (auto* assign = dynamic_cast<AssignmentNode*>(this->program.body[i]))
    {
      // On vérifie si la variable courante existe, si non -> erreur
      if (is_in_map(this->vars_int, assign->name) == false)
      {
        print_error(assign->line, "la variable '" + assign->name + "' n'existe pas.");
        return;
      }

      // si oui, on interpréte la suite

      // Plusieurs possibilitées
      // 1. La valeur à assigner est un nombre
      else if (auto* val_int = dynamic_cast<IntNode*>(assign->value))
      {
        this->vars_int[assign->name] = val_int->value;
        print_debug(assign->name + " = " + std::to_string(this->vars_int[assign->name]));
      }
      // 2. La valeur est associé à une autre variable
      else if (auto* id = dynamic_cast<IdentifierNode*>(assign->value))
      {
        // On vérifie si la variable existe
        if (is_in_map(this->vars_int, id->name) == false) 
        {
          print_error(assign->line, "la variable '" + id->name + "' n'existe pas.");
          return;
        }

        // Si elle existe, on attribue sa valeur à notre variable courante
        this->vars_int[assign->name] = this->vars_int[id->name];
        print_debug(assign->name + " = " + std::to_string(this->vars_int[id->name]));
      }
      // 3. La valeur associé est un sous-arbre de calcul
      else if (auto* bin_op = dynamic_cast<BinaryOpNode*>(assign->value))
      {
        this->vars_int[assign->name] = this->calculate(bin_op);
        print_debug(assign->name + " = " + std::to_string(this->vars_int[assign->name]));
      }
    }
  }
}

int Interpreter::calculate(Node* node)
{
  if (auto * int_node = dynamic_cast<IntNode*>(node)) return int_node->value;
  else if (auto * id = dynamic_cast<IdentifierNode*>(node)) return this->vars_int[id->name];
  else // On sait qu'il ne peut y a voir que des identifiants, des entiers ou des opérateurs binaire
  {
    auto* bin_op = dynamic_cast<BinaryOpNode*>(node);
    if (bin_op->name == "*") return static_cast<int>(this->calculate(bin_op->left) * this->calculate(bin_op->right));
    else if (bin_op->name == "/") return static_cast<int>(this->calculate(bin_op->left) / this->calculate(bin_op->right));
    else if (bin_op->name == "%") return static_cast<int>(this->calculate(bin_op->left) % this->calculate(bin_op->right));
    else if (bin_op->name == "+") return static_cast<int>(this->calculate(bin_op->left) + this->calculate(bin_op->right));
    else return static_cast<int>(this->calculate(bin_op->left) - this->calculate(bin_op->right));
  }
}
