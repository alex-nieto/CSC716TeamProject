//
//  Event.hpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include "Process.hpp"

class Event{
    
private:
    //protected data members (accessible by child classes)
    int time; //time the event took place
    string oldState; //prevous state of the process                                            //Possible states: new, ready, running, blocked, or terminated
    string newState; //new state of the process                                                //if new state, old state will be null
    Process* process; //pointer to the process this event is referring to
    
public:
    //default constructor
    Event();
    //constructor initializer
    Event(int time, Process process, string newState, string oldState);
    //set methods
    void setTime(int time);
    void setOldState(string oldState);
    void setNewState(string newState);
    void setProcess(Process process);
    //get methods
    int getTime();
    string getOldState();
    string getNewState();
    Process* getProcess();
    //print methods
    void printEventInfo(); //outputs the event info (At time X: Process {id} moves from {state} to {state})
    //overloaded operator methods
    void operator=(const Event &event); //assign event to another event (= operator)
    bool operator<(const Event &event) const; //check if event is greater than another event (time)
    bool operator>(const Event &event) const; //check if event is less than another event (time)
    bool operator<=(const Event &event) const; //check if event is less than or equal to another event (time)
    bool operator>=(const Event &event) const; //check if event is greater than or equal to another event (time)
    bool operator==(const Event &event) const; //check if event is equal to another event (time)
};

#endif /* Event_hpp */
