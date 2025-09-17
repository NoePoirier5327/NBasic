#include "headers/parser.hpp"

Node* Parser::parse_statement(Queue& tokens)
{
  this->pos = 0;
  this->tokens = tokens;

  if (this->tokens.get_first().type == t_key_word && this->tokens.get_first().name == "dim") return this->parse_var_decl();
  //else if (this->tokens.get_first().type == t_identifier) return this->parse_assignment();
  else
  {
    std::string msg = "token non reconnu " + this->tokens.get_first().name;
    print_error(this->tokens.get_first().line, msg);
    return nullptr;
  }
}

Node* Parser::parse_var_decl()
{
  // On empèche les débordements mémoire
  if (this->tokens.is_empty()) return nullptr;

  this->tokens.pop(); // dim
  
  // On empèche les débordements mémoire
  if (this->tokens.is_empty()) 
  {
    std::string msg = "nom de variable attendue";
    print_error(-1, msg);
    return nullptr;
  }

  // On est sur le nom de la variable
  if (this->tokens.get_first().type == t_key_word)
  {
    std::string msg = "ce nom est réservé par un mot clé";
    print_error(-1, msg);
    return nullptr;
  }
  std::string var_name = this->tokens.get_first().name;
  this->tokens.pop();
  
  // On empèche les débordements mémoire
  if (this->tokens.is_empty())
  {
    std::string msg = "mot clé 'as' attendu";
    print_error(-1, msg);
    return nullptr;
  }
  
  // On au moment où on attribue un type à une variable
  if (this->tokens.get_first().name != "as")
  {
    std::string msg = "mot clé 'as' attendu";
    print_error(-1, msg);
    return nullptr;
  }

  this->tokens.pop(); // as

  // On empèche les débordements mémoire
  if (this->tokens.is_empty())
  {
    std::string msg = "type de variable attendu";
    print_error(-1, msg);
    return nullptr;
  }

  // On vérifie la validité du type
  if (is_valid_type(this->tokens.get_first().name) == false)
  {
    std::string msg = "le type '" + this->tokens.get_first().name + "' n'est pas valable";
    print_error(this->tokens.get_first().line, msg);
    return nullptr;
  }

  std::string var_type = this->tokens.get_first().name;
  this->tokens.pop();

  return new VarDeclNode(var_name, var_type);
}

/*
Node* Parser::parse_assignment()
{
  std::string var_name = this->get_current().name; // nom de la variable
  this->eat(); // nom de la variable
  
  // On empèche les débordements mémoires
  if (this->is_at_end())
  {
    std::string msg = "mot clé '=' attendu";
    print_error(this->get_previous().line, msg);
    return nullptr;
  }

  // On vérifie qu'on a bien un égale après le nom de variable
  if (this->get_current().type != t_equal)
  {
    std::string msg = "mot clé '=' attendu";
    print_error(this->get_current().line, msg);
    return nullptr;
  }
  this->eat(); // '='

  // On empèche les débordements mémoire
  if (this->is_at_end())
  {
    std::string msg = "expression attendu";
    print_error(this->get_previous().line, msg);
    return nullptr;
  }

  // On traite l'expression associée à la variable
  Node* expr = this->parse_expression();

  return new AssignmentNode(var_name, expr);
}

Node* Parser::parse_expression()
{
  Node* left = this->parse_term();
  std::string op; Token temp = this->get_current();
  
  while (this->is_at_end() == false && (temp.type == t_bin_operator && (temp.name == "+" || temp.name == "-")))
  {
    op = this->eat().name; // On récupère l'opérateur
    Node *right = this->parse_term(); // On traite la valeur suivante
    left = new BinaryOpNode(op, left, right); // On créer le noeud d'opérateur binaire
    temp = this->get_current();
  }

  return left;
}

Node* Parser::parse_term()
{
  Node* left = this->parse_factor(); // On traite la valeur actuelle
  std::string op; Token temp = this->get_current();

  while (this->is_at_end() == false && (temp.type == t_bin_operator && (temp.name == "*" || temp.name == "/" || temp.name == "%")))
  {
    op = this->eat().name; // On récupère l'opérateur
    Node* right = this->parse_factor(); // On traite la valeur suivante
    left = new BinaryOpNode(op, left, right);
    temp = this->get_current();
  }

  return left;
}

Node* Parser::parse_factor()
{
  switch (this->get_current().type)
  {
    case t_num_literal:
    {
      int value = std::stoi(this->get_current().name);
      return new IntNode(value);
    }

    case t_identifier:
      return new IdentifierNode(this->get_current().name);

    default:
    {
      std::string msg = "token '" + this->get_current().name + "' inattendu dans l'expression";
      print_error(this->get_current().line, msg);
      return nullptr;
    }
  }
}
*/
