#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Structures.h"

using namespace std;

//structure of Node
struct Node{
    Worker data;
    Node* next;
    Node* prev;

    Node(Worker w){
        data=w;
        next=nullptr;
        prev=nullptr;
    }
};

//doubly linklist..
class List{
    private:
        Node* head;
        Node* tail;
        int size;
        
    public:
        List(){
            head=nullptr;
            tail=nullptr;
            size=0;
        }

        //add a node..
        void addNode(Worker w){
            Node* newNode=new Node(w);
            if(!head){
                head=newNode;
                tail=newNode;
            }else{
                tail->next=newNode;
                newNode->prev=tail;
                tail=newNode;
            }
            size++;
        }

        //remove a node
        void removeNode(int workerId){
            Node* current=head;
            while(current){
                if(current->data.workerId==workerId){
                    if(current->prev){
                        current->prev->next=current->next;
                    }else{
                        head=current->next;
                    }
                    if(current->next){
                        current->next->prev=current->prev;
                    }else{
                        tail=current->prev;
                    }
                    delete current;
                    size--;
                    return;
                }
                current=current->next;
            }
        }

        //search a worker..
        Worker* findWorker(int workerId){
            Node* current=head;
            while(current){
                if(current->data.workerId==workerId){
                    return &(current->data);
                }
                current=current->next;
            }
            return nullptr;
        }

        //display the list..
        void displayList(){
            Node* current=head;
            while(current){
                cout<<"Worker ID: "<<current->data.workerId<<", Name: "<<current->data.name<<", Phone: "<<current->data.phoneNo<<endl;
                current=current->next;
            }
        }

        //returning the size..
        int getSize(){
            return size;
        }

        //LINKED LIST ADT..
        void displayInfo(){
            cout<<endl;
            cout<<"\n          Linked List Structure Info\n";
            cout<<"                PURPOSE     \n";
            cout<<"     Dynamic Storage of Worker Records\n";
            cout<<"            Time Complexity: \n";
            cout<<"                Insertion: O(1) \n";
            cout<<"                Deletion: O(n) \n";
            cout<<"                Traversal: O(n) \n";
        }
};

#endif