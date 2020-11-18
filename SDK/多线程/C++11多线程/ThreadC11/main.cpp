//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

#pragma region C++11 thread������������

#if DOC1
// ����һ
void my_print()
{
	cout << "�߳̿�ʼִ����!" << " thread ID= " << std::this_thread::get_id() << endl;
	//...
	//...
	cout << "�߳̽���ִ����!" << " thread ID= " << std::this_thread::get_id() << endl;
}

// ������
class TA
{
public:
	TA()
	{
		cout << "TA���캯��ִ��" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}
	~TA()
	{
		cout << "~TA��������ִ��" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	// ������
	void operator()()	// ��������    ��������()  �����߳������к���
	{
		cout << "�߳�operator��ʼִ����!" << this << " thread ID= " << std::this_thread::get_id() << endl;
		//...
		//...
		cout << "�߳�operator����ִ����!" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	TA(const TA& ta)
	{
		cout << "TA�������캯��ִ��:" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	// ������
	void thread_fun()
	{
		cout << "thread_funִ��:" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}
};

int main()
{
	// ����һ ֱ���ú���������
	std::thread thobj(my_print);
	thobj.join();
	//bool b = thobj.joinable();
	//thobj.detach();
	//b = thobj.joinable();

	// ������ ֱ��������󵱶���
	//TA t;
	//std::thread thobj2(t);
	//std::thread thobj2(std::ref(t));  // ע�������ֵ����� std::refֱ������ԭ��������һ�ο���������
	//thobj2.join();		 // ��ʱ���߳̿����Ķ��� ������������ǰ̨����
	//thobj2.detach();	// ��ʱ���߳̿����Ķ��� �����������ں�̨����

	// ������ lambda���ʽ
	//auto my_thread = [] {
	//	cout << "lambda�߳̿�ʼִ����!" << endl;
	//	//...
	//	//...
	//	cout << "lambda�߳̽���ִ����!" << endl;
	//};
	//auto my_thread1 = []()->void {
	//	cout << "lambda�߳̿�ʼִ����!" << endl;
	//	//...
	//	//...
	//	cout << "lambda�߳̽���ִ����!" << endl;
	//};

	//std::thread thobj3(my_thread);
	//thobj3.join();

	//std::thread thobj4([] {
	//	cout << "lambda�߳̿�ʼִ����!" << endl;
	//	//...
	//	//...
	//	cout << "lambda�߳̽���ִ����!" << endl;
	//});

	//thobj4.join();
	//������ ʹ�����Ա������Ϊ�̺߳���
	//TA t;
	//std::thread thobj5(&TA::thread_fun, &t);
	//thobj5.join();

	printf("hello jadeshu...\n");
	//system("pause");
	return 0;
}
#endif
#pragma endregion C++11 thread������������

#pragma region �̴߳���ʵ��Ӧ��

#if DOC2
void my_print(const int num, const string &buf)
{
	cout << num << endl;
	cout << buf << endl;
}

int main()
{
	//һ��������ʱ������Ϊ�̲߳���
	int var = 20;
	int& my_var = var;
	char my_buf[] = "this is main.cpp";
	std::thread thobj1(my_print,my_var,string(my_buf));
	thobj1.detach();
	//thobj1.join();

	printf("hello jadeshu...\n");
	//system("pause");
	return 0;
}
#endif
#pragma endregion �̴߳���ʵ��Ӧ��

#pragma region �����͵ȴ�����߳�,��������

mutex mt;
void thread_fun(int num)
{
	mt.lock();
	cout << "thread_funִ��: num=" << num << " thread ID= " << std::this_thread::get_id() << endl;
	mt.unlock();
}

int main()
{
	// ����һ.��������߳�
	vector<std::thread> myThreads;
	for (int i = 0; i < 10; i++)
	{
		// ����10���߳�
		myThreads.push_back(std::thread(thread_fun, i));
	}

	for (auto &th : myThreads)
	{
		th.join();	// �ȴ�10���߳����
	}


	cout << " main  thread end!" << endl;
	return 0;
}
#pragma endregion �����͵ȴ�����߳�,��������