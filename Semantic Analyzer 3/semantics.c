/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // TODO
  Scope* scope = symtab->currentScope;
  Object* obj;

  while (scope != NULL) {
    obj = findObject(scope->objList, name);
    if (obj != NULL) return obj;
    scope = scope->outer; // Duyet ra ben ngoai
  }
  obj = findObject(symtab->globalObjectList, name); // Tim kiem pham vi global
  if (obj != NULL) return obj;
  return NULL;
}

// Kiem tra ten hop le
void checkFreshIdent(char *name) {
  // TODO
  if (findObject(symtab->currentScope->objList, name) != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

// Kiem tra mot dinh danh da duoc khai bao chua
Object* checkDeclaredIdent(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_IDENT,currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

// Kiem tra hang so da duoc khai bao hay chua
Object* checkDeclaredConstant(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_CONSTANT,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_CONSTANT)
    error(ERR_INVALID_CONSTANT,currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Kiem tra kieu da duoc khai bao chua
Object* checkDeclaredType(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_TYPE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_TYPE)
    error(ERR_INVALID_TYPE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Kiem tra bien da duoc khai bao chua
Object* checkDeclaredVariable(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_VARIABLE)
    error(ERR_INVALID_VARIABLE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Kiem tra ham da duoc khai bao chua
Object* checkDeclaredFunction(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_FUNCTION,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_FUNCTION)
    error(ERR_INVALID_FUNCTION,currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Kiem tra thu tuc da duoc khai bao chua
Object* checkDeclaredProcedure(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_PROCEDURE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_PROCEDURE)
    error(ERR_INVALID_PROCEDURE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

// Kiem tra mot dinh danh truoc phep gan la mot bien, mot tham so hay la mot ten ham, neu no la tem ham thi kiem tra xem co phai ten ham cua chinh no khong
Object* checkDeclaredLValueIdent(char* name) {
  // TODO
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_IDENT,currentToken->lineNo, currentToken->colNo);

  switch (obj->kind) {
    case OBJ_VARIABLE:
    case OBJ_PARAMETER:
      break;
    case OBJ_FUNCTION:
      if (obj != symtab->currentScope->owner) 
        error(ERR_INVALID_IDENT,currentToken->lineNo, currentToken->colNo);
      break;
    default:
      error(ERR_INVALID_IDENT,currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}

