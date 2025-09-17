#pragma once

#include <iomanip>
#include "queue.hpp"

/**
 * @brief Fonction d'affichage d'un vecteur de token
 * @param tokens: Queue&, file dont le contenu est à afficher
*/
void print_token(Queue& tokens);

/**
 * @brief Fonction permettant de découper une chaine de caractère en paramètre en un vecteur de token
 * @param src: std::string&, code à découper
 * @return Queue, chaine de caractère découper en token
*/
Queue tokenize(std::string& src);
