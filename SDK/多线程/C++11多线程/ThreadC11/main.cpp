//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

#pragma region C++11 thread基本创建方法

#if DOC1
// 案例一
void my_print()
{
	cout << "线程开始执行了!" << " thread ID= " << std::this_thread::get_id() << endl;
	//...
	//...
	cout << "线程结束执行了!" << " thread ID= " << std::this_thread::get_id() << endl;
}

// 案例二
class TA
{
public:
	TA()
	{
		cout << "TA构造函数执行" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}
	~TA()
	{
		cout << "~TA析构函数执行" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	// 案例二
	void operator()()	// 不带参数    必须重载()  因子线程需运行函数
	{
		cout << "线程operator开始执行了!" << this << " thread ID= " << std::this_thread::get_id() << endl;
		//...
		//...
		cout << "线程operator结束执行了!" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	TA(const TA& ta)
	{
		cout << "TA拷贝构造函数执行:" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}

	// 案例四
	void thread_fun()
	{
		cout << "thread_fun执行:" << this << " thread ID= " << std::this_thread::get_id() << endl;
	}
};

int main()
{
	// 案例一 直接用函数当对象
	std::thread thobj(my_print);
	thobj.join();
	//bool b = thobj.joinable();
	//thobj.detach();
	//b = thobj.joinable();

	// 案例二 直接用类对象当对象
	//TA t;
	//std::thread thobj2(t);
	//std::thread thobj2(std::ref(t));  // 注意这两种的区别 std::ref直接引用原对象，少了一次拷贝和析构
	//thobj2.join();		 // 此时子线程拷贝的对象 析构函数会在前台运行
	//thobj2.detach();	// 此时子线程拷贝的对象 析构函数会在后台运行

	// 案例三 lambda表达式
	//auto my_thread = [] {
	//	cout << "lambda线程开始执行了!" << endl;
	//	//...
	//	//...
	//	cout << "lambda线程结束执行了!" << endl;
	//};
	//auto my_thread1 = []()->void {
	//	cout << "lambda线程开始执行了!" << endl;
	//	//...
	//	//...
	//	cout << "lambda线程结束执行了!" << endl;
	//};

	//std::thread thobj3(my_thread);
	//thobj3.join();

	//std::thread thobj4([] {
	//	cout << "lambda线程开始执行了!" << endl;
	//	//...
	//	//...
	//	cout << "lambda线程结束执行了!" << endl;
	//});

	//thobj4.join();
	//案例四 使用类成员函数作为线程函数
	//TA t;
	//std::thread thobj5(&TA::thread_fun, &t);
	//thobj5.join();

	printf("hello jadeshu...\n");
	//system("pause");
	return 0;
}
#endif
#pragma endregion C++11 thread基本创建方法

#pragma region 线程传参实例应用

#if DOC2
void my_print(const int num, const string &buf)
{
	cout << num << endl;
	cout << buf << endl;
}

int main()
{
	//一、传递临时对象作为线程参数
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
#pragma endregion 线程传参实例应用

#pragma region 创建和等待多个线程,共享数据

mutex mt;
void thread_fun(int num)
{
	mt.lock();
	cout << "thread_fun执行: num=" << num << " thread ID= " << std::this_thread::get_id() << endl;
	mt.unlock();
}

int main()
{
	// 案例一.创建多个线程
	vector<std::thread> myThreads;
	for (int i = 0; i < 10; i++)
	{
		// 创建10个线程
		myThreads.push_back(std::thread(thread_fun, i));
	}

	for (auto &th : myThreads)
	{
		th.join();	// 等待10个线程完成
	}


	cout << " main  thread end!" << endl;
	return 0;
}
#pragma endregion 创建和等待多个线程,共享数据