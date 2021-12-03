#include "Process_Manager.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>

using namespace std;
Process_Manager::Process_Manager() {
	//Process Bursts Initialized
	//m_calculate = 0;
	//m_calculate1 = 0;
	//m_calculate2 = 0;
	//m_io = 0;
	//m_io1 = 0;

	//PCB Initialized
	m_PID = 0;
	m_Priority = 0;
	m_ProgramCounter = 0;
	m_Registers = 0;
	m_MemoryUsed = 0;
	m_List_of_OpenFiles = 0;
	m_CPU_Scheduling_Information = 0;
	m_IO_Status = 0;
	m_storedNum = 0;
	m_State = NEW;
	m_ParentOrChild = PARENT;
	
	m_CriticalState = NO_CRITICAL_SECTION;

	//m_RemainingBurst = 0;
	//m_RemainingIO = 0;

	//vector of stored calculates and IO
	m_templatedCalculates = {};
	m_templatedIO = {};

	//Critical Section
	m_semephore = 1;
}

void Process_Manager::genPCB() {
	m_PID;
	m_ProgramCounter;
	m_Registers;
	m_MemoryUsed = rand() % 350 + 50;
	m_List_of_OpenFiles = 0;
	m_CPU_Scheduling_Information = rand() % 1;
	m_IO_Status = rand() % 1;
	m_criticalSectionTicket = rand() % 2 + 1;
	m_storedNum = rand() % 200 + 50;
}

void Process_Manager::setPIDincrements(int PID, int PC, int Reg) {
	m_PID = PID;
	m_ProgramCounter = PC;
	m_Registers = Reg * 4;
}

void Process_Manager::printP() {
	const string process_state_names[5] = { "NEW", "READY", "RUNNING", "WAITING", "TERMINATED"};
	cout << "Process #" << m_PID << endl;
	cout << "Process State: " << process_state_names[m_State] << endl;
	for (auto itr : m_templatedCalculates) {
		cout << "CALCULATE\t" << itr << endl;
	}
	for (auto itr : m_templatedIO) {
		cout << "IO\t\t" << itr << endl;
	}
	cout << "Memory Used:\t" << m_MemoryUsed << endl;
	cout << endl;
}

void Process_Manager::printPCB() {
	const string process_state_names[6] = { "NEW", "READY", "RUNNING", "WAITING", "TERMINATED"};
	const string parent_or_child[2] = { "PARENT", "CHILD" };
	cout << "***Process Control Block****" << endl;
	cout << "Process State:\t" << process_state_names[m_State] << endl;
	cout << "PID:\t\t" << m_PID << endl;
	cout << "Process is a: " << parent_or_child[m_ParentOrChild] << endl;
	cout << "PC:\t\t" << m_ProgramCounter << endl;
	cout << "Register:\t" << m_Registers << endl;
	cout << "Memory Used:\t" << m_MemoryUsed << endl;
	cout << "OpenFiles:\t" << m_List_of_OpenFiles << endl;
	cout << "CPU Scheduling:\t" << m_CPU_Scheduling_Information << endl;
	cout << "IO_Status:\t" << m_IO_Status << endl;
	cout << "******************" << endl;
	cout << "Critical Section Entrance ID: " << m_criticalSectionTicket << endl;
	//cout << "Remaining Burst Cycles: " << m_RemainingBurst << endl;
	//cout << "Remaining IO Waiting: " << m_RemainingIO << endl << endl;
	cout << "Remaining Burst Cycles: " << m_RemainingTemplateBurst << endl;
	cout << "Remaining IO Waiting: " << m_RemainingTemplateIO << endl;
	if (m_Changed_Num != 0) {
		cout << "Changed Variable in Critical Section: " << m_Changed_Num << endl << endl;
	}
	else {
		cout << endl;
	}

}

void Process_Manager::printSchedule() {
	const string process_state_names[5] = { "NEW", "READY", "RUNNING", "WAITING", "TERMINATED" };
	const string parent_or_child[2] = { "PARENT", "CHILD" };
	const string critical_state_names[5] = { "NO_CRITICAL_SECTION", "READY_TO_ENTER_CS", "ENTER_CRITICAL_SECTION", "EXIT_CRITICAL_SECTION" };
	cout << "***Process in Schedule***" << endl;
	cout << "PID:\t\t\t" << m_PID << endl;
	cout << "Process is a: " << parent_or_child[m_ParentOrChild] << endl;
	cout << "Process Current State:\t" << process_state_names[m_State] << endl;
	cout << "Process Critical State:\t" << critical_state_names[m_CriticalState] << endl;
	//cout << "Remaining Burst Cycles:\t" << m_RemainingBurst << endl;
	//cout << "Remaining IO Waiting:\t" << m_RemainingIO << endl;
	cout << "Remaining Burst Cycles:\t" << m_RemainingTemplateBurst << endl;
	cout << "Remaining IO Waiting:\t" << m_RemainingTemplateIO << endl;
	cout << "*************************" << endl << endl;
}

void Process_Manager::printChildsParent() {
	cout << "Parents PID:\t" << m_ChildsPID << endl;
	cout << "PID:\t" << m_PID << endl;
}


int Process_Manager::getState() {
	return m_State;
}

//int Process_Manager::getRemainingBurst(){
//	return m_RemainingBurst;
//}
//
//int Process_Manager::getIORemaining() {
//	return m_RemainingIO;
//}

int Process_Manager::getProcessState() {
	return m_State;
}

void Process_Manager::setPID(int PID)
{
	m_PID = PID;
}

int Process_Manager::getRemainingTemplateBurst() {
	return m_RemainingTemplateBurst;
}

int Process_Manager::getRemainingTemplateIO() {
	return m_RemainingTemplateIO;
}

void Process_Manager::setScheduleStartIO(int scheduleStartIO) {
	m_scheduleStartIO = scheduleStartIO;
}

void Process_Manager::setCriticalSectionTicket(int ticketNum) {
	m_criticalSectionTicket = ticketNum;
}

void Process_Manager::setState(Process_State State) {
	m_State = State;
}

void Process_Manager::setCriticalState(Critical_Section section) {
	m_CriticalState = section;
}

void Process_Manager::setParentChild(Parent_Child ParentChild)
{
	m_ParentOrChild = ParentChild;
}

void Process_Manager::setStoredNum(int storedNum) {
	m_storedNum = storedNum;
}

//void Process_Manager::setBurstRemaining(int remBurst) {
//	m_RemainingBurst = remBurst;
//}
//
//void Process_Manager::setIORemaining(int remIO) {
//	m_RemainingIO = remIO;
//}

void Process_Manager::setRemainingTemplateBurst(int remTCalcs) {
	m_RemainingTemplateBurst = remTCalcs;
}
void Process_Manager::setRemainingTemplateIO(int remTIO) {
	m_RemainingTemplateIO = remTIO;
}

void Process_Manager::setTotalCalcProcesses(int totalCalc) {
	m_totalCalcProcesses = totalCalc;
}

//Critical Section Semephore Manager
void Process_Manager::wait(int semephore) {
	while (semephore <= 0);
	m_semephore--;
}
void Process_Manager::signal(int semephore) {
	m_semephore++;
}

void Process_Manager::setMemoryUsed(int MemoryInUse)
{
	m_MemoryUsed = MemoryInUse;
}

void Process_Manager::setChildsPID(int ParentPID)
{
	m_ChildsPID = ParentPID;
}
