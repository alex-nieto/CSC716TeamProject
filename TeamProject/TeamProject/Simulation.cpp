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
    Process* processes = NULL;
}
Simulation :: Simulation(string input){
    this->input = input;
    detail = false;
    verbose = false;
    algToImplement = "";
    numOfProcesses = 0;
    Process* processes = NULL;
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
    filePath = "/Users/acnieto/Library/CloudStorage/OneDrive-AmericanExpress/Desktop/in.txt";
    ifstream inputFile(filePath);
    if (inputFile.is_open()){
        // read Simulation from the file
        string simulationData;
        while (getline(inputFile, simulationData)){
            // process the Simulation
            cout << simulationData << endl;
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
        Algorithm* algorithToRun[6]{new FCFS(numOfProcesses,processes),new SJF(numOfProcesses,processes),new SJF(1,numOfProcesses,processes),
            new RR(10,numOfProcesses,processes),new RR(50,numOfProcesses,processes), new RR(100,numOfProcesses,processes)};
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
        }else{
            cout << "Need to use sim command. Please try again." << endl;
        }
        return true;
    }
    return false;
}
