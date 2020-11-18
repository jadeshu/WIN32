#include<iostream>
using namespace std;

class Test
{
public:
	static Test* GetInstance()
	{
		static Test *m_pTest = NULL;
		if (NULL == m_pTest)
		{
			return m_pTest = new Test();
		}
		return m_pTest;
	}	
private:
	Test(){}
};

int main()
{
	Test* p = Test::GetInstance();
	system("pause");
	return 0;
}