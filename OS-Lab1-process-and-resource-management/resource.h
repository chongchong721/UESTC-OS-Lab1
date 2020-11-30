#pragma once
#include "PCB.h"
#include <string>
#include <map>

class PCB;

class resource{
	std::string name;
	int num_all;


	std::vector<std::pair<PCB*,int>> waiting_list;

public:
	int num_remained;
	int num_occupied;
	std::map<std::string, int> map_occupied;
	resource(int i);
	std::string get_name();
	int get_num_remained();
	int get_num_occupied();
	//std::map<std::string, int> get_map_occupied();
	void add_to_waiting_list(std::pair<PCB*, int> p);
	void move_from_waiting_list(PCB*);
	bool require(PCB* process, int num);
	void release(PCB* process, int num);
};


