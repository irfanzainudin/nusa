#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"

typedef struct VISITOR_STRUCT
{} visitor_T;

visitor_T* init_visitor();

AST_T* visit(visitor_T* visitor, AST_T* node);
AST_T* visit_variable_definition(visitor_T* visitor, AST_T* node);
AST_T* visit_function_definition(visitor_T* visitor, AST_T* node);
AST_T* visit_variable(visitor_T* visitor, AST_T* node);
AST_T* visit_function_call(visitor_T* visitor, AST_T* node);
AST_T* visit_string(visitor_T* visitor, AST_T* node);
AST_T* visit_compound(visitor_T* visitor, AST_T* node);

#endif