#pragma once

#include "ast.hpp"
#include "token.hpp"
#include <istream>
#include <map>

/**
 * @brief Classe permettant l'analyse grammaticale du langage de programmation
*/
class Parser
{
  public:
    /**
     * @brief Constructeur de la classe
    */
    Parser();

    /**
     * @brief Méthode vérifiant si on a fini d'analyser le programme
     * @return bool, si true, on a fini d'analyser le programme, sinon false
    */
    bool is_at_end();

    /**
     * @brief Accesseur du token que l'on est en train de traiter
     * @return Token&, token que l'on traite couramment
    */
    Token& get_current();

    /**
     * @brief Accesseur du prochain token à traiter
     * @return Token&, nouveau token à traiter
    */
    Token& eat();

    /**
     * @brief Accesseur du token que l'on a traité précédemment
     * @return Token&, ancien token que l'on a traité
    */
    Token& get_previous();

    /**
     * @brief Méthode créant l'arbre de traitement du programme
     * @param tokens: std::vector<Token>&, liste de token à traiter
     * @return Node*, arbre contenant le programme traité
    */
    Node* parse_statement(std::vector<Token>& tokens);

  private:
    /**
     * @brief Méthode traitant la déclaration de variable
     * @return Node*, sous-arbre contenant la variable déclaré
    */
    Node* parse_var_decl();

    /**
     * @brief Méthode traitant l'assignation de valeur à une variable
     * @return Node*, instruction d'assignation de valeur à la variable
    */
    Node* parse_assignment();

    /**
     * @brief Méthode traitant l'expression à assigner à une variable s'il s'agit d'une opération "+" ou "-"
     * @return Node*, sous-arbre contenant les instructions de traitement de l'expression
    */
    Node* parse_expression();

    /**
     * @brief Méthode traitant le reste des opérations de calcul
     * @return Node*, sous-arbre contenant les instructions de traitement de l'expression
    */
    Node* parse_term();
    
    /**
     * @brief Méthode chargée d'assigner des types à des valeurs
     * @return Node*, sous-arbre contenant les valeurs et leurs types
    */
    Node* parse_factor();

    size_t pos;
    std::vector<Token> tokens;
    Token parse_end;
};
