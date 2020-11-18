#include <string>
#include <iostream>
#include <list>

using namespace std;
// �۲���ģʽ

// �۲���
class Observer
{
public:
	virtual void Update(int value) = 0;
};

// Ŀ����
class Subject
{
public:
	virtual void Attach(Observer *) = 0;
	virtual void Detach(Observer *) = 0;
	virtual void Notify() = 0;

};

// ����Ŀ��
class ConcreteSubject : public Subject
{
public:
	void SetState(int state)
	{
		m_iState = state;
	}

	void Attach(Observer * obj) override
	{
		m_ObserverList.push_back(obj);
	}

	void Detach(Observer * obj) override
	{
		m_ObserverList.remove(obj);
	}

	void Notify() override
	{
		std::list<Observer *>::iterator it = m_ObserverList.begin();
		while (it != m_ObserverList.end())
		{
			(*it)->Update(m_iState);
			++it;
		}

	}

private:
	std::list<Observer *> m_ObserverList;
	int m_iState;
};



// ����۲���
class ConcreteObserver : public Observer
{
public:
	void Update(int value) override
	{
		cout << "ConcreteObserver  update! New State:" << value << endl;
	}
};

int main()
{
	Observer *pObserver = new ConcreteObserver();
	ConcreteSubject *pSubject = new ConcreteSubject();
	pSubject->SetState(10);
	pSubject->Attach(pObserver);
	pSubject->Notify();

	pSubject->SetState(20);
	pSubject->Notify();

	system("pause");
	return 0;
}