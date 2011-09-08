#ifndef __ValueProcessor_h__
#define __ValueProcessor_h__

#include "TokenList.h"
#include "Token.h"
#include "Value.h"
#include <map>
#include <vector>

/**
 * 
 */
class ValueProcessor {
private:
  map<string, TokenList*> variables;
  
  Value* processStatement(TokenList* value);
  Value* processOperator(TokenList* value, Value* v1,
                         Token* lastop = NULL);
  Value* processConstant(TokenList* value);
  TokenList* processDeepVariable (Token* token, Token* nexttoken);
  Value* processFunction(Token* function,
                         vector<Value*> arguments);
  
public:
  ValueProcessor();
  virtual ~ValueProcessor();

  void putVariable(string key, TokenList* value);
  TokenList* processValue(TokenList* value);
};

#endif