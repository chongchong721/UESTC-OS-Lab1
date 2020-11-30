#include "RCB.h"
#include "mylist.h"

RCB::RCB(){
	for (int i = 1; i < 5; i++) {
		resource *temp_resource = new resource(i);
		resource_list.push_back(temp_resource);
	}
}

void RCB::require(PCB* process, std::string resource_name, int num){
	for (auto iterator : resource_list) {
		if (iterator->get_name() == resource_name) {
			if (iterator->require(process, num)) {
				return;
			}
			else {
				process->move_to_blocklist();
				return;
			}
		}
	}
}

void RCB::release(PCB* process, std::string resource_name, int num){
	for (auto iterator : resource_list) {
		if (iterator->get_name() == resource_name) {
			iterator->release(process, num);
			break;
		}
	}
	return;
}

void RCB::release_all_by_process(PCB* process){
	for (auto iterator = process->resource_acquired.begin(); iterator != process->resource_acquired.end(); iterator++) {
		for (auto iteratorResource : resource_list) {
			if (iteratorResource->get_name() == iterator->first) {
				iteratorResource->num_occupied -= iterator->second;
				iteratorResource->num_remained += iterator->second;
				auto it = iteratorResource->map_occupied.find(process->get_name());
				iteratorResource->map_occupied.erase(it);
				break;
			}
		}
	}
	for (auto iterator = process->resource_needed.begin(); iterator != process->resource_needed.end(); iterator++) {
		for (auto iteratorResource : resource_list) {
			if (iteratorResource->get_name() == iterator->first) {
				iteratorResource->num_occupied -= iterator->second;
				iteratorResource->num_remained += iterator->second;
				iteratorResource->move_from_waiting_list(process);
				break;
			}
		}
	}
	process->resource_acquired.clear();
	process->resource_needed.clear();
}

void RCB::remove_waiting_list(PCB* process){
	for (auto iterator : resource_list) {
		iterator->move_from_waiting_list(process);
	}
	return;
}



void RCB::modify_blocklist(){
	if (blocked_list.empty()) {
		return;
	}
	else {
		PCB* process = blocked_list[0];
		bool flag = true;
		for (auto iteratorNeeded = process->resource_needed.begin(); iteratorNeeded != process->resource_needed.end();iteratorNeeded++) {
			if (flag) {
				for (auto iteratorResource : this->resource_list) {
					if (iteratorResource->get_name() == iteratorNeeded->first) {
						if (iteratorResource->get_num_remained() < iteratorNeeded->second) {
							flag = false;
							break;
						}
					}
				}
			}
			else {
				break;
			}
		}
		if (flag) {
			blocked_list.erase(blocked_list.begin());
			for (auto iteratorNeeded = process->resource_needed.begin(); iteratorNeeded != process->resource_needed.end(); iteratorNeeded++) {
				this->require(process, iteratorNeeded->first, iteratorNeeded->second);
			}
			switch (process->get_priority()){
			case 0:
				ready_list0.push_back(process);
				break;
			case 1:
				ready_list1.push_back(process);
				break;
			case 2:
				ready_list2.push_back(process);
				break;
			}
		}
	}
	return;
}


