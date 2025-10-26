#include "include/JobPortal.h"
#include <iostream>
#include <sstream>
#include <limits>


void Menu(){
    cout<<"\n   JOB PORTAL.....\n";
    cout<<"DATA STRUCTURE USED AND THIER DEMONSTRATIONS:\n";
    cout<<"1. Trie - Job Title Autocomplete\n";
    cout<<"2. Graph - Skill Relationships (BFS/DFS)\n";
    cout<<"3. Priority Queue - Urgent Jobs (Heap)\n";
    cout<<"4. AVL Tree - Wage Range Search\n";
    cout<<"5. Linked List - Worker Management\n";
    cout<<"6. Hash Table - Location-based Search\n";
    cout<<endl;
    cout<<"7. Post New Job\n";
    cout<<"8. Register Worker\n";
    cout<<"9. Show All Data Structures Info\n";
    cout<<"10. Load Sample Data\n";
    cout<<"0. Exit\n";
    cout<<"Choice: ";
}

int main(){
    JobPortal portal;

    int choice;
    while(true){
        Menu();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(choice){
            case 1:
                portal.searchJobsByPrefix();
                break;
            case 2:
                portal.findRelatedSkills();
                break;
            case 3:
                portal.UrgentJobs();
                break;
            case 4:
                portal.JobsByWageRange();
                break;
            case 5:
                portal.searchJobsByLocation();
                break;
            case 6:
                portal.displayAllWorkers();
                break;
            case 7:
                portal.postJob();
                break;
            case 8:
                portal.registerWorker();
                break;
            case 9:
                portal.demonstrateAllDataStructures();
                break;
            case 10:
                portal.setupSampleData();
                break;
            case 0:
                cout<<"\n Thank you for using this website..."<<endl;
                return 0 ;
            default:
                cout<<"Invalid choice ...!!!"<<endl;
        }
        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}