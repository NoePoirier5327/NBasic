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

void destroy_ast(Node* node);
void print_ast(Node* node, int indent = 0);
