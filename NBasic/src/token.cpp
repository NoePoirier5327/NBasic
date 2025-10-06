#include "headers/token.hpp"
#include "headers/global.hpp"

void print_token(Queue &tokens)
{
  int n = tokens.get_size();
  for (int i = 0; i < n; i++)
  {
    std::cout << "Name : " << tokens.get_first().name;
    std::cout << " | Type : " << tokens.get_first().type;
    std::cout << " | Line : " << tokens.get_first().line;
    std::cout << " | Scope : " << tokens.get_first().scope << std::endl;
    tokens.push(tokens.pop());
  }
}

Queue tokenize(std::string &src)
{
  Queue tokens;
  Token token;
  std::string line; std::string word;
  std::istringstream iss(src);
  int i_line = 0;

  // On traite les tokens
  while (std::getline(iss, line))
  {
    i_line++; std::istringstream line_stream(line);

    while (line_stream >> word)
    {
      if (word == "true" || word == "false") token = {word, t_bool_literal, i_line, 1};
      else if (word == "and" || word == "or" || word == "not") token = {word, t_bin_operator, i_line, 1};
      else if (word == "nand" || word == "nor") token = {word, t_bin_operator, i_line, 1};
      else if (word == "xor" || word == "xnor") token = {word, t_bin_operator, i_line, 1};
      else if (word == "==" || word == "<=" || word == ">=") token = {word, t_bin_operator, i_line, 1};
      else if (word == ">" || word == "<" || word == "!=") token = {word, t_bin_operator, i_line, 1};
      else if (is_key_word(word)) token = {word, t_key_word, i_line, 1};
      else if (word == "=") token = {word, t_equal, i_line, 1};
      else if (word == "+=") token = {word, t_equal, i_line, 1};
      else if (word == "-=") token = {word, t_equal, i_line, 1};
      else if (word == "/=") token = {word, t_equal, i_line, 1};
      else if (word == "*=") token = {word, t_equal, i_line, 1};
      else if (word == "+") token = {word, t_bin_operator, i_line, 1};
      else if (word == "-") token = {word, t_bin_operator, i_line, 1};
      else if (word == "*") token = {word, t_bin_operator, i_line, 1};
      else if (word == "/") token = {word, t_bin_operator, i_line, 1};
      else if (word == "%") token = {word, t_bin_operator, i_line, 1};
      else if (word == ",") token = {word, t_comma, i_line, 1};
      else if (word == "(") token = {word, t_left_parenthese, i_line, 1};
      else if (word == ")") token = {word, t_right_parenthese, i_line, 1};
      else if (is_a_digit(word) == true) token = {word, t_num_literal, i_line, 1};
      else if (is_alpha(word) == true) token = {word, t_identifier, i_line, 1};
      else print_error(i_line, "token '" + word + "' non reconnu");
      tokens.push(token);
    }
  }

  return tokens;
}
