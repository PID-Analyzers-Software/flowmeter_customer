#pragma once

#include <Arduino.h>

class SleepTimer;
class GasManager;
class ParamChangeListener;


class ParamChangeListener
{
public:

	virtual void onParamChange(String param, String value) = 0;

};


class ConfigurationManager : public ParamChangeListener
{
	
const uint16_t EEPROM_SIZE = sizeof(int) + 				// TIMER
							sizeof(double) * (2 + 8)	// GASES
							+ 208;
	
const uint8_t EEPROM_TIMER_OFFSET = 0;
const uint8_t EEPROM_GAS_SLOPE_OFFSET = 4;
const uint8_t EEPROM_GAS_INTERCEPT_OFFSET = 12;
const uint8_t EEPROM_GAS_SECONDP_OFFSET = 20;
const uint8_t EEPROM_GAS_AIR_TC_OFFSET = 28;
const uint8_t EEPROM_GAS_O2_TC_OFFSET = 36;
const uint8_t EEPROM_GAS_N2_TC_OFFSET = 44;
const uint8_t EEPROM_GAS_He_TC_OFFSET = 52;
const uint8_t EEPROM_GAS_H2_TC_OFFSET = 60;
const uint8_t EEPROM_GAS_ArCH4_TC_OFFSET = 68;
const uint8_t EEPROM_DEVICE_ID_OFFSET = 132;			//64 chars
const uint8_t EEPROM_WIFI_SSID_OFFSET = 164;		//32 chars
const uint8_t EEPROM_WIFI_PASSWORD_OFFSET = 196;	//32 chars
const uint8_t EEPROM_MQTT_SERVER_URL_OFFSET = 260;	//64 chars
const uint8_t EEPROM_FLASH_LOG_FREQ_OFFSET = 262;	//uint16_t
const uint8_t EEPROM_WIFI_RT_LOG_FREQ_OFFSET = 270;	//uint16_t


	bool m_loadAllInProgress = false;

	std::vector<ParamChangeListener*> m_paramChangeListeners;

	String m_wifiSsid;
	String m_wifiPassword;
	String m_deviceId;
	String m_wifiRtLogFreq;
	String m_flashLogFreq;
	String m_mqttServerUrl;

public:

	ConfigurationManager();
	
	void init();
	
	void loadFromEEPROM();
		
	void saveTimerIntervalToEEPROM(int interval, bool doCommit = true);
	void saveSlopeToEEPROM(double slope, bool doCommit = true);
	void saveInterceptToEEPROM(double intercept, bool doCommit = true);
    void saveSecondpToEEPROM(double secondp, bool doCommit = true);
    void saveGasThermalConductivity(String gasName, double tc, bool doCommit = true);
	void saveWifiSSID(String ssid, bool doCommit = true);
	void saveWifiPassword(String password, bool doCommit = true);
	void saveMqttServerUrl(String url, bool doCommit = true);
	void saveFlashLogFrequency(uint16_t freq, bool doCommit = true);
	void saveWifiRtLogFrequency(uint16_t freq, bool doCommit = true);
	void saveDeviceId(String id, bool doCommit = true);

	// Getters
	String getWifiSsid() const { return m_wifiSsid; }
	String getWifiPassword() const { return m_wifiPassword; }
	String getDeviceId() const { return m_deviceId; }
	String getWifiRtLogFreq() const { return m_wifiRtLogFreq; }
	String getFlashLogFreq() const { return m_flashLogFreq; }
	String getMqttServerUrl() const { return m_mqttServerUrl; }


	void setupEEPROM();
	
	void clearEEPROM();

	void onParamChange(String param, String value);


	void addParamChangeListener(ParamChangeListener* l);
	void notifyParamChanged(String param, String value);

};
