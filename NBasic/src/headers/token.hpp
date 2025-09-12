#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <iomanip>

/**
 * @brief Type correspondant aux tokens disponible pour le langage
*/
enum token_type
{
  t_dim,              // Mot clé de déclaration de variable
  t_as,               // Mot clé d'attribution de type
  t_end,              // Mot clé de fin de code
  t_integer,          // type entier relatif
  t_real,             // type réel
  t_string,           // type de chaine de caractère
  t_boolean,          // type booléen
  t_identifier,       // type, fonction, class, enum, struct etc...
  t_num_var,          // valeur numérique variable
  t_equal,            // token d'attribution de valeur
  t_comma,            // token de virgule
  t_num_literal,      // valeur numérique en tant que telle
  t_left_parenthese,  // parenthese de gauche
  t_right_parenthese, // parenthese de droite
  t_bin_operator      // token d'opérateur binaire "+", "-", "%", "*", "/"
};

/**
 * @brief Structure gérant le token courant en lui-même
*/
struct Token
{
  std::string name;
  token_type type;
  int line;
  int scope;
};

int to_dec(std::string& input);

bool is_key_word(std::string& word);
bool is_valid_type(std::string& type);
bool is_a_digit(std::string& c);
bool is_alpha(std::string& word);

/**
 * @brief Fonction permettant d'afficher un message d'erreur
 * @param line: int, ligne à laquelle l'erreur est apparue
 * @param msg: std::string&, message d'erreur à afficher
*/
void print_error(int line, std::string& msg);

void print_debug(std::string& msg);

/**
 * @brief Fonction d'affichage d'un vecteur de token
 * @param token: std::vector<Token>&, vecteur dont le contenu est à afficher
*/
void print_token(std::vector<Token>& tokens);

/**
 * @brief Fonction permettant de découper une chaine de caractère en paramètre en un vecteur de token
 * @param src: std::string&, code à découper
 * @return std::vector<token>, chaine de caractère découper en token
*/
std::vector<Token> tokenize(std::string& src);
