#ifndef PARSE_TABLE_H_INCLUDED
#define PARSE_TABLE_H_INCLUDED
#include "recource.h"



void filltable();
bool isterminal(string);
int get_nonTreminalindex(string);
bool is_this_production(string , string);
bool has_epsilon(string);

extern map<string , map<string, vector<string> > >parse_table;
extern map<string, set<string>> follow;
extern map<string, set<string>> first;


#endif // FIRST_H_INCLUDED