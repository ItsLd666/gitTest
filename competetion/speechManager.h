#pragma once
#include <iostream>
#include "speaker.h"
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class SpeechManager {
public:
	//构造函数
	SpeechManager();

	//显示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();
	
	//初始化容器
	void initSpeech();

	//创建选手
	void createSpeaker();

	//开始比赛
	void startSpeech();
	void speechDraw();  //抽签
	void speechContest();  //比赛
	void showRes();
	void writeRes();

	//*****************************
	//******members available******
	//*****************************

	//第一轮 12人
	vector<int> v1;

	//第二轮 6人
	vector<int> v2;

	//胜出 3人
	vector<int> vVictory;

	//选手编号 对应具体人
	map<int, Speaker> m_Speaker;

	//比赛轮次
	int m_Index;
};