#include "mylist.h"

PCB* running_process = nullptr;

std::vector<PCB*>ready_list0;
std::vector<PCB*>ready_list1;
std::vector<PCB*>ready_list2;

std::vector<PCB*>blocked_list;


