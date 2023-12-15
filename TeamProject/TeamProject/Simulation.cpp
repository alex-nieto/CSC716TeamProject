//
//  Simulation.cpp
//  TeamProject
//
//  Created by Alex C Nieto on 12/4/23.
//

#include "Simulation.hpp"

Simulation :: Simulation(){
    input = "";
    detail = false;
    verbose = false;
    algToImplement = " ";
    numOfProcesses = 0;
    switchTime = -1;
}
Simulation :: Simulation(string input){
    this->input = input;
    detail = false;
    verbose = false;
    algToImplement = "";
    numOfProcesses = 0;
    switchTime = -1;
}
void Simulation :: setInput(string input){
    this->input = input;
}
string Simulation :: getInput(){
    return input;
}
bool Simulation :: getDetail(){
    return detail;
}
bool Simulation :: getVerbose(){
    return verbose;
}
string Simulation :: getAlgToImpl(){
    return algToImplement;
}
int Simulation :: getNumOfProcesses(){
    return numOfProcesses;
}
vector<Process> Simulation :: getProcesses(){
    return processList;
}
bool Simulation :: readFile(){
    string filePath = input.substr(input.find("<") + 1);
    if(filePath == "" || filePath == " " || filePath == input){
        cout << "No file path indicated. Please try again." << endl;
        return true;
    }
    //open the file for reading
    filePath = "/Users/alexnieto/Desktop/Desktop - Alex’s MacBook Pro/inputFile.txt";
    ifstream inputFile(filePath);
    if(inputFile.is_open()){
        //temp variables
        string simulationData;
        queue<string> parameterlist;
        string segment;
        int ioTime = 0;
        int serviceTime = 0;
        Process *processPtr = NULL;
        //count will keep track of the line of cpu time and io time
        int count = 0;
        //getting each line
        while (getline(inputFile, simulationData)){
            //geting each input of the line
            stringstream parameterInput(simulationData.substr(0, simulationData.find("\n")));
            while(getline(parameterInput, segment, ' '))
            {
                parameterlist.push(segment);
            }
            //checking for first line
            if(parameterlist.size() == 2 && numOfProcesses == 0){
                numOfProcesses = stoi(parameterlist.front());
                parameterlist.pop();
                switchTime = stoi(parameterlist.front());
                parameterlist.pop();
            }else{
                //otherwise we check for next line(s)
                if(parameterlist.size() == 3){
                    if(count == 0){
                        Process p;
                        processPtr = &p;
                    }
                    //check for process
                    if(processPtr->getProcessId() == 0){
                        processPtr->setProcessId(stoi(parameterlist.front()));
                        parameterlist.pop();
                        processPtr->setArrivalTime(stoi(parameterlist.front()));
                        parameterlist.pop();
                        count = stoi(parameterlist.front());
                    }else{
                        count--;
                        parameterlist.pop();
                        serviceTime+=stoi(parameterlist.front());
                        parameterlist.pop();
                        ioTime+=stoi(parameterlist.front());
                    }
                    parameterlist.pop();
                }else if(parameterlist.size() == 2){
                    count--;
                    parameterlist.pop();
                    serviceTime+=stoi(parameterlist.front());
                    parameterlist.pop();
                }
                //if hit count, then save process to list
                if(count == 0){
                    processPtr->setServiceTime(serviceTime);
                    processPtr->setIOtime(ioTime);
                    processList.push_back(*processPtr);
                    ioTime = 0;
                    serviceTime = 0;
                }
            }
        }
        // close the file
        inputFile.close();
    }else{
        cout << "Unable to open file" << endl;
        return true;
    }
    return false;
}
bool Simulation :: readParameterInput(){
    stringstream parameterInput(input.substr(0, input.find("<")));
    string segment;
    vector<string> parameterlist;
    while(getline(parameterInput, segment, '-'))
    {
        parameterlist.push_back(segment);
    }
    for(int i = 1; i < parameterlist.size(); i++ ){
        if(parameterlist[i] == "d " || parameterlist[i] == "d"){
            this->detail = true;
        }else if(parameterlist[i] == "v " || parameterlist[i] == "v"){
            this->verbose = true;
        }else if(parameterlist[i].find("a") || parameterlist[i].find("a ")){
            this->algToImplement = parameterlist[i].substr(input.find("a")+1);
        }
    }
    return false;
}
void Simulation :: runAlgorithm(Algorithm** algorithToRun, int arrSize){
    for(int i = 0; i < arrSize; i++){
        algorithToRun[i]->implementAlg();
        algorithToRun[i]->printAlgorithmInfo();
        if(detail){
            algorithToRun[i]->printProcessInfo();
        }
        if(verbose){
            algorithToRun[i]->printProcessEvents();
        }
        cout << endl;
    }
}
void Simulation :: runSelectAlgorithm(){
    if(!readParameterInput()){
        int arrSize = 6;
        Algorithm* algorithToRun[6]{new FCFS(numOfProcesses,processList,switchTime),new SJF(numOfProcesses,processList,switchTime),new SJF(1,numOfProcesses,processList,switchTime),
            new RR(10,numOfProcesses,processList,switchTime),new RR(50,numOfProcesses,processList,switchTime), new RR(100,numOfProcesses,processList,switchTime)};
        if(algToImplement != ""){
            arrSize = 1;
            if(algToImplement == "FCFS "){
                runAlgorithm(&algorithToRun[0], arrSize);
            }else if (algToImplement == "SJF "){
                //algorithToRun = new SJF(0,numOfProcesses,processes);
                runAlgorithm(&algorithToRun[1], arrSize);
            }else if (algToImplement == "SRTN "){
                //algorithToRun = new SJF(1,numOfProcesses,processes);
                runAlgorithm(&algorithToRun[2], arrSize);
            }else if (algToImplement == "RR10 " || algToImplement == "RR 10 "){
                runAlgorithm(&algorithToRun[3], arrSize);
            }else if (algToImplement == "RR50 " || algToImplement == "RR 50 "){
                runAlgorithm(&algorithToRun[4], arrSize);
            }else if (algToImplement == "RR100 " || algToImplement == "RR 100 "){
                runAlgorithm(&algorithToRun[5], arrSize);
            }
        }else{
            runAlgorithm(algorithToRun, arrSize);
        }
    }
}
bool Simulation :: execute(){
    if(input != "" && input != "exit"){
        if(input.find("sim") == 0){
            if(!readFile())
                runSelectAlgorithm();
        }else{
            cout << "Need to use sim command. Please try again." << endl;
        }
        return true;
    }
    return false;
}
