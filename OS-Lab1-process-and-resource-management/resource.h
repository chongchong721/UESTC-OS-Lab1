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
	std::map<std::string, int> map_occupied;  //占有目前资源的进程和数量的map
	resource(int i);
	std::string get_name();
	int get_num_remained();
	int get_num_occupied();
	//std::map<std::string, int> get_map_occupied();
	void add_to_waiting_list(std::pair<PCB*, int> p); //将进程和其申请的资源数加入对应资源的waiting_list中（如果进程无法申请到这么多资源时）
	void move_from_waiting_list(PCB*);  //从waiting_list中删除
	bool require(PCB* process, int num);  //进程申请资源
	void release(PCB* process, int num);  //进程释放资源
};


