#include <iostream>
#include "recource.h"
#include "First.h"
#include "Follow.h"
#include "left.h"
#include "Parse_table.h"
#include "Panic_mode.h"

vector<Non_terminal> all_nonTerminals;
vector<string> terminals;
string start_nonTerminal;
void read_inputFile(const char *input_file)
{
    fstream newfile;
    newfile.open(input_file, ios::in); //open a file to perform read operation using file object
    if (newfile.is_open())             //checking whether the file is open
    {
        struct Non_terminal non_terminal;
        terminals.push_back("^");
        terminals.push_back("$");
        string line = "";
        int get = 0;
        vector<string> production;
        while (getline(newfile, line)) //read data from file object and put it into string.
        {
            string word = "";
            bool terminal = false;
            for (std::string::size_type i = 0; i < line.size(); i++)
            {
                if (line[i] == '\\')
                {
                    if (line[i + 1] == 'L')
                    {
                        word += '^';
                    }
                    else
                    {
                        word += line[i + 1];
                    }
                    i++;
                    continue;
                }
                if (line[i] == ' ' && line[i + 1] != '=' && line[i - 1] != '=')
                {
                    if (word != "")
                    {
                        production.push_back(word);
                        word = "";
                    }
                    continue;
                }
                if (line[i] == '\'' && terminal)
                {
                    if (word != "")
                    {
                        std::vector<string>::iterator it;
                        it = std::find(terminals.begin(), terminals.end(), word);
                        if (it == terminals.end())
                        {
                            terminals.push_back(word);
                        }
                        production.push_back(word);
                        word = "";
                        terminal = false;
                    }
                    continue;
                }
                if (line[i] == '\'')
                {
                    terminal = true;
                    continue;
                }
                if (line[i] == '=' && line[i - 1] != '\'')
                {
                    if (start_nonTerminal.size() == 0)
                    {
                        start_nonTerminal = word;
                    }
                    non_terminal.name = word;
                    non_terminal.max_size = 0;
                    first[word];
                    word = "";
                    continue;
                }
                if (line[i] == '#')
                {
                    if (production.size() != 0)
                    {
                        non_terminal.productions.push_back(production);
                        if (production.size() > non_terminal.max_size)
                        {
                            non_terminal.max_size = production.size();
                        }
                    }
                    if (get != 0)
                    {
                        all_nonTerminals.push_back(non_terminal);
                    }
                    word = "";
                    non_terminal.name = "";
                    production.clear();
                    non_terminal.productions.clear();
                    get++;
                    continue;
                }
                if (line[i] == '|')
                {
                    non_terminal.productions.push_back(production);
                    if (production.size() > non_terminal.max_size)
                    {
                        non_terminal.max_size = production.size();
                    }
                    production.clear();
                    word = "";
                    continue;
                }
                if (line[i] != ' ' && line[i] != '|' && line[i] != '#' && line[i] != '=')
                {
                    word += line[i];
                }
            }
            if (word != "")
            {
                production.push_back(word);
                word = "";
            }
        }
        if (production.size() != 0)
        {
            non_terminal.productions.push_back(production);
            if (production.size() > non_terminal.max_size)
            {
                non_terminal.max_size = production.size();
            }
        }
        all_nonTerminals.push_back(non_terminal);
    }
}

void printfirstfollow()
{
    for (auto it : first)
    {
        cout << it.first << "\t"
             << "\t"
             << "\t";
        for (auto i : it.second)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------------" << endl;
    for (auto it : follow)
    {
        cout << it.first << "\t"
             << "\t"
             << "\t";
        for (auto i : it.second)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl
         << endl;
}

void printtable()
{
    for (auto nonterminal : parse_table)
    {
        cout << nonterminal.first << "   ";
        for (auto terminal : nonterminal.second)
        {
            cout << terminal.first << "    ";
            for (auto str : terminal.second)
            {
                cout << str << " ";
            }
            cout << "     ";
        }
        cout << endl;
    }
}
int main()
{
    // get programming language grammar
    read_inputFile("grammar.txt");
    vector<Non_terminal> nonTerminals = all_nonTerminals;

    // remove left factoring
    vector<Non_terminal> left_factor = left_factoring(nonTerminals);

    //remove left recursion
    left_recurion(left_factor);

    // get first and follow to fill table
    set_first();
    set_follow();

    //to print first and follow 
    // printfirstfollow();
    filltable();

    //to print table 
    // printtable();

    vector<string> input;
    ifstream myfile;

    //read tokens file
    myfile.open("tokens.txt");

    string line;
    while (getline(myfile, line))
    {
        input.push_back(line);
    }

    parser_panic_mode(start_nonTerminal, input);

    return 0;
}
