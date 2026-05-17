#include "token.hpp"
#include "global.hpp"

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
  std::string line; std::string word;
  std::istringstream iss(src);
  int i_line = 0;
  bool error = false;

  // On traite les tokens
  while (std::getline(iss, line) && error == false)
  {
    i_line++; std::istringstream line_stream(line);

    while (line_stream >> word && error == false)
    {
      if (word == "true" || word == "false") tokens.push({word, t_bool_literal, i_line, 1});
      else if (word == "and" || word == "or" || word == "not") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "nand" || word == "nor") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "xor" || word == "xnor") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "==" || word == "<=" || word == ">=") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == ">" || word == "<" || word == "!=") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "if" || word == "then" || word == "else") tokens.push({word, t_condition, i_line, 1});
      else if (word == "disp" || word == "input") tokens.push({word, t_function_call, i_line, 1});
      else if (is_key_word(word)) tokens.push({word, t_key_word, i_line, 1});
      else if (word == "=") tokens.push({word, t_equal, i_line, 1});
      else if (word == "+=") tokens.push({word, t_equal, i_line, 1});
      else if (word == "-=") tokens.push({word, t_equal, i_line, 1});
      else if (word == "/=") tokens.push({word, t_equal, i_line, 1});
      else if (word == "*=") tokens.push({word, t_equal, i_line, 1});
      else if (word == "+") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "-") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "*") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "/") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == "%") tokens.push({word, t_bin_operator, i_line, 1});
      else if (word == ",") tokens.push({word, t_comma, i_line, 1});
      else if (word == "(") tokens.push({word, t_left_parenthese, i_line, 1});
      else if (word == ")") tokens.push({word, t_right_parenthese, i_line, 1});
      else if (is_a_digit(word) == true) tokens.push({word, t_num_literal, i_line, 1});
      else if (is_alpha(word) == true) tokens.push({word, t_identifier, i_line, 1});
      else
      {
        print_error(i_line, "token '" + word + "' non reconnu");
        while (tokens.get_size() != 0) tokens.pop();
        error = true;
      }
    }
  }

  return tokens;
}
