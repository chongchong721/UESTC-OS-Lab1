#pragma once
#include <vector>
#include "PCB.h"

//定义全局变量

extern PCB* running_process;  //正在运行的进程

extern std::vector<PCB*>ready_list0;//优先级为0的就绪队列
extern std::vector<PCB*>ready_list1;//优先级为1的就绪队列
extern std::vector<PCB*>ready_list2;//优先级为2的就绪队列

extern std::vector<PCB*>blocked_list;//阻塞队列


