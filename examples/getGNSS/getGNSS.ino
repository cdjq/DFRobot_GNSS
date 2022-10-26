 /*!
  * @file  getGNSS.ino
  * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V1.0
  * @date 2022-10-26
  * @url https://github.com/dfrobot/DFRobot_GNSS
  */

#include "DFRobot_GNSS.h"

#define I2C_COMMUNICATION  //use I2C for communication, but use the serial port for communication if the line of codes were masked

#ifdef  I2C_COMMUNICATION
  DFRobot_GNSS_I2C gnss(&Wire ,GNSS_DEVICE_ADDR);
#else
/* ---------------------------------------------------------------------------------------------------------------------
 *    board   |             MCU                | Leonardo/Mega2560/M0 |    UNO    | ESP8266 | ESP32 |  microbit  |   m0  |
 *     VCC    |            3.3V/5V             |        VCC           |    VCC    |   VCC   |  VCC  |     X      |  vcc  |
 *     GND    |              GND               |        GND           |    GND    |   GND   |  GND  |     X      |  gnd  |
 *     RX     |              TX                |     Serial1 TX1      |     5     |   5/D6  |  D2   |     X      |  tx1  |
 *     TX     |              RX                |     Serial1 RX1      |     4     |   4/D7  |  D3   |     X      |  rx1  |
 * ----------------------------------------------------------------------------------------------------------------------*/
/* 波特率不可以更改 */
  #if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
    SoftwareSerial mySerial(4, 5);
    DFRobot_GNSS_UART gnss(&mySerial ,9600);
  #elif defined(ARDUINO_SAM_ZERO)
    DFRobot_GNSS_UART gnss(&Serial1 ,9600);
  #else
    DFRobot_GNSS_UART gnss(&Serial1 ,9600 ,/*rx*/D2 ,/*tx*/D3);
  #endif
#endif

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


  // gnss.setRgbOff();
  gnss.setRgbOn();
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
  Serial.println((char)lat.latDirection);
  Serial.println((char)lon.lonDirection);
  
  // Serial.print("lat DDMM.MMMMM = ");
  // Serial.println(lat.latitude, 5);
  // Serial.print(" lon DDDMM.MMMMM = ");
  // Serial.println(lon.lonitude, 5);
  Serial.print("lat degree = ");
  Serial.println(lat.latitudeDegree,6);
  Serial.print("lon degree = ");
  Serial.println(lon.lonitudeDegree,6);

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