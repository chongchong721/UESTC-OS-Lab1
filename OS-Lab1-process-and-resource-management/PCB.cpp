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

void PCB::move_to_blocklist(){

	for (auto iterator = status_list->begin(); iterator != status_list->end(); iterator++) {
		if (*iterator == this) {
			status_list->erase(iterator);
		}
	}
	running_process = nullptr;
	set_status_list("blocked");
	blocked_list.push_back(this);
	return;
}

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
		get_PCB_by_name(iterator, name, result);
	}
	return;
}

void PCB::delete_on_cascade(RCB* rcb){
	this->release_all_resource(rcb);
	if (!this->children.empty()) {
		for (auto iterator : this->children) {
			iterator->delete_on_cascade(rcb);
		}
	}
	return;

}


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

void PCB::release_from_resourcemap(std::string name, int num){
	auto iterator = resource_acquired.find(name);
	if (iterator != resource_acquired.end()) {
		if (iterator->second - num > 0) {
			iterator->second -= num;
		}
		else {
			resource_acquired.erase(iterator);
		}
	}
}

void PCB::release_all_resource(RCB *rcb){
	rcb->release_all_by_process(this);
}
