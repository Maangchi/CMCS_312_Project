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
class Process_Manager {
private:
	int m_calculate;
	int m_calculate1;
	int m_calculate2;
	int m_io;
	int m_io1;
	int m_processNum;

public:
	Process_Manager();
	void setProcessNum(int processNum);
	void printP();
	void genVal();
	void executing(int useCPU);

	int getCalc();
	int getCalc1();
	int getCalc2();
	int getIO();
	int getIO1();
};
