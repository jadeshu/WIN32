#include <iostream>
#include <vector>
using namespace std;

class ConcreteElementA;
class ConcreteElementB;

class Visitor
{
public:
	virtual void VisitConcreteElementA(ConcreteElementA *pElementA) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB *pElementB) = 0;
};

class ConcreteVisitor1 : public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA *pElementA)
	{
		// 现在根据传进来的pElementA，可以对ConcreteElementA中的element进行操作
		printf("ConcreteVisitor1::A \n");
	}
	void VisitConcreteElementB(ConcreteElementB *pElementB)
	{
		// 现在根据传进来的pElementB，可以对ConcreteElementB中的element进行操作
		printf("ConcreteVisitor1::B \n");
	}
};

class ConcreteVisitor2 : public Visitor
{
public:
	void VisitConcreteElementA(ConcreteElementA *pElementA)
	{
		printf("ConcreteVisitor2::A \n");
	}

	void VisitConcreteElementB(ConcreteElementB *pElementB)
	{
		printf("ConcreteVisitor2::B \n");
	}
};

// Element object
class Element
{
public:
	virtual void Accept(Visitor *pVisitor) = 0;
};

class ConcreteElementA : public Element
{
public:
	void Accept(Visitor *pVisitor)
	{
		pVisitor->VisitConcreteElementA(this);
	}
};


class ConcreteElementB : public Element
{
public:
	void Accept(Visitor *pVisitor)
	{
		pVisitor->VisitConcreteElementB(this);
	}
};

// ObjectStructure类，能枚举它的元素，可以提供一个高层的接口以允许访问者访问它的元素
class ObjectStructure
{
public:
	void Attach(Element *pElement)
	{
		elements.push_back(pElement);
	}

	void Detach(Element *pElement)
	{
		vector<Element *>::iterator it = find(elements.begin(), elements.end(), pElement);
		if (it != elements.end())
		{
			elements.erase(it);
		}
	}

	void Accept(Visitor *pVisitor)
	{
		// 为每一个element设置visitor，进行对应的操作
		for (vector<Element *>::const_iterator it = elements.begin(); it != elements.end(); ++it)
		{
			(*it)->Accept(pVisitor);
		}
	}

private:
	vector<Element *> elements;
};

int main()
{
	ObjectStructure *pObject = new ObjectStructure;

	ConcreteElementA *pElementA = new ConcreteElementA;
	ConcreteElementB *pElementB = new ConcreteElementB;

	pObject->Attach(pElementA);
	pObject->Attach(pElementB);

	ConcreteVisitor1 *pVisitor1 = new ConcreteVisitor1;
	ConcreteVisitor2 *pVisitor2 = new ConcreteVisitor2;

	pObject->Accept(pVisitor1);
	printf("======================= \n");
	pObject->Accept(pVisitor2);

	if (pVisitor2) delete pVisitor2;
	if (pVisitor1) delete pVisitor1;
	if (pElementB) delete pElementB;
	if (pElementA) delete pElementA;
	if (pObject) delete pObject;

	return 0;
}