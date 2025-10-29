#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <vector>
#include "Structures.h"

//structure for AVLNode
struct AVLNode{
    double wage;
    vector<int> jobIds;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(double w, int jobId){
        wage=w;
        jobIds.push_back(jobId);
        left=nullptr;
        right=nullptr;
        height=1;
    }
};

//class for AVL TREE with its functions
class AVLTree{
    private:
        AVLNode* root;

        int Height(AVLNode* AVLnode){
            if(!AVLnode) return 0;
            return AVLnode->height;
        }

        int BalanceFactor(AVLNode* AVLnode){
            if(!AVLnode) return 0;
            return Height(AVLnode->left) - Height(AVLnode->right);
        }

        AVLNode* rightRotate(AVLNode* AVLnode){
            AVLNode* child1=AVLnode->left;
            AVLNode* child2=child1->right;

            child1->right=AVLnode;
            AVLnode->left=child2;

            AVLnode->height=1+max(Height(AVLnode->left),Height(AVLnode->right));
            child1->height=1+max(Height(child1->left),Height(child1->right));

            return child1;
        }

        AVLNode* leftRotate(AVLNode* AVLnode){
            AVLNode* child1=AVLnode->right;
            AVLNode* child2=child1->left;

            child1->left=AVLnode;
            AVLnode->right=child2;

            AVLnode->height=1+max(Height(AVLnode->left),Height(AVLnode->right));
            child1->height=1+max(Height(child1->left),Height(child1->right));

            return child1;
        }

        AVLNode* insert(AVLNode* AVLnode,double wage,int jobId){
            if(!AVLnode){
                return new AVLNode(wage,jobId);
            }
            if(wage < AVLnode->wage){
                AVLnode->left=insert(AVLnode->left,wage,jobId);
            }else if(wage > AVLnode->wage){
                AVLnode->right=insert(AVLnode->right,wage,jobId);
            }else{
                AVLnode->jobIds.push_back(jobId);
                return AVLnode;
            }

            AVLnode->height=1+max(Height(AVLnode->left),Height(AVLnode->right));

            int balance=BalanceFactor(AVLnode);


            if(balance > 1 && wage < AVLnode->left->wage){
                return rightRotate(AVLnode);
            }

            if(balance < -1 && wage > AVLnode->right->wage){
                return leftRotate(AVLnode);
            }

            if(balance > 1 && wage > AVLnode->left->wage){
                AVLnode->left=leftRotate(AVLnode->left);
                return rightRotate(AVLnode);
            }
        
            if(balance < -1 && wage < AVLnode->right->wage){
                AVLnode->right=rightRotate(AVLnode->right);
                return leftRotate(AVLnode);
            }

            return AVLnode;
        }

        void inOrder(AVLNode* AVLnode,vector<pair<double,vector<int>>>& result){
            if(!AVLnode) return;

            inOrder(AVLnode->left,result);
            result.push_back({AVLnode->wage,AVLnode->jobIds});
            inOrder(AVLnode->right,result);
        }

        //finding the job in the range..
        void rangeQuery(AVLNode* AVLnode,double minWage,double maxWage,vector<int>& jobIds){
            if(!AVLnode) return;

            if(AVLnode->wage > minWage){
                rangeQuery(AVLnode->left,minWage,maxWage,jobIds);
            }

            if(AVLnode->wage >= minWage && AVLnode->wage <= maxWage){
                jobIds.insert(jobIds.end(),AVLnode->jobIds.begin(),AVLnode->jobIds.end());
            }

            if(AVLnode->wage < maxWage){
                rangeQuery(AVLnode->right,minWage,maxWage,jobIds);
            }
        }

        void deleteTree(AVLNode* AVLnode){
            if(!AVLnode) return;

            deleteTree(AVLnode->left);
            deleteTree(AVLnode->right);
            delete AVLnode;
        }

        //no of nodes in AVL..
        int countAVLNode(AVLNode* AVLnode){
            if(!AVLnode) return 0;
            return 1+countAVLNode(AVLnode->left)+countAVLNode(AVLnode->right);
        }

    public:
        //constructor..
        AVLTree(){
            root=nullptr;
        }

        ~AVLTree(){
            deleteTree(root);
        }

        void insert(double wage,int jobId){
            root=insert(root,wage,jobId);
        }

        vector<pair<double,vector<int>>> inOrder(){
            vector<pair<double,vector<int>>> result;
            inOrder(root,result);
            return result;
        }

        //finding the jobIds
        vector<int> JobrangeQuery(double minWage,double maxWage){
            vector<int> jobIds;
            rangeQuery(root,minWage,maxWage,jobIds);
            return jobIds;
        }  

        //ABOUT THE ADT..
        void displayInfo(){
            cout<<endl;
            cout<<"             AVL TREE Structure     "<<endl;
            cout<<"                  PURPOSE??        "<<endl;
            cout<<"       Balanced BST to store jobs based on wage "<<endl;
            cout<<"       Insertion in o(log n) time "<<endl;
            cout<<"       Range Query in o(k + log n) time where k is number of jobs in range"<<endl;
            cout<<"       Property: Height-balanced and |BF|<=1 "<<endl;
            cout<<"       Current number of unique wage AVLnodes: "<<countAVLNode(root)<<endl;
            cout<<"       Current height of tree: "<<Height(root)<<endl;
            cout<<endl;
        }
};

#endif