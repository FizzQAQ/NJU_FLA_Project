#include"TuringMachine.h"
#include<iostream>
#include <fstream>
using namespace std;
const string RUN_HEAD="==================== RUN ====================";
const string END_LINE="==================== END ====================";
const string DIVIDED_LINE="---------------------------------------------";
const string ERR_HEAD="==================== ERR ====================";
TuringMachine::TuringMachine(){};
TuringMachine::TuringMachine(string tm_file_name, bool verbose){
    this->tm_file_name = tm_file_name;
    this->verbose=verbose;
    readFile();
};
TuringMachine::~TuringMachine(){
    delete []N;
    delete []pointer;
    delete []Headindex;
};
vector<string> TuringMachine::statesAdd(string state){
   vector<string>states;
   int start= state.find("{");
   int end=state.find("}");
   if(start!=string::npos&&end!=string::npos){
        string tmp=state.substr(start+1,end-start-1);
        int dot=0;
            while (dot!=string::npos){
            dot=tmp.find(",");
            string unit=tmp.substr(0,dot);
            states.push_back(unit);
            tmp=tmp.substr(dot+1);
        }
        return states;
   }
   else {
    cerr<<"syntax error"<<endl;
    exit(3);
   }
}
void TuringMachine::readFile(){
        ifstream in;
        in.open("../programs/"+tm_file_name,ios::in);
        if(!in.is_open()){
            cerr<<"file no found"<<endl;
            exit(2);
        }
        char buf[1024]={0};
        bool fuctionStart=false;
        while(in.getline(buf,sizeof(buf)))
        {
            string tmp=buf;
            if(tmp.find("#Q")!=string::npos){
                tmp=buf;
                vector<string>states=statesAdd(tmp);
                for(int i=0;i<states.size();i++){
                    Q.insert(states[i]);
                }
                continue;
            }
            else if(tmp.find("#S")!=string::npos){
                tmp=buf;
                vector<string>states=statesAdd(tmp);
                for(int i=0;i<states.size();i++){
                    S.insert(states[i][0]);
                }
                //for(auto i=S.begin();i!=S.end();i++){
                  //  cout<<*i<<" ";
                //}
                //cout<<endl;
                continue;
            }
            else if(tmp.find("#G")!=string::npos){
                tmp=buf;
                vector<string>states=statesAdd(tmp);
                for(int i=0;i<states.size();i++){
                    G.insert(states[i][0]);
                }
                //for(auto i=G.begin();i!=G.end();i++){
                  //  cout<<*i<<" ";
                //}
                //cout<<endl;
                continue;
            }
            else if(tmp.find("#F")!=string::npos){
                tmp=buf;
                vector<string>states=statesAdd(tmp);
                for(int i=0;i<states.size();i++){
                    F.insert(states[i]);
                }
                //for(auto i=F.begin();i!=F.end();i++){
                  //  cout<<*i<<" ";
                //}
                //cout<<endl;
                continue;
            }
            else if(tmp.find("#q0")!=string::npos){
                q0=tmp.substr(6);
                current_state=q0;
                //cout<<q0<<endl;
            }
            else if(tmp.find("#B")!=string::npos){
                B=tmp.substr(5)[0];
                //cout<<B<<endl;
            }
            else if(tmp.find("#N")!=string::npos){
                typeNum=stoi(tmp.substr(5));
                N=new deque<char>[typeNum];
                pointer=new int[typeNum];
                Headindex=new int[typeNum];
                for(int i=0;i<typeNum;i++){
                    pointer[i]=0;
                    Headindex[i]=0;
                }
                //cout<<typeNum<<endl;
            }
            else if(tmp=="; the transition functions"){
                fuctionStart=true;
            }
            else if(tmp.find("#")==string::npos){
                int semicolon=tmp.find(";");
                if(semicolon!=string::npos){
                    tmp=tmp.substr(0,semicolon);
                }
                if(tmp!=""){
                while (tmp[tmp.length()-1]==' ')
                {
                    tmp=tmp.substr(0,tmp.length()-1);
                }
                functions.insert(tmp);
                }
            }
        }
        // for(auto it=functions.begin();it!=functions.end();it++){
        //     cout<<(*it)<<endl;
        // }
        if(Q.empty()||S.empty()||G.empty()||q0.empty()||F.empty()||N==NULL){
            cerr<<"syntax error"<<endl;
            exit(10);
        }
    
}
void TuringMachine::run(string input){
    
    for(int i=0;i<input.size();i++){
        if(S.find(input[i])==S.end()){
            if(verbose){
            cerr<<"Input: "+input<<endl;
            cerr<<ERR_HEAD<<endl;
            cerr<<"error: Symbol\"" <<input[i]<< "\"in input is not defined in the set of input symbols"<<endl;
            cerr<<"Input: "<<input<<endl;
            cerr<<"       ";
            for(int j=0;j<i;j++){
                cerr<<" ";
            }
            cerr<<"^"<<endl;
            cerr<<END_LINE<<endl;
            }
            else{
                cerr<<"illegal input string"<<endl;
            }
            exit(10);
        }
    }
    if(verbose){
        cout<<"Input: "+input<<endl;
        cout<<RUN_HEAD<<endl;
    }
    for(int i=0;i<input.length();i++)
       {N[0].push_back(input[i]);}
    int Step=0;
    while(1){
        if(F.find(current_state)!=F.end()){
            Acc=true;
        }
        if(verbose){
            cout<<"Step   "<<(typeNum>=10?" ":"")<<": "<<Step<<endl;
            cout<<"State  "<<(typeNum>=10?" ":"")<<": "<<current_state<<endl;
            cout<<"Acc    "<<(typeNum>=10?" ":"")<<": ";
            if(Acc){
                cout<<"Yes"<<endl;
            }
            else{
                cout<<"No"<<endl;
            }
            for(int i=0;i<typeNum;i++){
                if(typeNum<10)
                    cout<<"Index"<<i<<" :";
                else{
                    if(i<10){
                        cout<<"Index"<<i<<"  :";
                    }
                    else 
                        cout<<"Index"<<i<<" :";
                } 
            if(pointer[i]<Headindex[i]){
                
                if(N[i].size()==0){
                    cout<<" "<<(pointer[i]<0?-pointer[i]:pointer[i]);
                }
                else{
                for(int j=pointer[i];j<(Headindex[i]+(int)N[i].size());j++){
                    cout<<" "<<(j<0?-j:j);
                    }
                }
            }
            else if(pointer[i]>=(Headindex[i]+(int)N[i].size())){
                if(N[i].size()==0){
                    cout<<" "<<(pointer[i]<0?-pointer[i]:pointer[i]);
                }
                else {
                for(int j=Headindex[i];j<=pointer[i];j++){
                    cout<<" "<<(j<0?-j:j);
                }
                }
            }
            else{
            for(int j=Headindex[i];j<(Headindex[i]+(int)N[i].size());j++){
               cout<<" "<<(j<0?-j:j);
            }
            }
            cout<<endl;
            if(typeNum<10)
            cout<<"Tape"<<i<<"  :";
            else{
                if(i<10){
                    cout<<"Tape"<<i<<"   :";
                }
                else{
                    cout<<"Tape"<<i<<"  :";
                }
            }
            if(pointer[i]<Headindex[i]){
                if(N[i].size()==0){
                    cout<<" "<<B;
                }
                else{
                    for(int j=pointer[i];j<(Headindex[i]+(int)N[i].size());j++){
                        if(j<Headindex[i])
                            if(-10<j&&j<10)
                            cout<<" "<<B;
                            else cout<<" "<<B<<" ";
                        else{
                            if(-10<j&&j<10)
                            cout<<" "<<N[i][j-Headindex[i]];
                            else cout<<" "<<N[i][j-Headindex[i]]<<" ";
                        }
                    }
                }
            }
            else if(pointer[i]>=(Headindex[i]+(int)N[i].size())){
                if(N[i].size()==0){
                    cout<<" "<<B;
                }
                else {
                for(int j=Headindex[i];j<=pointer[i];j++){
                    if(j<(Headindex[i]+(int)N[i].size())){
                        if(-10<j&&j<10)
                            cout<<" "<<N[i][j-Headindex[i]];
                            else cout<<" "<<N[i][j-Headindex[i]]<<" ";
                    }
                    else {
                        if(-10<j&&j<10)
                        cout<<" "<<B;
                        else cout<<" "<<B<<" ";
                    }
                }
                }
            }
            else{
                for(int j=Headindex[i];j<(Headindex[i]+(int)N[i].size());j++){
                if(-10<j&&j<10)
                    cout<<" "<<N[i][j-Headindex[i]];
                else cout<<" "<<N[i][j-Headindex[i]]<<" ";
                }
            }
            cout<<endl;

            if(typeNum<10)
            cout<<"Head"<<i<<"  :";
            else{
                if(i<10){
                    cout<<"Head"<<i<<"   :";
                }
                else{
                    cout<<"Head"<<i<<"  :";
                }
            }
            if(pointer[i]<Headindex[i]){
                cout<<" ^";
            }
            else if(pointer[i]>=(Headindex[i]+(int)N[i].size())){
                if(N[i].size()==0){
                    cout<<" ^";
                }
                else {
                for(int j=Headindex[i];j<=pointer[i];j++){
                    if(j==pointer[i])
                        if(-10<j&&j<10)
                       {
                         cout<<" ^";
                        }
                        else cout<<"  ^";
                        
                    else
                        if(-10<j&&j<10)
                            cout<<"  ";
                        else cout<<"   ";
                    }
                }
            }
            else{
            for(int j=Headindex[i];j<(Headindex[i]+(int)N[i].size());j++){
                 if(j==pointer[i])
                    if(-10<j&&j<10)
                        cout<<" ^";
                    else cout<<" ^ ";
                else
                    if(-10<j&&j<10)
                        cout<<"  ";
                    else cout<<"   ";
            }
        }
            cout<<endl;
            
        }
        cout<<DIVIDED_LINE<<endl;
        }
        state_change();
        if(End){
        if(Acc&&verbose){
        cout<<"ACCEPTED"<<endl;
        cout<<"Result: ";
        for(int j=0;j<N[0].size();j++){
            cout<<N[0][j];
        }
        cout<<endl;
        cout<<END_LINE<<endl;
        }
        else if(Acc){
            cout<<"(ACCEPTED) ";
            for(int j=0;j<N[0].size();j++){
                cout<<N[0][j];
            }
            cout<<endl;
        }
        else {
            if(verbose){
            cout<<"UNACCEPTED"<<endl;
            cout<<"Result: ";
            for(int j=0;j<N[0].size();j++){
                cout<<N[0][j];
            }
            cout<<endl;
            cout<<END_LINE<<endl;
            }
            else{
            cout<<"(UNACCEPTED) ";
            for(int j=0;j<N[0].size();j++){
                cout<<N[0][j];
            }
            cout<<endl;
            }
        }
        break;   
        }
    
    Step++;
    }
    

}
void TuringMachine::state_change(){
    for(auto it=functions.begin();it!=functions.end();it++){
        string tmp=(*it);
        int space=tmp.find(" ");
        if(current_state==tmp.substr(0,space)){
            tmp=tmp.substr(space+1);
            space=tmp.find(" ");
            string oldtape=tmp.substr(0,space);
            bool right=true;
            for(int i=0;i<typeNum;i++){
                if(pointer[i]>=Headindex[i]&&pointer[i]<(Headindex[i]+(int)N[i].size()))
                    {
                    if(oldtape[i]=='*'){
                        if(N[i][pointer[i]-Headindex[i]]==B){
                        right=false;
                         }
                    }   
                    else if(N[i][pointer[i]-Headindex[i]]!=oldtape[i]){
                    right=false;
                    }
                }
                else{
                    if(oldtape[i]!=B){
                       right=false; 
                    }
                }

            }
            if(right){
                tmp=tmp.substr(space+1);
                space=tmp.find(" ");
                string newtape=tmp.substr(0,space);
                for(int i=0;i<typeNum;i++){
                    auto it=N[i].begin();
                    if(newtape[i]!='*'){
                    if(pointer[i]>=Headindex[i]&&pointer[i]<(Headindex[i]+(int)N[i].size())){
                        *(it+pointer[i]-Headindex[i])=newtape[i];
                    }
                    else{//pointer指向blank
                        if(newtape[i]!=B){
                            if(pointer[i]<Headindex[i]){
                                for(int j=0;j<(Headindex[i]-pointer[i]-1);j++){
                                    N[i].push_front(B);
                                    
                                }
                                N[i].push_front(newtape[i]);
                                Headindex[i]-=(Headindex[i]-pointer[i]);

                            }
                            else if(pointer[i]>=(Headindex[i]+(int)N[i].size())){
                                for(int j=0;j<(pointer[i]-N[i].size()-Headindex[i]);j++){
                                    N[i].push_back(B);
                                }
                                N[i].push_back(newtape[i]);
                                
                            }
                        }

                    }
                    }
                    it=N[i].begin();
                    while (N[i].size()!=0&&(*it)==B)
                    {
                        N[i].pop_front();
                        if(N[i].size()!=0)
                        Headindex[i]++;
                        it=N[i].begin();
                    }
                    while(N[i].size()!=0&&*(it+N[i].size()-1)==B){
                        N[i].pop_back();
                        it=N[i].begin();
                    }
                      
                    }
                
                tmp=tmp.substr(space+1);
                space=tmp.find(" ");
                string directions=tmp.substr(0,space);
                for(int i=0;i<typeNum;i++){
                    if(directions[i]=='r'){
                        pointer[i]++;
                    }
                    else if(directions[i]=='l'){
                        pointer[i]--;
                    }
                }
                current_state=tmp.substr(space+1);
                return;
            }
            
        }
    }
    End=true;
}