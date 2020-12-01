#include "resource.h"

//按照Ri资源有i个的规则分配资源
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
//移出waiting_list
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
	//无法请求，资源数目不够，需要进程更改自己的resource_needed map 需要资源更改自己的waiting_list
	if (this->num_remained < num) {
		process->add_to_resource_needed(this->name, num);
		std::pair<PCB*, int> temp(process, num);
		waiting_list.push_back(temp);
		return false;
	}
	//可以请求
	else {
		num_occupied += num;
		num_remained -= num;
		auto it = map_occupied.find(process->get_name());
		//如果已经占有一定数目的资源，再次请求的话，只用更改资源数目即可，如果没有则insert到Map_occupied
		if (it == map_occupied.end()) {
			map_occupied.insert(std::pair<std::string, int>(process->get_name(), num));
		}
		else {
			it->second += num;
		}
		//进程更改自己获取资源的map
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
	//进程从自己的map中释放资源
	process->release_from_resourcemap(this->name, num);
	//如果进程全部释放了资源，则从资源的map_occupied中删除，否则更改数值
	if (occupied == 0) {
		map_occupied.erase(iterator);
	}
	else if(occupied>0){
		iterator->second = occupied;
	}
	return;
}


	