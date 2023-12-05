//
//  RR.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef RR_hpp
#define RR_hpp

#include <stdio.h>
#include "Algorithm.hpp"

class RR : public Algorithm{
    
private:
    int quantum;
    
public:
    RR();
    RR(int quantum, int numOfProcesses, Process processes[]);
    void implementAlg() override;
};

#endif /* RR_hpp */
