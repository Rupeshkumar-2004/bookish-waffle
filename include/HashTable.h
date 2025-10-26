#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class HashTable{
    private:
        unordered_map<string,vector<int>> villageToJob;
        unordered_map<string,vector<int>> districtToJob;
        int collisions;

    public:
        HashTable(){
            collisions=0;
        }

        void addJob(const string village,const string district,int jobIds){
            villageToJob[village].push_back(jobIds);
            districtToJob[district].push_back(jobIds);
        }

        vector<int> byVillage(const string village){
            auto s=villageToJob.find(village);
            if(s!=villageToJob.end()){
                return s->second;
            }
            return vector<int>();
        }

        vector<int> byDistrict(const string district){
            auto s=districtToJob.find(district);
            if(s!=districtToJob.end()){
                return s->second;
            }
            return vector<int>();
        }

        void displayInfo(){
            cout<<"\n    HASH TABLE       \n";
            cout<<"        PURPOSE??      \n";
            cout<<" O(1) job lookup by location";
            cout<<"Unique villages: "<<villageToJob.size()<<endl;
            cout<<"Unique district: "<<districtToJob.size()<<endl;
        }

};


#endif