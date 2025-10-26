#include "include/JobPortal.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

string toLower(string s){
    transform(s.begin(),s.end(),s.begin(), ::tolower);
    return s;
}

// void printDoubleLineBox(const string& title, const vector<string>& lines={}){
//     const int width=80;
//     const char TL ='╔',TR='╗',BL='╚',BR='╝';
//     const char H='═',V='║';

//     string top    =string(1,TL)+string(width,H)+string(1,TR);
//     cout <<'\n'<<top<<'\n';

//     int padding=(width-(int)title.size())/2;
//     string titleLine=string(1,V)+string(padding,' ')+title+string(width-title.size()-padding,' ')+string(1,V);
//     cout<<titleLine<<'\n';
    
//     // // Optional content lines
//     // for (auto& text : lines) {
//     //     std::string line = text;
//     //     if ((int)line.size() > width) line = line.substr(0, width); // trim if too long
//     //     std::cout << V << ' ' << line << std::string(width - line.size() - 1, ' ') << V << '\n';
//     // }

    
//     string bottom =string(1,BL)+string(width,H)+string(1,BR);
//     std::cout << bottom << '\n';
// }

void JobPortal::postJob(){
    Job job;
    job.jobId =nextJobId++;
    job.isActive=true;
    job.postedDate=time(nullptr);

    cout<<" Job Name: ";
    getline(cin,job.jobType);

    cout<<" Village: ";
    getline(cin,job.village);

    cout << "District: ";
    getline(std::cin, job.district);
    
    cout << "Daily Wage (₹): ";
    cin >> job.dailywage;
    
    cout << "Workers Needed: ";
    cin >> job.workersNeeded;
    
    cout << "Urgency Level (1-5, 5=Critical): ";
    cin >> job.urgencyLevel;
     
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Employer Phone: ";
    getline(cin,job.employerPhoneNo);
    cout << "Required Skills (comma-separated): ";
    string skill;
    getline(cin, skill);

    size_t pos=0;
        while((pos = skill.find(','))!=string::npos) {
            string skill = skill.substr(0, pos);
            skill.erase(0,skill.find_first_not_of(" \t"));
            skill.erase(skill.find_last_not_of(" \t")+1);
            if(!skill.empty()){
                job.requiredSkills.push_back(skill);
            }
            skill.erase(0,pos+1);
        }
        if(!skill.empty()) {
            skill.erase(0,skill.find_first_not_of(" \t"));
            skill.erase(skill.find_last_not_of(" \t")+1);
            job.requiredSkills.push_back(skill);
        }
        
        jobs.push_back(job);
        string temp =toLower(job.jobType);
        jobTrie.insert(temp, job.jobId);
        
        if(job.urgencyLevel>=3){
            urgentQueue.addJob(job);
        }
        
        wageTree.insert(job.dailywage, job.jobId);
        
        location.addJob(toLower(job.village), toLower(job.district), job.jobId);
        
        cout << "\nJob Posted Successfully! Job ID: " << job.jobId << "\n";

};

void JobPortal::registerWorker(){
        Worker newWorker;
        newWorker.workerId=nextWorkerId++;
                
        cout<<"Name: ";
        getline(cin,newWorker.name);
        
        cout<<"Phone Number: ";
        getline(cin,newWorker.phoneNo);
        
        cout<<"Village: ";
        getline(cin, newWorker.village);
        
        cout<<"Skills (comma-separated): ";
        string skill;
        getline(cin, skill);
        
        size_t pos=0;
        while((pos=skill.find(','))!=string::npos){
            string skill=skill.substr(0,pos);
            skill.erase(0,skill.find_first_not_of(" \t"));
            skill.erase(skill.find_last_not_of(" \t")+1);
            if(!skill.empty()){
                newWorker.skills.push_back(skill);
            }
            skill.erase(0,pos+1);
        }
        if(!skill.empty()){
            skill.erase(0,skill.find_first_not_of(" \t"));
            skill.erase(skill.find_last_not_of(" \t")+1);
            newWorker.skills.push_back(skill);
        }
        
        cout<<"Minimum Wage Expected (₹/day): ";
        cin>>newWorker.minWage;
        
        cout<<"Max Travel Distance (km): ";
        cin>>newWorker.maxDistanceKm;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        workerslist.addNode(newWorker);
        
        cout << "\nWorker Registered! Worker ID: " <<newWorker.workerId<< "\n";
    }

