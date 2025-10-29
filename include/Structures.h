#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//structure for job..
struct Job{
    int jobId;
    string jobType;
    string village;
    string district;
    double dailywage;
    int workersNeeded;
    string employerPhoneNo;
    int urgencyLevel;
    vector<string> requiredSkills;
    bool isActive;
    time_t postedDate;
};

//structure for worker...
struct Worker{
    int workerId;
    string name;
    string phoneNo;
    string village;
    string district;
    vector<string> skills;
    double minWage;
    int maxDistanceKm;;
};

#endif

