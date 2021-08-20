#pragma once

#include "GasManager.h"
#include "MenuRenderer.h"
#include "SleepTimer.h"
#include "DataLogger.h"
#include "TimeSync.h"

class Menu 
{
protected:

	String m_menuName;
	String m_parentMenuName;
	
	MenuRenderer* m_menuRenderer;

public:
	
	Menu(String name, String parentName, MenuRenderer* renderer) : m_menuName(name),
																   m_parentMenuName(parentName),
																   m_menuRenderer(renderer)
	{
		
	}
	
	virtual ~Menu() = default;
	
	
	String getName() { return m_menuName; }
	String getParentName() { return m_parentMenuName; }
	
	virtual void action() = 0;
	
	virtual void render()
	{
		m_menuRenderer->render(this);
	}
	
};

class GasMenuItem : public Menu 
{
	GasManager* m_gasManager;
	int m_gasIndex;
	
public:	

	GasMenuItem(String name, String parentName, int gasIndex, GasManager* gasManager, MenuRenderer* renderer) : Menu(name, parentName, renderer),
																					   m_gasManager(gasManager),
																					   m_gasIndex(gasIndex)
	{
		
	}

	void action()
	{
		m_gasManager->selectGasByIndex(m_gasIndex);		
	}
	
};

class RunMenuItem : public Menu 
{
	GasManager* m_gasManager;
	
public:	

	RunMenuItem(String name, String parentName, GasManager* gasManager, MenuRenderer* renderer) 
		: Menu(name, parentName, renderer),
		  m_gasManager(gasManager)
	{
		
	}

	void action()
	{
		//m_gasManager->selectGasByIndex(m_gasIndex);	
	}
	
};

class SleepTimerMenuItem : public Menu 
{
	SleepTimer* m_sleepTimer;
	
	int m_intervalIndex;
	
public:	

	SleepTimerMenuItem(String name, String parentName, int intervalIndex, SleepTimer* sleepTimer, MenuRenderer* renderer) 
		: Menu(name, parentName, renderer),
		m_sleepTimer(sleepTimer),
		m_intervalIndex(intervalIndex)
	{
		
	}

	void action()
	{
		m_sleepTimer->selectIntervalByIndex(m_intervalIndex);
	}
	
};

class DataLoggerFlashStoreMenuItem : public Menu 
{
	DataLogger* m_dataLogger;
	
public:	

	DataLoggerFlashStoreMenuItem(String name, String parentName, DataLogger* dataLogger, MenuRenderer* renderer) 
		: Menu(name, parentName, renderer),
		m_dataLogger(dataLogger)
	{

	}

	void action()
	{
		if( m_dataLogger->isFlashStoreSessionRunning() )
			m_dataLogger->stopFlashStoreSession();
		else
			m_dataLogger->startFlashStoreSession();
	}
	
};

class WiFiDumpMenuItem : public Menu
{
	DataLogger* m_dataLogger;

public:

	WiFiDumpMenuItem(String name, String parentName, DataLogger* dataLogger, MenuRenderer* renderer)
		: Menu(name, parentName, renderer),
		m_dataLogger(dataLogger)
	{

	}

	void action()
	{
		if (m_dataLogger->isWiFiDumpRunning())
			m_dataLogger->stopWiFiDumpSession();
		else
			m_dataLogger->startWiFiDumpSession();
	}

};

class WiFiRealTimeDumpMenuItem : public Menu
{
	DataLogger* m_dataLogger;

public:

	WiFiRealTimeDumpMenuItem(String name, String parentName, DataLogger* dataLogger, MenuRenderer* renderer)
		: Menu(name, parentName, renderer),
		m_dataLogger(dataLogger)
	{

	}

	void action()
	{
		if (m_dataLogger->isWiFiRealTimeDumpRunning())
			m_dataLogger->stopWiFiRealTimeDumpSession();
		else
			m_dataLogger->startWiFiRealTimeDumpSession();
	}

};

class NTPSyncMenuItem : public Menu
{

	TimeSync* m_timeSync;

public:

	NTPSyncMenuItem(String name, String parentName, TimeSync* timeSync, MenuRenderer* renderer)
		: Menu(name, parentName, renderer)
	{
		m_timeSync = timeSync;
	}

	void action()
	{
		if(!m_timeSync->isNTCSyncRunning())
			m_timeSync->startNTPSync();
		else
		{
			m_timeSync->stopNTPSync();
		}
		
	}

};




class InfoMenuItem : public Menu
{

    //TimeSync* m_timeSync;

public:

    InfoMenuItem(String name, String parentName, MenuRenderer* renderer)
            : Menu(name, parentName, renderer)
    {
        //m_timeSync = timeSync;
    }

    void action()
    {


    }

};





class ShowTimeMenuItem : public Menu
{

public:

	ShowTimeMenuItem(String name, String parentName, MenuRenderer* renderer)
		: Menu(name, parentName, renderer)
	{

	}

	void action()
	{

	}

};

class CompositeMenu : public Menu
{
	std::vector<Menu*> m_menus;
	int m_currentIndex;
	
public:	

	CompositeMenu(String name, String parentName, std::vector<Menu*> menus) : Menu(name, parentName, nullptr),
														   m_menus(menus),
														   m_currentIndex(0)
	{
		
	}

	Menu* getCurrentMenu()
	{
		return m_menus[ m_currentIndex ];
	}

	void moveToNext()
	{
		m_currentIndex = (m_currentIndex + 1) % m_menus.size();
		Serial.println("moveToNext" + String(m_currentIndex) + " " + String(m_menus.size()) );
		Serial.println("moveToNext: " + m_menuName );	
		Serial.flush();
	}

	void action() override
	{
		m_menus[m_currentIndex]->action();
	}
	
	void render() override
	{
		//Serial.println("RENDER COMP : " + m_menuName );
		//Serial.flush();
		m_menus[ m_currentIndex ]->render();
	}
	
	void print()
	{
		Serial.println("Menu name: " + m_menuName + " Parent name: " + m_parentMenuName );
		for(Menu* m : m_menus)
			Serial.println("Menu name: " + m->getName() + " Parent name: " + m->getParentName() );
		Serial.flush();
	}
	
};

