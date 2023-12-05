//
//  FCFS.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef FCFS_hpp
#define FCFS_hpp

#include <stdio.h>
#include "Algorithm.hpp"

class FCFS : public Algorithm{
    
private:

    
public:
    FCFS();
    FCFS(int numOfProcesses, Process processes[]);
    void implementAlg() override;
};

#endif /* FCFS_hpp */
