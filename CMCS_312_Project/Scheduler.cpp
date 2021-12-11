#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <future>
#include "Process_Manager.h"
#include "memory_manage.h"
#include "IO_Handler.h"

using namespace std;

void timeSim(int time);

// phase 2 threading. 2 threads, main and thread t1
void thread_calc(Process_Manager* process, int remaining) {
	process->printSchedule();
	int newRemaining = remaining - process->m_timeSlice;
	process->setRemainingTemplateBurst(newRemaining);
	cout << "Current Thread PID\t: " << process->getPID() << " " << endl;
	cout << "Calculations Ran by Thread: " << process->m_timeSlice << endl << endl;

	timeSim(process->m_timeSlice);
}

void thread_IO(Process_Manager* process, int remaining) {
	process->printSchedule();
	int newRemaining = remaining - process->m_timeSlice;
	process->setRemainingTemplateIO(newRemaining);
	cout << "Current Thread PID\t: " << process->getPID() << " " << endl;
	cout << "Waiting cycles of Thread: " << process->m_timeSlice << endl << endl;

	timeSim(process->m_timeSlice);
}

void cascade_terminate(vector<Process_Manager*>& processes, int PID) {
	for (auto itr : processes) {
		if ((itr->getParentChild() == CHILD || itr->getParentChild() == GRAND_CHILD) && PID == itr->getChildsPID() && itr->getState() != TERMINATED) {
			itr->setState(TERMINATED);
			cout << ":: ********************Track Cascade Termination********************** :: " << endl;
			itr->printChildsParent();
		}
	}
}

void print_Resources(int resources) {
	cout << "\n*************Resource Manager****************\n\t Used Resources: " << resources << endl << endl;
}

int usedResources = 0;
static int maxResources = 1042;

void resource_manager_add(int resources) {
	usedResources += resources;
}
void resource_manager_sub(int resources) {
	usedResources -= resources;
}

void deadlock_avoid(Process_Manager* process) {
	int need = process->getResources();
	if (need > (maxResources - usedResources)) {
		process->setState(READY);
		process->setResources(0);
		cout << "\n******Need Greater Than Available Resources******\n" << endl;
	}
}



void RoundRobin(vector<Process_Manager*>& processes) {
	int counting = 0;
	int watchValue = 0;
	int numOfProcesses = processes.size();
	IO_Handler io_handler;
	memory_manage memoryManager;
	memoryManager.setProcessMemoryUsage(memoryManager.m_Memory_Slots);
	cout << "Total Memory being Used: " << memoryManager.getProcessMemoryUsage() << endl;
	while(1){
		bool done = true;
		for (auto itr : processes) {
			counting += itr->m_timeSlice;
			io_handler.external_Event(itr, itr->m_timeSlice); //25 cycles are passed with each time the scheduler loops, thus for 25 cycles in each process, there is a chance for it to be interrupted by a peripheral device
			memoryManager.setProcessMemoryUsage(memoryManager.m_Memory_Slots);
			if (itr->getProcessState() == NEW) {
				itr->printSchedule();
				done = false;
				//fill up memory with new processes
				if ((memoryManager.getProcessMemoryUsage() + itr->getMemoryUsed()) > memoryManager.m_TotalMemory)
				{
					itr->setState(NEW);

					cout << memoryManager.getProcessMemoryUsage() << endl;
				}
				else {
					memoryManager.m_Memory_Slots.push_back(itr->getMemoryUsed());
					timeSim(1);
					for (auto itr : memoryManager.m_Memory_Slots) cout << "Memory Used Slot check: "  << "{" << itr << "}" << endl;
					cout << memoryManager.m_TotalMemory << endl;
					memoryManager.setProcessMemoryUsage(memoryManager.m_Memory_Slots);
					cout << "Total Memory being Used: " << memoryManager.getProcessMemoryUsage() << endl;
					itr->setState(READY);
				}
				if (itr->getCriticalSectionTicket() == 2) {
					itr->setCriticalState(READY_TO_ENTER_CS);
				}
			}
			if (itr->getProcessState() == READY) {
				resource_manager_sub(itr->getResources());
				print_Resources(usedResources);
				itr->setResources(0);
				itr->printSchedule();
				itr->setState(RUNNING);
				deadlock_avoid(itr);
			}
			if (itr->getProcessState() == RUNNING) {
				if (itr->getCriticalState() == READY_TO_ENTER_CS) {
					itr->setCriticalState(ENTER_CRITICAL_SECTION);
				}
				if (itr->getRemainingTemplateBurst() > 0){
					itr->setResources(itr->getRemainingTemplateBurst() + itr->getMemoryUsed());
					resource_manager_add(itr->getResources());
					print_Resources(usedResources);
					done = false;
					int processBurstRemaining = itr->getRemainingTemplateBurst() - itr->m_timeSlice;
					itr->setRemainingTemplateBurst(processBurstRemaining); //thread 1 (main thread)
					thread t1(thread_calc, ref(itr), processBurstRemaining);	// phase 2 thread 2 calcs
					t1.join(); //thread 2 finished computing and joined
					itr->printSchedule();
					if (itr->getRemainingTemplateIO() >= 0) {
						itr->setState(WAITING);
					}
					else {
						itr->setState(READY);
					}
					if (itr->getCriticalState() == ENTER_CRITICAL_SECTION) {
						itr->printSchedule();
						itr->wait(itr->m_semephore);
						itr->setCriticalSectionTicket(0);
						watchValue = itr->m_Changed_Num;
						itr->m_Changed_Num = itr->getStoredNum();
						watchValue = itr->m_Changed_Num;
						itr->signal(itr->m_semephore);
						itr->setCriticalState(EXIT_CRITICAL_SECTION);
					}
				}
				else if(itr->getRemainingTemplateBurst() < itr->m_timeSlice) {
					itr->setRemainingTemplateBurst(0);
					itr->setRemainingTemplateIO(0);
					itr->setState(TERMINATED);
					for (auto itr : memoryManager.m_Memory_Slots) cout << "Memory Freed Slot check: " << "{" << itr << "}" << endl;
					itr->printSchedule();
				}
			}
			if (itr->getProcessState() == WAITING) {
				done = false;
				int processIORemaining = itr->getRemainingTemplateIO() - itr->m_timeSlice;
				itr->setRemainingTemplateIO(processIORemaining); //thread 1 (main thread)
				thread t1(thread_IO, ref(itr), processIORemaining); //phase 2 thread 2 IO waits
				t1.join();	//thread 2 finished computing and joined
				timeSim(processIORemaining);
				itr->printSchedule();
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
			if (itr->getProcessState() == TERMINATED) {
				resource_manager_sub(itr->getResources());
				print_Resources(usedResources);
				itr->setResources(0);
				if (itr->getParentChild() == PARENT) cascade_terminate(processes, itr->getPID()); //terminates children if parent terminates before child
				memoryManager.freeUpSpace(itr, memoryManager.m_Memory_Slots);
				memoryManager.setProcessMemoryUsage(memoryManager.m_Memory_Slots);
			}
		}
		if (done == true) break;
	}
	for (auto itr : processes) { itr->printPCB(); }
	for (auto itr : memoryManager.m_Memory_Slots) cout << "Memory Used Slot check: " << "{" << itr << "}" << endl;
}