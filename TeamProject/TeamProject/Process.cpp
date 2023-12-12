//
//  Process.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/1/23.
//

#include "Process.hpp"

Process :: Process(){
    processId = 0;
    arrivalTime = 0;
    serviceTime = 0;
    ioTime = 0;
    priority = 0;
    startTime = 0;
}
Process :: Process(int processId, int serviceTime){
    this->processId = processId;
    this->arrivalTime = 0;
    this->serviceTime = serviceTime;
    this->ioTime = 0;
    this->priority = 0;
    this->startTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = 0;
    this->startTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = priority;
    this->startTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority, int startTime){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = priority;
    this->startTime = startTime;
}
void Process :: setProcessId(int processId){
    this->processId = processId;
}
void Process :: setArrivalTime(int arrivalTime){
    this->arrivalTime = arrivalTime;
}
void Process :: setServiceTime(int serviceTime){
    this->serviceTime = serviceTime;
}
void Process :: setIOtime(int ioTime){
    this->ioTime = ioTime;
}
void Process :: setStartTime(int startTime){
    this->startTime = startTime;
}
int Process :: getProcessId(){
    return processId;
}
int Process :: getArrivalTime(){
    return arrivalTime;
}
int Process :: getServiceTime(){
    return serviceTime;
}
int Process :: getIOtime(){
    return ioTime;
}
int Process :: getStartTime(){
    return startTime;
}
int Process :: calculateFinishTime(){
    return startTime + serviceTime;
}
int Process :: calculateTurnAroundTime(){
    return calculateFinishTime() - arrivalTime;
}
int Process :: calculateNormalizedTAT(){
    return calculateTurnAroundTime()/serviceTime;
}
int Process :: calculateWaitTime(){
    return calculateFinishTime() - arrivalTime;
}
void Process :: printProcessInfo(){
    cout << "Arrival Time: " << this->arrivalTime << " time units" << endl;
    cout << "Service Time: " << this->serviceTime << " time units" << endl;
    cout << "I/O Time: " << this->ioTime << " time units" << endl;
    cout << "Turnaround Time: " << calculateTurnAroundTime() << " time units" << endl;
    cout << "Start Time: " << this->startTime << " time units" << endl;
    cout << "Finish Time: " << calculateFinishTime() << " time units" << endl;
}
void Process :: operator=(const Process &p){
    this->processId = p.processId;
    this->arrivalTime = p.arrivalTime;
    this->serviceTime = p.serviceTime;
    this->ioTime = p.ioTime;
    this->priority = p.priority;
    this->startTime = p.startTime;
}
bool Process :: operator==(const Process &p) const{
    return this->processId == p.processId
            && this->arrivalTime == p.arrivalTime
            && this->serviceTime == p.serviceTime
            && this->ioTime == p.ioTime
            && this->priority == p.priority;
}