void JobPortal::searchJobsByPrefix() {
    cout<<"Enter prefix to search: ";
    string prefix;
    getline(cin, prefix);
    
    prefix = toLower(prefix);
    
    vector<string> suggestions=jobTrie.complete(prefix);
    
    if(suggestions.empty()){
        cout<<"\n No jobs found with prefix: "<<prefix<<"\n";
    }else{
        cout<<"\nFound "<<suggestions.size()<<" matching job titles:\n";
        for(size_t i=0;i<suggestions.size();++i) {
            cout <<(i+1)<<". "<<suggestions[i]<<"\n";
            
            vector<int> jobIds =jobTrie.getJobIds(suggestions[i]);
            cout<< "   Job IDs: ";
            for(size_t j=0;j<jobIds.size();++j){
                cout<<jobIds[j];
                if(j<jobIds.size()-1) cout<<", ";
            }
            cout<<"\n";
        }
    }
    
    jobTrie.displayInfo();
}

void JobPortal::JobsByWageRange(){
    double minWage,maxWage;
    cout<<"Enter minimum wage (₹): ";
    cin>>minWage;
    cout<<"Enter maximum wage (₹): ";
    cin>>maxWage;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    vector<int> jobIds = wageTree.JobrangeQuery(minWage, maxWage);
    
    if(jobIds.empty()){
        cout << "\n No jobs found in wage range ₹" << minWage << " - ₹" << maxWage << "\n";
    }else{
        cout<<"\n Found "<<jobIds.size()<<" jobs in range:\n";
        cout<<"----------------------------------------\n";
        for(int jobId:jobIds){
            for(auto& job : jobs){
                if(job.jobId==jobId && job.isActive){
                    cout<<"Job ID: " << job.jobId << "\n";
                    cout<<"Title: " << job.jobType << "\n";
                    cout<<"Location: " << job.village << ", " << job.district << "\n";
                    cout<<"Wage: ₹" << job.dailywage << "/day\n";
                    cout<<"Workers Needed: " << job.workersNeeded << "\n";
                    cout<<"Contact: " << job.employerPhoneNo << "\n";
                    break;
                }
            }
        }
    }
    
    wageTree.displayInfo();
}

void JobPortal::UrgentJobs() {
    if(urgentQueue.isEmpty()){
        cout<<"No urgent jobs available.\n";
        return;
    }
    
    int count = 0;
    while(!urgentQueue.isEmpty() && count<5){
        try{
            Job urgentJob = urgentQueue.topUrgentJob();
            
            cout<<"\n[Priority Level: " << urgentJob.urgencyLevel << "]\n";
            cout<<"Job ID: " << urgentJob.jobId << "\n";
            cout<<"Title: " << urgentJob.jobType << "\n";
            cout<<"Location: " << urgentJob.village << "\n";
            cout<<"Wage: ₹" << urgentJob.dailywage << "/day\n";
            cout<<"Workers Needed: " << urgentJob.workersNeeded << "\n";
            cout<<"Contact: " << urgentJob.employerPhoneNo << "\n";
            count++;
        }catch(const exception& e){
            break;
        }
    }
    
    urgentQueue.displayInfo();
}

void JobPortal::displayAllWorkers() {
    if(workerslist.getSize()==0){
        cout<<"No workers registered yet.\n";
        return;
    }
    
    workerslist.displayList();

    workerslist.displayInfo();
    
    cout<<"Search Worker by ID \n";
    cout<<"Enter Worker ID: ";
    int workerId;
    cin>>workerId;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    Worker* worker = workerslist.findWorker(workerId);
    
    if (worker) {
        cout<<"\n Worker Found:\n";
        cout<<"ID: " << worker->workerId << "\n";
        cout<<"Name: " << worker->name << "\n";
        cout<<"Phone: " << worker->phoneNo << "\n";
        cout<<"Village: " << worker->village << "\n";
        cout<<"Skills: ";
        for(size_t i=0;i<worker->skills.size();++i){
            cout<<worker->skills[i];
            if(i<worker->skills.size()-1){
                cout << ", ";
            }
        }
        cout << "\n";
        cout << "Min Wage: ₹" << worker->minWage<<"/day\n";
        cout<<"Max Distance: "<<worker->maxDistanceKm<<" km\n";
    }else{
        cout<<"\n Worker not found!\n";
    }
}

