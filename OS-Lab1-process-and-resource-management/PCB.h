#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "RCB.h"

class RCB;

enum processStatus{running,blocked,ready};

class PCB{
	std::string PID; //���̵�����
	processStatus status; //���̵�״̬ ò��ûɶ��
	std::vector<PCB*>* status_list; //����Ŀǰ״̬���ڵ�list

	int priority; //���ȼ�


public:
	PCB(std::string,  int priority);
	std::vector<PCB*> children; //���̵ĺ���
	PCB* parent; //���̵ĵ�
	std::map < std::string, int> resource_acquired; //�����Ѿ���ȡ����Դ��map
	std::map < std::string, int> resource_needed;	//������Ҫ���ǻ�δ��ȡ����Դ��map
	int get_priority();
	//std::map<std::string, int> get_resource_needed();
	//std::map<std::string, int> get_resource_acquired();
	void set_parent(PCB*);
	void set_children(PCB*);
	void set_status_list(std::string);
	void move_to_blocklist(); //�����̴����ж����ƶ���blocklist
	void move_to_readylist(); //�����̴����ж��У����������У��ƶ�����Ӧreadylist
	void remove_from_all_lists();  //�����̴Ӷ������Ƴ� �ú�������ɾ������ʱ����
	std::string get_name();
	void get_PCB_by_name(PCB* init, std::string name, PCB*& result);  //�ӽ���������(init)��ʼ����name��Ӧ�Ľ��̣����ͨ��result����
	void delete_on_cascade(RCB* rcb); //����ɾ������
	void add_to_resource_acquired(std::string, int); //����Դ��������Ŀ���������ѻ�ȡ��Դmap
	void add_to_resource_needed(std::string, int); //����Դ����Ҫ��Ŀ����������Ҫ(��δ��ȡ)��Դmap
	void release_from_resourcemap(std::string, int);  //���Ľ��̵�resourcemap
	void release_all_resource(RCB *rcb); //ɾ������ʱʹ�ã����������Դ��Ϣ
};

