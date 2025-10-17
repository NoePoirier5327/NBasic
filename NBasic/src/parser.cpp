#include "headers/parser.hpp"
#include "headers/ast.hpp"
#include "headers/global.hpp"

ProgramNode Parser::parse_program(Queue& tokens, bool console)
{
  this->tokens = tokens;
  ProgramNode program;
  program.name = "cli";
  
  bool error = false;
  while (this->tokens.is_empty() == false && error == false)
  {
    program.body.push_back(this->parse_statement());
    if (program.body.back() == nullptr) error = true; // On gère l'arrêt du programme lorsqu'on a une erreur
  }

  if (error == true) return ProgramNode(); // On gère l'arrêt du programme lorsqu'on a une erreur
  return program; // On a pas d'erreur
}

Node* Parser::parse_statement()
{
  switch (this->tokens.get_first().type)
  {
    case t_key_word:
      if (this->tokens.get_first().name == "dim")
        return this->parse_var_decl();
      return nullptr;

    case t_identifier:
      return this->parse_assignment();

    case t_function_call:
      return this->parse_function_call();

    case t_num_literal:
      return this->parse_additive();

    default:
      print_error(this->tokens.get_first().line, "token non reconnu : " + this->tokens.get_first().name);
      return nullptr;
  }
}

Node* Parser::parse_var_decl()
{
  // On empèche les débordements mémoire
  if (this->tokens.is_empty()) return nullptr;

  int line = this->tokens.get_first().line;
  this->tokens.pop(); // dim
  
  // On empèche les débordements mémoire
  if (this->tokens.is_empty()) 
  {
    print_error(line, "nom de variable attendu.");
    return nullptr;
  }

  // On est sur le nom de la variable
  if (this->tokens.get_first().type == t_key_word)
  {
    print_error(line, "ce nom est réservé par un mot clé.");
    return nullptr;
  }
  std::string var_name = this->tokens.pop().name;
  
  // On empèche les débordements mémoire
  if (this->tokens.is_empty())
  {
    print_error(line, "mot clé 'as' attendu.");
    return nullptr;
  }
  
  // On au moment où on attribue un type à une variable
  if (this->tokens.get_first().name != "as")
  {
    print_error(line, "mot clé 'as' attendu.");
    return nullptr;
  }

  this->tokens.pop(); // as

  // On empèche les débordements mémoire
  if (this->tokens.is_empty())
  {
    print_error(line, "type de variable attendu.");
    return nullptr;
  }

  // On vérifie la validité du type
  if (is_valid_type(this->tokens.get_first().name) == false)
  {
    print_error(line, "le type '" + this->tokens.get_first().name + "' n'est pas valable.");
    return nullptr;
  }

  std::string var_type = this->tokens.pop().name;

  return new VarDeclNode(var_name, var_type, line);
}

Node* Parser::parse_function_call()
{
  int line = this->tokens.get_first().line;
  std::string func_name = this->tokens.pop().name;
  std::vector<Node*> args;
  
  // On récupère tout les arguments de la fonction qui est appelé
  while (this->tokens.get_size() != 0 && line == this->tokens.get_first().line)
    args.push_back(this->parse_bool_prim());
  
  // On retourne l'appelle de la fonction 
  return new FunctionCallNode(func_name, args, line);
}

Node* Parser::parse_assignment()
{
  // On empèche les débordements mémoire
  if (this->tokens.is_empty() == true) return nullptr;

  // On récupère le nom de la variable
  std::string var_name = this->tokens.get_first().name;
  int line = this->tokens.pop().line;

  // On évite les débordements mémoire
  if (this->tokens.is_empty() == true)
  {
    print_error(line, "le mot clé '=' est attendu.");
    return nullptr;
  }

  // On vérifie que le mot clé '=' soit bien à la suite de l'expression
  if (this->tokens.get_first().name != "=" &&
     this->tokens.get_first().name != "+=" &&
     this->tokens.get_first().name != "-=" &&
     this->tokens.get_first().name != "*=" &&
     this->tokens.get_first().name != "/=")
  {
    std::cout << this->tokens.get_first().name << std::endl;
    print_error(line, "un mot clé d'assignation est attendu.");
    return nullptr;
  }

  std::string assign_op = this->tokens.pop().name; // On récupère l'opérateur d'assignation
  
  // On évite les débordements mémoire
  if (this->tokens.is_empty() == true)
  {
    print_error(line, "la valeur à assigner est attendue.");
    return nullptr;
  }

  // On traite la valeur de l'assignement en un noeud courant
  Node* val = this->parse_bool_prim();

  // On renvoie un noeud d'assignation de variable
  return new AssignmentNode(var_name, assign_op, val, line);
}

Node* Parser::parse_bool_prim()
{
  if (this->tokens.is_empty() == true) return nullptr;

  std::string op = "";
  BinaryOpNode* left = new BinaryOpNode(op, this->parse_eval(), nullptr);
  
  while (this->tokens.get_first().name == "and" ||
         this->tokens.get_first().name == "or" ||
         this->tokens.get_first().name == "not")
  {
    left->name = this->tokens.pop().name;
    left->right = this->parse_eval();
    left = new BinaryOpNode(left->name, left->left, left->right);
  }
  
  return left;
}

Node* Parser::parse_eval()
{
  if (this->tokens.is_empty() == true) return nullptr;
  
  std::string op = "";
  BinaryOpNode* left = new BinaryOpNode(op, this->parse_additive(), nullptr);

  while (this->tokens.get_first().name == "==" ||
         this->tokens.get_first().name == "!=" ||
         this->tokens.get_first().name == ">=" ||
         this->tokens.get_first().name == "<=" ||
         this->tokens.get_first().name == ">" ||
         this->tokens.get_first().name == "<")
  {
    left->name = this->tokens.pop().name;
    left->right = this->parse_additive();
    left = new BinaryOpNode(left->name, left->left, left->right);
  }

  return left;
}

Node* Parser::parse_additive()
{
  if (this->tokens.is_empty() == true) return nullptr;
  
  std::string op = "";
  BinaryOpNode* left = new BinaryOpNode(op, this->parse_multiplicative(), nullptr);

  while (this->tokens.get_first().name == "+" || this->tokens.get_first().name == "-")
  {
    //Node* right = this->parse_multiplicative();
    left->name = this->tokens.pop().name;
    left->right = this->parse_multiplicative();
    left = new BinaryOpNode(left->name, left->left, left->right);
  }

  return left;
}

Node* Parser::parse_multiplicative()
{
  if (this->tokens.is_empty() == true) return nullptr;

  std::string op = "";
  BinaryOpNode* left = new BinaryOpNode(op, this->parse_prim_expr(), nullptr);

  while (this->tokens.get_first().name == "*" || this->tokens.get_first().name == "/" || this->tokens.get_first().name == "%")
  {
    //op = this->tokens.pop().name;
    //Node* right = this->parse_prim_expr();
    
    left->name = this->tokens.pop().name;
    left->right = this->parse_prim_expr();
    left = new BinaryOpNode(left->name, left->left, left->right);
  }

  return left;
}

Node* Parser::parse_prim_expr()
{
  switch (this->tokens.get_first().type)
  {
    case t_num_literal:
      return new IntNode(std::stoi(this->tokens.pop().name));

    case t_bool_literal:
      return new BoolNode(this->tokens.pop().name == "true");

    case t_identifier:
    {
      Token temp = this->tokens.pop();
      return new IdentifierNode(temp.name, temp.line);
    }
    
    default:
      print_error(this->tokens.get_first().line, "expression '" + this->tokens.get_first().name + "' non reconnue.");
      return nullptr;
  }
}
