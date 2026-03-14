#include "headers/ast.hpp"
#include <iterator>

void destroy_ast(ProgramNode& program)
{
  if (program.body.size() <= 0) return;

  for (size_t i = 0; i < program.body.size(); i++)
    destroy_ast_rec(program.body[i]);
}

void destroy_ast_rec(Node * node)
{
  // On a un noeud vide, besoin de ne rien faire
  if (node == nullptr) return;

  std::string msg;

  // Sinon, on détruit récursivement l'arbre
  if (auto* var_decl = dynamic_cast<VarDeclNode*>(node)) delete var_decl;
  else if (auto* assign = dynamic_cast<AssignmentNode*>(node))
  {
    destroy_ast_rec(assign->value); // On supprime son enfant
    delete assign;              // On le supprime ensuite
  }
  else if (auto* bin_op = dynamic_cast<BinaryOpNode*>(node))
  {
    destroy_ast_rec(bin_op->left);  // On supprime le fils gauche
    destroy_ast_rec(bin_op->right); // puis le droit
    delete bin_op;              // puis enfin le parent
  }
  else if (auto* int_node = dynamic_cast<IntNode*>(node)) delete int_node;
  else if (auto* bool_node = dynamic_cast<BoolNode*>(node)) delete bool_node;
  else if (auto* identifier = dynamic_cast<IdentifierNode*>(node)) delete identifier;
  else if (auto* fun_call = dynamic_cast<FunctionCallNode*>(node))
  {
    for (size_t i = 0; i < fun_call->args.size(); i++) destroy_ast_rec(fun_call->args[i]);
    delete fun_call;
  }
  else if (auto* condition = dynamic_cast<ConditionNode*>(node))
  {
    delete condition->condition;

    for (auto* statement : condition->main_statement) delete statement;
    for (auto* statement : condition->else_statement) delete statement;
  }
}

void print_ast(ProgramNode& program)
{
  std::cout << "Program " << program.name << " (" << std::endl;
  for (size_t i = 0; i < program.body.size(); i++)
    print_ast_rec(program.body[i], 1);
  std::cout << ")" << std::endl;
}

void print_ast_rec(Node *ast, int indent)
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
    std::cout << indentation << "AssignVar(" << assign->name << " " << assign->assign_op << " ";
    print_ast_rec(assign->value, indent+1); std::cout<<")" << std::endl;
  }
  else if (auto* bin_op = dynamic_cast<BinaryOpNode*>(ast))
  {
    print_ast_rec(bin_op->left, indent+1);
    std::cout << " " << bin_op->name << " ";
    print_ast_rec(bin_op->right, indent+1);
  }
  else if (auto* int_node = dynamic_cast<IntNode*>(ast)) std::cout << int_node->value;
  else if (auto* bool_node = dynamic_cast<BoolNode*>(ast)) std::cout << ((bool_node->value == true) ? "true" : "false");
  else if (auto* identifier = dynamic_cast<IdentifierNode*>(ast)) std::cout << "var(" << identifier->name << ")";
  else if (auto* fun_call = dynamic_cast<FunctionCallNode*>(ast))
  {
    std::cout << fun_call->name << "(";
    for (size_t i = 0; i < fun_call->args.size() - 1; i++)
    {
      print_ast_rec(fun_call->args[i]);
      std::cout << ", ";
    }
    print_ast_rec(fun_call->args[fun_call->args.size() - 1]);
    std::cout << ")" << std::endl;
  }
  else if (auto* condition = dynamic_cast<ConditionNode*>(ast))
  {
    std::cout << "if ";
    print_ast_rec(condition->condition);
    std::cout << " then" << std::endl;

    for (auto* statement : condition->main_statement)
      print_ast_rec(statement);

    if (condition->else_statement.size() == 0)
      std::cout << "end if" << std::endl;
    else
    {
      std::cout << "else" << std::endl;

      for (auto* statement : condition->else_statement)
        print_ast_rec(statement);

      std::cout << "end if" << std::endl;
    }
  }
  else std::cout << indentation << "noeud non reconnu" << std::endl;
}
