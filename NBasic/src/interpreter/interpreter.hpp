#pragma once

#include "../parser/ast.hpp"
#include "../parser/parser.hpp"
#include "../tokenizer/token.hpp"
#include "../tokenizer/global.hpp"
#include <fstream>

/**
 * @brief Classe chargé de l'interprétation du langage de programmation
*/
class Interpreter
{
  public:    
    /**
     * @brief Méthode permettant de lancer l'interface en ligne de commande de l'interpréteur
    */
    void run_cli();
    
    /**
     * @brief Méthode permettant d'exécuter un programme contenu dans un fichier
     * @param file_name: std::string&, chemin du fichier à exécuter
    */
    void run_file(std::string& file_name);

  private:
    /**
     * @brief Méthode de lecture est conversion en chaine de caractère d'un fichier
     * @param file_name: std::string&, nom du fichier à lire
     * @return std::string, chaine de caractère contenu dans le fichier
    */
    std::string read_file(std::string& file_name);
    
    /**
     * @brief Méthode permettant d'interpréter le contenu de l'ast courant
    */
    void run_ast();

    /**
     * @brief Méthode permettant de faire le calcul contenu dans un arbre binary operator
     * @param node: Node*, sous-arbre courant pour éffectuer le calcul récursivement
     * @return int, résultat du calcul sous-forme entière pour l'instant
    */
    int calculate(Node* node);
    
    /**
     * @brief Méthode permettant de traiter l'arbre de syntaxe réalisant des opérations sur les booléens
     * @param node: Node*, sous-arbre courant sur lequel réaliser le traitement
     * @return bool, résultat de l'évaluation booléenne
    */
    bool evaluate(Node* node);

    ProgramNode program;
    Queue tokens;
    Parser parser;
    std::map<std::string, int> vars_int;
    std::map<std::string, bool> vars_bool;
};
