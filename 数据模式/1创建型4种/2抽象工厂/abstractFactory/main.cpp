#include <string>
#include <iostream>
using namespace std;
// 抽象工厂
// ---1.抽象工厂能生产一系统产品

// 产品基类A
class ProductA
{
public:
	virtual void Show() = 0;
};

// 具体产品A1
class ProductA1 : public ProductA
{ 
public:
	void Show() override
	{
		cout << "I'm ProductA1" << endl;
	}

};

// 具体产品A2
class ProductA2 : public ProductA
{ 
public:
	void Show() override
	{
		cout << "I'm ProductA2" << endl;
	}
};

// 产品基类B
class ProductB
{
public:
	virtual void Show() = 0;
};

// 具体产品B1
class ProductB1 : public ProductB
{
public:
	void Show() override
	{
		cout << "I'm ProductB1" << endl;
	}

};

// 具体产品B2
class ProductB2 : public ProductB
{
public:
	void Show() override
	{
		cout << "I'm ProductB2" << endl;
	}
};

// 抽象工厂基类(具备能生产产品A和产品B两种产品的能力)
class AbstractFactory
{
public:
	virtual ProductA* createProductA() = 0;
	virtual ProductB* createProductB() = 0;
};

// 工厂1(能生产产品A和产品B的具体产品)
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

// 工厂2(能生产产品A和产品B的具体产品)
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