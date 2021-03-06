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

#ifndef __Stylesheet_h__
#define __Stylesheet_h__

#include "CssWritable.h"
#include "Selector.h"

#include "../Token.h"
#include "../TokenList.h"

#include "../css/CssWriter.h"

#include <list>

class AtRule;
class Ruleset;
class StylesheetStatement;
class CssComment;
class MediaQuery;

class Stylesheet: public CssWritable {
private:
  std::list<AtRule*> atrules;
  std::list<Ruleset*> rulesets;
  std::list<StylesheetStatement*> statements;

protected:
  virtual void addStatement(StylesheetStatement &statement);
  virtual void addRuleset(Ruleset &ruleset);
  virtual void addAtRule(AtRule &rule);
  void deleteStatement(StylesheetStatement &statement);
  
public:
  Stylesheet() {}
  virtual ~Stylesheet();
  
  Ruleset* createRuleset();
  Ruleset* createRuleset(const Selector &selector);

  AtRule* createAtRule(const Token &keyword);
  virtual MediaQuery* createMediaQuery();

  CssComment* createComment();
  
  void deleteRuleset(Ruleset &ruleset);
  void deleteAtRule(AtRule &atrule);
  void deleteMediaQuery(MediaQuery &query);
  
  std::list<AtRule*>& getAtRules();
  std::list<Ruleset*>& getRulesets();
  std::list<StylesheetStatement*>& getStatements();
  
  virtual Ruleset* getRuleset(const Selector& selector);

  virtual void process(Stylesheet &s);
  virtual void write(CssWriter &writer);
};

#include "StylesheetStatement.h"
#include "AtRule.h"
#include "Ruleset.h"
#include "CssComment.h"
#include "MediaQuery.h"

#endif
