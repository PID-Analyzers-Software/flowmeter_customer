#include "inc/ConfigurationManager.h"
#include <EEPROM.h>

#include "inc/Globals.h"
#include "inc/SleepTimer.h"
#include "inc/GasManager.h"

ConfigurationManager::ConfigurationManager()
{

}

void ConfigurationManager::init()
{
	setupEEPROM();
}

void ConfigurationManager::loadFromEEPROM()
{
	m_loadAllInProgress = true;
	
	int timerInterval = EEPROM.readInt(EEPROM_TIMER_OFFSET);
	Serial.println("config: timer interval: " + String(timerInterval));
	
	//m_sleepTimer->selectIntervalByValue( timerInterval );	
			
	// SLOPE
	double slope = -1;
	slope = EEPROM.readDouble(EEPROM_GAS_SLOPE_OFFSET);
	if(slope != -1)
		notifyParamChanged(c_SLOPE_PARAM_NAME, String(slope));
	Serial.println("config: slope: " + String(slope));
	// INTERCEPT
	double intercept = -1;
	intercept = EEPROM.readDouble(EEPROM_GAS_INTERCEPT_OFFSET);		
	if(intercept != -1)
		notifyParamChanged(c_INTERCEPT_PARAM_NAME, String(intercept));
	Serial.println("config: intercept: " + String(intercept));

	//secondP
    double secondp = -1;
    secondp = EEPROM.readDouble(EEPROM_GAS_SECONDP_OFFSET);
    if(secondp != -1)
        notifyParamChanged(c_SECONDP_PARAM_NAME, String(secondp));
    Serial.println("config: secondp: " + String(secondp));
	/*
		Gas TCs
	*/

	double AirTC = -1;
	AirTC =	EEPROM.readDouble(EEPROM_GAS_AIR_TC_OFFSET);
	if(AirTC != -1)
		notifyParamChanged(c_GAS_AIR_PARAM_NAME, String(AirTC));
	Serial.println("config: Air TC: " + String(AirTC));
	
	double O2TC = -1;
	O2TC = EEPROM.readDouble(EEPROM_GAS_O2_TC_OFFSET);
	if(O2TC != -1)
		notifyParamChanged(c_GAS_O2_PARAM_NAME, String(O2TC));
	Serial.println("config: O2 TC: " + String(O2TC));		
	
	double N2TC = -1;
	N2TC = EEPROM.readDouble(EEPROM_GAS_N2_TC_OFFSET);	
	if(N2TC != -1)
		notifyParamChanged(c_GAS_N2_PARAM_NAME, String(N2TC));
	Serial.println("config: N2 TC: " + String(N2TC));
	
	double HeTC = -1;
	HeTC = EEPROM.readDouble(EEPROM_GAS_He_TC_OFFSET);
	if(HeTC != -1)
		notifyParamChanged(c_GAS_He_PARAM_NAME, String(HeTC));
	Serial.println("config: He TC: " + String(HeTC));
	
	double H2TC = -1;
	H2TC = EEPROM.readDouble(EEPROM_GAS_H2_TC_OFFSET);		
	if(H2TC != -1)
		notifyParamChanged(c_GAS_H2_PARAM_NAME, String(H2TC));
	Serial.println("config: H2 TC: " + String(H2TC));
	
	double ArCH4TC = -1;
	ArCH4TC = EEPROM.readDouble(EEPROM_GAS_ArCH4_TC_OFFSET);		
	if(ArCH4TC != -1)
		notifyParamChanged(c_GAS_ARCH4_PARAM_NAME, String(ArCH4TC));
	Serial.println("config: ArCH4 TC: " + String(ArCH4TC));
	
	///////////////

	// WiFi SSID
	char wifiSsid[32] = { 0 };
	size_t readSsid = EEPROM.readString(EEPROM_WIFI_SSID_OFFSET, wifiSsid, 31);
	if (readSsid > 0)
		notifyParamChanged(c_WIFI_SSID_PARAM_NAME, String(wifiSsid));
	Serial.println("config: WiFi SSID: " + String(wifiSsid));
	m_wifiSsid = wifiSsid;

	// WiFi PASSWORD
	char wifiPsw[32] = { 0 };
	size_t readPsw = EEPROM.readString(EEPROM_WIFI_PASSWORD_OFFSET, wifiPsw, 31);
	if (readPsw > 0)
		notifyParamChanged(c_WIFI_PASSWORD_PARAM_NAME, String(wifiPsw));
	Serial.println("config: WiFi PSW: " + String(wifiPsw));
	m_wifiPassword = wifiPsw;

	// MQTT SERVER URL
	char mqttUrl[64] = { 0 };
	size_t readUrl = EEPROM.readString(EEPROM_MQTT_SERVER_URL_OFFSET, mqttUrl, 63);
	if (readUrl > 0)
		notifyParamChanged(c_MQTT_SERVER_URL_PARAM_NAME, String(mqttUrl));
	Serial.println("config: MQTT SERVER URL: " + String(mqttUrl));
	m_mqttServerUrl = mqttUrl;

	// FLASH LOG FREQUENCY
	uint16_t flashLogFreq = EEPROM.readUShort(EEPROM_FLASH_LOG_FREQ_OFFSET);
	if (flashLogFreq > 0)
		notifyParamChanged(c_MQTT_SERVER_URL_PARAM_NAME, String(flashLogFreq));
	Serial.println("config: FLASH LOG FREQUENCY: " + String(flashLogFreq));
	m_flashLogFreq = flashLogFreq;

	// WIFI RT LOG FREQUENCY
	uint16_t wifiRtLogFreq = EEPROM.readUShort(EEPROM_WIFI_RT_LOG_FREQ_OFFSET);
	if (wifiRtLogFreq > 0)
		notifyParamChanged(c_MQTT_SERVER_URL_PARAM_NAME, String(wifiRtLogFreq));
	Serial.println("config: WIFI RT LOG FREQUENCY: " + String(wifiRtLogFreq));
	m_wifiRtLogFreq = wifiRtLogFreq;

	/////////////////

	m_loadAllInProgress = false;

	return;		
}

