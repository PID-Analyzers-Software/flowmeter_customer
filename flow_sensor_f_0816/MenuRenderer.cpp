#include "inc/MenuRenderer.h"

#include "inc/Menu.h"
#include "inc/SleepTimer.h"
#include "inc/DataSource.h"
#include <Adafruit_ADS1015.h>
#include "SSD1306.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SimpleKalmanFilter.h>


/////////////////////////

///////////
//// SSD1327
///////////

SSD1327GasMenuRenderer::SSD1327GasMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2) : SSD1327MenuRenderer(u8g2)
{

}



void SSD1327GasMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(20, 30, menu->getParentName().c_str());
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(50, 80, menu->getName().c_str());
  m_display->sendBuffer();
}

SSD1327RunMenuRenderer::SSD1327RunMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, DataSource* dataSource, GasManager* gasManager) : SSD1327MenuRenderer(u8g2),
  m_dataSource(dataSource),
  m_gasManager(gasManager)
{


}

SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.1);

void SSD1327RunMenuRenderer::render(Menu* menu)
{
  const float multiplier = 0.125F; //GAIN 1

  double sensor_val = m_dataSource->getDoubleValue();
  //Serial.print("ADC A0: ");
  //Serial.println(ads_val);
  //Serial.println("15: " + String(digitalRead(15)));

  Gas& selectedGas = m_gasManager->getSelectedGas();

  m_display->clearBuffer();
  m_display->setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  //m_display->drawStr(0, 30, String(String(m_dataSource->getRawMiliVolts_battery()) + "mV").c_str());
  //m_display->drawStr(0, 30, String("2nd order").c_str());
  m_display->drawStr(100, 30, String(String(m_dataSource->getRawMiliVolts_battery() / 34.00, 0) + "%").c_str());
  m_display->setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  m_display->drawStr(50, 40, String(selectedGas.getName()).c_str());
  m_display->drawLine(5, 45, 123, 45);
  m_display->setFont(u8g2_font_ncenB24_tr); // choose a suitable font
  if (sensor_val > 550) {
    m_display->drawStr(40, 80, "xxx");
  } else {
    m_display->drawStr(40, 80, String(simpleKalmanFilter.updateEstimate(sensor_val), 1).c_str());
  }
  m_display->drawLine(5, 90, 123, 90);
  m_display->setFont(u8g2_font_ncenB12_tr); // choose a suitable font
  m_display->drawStr(40, 110, " sccm");
 // m_display->drawStr(60, 110, String(String(m_dataSource->getRawMiliVolts()) + "mV").c_str());
  m_display->sendBuffer();
}

///////////////////////////

SSD1327SleepTimerMenuRenderer::SSD1327SleepTimerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, SleepTimer* sleepTimer) : SSD1327MenuRenderer(u8g2),
  m_sleepTimer(sleepTimer)
{






}

void SSD1327SleepTimerMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(10, 0, "TIMER SLEEP");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 30, menu->getName().c_str());
  m_display->sendBuffer();
}

///////////////////////////////

SSD1327FlashLoggerMenuRenderer::SSD1327FlashLoggerMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, DataLogger* dataLogger) : SSD1327MenuRenderer(u8g2),
  m_dataLogger(dataLogger)
{


}

void SSD1327FlashLoggerMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->setFont(u8g2_font_ncenB10_tr); // choose a suitable font
  //m_display->drawStr(10, 20, "DATA LOGGER");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(0, 30, menu->getName().c_str());
  m_display->setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  m_display->drawStr(40, 80, m_dataLogger->isFlashStoreSessionRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

///////////////////////////////

SSD1327WiFiDumpMenuRenderer::SSD1327WiFiDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, DataLogger* dataLogger) : SSD1327MenuRenderer(u8g2),
  m_dataLogger(dataLogger)
{


}

void SSD1327WiFiDumpMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(10, 0, "WIFI DATA DUMP");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 60, menu->getName().c_str());
  m_display->drawStr(10, 80, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

SSD1327WiFiRealTimeDumpMenuRenderer::SSD1327WiFiRealTimeDumpMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, DataLogger* dataLogger) : SSD1327MenuRenderer(u8g2),
  m_dataLogger(dataLogger)
{


}

void SSD1327WiFiRealTimeDumpMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->drawStr(10, 0, "WIFI REAL-TIME DUMP");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 60, menu->getName().c_str());
  m_display->drawStr(10, 80, m_dataLogger->isWiFiDumpRunning() ? "Started" : "Idle");
  m_display->sendBuffer();


}

SSD1327NTPSyncMenuRenderer::SSD1327NTPSyncMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2, TimeSync* timeSync) : SSD1327MenuRenderer(u8g2),
  m_timeSync(timeSync)
{

}

void SSD1327NTPSyncMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->setFont(u8g2_font_ncenB12_tr); // choose a suitable font
  //m_display->drawStr(10, 10, "NTP Sync");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 30, menu->getName().c_str());
  m_display->setFont(u8g2_font_ncenB14_tr); // choose a suitable font
  m_display->drawStr(40, 80, m_timeSync->isNTCSyncRunning() == true ? "In Progress!" : "Idle");
  m_display->sendBuffer();
}


SSD1327InfoMenuRenderer::SSD1327InfoMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2) : SSD1327MenuRenderer(u8g2)
{

}

void SSD1327InfoMenuRenderer::render(Menu* menu)
{
  m_display->clearBuffer();
  m_display->setFont(u8g2_font_ncenB12_tr); // choose a suitable font
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 30, menu->getName().c_str());
  m_display->setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  m_display->drawStr(5, 60, "S/W ver: 053121_1");
  m_display->drawStr(5, 80, "Calibration date:");
  m_display->drawStr(5, 90, "05/31/2021");

  m_display->sendBuffer();
}




SSD1327ShowTimeMenuRenderer::SSD1327ShowTimeMenuRenderer(U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI* u8g2) : SSD1327MenuRenderer(u8g2)
{

}

void SSD1327ShowTimeMenuRenderer::render(Menu* menu)
{
  int64_t startMicros = esp_timer_get_time();

  m_display->clearBuffer();

  struct tm timeinfo;
  getLocalTime(&timeinfo, 10);

  int64_t passed = esp_timer_get_time() - startMicros;

  Serial.println("render time: " + String((uint32_t)(passed / 1000)));

  char dateString[30] = { 0 };
  char timeString[30] = { 0 };
  strftime(dateString, 30, "%b %d %y", &timeinfo);
  strftime(timeString, 30, "%H:%M:%S", &timeinfo);

  m_display->drawStr(10, 0, "Current DateTime");
  m_display->drawLine(5, 40, 123, 40);
  m_display->drawStr(10, 60, String(dateString).c_str());
  m_display->drawStr(10, 80, String(timeString).c_str());
  m_display->sendBuffer();



}
