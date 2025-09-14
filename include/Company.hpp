// Company.hpp
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// Represents a company registered in the system
struct Company {
    std::string companyId;           // Unique identifier (e.g., email or UUID)
    std::string companyName;         // Company name
    std::string ownerId;             // The userId of the person who registered
    std::vector<std::string> jobIds; // Jobs posted by this company
};

// Global storage for companies (acts like an in-memory database)
inline std::unordered_map<std::string, Company> company_data;