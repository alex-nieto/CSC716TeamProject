//
//  Process.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/1/23.
//

#include "Process.hpp"

Process :: Process(){
    processId = 0;
    arrivalTime = -1;
    serviceTime = 0;
    ioTime = 0;
    priority = 0;
    startTime = -1;
    finishTime = 0;
}
Process :: Process(int processId, int serviceTime){
    this->processId = processId;
    this->arrivalTime = 0;
    this->serviceTime = serviceTime;
    this->ioTime = 0;
    this->priority = 0;
    this->startTime = -1;
    this->finishTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = 0;
    this->startTime = -1;
    this->finishTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = priority;
    this->startTime = -1;
    this->finishTime = 0;
}
Process :: Process(int processId, int arrivalTime, int serviceTime, int ioTime, int priority, int startTime){
    this->processId = processId;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
    this->ioTime = ioTime;
    this->priority = priority;
    this->startTime = startTime;
    this->finishTime = 0;
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
void Process :: setFinishTime(int finishTime){
    this->finishTime = finishTime;
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
int Process :: getFinishTime(){
    return finishTime;
}
int Process :: calculateFinishTime(){
    return startTime + serviceTime;
}
int Process :: calculateTurnAroundTime(){
    return finishTime - arrivalTime;
}
int Process :: calculateNormalizedTAT(){
    return calculateTurnAroundTime()/serviceTime;
}
int Process :: calculateWaitTime(){
    return finishTime - arrivalTime;
}
void Process :: printProcessInfo(){
    cout << "Arrival Time: " << this->arrivalTime << " time units" << endl;
    cout << "Service Time: " << this->serviceTime << " time units" << endl;
    cout << "I/O Time: " << this->ioTime << " time units" << endl;
    cout << "Turnaround Time: " << calculateTurnAroundTime() << " time units" << endl;
    cout << "Start Time: " << this->startTime << " time units" << endl;
    cout << "Finish Time: " << finishTime << " time units" << endl;
}
Process& Process :: operator=(const Process &process){
    this->processId = process.processId;
    this->arrivalTime = process.arrivalTime;
    this->serviceTime = process.serviceTime;
    this->ioTime = process.ioTime;
    this->priority = process.priority;
    this->startTime = process.startTime;
    return *this;
}
bool Process :: operator==(const Process &p) const{
    return this->processId == p.processId;
}
