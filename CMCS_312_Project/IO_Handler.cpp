#include "IO_Handler.h"
#include <iostream>
using namespace std;
IO_Handler::IO_Handler() {
	m_Peripheral1 = 5;
	m_Peripheral2 = 15;
	m_Peripheral3 = 30;
	m_Peripheral4 = 45;

	m_PeriphHit1 = 3;
	m_PeriphHit2 = 7;
	m_PeriphHit3 = 11;
	m_PeriphHit4 = 16;
}

void IO_Handler::external_Event(Process_Manager* process, int cycles)
{
	process->getRemainingTemplateBurst();
	int eventPoll = 0;
	for (int i = 0; i < cycles; i++) {
		eventPoll = rand() % 25;
		if (eventPoll == m_PeriphHit1){
			process->setRemainingTemplateBurst(process->getRemainingTemplateBurst() + m_Peripheral1);
			cout << "Need Peripheral 1 for this process: " << process->getPID() << endl;
			break;
		}
		if (eventPoll == m_PeriphHit2){
			process->setRemainingTemplateBurst(process->getRemainingTemplateBurst() + m_Peripheral2);
			cout << "Need Peripheral 2 for this process: " << process->getPID() << endl;
			break;
		}
		if (eventPoll == m_PeriphHit3){
			process->setRemainingTemplateBurst(process->getRemainingTemplateBurst() + m_Peripheral3);
			cout << "Need Peripheral 3 for this process: " << process->getPID() << endl;
			break;
		}
		if (eventPoll == m_PeriphHit4){
			process->setRemainingTemplateBurst(process->getRemainingTemplateBurst() + m_Peripheral4);
			cout << "Need Peripheral 4 for this process: " << process->getPID() << endl;
			break;
		}
	}
}

