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
		cout<<"算法A实现 "<<"ConcreteStrategyA :: AlgorithmInterface()方法"<<endl;
	}
};

class ConcreteStrategyB : public strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout<<"算法B实现 "<<"ConcreteStrategyB :: AlgorithmInterface()方法"<<endl;
	}
};

class ConcreteStrategyC : public strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout<<"算法C实现 "<<"ConcreteStrategyC :: AlgorithmInterface()方法"<<endl;
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