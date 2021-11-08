#ifndef PANIC_MODE_H_INCLUDED
#define PANIC_MODE_H_INCLUDED
#include "recource.h"

extern map<string , map<string, vector<string> > >parse_table;
void parser_panic_mode(string,vector<string>);
bool isNonTerminal(string);


#endif // PANIC_MODE_H_INCLUDED