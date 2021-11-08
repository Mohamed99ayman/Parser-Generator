#include "Parse_table.h"
#include "recource.h"

map<string, map<string, vector<string>>> parse_table;

bool isterminal(string str) // check if a string is a terminal or not.
{
    std::vector<string>::iterator it;
    it = std::find(terminals.begin(), terminals.end(), str);
    if (it != terminals.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int get_nonTreminalindex(string str) // get the index of a certain non terminal by its name.
{
    for (int i = 0; i < all_nonTerminals.size(); i++)
    {
        if (all_nonTerminals.at(i).name == str)
        {
            return i;
        }
    }
    return -1;
}

bool is_this_production(string production_first, string terminal)
{
    bool ans = false;
    if (production_first.size() == 0)
        return false;
    if (isterminal(production_first))
    {
        if (production_first == terminal)
            return true;
        else
            return false;
    }
    else
    {
        int index = get_nonTreminalindex(production_first);
        for (auto each_production : all_nonTerminals[index].productions)
        {
            ans |= is_this_production(each_production[0], terminal);
        }
    }

    return ans;
}

bool has_epsilon(string non_terminal_name)
{
    int index = get_nonTreminalindex(non_terminal_name);
    for (auto production : all_nonTerminals[index].productions)
    {
        if (production.back() == "^")
        {
            return true;
        }
    }
    return false;
}

void filltable()
{

    for (auto non_T : all_nonTerminals)
    {
        string nonT_name = non_T.name;

        vector<vector<string>> productions = non_T.productions;

        for (auto terminal : first[nonT_name])
        {
            if (terminal == "^")
                continue;
            if (productions.size() == 1)
            {
                parse_table[nonT_name][terminal] = productions.back();
            }
            else
            {
                for (auto production : productions)
                {
                    if (is_this_production(production[0], terminal))
                    {
                        parse_table[nonT_name][terminal] = production;
                    }
                }
            }
        }

        //add synch for error panic recovery mode
        if (has_epsilon(nonT_name))
        {
            for (auto terminal : follow[nonT_name])
            {
                if (parse_table[nonT_name].count(terminal) == 0)
                    parse_table[nonT_name][terminal] = {"^"};
            }
        }
        else
        {
            for (auto terminal : follow[nonT_name])
            {
                if (parse_table[nonT_name].count(terminal) == 0)
                    parse_table[nonT_name][terminal] = {"synch"};
            }
        }
        //check if non terminal has an epsilon
    }
}
