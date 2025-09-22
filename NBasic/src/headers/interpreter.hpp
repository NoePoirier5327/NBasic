#pragma once

#include "ast.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "global.hpp"
#include <fstream>

/**
 * @brief Classe chargé de l'interprétation du langage de programmation
*/
class Interpreter
{
  public:
    /**
     * @brief Constructeur de l'interpréteur
    */
    //Interpreter();
    
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
    //void run_ast();

    ProgramNode program;
    Queue tokens;
    Parser parser;
    std::map<std::string, int> vars_int;
};
