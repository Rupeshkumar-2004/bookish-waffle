#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include<vector>
#include<queue>
#include<stdexcept>
#include"Structures.h"
using namespace std;

//Comparator for deciding which to priotize..
struct UrgencyComparator{
    bool operator()(Job& Job1,Job& Job2){
        if(Job1.urgencyLevel==Job2.urgencyLevel){
            return Job1.dailywage<Job2.dailywage;
        }
        return Job1.urgencyLevel<Job2.urgencyLevel;
    }
};

//class for job queue
class JobQueue{
    private:
        priority_queue<Job,vector<Job>,UrgencyComparator> pq;

    public:
        //adding job to the queue..
        void addJob(Job& job){
            if(!job.isActive){
                throw invalid_argument("Cannot add inactive job to the queue.");
            }
            if(job.urgencyLevel>=3){
                pq.push(job);
            }        
        }
        
        //retriving the top urgent jobs..
        Job topUrgentJob(){
            if(pq.empty()){
                throw runtime_error("No urgent jobs available.");
            }
            return pq.top();
        }

        //basic queue function
        bool isEmpty(){
            return pq.empty();
        }

        //basic queue function
        int size(){
            return pq.size();
        }

        //ABOUT THE ADT..
        void displayInfo(){
            cout<<"               PRIORITY QUEUE(Max-Heap)   "<<endl;
            cout<<"                     PURPOSE??         "<<endl;
            cout<<"         Always get most urgent job in o(1) time"<<endl;
            cout<<"         Insertion of new job in o(log n) time"<<endl;
            cout<<"         Implementation: Binary Heap"<<endl;
            cout<<"         Current urgent jobs in queue: "<<size()<<endl;
        }
};

#endif