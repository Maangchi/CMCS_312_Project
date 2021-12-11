#pragma once
#include <vector>
#include <thread>
#include <mutex>

namespace choices {
	enum Options
	{
		CALCULATE,
		IO,
		SCHEDULE,
		FORK,
		END
	};
}

enum Process_State {
	NEW,
	READY,
	RUNNING,
	WAITING,
	TERMINATED,
};

enum Parent_Child {
	PARENT,
	CHILD,
	GRAND_CHILD
};

enum Critical_Section {
	NO_CRITICAL_SECTION,
	READY_TO_ENTER_CS,
	ENTER_CRITICAL_SECTION,
	EXIT_CRITICAL_SECTION
};

class Process_Manager{
private:
	std::vector<int> m_templatedCalculates;
	std::vector<int> m_templatedIO;
	int m_storedNum;
	int m_RemainingTemplateBurst;
	int m_RemainingTemplateIO;
	int m_totalCalcProcesses;
	int m_scheduleStartIO;
	int m_criticalSectionTicket;
	std::mutex m_mutex;

private:
	//PCB Information
	int m_PID;
	int m_ChildsPID;
	int m_Priority;	//PHASE 3 PRIORITIES
	int m_ProgramCounter;
	int m_Registers;
	int m_MemoryUsed;
	int m_List_of_OpenFiles;
	int m_CPU_Scheduling_Information;
	int m_IO_Status;
	int m_Resources;
	Process_State m_State;
	Critical_Section m_CriticalState;
	Parent_Child m_ParentOrChild;

public:
	int m_semephore;
	int m_timeSlice = 25;
	int m_Changed_Num;

	//Constructor
	Process_Manager();


	//Printers
	void printP();
	void printChildsParent();
	void printPCB();
	void printSchedule();

	//Critical section operations
	void wait(int m_semephore);
	void signal(int m_semephore);

	//Generate PCB block information
	void genPCB();

	//Getters
	int getState();
	int getProcessState();
	int getChildsPID() { return m_ChildsPID; }
	int getCriticalState() { return m_CriticalState; }
	int getParentChild() { return m_ParentOrChild; }
	int getRemainingTemplateBurst();
	int getRemainingTemplateIO();
	int getMemoryUsed() { return m_MemoryUsed; }
	int getStoredNum() { return m_storedNum; }
	int getCriticalSectionTicket() { return m_criticalSectionTicket; }
	int getScheduleStartIO() { return m_scheduleStartIO; }
	int getTotalCalcProcesses() { return m_totalCalcProcesses; }
	int getPID() { return m_PID; }
	int getResources() { return m_Resources; }
	std::vector<int>& getCalcVec() { return m_templatedCalculates; }
	std::vector<int>& getIOVec() { return m_templatedIO; }

	//Setters
	void setPIDincrements(int PN, int PC, int Reg);
	void setChildsPID(int ParentPID);
	void setState(Process_State State);
	void setCriticalState(Critical_Section section);
	void setParentChild(Parent_Child ParentChild);
	void setCriticalSectionTicket(int ticketNum);
	void setMemoryUsed(int MemoryInUse);
	void setPID(int PID);
	void setRemainingTemplateBurst(int remTCalcs);
	void setRemainingTemplateIO(int remTIO);
	void setTotalCalcProcesses(int totalCalc);
	void setScheduleStartIO(int scheduleStartIO);
	void setStoredNum(int storedNum);
	void setResources(int resources) { m_Resources = resources; }
};