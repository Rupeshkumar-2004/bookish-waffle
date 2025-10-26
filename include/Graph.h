#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <queue>
#include <string>

using namespace std;

class Graph{
    private:
        unordered_map<string,vector<string>> adjacencyList;

    public:
        void addEdge(const string& skill1,const string& skill2){
            adjacencyList[skill1].push_back(skill2);
            adjacencyList[skill2].push_back(skill1);
        }

        vector<string> RelatedSkills(string& skill){
            vector<string> related;
            set<string> visited;
            queue<string> q;

            q.push(skill);
            visited.insert(skill);

            while(!q.empty()){
                string current=q.front();
                q.pop();

                if(adjacencyList.find(current)!=adjacencyList.end()){
                    for(auto& neighbor:adjacencyList[current]){
                        if(visited.find(neighbor)==visited.end()){
                            visited.insert(neighbor);
                            related.push_back(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
            }
            return related;
        }
        void topologicalSort(string& skill,set<string>& visited,vector<string>& stack){
            visited.insert(skill);

            if(adjacencyList.find(skill)!=adjacencyList.end()){
                for(auto& neighbor:adjacencyList[skill]){
                    if(visited.find(neighbor)==visited.end()){
                        topologicalSort(neighbor,visited,stack);
                    }
                }
            }
            stack.push_back(skill);
        }

        vector<string> getLearningPath(string& targetSkill){
            vector<string> path;
            set<string> visited;
            vector<string> stack;

            topologicalSort(targetSkill, visited, stack);

            return stack;
        }

        void displayInfo(){
            cout<<"\n Graph Structure:  \n";
            cout<<" Represenation using Adjacency List \n";
            cout<<"      PURPOSE??       \n";
            cout<<" Models relationships between skills for learning paths\n";
            cout<<"\n Example Related Skills \n";
            for(auto& pair: adjacencyList){
                cout<<pair.first<<"->";
                for(int i=0;i<pair.second.size();i++){
                    cout<<pair.second[i];
                    if(i!=pair.second.size()-1){
                        cout<<", ";
                    }
                }
                cout<<endl;
            }
        }
};
#endif
