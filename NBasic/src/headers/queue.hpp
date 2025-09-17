#pragma once

#include <vector>
#include "global.hpp"

/**
 * @brief Classe gérant le fonctionnement du file de token à traiter
*/
class Queue
{
  public:
    /**
     * @brief Méthode permettant d'empiler un token dans la file courante
     * @param token: Token&, token à stocker
    */
    void push(Token& token);
    
    /**
     * @brief Méthode d'accès et de supression au début de la file
     * @return Token&, token correspondant au début de la file
    */
    Token& pop();
    
    /**
     * @brief Méthode d'accès au début de la file
     * @return Token&, début de la file
    */
    Token& get_first();
    
    /**
     * @brief Méthode vérifiant si la file est vide ou non
     * @return bool, si true, la file est vide, sinon non
    */
    bool is_empty();
    
    /**
     * @brief Accesseur de la taille de la file courante
     * @return int, taille de la file
    */
    int get_size();

  private:
    std::vector<Token> queue;
    Token temp; // variable utile pour la manipulation des pointeurs dans le stack
};
