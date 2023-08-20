#include <bits/stdc++.h>
using namespace std;

int main(){

    ifstream a_data("medium_set.dat");
    ifstream c_data("medium1.dat");
    ofstream result("output_file.dat");

    string str;
    string str2;
    int line=0;
    
    while(getline(a_data,str) && getline(c_data,str2)){
        stringstream aa;
        string x;
        vector<int> p;
        while(aa>>x){
            p.push_back(stoi(x));
        }
        line++;

        stringstream bb;
        vector<int> p2;
        while(bb>>x){
            p2.push_back(stoi(x));
        }
        sort(p.begin(),p.end());
        sort(p2.begin(),p2.end());
        if(p.size()!=p2.size()){
            cout<< line<<endl;
            return 0;
        }
        for(int i=0;i<p.size();i++){
            if(p[i]!=p2[i]){
                cout<< line<<endl;
                return 0;
            }
        }


    }

    cout<<"no error"<<endl;


}