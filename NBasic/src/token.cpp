#include "headers/token.hpp"

int to_dec(std::string& input) { return (int)(static_cast<unsigned char>(input[0])); }

bool is_key_word(std::string& word)
{
  const static std::map<std::string, bool> key_words = {
    {"dim", true},
    {"as", true},
    {"integer", true},
    {"real", true},
    {"boolean", true},
    {"string", true},
    {"end", true},
    {"p_end", true}
  };

  return key_words.find(word) != key_words.end(); // recherche de complexité O(log(n));
}

bool is_valid_type(std::string &type)
{
  const static std::map<std::string, bool> types = {
    {"integer", true},
    {"real", true},
    {"boolean", true},
    {"string", true}
  };

  return types.find(type) != types.end();
}

// c >= "0" && c <= "9"
bool is_a_digit(std::string& c) { return to_dec(c) >= 48 && to_dec(c) <= 57; }

bool is_alpha(std::string& word)
{
  int word_dec = to_dec(word);

  if ((word_dec >= 97 && word_dec <= 122) || // word >= "a" && word <= "z"
  (word_dec >= 65 && word_dec <= 90) ||      // word >= "A" && word <== "Z"
  (word_dec == 95))                          // word == "_"
  { return true; }

  return false;
}

void print_error(int line, std::string &msg)
{
  //throw std::runtime_error("[ERREUR] : l " + std::to_string(line) + " -> " + msg + "\n");
  std::cout << "[ERREUR] : l " << line << " -> " << msg << std::endl;
}

void print_debug(std::string& msg) { std::cout << "[DEBUG] : " << msg << std::endl; }

void print_token(std::vector<Token> &tokens)
{
  for (auto& token : tokens)
    std::cout << "Name : " << token.name << " | Type : " << token.type << " | Scope : " << token.scope << "\n";
}

std::vector<Token> tokenize(std::string &src)
{
  std::vector<Token> tokens;
  std::string line; std::string word;
  std::istringstream iss(src);
  int i_line = 0;

  // On traite les tokens
  while (std::getline(iss, line))
  {
    i_line++; std::istringstream line_stream(line);

    while (line_stream >> word)
    {
      //if (is_valid_type(word) == true) tokens.push_back({word, t_var_type, 1});
      if (word == "integer") tokens.push_back({word, t_integer, i_line, 1});
      else if (word == "real") tokens.push_back({word, t_real, i_line, 1});
      else if (word == "boolean") tokens.push_back({word, t_boolean, i_line, 1});
      else if (word == "string") tokens.push_back({word, t_string, i_line, 1});
      else if (word == "dim") tokens.push_back({word, t_dim, i_line, 1});
      else if (word == "as") tokens.push_back({word, t_as, i_line, 1});
      else if (word == "=") tokens.push_back({word, t_equal, i_line, 1});
      else if (word == "+") tokens.push_back({word, t_bin_operator, i_line, 1});
      else if (word == "-") tokens.push_back({word, t_bin_operator, i_line, 1});
      else if (word == "*") tokens.push_back({word, t_bin_operator, i_line, 1});
      else if (word == "/") tokens.push_back({word, t_bin_operator, i_line, 1});
      else if (word == "%") tokens.push_back({word, t_bin_operator, i_line, 1});
      else if (word == ",") tokens.push_back({word, t_comma, i_line, 1});
      else if (word == "(") tokens.push_back({word, t_left_parenthese, i_line, 1});
      else if (word == ")") tokens.push_back({word, t_right_parenthese, i_line, 1});
      else if (is_a_digit(word) == true) tokens.push_back({word, t_num_literal, i_line, 1});
      else if (is_alpha(word) == true) tokens.push_back({word, t_identifier, i_line, 1});
      else 
      {
        std::string msg = "token non reconnu : " + word;
        print_error(i_line, msg);
      }
    }
  }

  return tokens;
}
