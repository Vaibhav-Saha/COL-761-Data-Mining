#include <bits/stdc++.h>
using namespace std;

#include "fptree.hpp"

bool static cmp(pair<int,set<Item>> a, pair<int,set<Item>> b){
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

vector<Transaction> compress(vector<pair<int,set<Item>>> &freq, Item input_file, Item output_file, int &count, map<string,set<string>> &mapping){
    ifstream data(input_file);
    Item str;

    int size_freq = freq.size();
    
    map<set<string>,string> rev_map;
    vector<string> data_out;
    vector<Transaction> Transactions;
    
    while(getline(data,str)){
        stringstream ss(str);
        vector<Item> vec;
        Item num;

        unordered_map<string,int> maps={};
        while(ss>>num){
            maps[num]=1;
        }

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
                string k="";
                if(rev_map.find(s)==rev_map.end()){  
                    mapping[to_string(count)] = s;
                    rev_map[s]=to_string(count);
                    k=to_string(count);
                    count--;
                }
                else{
                    k = rev_map[s];
                }
                for(auto it=s.begin();it!=s.end();it++){
                    maps.erase((*it));
                }
                ans+= k +" ";
                vec.push_back((Item)k);
            }

        }

        for(auto it=maps.begin();it!=maps.end();it++){
            ans+= (*it).first +" ";
            vec.push_back((Item)(*it).first);
        }

        data_out.push_back(ans);
    }
    
    //writing to new file
    ofstream result;
    ofstream damdam;
    damdam.open("damru.dat", std::ofstream::out | std::ofstream::trunc);
    result.open(output_file, std::ofstream::out | std::ofstream::trunc);

    if(mapping.size()!=0){result<<to_string(mapping.size())<<endl;}
    for(auto it=mapping.begin();it!=mapping.end();it++){
        Item ans= (*it).first +" ";
        set<string> &s = (*it).second;
        for(auto a: s){
            ans+= a +" ";
        }
        result<<ans<<endl;

    }
    for(int i=0;i<data_out.size();i++){
        result<< data_out[i]<<endl;
        damdam<<data_out[i]<<endl;
    }

    return Transactions;
}

void multi_compress(Item input_file, Item output_file){

    Item item;
    vector<Transaction> transactions;
    ifstream data(input_file);
    ofstream result(output_file);

    Item str;
    long long num_lines=0;
    while(getline(data,item)){
        vector<Item> vec;
        stringstream itemset(item);
        Item s;
        num_lines++;
        while(itemset>>s){
            vec.push_back(s);
        }
        transactions.push_back(vec);
    }

    int percentage = 90;
    int cnt=-1;
    Item damru = "damru.dat";
    map<string,set<string>> mapping;
    while(percentage>1){
        cout<<"fghj"<<endl;
        unsigned long long minimum_support_threshold = num_lines*percentage/100;
        FPTree fptree{ transactions, minimum_support_threshold };
        std::set<Pattern> Freq1 = fptree_growth( fptree );
        vector<pair<int,set<Item>>> freq = converter(Freq1);

        transactions=compress(freq, input_file, output_file, cnt,mapping);
        input_file = damru;
        percentage-=5;
    
    }

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
        while(ss>>num){
            mapping[id].insert(num);
        }
    }

    while(getline(data,str)){
        stringstream ss(str);
        Item num;
        Item ans ="";
        set<int> sets;
        while(ss>>num){
            sets.insert(stoi(num));
        }

        while(!sets.empty() && *sets.begin()<0){
            int x = *sets.begin();
            sets.erase(sets.begin());
            set<string> &m = mapping[to_string(x)];
            for(auto it:m){
                sets.insert(stoi(it));
            }
        }

        for(auto it:sets){
            ans += to_string(it)+ " ";
        }
        result<< ans<<endl;
    }
    
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <C> <input_file> <output_file>" << endl;
        return 1;
    }

    Item command = argv[1];
    Item input_file = argv[2];
    Item output_file = argv[3];


    if(command=="C"){
        multi_compress(input_file,output_file);
        // compress(freq, input_file, output_file, cnt);
    }else{
        decompress( input_file, output_file);
    }
    
    return 0;
}