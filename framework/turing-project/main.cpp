#include <iostream>
#include"TuringMachine.h"
using namespace std;
const string HLEP_INFOR="usage: turing [-v|--verbose] [-h|--help] <tm> <input>";
const string UNKOWN_COMMAND="syntax error";
int main(int argc, char* argv[]){
    string tm_file_name="";
    string input="";
    bool verbose=false;
    if(argc == 1){
        cout<<HLEP_INFOR<<endl;
        exit(1);
    }
    else{
        for(int i=1;i<argc;i++){
            string arg=argv[i];
            if(arg[0]=='-'){
                if(arg=="--help"||arg=="-h"){
                cout<<HLEP_INFOR<<endl;
                exit(1);
                }
                else if(arg=="--verbose"||arg=="-v"){
                    verbose=true;
                }
                }
            else if(tm_file_name==""){
                string file_suffix=arg.substr(arg.length()-3,arg.length()-1);
                if(file_suffix==".tm"){
                    //cout<<arg<<endl;
                    tm_file_name=arg;
                    }
                    else{
                        cerr<<UNKOWN_COMMAND<<endl;
                        exit(1);
                    }

            }
            else if(input==""){
                //cout<<arg<<endl;
                input=arg;
            }
            else {
                cerr<<UNKOWN_COMMAND<<endl;
                exit(1);
            }
            
        }
    }
    TuringMachine TM(tm_file_name,verbose);
    TM.run(input);
    return 0;
}