#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Process_Manager.h"

using namespace std;

void RoundRobin(vector<Process_Manager*>& processes) {
	int counting = 0;
	int watchValue = 0;
	while(1){
		bool done = true;
		for (auto itr : processes) {
			counting += itr->m_timeSlice;
			if (itr->getProcessState() == NEW) {
				itr->printSchedule();
				if (itr->getCriticalSectionTicket() == 3) {
					itr->setCriticalState(READY_TO_ENTER_CS);
				}
				itr->setState(READY);
			}
			if (itr->getProcessState() == READY) {
				itr->printSchedule();
				itr->setState(RUNNING);
			}
			if (itr->getProcessState() == RUNNING) {
				itr->printSchedule();
				//if (itr->getRemainingBurst() > 0) {
				if (itr->getCriticalState() == READY_TO_ENTER_CS) {
					itr->setCriticalState(ENTER_CRITICAL_SECTION);
				}
				if (itr->getRemainingTemplateBurst() > 0){
					done = false;
					//int timeRemaining = itr->getRemainingBurst() - itr->m_timeSlice;
					int processBurstRemaining = itr->getRemainingTemplateBurst() - itr->m_timeSlice;
					//itr->setBurstRemaining(timeRemaining);
					itr->setRemainingTemplateBurst(processBurstRemaining);
					if (itr->getRemainingTemplateIO() >= 0) {
						itr->setState(WAITING);
					}
					else {
						itr->setState(READY);
					}
					if (itr->getCriticalState() == ENTER_CRITICAL_SECTION) {
						itr->wait(itr->m_semephore);
						itr->setCriticalSectionTicket(0);
						watchValue = itr->m_Changed_Num;
						itr->m_Changed_Num = itr->getStoredNum();
						watchValue = itr->m_Changed_Num;
						itr->signal(itr->m_semephore);
						itr->setCriticalState(EXIT_CRITICAL_SECTION);
					}
				}
				//else if(itr->getRemainingBurst() < itr->m_timeSlice) {
				else if(itr->getRemainingTemplateBurst() < itr->m_timeSlice) {
					//itr->setBurstRemaining(0);
					itr->setRemainingTemplateBurst(0);
					itr->setRemainingTemplateIO(0);
					itr->setState(TERMINATED);
					itr->printSchedule();
				}
			}
			if (itr->getProcessState() == WAITING) {
				done = false;
				itr->printSchedule();
				int processIORemaining = itr->getRemainingTemplateIO() - itr->m_timeSlice;
				itr->setRemainingTemplateIO(processIORemaining);
				if (itr->getScheduleStartIO() > itr->getRemainingTemplateIO()) {
					itr->setState(WAITING);
				}
				else{
					itr->setState(READY);
				}
				if (itr->getRemainingTemplateBurst() < counting && itr->getScheduleStartIO() > itr->getRemainingTemplateIO()) {
					itr->setState(READY);
				}
			}
		}
		if (done == true) break;
	}
	for (auto itr : processes) {
		itr->printPCB();
	}
}
