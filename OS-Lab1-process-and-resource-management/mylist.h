#pragma once
#include <vector>
#include "PCB.h"

extern PCB* running_process;

extern std::vector<PCB*>ready_list0;
extern std::vector<PCB*>ready_list1;
extern std::vector<PCB*>ready_list2;

extern std::vector<PCB*>blocked_list;


