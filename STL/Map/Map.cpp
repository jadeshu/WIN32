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
	//1.一对一(key-value)
	//2.内部是红黑树实现
	//3.内部是有序的
	//////////////////////////////////////////////////////////////////////////
	map<int, string> map1;
	//第一种插入数据
	map1.insert(map<int, string>::value_type(10,"aaaa"));
	//第二种插入数据
	map1.insert(pair<int, string>(20,"bbbb"));
	//第三种插入数据
	map1.insert(make_pair(30,"cccc"));
	//第四种插入数据
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

	printf("===========分隔符============\t\n");

	//////////////////////////////////////////////////////////////////////////
	/*multimap*/
	//1.一对多个值(key-value)
	//////////////////////////////////////////////////////////////////////////
	multimap<int,string> mulmap;
	mulmap.insert(make_pair(10,"aaaa"));
	mulmap.insert(make_pair(10,"a1010"));
	mulmap.insert(make_pair(30,"cccc"));
	mulmap.insert(make_pair(20,"bbbb"));
	mulmap.insert(make_pair(10,"aa000"));
	//遍历所有数据并输出
	for (multimap<int, string>::iterator it=mulmap.begin();it!=mulmap.end();it++)
	{
		cout<<it->first<<"  "<<it->second<<endl;
	}
	printf("===========分隔符============\t\n");

	//查找10键的所有数据
	int count = mulmap.count(10);	//返回键值为10的值项个数
	multimap<int, string>::iterator it=mulmap.find(10);//查找第一个10键对应的迭代器
	for (int i=0;i<count;i++)
	{
		cout<<it->first<<"  "<<it->second<<endl;
		++it;
	}
	
	mulmap.lower_bound(20);	//返回第一个>=key的元素的迭代器		==即返回20的
	mulmap.upper_bound(20);	//返回第一个>key的元素的迭代器	[begin,end)	==即返回大于20的即30
	getchar();
	return 0;
}

