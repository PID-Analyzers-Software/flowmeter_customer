#pragma once

#include <Arduino.h>

#include "ConfigurationManager.h"

extern const uint8_t c_BUTTON_DOWN_PIN;
extern const uint8_t c_BUTTON_S_PIN;
extern const uint8_t c_BUTTON_RIGHT_PIN;
extern const uint8_t c_BUTTON_SINGLE_CLICK_HOLD_DURATION;
extern const uint16_t c_BUTTON_COMBO_CLICK_HOLD_DURATION;

extern const char* c_FLASH_LOG_FREQ_PARAM_NAME;
extern const char* c_WIFI_RT_LOG_FREQ_PARAM_NAME;
extern const char* c_WIFI_SSID_PARAM_NAME;
extern const char* c_WIFI_PASSWORD_PARAM_NAME;
extern const char* c_MQTT_SERVER_URL_PARAM_NAME;

extern const char* c_SLOPE_PARAM_NAME;
extern const char* c_INTERCEPT_PARAM_NAME;
extern const char* c_SECONDP_PARAM_NAME;

extern const char* c_GAS_AIR_PARAM_NAME;
extern const char* c_GAS_O2_PARAM_NAME;
extern const char* c_GAS_N2_PARAM_NAME;
extern const char* c_GAS_He_PARAM_NAME;
extern const char* c_GAS_H2_PARAM_NAME;
extern const char* c_GAS_ARCH4_PARAM_NAME;

extern ConfigurationManager g_configurationManager;

