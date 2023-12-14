#ifndef _TURING_MACHINE_H_
#define _TURING_MACHINE_H_
#include<iostream>
#include<set>
#include<deque>
#include<vector>
using namespace std;
class TuringMachine
{
private:
    string tm_file_name;
    string input;
    bool verbose;
    set<string>Q,F;
    set<char>S,G;
    string q0;
    char B='_';
    int typeNum;
    deque<char>*N=NULL;
    set<string>functions;
    string current_state;
    int *pointer;
    int *Headindex;
    bool Acc=false;
    bool End=false;
public:
    TuringMachine();
    TuringMachine(string tm_file_name, bool verbose);
    void readFile();
    void run(string input);
    vector<string>statesAdd(string state);
    ~TuringMachine();
    void state_change();
};

#endif