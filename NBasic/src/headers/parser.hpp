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
     * @brief Méthode permettant de créer l'arbre contenant l'entièreté du programme à éxécuter
     * @param tokens: Queue&, file de tokens à traiter
     * @return ProgramNode, arbre contenant le programme à traiter
    */
    ProgramNode parse_program(Queue& tokens);

  private:
    /**
     * @brief Méthode créant l'arbre de traitement du programme
     * @return Node*, arbre contenant le programme traité
    */
    Node* parse_statement();

    /**
     * @brief Méthode traitant la déclaration de variable
     * @return Node*, sous-arbre contenant la variable déclaré
    */
    Node* parse_var_decl();
    
    /**
     * @brief Méthode traitant l'assignation de valeur à une variable
     * @return Node*, arbre d'assignation d'instruction de valeur à la variable
    */
    Node* parse_assignment();
    
    /**
     * @brief Méthode traitant l'expression additive courante ('+' ou '-')
     * @return Node*, noeud d'instruction additif courant
    */
    Node* parse_additive();

    /**
     * @brief Méthode traitant l'expression multiplicative courante ('*', '/' ou '%')
     * @return Node*, noeud d'instruction multiplicatif courant
    */
    Node* parse_multiplicative();

    /**
     * @brief Méthode permettant de traiter les expressions gauche et ou droite d'un noeud opérateur binaire
     * @return Node*, noeud de valeur courant
    */
    Node* parse_prim_expr();

    Queue tokens; // file de token courante à traiter
};
