#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "RCB.h"

class RCB;

enum processStatus{running,blocked,ready};

class PCB{
	std::string PID;
	processStatus status;
	std::vector<PCB*>* status_list;

	std::vector<PCB*> children;
	PCB* parent;
	int priority;


public:
	PCB(std::string,  int priority);
	std::map < std::string, int> resource_acquired;
	std::map < std::string, int> resource_needed;
	int get_priority();
	//std::map<std::string, int> get_resource_needed();
	//std::map<std::string, int> get_resource_acquired();
	void set_parent(PCB*);
	void set_children(PCB*);
	void set_status_list(std::string);
	void move_to_blocklist();
	void move_to_readylist();
	std::string get_name();
	void get_PCB_by_name(PCB* init, std::string name, PCB*& result);
	void delete_on_cascade(RCB* rcb);
	void add_to_resource_acquired(std::string, int);
	void add_to_resource_needed(std::string, int);
	void release_from_resourcemap(std::string, int);  //更改进程的resourcemap
	void release_all_resource(RCB *rcb); //删除进程时使用，清空所有资源信息
};

