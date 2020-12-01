#pragma once
#include "PCB.h"
#include <string>
#include <map>

class PCB;

class resource{
	std::string name;
	int num_all;


	std::vector<std::pair<PCB*,int>> waiting_list;

public:
	int num_remained;
	int num_occupied;
	std::map<std::string, int> map_occupied;  //ռ��Ŀǰ��Դ�Ľ��̺�������map
	resource(int i);
	std::string get_name();
	int get_num_remained();
	int get_num_occupied();
	//std::map<std::string, int> get_map_occupied();
	void add_to_waiting_list(std::pair<PCB*, int> p); //�����̺����������Դ�������Ӧ��Դ��waiting_list�У���������޷����뵽��ô����Դʱ��
	void move_from_waiting_list(PCB*);  //��waiting_list��ɾ��
	bool require(PCB* process, int num);  //����������Դ
	void release(PCB* process, int num);  //�����ͷ���Դ
};


