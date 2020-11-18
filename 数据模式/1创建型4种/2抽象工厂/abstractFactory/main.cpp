#include <string>
#include <iostream>
using namespace std;
// ���󹤳�
// ---1.���󹤳�������һϵͳ��Ʒ

// ��Ʒ����A
class ProductA
{
public:
	virtual void Show() = 0;
};

// �����ƷA1
class ProductA1 : public ProductA
{ 
public:
	void Show() override
	{
		cout << "I'm ProductA1" << endl;
	}

};

// �����ƷA2
class ProductA2 : public ProductA
{ 
public:
	void Show() override
	{
		cout << "I'm ProductA2" << endl;
	}
};

// ��Ʒ����B
class ProductB
{
public:
	virtual void Show() = 0;
};

// �����ƷB1
class ProductB1 : public ProductB
{
public:
	void Show() override
	{
		cout << "I'm ProductB1" << endl;
	}

};

// �����ƷB2
class ProductB2 : public ProductB
{
public:
	void Show() override
	{
		cout << "I'm ProductB2" << endl;
	}
};

// ���󹤳�����(�߱���������ƷA�Ͳ�ƷB���ֲ�Ʒ������)
class AbstractFactory
{
public:
	virtual ProductA* createProductA() = 0;
	virtual ProductB* createProductB() = 0;
};

// ����1(��������ƷA�Ͳ�ƷB�ľ����Ʒ)
class Factory1 : public AbstractFactory
{
public:
	ProductA* createProductA() override
	{
		return new ProductA1();
	}
	ProductB* createProductB() override
	{
		return new ProductB1();
	}
};

// ����2(��������ƷA�Ͳ�ƷB�ľ����Ʒ)
class Factory2 : public AbstractFactory
{
public:
	ProductA* createProductA() override
	{
		return new ProductA2();
	}
	ProductB* createProductB() override
	{
		return new ProductB2();
	}
};


int main()
{
	AbstractFactory *factoryObj1 = new Factory1();
	ProductA *productObjA1 = factoryObj1->createProductA();
	ProductB *productObjB1 = factoryObj1->createProductB();

	productObjA1->Show();
	productObjB1->Show();

	AbstractFactory *factoryObj2 = new Factory2();
	ProductA *productObjA2 = factoryObj2->createProductA();
	ProductB *productObjB2 = factoryObj2->createProductB();

	productObjA2->Show();
	productObjB2->Show();

	system("pause");
	return 0;
}