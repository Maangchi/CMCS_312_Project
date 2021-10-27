//Brandon Willoughby
//CMSC 312
//Project Phase 1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Process_Manager.h"

using namespace std;

int mainMenu();	//shows how many process you would like to generate initially
choices::Options resolveOptions(string input);
void menuShow(vector<Process_Manager*>& size);
void createProcesses(vector<Process_Manager*>& processes, int howMany);
void printP(vector<Process_Manager*>& processes);
void computeProcess(vector<Process_Manager*>& process);
void computeIO(vector<Process_Manager*>& process);
void printPCB(vector<Process_Manager*>& processes);
void RoundRobin(vector<Process_Manager*>& processes);

int main() {
	vector<Process_Manager*> processes;
	int numP = 0;
	string menu = "";
	numP = mainMenu();
	createProcesses(processes, numP);
	printP(processes);
	while (true) {
		menuShow(processes);
		cin >> menu;
		switch (resolveOptions(menu)) {
		case choices::Options::CALCULATE:
			//computeProcess(processes);
			//printPCB(processes);
			RoundRobin(processes);
			break;
		case choices::Options::IO:
			computeIO(processes);
			break;
		case choices::Options::FORK:
			cout << "FORK you selected" << endl;
			break;
		case choices::Options::END:
			cout << "To Processor" << endl;
			return false;
			break;
		}
	}
}