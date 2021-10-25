#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Process_Manager.h"

using namespace std;

//function to show main menu
void menuShow(vector<Process_Manager*>& size) {
	cout << "\nNumber of Processes: " << size.size() << endl;
	cout << "Enter Option:" << endl;
	cout << "\tCALCULATE" << endl;
	cout << "\tIO" << endl;
	cout << "\tFORK" << endl;
	cout << "\tEND" << endl;
}

int mainMenu() {
	cout << "Enter the number of processes you would like" << endl;
	int numOfProcesses = 0;
	cin >> numOfProcesses;
	return numOfProcesses;
}

void createProcesses(vector<Process_Manager*>& processes, int howMany) {
	processes.reserve(howMany);
	for (int i = 0; i < howMany; i++) {
		Process_Manager* process = new Process_Manager;
		process->setPIDincrements(i,i,i);
		//process->setProcessNum(i);
		process->genPCB();
		process->genVal();
		processes.push_back(process);
	}
}


void printP(vector<Process_Manager*>& processes) {
	for (auto itr : processes) {
		itr->printP();
	}
}

void computeProcess(vector<Process_Manager*>& process) {
	int selection = 0;
	cout << "Select which process you would like to run: ";
	cin >> selection;
	process[selection]->printP();
	int c = process[selection]->getCalc();
	int c1 = process[selection]->getCalc1();
	int c2 = process[selection]->getCalc2();
	int processTime = c + c1 + c2;

	cout << "Your process Ran for: " << processTime << " Cycles" << endl;
}

void computeIO(vector<Process_Manager*>& process) {
	int selection = 0;
	cout << "Select which process you would like to run: ";
	cin >> selection;
	process[selection]->printP();
	int io = process[selection]->getIO();
	int io1 = process[selection]->getIO1();
	int processTime = io + io1;
	cout << "Your process waited for: " << processTime << " Cycles" << endl;
}


choices::Options resolveOptions(string input) {
	if (input == "CALCULATE") return choices::Options::CALCULATE;
	if (input == "IO") return choices::Options::IO;
	if (input == "FORK") return choices::Options::FORK;
	if (input == "END") return choices::Options::END;
}



std::ostream& operator<<(std::ostream& out, const Process_State value) {
	static std::map<Process_State, string> strings;
	if (strings.size() == 0) {
#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(NEW);
		INSERT_ELEMENT(READY);
		INSERT_ELEMENT(RUNNING);
		INSERT_ELEMENT(WAITING);
		INSERT_ELEMENT(TERMINATED);
#undef INSERT_ELEMENT
		return out << strings[value];
	}
}