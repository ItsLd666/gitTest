#include "speechManager.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <deque>
#include <fstream>
#include <ctime>

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
	//加载往届记录
	this->loadRecord();
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::exitSystem() {
	cout << "感谢您的使用！" << endl;
	system("pause");
	exit(0); //退出
}

void SpeechManager::show_Menu() {
	cout << "***********************************************" << endl;
	cout << "*****************   欢迎参加比赛   ***************" << endl;
	cout << "*****************  1.开始演讲比赛  ****************" << endl;
	cout << "*****************  2.查看往届记录  ****************" << endl;
	cout << "*****************  3.清空比赛记录  ****************" << endl;
	cout << "*****************  0.退出比赛程序  ****************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech() {
	//容器全部清空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	//比赛轮次初始化
	this->m_Index = 1;
}

void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}
		 
		this->v1.push_back(i + 10001); //成员id

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//抽签
void SpeechManager::speechDraw() {
	cout << "第<" << this->m_Index << ">轮选手正在抽签" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "抽签结果如下：" << endl;
	//随机种子
	srand((unsigned int)time(NULL));
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------------" << endl;
	system("pause");
}

//比赛
void SpeechManager::speechContest() {
	cout << "--------------第<" << this->m_Index << ">轮正式比赛开始：--------------" << endl;
	multimap<double, int, greater<double>> groupScore;  //临时容器，保存key分数。value，选手编号
	int num = 0;//记录人数，6人一组

	vector<int> v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++) {        //10个评委
			double score = (rand() % 401 + 600) / 10.f;  //600~100
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		//去掉最低和最高分
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //在map容器中保存所有人第一轮的分数
		groupScore.insert(make_pair(avg, *it));   //临时容器保存，下面判断num是否等于6. 6人一组单独处理。
		if (num % 6 == 0) {
			cout << "第<" << num / 6 << ">小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name << " 成绩：" << this->m_Speaker[it->second].m_Score[m_Index-1] << endl;
			}
			int count = 0;
			//取前三名  multimap<double, int, greater<double>> 暂存前三名。每次操作完之后，清空，方便下一轮存储。
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++) {
				count++;
				if (this->m_Index == 1) {
					v2.push_back(it->second);
				}
				else {
					vVictory.push_back(it->second);
				}
			}
			groupScore.clear();
		}
	}
	cout << "--------------第<" << this->m_Index << ">轮比赛完毕-------------" << endl;
	system("pause");
}

//控制比赛流程
void SpeechManager::startSpeech() {
	//第一轮
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示比赛结果
	this->showRes();
	//第二轮
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showRes();
	//4.保存分数
	this->saveRecord();

	//重置信息
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛已结束！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::showRes() {
	cout << "-----------------------第<"<< this->m_Index <<">轮比赛晋级结果-------------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	//int number = 1;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "选手编号"<< *it <<" 姓名：" << this->m_Speaker[*it].m_Name << " 得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
		//number++;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Name << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存！" << endl;
	//文件不为空
	this->fileIsEmpty = false;
}

//查看记录
void SpeechManager::loadRecord() {
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在..." << endl;
		ifs.close();
		return;
	}

	//文件被清空过
	char ch;
	ifs >> ch;
	//到达文件结尾
	if (ifs.eof()) {
		//cout << "文件为空..." << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);//因为刚刚为了判断文件是否到达结尾，读走了一个字符。

	string data;
	int index = 0;
	while (ifs >> data) {
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true) {
			pos = data.find(",",start);   //从起始位置开始找
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件不存在或为空..." << endl;
		return;
	}
	for (int i = 0; i < m_Record.size();i++) {
		cout << "------第<" << i + 1 << ">届------\n" << "冠军编号" << m_Record[i][0] << "姓名" << m_Record[i][1] << "得分" << m_Record[i][2] << endl \
			<< "亚军编号" << m_Record[i][3] << "姓名" << m_Record[i][4] << "得分" << m_Record[i][5] << endl \
			<< "季军编号" << m_Record[i][6] << "姓名" << m_Record[i][7] << "得分" << m_Record[i][8] << endl;
		cout << endl;
	}
	system("pause");
	system("cls");
}
