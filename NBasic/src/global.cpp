#include "headers/global.hpp"

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
    {"disp", true}
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

bool is_in_map(std::map<std::string, int>& vars, std::string& key) { return vars.find(key) != vars.end(); }

void print_error(int &line, std::string msg)
{
  //throw std::runtime_error("[ERREUR] : l " + std::to_string(line) + " -> " + msg + "\n");
  std::cout << "[ERREUR] : l " << line << " -> " << msg << std::endl;
}

void print_debug(std::string msg) { std::cout << "[DEBUG] : " << msg << std::endl; }

void print_warning(std::string msg) { std::cout << "[ATTENTION] : " << msg << std::endl; }
