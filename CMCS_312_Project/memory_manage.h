#pragma once
#include <vector>
#include "Process_manager.h"

class memory_manage
{
private:
	int m_ProcessMemoryUsage;
public:
	memory_manage();
	void swapping(Process_Manager* process, std::vector<int> MemorySlot);
	void freeUpSpace(Process_Manager* process, std::vector<int> MemorySlot);

	//setters
	void setProcessMemoryUsage(std::vector<int> currentSlotUsage);

	//getters
	int getProcessMemoryUsage() { return m_ProcessMemoryUsage; }

	//printing functions
	void print_memory_info();

	//configs
	int m_TotalMemory;
	std::vector<int> m_Memory_Slots;
};

