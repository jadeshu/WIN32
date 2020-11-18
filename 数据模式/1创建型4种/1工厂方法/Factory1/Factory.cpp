#include <iostream>
using namespace std;
// 工厂方法模式案例
// ---1.工厂方法只能生产单一产品
// ---2.具体产品工厂生产具体产品

//产品抽象类
class Product
{
public:
	virtual ~Product() {};
	virtual void show() = 0;

};

//产品A
class ProductA : public Product
{
public:
	virtual ~ProductA() {};
	void show() { cout << "ProductA" << endl; }
};

//产品B
class ProductB : public Product
{
public:
	virtual ~ProductB() {};
	void show() { cout << "ProductB" << endl; }
};

//简单工厂类
class Factory
{
public:
	virtual Product *CreateProduct() = 0;
};

//派生工厂A
class FactoryA : public Factory
{
public:
	Product *CreateProduct()
	{
		return new ProductA();
	}
};
//派生工厂B
class FactoryB : public Factory
{
public:
	Product *CreateProduct()
	{
		return new ProductB();
	}
};


int main()
{
	Factory *pFactoryA = new FactoryA();
	Product* pA = pFactoryA->CreateProduct();
	pA->show();

	Factory *pFactoryB = new FactoryB();
	Product* pB = pFactoryB->CreateProduct();
	pB->show();

	delete pFactoryA;
	delete pFactoryB;

	system("pause");
	return 0;
}