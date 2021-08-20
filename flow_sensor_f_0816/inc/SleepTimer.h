#pragma once

#include <array>

#define SSD1306_DISPLAYOFF          0xAE

#include "ConfigurationManager.h"

class SleepTimer
{
	//int m_intervalArray[] = {1,2,5,-1};
	std::array <int,5> m_intervalArray{{5,60,120,360,-1}};
	int m_selectedIndex = 0;
	
	unsigned long m_startMillis = 0;
	
	ConfigurationManager* m_configurationManager;
	
public:

	SleepTimer()
	{
		m_selectedIndex = 4;
	}
	
	~SleepTimer()=default;
	
	void init(ConfigurationManager* configurationManager)
	{
		m_configurationManager = configurationManager;
	}
	
	void selectIntervalByIndex(int index)
	{	
		if(index >= 0 && index < m_intervalArray.size())
		{
			m_selectedIndex = index;
			m_configurationManager->saveTimerIntervalToEEPROM(m_intervalArray[m_selectedIndex]);
		}
		
		return;
	}

	void selectIntervalByValue(int interval)
	{
		for(int i=0; i < m_intervalArray.size(); i++)
			if(m_intervalArray[i] == interval)
			{
				m_selectedIndex = i;
				m_configurationManager->saveTimerIntervalToEEPROM(m_intervalArray[m_selectedIndex]);
				break;
			}
		
		return;
	}
	
	void selectNextInterval()
	{
		m_selectedIndex = (m_selectedIndex + 1) % m_intervalArray.size();
	}
	
	void selectPreviousInterval()
	{
		if(m_selectedIndex == 0)
			m_selectedIndex = m_intervalArray.size() - 1;
		else
			m_selectedIndex = m_selectedIndex - 1;		
	}
	
	void resetIdleCounter()
	{
		m_startMillis = millis();	
	}
	
	int getSelectedInterval() { m_intervalArray[m_selectedIndex]; } 
	
	void handleTick()
	{
		if(m_intervalArray[m_selectedIndex] == -1)
			return;
		
		unsigned long passedMillis = millis() - m_startMillis;
		
		//Serial.println("SleepTimer tick: " + String(passedMillis) );	
		//Serial.flush();
		
		if(passedMillis / 1000 >= m_intervalArray[m_selectedIndex])	
		{
			Serial.println("SleepTimer deep_sleep!");	
			Serial.flush();


			#ifdef USE_SSD1306_DISPLAY
			//Power off SSD1306 before going to deep sleep
			Wire.beginTransmission(0x3C);
			Wire.write(0x80);
			Wire.write(SSD1306_DISPLAYOFF);
			Wire.endTransmission();
			
			#endif
			esp_deep_sleep_start();					
		}			
	}
};