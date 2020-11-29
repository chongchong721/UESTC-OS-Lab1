#pragma once
#include <string>
#include <map>
#include "PCB.h"

class process_wait_for_resource {
	PCB* process;
	int wait_num;

public:
	process_wait_for_resource(PCB*, int);
};


class resource{
	std::string name;
	int num_all;
	int num_remained;
	int num_occupied;
	std::map<std::string, int> map_occupied;
	std::vector<process_wait_for_resource *> waiting_list;

public:
	resource(int i);
	std::string get_name();
	void add_to_waiting_list(process_wait_for_resource * p);
	bool require(PCB* process, int num);
	void release(PCB* process, int num);
};

