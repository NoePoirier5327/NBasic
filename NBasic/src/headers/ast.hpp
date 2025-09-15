#pragma once

#include "token.hpp"

// Structure de noeud classique
struct Node { virtual ~Node() = default; };

// Noeud de déclaration de variable
struct VarDeclNode : Node
{
  std::string name;
  std::string type;
  VarDeclNode(std::string &n, std::string &t) : name(n), type(t) {};
};

// Noeud d'assignation de variable
struct AssignmentNode : Node
{
  std::string name;
  Node* value;
  AssignmentNode(std::string &n, Node* val) : name(n), value(val) {};
};

// Noeud d'opérateur binaire
struct BinaryOpNode : Node
{
  std::string name;
  Node* left;
  Node* right;
  BinaryOpNode(std::string &n, Node* l, Node* r) : name(n), left(l), right(r) {};
};

// Noeud d'entier
struct IntNode : Node
{
  int value;
  IntNode(int val) : value(val) {};
};

// Noeud d'identifiant
struct IdentifierNode : Node
{
  std::string name;
  IdentifierNode(std::string &n) : name(n) {};
};

/**
 * @brief Fonction chargé de dé allouer la mémoire occupé par l'arbre de manière récursive
 * @param node: Node*, sous-arbre courant dont la mémoire est à dé allouer
*/
void destroy_ast(Node* node);

/**
 * @brief Fonction d'affichage de l'arbre d'instruction
 * @param node: Node*, noeud courant dont le contenu est afficher
 * @param indent: int, indentation de l'affichage de l'affichage courant, par défaut à 0
*/
void print_ast(Node* node, int indent = 0);
