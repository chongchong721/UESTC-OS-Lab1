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
			//如果无法申请资源（资源不足）,将进程移动到阻塞队列
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

//该函数用于删除时进程时使用,将进程的两个map中的所有内容清空，同时更改相关的rcb中的资源值
void RCB::release_all_by_process(PCB* process){
	//修改进程获取的资源map 同时修改资源中的num_occupied和num_remained以及map_occupied
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
	//修改进程需要但未获取的资源map,同时从资源中的waiting_list移除进程
	for (auto iterator = process->resource_needed.begin(); iterator != process->resource_needed.end(); iterator++) {
		for (auto iteratorResource : resource_list) {
			if (iteratorResource->get_name() == iterator->first) {
				//iteratorResource->num_occupied -= iterator->second;
				//iteratorResource->num_remained += iterator->second;
				iteratorResource->move_from_waiting_list(process);
				break;
			}
		}
	}
	//清空进程的resource_xxx_map
	process->resource_acquired.clear();
	process->resource_needed.clear();
}

//将进程从所有resource的waiting_list中移除，用在删除中
void RCB::remove_waiting_list(PCB* process){
	for (auto iterator : resource_list) {
		iterator->move_from_waiting_list(process);
	}
	return;
}


//检查blocklist 如果blocklist的第一个进程已经可以申请到所有需要的资源，将他放进相应readylist的队尾
void RCB::modify_blocklist(){
	if (blocked_list.empty()) {
		return;
	}
	else {
		PCB* process = blocked_list[0];
		bool flag = true;
		//检查资源是否可以供进程申请
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
		//变换队列
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


