 /*!
  * @file  getAllGNSS.ino
  * @brief read all gnss data
  * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V0.1
  * @date 2022-08-15
  * @url https://github.com/dfrobot/DFRobot_GNSS
  */

#include "DFRobot_GNSS.h"

void callback(char *data ,uint8_t len)
{
  for(uint8_t i = 0; i < len; i++){
    Serial.print((char)data[i]);
  }
}

DFRobot_GNSS_I2C gnss(&Wire ,GNSS_DEVICE_ADDR);
/*
#ifdef ESP_PLATFORM
  // ESP32 user hardware uart
  // RX io16
  // TX io17
  DFRobot_GNSS_UART gnss(&Serial2 ,9600);
#else
  // Arduino user software uart
  // RX io10
  // TX io11
  SoftwareSerial mySerial(10 ,11);
  DFRobot_GNSS_UART gnss(&mySerial ,9600);
#endif
*/
void setup() 
{
  Serial.begin(115200);
  while(!gnss.begin()){
    Serial.println("NO Deivces !");
    delay(1000);
  }

  gnss.enablePower();      // 使能gnss电源

/** 设置使用的星系
 *   eGPS              使用 gps
 *   eBeiDou           使用 beidou
 *   eGPS_BeiDou       使用 gps + beidou
 *   eGLONASS          使用 glonass
 *   eGPS_GLONASS      使用 gps + glonass
 *   eBeiDou_GLONASS   使用 beidou +glonass
 *   eGPS_BeiDou_GLONASS 使用 gps + beidou + glonass
 */
  gnss.setGnss(eGPS_BeiDou_GLONASS);

  gnss.setCallback(callback);
}

void loop()
{
  gnss.getAllGnss();
  delay(3000);
}
