#include "speechManager.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <deque>

SpeechManager::SpeechManager() {
	this->initSpeech();
	this->createSpeaker();
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
	cout << "*******************欢迎参加比赛****************" << endl;
	cout << "*****************1.开始演讲比赛****************" << endl;
	cout << "*****************2.查看往届记录****************" << endl;
	cout << "*****************3.清空比赛记录****************" << endl;
	cout << "*****************0.退出比赛程序****************" << endl;
	cout << "***********************************************" << endl;
	cout << endl;
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

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
			//取前三名
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

	//第二轮
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showRes();
	//4.保存分数

}

void SpeechManager::showRes() {
	cout << "-----------------------比赛结果-------------------------" << endl;
	int number = 1;
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		cout << "第<" << number << ">名:" << " 姓名：" << this->m_Speaker[*it].m_Name << " 得分：" << this->m_Speaker[*it].m_Score[1] << endl;
		number++;
	}
	cout << endl;
}
void SpeechManager::writeRes() {

}