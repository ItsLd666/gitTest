#include <iostream>
#include "speechManager.h"

using namespace std;

int main() {
	SpeechManager sm;
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//��ʼ����
			sm.startSpeech();

			//����
			/*sm.createSpeaker();
			for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
				cout << "ѡ�ֱ�ţ�" << it->first << " " << "ѡ��������" << it->second.m_Name << " " << "ѡ�ֳɼ���" << *it->second.m_Score << endl;	
			}*/

			break;
		case 2:		//�鿴��¼
			sm.showRecord();
			break;
		case 3:		//��ռ�¼
			sm.clearRecord();
			break;
		case 0:		//�˳�ϵͳ
			sm.exitSystem();
		default:
			system("cls"); //����
			break;
		}
	}

	system("pause");
	return 0;
}