void JobPortal::findRelatedSkills(){    
    cout<< "\nEnter skill name: ";
    string skill;
    getline(cin, skill);
    
    // BFS: Find related skills
    cout << "\n--- BFS: Related Skills (Skills you can learn next) ---\n";
    vector<string> related = graph.RelatedSkills(skill);
    
    if(related.empty()) {
        cout<<"No advanced skills found. This might be a terminal skill.\n";
    }else{
        for(size_t i=0;i<related.size();++i){
            cout<<(i+1)<<". "<<related[i]<<"\n";
        }
    }
    
    // Learning Path (Topological Sort)
    cout<<"\n--- Learning Path (Prerequisites in order) ---\n";
    vector<string> path =graph.getLearningPath(skill);
    
    if(path.empty()){
        cout<< "This is a basic skill. No prerequisites needed.\n";
    }else{
        cout<<"To learn '"<<skill<<"', follow this path:\n";
        for(size_t i=0;i<path.size();++i){
            cout<<(i+1)<<". "<<path[i];
            if(i==path.size()-1){
                cout<<" ← YOUR GOAL";
            }
            cout<<"\n";
        }
    }
    
    graph.displayInfo();
}

void JobPortal::searchJobsByLocation(){

    cout<<"1. Search by Village\n";
    cout<<"2. Search by District\n";
    cout<<"Choice: ";
    int choice;
    cin>>choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> jobIds;
    string loc;
    
    if(choice==1){
        cout<<"Enter village name: ";
        getline(cin,loc);
        jobIds=location.byVillage(toLower(loc));
    }else{
        cout<<"Enter district name: ";
        getline(cin,loc);
        jobIds=location.byDistrict(toLower(loc));
    }
    
    cout<<"Time Complexity: O(1) average case\n\n";
    
    if(jobIds.empty()){
        cout<<"No jobs found in "<<loc<<"\n";
    }else{
        cout<<"Found "<<jobIds.size()<<"jobs:\n";
        for(int jobId:jobIds){
            for(auto& job:jobs){
                if(job.jobId==jobId &&job.isActive){
                    cout<<"Job ID: "<<job.jobId<<" | "<<job.jobType<<" | ₹"<<job.dailywage<<"/day | "<<job.village<<"\n";
                    break;
                }
            }
        }
    }
    
    location.displayInfo();
}


void JobPortal::demonstrateAllDataStructures(){
    //printDoubleLineBox("ALL DATA STRUCTURES IN THIS PROJECT");

    jobTrie.displayInfo();
    graph.displayInfo();
    urgentQueue.displayInfo();
    wageTree.displayInfo();
    workerslist.displayInfo();
    location.displayInfo();

    vector<string> complexityTable ={
        "Data Structure      Insert    Search    Delete",
        "─────────────────────────────────────────────────────",
        "Trie                O(m)      O(m)      O(m)",
        "Graph (Adj List)    O(1)      BFS/DFS   O(V+E)",
        "Priority Queue      O(log n)  O(1)      O(log n)",
        "AVL Tree            O(log n)  O(log n)  O(log n)",
        "Doubly Linked List  O(1)*     O(n)      O(n)",
        "Hash Table          O(1)      O(1)      O(1)"
    };

    //printDoubleLineBox("COMPLEXITY ANALYSIS SUMMARY", complexityTable);
    cout <<"* Insert at end with tail pointer\n";
    cout <<"m = string length,n =number of elements\n";
    cout <<"V =vertices,E =edges\n";
}

