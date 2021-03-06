/*
 * Copyright 2012 Bram van der Kroef
 *
 * This file is part of LESS CSS Compiler.
 *
 * LESS CSS Compiler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LESS CSS Compiler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LESS CSS Compiler.  If not, see <http://www.gnu.org/licenses/>. 
 *
 * Author: Bram van der Kroef <bram@vanderkroef.net>
 */

#include "FunctionLibrary.h"

const FuncInfo* FunctionLibrary::getFunction(const char* functionName) const {
  std::map<std::string, FuncInfo*>::const_iterator i =
    map.find(functionName);

  if (i != map.end())
    return i->second;
  else
    return NULL;
}

void FunctionLibrary::push(string name, const char* parameterTypes,
                           Value* (*func)(const vector<const Value*> &arguments))
{
  FuncInfo* fi = new FuncInfo();
  fi->parameterTypes = parameterTypes;
  fi->func = func;
  map[name] = fi;
}

bool FunctionLibrary::checkArguments(const FuncInfo* fi,
                                     const vector<const Value*>
                                     &arguments) const {
  const char* types = fi->parameterTypes;
  vector<const Value*>::const_iterator it = arguments.begin();
  unsigned int i, len = strlen(types);
  
  for (i = 0; i < len; i++) {
    if (it == arguments.end()) {
      if (i + 1 < len && 
          (types[i + 1] == '?' ||
           types[i + 1] == '+')) {
        i++;
        continue;
      } else
        return false;
    } 
      
    if (types[i] != '.' && 
        (*it)->type != Value::codeToType(types[i])) 
      return false;

    it++;
    
    if (i + 1 < len) {
      if (types[i + 1] == '+') {
        while (it != arguments.end() &&
               (types[i] == '.' || 
                (*it)->type == Value::codeToType(types[i]))) {
          it++;
        }
        i++;
      } else if (types[i + 1] == '?') {
        i++;
      }
    }
  }
  
  if (it != arguments.end())
    return false;
  return true;
}

const char* FunctionLibrary::functionDefToString (const char* functionName, const FuncInfo* fi) {
  
  if (fi == NULL)
    fi = getFunction(functionName);
  if (fi == NULL)
    return "";
  
  string str(functionName);
  const char* types = fi->parameterTypes;
  unsigned int i, len = strlen(types);
  char* retstr;

  str.append("(");
  for (i = 0; i < len; i++) {
    if (types[i] == '.')
      str.append("Any");
    else
      str.append(Value::typeToString(Value::codeToType(types[i])));

    if (i + 1 < len) {
      if (types[i + 1] == '?') {
        str.append(" (optional)");
        i++;
      } else if(types[i + 1] == '+'){
        str.append("...");
        i++;
      }
    }

    if (i != len - 1)
      str.append(", ");
  }
  str.append(")");

  retstr = new char[str.length() + 1];
  std::strcpy (retstr, str.c_str());
  
  return retstr;
}
