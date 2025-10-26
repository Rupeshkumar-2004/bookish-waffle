#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <queue>
#include <stdexcept>
#include "Structures.h"

using namespace std;

struct UrgancyComparator{
    bool operator()(Job& Job1,Job& Job2){
        if(Job1.urgencyLevel==Job2.urgencyLevel){
            return Job1.dailywage < Job2.dailywage;
        }
        return Job1.urgencyLevel < Job2.urgencyLevel;
    }
};


class JobQueue{
    private:
        priority_queue<Job,vector<Job>,UrgancyComparator> pq;

    public:
        void addJob(Job& job){
            if(!job.isActive){
                throw invalid_argument("Cannot add inactive job to the queue.");
            }
            if(job.urgencyLevel>=3){
                pq.push(job);
            }        
        }
        
        Job topUrgentJob(){
            if(pq.empty()){
                throw runtime_error("No urgent jobs available.");
            }
            return pq.top();
        }

        bool isEmpty(){
            return pq.empty();
        }

        int size(){
            return pq.size();
        }

        void displayInfo(){
            cout<<"   PRIORITY QUEUE(Max-Heap)   "<<endl;
            cout<<"            PURPOSE??         "<<endl;
            cout<<"Always get most urgent job in o(1) time"<<endl;
            cout<<"Insertion of new job in o(log n) time"<<endl;
            cout<<"Implementation: Binary Heap"<<endl;
            cout<<"Current urgent jobs in queue: "<<size()<<endl;
        }
};

#endif