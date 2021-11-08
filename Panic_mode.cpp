#include "Panic_mode.h"
#include "recource.h"

bool isNonTerminal(string str)
{
    std::vector<string>::iterator it;
    it = std::find(terminals.begin(), terminals.end(), str);
    if (it != terminals.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void parser_panic_mode(string start_NonTerminal, vector<string> input)
{
  ofstream myfile;
  myfile.open ("output.txt");
  
  

    stack<string> stck;

    stck.push("$");
    input.push_back("$");

    stck.push(start_NonTerminal);
    int input_index = 0;

    while (!stck.empty())
    {
        //top of stack
        string X = stck.top();

        //element in input
        string a = input[input_index];
       // cout << X << endl;
        //check if top of stack is terminal or non terminal
        if (isNonTerminal(X))
        {
            auto table_row = parse_table[X];
            if (table_row.count(a))
            {
                if (table_row[a].size() == 1 && table_row[a].back() == "synch")
                {
                    myfile << "Error here : skip " << stck.top() << endl;
                    stck.pop();
                }
                else if (table_row[a].size() == 1 && table_row[a].back() == "^")
                {
                    myfile << X <<" -> epsilon "<< endl;   
                    stck.pop();
                }
                else
                {
                    vector<string> production = table_row[a];
                    stck.pop();
                    int j=0;
                    myfile <<X<<" -> ";
                    for (int i = production.size() - 1; i >= 0; i--)
                    {
                        myfile <<production[j++]<<" ";
                        stck.push(production[i]);
                    }
                    myfile<<endl;
                }
            }
            else
            {
                myfile << "Error here : (Illegal " << stck.top() << ") - discard " << input[input_index] << endl;
                input_index++;
            }
        }
        else
        {
            if (X == a)
            {
                stck.pop();
                input_index++;
                if (X == "$" && a == "$")
                {
                    myfile << "accept" << endl;
                }else{
                    myfile<<"Match "<<a<<endl;
                }
            }
            else
            {
                myfile << "Error here: missing " << stck.top() << ", inserted" << endl;
                stck.pop();
            }
        }
    }

    myfile.close();
}
