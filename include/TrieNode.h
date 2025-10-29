#ifndef TRIENODE_H
#define TRIENODE_H

#include<unordered_map>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

//class for trie ADT..
class TrieNode{
    public:
        //mapping...
        unordered_map<char,TrieNode*>edge;
        bool isEndOfWord;
        vector<int> jobIds;

        //constructor..
        TrieNode(){
            isEndOfWord = false;
        }
};

//for job title handling..
class JobTrie{
    private:
        TrieNode* root;

        //collets the word...
        void collectWords(TrieNode* node,string& prefix,vector<string>& results){
            if(node->isEndOfWord){
                results.push_back(prefix);
            }
            for(auto& pair: node->edge){
                prefix.push_back(pair.first);
                collectWords(pair.second,prefix,results);
                prefix.pop_back();
            }
        }


        //delete's a node..
        void deleteNode(TrieNode* node){
            if(!node) return;

            for(auto& [ch,childNode]: node->edge){
                deleteNode(childNode);
            }
            delete node;
        }
    public:
        //constructor..
        JobTrie(){
            root=new TrieNode();
        }

        //destructor..
        ~JobTrie(){
            deleteNode(root);
        }

        //insertion..
        void insert(const string word,int jobId){
            TrieNode* current = root;
            for(char ch: word){
                if(current->edge.find(ch) ==current->edge.end()){
                    current->edge[ch] =new TrieNode();
                }
                current =current->edge[ch];
            }
            current->isEndOfWord =true;
            current->jobIds.push_back(jobId);
        }

        //autocompleting..
        vector<string> complete(string& prefix){
            TrieNode* current =root;
            vector<string> results;

            for(char ch:prefix){
                if(current->edge.find(ch)==current->edge.end()){
                    return results;
                }
                current =current->edge[ch];
            }
            string currentPrefix =prefix;
            collectWords(current,currentPrefix,results);
            return results;
        }

        //getting the respective ids
        vector<int> getJobIds(string& word){
            TrieNode* current=root;
            for(char ch:word){
                if(current->edge.find(ch)==current->edge.end()){
                    return vector<int>();
                }
                current=current->edge[ch];
            }
            if(current->isEndOfWord){
                return current->jobIds;
            }
            return vector<int>();
        }
        
        //ABOUT THE ADT..
        void displayInfo(){
            cout<<endl;
            cout<<"\n                 Trie Structure Info\n";
            cout<<"                      PURPOSE??     \n";
            cout<<"             Fast Prefix-Based Job Search\n";
            cout<<"                 Time Complexity: \n";
            cout<<"         Insertion:O(m) where m=prefix length \n";
            cout<<"Space Complexity:O(N*M) where N=number of words, M=average length of words\n";
            cout<<endl;
        }

};

#endif