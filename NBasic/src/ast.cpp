#include "headers/ast.hpp"
#include "headers/token.hpp"

void destroy_ast(Node * node)
{
  // On a un noeud vide, besoin de ne rien faire
  if (node == nullptr) return;

  std::string msg;

  // Sinon, on détruit récursivement l'arbre
  if (auto* var_decl = dynamic_cast<VarDeclNode*>(node)) delete var_decl;
  else if (auto* assign = dynamic_cast<AssignmentNode*>(node))
  {
    destroy_ast(assign->value); // On supprime son enfant
    delete assign;              // On le supprime ensuite
  }
  else if (auto* bin_op = dynamic_cast<BinaryOpNode*>(node))
  {
    destroy_ast(bin_op->left);  // On supprime le fils gauche
    destroy_ast(bin_op->right); // puis le droit
    delete bin_op;              // puis enfin le parent
  }
  else if (auto* int_node = dynamic_cast<IntNode*>(node)) delete int_node;
  else if (auto* identifier = dynamic_cast<IdentifierNode*>(node)) delete identifier;
}

void print_ast(Node *ast, int indent)
{
  // Si l'arbre est vide, on ne retourne rien
  if (ast == nullptr) return;
  
  // Sinon, on affiche les éléments parsé  
  // On prépare l'indentation de l'affichage
  std::string indentation = "";
  for (int i = 0; i < indent; i++) indentation += "  ";
  
  // On affiche le contenu de l'arbre en fonction de son type
  if (auto* var_decl = dynamic_cast<VarDeclNode*>(ast)) 
    std::cout << indentation << "VarDecl(" << var_decl->name << ", " << var_decl->type << ")" << std::endl;
  else if (auto* assign = dynamic_cast<AssignmentNode*>(ast))
  {
    std::cout << indentation << "AssignVar(" << assign->name << "," << std::endl;
    print_ast(assign->value, indent+1); std::cout<<")" << std::endl;
  }
  else if (auto* bin_op = dynamic_cast<BinaryOpNode*>(ast))
  {
    std::cout << indentation << "BinOp(";
    print_ast(bin_op->left, indent+1);
    std::cout << " " << bin_op->name << " ";
    print_ast(bin_op->right, indent+1);
    std::cout << ")"<< std::endl;
  }
  else if (auto* int_node = dynamic_cast<IntNode*>(ast)) std::cout << int_node->value;
  else if (auto* identifier = dynamic_cast<IdentifierNode*>(ast))
    std::cout << indentation << "Id(" << identifier->name << ")" << std::endl;
  else std::cout << indentation << "noeud non reconnu" << std::endl;
}
