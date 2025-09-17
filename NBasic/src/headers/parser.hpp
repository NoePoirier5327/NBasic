#pragma once

#include "ast.hpp"
#include "global.hpp"

/**
 * @brief Classe permettant l'analyse grammaticale du langage de programmation
*/
class Parser
{
  public:
    /**
     * @brief Constructeur de la classe
    */
    //Parser();

    /**
     * @brief Méthode créant l'arbre de traitement du programme
     * @param tokens: Queue&, liste de token à traiter
     * @return Node*, arbre contenant le programme traité
    */
    Node* parse_statement(Queue& tokens);

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
    //Node* parse_assignment();

    /**
     * @brief Méthode traitant l'expression à assigner à une variable s'il s'agit d'une opération "+" ou "-"
     * @return Node*, sous-arbre contenant les instructions de traitement de l'expression
    */
    //Node* parse_expression();

    /**
     * @brief Méthode traitant le reste des opérations de calcul
     * @return Node*, sous-arbre contenant les instructions de traitement de l'expression
    */
    //Node* parse_term();
    
    /**
     * @brief Méthode chargée d'assigner des types à des valeurs
     * @return Node*, sous-arbre contenant les valeurs et leurs types
    */
    //Node* parse_factor();

    size_t pos;
    Queue tokens;
};
