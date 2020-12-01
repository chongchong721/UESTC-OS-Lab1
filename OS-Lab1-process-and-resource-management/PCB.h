#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "RCB.h"

class RCB;

enum processStatus{running,blocked,ready};

class PCB{
	std::string PID; //进程的名字
	processStatus status; //进程的状态 貌似没啥用
	std::vector<PCB*>* status_list; //进程目前状态所在的list

	int priority; //优先级


public:
	PCB(std::string,  int priority);
	std::vector<PCB*> children; //进程的孩子
	PCB* parent; //进程的爹
	std::map < std::string, int> resource_acquired; //进程已经获取的资源的map
	std::map < std::string, int> resource_needed;	//进程需要但是还未获取的资源的map
	int get_priority();
	//std::map<std::string, int> get_resource_needed();
	//std::map<std::string, int> get_resource_acquired();
	void set_parent(PCB*);
	void set_children(PCB*);
	void set_status_list(std::string);
	void move_to_blocklist(); //将进程从现有队列移动到blocklist
	void move_to_readylist(); //将进程从现有队列（或正在运行）移动到相应readylist
	void remove_from_all_lists();  //将进程从队列中移除 该函数会在删除进程时调用
	std::string get_name();
	void get_PCB_by_name(PCB* init, std::string name, PCB*& result);  //从进程树根部(init)开始查找name对应的进程，结果通过result返回
	void delete_on_cascade(RCB* rcb); //级联删除进程
	void add_to_resource_acquired(std::string, int); //将资源及申请数目加至进程已获取资源map
	void add_to_resource_needed(std::string, int); //将资源及需要数目加至进程需要(但未获取)资源map
	void release_from_resourcemap(std::string, int);  //更改进程的resourcemap
	void release_all_resource(RCB *rcb); //删除进程时使用，清空所有资源信息
};

