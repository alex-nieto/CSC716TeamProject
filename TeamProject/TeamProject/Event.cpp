//
//  Event.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/5/23.
//

#include "Event.hpp"

Event :: Event(){
    time = 0;
    oldState = "";
    newState = "";
    process = NULL;
}
Event :: Event(int time, Process process, string newState, string oldState){
    this->time = time;
    this->oldState = oldState;
    this->newState = newState;
    this->process = process;
}
void Event :: setTime(int time){
    this->time = time;
}
void Event :: setOldState(string oldState){
    this->oldState = oldState;
}
void Event :: setNewState(string newState){
    this->newState = newState;
}
void Event :: setProcess(Process process){
    this->process = process;
}
int Event :: getTime(){
    return time;
}
string Event :: getOldState(){
    return oldState;
}
string Event :: getNewState(){
    return newState;
}
Process Event :: getProcess(){
    return process;
}
void Event :: printEventInfo(){
    cout << "At time " << time << ": Process " << process.getProcessId() << "moves from " << oldState << " to " << newState << endl;
}
void Event :: operator=(const Event &event){
    this->time = event.time;
    this->oldState = event.oldState;
    this->newState = event.newState;
    this->process = event.process;
}
bool Event :: operator<(Event &event){
    return this->time < event.time;
}
bool Event :: operator>(Event &event){
    return this->time > event.time;
}
bool Event :: operator<=(Event &event){
    return this->time <= event.time;
}
bool Event :: operator>=(Event &event){
    return this->time >= event.time;
}
bool Event :: operator==(Event &event){
    return this->time == event.time;
}
