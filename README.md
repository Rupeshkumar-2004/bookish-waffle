# Rural Job Portal System 🌾

A C++ console application connecting rural workers with local employment opportunities, demonstrating advanced data structures and algorithms.

## Features

- **Job Posting & Search** - Employers post jobs, workers find opportunities
- **Autocomplete Search** - Type-ahead job title suggestions
- **Wage-based Filtering** - Find jobs within salary range
- **Location Search** - Discover jobs by village/district
- **Urgent Jobs Queue** - Priority-based job listings
- **Skill Pathways** - Learn related skills and prerequisites
- **Worker Registry** - Manage worker profiles and skills

## Data Structures Implemented

| Structure | Purpose | Time Complexity |
|-----------|---------|-----------------|
| **Trie** | Job title autocomplete | O(m) search |
| **AVL Tree** | Wage range queries | O(log n) insert/search |
| **Priority Queue** | Urgent jobs (max-heap) | O(1) peek, O(log n) insert |
| **Graph** | Skill relationships (BFS/DFS) | O(V+E) traversal |
| **Doubly Linked List** | Worker records | O(1) insert, O(n) search |
| **Hash Table** | Location-based lookup | O(1) average case |

## Project Structure

```
├── main.cpp                    # Entry point
├── JobPortal.cpp              # Core logic
└── include/
    ├── JobPortal.h            # Main class
    ├── Structures.h           # Job & Worker structs
    ├── TrieNode.h             # Autocomplete
    ├── AVLTree.h              # Wage indexing
    ├── PriorityQueue.h        # Urgent jobs
    ├── Graph.h                # Skill graph
    ├── LinkedList.h           # Worker list
    └── HashTable.h            # Location index
```

## Compilation & Execution

```bash
# Compile
g++ -std=c++17 main.cpp JobPortal.cpp -I./include -o job_portal

# Run
./job_portal
```

## Usage

1. **Load Sample Data** (Option 10) - Populate with test jobs/workers
2. **Search Jobs** (Options 1, 4, 6) - Find by title, wage, or location
3. **View Urgent Jobs** (Option 3) - See high-priority listings
4. **Explore Skills** (Option 2) - Discover learning paths
5. **Manage Workers** (Options 5, 8) - Register and view workers

## Sample Data Included

- 4 jobs across Tiruchirappalli district (Rice Harvesting, Construction, etc.)
- 3 workers with various skills (Farming, Masonry, Painting)
- Pre-seeded skill graph with learning paths

## Key Algorithms

- **Prefix Matching** - Trie-based autocomplete
- **Range Queries** - AVL tree in-order traversal
- **Topological Sort** - Skill prerequisite ordering
- **BFS** - Related skill discovery
- **Heap Operations** - Priority-based job retrieval

## Time Complexity Summary

- Job insertion: **O(m + log n)** - Trie + AVL operations
- Prefix search: **O(p + k)** - p = prefix length, k = results
- Wage range query: **O(log n + k)** - k = matching jobs
- Location lookup: **O(1)** - Hash table average case

## Future Enhancements

- Job application tracking
- Distance-based matching (geo-coordinates)
- Skill proficiency levels
- Job expiration handling
- Persistent storage (database integration)

---

**Built with:** C++17 | STL Containers | Custom Data Structures