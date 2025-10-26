#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Structures.h"

using namespace std;

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

        void displayList(){
            Node* current=head;
            while(current){
                cout<<"Worker ID: "<<current->data.workerId<<", Name: "<<current->data.name<<", Phone: "<<current->data.phoneNo<<endl;
                current=current->next;
            }
        }

        int getSize(){
            return size;
        }

        void displayInfo(){
            std::cout<<"\n  Linked List Structure Info\n";
            std::cout<<"       PURPOSE     \n";
            std::cout<<"Dynamic Storage of Worker Records\n";
            std::cout<<"       Time Complexity: \n";
            std::cout<<"Insertion: O(1) \n";
            std::cout<<"Deletion: O(n) \n";
            std::cout<<"Traversal: O(n) \n";
        }
};

#endif