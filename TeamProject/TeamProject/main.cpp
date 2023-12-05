//
//  main.cpp
//  CSC 716 TeamProject
//
//  Created by Alex C Nieto on 11/27/23.
//

#include <iostream>
#include "Simulation.hpp"

int main() {
    Simulation* simulation; //simulation class pointer created
    string input = ""; //string for input
    do{
        //asking for user input
        cout << "$ ";
        getline(cin,input);
        Simulation data(input); //creating new simulation object and passing input into constructor
        simulation = &data; //updating the pointer to access new simulation object
    }while(simulation->execute()); //execute simulation
    return 0;
}
