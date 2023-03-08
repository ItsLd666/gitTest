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
	cout << "��л����ʹ�ã�" << endl;
	system("pause");
	exit(0); //�˳�
}

void SpeechManager::show_Menu() {
	cout << "***********************************************" << endl;
	cout << "*******************��ӭ�μӱ���****************" << endl;
	cout << "*****************1.��ʼ�ݽ�����****************" << endl;
	cout << "*****************2.�鿴�����¼****************" << endl;
	cout << "*****************3.��ձ�����¼****************" << endl;
	cout << "*****************0.�˳���������****************" << endl;
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
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++) {
			sp.m_Score[i] = 0;
		}
		 
		this->v1.push_back(i + 10001); //��Աid

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void SpeechManager::speechDraw() {
	cout << "��<" << this->m_Index << ">��ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "��ǩ������£�" << endl;
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

//����
void SpeechManager::speechContest() {
	cout << "--------------��<" << this->m_Index << ">����ʽ������ʼ��--------------" << endl;
	multimap<double, int, greater<double>> groupScore;  //��ʱ����������key������value��ѡ�ֱ��
	int num = 0;//��¼������6��һ��

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
		for (int i = 0; i < 10; i++) {        //10����ί
			double score = (rand() % 401 + 600) / 10.f;  //600~100
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		//ȥ����ͺ���߷�
		d.pop_back();
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //��map�����б��������˵�һ�ֵķ���
		groupScore.insert(make_pair(avg, *it));   //��ʱ�������棬�����ж�num�Ƿ����6. 6��һ�鵥������
		if (num % 6 == 0) {
			cout << "��<" << num / 6 << ">С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���" << this->m_Speaker[it->second].m_Score[m_Index-1] << endl;
			}
			int count = 0;
			//ȡǰ����
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
	cout << "--------------��<" << this->m_Index << ">�ֱ������-------------" << endl;
	system("pause");
}

//���Ʊ�������
void SpeechManager::startSpeech() {
	//��һ��
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������

	//�ڶ���
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showRes();
	//4.�������

}

void SpeechManager::showRes() {
	cout << "-----------------------�������-------------------------" << endl;
	int number = 1;
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		cout << "��<" << number << ">��:" << " ������" << this->m_Speaker[*it].m_Name << " �÷֣�" << this->m_Speaker[*it].m_Score[1] << endl;
		number++;
	}
	cout << endl;
}
void SpeechManager::writeRes() {

}