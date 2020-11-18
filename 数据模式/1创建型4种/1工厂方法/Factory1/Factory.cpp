#include <iostream>
using namespace std;
// ��������ģʽ����
// ---1.��������ֻ��������һ��Ʒ
// ---2.�����Ʒ�������������Ʒ

//��Ʒ������
class Product
{
public:
	virtual ~Product() {};
	virtual void show() = 0;

};

//��ƷA
class ProductA : public Product
{
public:
	virtual ~ProductA() {};
	void show() { cout << "ProductA" << endl; }
};

//��ƷB
class ProductB : public Product
{
public:
	virtual ~ProductB() {};
	void show() { cout << "ProductB" << endl; }
};

//�򵥹�����
class Factory
{
public:
	virtual Product *CreateProduct() = 0;
};

//��������A
class FactoryA : public Factory
{
public:
	Product *CreateProduct()
	{
		return new ProductA();
	}
};
//��������B
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