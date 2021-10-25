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
	int m_io;
	int m_io1;
	int m_CSVariable;	//Variable that will be edited during critical section of a process

private:
	//PCB Information
	Process_State m_State;
	int m_PID;
	int m_ProgramCounter;
	int m_Registers;
	int m_MemoryLimits;
	int m_List_of_OpenFiles;
	int m_CPU_Scheduling_Information;
	int m_IO_Status;


public:
	int m_semephore;

	Process_Manager();
	//void setProcessNum(int processNum);
	void printP();
	void genVal();
	void executing(int useCPU);

	void wait(int m_semephore);
	void signal(int m_semephore);

	void genPCB();
	void setPIDincrements(int PN, int PC, int Reg);
	
	void dispatcher();

	//Getters
	int getCalc();
	int getCalc1();
	int getCalc2();
	int getIO();
	int getIO1();
};

class Process_Child :public Process_Manager {
private:
	int m_PID;

public:
	void genPCB();
};