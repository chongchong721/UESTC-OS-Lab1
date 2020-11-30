#pragma once
#include <vector>
#include "PCB.h"
#include "resource.h"

class resource;
class PCB;


class RCB{
private:
	std::vector<resource*> resource_list;

public:
	RCB();
	void require(PCB* process,std::string resource_name, int num);
	void release(PCB* process,std::string resource_name, int num);
	void release_all_by_process(PCB* process); //����delete������ɾ��������iterator erase����Ƿ��������
	void remove_waiting_list(PCB* process);
	void modify_blocklist();//blocklist�е�һ�������ܷ񱻼�����readylist��
};

