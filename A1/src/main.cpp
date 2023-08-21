#include <bits/stdc++.h>
using namespace std;

#include "fptree.hpp"

void compress(vector<pair<int,set<Item>>> &freq, Item input_file, Item output_file){
    ifstream data(input_file);
    ofstream result(output_file);
    Item str;

    int size_freq = freq.size();
    map<string,set<string>> mapping;
    vector<string> data_out;
    int buffer = 0;
    while(getline(data,str)){
        stringstream ss(str);
        Item num;

        unordered_map<string,int> maps={};
        while(ss>>num){
            maps[num]=1;
        }

        int cnt=-1;
        Item ans="";
        for(int i=size_freq-1;i>=0;i--){
            set<string> s = freq[i].second;
            bool pos=true;
            if(s.size()>maps.size()){
                break;
            }
            for(auto it=s.begin();it!=s.end();it++){
                if(maps.find(*it)==maps.end()){
                    pos=false;
                    break;
                }
            }
            if(pos){
                mapping[to_string((i-size_freq))] = s;
                for(auto it=s.begin();it!=s.end();it++){
                    maps.erase((*it));
                }
                ans+= to_string((i-size_freq) ) +" ";
            }

        }

        for(auto it=maps.begin();it!=maps.end();it++){
            ans+= (*it).first +" ";
        }

        // result<<ans<<endl;
        data_out.push_back(ans);
    }
    
    result<< to_string(mapping.size())<<endl;
    for(auto it=mapping.begin();it!=mapping.end();it++){
        Item ans= (*it).first +" : ";
        set<string> &s = (*it).second;
        for(auto a: s){
            ans+= a +" ";
        }
        result<<ans<<endl;

    }
    for(int i=0;i<data_out.size();i++){
        result<< data_out[i]<<endl;
    }
    // return mapping;
    
}

void decompress( Item input_file, Item output_file){
    ifstream data(input_file);
    ofstream result(output_file);
    Item str;

    int cnt= (getline(data,str)) ? stoi(str):0;
    map<string,set<string>> mapping;

    while(cnt>0 && getline(data,str)){
        cnt--;
        stringstream ss(str);
        Item num;
        Item ans ="";
        Item id;
        ss>>id;
        set<string> s;
        mapping[id] = s;
        ss>>num;
        while(ss>>num){
            mapping[id].insert(num);
        }
    }

    // for(auto it= mapping.begin();it!=mapping.end();it++){
    //     cout<< (*it).first<<" : ";
    //     set<string> s = (*it).second;
    //     for(auto x:s){
    //         cout<< x<<" ";
    //     }
    //     cout<<endl;
    // }

    while(getline(data,str)){
        stringstream ss(str);
        Item num;
        Item ans ="";
        while(ss>>num){
            if(stoi(num)>=0){
                ans+= num +" ";
            }else{
                set<string> &s = mapping[num];
                for(auto it: s){
                    ans+= (it)+" ";
                }
            }

        }
        result<< ans<<endl;
    }
    
}

bool static cmp(pair<int,set<string>> a, pair<int,set<string>> b){
    return a.first<b.first;
}

vector<pair<int,set<Item>>> converter(set<pair<set<Item>,uint64_t>> freq){

    vector<pair<int,set<Item>>> ans={};
    for(auto i : freq){
        if(i.first.size()==1){
            continue;
        }
        ans.push_back(make_pair(i.first.size(),i.first));
    }
    sort(ans.begin(),ans.end(),cmp);
    return ans;

}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <C> <input_file> <output_file>" << endl;
        return 1;
    }

    Item command = argv[1];
    Item input_file = argv[2];
    Item output_file = argv[3];

    Item item;
    vector<Transaction> transactions;
    ifstream data(input_file);
    // ofstream result(output_file);
    Item str;
    long long count=0;
    while(getline(data,item)){
        vector<Item> vec;
        stringstream itemset(item);
        Item s;
        count++;
        while(itemset>>s){
            vec.push_back(s);
        }
        transactions.push_back(vec);
    }

    const uint64_t minimum_support_threshold = count*90/100;

    const FPTree fptree{ transactions, minimum_support_threshold };

    const std::set<Pattern> Freq1 = fptree_growth( fptree );

    vector<pair<int,set<Item>>> freq = converter(Freq1);
        
    if(command=="C"){
        compress(freq, input_file, output_file);
    }else{
        decompress( input_file, output_file);
    }
    
    return 0;
}