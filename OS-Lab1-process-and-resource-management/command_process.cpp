#include "command_process.h"
#include "PCB.h"
#include "mylist.h"
#include <iostream>
#include "RCB.h"

PCB* Init;
RCB* rcb = new RCB();

//按照string c分割字符串，存在vector中
void split(std::string& str, std::vector<std::string>& store, std::string& c) {
	std::string::size_type pos1, pos2;
	pos2 = str.find(c);
	pos1 = 0;
	while (pos2 != std::string::npos) {
		store.push_back(str.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = str.find(c, pos1);
	}
	if (pos1 != str.length()) {
		store.push_back(str.substr(pos1));
	}

}

//处理字符串，转换为命令，并执行
void command_process(std::string str) {
	std::string space = " ";
	std::vector<std::string> store_string;
	store_string.clear();
	split(str, store_string, space);
	command temp = command(store_string);
	temp.excecute();
}

command::command(std::vector<std::string> store_string) {
	if (store_string[0] == "init") {
		type = init;
		name = "null";
		num = INVALID;
	}
	else if (store_string[0] == "cr") {
		type = cr;
		name = store_string[1];
		num = std::stoi(store_string[2]);
	}
	else if (store_string[0] == "de") {
		type = de;
		name = store_string[1];
		num = INVALID;
	}
	else if (store_string[0] == "req") {
		type = req;
		name = store_string[1];
		num = std::stoi(store_string[2]);
	}
	else if (store_string[0] == "rel") {
		type = rel;
		name = store_string[1];
		num = std::stoi(store_string[2]);
	}
	else if (store_string[0] == "to") {
		type = to;
		name = "null";
		num = INVALID;
	}
	else if (store_string[0] == "lp") {
		type = lp;
		name = "null";
		num = INVALID;

	}
	else if (store_string[0] == "lr") {
		type = lr;
		name = "null";
		num = INVALID;
	}
}

void command::excecute() {
	switch (type)
	{
	case init:
		cmd_init();
		dispatch();
		break;
	case cr:
		cmd_cr();
		dispatch();
		break;
	case de:
		cmd_de();
		dispatch();
		break;
	case req:
		cmd_req();
		dispatch();
		break;
	case rel:
		cmd_rel();
		dispatch();
		break;
	case to:
		cmd_to();
		break;
	case lp:
		break;
	case lr:
		break;
	}
	std::cout << running_process->get_name() << " ";
}

//初始进程
void command::cmd_init(){
	PCB* process = new PCB("init", 0);
	Init = process;
	process->set_parent(nullptr);
	ready_list0.push_back(process);
	return;
}
//创建进程
void command::cmd_cr(){
	PCB* process = new PCB(this->name, this->num);
	process->set_parent(running_process);
	running_process->set_children(process);
	if (this->num == 1) {
		ready_list1.push_back(process);
	}
	else if (this->num == 2) {
		ready_list2.push_back(process); 
	}
	return;
}
//删除
void command::cmd_de(){
	PCB* process = nullptr;
	Init->get_PCB_by_name(Init, this->name, process);
	//将进程从父亲的孩子vector中删除
	for (auto iterator = process->parent->children.begin(); iterator != process->parent->children.end(); iterator++) {
		if ((*iterator) == process) {
			process->parent->children.erase(iterator);
			break;
		}
	}
	process->delete_on_cascade(rcb);
	//rcb->modify_blocklist(); 
	return;
}

void command::cmd_req(){
	rcb->require(running_process, this->name, this->num);
	return;
}

void command::cmd_rel(){
	PCB* process = running_process;
	rcb->release(process, this->name, this->num);
	rcb->modify_blocklist();
	return;
}

void command::cmd_to(){
	PCB* process;
	process = this->get_next_running_process(running_process->get_priority(), "to");
	//如果返回nullptr 说明不改变running_process
	if (process != nullptr) {
		running_process->move_to_readylist();
		running_process = process;
	}
	return;
}

//待实现
void command::cmd_lp(){

}
//待实现
void command::cmd_lr(){

}

//调度命令
void command::dispatch(){
	PCB* process = nullptr;
	//如果running_process是空指针，只可能在req或者de命令时出现这种情况
	if (running_process == nullptr) {
		//参数传递-1 表示running_process为nptr
		process = this->get_next_running_process(-1,"normal"); //-1表示running_process为空
	}
	//to rel cr命令的running_process都不为空
	else {
		process = this->get_next_running_process(running_process->get_priority(),"normal");
		if (process == nullptr) {
			process = running_process;
		}
	}
	if (running_process != process && running_process != nullptr) {
		running_process->move_to_readylist();
		//将被调度进程移除队列的操作在get___函数中
	}
	running_process = process;
	return;
}

//根据队列，获取下一个应该调度的进程的指针
PCB* command::get_next_running_process(int priority,std::string mode)
{
	PCB* process = nullptr;
	//正常调度模式，同优先级无法打断
	if (mode == "normal") {
		//priority为-1的情况表示running_process为nullptr 只需要找到优先级最高的即可
		if (priority == -1) {
			if (ready_list2.empty()) {
				if (ready_list1.empty()) {
					process = ready_list0[0];
					ready_list0.erase(ready_list0.begin());
				}
				else {
					process = ready_list1[0];
					ready_list1.erase(ready_list1.begin());
				}
			}
			else {
				process = ready_list2[0];
				ready_list2.erase(ready_list2.begin());
			}
			return process;
		}
		//running_process还有的情况，需要比较优先级
		else {
			if (priority == 1) {
				if (!ready_list2.empty()) {
					process = ready_list2[0];
					ready_list2.erase(ready_list2.begin());
				}
			}
			else if (priority == 0) {
				if (!ready_list2.empty()) {
					process = ready_list2[0];
					ready_list2.erase(ready_list2.begin());
				}
				else {
					if (!ready_list1.empty()) {
						process = ready_list1[0];
						ready_list1.erase(ready_list1.begin());
					}
				}
			}
			return process;
		}
	}
	//time out模式，同优先级可以打断
	else if (mode == "to") {
		if (priority == 2) {
			if (!ready_list2.empty()) {
				process = ready_list2[0];
				ready_list2.erase(ready_list2.begin());
			}
		}
		else if (priority == 1) {
			if (!ready_list2.empty()) {
				process = ready_list2[0];
				ready_list2.erase(ready_list2.begin());
			}
			else {
				if (!ready_list1.empty()) {
					process = ready_list1[0];
					ready_list1.erase(ready_list1.begin());
				}
			}
		}
		else if (priority == 0) {
			if (!ready_list2.empty()) {
				process = ready_list2[0];
				ready_list2.erase(ready_list2.begin());
			}
			else {
				if (!ready_list1.empty()) {
					process = ready_list1[0];
					ready_list1.erase(ready_list1.begin());
				}
				else {
					if (!ready_list0.empty()) {
						process = ready_list0[0];
						ready_list0.erase(ready_list0.begin());
					}
				}
			}
		}
		return process;
	}
	
}
