// C++_learn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <numeric>

using namespace std;

void func(int a) {
	cout << a << " ";
}

void test01() {
	vector<int> vec;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++) {
		vec.emplace_back(i);
	}
	random_shuffle(vec.begin(), vec.end());
	for_each(vec.begin(), vec.end(), func);
	cout << endl;
}

class myPred {
public:
	bool operator() (int a) {
		return a > 6;
	}
};

void test02() {
	vector<int> vec2, vec3, vec4;
	for (int i = 0; i < 10; i++) {
		vec2.push_back(i + 1);
		vec3.push_back(i + 2);
	}
	vec4.resize(vec2.size() + vec3.size());
	merge(vec2.begin(), vec2.end(), vec3.begin(), vec3.end(), vec4.begin());
	for_each(vec4.begin(), vec4.end(), func);
	cout << endl;
	cout << "-------------翻转--------------" << endl;
	reverse(vec4.begin(), vec4.end());
	for_each(vec4.begin(), vec4.end(), func);
	cout << endl;
	cout << "-------------替换--------------" << endl;
	replace(vec4.begin(), vec4.end(), 8, 80);
	for_each(vec4.begin(), vec4.end(), func);
	cout << endl;
	cout << "-------------条件替换--------------" << endl;
	replace_if(vec4.begin(), vec4.end(), myPred(), 999);
	for_each(vec4.begin(), vec4.end(), func);
	cout << endl;
	cout << "-------------accumulate--------------" << endl;
	int total = accumulate(vec4.begin(), vec4.end(), 0);
	cout << total << endl;
	//fill(iterator beg , iterator end , value); 
	cout << "-------------交集并集-----------------" << endl;
	vector<int> target;
	target.resize(min(vec2.size(), vec3.size()));
	vector<int>::iterator isEnd = set_intersection(vec2.begin(), vec2.end(), vec3.begin(), vec3.end(), target.begin());
	for_each(target.begin(), isEnd, func);
	cout << endl;
}
 
int main()
{
	//test01();
	test02();
	system("pause");
    return 0;
}