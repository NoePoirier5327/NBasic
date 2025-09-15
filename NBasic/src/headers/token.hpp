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

/**
 * @brief Fonction chargé de convertir une chaine de caractère en son identifiant entier correspondant
 * @param input: std::string&, chaine à traiter
 * @return int, valeur entière correspondant à la chaine en paramètre
*/
int to_dec(std::string& input);

/**
 * @brief Fonction chargé de déterminer si la chaine en paramètre est un mot clé ou non
 * @param word: std::string&, chaine de caractère dont on doit décider la nature
 * @return bool, si true alors la chaine est un mot clé, sinon non
*/
bool is_key_word(std::string& word);

/**
 * @brief Fonction chargé de savoir si la chaine en paramètre est un type existant ou non
 * @param type: std::string&, chaine dont la nature est à déterminer
 * @return bool, si true, la chaine correspond à un type existant, sinon non
*/
bool is_valid_type(std::string& type);

/**
 * @brief Fonction chargé de savoir si la chaine en paramètre est une valeur numérique
 * @param c: std::string&, caractère dont la nature est à déterminer
 * @return bool, si true, la chaine est une valeur numérique, sinon non
*/
bool is_a_digit(std::string& c);

/**
 * @brief Fonction chargé de savoir si la valeur en paramètre en alpha numérique ou non
 * @param word: std::string&, valeur dont la nature est à déterminer
 * @return bool, si true, la chaine est alpha numérique, sinon non
*/
bool is_alpha(std::string& word);

/**
 * @brief Fonction permettant d'afficher un message d'erreur
 * @param line: int, ligne à laquelle l'erreur est apparue
 * @param msg: std::string&, message d'erreur à afficher
*/
void print_error(int line, std::string& msg);

/**
 * @brief Fonction d'affichage d'un message de débug dans l'interpréteur
 * @param msg: std::string&, message de débug à afficher
*/
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
