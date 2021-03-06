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

#include "Declaration.h"

Declaration::Declaration() {
  property = "";
}

Declaration::Declaration(const Token &property) {
  this->property = property;
}

Declaration::~Declaration() {
}

void Declaration::setProperty(const Token &property) {
  this->property = property;
}
void Declaration::setValue(const TokenList &value) {
  this->value = value;
}
Token& Declaration::getProperty() {
  return property;
}
TokenList& Declaration::getValue() {
  return value;
}

void Declaration::process(Ruleset &r) {
#ifdef WITH_LIBGLOG
  VLOG(2) << "Processing declaration " << property << ": " <<
    value.toString();
#endif
  Declaration* d = r.createDeclaration();
  d->setProperty(property);
  d->setValue(value);
}


void Declaration::write(CssWriter &writer) {
  writer.writeDeclaration(property, value);
}
