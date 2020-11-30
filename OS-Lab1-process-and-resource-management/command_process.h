#pragma once
#include <string>
#include <vector>
#include "PCB.h"
#define INVALID 0xFFFFFFFF;
void command_process(std::string);
void split(std::string& std, std::vector<std::string>& store, std::string& c);

enum commandType {init,cr,de,req,rel,to,lp,lr};

class command {
private:
	enum commandType type;
	std::string name;
	int num;
	void cmd_init();
	void cmd_cr();
	void cmd_de();
	void cmd_req();
	void cmd_rel();
	void cmd_to();
	void cmd_lp();
	void cmd_lr();
	void dispatch();
	

public:
	command(std::vector<std::string>);
	void excecute();
	PCB* get_next_running_process(int, std::string); //从readylist中找到应该调度的进程

};