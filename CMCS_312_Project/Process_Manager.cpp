#include "Process_Manager.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
/*
string_code hashit(std::string const& inString) {
	if (inString == "CALCULATE") return CALCULATE;
	if (inString == "IO") return IO;
	if (inString == "FORK") return FORK;
}
*/

Process_Manager::Process_Manager() {
	m_calculate = 0;
	m_calculate1 = 0;
	m_calculate2 = 0;
	m_io = 0;
	m_io1 = 0;
	m_processNum = 0;
}

void Process_Manager::genVal() {
	m_processNum += 1;
	m_calculate = rand() % 100 + 5;
	m_calculate1 = rand() % 100 + 5;
	m_calculate2 = rand() % 100 + 5;
	m_io = rand() % 25 + 10;
	m_io1 = rand() % 25 + 10;
}

void Process_Manager::setProcessNum(int processNum) {
	m_processNum = processNum;
}

void Process_Manager::executing(int useCPU) {
	chrono::milliseconds timespane(useCPU);
	this_thread::sleep_for(timespane);
}


void Process_Manager::printP() {
	cout << "Process #" << m_processNum << endl;
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