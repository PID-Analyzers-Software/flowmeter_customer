#pragma once

class Menu;
class SSD1306Wire;
class U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI;
class Adafruit_ADS1115;
class GasManager;
class GasMenuItem;
class RunMenuItem;
class SleepTimer;
class DataLogger;
class DataSource;
class TimeSync;


class MenuRenderer
{
public:

	virtual void render(Menu* menu) = 0;
};

class SSD1306MenuRenderer : public MenuRenderer
{
protected:	
	SSD1306Wire* 			m_display;
	
public:

	SSD1306MenuRenderer(SSD1306Wire* display) : m_display(display)
	{}

	void render(Menu* menu);
	
};

class SSD1306GasMenuRenderer : public SSD1306MenuRenderer
{


public:

	SSD1306GasMenuRenderer(SSD1306Wire* display);
	
	void render(Menu* menu);
	
};

class SSD1306RunMenuRenderer : public SSD1306MenuRenderer
{
	DataSource* 		m_dataSource;
	GasManager*				m_gasManager;
	
public:

	SSD1306RunMenuRenderer(SSD1306Wire* display, DataSource* dataSource, GasManager* gasManager);

	void render(Menu* menu);
};

class SSD1306SleepTimerMenuRenderer : public SSD1306MenuRenderer
{
	SleepTimer* m_sleepTimer;
	
public:	
	
	SSD1306SleepTimerMenuRenderer(SSD1306Wire* display, SleepTimer* sleepTimer);
	
	void render(Menu* menu);
};

class SSD1306FlashLoggerMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;
	
public:	
	
	SSD1306FlashLoggerMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);
	
	void render(Menu* menu);
};

class SSD1306WiFiDumpMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1306WiFiDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1306WiFiRealTimeDumpMenuRenderer : public SSD1306MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1306WiFiRealTimeDumpMenuRenderer(SSD1306Wire* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1306NTPSyncMenuRenderer : public SSD1306MenuRenderer
{
	TimeSync* m_timeSync;

public:

	SSD1306NTPSyncMenuRenderer(SSD1306Wire* display, TimeSync* timeSync);

	void render(Menu* menu);
};

class SSD1306ShowTimeMenuRenderer : public SSD1306MenuRenderer
{

public:

	SSD1306ShowTimeMenuRenderer(SSD1306Wire* display);

	void render(Menu* menu);
};


///////////
//// SSD1327
///////////

class SSD1327MenuRenderer : public MenuRenderer
{
protected:
	U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* m_display;

public:

	SSD1327MenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display) : m_display(display)
	{}

	void render(Menu* menu);

};

class SSD1327GasMenuRenderer : public SSD1327MenuRenderer
{
public:

	SSD1327GasMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

	void render(Menu* menu);

};

class SSD1327RunMenuRenderer : public SSD1327MenuRenderer
{
	DataSource* m_dataSource;
	GasManager* m_gasManager;

public:

	SSD1327RunMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataSource* dataSource, GasManager* gasManager);

	void render(Menu* menu);
};

class SSD1327SleepTimerMenuRenderer : public SSD1327MenuRenderer
{
	SleepTimer* m_sleepTimer;

public:

	SSD1327SleepTimerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, SleepTimer* sleepTimer);

	void render(Menu* menu);
};

class SSD1327FlashLoggerMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327FlashLoggerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327WiFiDumpMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327WiFiDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327WiFiRealTimeDumpMenuRenderer : public SSD1327MenuRenderer
{
	DataLogger* m_dataLogger;

public:

	SSD1327WiFiRealTimeDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, DataLogger* dataLogger);

	void render(Menu* menu);
};

class SSD1327NTPSyncMenuRenderer : public SSD1327MenuRenderer
{
	TimeSync* m_timeSync;

public:

	SSD1327NTPSyncMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display, TimeSync* timeSync);

	void render(Menu* menu);
};


class SSD1327InfoMenuRenderer : public SSD1327MenuRenderer
{
    //TimeSync* m_timeSync;

public:

    SSD1327InfoMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

    void render(Menu* menu);
};




class SSD1327ShowTimeMenuRenderer : public SSD1327MenuRenderer
{

public:

	SSD1327ShowTimeMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* display);

	void render(Menu* menu);
};



