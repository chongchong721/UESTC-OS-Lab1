#include "resource.h"

//����Ri��Դ��i���Ĺ��������Դ
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

//�ѽ��̺͵ȴ���Դ���������
void resource::add_to_waiting_list(std::pair<PCB*, int> p){
	waiting_list.push_back(p);
}
//�Ƴ�waiting_list
void resource::move_from_waiting_list(PCB* process){
	for (auto iterator = waiting_list.begin(); iterator != waiting_list.end();iterator++) {
		if (iterator->first == process) {
			waiting_list.erase(iterator);
			break;
		}
	}
	return;
}

//����������Դ
bool resource::require(PCB* process, int num){
	//�޷�������Դ��Ŀ��������Ҫ���̸����Լ���resource_needed map ��Ҫ��Դ�����Լ���waiting_list
	if (this->num_remained < num) {
		process->add_to_resource_needed(this->name, num);
		std::pair<PCB*, int> temp(process, num);
		waiting_list.push_back(temp);
		return false;
	}
	//��������
	else {
		num_occupied += num;
		num_remained -= num;
		auto it = map_occupied.find(process->get_name());
		//����Ѿ�ռ��һ����Ŀ����Դ���ٴ�����Ļ���ֻ�ø�����Դ��Ŀ���ɣ����û����insert��Map_occupied
		if (it == map_occupied.end()) {
			map_occupied.insert(std::pair<std::string, int>(process->get_name(), num));
		}
		else {
			it->second += num;
		}
		//���̸����Լ���ȡ��Դ��map
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
	//���̴��Լ���map���ͷ���Դ
	process->release_from_resourcemap(this->name, num);
	//�������ȫ���ͷ�����Դ�������Դ��map_occupied��ɾ�������������ֵ
	if (occupied == 0) {
		map_occupied.erase(iterator);
	}
	else if(occupied>0){
		iterator->second = occupied;
	}
	return;
}


	