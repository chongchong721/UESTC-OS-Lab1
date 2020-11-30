#pragma once
#include <vector>
#include "PCB.h"
#include "resource.h"

class resource;
class PCB;


class RCB{
private:
	std::vector<resource*> resource_list;

public:
	RCB();
	void require(PCB* process,std::string resource_name, int num);
	void release(PCB* process,std::string resource_name, int num);
	void release_all_by_process(PCB* process); //用于delete函数的删除（避免iterator erase过后非法的情况）
	void remove_waiting_list(PCB* process);
	void modify_blocklist();//blocklist中第一个进程能否被加入至readylist中
};

