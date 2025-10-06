#pragma once

#include "token.hpp"

// Structure de noeud classique
struct Node {
  virtual ~Node() = default;
};

// Noeud contenant l'entièreté du programme courant
struct ProgramNode
{
  std::string name;
  std::vector<Node*> body;
};

// Noeud de déclaration de variable
struct VarDeclNode : Node
{
  std::string name;
  std::string type;
  int line;
  VarDeclNode(std::string &n, std::string &t, int &l) : name(n), type(t), line(l) {};
};

// Noeud d'assignation de variable
struct AssignmentNode : Node
{
  std::string name;
  std::string assign_op;
  Node* value;
  int line;
  AssignmentNode(std::string &n, std::string &a, Node* val, int &l) : name(n), assign_op(a), value(val), line(l) {};
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

struct BoolNode : Node
{
  bool value;
  BoolNode(bool val) : value(val) {};
};

// Noeud d'identifiant
struct IdentifierNode : Node
{
  std::string name;
  IdentifierNode(std::string &n) : name(n) {};
};

/**
 * @brief Fonction chargé de dé allouer la mémoire prise par l'arbre de syntaxe courant
 * @param program: ProgramNode&, arbre de syntaxe du programme courant
*/
void destroy_ast(ProgramNode& program);

/**
 * @brief Fonction chargé de dé allouer la mémoire occupé par l'arbre de manière récursive
 * @param node: Node*, sous-arbre courant dont la mémoire est à dé allouer
*/
void destroy_ast_rec(Node* node);

/**
 * @brief Fonction d'affichage de l'arbre de syntaxe courant
 * @param program: ProgramNode&, arbre à afficher
*/
void print_ast(ProgramNode& program);

/**
 * @brief Fonction d'affichage de l'arbre d'instruction
 * @param node: Node*, noeud courant dont le contenu est afficher
 * @param indent: int, indentation de l'affichage de l'affichage courant, par défaut à 0
*/
void print_ast_rec(Node* node, int indent = 0);
