#ifndef JOBPORTAL_H
#define JOBPORTAL_H

#include <vector>
#include <iostream>
#include "Structures.h"
#include "TrieNode.h"
#include "Graph.h"
#include "AVLTree.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "PriorityQueue.h"

class JobPortal{
    private:
        vector<Job> jobs;

        JobTrie jobTrie;
        Graph graph;
        JobQueue urgentQueue;
        AVLTree wageTree;
        List workerslist;
        HashTable location;

        int nextJobId;
        int nextWorkerId;
    
    public:
        JobPortal(){
            nextJobId=1;
            nextWorkerId=1;
            preSeedGraph();
        }

        void preSeedGraph(){
            graph.addEdge("Basic Framing","Seeding");
            graph.addEdge("Plowing", "Tractor Operation");
            graph.addEdge("Seeding", "Harvesting");
            graph.addEdge("Harvesting", "Crop Processing");           
            graph.addEdge("Basic Construction", "Mason Work");
            graph.addEdge("Mason Work", "Plastering");
            graph.addEdge("Mason Work", "Tile Work");
            graph.addEdge("Basic Construction", "Painting");
            graph.addEdge("Painting", "Decorative Painting");
        }

        void postJob();
        void registerWorker();
        void demonstrateAllDataStructures();
        void searchJobsByPrefix();
    void JobsByWageRange();
    void UrgentJobs();
        void findRelatedSkills();
        void searchJobsByLocation();
        void displayAllWorkers();
        void setupSampleData();
};
#endif