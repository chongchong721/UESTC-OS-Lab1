#pragma once
#include <vector>
#include "PCB.h"
#include "resource.h"

class resource;
class PCB;


class RCB{
private:
	std::vector<resource*> resource_list; //��Դ�б�

public:
	RCB();
	void require(PCB* process,std::string resource_name, int num); //������Դ
	void release(PCB* process,std::string resource_name, int num); //�ͷ���Դ
	void release_all_by_process(PCB* process); //����delete������ɾ��������iterator erase����Ƿ��������
	void remove_waiting_list(PCB* process);//��process��������Դ��waiting_list���Ƴ�
	void modify_blocklist();//blocklist�е�һ�������ܷ񱻼�����readylist��
};

