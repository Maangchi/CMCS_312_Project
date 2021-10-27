#pragma once
namespace choices {
	enum Options
	{
		CALCULATE,
		IO,
		FORK,
		END,
	};
}

enum Process_State {
	NEW,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
};

class Process_Manager {
private:
	//Process Burst Cycle Information
	int m_calculate;
	int m_calculate1;
	int m_calculate2;
	int m_calculateTotal;
	int m_io;
	int m_io1;
	int m_ioTotal;
	int m_CSVariable;	//Variable that will be edited during critical section of a process

	int m_RemainingBurst;
	int m_RemainingIO;

private:
	//PCB Information
	int m_PID;
	int m_ProgramCounter;
	int m_Registers;
	int m_MemoryLimits;
	int m_List_of_OpenFiles;
	int m_CPU_Scheduling_Information;
	int m_IO_Status;
	Process_State m_State;


public:
	int m_semephore;
	int m_timeSlice = 15;


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
	int getCalc();
	int getCalc1();
	int getCalc2();
	int getCalcTotal();
	int getIO();
	int getIO1();
	int getIOTotal();
	int getState();
	int getRemainingBurst();
	int getIORemaining();
	int getProcessState();

	//Setters
	void setPIDincrements(int PN, int PC, int Reg);
	void setState(Process_State State);
	void setBurstRemaining(int remBurst);
	void setIORemaining(int remIO);
};

class Process_Child :public Process_Manager {
private:
	int m_PID;

public:
	void genPCB();
};