#pragma once
#include <vector>
#include "PCB.h"
#include "resource.h"

class resource;
class PCB;


class RCB{
private:
	std::vector<resource*> resource_list; //资源列表

public:
	RCB();
	void require(PCB* process,std::string resource_name, int num); //申请资源
	void release(PCB* process,std::string resource_name, int num); //释放资源
	void release_all_by_process(PCB* process); //用于delete函数的删除（避免iterator erase过后非法的情况）
	void remove_waiting_list(PCB* process);//把process从所有资源的waiting_list中移除
	void modify_blocklist();//blocklist中第一个进程能否被加入至readylist中
};

