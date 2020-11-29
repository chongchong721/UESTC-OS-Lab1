#pragma once
#include <vector>
#include "resource.h"


class RCB{
	std::vector<resource*> resource_list;

public:
	RCB();
	void require(PCB* process,std::string resource_name, int num);
	void release(PCB* process,std::string resource_name, int num);
	void modify_blocklist();
};

