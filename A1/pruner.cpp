#include <bits/stdc++.h>

using namespace std;

bool static cmp(pair<int,set<string>> &a, pair<int,set<string>> &b){
    return a.first<b.first;
}

vector<pair<int,set<string>>> converter(vector<pair<set<string>,int>> &freq){

    vector<pair<int,set<string>>> ans={};
    for(int i=0;i<freq.size();i++){
        ans.push_back(make_pair(freq[i].first.size(),freq[i].first));
    }
    sort(ans.begin(),ans.end(),cmp);
    return ans;

}


signed main(){

    vector<pair<set<string>,int>> Freq1;

    vector<pair<int,set<string>>>vec = converter(Freq1);
}