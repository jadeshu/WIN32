//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
#include <string>
#include <iostream>
using namespace std;

// ΪʲôҪʹ��ԭ��ģʽ��
//1.�����ǵĶ������Ͳ��ǿ�ʼ����ȷ���ģ��������������������ȷ���Ļ���
//	��ô����ͨ��������͵Ķ����¡��һ���µĶ���Ƚ�����һЩ��
//2.�е�ʱ��������Ҫһ��������ĳ��״̬�µĸ�������ʱ������ʹ��ԭ��ģʽ����õ�ѡ��
//	���磺һ�����󣬾���һ�δ���֮�����ڲ���״̬�����˱仯�����ʱ��������Ҫһ����
//	��״̬�ĸ��������ֱ��newһ���µĶ���Ļ�����������״̬�ǲ��Եģ���ʱ������ʹ��ԭ��ģʽ��
//	��ԭ���Ķ��󿽱�һ���������������ͺ�֮ǰ�Ķ�������ȫһ�µ��ˣ�
//3.�����Ǵ���һЩ�Ƚϼ򵥵Ķ���ʱ�����Ҷ���֮��������С�����ܾͼ������Բ�ͬ���ѣ�
//	��ô�Ϳ���ʹ��ԭ��ģʽ����ɣ�ʡȥ�˴�������ʱ���鷳�ˣ�
//4.�е�ʱ�򣬴�������ʱ�����캯���Ĳ����ܶ࣬���Լ��ֲ���ȫ��֪��ÿ�����������壬
//	�Ϳ���ʹ��ԭ��ģʽ������һ���µĶ��󣬲���ȥ��ᴴ���Ĺ��̣��ô������̼���ȥ�ɡ�
class CPrototype
{
public:
	CPrototype() {}
	virtual ~CPrototype(){}

	virtual CPrototype * Clone() = 0;
};

class CConcretePrototype : public CPrototype
{
public:
	CConcretePrototype()/* : m_count(0) */{}
	virtual ~CConcretePrototype() {}

	// �������캯��
	CConcretePrototype(const CConcretePrototype& rhs)
	{
		this->m_count = rhs.m_count;
	}

	CPrototype * Clone() override
	{
		//���ÿ������캯��
		return new CConcretePrototype(*this);
	}

private:
	int m_count = 10;	// �������ڲ�����
};

int main()
{
	//���ɶ���
	CPrototype* p = new CConcretePrototype();
	CPrototype* pclone = p->Clone();

	system("pause");
	return 0;
}