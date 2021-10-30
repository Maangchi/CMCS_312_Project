#pragma once
#include <vector>
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

enum Critical_Section {
	NO_CRITICAL_SECTION,
	READY_TO_ENTER_CS,
	ENTER_CRITICAL_SECTION,
	EXIT_CRITICAL_SECTION
};

class Process_Manager {
private:
	//Process Burst Cycle Information
	//int m_calculate;
	//int m_calculate1;
	//int m_calculate2;
	//int m_calculateTotal;
	//int m_io;
	//int m_io1;
	//int m_ioTotal;

	//Refined Burst IO cycle Members
	//int m_RemainingBurst;
	//int m_RemainingIO;
	std::vector<int> m_templatedCalculates;
	std::vector<int> m_templatedIO;
	int m_storedNum;
	int m_RemainingTemplateBurst;
	int m_RemainingTemplateIO;
	int m_totalCalcProcesses;
	int m_scheduleStartIO;

	int m_criticalSectionTicket;

private:
	//PCB Information
	int m_PID;
	int m_Priority;
	int m_ProgramCounter;
	int m_Registers;
	int m_MemoryLimits;
	int m_List_of_OpenFiles;
	int m_CPU_Scheduling_Information;
	int m_IO_Status;
	Process_State m_State;
	Critical_Section m_CriticalState;

public:
	const int size = 5;
	int m_semephore;
	int m_timeSlice = 25;
	int m_Changed_Num;

	//Constructor
	Process_Manager();

	//void setProcessNum(int processNum);
	void printP();
	void genVal();
	void executing(int useCPU);

	//Critical section operations
	void wait(int m_semephore);
	void signal(int m_semephore);

	//Generate PCB block information
	void genPCB();
	void printPCB();
	void printSchedule();

	//Scheduler
	//void RoundRobin(vector<Process_Manager*>& processes);

	//Getters
	//int getCalc();
	//int getCalc1();
	//int getCalc2();
	//int getCalcTotal();
	//int getIO();
	//int getIO1();
	int getIOTotal();
	int getState();
	int getRemainingBurst();
	int getIORemaining();
	int getProcessState();
	int getCriticalState() { return m_CriticalState; }
	int getRemainingTemplateBurst();
	int getRemainingTemplateIO();
	int getStoredNum() { return m_storedNum; }
	int getCriticalSectionTicket() { return m_criticalSectionTicket; }
	int getScheduleStartIO() { return m_scheduleStartIO; }
	int getTotalCalcProcesses() { return m_totalCalcProcesses; }
	std::vector<int>& getCalcVec() { return m_templatedCalculates; }
	std::vector<int>& getIOVec() { return m_templatedIO; }

	//Setters
	void setPIDincrements(int PN, int PC, int Reg);
	void setState(Process_State State);
	void setCriticalState(Critical_Section section);
	void setCriticalSectionTicket(int ticketNum);
	void setBurstRemaining(int remBurst);
	void setIORemaining(int remIO);
	void setRemainingTemplateBurst(int remTCalcs);
	void setRemainingTemplateIO(int remTIO);
	void setTotalCalcProcesses(int totalCalc);
	void setScheduleStartIO(int scheduleStartIO);
	void setStoredNum(int storedNum);
};

class Process_Child :public Process_Manager {
private:
	int m_PID;

public:
	void genPCB();
};