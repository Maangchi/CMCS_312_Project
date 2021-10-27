#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Process_Manager.h"

using namespace std;

template <typename Process_Manager>
void moveItemToBack(vector<Process_Manager*>& v, size_t itemIndex)
{
	auto it = v.begin() + itemIndex;
	std::rotate(it, it + 1, v.end());
}

void RoundRobin(vector<Process_Manager*>& processes) {
	
	for (auto itr : processes){
		if (itr->getProcessState() == NEW) {
			itr->setState(READY);
		}
	}
	for (auto itr : processes) {
		if (itr->getProcessState() == READY) {
			itr->setState(RUNNING);
		}
	}
	while(1){
		bool done = true;
		for (auto itr : processes) {
			if (itr->getProcessState() == RUNNING) {
				if (itr->getRemainingBurst() > 0) {
					done = false;
					int timeRemaining = itr->getRemainingBurst() - itr->m_timeSlice;
					itr->setBurstRemaining(timeRemaining);
					itr->setState(WAITING);
					itr->printSchedule();
				}
				else if(itr->getRemainingBurst() < itr->m_timeSlice) {
					itr->setBurstRemaining(0);
					itr->setState(TERMINATED);
					itr->printSchedule();
				}
				if (itr->getProcessState() == WAITING) {
					itr->setIORemaining(0);
					itr->setState(RUNNING);
					itr->printSchedule();
				}
				if (itr->getState() == TERMINATED) {
					itr->setBurstRemaining(0);
					itr->printSchedule();
				}
			}
		}
		if (done == true) break;
	}
}