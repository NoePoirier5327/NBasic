#pragma once

#include "ast.hpp"
#include "token.hpp"
#include <istream>
#include <map>

class Parser
{
  public:
    Parser();
    bool is_at_end();
    Token& get_current();
    Token& eat();
    Token& get_previous();
    Node* parse_statement(std::vector<Token>& tokens);

  private:
    Node* parse_var_decl();
    
    Node* parse_assignment();

    Node* parse_expression();

    Node* parse_term();

    Node* parse_factor();
    size_t pos;
    std::vector<Token> tokens;
    Token parse_end;
};
