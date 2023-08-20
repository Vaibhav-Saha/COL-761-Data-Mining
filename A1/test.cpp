#include <bits/stdc++.h>
using namespace std;
// #include <boost/algorithm/string.hpp>

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}


int main(){

    ifstream a_data("medium_set.dat");
    ifstream c_data("medium1.dat");
    ofstream result("output_file.dat");
    string str;

    // int cn
    vector<string> d1;
    vector<string> d2;
    int cnt1=0;
    int cnt2=0;
    while(getline(a_data,str)){
        stringstream ss(str);
        string s;
        vector<int> nums;
        while(ss>>s){
            nums.push_back(stoi(s));
            // cnt1++;
        }

        sort(nums.begin(),nums.end());
        string ans="";
        for(int i=0;i<nums.size();i++){
            ans+= to_string(nums[i])+" ";
        }
        trim(ans);
        //  boost::trim_left(ans);
        cnt1++;
        ans = to_string(cnt1)+": " +ans;
        d1.push_back(ans);
    }


    while(getline(c_data,str)){
        stringstream ss(str);
        string s;
        vector<int> nums;
        while(ss>>s){
            nums.push_back(stoi(s));
            // cnt2++;
        }
        sort(nums.begin(),nums.end());
        string ans="";
        for(int i=0;i<nums.size();i++){
            ans+= to_string(nums[i])+" ";
        }

        trim(ans);
        // boost::trim_left(ans);
        // result<<ans<<endl;
        cnt2++;
        ans = to_string(cnt2)+": " +ans;
        d2.push_back(ans);


    }

    std::vector<std::string> intersection;
    std::set_intersection(d1.begin(), d1.end(), d2.begin(), d2.end(), std::inserter(intersection, intersection.begin()));

    // Find the union of the sets
    std::vector<std::string> unionSet;
    std::set_union(d1.begin(), d1.end(), d2.begin(), d2.end(), std::inserter(unionSet, unionSet.begin()));

    cout<< unionSet.size()<<" "<< intersection.size()<<" " <<d1.size()<<" "<<d2.size()<<endl;
    cout<< cnt1<<" "<<cnt2<<endl;
    // cout<< cnt1<<" "<< cnt2<< " "<< ((double) cnt1-cnt2) /cnt2<<endl;
    cout<< ((double ) unionSet.size()- intersection.size()) / (d1.size())<<" Sfsg";

}