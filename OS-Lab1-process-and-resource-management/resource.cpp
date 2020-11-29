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

//�ѽ��̺͵ȴ���Դ���������
void resource::add_to_waiting_list(process_wait_for_resource* p){
	waiting_list.push_back(p);
}

//����������Դ
bool resource::require(PCB* process, int num){
	if (this->num_remained < num) {
		process->add_to_resource_needed(this->name, num);
		process_wait_for_resource* temp = new process_wait_for_resource(process, num);
		waiting_list.push_back(temp);
		return false;
	}
	else {
		num_occupied += num;
		num_remained -= num;
		map_occupied.insert(std::pair<std::string, int>(process->get_name(), num));
		process->add_to_resource_acquired(this->name, num);
		return true;
	}
}

//�����ͷ���Դ
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


process_wait_for_resource::process_wait_for_resource(PCB* process, int wait_num){
	this->process = process;
	this->wait_num = wait_num;
}
	