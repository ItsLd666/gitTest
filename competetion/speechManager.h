#pragma once
#include <iostream>
#include "speaker.h"
#include <vector>
#include <map>


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
	void showRes();  //显示结果
	void saveRecord();

	//查看记录
	void loadRecord();
	void showRecord();

	//清空记录
	void clearRecord();

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

	//文件是否为空
	bool fileIsEmpty = true;

	//存储读取结果
	map<int, vector<string>> m_Record;
};