#include <iostream>
#include "speechManager.h"

using namespace std;

int main() {
	SpeechManager sm;
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//开始比赛
			sm.startSpeech();

			//测试
			/*sm.createSpeaker();
			for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
				cout << "选手编号：" << it->first << " " << "选手姓名：" << it->second.m_Name << " " << "选手成绩：" << *it->second.m_Score << endl;	
			}*/

			break;
		case 2:		//查看记录
			sm.showRecord();
			break;
		case 3:		//清空记录
			sm.clearRecord();
			break;
		case 0:		//退出系统
			sm.exitSystem();
		default:
			system("cls"); //清屏
			break;
		}
	}

	system("pause");
	return 0;
}