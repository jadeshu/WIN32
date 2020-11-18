// 模板模式
#include <iostream>
using namespace std;

class Template
{
public:
	Template() = default;
	virtual ~Template(){};

	virtual void print(int num) = 0;

	void update()
	{
		cout << "打印开始" << endl;
		// 打印10次
		for (int i = 1; i < 11; ++i)
		{
			print(i);
		}
	}
};

class Sub : public Template
{
public:
	Sub() = default;
	~Sub() = default;

	void print(int num) override
	{
		cout << "子类的实现" << num << endl;
	}
	
};

int main(int argc, char const *argv[])
{
	Sub sub;
	sub.update();
	return 0;
}