#pragma once
#include <vector>
#include "PCB.h"

//����ȫ�ֱ���

extern PCB* running_process;  //�������еĽ���

extern std::vector<PCB*>ready_list0;//���ȼ�Ϊ0�ľ�������
extern std::vector<PCB*>ready_list1;//���ȼ�Ϊ1�ľ�������
extern std::vector<PCB*>ready_list2;//���ȼ�Ϊ2�ľ�������

extern std::vector<PCB*>blocked_list;//��������


