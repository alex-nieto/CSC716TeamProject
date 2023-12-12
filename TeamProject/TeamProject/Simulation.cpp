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
bool Simulation :: readFile(){
    string filePath = input.substr(input.find("<") + 1);
    cout << input << endl;
    cout << "file path: " << filePath << endl;
    if(filePath == "" || filePath == " " || filePath == input){
        cout << "No file path indicated. Please try again." << endl;
        return true;
    }
    // open the file for reading
    filePath = "/Users/alexnieto/Desktop/testInputFile.txt";
    ifstream inputFile(filePath);
    if(inputFile.is_open()){
        // read Simulation from the file
        string simulationData;
        queue<string> parameterlist;
        string segment;
        int ioTime = 0;
        int serviceTime = 0;
        Process *processPtr = NULL;
        int count = 0;
        while (getline(inputFile, simulationData)){
            stringstream parameterInput(simulationData.substr(0, simulationData.find("\n")));
            while(getline(parameterInput, segment, ' '))
            {
                parameterlist.push(segment);
            }
            if(parameterlist.size() == 2 && numOfProcesses == 0){
                numOfProcesses = stoi(parameterlist.front());
                cout << "numOfProcesses: " << numOfProcesses << endl;
                parameterlist.pop();
                switchTime = stoi(parameterlist.front());
                cout << "switchTime: " << switchTime << endl;
                parameterlist.pop();
            }else{
                if(parameterlist.size() == 3){
                    if(count == 0){
                        Process p;
                        processPtr = &p;
                    }
                    if(processPtr->getProcessId() == 0){
                        processPtr->setProcessId(stoi(parameterlist.front()));
                        parameterlist.pop();
                        processPtr->setArrivalTime(stoi(parameterlist.front()));
                        parameterlist.pop();
                        count = stoi(parameterlist.front());
                        cout << "initial count: " << count << endl;
                    }else{
                        count--;
                        cout << "else count: " << count << endl;
                        parameterlist.pop();
                        serviceTime+=stoi(parameterlist.front());
                        cout << "else serviceTime: " << serviceTime << endl;
                        parameterlist.pop();
                        ioTime+=stoi(parameterlist.front());
                        cout << "else ioTime: " << ioTime << endl;
                    }
                    parameterlist.pop();
                }else if(parameterlist.size() == 2){
                    count--;
                    cout << "else if count: " << count << endl;
                    parameterlist.pop();
                    serviceTime+=stoi(parameterlist.front());
                    cout << "else if serviceTime: " << serviceTime << endl;
                    parameterlist.pop();
                }
                if(count == 0){
                    cout << "*serviceTime: " << serviceTime << endl;
                    cout << "*ioTime: " << ioTime << endl;
                    processPtr->setServiceTime(serviceTime);
                    processPtr->setIOtime(ioTime);
                    processList.push_back(*processPtr);
                    cout  << "PId: " << processList.back().getProcessId() << endl;
                    cout  << "PAt: " << processList.back().getArrivalTime() << endl;
                    cout  << "PSt " << processList.back().getServiceTime() << endl;
                    cout  << "PIo " << processList.back().getIOtime() << endl;
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
Process* Simulation :: copyProcessListToArr(){
    Process newProcessArr[numOfProcesses];
    int i = 0;
    for(Process process : processList){
        newProcessArr[i] = process;
        i++;
    }
    return newProcessArr;
}
void Simulation :: runSelectAlgorithm(){
    if(!readParameterInput()){
        int arrSize = 6;
        Algorithm* algorithToRun[6]{new FCFS(numOfProcesses,copyProcessListToArr()),new SJF(numOfProcesses,copyProcessListToArr(),switchTime),new SJF(1,numOfProcesses,copyProcessListToArr(),switchTime),
            new RR(10,numOfProcesses,copyProcessListToArr()),new RR(50,numOfProcesses,copyProcessListToArr()), new RR(100,numOfProcesses,copyProcessListToArr())};
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
        if(!input.find("sim")){
            if(!readFile())
                runSelectAlgorithm();
                //cout << "Compute Somthing" << endl;
        }else{
            cout << "Need to use sim command. Please try again." << endl;
        }
        return true;
    }
    return false;
}
