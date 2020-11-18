// 状态模式

#include <iostream>
#include <string>
using namespace std;

class Weather
{
public:
	Weather() = default;
	virtual ~Weather(){};
	
	// 获取天气
	virtual string GetWeather() = 0;
};

class Sunshine : public Weather
{
public:
	string GetWeather() override
	{
		return "阳光";
	}
	
};

class Rain : public Weather
{
public:
	string GetWeather() override
	{
		return "下雨";
	}
	
};

class Context
{
public:
	Context() = default;
	~Context() = default;

	void SetWeather(Weather* wea)
	{
		this->weather = wea;
	}
	
	void Message()
	{
		if (weather)
		{
			cout << "今天天气是：" << weather->GetWeather() << endl;
		}
	}
private:
	Weather* weather;
};



int main(int argc, char const *argv[])
{
	Context cxt;
	Weather* w = new Sunshine();
	cxt.SetWeather(w);
	cxt.Message();
	delete w;
	w = nullptr;

	cout << "================" << endl;
	w = new Rain();
	cxt.SetWeather(w);
	cxt.Message();
	delete w;
	return 0;
}