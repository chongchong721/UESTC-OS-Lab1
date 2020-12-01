#include "PCB.h"
#include "mylist.h"

PCB::PCB(std::string PID, int priority){
	this->PID = PID;
	this->priority = priority;
}

int PCB::get_priority()
{
	return this->priority;
}

//std::map<std::string, int> PCB::get_resource_needed()
//{
//	return std::map<std::string, int>(this->resource_needed);
//}
//
//std::map<std::string, int> PCB::get_resource_acquired(){
//	return std::map<std::string, int>(resource_acquired);
//}

void PCB::set_parent(PCB* parent){
	this->parent = parent;
}

void PCB::set_children(PCB* children) {
	this->children.push_back(children);
}

//设置进程对应的队列指针
void PCB::set_status_list(std::string type){
	if (type == "blocked") {
		status_list = &blocked_list;
	}
	else if (type == "ready") {
		switch (this->priority) {
		case 0:
			status_list = &ready_list0;
			break;
		case 1:
			status_list = &ready_list1;
			break;
		case 2:
			status_list = &ready_list2;
			break;
		}
	}
}

//移动到blocklist
void PCB::move_to_blocklist(){

	if (running_process != this) {
		for (auto iterator = status_list->begin(); iterator != status_list->end(); iterator++) {
			if (*iterator == this) {
				status_list->erase(iterator);
			}
		}
	}
	running_process = nullptr;  //该函数只可能在require的时候调用，即running_process本身被阻塞，因此可以直接将running_process置空
	set_status_list("blocked");
	blocked_list.push_back(this);
	return;
}

//从其他地方（readylist或running_process）移动到readylist
void PCB::move_to_readylist(){
	//如果不是正在运行的进程，即在其他队列中
	if (running_process != this) {
		for (auto iterator = status_list->begin(); iterator != status_list->end(); iterator++) {
			if (*iterator == this) {
				status_list->erase(iterator);
			}
		}
	}
	set_status_list("ready");
	switch (priority) {
	case 0:
		ready_list0.push_back(this);
		break;
	case 1:
		ready_list1.push_back(this);
		break;
	case 2:
		ready_list2.push_back(this);
		break;
	}
	return;
}

//遍历所有list 移除进程
void PCB::remove_from_all_lists(){
	int priority = this->get_priority();
	if (running_process == this) {
		running_process = nullptr;
	}
	else {
		switch (priority) {
		case 0:
			for (auto iterator = ready_list0.begin(); iterator != ready_list0.end(); iterator++) {
				if ((*iterator) == this) {
					ready_list0.erase(iterator);
					break;
				}
			}
			break;
		case 1:
			for (auto iterator = ready_list1.begin(); iterator != ready_list1.end(); iterator++) {
				if ((*iterator) == this) {
					ready_list1.erase(iterator);
					break;
				}
			}
			break;
		case 2:
			for (auto iterator = ready_list2.begin(); iterator != ready_list2.end(); iterator++) {
				if ((*iterator) == this) {
					ready_list2.erase(iterator);
					break;
				}
			}
			break;
		}
		for (auto iterator = blocked_list.begin(); iterator != blocked_list.end(); iterator++) {
			if ((*iterator) == this) {
				blocked_list.erase(iterator);
				break;
			}
		}
	}
	return;
}

std::string PCB::get_name()
{
	return std::string(this->PID);
}

void PCB::get_PCB_by_name(PCB* init, std::string name,PCB*& result)
{
	if (init->children.empty()) {
		return;
	}
	for (auto iterator : init->children) {
		if (iterator->get_name() == name) {
			result = iterator;
			return;
		}
		//递归调用找到相应的进程
		get_PCB_by_name(iterator, name, result);
	}
	return;
}

//级联删除
void PCB::delete_on_cascade(RCB* rcb){
	this->release_all_resource(rcb); //在rcb中释放所有资源
	this->remove_from_all_lists(); //从所有list中移除
	rcb->modify_blocklist();  //检查blocklist
	if (!this->children.empty()) {
		for (auto iterator : this->children) {
			//级联删除
			iterator->delete_on_cascade(rcb);
		}
	}
	//commit suicide
	delete this;
	return;

}

//把资源加入已获取map
void PCB::add_to_resource_acquired(std::string name, int num) {
	auto it = resource_acquired.find(name);
	if (it != resource_acquired.end()) {
		it->second += num;
	}
	else {
		resource_acquired.insert(std::pair<std::string, int>(name, num));
	}
	return;
}
//把资源加入需要但未获取map
void PCB::add_to_resource_needed(std::string name, int num) {
	auto it = resource_needed.find(name);
	if (it != resource_needed.end()) {
		it->second += num;
	}
	else {
		resource_needed.insert(std::pair<std::string, int>(name, num));
	}
	return;
}

//从已获取的map中释放
void PCB::release_from_resourcemap(std::string name, int num){
	auto iterator = resource_acquired.find(name);
	if (iterator != resource_acquired.end()) {
		//如果没有完全释放
		if (iterator->second - num > 0) {
			iterator->second -= num;
		}
		//若完全释放 直接删除
		else {
			resource_acquired.erase(iterator);
		}
	}
}
//释放所有资源 用在delete中
void PCB::release_all_resource(RCB *rcb){
	rcb->release_all_by_process(this);
}
