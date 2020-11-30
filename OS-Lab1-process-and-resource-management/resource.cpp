#include "resource.h"

resource::resource(int i){
	switch (i) {
	case 1:
		name = "R1";
		num_all = num_remained = 1;
		num_occupied = 0;
		break;
	case 2:
		name = "R2";
		num_all = num_remained = 2;
		num_occupied = 0;
		break;
	case 3:
		name = "R3";
		num_all = num_remained = 3;
		num_occupied = 0;
		break;
	case 4:
		name = "R4";
		num_all = num_remained = 4;
		num_occupied = 0;
		break;
	}
}

std::string resource::get_name()
{
	return std::string(this->name);
}

int resource::get_num_remained()
{
	return this->num_remained;
}

int resource::get_num_occupied()
{
	return this->num_occupied;
}

//std::map<std::string, int> resource::get_map_occupied(){
//	return std::map<std::string, int>(map_occupied);
//}

//把进程和等待资源数加入队列
void resource::add_to_waiting_list(std::pair<PCB*, int> p){
	waiting_list.push_back(p);
}

void resource::move_from_waiting_list(PCB* process){
	for (auto iterator = waiting_list.begin(); iterator != waiting_list.end();iterator++) {
		if (iterator->first == process) {
			waiting_list.erase(iterator);
			break;
		}
	}
	return;
}

//进程请求资源
bool resource::require(PCB* process, int num){
	if (this->num_remained < num) {
		process->add_to_resource_needed(this->name, num);
		std::pair<PCB*, int> temp(process, num);
		waiting_list.push_back(temp);
		return false;
	}
	else {
		num_occupied += num;
		num_remained -= num;
		auto it = map_occupied.find(process->get_name());
		if (it == map_occupied.end()) {
			map_occupied.insert(std::pair<std::string, int>(process->get_name(), num));
		}
		else {
			it->second += num;
		}
		process->add_to_resource_acquired(this->name, num);
		return true;
	}
}

//进程释放资源
void resource::release(PCB* process, int num){
	auto iterator = map_occupied.find(process->get_name());
	int occupied = iterator->second;
	occupied -= num;
	this->num_occupied -= num;
	this->num_remained += num;
	process->release_from_resourcemap(this->name, num);
	if (occupied == 0) {
		map_occupied.erase(iterator);
	}
	else if(occupied>0){
		iterator->second = occupied;
	}
	return;
}


	