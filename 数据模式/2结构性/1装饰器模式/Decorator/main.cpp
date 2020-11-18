#include <iostream>
using namespace std;
/************************************************************************/
/* 在原有实现上增加功能                                                 */
/************************************************************************/
class Component
{
public:
	virtual void Operation() = 0;
};
class ConcreteComponent : public Component
{
public:
	void Operation()
	{
		cout << "I am no decoratored ConcreteComponent" << endl;
	}
};
class Decorator : public Component
{
public:
	Decorator(Component *pComponent) : m_pComponentObj(pComponent) {}
	virtual void Operation()
	{
		if (m_pComponentObj != NULL)
		{
			m_pComponentObj->Operation();
		}
	}
protected:
	Component *m_pComponentObj;
};
class ConcreteDecoratorA : public Decorator
{
public:
	ConcreteDecoratorA(Component *pDecorator) : Decorator(pDecorator) {}
	void Operation()
	{
		AddedBehavior();
		Decorator::Operation();
	}
	void  AddedBehavior()
	{
		cout << "This is added behavior A." << endl;
	}
};
class ConcreteDecoratorB : public Decorator
{
public:
	ConcreteDecoratorB(Component *pDecorator) : Decorator(pDecorator) {}
	void Operation()
	{
		AddedBehavior();
		Decorator::Operation();
	}
	void  AddedBehavior()
	{
		cout << "This is added behavior B." << endl;
	}
};
int main()
{
	Component *pComponentObj = new ConcreteComponent();
	Decorator *pDecoratorAOjb = new ConcreteDecoratorA(pComponentObj);
	pDecoratorAOjb->Operation();
	cout << "=============================================" << endl;
	Decorator *pDecoratorBOjb = new ConcreteDecoratorB(pComponentObj);
	pDecoratorBOjb->Operation();
	cout << "=============================================" << endl;
	Decorator *pDecoratorBAOjb = new ConcreteDecoratorB(pDecoratorAOjb);
	pDecoratorBAOjb->Operation();
	cout << "=============================================" << endl;
	Decorator *pDecoratorABOjb = new ConcreteDecoratorA(pDecoratorBOjb);
	pDecoratorABOjb->Operation();
	cout << "=============================================" << endl;
	delete pDecoratorABOjb;
	pDecoratorABOjb = NULL;
	delete pDecoratorBAOjb;
	pDecoratorBAOjb = NULL;
	delete pDecoratorBOjb;
	pDecoratorBOjb = NULL;
	delete pDecoratorAOjb;
	pDecoratorAOjb = NULL;
	delete pComponentObj;
	pComponentObj = NULL;
}