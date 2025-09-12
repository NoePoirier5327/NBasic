#include "headers/parser.hpp"
#include "headers/ast.hpp"
#include "headers/token.hpp"

Parser::Parser()
{
  this->parse_end.name = "p_end";
  this->parse_end.type = t_end;
  this->parse_end.line = -1;
  this->parse_end.scope = -1;
}

bool Parser::is_at_end() { return this->get_current().name == "p_end"; }

Token& Parser::get_previous()
{
  if (this->pos <= 0)
    return this->parse_end;
  return this->tokens[this->pos-1];
}

Token& Parser::get_current() 
{
  if (this->pos == this->tokens.size()) // Empèche les dépassements mémoire
    return this->parse_end;
  return this->tokens[this->pos];
}

Token& Parser::eat()
{ 
  if (this->pos == this->tokens.size()) // Empèche les dépassements mémoire 
    return this->parse_end;
  return this->tokens[this->pos++];
}

Node* Parser::parse_statement(std::vector<Token>& tokens)
{
  this->pos = 0;
  this->tokens = tokens;

  switch (this->get_current().type)
  {
    case t_dim: // Si on a 'dim' en début de ligne, on cherche à déclarer une variable
      return this->parse_var_decl();

    case t_identifier: // Si on a un nom de variable en première ligne, alors, on cherche à assigner une valeur
      return this->parse_assignment();

    default:
    {
      std::string msg = "token non reconnu " + this->get_current().name;
      print_error(this->get_current().line, msg);
      return nullptr;
    }
  }
}

Node* Parser::parse_var_decl()
{
  // On empèche les débordements mémoire
  if (this->is_at_end()) return nullptr;

  this->eat(); // dim
  
  // On empèche les débordements mémoire
  if (this->is_at_end()) 
  {
    std::string msg = "nom de variable attendue";
    print_error(this->get_previous().line, msg);
    return nullptr;
  }

  // On est sur le nom de la variable
  if (is_key_word(this->get_current().name))
  {
    std::string msg = "ce nom est utilisé par un mot clé";
    print_error(this->get_current().line, msg);
    return nullptr;
  }
  
  std::string var_name = this->get_current().name;
  this->eat();
  
  // On empèche les débordements mémoire
  if (this->is_at_end())
  {
    std::string msg = "mot clé 'as' attendu";
    print_error(this->get_previous().line, msg);
    return nullptr;
  }
  
  // On au moment où on attribue un type à une variable
  if (this->get_current().name != "as")
  {
    std::string msg = "mot clé 'as' attendu";
    print_error(this->get_current().line, msg);
    return nullptr;
  }

  this->eat(); // as

  // On empèche les débordements mémoire
  if (this->is_at_end())
  {
    std::string msg = "type de variable attendu";
    print_error(this->get_previous().line, msg);
    return nullptr;
  }

  // On vérifie la validité du type
  if (is_valid_type(this->get_current().name) == false)
  {
    std::string msg = "le type '" + this->get_current().name + "' n'est pas valable";
    print_error(this->get_current().line, msg);
    return nullptr;
  }

  std::string var_type = this->get_current().name;
  this->eat();

  return new VarDeclNode(var_name, var_type);
}

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

