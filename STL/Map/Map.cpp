// Map.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <iostream>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//////////////////////////////////////////////////////////////////////////
	/*map*/
	//1.һ��һ(key-value)
	//2.�ڲ��Ǻ����ʵ��
	//3.�ڲ��������
	//////////////////////////////////////////////////////////////////////////
	map<int, string> map1;
	//��һ�ֲ�������
	map1.insert(map<int, string>::value_type(10,"aaaa"));
	//�ڶ��ֲ�������
	map1.insert(pair<int, string>(20,"bbbb"));
	//�����ֲ�������
	map1.insert(make_pair(30,"cccc"));
	//�����ֲ�������
	map1[40] = "dddd";

	//for (int i=10; i<=40; i+=10)
	//{
	//	cout<<map1[i].c_str()<<endl;
	//}
	for (map<int, string>::iterator it=map1.begin();it!=map1.end();it++)
	{
		cout<<it->first<<"  "<<it->second<<endl;
	}

	cout<<(map1.find(10))->second<<endl;

	printf("===========�ָ���============\t\n");

	//////////////////////////////////////////////////////////////////////////
	/*multimap*/
	//1.һ�Զ��ֵ(key-value)
	//////////////////////////////////////////////////////////////////////////
	multimap<int,string> mulmap;
	mulmap.insert(make_pair(10,"aaaa"));
	mulmap.insert(make_pair(10,"a1010"));
	mulmap.insert(make_pair(30,"cccc"));
	mulmap.insert(make_pair(20,"bbbb"));
	mulmap.insert(make_pair(10,"aa000"));
	//�����������ݲ����
	for (multimap<int, string>::iterator it=mulmap.begin();it!=mulmap.end();it++)
	{
		cout<<it->first<<"  "<<it->second<<endl;
	}
	printf("===========�ָ���============\t\n");

	//����10������������
	int count = mulmap.count(10);	//���ؼ�ֵΪ10��ֵ�����
	multimap<int, string>::iterator it=mulmap.find(10);//���ҵ�һ��10����Ӧ�ĵ�����
	for (int i=0;i<count;i++)
	{
		cout<<it->first<<"  "<<it->second<<endl;
		++it;
	}
	
	mulmap.lower_bound(20);	//���ص�һ��>=key��Ԫ�صĵ�����		==������20��
	mulmap.upper_bound(20);	//���ص�һ��>key��Ԫ�صĵ�����	[begin,end)	==�����ش���20�ļ�30
	getchar();
	return 0;
}

