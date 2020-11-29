#include "PCB.h"
#include "mylist.h"

PCB::PCB(std::string PID, int priority){
	this->PID = PID;
	this->priority = priority;
}

void PCB::set_parent(PCB* parent){
	this->parent = parent;
}

void PCB::set_children(PCB* children) {
	this->children.push_back(children);
}

void PCB::move_to_blocklist(){

	for (auto iterator = status_list->begin(); iterator != status_list->end(); iterator++) {
		if (*iterator == this) {
			status_list->erase(iterator);
		}
	}
	blocked_list.push_back(this);
	return;
}

void PCB::move_to_readylist(){
	for (auto iterator = status_list->begin(); iterator != status_list->end(); iterator++) {
		if (*iterator == this) {
			status_list->erase(iterator);
		}
	}
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

void PCB::delete_on_cascade(PCB *node,RCB* rcb){
	if (node->children.empty()) {
		rcb->release
		return;
	}

}


void PCB::add_to_resource_acquired(std::string name, int num) {
	resource_acquired.insert(std::pair<std::string, int>(name, num));
}

void PCB::add_to_resource_needed(std::string name, int num) {
	resource_needed.insert(std::pair<std::string, int>(name, num));
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
