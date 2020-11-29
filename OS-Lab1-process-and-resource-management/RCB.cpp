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

}

void RCB::modify_blocklist(){
	
}
