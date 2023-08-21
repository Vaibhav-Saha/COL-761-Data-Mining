#include <bits/stdc++.h>
using namespace std;

int main(){

    ifstream a_data("small.dat");
    ifstream c_data("m.dat");
    ofstream result("output_file.dat");

    string useless;
    getline(c_data,useless);
    string str;
    string str2;
    int line=0;
    int cnt1=0;
    int cnt2=0;
    while(getline(a_data,str) && getline(c_data,str2)){
        stringstream aa(str);
        string x;
        vector<int> p;
        while(aa>>x){
            p.push_back(stoi(x));
        }
        line++;
        cout<< line<<" "<<p.size()<<endl;
        cnt1+=p.size();

        stringstream bb(str2);
        vector<int> p2;
        while(bb>>x){
            if(x==":") continue;
            p2.push_back(stoi(x));
        }
        cnt2+=p2.size();
        // sort(p.begin(),p.end());
        // sort(p2.begin(),p2.end());
        // if(p.size()!=p2.size()){
        //     cout<< line<< endl;
        //     return 0;
        // }
        // for(int i=0;i<p.size();i++){
        //     if(p[i]!=p2[i]){
        //         cout<< line<<endl;
        //         return 0;
        //     }
        // }


    }
    cout<< cnt1<<" "<< cnt2<<" "<< ((double) cnt1-cnt2)/cnt1;

    cout<<"-- no error"<<endl;


}