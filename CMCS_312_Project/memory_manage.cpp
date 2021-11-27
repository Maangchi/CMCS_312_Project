#include "memory_manage.h"
#include <iostream>
#include <vector>

memory_manage::memory_manage() {
	m_Memory_Slots = {};
	m_ProcessMemoryUsage = 0;
	m_TotalMemory = 1024;
}

void memory_manage::swapping(Process_Manager* process, std::vector<int> MemorySlots){
	m_Memory_Slots.push_back(process->getMemoryUsed());
	
}

void memory_manage::freeUpSpace(Process_Manager* process, std::vector<int> MemorySlots) {
	for (auto& it : MemorySlots) {
		if (process->getMemoryUsed() == it) {
			it = 0;
		}
	}
	m_Memory_Slots = MemorySlots;
}

void memory_manage::print_memory_info() {

}

void memory_manage::setProcessMemoryUsage(std::vector<int> currentSlotUsage)
{
	int sum = 0;
	for (auto itr : currentSlotUsage) {
		sum += itr;
	}
	m_ProcessMemoryUsage = sum;
}