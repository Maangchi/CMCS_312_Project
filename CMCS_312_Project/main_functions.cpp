#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <numeric>
#include <chrono>
#include <thread>
#include "Process_Manager.h"

using namespace std;

//function to show main menu
void menuShow(vector<Process_Manager*>& size) {
	cout << "\nNumber of Processes: " << size.size() << endl;
	cout << "Enter Option:" << endl;
	cout << "\tCALCULATE" << endl;
	cout << "\tIO" << endl;
	cout << "\tSCHEDULE" << endl;
	cout << "\tFORK" << endl;
	cout << "\tEND" << endl;
}

int howManyProcesses() {
	int numOfProcesses = 0;
	cout << "Enter the number of processes you would like" << endl;
	cin >> numOfProcesses;
	return numOfProcesses;
}
int howManyCalcs() {
	int numOfCalcs = 0;
	cout << "Enter the number of calculates you would like" << endl;
	cin >> numOfCalcs;
	return numOfCalcs;
}
int howManyIO() {
	int numOfIO = 0;
	cout << "Enter the number of IO you would like" << endl;
	cin >> numOfIO;
	return numOfIO;
}

void createProcesses(vector<Process_Manager*>& processes, int howManyProcesses, int howManyCalcs, int howManyIO) {
	processes.reserve(howManyProcesses);
	vector<int>vecCalcs;
	vector<int>vecIO;
	for (int i = 0; i < howManyProcesses; i++) {
		Process_Manager* process = new Process_Manager;
		process->setPIDincrements(i, i, i);
		process->genPCB();
		//process->genVal();
		for (int j = 0; j < howManyCalcs; j++) {
			int randy = rand() % 100 + 5;
			vecCalcs.push_back(randy);
		}
		for (int k = 0; k < howManyIO; k++) {
			int randy = rand() % 30 + 10;
			vecIO.push_back(randy);
		}
		for (auto itr : vecCalcs) {
			process->getCalcVec().push_back(itr);
		}
		for (auto itr : vecIO) {
			process->getIOVec().push_back(itr);
		}
		int sumC = accumulate(vecCalcs.begin(), vecCalcs.end(), 0);
		int sumIO = accumulate(vecIO.begin(), vecIO.end(), 0);
		process->setRemainingTemplateBurst(sumC);
		process->setRemainingTemplateIO(sumIO);
		process->setScheduleStartIO(sumIO);
		vecCalcs = {};
		vecIO = {};
		processes.push_back(process);
	}
}


void createChildren(vector<Process_Manager*>& processes, vector<Process_Manager*>& processesAndChildren)
{
	vector<Process_Manager*> children;
	for (auto itr : processes) {
		Process_Manager* child = new Process_Manager;
		child->setParentChild(CHILD);
		child->setPID(itr->getPID() + processes.size());
		child->setRemainingTemplateBurst(itr->getRemainingTemplateBurst());
		child->setRemainingTemplateIO(itr->getRemainingTemplateIO());
		child->setChildsPID(itr->getPID());
		child->setMemoryUsed(itr->getMemoryUsed());
		cout << "child of process: " << itr->getPID() - children.size() << endl;
		children.push_back(child);
	}
	processesAndChildren.reserve(processes.size() + children.size());
	processesAndChildren.insert(processesAndChildren.end(), processes.begin(), processes.end());
	processesAndChildren.insert(processesAndChildren.end(), children.begin(), children.end());
	for (auto itr : processesAndChildren) {
		itr->printPCB();
	}

}

void createGrandChildren(vector<Process_Manager*>& processes, vector<Process_Manager*>& processesAndChildren)
{
	vector<Process_Manager*> grandChildren;
	for (auto itr : processes) {
		if (itr->getParentChild() == CHILD) {
			Process_Manager* grandChild = new Process_Manager;
			grandChild->setParentChild(GRAND_CHILD);
			grandChild->setPID(itr->getPID() + processes.size()/2);
			grandChild->setRemainingTemplateBurst(itr->getRemainingTemplateBurst());
			grandChild->setRemainingTemplateIO(itr->getRemainingTemplateIO());
			grandChild->setChildsPID(itr->getPID());
			grandChild->setMemoryUsed(itr->getMemoryUsed());
			cout << "grandChild of process: " << itr->getPID() - grandChildren.size() << endl;
			grandChildren.push_back(grandChild);
		}
	}
	processesAndChildren.reserve(processes.size() + grandChildren.size());
	processesAndChildren.insert(processesAndChildren.end(), processes.begin(), processes.end());
	processesAndChildren.insert(processesAndChildren.end(), grandChildren.begin(), grandChildren.end());
	for (auto itr : processesAndChildren) {
		itr->printPCB();
	}

}

void printP(vector<Process_Manager*>& processes) {
	for (auto itr : processes) {
		itr->printP();
	}
}

void timeSim(int time) {
	chrono::milliseconds timespane(time);
	this_thread::sleep_for(timespane);
}

void printPCB(vector<Process_Manager*>& processes) {
	for (auto itr : processes) {
		itr->printPCB();
	}
}

void computeProcess(vector<Process_Manager*>& process) {
	int selection = 0;
	cout << "Select which process you would like to run: ";
	cin >> selection;
	if (selection >= process.size() || selection < 0) {
		cout << "\nYou have entered too high of a number" << endl;
		return;
	}
	timeSim(process[selection]->getRemainingTemplateBurst());
	process[selection]->printP();
	int total = process[selection]->getRemainingTemplateBurst();
	cout << "Your process Ran for: " << total << " Cycles" << endl;
}

void computeIO(vector<Process_Manager*>& process) {
	int selection = 0;
	cout << "Select which process you would like to run: ";
	cin >> selection;
	if (selection >= process.size() || selection < 0) {
		cout << "\nYou have entered too high of a number" << endl;
		return;
	}
	timeSim(process[selection]->getRemainingTemplateIO());
	process[selection]->printP();
	int io = process[selection]->getRemainingTemplateIO();
	cout << "Your process waited for: " << io << " Cycles" << endl;
}

void calculateTotalBurstsOfProcesses(vector<Process_Manager*>& processesCalcs) {
	int sum = 0;
	for (auto itr : processesCalcs) {
		sum += itr->getRemainingTemplateBurst() + itr->getTotalCalcProcesses();
	}
	for (auto itr : processesCalcs) {
		itr->setTotalCalcProcesses(sum);
	}
}

choices::Options resolveOptions(string input) {
	if (input == "CALCULATE") return choices::Options::CALCULATE;
	if (input == "IO") return choices::Options::IO;
	if (input == "SCHEDULE") return choices::Options::SCHEDULE;
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

std::ostream& operator<<(std::ostream& out, const Critical_Section value) {
	static std::map<Critical_Section, string> strings;
	if (strings.size() == 0) {
#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(NO_CRITICAL_SECTION);
		INSERT_ELEMENT(READY_TO_ENTER_CS);
		INSERT_ELEMENT(ENTER_CRITICAL_SECTION);
		INSERT_ELEMENT(EXIT_CRITICAL_SECTION);
#undef INSERT_ELEMENT
		return out << strings[value];
	}
}

std::ostream& operator<<(std::ostream& out, const Parent_Child value) {
	static std::map<Parent_Child, string> strings;
	if (strings.size() == 0) {
#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(PARENT);
		INSERT_ELEMENT(CHILD);
		INSERT_ELEMENT(GRAND_CHILD);
#undef INSERT_ELEMENT
		return out << strings[value];
	}
}