#pragma once
#include "memory_manage.h"
#include "Process_manager.h"

class IO_Handler
{
public:
	IO_Handler();

	int m_Peripheral1;
	int m_Peripheral2;
	int m_Peripheral3;
	int m_Peripheral4;

	int m_PeriphHit1;
	int m_PeriphHit2;
	int m_PeriphHit3;
	int m_PeriphHit4;

	void external_Event(Process_Manager* process, int remainingIO);
};

