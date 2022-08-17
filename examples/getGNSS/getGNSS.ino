 /*!
  * @file  getGNSS.ino
  * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V0.1
  * @date 2022-08-15
  * @url https://github.com/dfrobot/DFRobot_GNSS
  */

#include "DFRobot_GNSS.h"

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

  // gnss.disablePower();      // 失能gnss电源，失能后数据不会刷新
}

void loop()
{
  sTim_t utc = gnss.getUTC();
  sTim_t date = gnss.getDate();
  sLonLat_t lat = gnss.getLat();
  sLonLat_t lon = gnss.getLon();
  double high = gnss.getAlt();
  uint8_t starUserd = gnss.getNumSatUsed();
  double sog = gnss.getSog();
  double cog = gnss.getCog();

  Serial.println("");
  Serial.print(date.year);
  Serial.print("/");
  Serial.print(date.month);
  Serial.print("/");
  Serial.print(date.date);
  Serial.print("/");
  Serial.print(utc.hour);
  Serial.print(":");
  Serial.print(utc.minute);
  Serial.print(":");
  Serial.print(utc.second);
  Serial.println();
  Serial.print((char)lat.latDirection);
  Serial.print(" lat = ");
  Serial.println(lat.latitude, 7);
  Serial.print((char)lon.lonDirection);
  Serial.print(" lon = ");
  Serial.println(lon.lonitude, 7);
  Serial.print("star userd = ");
  Serial.println(starUserd);
  Serial.print("alt high = ");
  Serial.println(high);
  Serial.print("sog =  ");
  Serial.println(sog);
  Serial.print("cog = ");
  Serial.println(cog);
  Serial.print("gnss mode =  ");
  Serial.println(gnss.getGnssMode());
  delay(1000);
}