void JobPortal::setupSampleData() {
    cout<<"\n LOADING SAMPLE DATA.....\n";
    
    // Sample Job 1
    Job job1;
    job1.jobId = nextJobId++;
    job1.jobType = "Rice Harvesting";
    job1.village = "Thiruverumbur";
    job1.district = "Tiruchirappalli";
    job1.dailywage = 500;
    job1.workersNeeded = 5;
    job1.urgencyLevel = 5;
    job1.employerPhoneNo = "9876543210";
    job1.requiredSkills = {"Harvesting", "Physical Fitness"};
    job1.isActive = true;
    job1.postedDate = time(nullptr);
    
    jobs.push_back(job1);
    jobTrie.insert(job1.jobType, job1.jobId);
    urgentQueue.addJob(job1);
    wageTree.insert(job1.dailywage, job1.jobId);
    location.addJob(job1.village, job1.district, job1.jobId);
    
    // Sample Job 2
    Job job2;
    job2.jobId = nextJobId++;
    job2.jobType = "Wall Construction";
    job2.village = "Srirangam";
    job2.district = "Tiruchirappalli";
    job2.dailywage = 600;
    job2.workersNeeded = 3;
    job2.urgencyLevel = 3;
    job2.employerPhoneNo = "9988776655";
    job2.requiredSkills = {"Mason Work", "Construction"};
    job2.isActive = true;
    job2.postedDate = time(nullptr);
    
    jobs.push_back(job2);
    jobTrie.insert(job2.jobType, job2.jobId);
    urgentQueue.addJob(job2);
    wageTree.insert(job2.dailywage, job2.jobId);
    location.addJob(job2.village, job2.district, job2.jobId);
    
    // Sample Job 3
    Job job3;
    job3.jobId = nextJobId++;
    job3.jobType = "Rice Planting";
    job3.village = "Lalgudi";
    job3.district = "Tiruchirappalli";
    job3.dailywage = 450;
    job3.workersNeeded = 8;
    job3.urgencyLevel = 4;
    job3.employerPhoneNo = "9123456789";
    job3.requiredSkills = {"Planting", "Farming"};
    job3.isActive = true;
    job3.postedDate = time(nullptr);
    
    jobs.push_back(job3);
    jobTrie.insert(job3.jobType, job3.jobId);
    urgentQueue.addJob(job3);
    wageTree.insert(job3.dailywage, job3.jobId);
    location.addJob(job3.village, job3.district, job3.jobId);
    
    // Sample Job 4
    Job job4;
    job4.jobId = nextJobId++;
    job4.jobType = "Painting Work";
    job4.village = "Srirangam";
    job4.district = "Tiruchirappalli";
    job4.dailywage = 550;
    job4.workersNeeded = 2;
    job4.urgencyLevel = 2;
    job4.employerPhoneNo = "9000111222";
    job4.requiredSkills = {"Painting"};
    job4.isActive = true;
    job4.postedDate = time(nullptr);
    
    jobs.push_back(job4);
    jobTrie.insert(job4.jobType, job4.jobId);
    wageTree.insert(job4.dailywage, job4.jobId);
    location.addJob(job4.village, job4.district, job4.jobId);
    
    // Sample Workers
    Worker worker1;
    worker1.workerId = nextWorkerId++;
    worker1.name = "Selvam";
    worker1.phoneNo = "9876543211";
    worker1.village = "Thiruverumbur";
    worker1.skills = {"Harvesting", "Plowing", "Seeding"};
    worker1.minWage = 400;
    worker1.maxDistanceKm = 15;
    workerslist.addNode(worker1);
    
    Worker worker2;	
    worker2.workerId = nextWorkerId++;
    worker2.name = "Murugan";
    worker2.phoneNo = "9876543212";
    worker2.village = "Srirangam";
    worker2.skills = {"Mason Work", "Painting", "Construction"};
    worker2.minWage = 500;
    worker2.maxDistanceKm = 20;
    workerslist.addNode(worker2);
    
    Worker worker3;
    worker3.workerId = nextWorkerId++;
    worker3.name = "Kumar";
    worker3.phoneNo = "9876543213";
    worker3.village = "Lalgudi";
    worker3.skills = {"Planting", "Harvesting", "Basic Farming"};
    worker3.minWage = 350;
    worker3.maxDistanceKm = 10;
    workerslist.addNode(worker3);
    
    cout<<"\n Sample Data Loaded Successfully!\n";
    cout<<"   Jobs: " << jobs.size() << "\n";
    cout<<"   Workers: " << workerslist.getSize() << "\n";
}