void ConfigurationManager::addParamChangeListener(ParamChangeListener* l)
{
	m_paramChangeListeners.push_back(l);
}

void ConfigurationManager::notifyParamChanged(String param, String value)
{
	for (auto& l : m_paramChangeListeners)
		l->onParamChange(param, value);
}

void ConfigurationManager::onParamChange(String param, String value)
{
	if (param.equals(c_SLOPE_PARAM_NAME))
	{
		Serial.println("EEPROM save SLOPE: " + value);
		EEPROM.writeDouble(EEPROM_GAS_SLOPE_OFFSET, value.toDouble());
	}
	else if (param.equals(c_INTERCEPT_PARAM_NAME))
	{
		Serial.println("EEPROM save INTERCEPT: " + value);
		EEPROM.writeDouble(EEPROM_GAS_INTERCEPT_OFFSET, value.toDouble());
	}
    else if (param.equals(c_SECONDP_PARAM_NAME))
    {
        Serial.println("EEPROM save SECONDP: " + value);
        EEPROM.writeDouble(EEPROM_GAS_SECONDP_OFFSET, value.toDouble());
    }
	else if (param.equals(c_GAS_AIR_PARAM_NAME))
	{
		Serial.println("EEPROM save Air: " + value);
		EEPROM.writeDouble(EEPROM_GAS_AIR_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_GAS_O2_PARAM_NAME))
	{
		Serial.println("EEPROM save O2: " + value);
		EEPROM.writeDouble(EEPROM_GAS_O2_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_GAS_N2_PARAM_NAME))
	{
		Serial.println("EEPROM save N2: " + value);
		EEPROM.writeDouble(EEPROM_GAS_N2_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_GAS_He_PARAM_NAME))
	{
		Serial.println("EEPROM save He: " + value);
		EEPROM.writeDouble(EEPROM_GAS_He_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_GAS_H2_PARAM_NAME))
	{
		Serial.println("EEPROM save H2: " + value);
		EEPROM.writeDouble(EEPROM_GAS_H2_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_GAS_ARCH4_PARAM_NAME))
	{
		Serial.println("EEPROM save ArCH4: " + value);
		EEPROM.writeDouble(EEPROM_GAS_ArCH4_TC_OFFSET, value.toDouble());
	}
	else if (param.equals(c_FLASH_LOG_FREQ_PARAM_NAME))
	{
		Serial.println("EEPROM save c_FLASH_LOG_FREQ_PARAM_NAME: " + value);
		EEPROM.writeUShort(EEPROM_FLASH_LOG_FREQ_OFFSET, value.toInt());

		m_flashLogFreq = value.toInt();
	}
	else if (param.equals(c_WIFI_RT_LOG_FREQ_PARAM_NAME))
	{
		Serial.println("EEPROM save c_WIFI_RT_LOG_FREQ_PARAM_NAME: " + value);
		EEPROM.writeUShort(EEPROM_WIFI_RT_LOG_FREQ_OFFSET, value.toInt());

		m_wifiRtLogFreq = value.toInt();
	}
	else if (param.equals(c_WIFI_SSID_PARAM_NAME))
	{
		size_t ret = EEPROM.writeString(EEPROM_WIFI_SSID_OFFSET, value.c_str());
		Serial.println("EEPROM save c_WIFI_SSID_PARAM_NAME: " + value + " ret:" + String(ret) + " len:" + String(strlen(value.c_str())));
		m_wifiSsid = value;
	}
	else if (param.equals(c_WIFI_PASSWORD_PARAM_NAME))
	{
		size_t ret = EEPROM.writeString(EEPROM_WIFI_PASSWORD_OFFSET, value.c_str());
		Serial.println("EEPROM save c_WIFI_PASSWORD_PARAM_NAME: " + value + " ret:" + String(ret) + " len:" + String(strlen(value.c_str())));
		m_wifiPassword = value;
	}

	if (!EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");

	// This is WebServer changing params so notify others too!
	notifyParamChanged(param, value);
}

void ConfigurationManager::saveSlopeToEEPROM(double slope, bool doCommit)
{
	if(m_loadAllInProgress)
		return;
	
	Serial.println("EEPROM saveSlopeToEEPROM: " + String(slope));
	size_t written = EEPROM.writeDouble(EEPROM_GAS_SLOPE_OFFSET, slope);
	Serial.println("EEPROM written: " + String(written));
	if(doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager:: saveInterceptToEEPROM(double intercept, bool doCommit)
{
	if(m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveInterceptToEEPROM: " + String(intercept));
	size_t written = EEPROM.writeDouble(EEPROM_GAS_INTERCEPT_OFFSET, intercept);
	Serial.println("EEPROM written: " + String(written));
	if(doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager:: saveSecondpToEEPROM(double secondp, bool doCommit)
{
    if(m_loadAllInProgress)
        return;
    Serial.println("EEPROM saveSecondpToEEPROM: " + String(secondp));
    size_t written = EEPROM.writeDouble(EEPROM_GAS_SECONDP_OFFSET, secondp);
    Serial.println("EEPROM written: " + String(written));
    if(doCommit && !EEPROM.commit())
        Serial.println("EEPROM commit ERROR!!!");
}


void ConfigurationManager::saveTimerIntervalToEEPROM(int interval, bool doCommit)
{	
	if(m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveTimerIntervalToEEPROM: " + String(interval));
	size_t written = EEPROM.put(0, interval);
	Serial.println("EEPROM written: " + String(written));
	if(doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}			

void ConfigurationManager::saveWifiSSID(String ssid, bool doCommit)
{
	if (m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveWifiSSID: " + ssid);
	size_t written = EEPROM.writeString(EEPROM_WIFI_SSID_OFFSET, ssid.c_str());
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::saveWifiPassword(String password, bool doCommit)
{
	if (m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveWifiPassword: " + password);
	size_t written = EEPROM.writeString(EEPROM_WIFI_PASSWORD_OFFSET, password.c_str());
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::saveMqttServerUrl(String url, bool doCommit)
{
	if (m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveMqttServerUrl: " + url);
	size_t written = EEPROM.writeString(EEPROM_MQTT_SERVER_URL_OFFSET, url.c_str());
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::saveFlashLogFrequency(uint16_t freq, bool doCommit)
{
	if (m_loadAllInProgress)
		return;
	Serial.println("EEPROM saveFlashLogFrequency: " + String(freq));
	uint16_t written = EEPROM.writeUShort(EEPROM_FLASH_LOG_FREQ_OFFSET, freq);
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::saveWifiRtLogFrequency(uint16_t freq, bool doCommit)
{
	if (m_loadAllInProgress)
		return;

	Serial.println("EEPROM saveWifiRtLogFrequency: " + String(freq));
	size_t written = EEPROM.writeUShort(EEPROM_WIFI_RT_LOG_FREQ_OFFSET, freq);
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::saveDeviceId(String id, bool doCommit)
{
	if (m_loadAllInProgress)
		return;

	Serial.println("EEPROM saveDeviceId: " + id);
	size_t written = EEPROM.writeString(EEPROM_DEVICE_ID_OFFSET, id.c_str());
	Serial.println("EEPROM written: " + String(written));
	if (doCommit && !EEPROM.commit())
		Serial.println("EEPROM commit ERROR!!!");
}

void ConfigurationManager::setupEEPROM()
{
	if (!EEPROM.begin(EEPROM_SIZE))
	{
		Serial.println("EEPROM start failed");
		delay(60000);
		return;
	}

	Serial.println("EEPROM begin!!");
}

void ConfigurationManager::clearEEPROM()
{
	for (size_t i = 0; i < EEPROM_SIZE; ++i)
		EEPROM.writeByte(i, 0xFF);
	EEPROM.commit();
}