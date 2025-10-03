#include "headers/parser.hpp"

ProgramNode Parser::parse_program(Queue& tokens, bool console)
{
  this->tokens = tokens;
  ProgramNode program;
  program.name = "cli";
  
  while (this->tokens.is_empty() == false)
    program.body.push_back(this->parse_statement());

  return program;
}

Node* Parser::parse_statement()
{
  switch (this->tokens.get_first().type)
  {
    case t_key_word:
      if (this->tokens.get_first().name == "dim")
        return this->parse_var_decl();
      return nullptr;

    case t_num_literal:
      // Pour l'instant on considère que tout les chiffres sont des entiers
      return new IntNode(std::stoi(this->tokens.get_first().name));

    case t_identifier:
      return this->parse_assignment();

    default:
    {
      print_error(this->tokens.get_first().line, "token non reconnu : " + this->tokens.get_first().name);
      return nullptr;
    }
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
  Node* val = this->parse_additive();

  // On renvoie un noeud d'assignation de variable
  return new AssignmentNode(var_name, assign_op, val, line);
}

Node* Parser::parse_additive()
{
  if (this->tokens.is_empty() == true) return nullptr;

  Node* left = this->parse_multiplicative();

  while (this->tokens.get_first().name == "+" || this->tokens.get_first().name == "-")
  {
    std::string op = this->tokens.pop().name;
    Node* right = this->parse_multiplicative();
    left = new BinaryOpNode(op, left, right);
  }

  return left;
}

Node* Parser::parse_multiplicative()
{
  if (this->tokens.is_empty() == true) return nullptr;
  Node* left = this->parse_prim_expr();

  while (this->tokens.get_first().name == "*" || this->tokens.get_first().name == "/" || this->tokens.get_first().name == "%")
  {
    std::string op = this->tokens.pop().name;
    Node* right = this->parse_prim_expr();

    left = new BinaryOpNode(op, left, right);
  }

  return left;
}

Node* Parser::parse_prim_expr()
{
  switch (this->tokens.get_first().type)
  {
    case t_num_literal:
      return new IntNode(std::stoi(this->tokens.pop().name));

    case t_identifier:
      return new IdentifierNode(this->tokens.pop().name);
    
    /*
    case t_left_parenthese:
    {
      int line = this->tokens.pop().line; // !'('
      bool not_found = true;
      
      // On cherche si on a bien une parenthèse fermante quelque part, si oui, on l'enlève
      Queue temp;
      while (this->tokens.is_empty() == false)
      {
        // On cherche si on trouve le token parenthese fermante qui correspond à celui qui ferme la parenthèse ouverte
        if (this->tokens.get_first().type == t_right_parenthese && this->tokens.get_first().line == line && not_found == true)
        {
          //this->tokens.pop();
          not_found = false;
        }
        else temp.push(this->tokens.pop());
      }

      if (not_found == true)
      {
        print_error(line, "parenthèse fermante manquante.");
        return nullptr;
      }

      // On récupère le reste des tokens et on les remets dans la file courante
      while (temp.is_empty() == false) this->tokens.push(temp.pop());

      return this->parse_prim_expr();
    }

    case t_right_parenthese:
      this->tokens.pop();
      return this->parse_prim_expr();
    */
    
    default:
      print_error(this->tokens.get_first().line, "expression '" + this->tokens.get_first().name + "' non reconnue.");
      return nullptr;
  }
}
