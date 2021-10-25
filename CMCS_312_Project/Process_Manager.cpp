#include "Process_Manager.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <map>

using namespace std;
Process_Manager::Process_Manager() {
	//Process Bursts Initialized
	m_calculate = 0;
	m_calculate1 = 0;
	m_calculate2 = 0;
	m_io = 0;
	m_io1 = 0;

	//Semephore initialized to 1
	m_semephore = 1;

	//PID Initialized
	m_PID = 0;
	m_ProgramCounter = 0;
	m_Registers = 0;
	m_MemoryLimits = 0;
	m_List_of_OpenFiles = 0;
	m_CPU_Scheduling_Information = 0;
	m_IO_Status = 0;
	Process_State::NEW;
}

void Process_Manager::dispatcher() {
	m_State = Process_State::READY;
}

void Process_Manager::genVal() {
	m_calculate = rand() % 100 + 5;
	m_calculate1 = rand() % 100 + 5;
	m_calculate2 = rand() % 100 + 5;
	m_io = rand() % 25 + 10;
	m_io1 = rand() % 25 + 10;
	m_CSVariable = rand() % 10;
}

void Process_Manager::genPCB() {
	m_PID++;
	m_ProgramCounter++;
	m_Registers++;
	m_MemoryLimits = rand() % 100 + 20;
	m_List_of_OpenFiles = 0;
	m_CPU_Scheduling_Information = rand() % 1;
	m_IO_Status = rand() % 1;
}

void Process_Child::genPCB() {
	Process_Manager::genPCB();
	m_PID += 1;
}

void Process_Manager::setPIDincrements(int PID, int PC, int Reg) {
	m_PID = PID;
	m_ProgramCounter = PC + 4;
	m_Registers = Reg + 8;
}

/*
void Process_Manager::setProcessNum(int processNum) {
	m_processNum = processNum;
}
*/

void Process_Manager::executing(int useCPU) {
	chrono::milliseconds timespane(useCPU);
	this_thread::sleep_for(timespane);
}


void Process_Manager::printP() {
	cout << "Process #" << m_PID << endl;
	cout << "CALCULATE\t" << m_calculate << endl;
	cout << "CALCULATE\t" << m_calculate1 << endl;
	cout << "I/O\t\t" << m_io << endl;
	cout << "CALCULATE\t" << m_calculate2 << endl;
	cout << "I/O\t\t" << m_io1 << endl << endl;
}

int Process_Manager::getCalc() {
	return m_calculate;
}
int Process_Manager::getCalc1() {
	return m_calculate1;
}
int Process_Manager::getCalc2() {
	return m_calculate2;
}
int Process_Manager::getIO() {
	return m_io;
}
int Process_Manager::getIO1() {
	return m_io1;
}


//Critical Section Semephore Manager
void Process_Manager::wait(int m_semephore) {
	while (m_semephore <= 0);
	m_semephore--;
}
void Process_Manager::signal(int m_semephore) {
	m_semephore++;
}
