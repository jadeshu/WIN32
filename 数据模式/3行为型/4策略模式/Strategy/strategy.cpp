#include <iostream>
using namespace std;

class strategy
{
public:
	virtual void AlgorithmInterface() = 0;
};

class ConcreteStrategyA : public strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout<<"�㷨Aʵ�� "<<"ConcreteStrategyA :: AlgorithmInterface()����"<<endl;
	}
};

class ConcreteStrategyB : public strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout<<"�㷨Bʵ�� "<<"ConcreteStrategyB :: AlgorithmInterface()����"<<endl;
	}
};

class ConcreteStrategyC : public strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout<<"�㷨Cʵ�� "<<"ConcreteStrategyC :: AlgorithmInterface()����"<<endl;
	}
};

class Context
{
public:
	Context(strategy* strate):m_strate(strate)
	{
	}
	void ContextInterface()
	{
		m_strate->AlgorithmInterface();
	}
private:
	strategy* m_strate;
};
int main()
{
	Context *context = new Context(new ConcreteStrategyA());
	context->ContextInterface();
	context = new Context(new ConcreteStrategyB());
	context->ContextInterface();
	context = new Context(new ConcreteStrategyC());
	context->ContextInterface();

	system("PAUSE");
	return 0;
}