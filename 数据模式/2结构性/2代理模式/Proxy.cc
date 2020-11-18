// 代理模式
#include <iostream>
using namespace std;

class Object
{
public:
	virtual ~Object(){};
	
	virtual void action() = 0;
};

class ObjImpl : public Object
{
public:
	void action() override
	{
        cout << "========" << endl;
        cout << "被代理的类执行函数" << endl;
        cout << "========" << endl;

	}
};

class ProxyObj
{
public:
	ProxyObj()
	{
		cout << "代理类创建" << endl;
		pObj = new ObjImpl();
	}
	~ProxyObj()
	{
		if (pObj)
		{
			delete pObj;
			pObj = nullptr;
		}
	}

	void action()
	{
		cout << "代理开始" << endl;
		pObj->action();
		cout << "代理结束" << endl;
	}
private:
	Object* pObj;
};

int main(int argc, char const *argv[])
{
	ProxyObj obj;
	cout << "**********" << endl;
	obj.action();
	return 0;
}