//Brandon Willoughby
//CMSC 312
//Project Phase 1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Process_Manager.h"

using namespace std;

int howManyProcesses(); //shows how many process you would like to generate initially
int howManyCalcs();
int howManyIO();
choices::Options resolveOptions(string input);
void calculateTotalBurstsOfProcesses(vector<Process_Manager*>& processesCalcs);
void menuShow(vector<Process_Manager*>& size);
void createProcesses(vector<Process_Manager*>& processes, int howManyProcesses, int howManyCalcs, int howManyIO);
void createChildren(vector<Process_Manager*>& processes, vector<Process_Manager*>& ParentAndChild);
void printP(vector<Process_Manager*>& processes);
void computeProcess(vector<Process_Manager*>& process);
void computeIO(vector<Process_Manager*>& process);
void printPCB(vector<Process_Manager*>& processes);
void RoundRobin(vector<Process_Manager*>& processes);


int main() {
	vector<Process_Manager*> processes;
	vector<Process_Manager*> ParentAndChild;
	int processNum = howManyProcesses();
	int calcNum = howManyCalcs();
	int ioNum = howManyIO();
	string menu = "";
	createProcesses(processes, processNum, calcNum, ioNum);
	printP(processes);
	printPCB(processes);
	//printPCB(processes);
	while (true) {
		menuShow(ParentAndChild);
		cin >> menu;
		switch (resolveOptions(menu)) {
		case choices::Options::CALCULATE:
			computeProcess(ParentAndChild);
			break;
		case choices::Options::IO:
			computeIO(ParentAndChild);
			break;
		case choices::Options::SCHEDULE:
			calculateTotalBurstsOfProcesses(ParentAndChild);
			RoundRobin(ParentAndChild);
			break;
		case choices::Options::FORK:
			cout << "FORK you selected" << endl;
			createChildren(processes, ParentAndChild);
			break;
		case choices::Options::END:
			cout << "To Processor" << endl;
			return false;
			break;
		}
	}
}