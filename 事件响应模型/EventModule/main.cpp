#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include <windows.h>

enum class EventType
{
	NON = 1,
	KEY_BOARD,  // 键盘
	MOUSE		// 鼠标
};
// 监听者、观察者基类
class EventListener
{
public:
	EventListener():m_Type(EventType::NON){	}

	virtual EventType getType() { return m_Type; }

	virtual void update() = 0;
protected:
	EventType m_Type;
};

// [举例一]键盘事件
class KeyListener : public EventListener
{
public:
	KeyListener() 
	{
		this->m_Type = EventType::KEY_BOARD;
	}

	virtual void update() override
	{
		cout << "KeyListener upDate()" << endl;
	}

};
// [举例二]键盘事件
class MouseListener : public EventListener
{
public:
	MouseListener()
	{
		this->m_Type = EventType::MOUSE;
	}

	virtual void update() override
	{
		cout << "MouseListener upDate()" << endl;
	}

};

// 派送中心
class EventDispatch
{
public:
	EventDispatch() {
		// 创建EventListener*数组并添加到map中
		vector<EventListener*> *vec1 = new vector<EventListener *>();
		vec1->reserve(20);
		vector<EventListener*> *vec2 = new vector<EventListener *>();
		vec2->reserve(20);
		map_type_listener.insert(pair<EventType, 
				vector<EventListener*>*>(EventType::KEY_BOARD, vec1));
		map_type_listener.insert(pair<EventType, 
				vector<EventListener*>*>(EventType::MOUSE, vec2));
	}

	void addListener(EventListener* e)
	{
		map<EventType, vector<EventListener*>*>::iterator iter;

		if (e->getType() == EventType::KEY_BOARD)
		{
			iter = map_type_listener.find(EventType::KEY_BOARD);
			//if (iter == map_type_listener.end()){
			//	vector<EventListener*> *vec1 = new vector<EventListener *>();
			//	map_type_listener.insert(pair<EventType,
			//		vector<EventListener*>*>(EventType::KEY_BOARD, vec1));
			//}
		}else if (e->getType() == EventType::MOUSE)
		{
			iter = map_type_listener.find(EventType::MOUSE);
			//if (iter == map_type_listener.end()) {
			//	vector<EventListener*> *vec2 = new vector<EventListener *>();
			//	map_type_listener.insert(pair<EventType,
			//		vector<EventListener*>*>(EventType::MOUSE, vec2));
			//}
		}
		vector<EventListener*>* eListener = iter->second;
		eListener->push_back(e);
	}

	void dispatch()
	{
		map<EventType, vector<EventListener*>*>::iterator iter;
		for (iter = map_type_listener.begin(); iter != map_type_listener.end(); iter++)
		{
			vector<EventListener*>* eListener = iter->second;
			vector<EventListener*>::iterator it = eListener->begin();
			for (it; it != eListener->end(); it++)
			{
				// 更新状态
				(*it)->update();
			}
		}
	}
private:
	// map[key:事件类型 value:EventListener*数组的指针]
	map<EventType, vector<EventListener*>*> map_type_listener;
};

// 游戏节点
class GameNode
{
public:
	GameNode(EventDispatch* pEventDispatch):m_pEventDispatch(pEventDispatch){}

public:
	EventDispatch* m_pEventDispatch;
};

EventDispatch dis;
int main()
{
	KeyListener kListener;
	KeyListener kListener2;
	MouseListener mListener;
	GameNode node(&dis);

	// 添加键盘监听事件
	node.m_pEventDispatch->addListener(&kListener);
	
	// 添加鼠标监听事件
	node.m_pEventDispatch->addListener(&mListener);

	while (true)
	{
		dis.dispatch();
		Sleep(5000);
	}
	
	system("pause");
	return 0;
}