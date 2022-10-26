/*!
 * @file DFRobot_GNSS.h
 * @brief Define the basic structure of the DFRobot_GNSS class, the implementation of the basic methods
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [ZhixinLiu](zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2022-10-26
 * @url https://github.com/DFRobot/DFRobot_GNSS
 */
#ifndef __DFRobot_GNSS_H__
#define __DFRobot_GNSS_H__

#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

/**
 * @struct sTim_t
 * @brief 存放从gps获取的时间日期信息
 */
typedef struct {
  uint16_t year;
  uint8_t month;
  uint8_t date;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
}sTim_t;

/**
 * @struct sLonLat_t
 * @brief 存放从gps获取的经纬度和方向信息
 */
typedef struct {
  uint8_t lonDDD;
  uint8_t lonMM;
  uint32_t lonMMMMM;
  char lonDirection;
  uint8_t latDD;
  uint8_t latMM;
  uint32_t latMMMMM;
  char latDirection;
  double latitude;
  double latitudeDegree;
  double lonitude;
  double lonitudeDegree;
}sLonLat_t;


/**
 * @brief GNSS 星系配置
 */
typedef enum {
  eGPS=1,
  eBeiDou,
  eGPS_BeiDou,
  eGLONASS,
  eGPS_GLONASS,
  eBeiDou_GLONASS,
  eGPS_BeiDou_GLONASS,
}eGnssMode_t;

class DFRobot_GNSS{
public:
  #define GNSS_DEVICE_ADDR  0x20
  #define I2C_YEAR_H 0
  #define I2C_YEAR_L 1
  #define I2C_MONTH 2
  #define I2C_DATE  3
  #define I2C_HOUR  4
  #define I2C_MINUTE 5
  #define I2C_SECOND 6
  #define I2C_LAT_1 7
  #define I2C_LAT_2 8
  #define I2C_LAT_X_24 9
  #define I2C_LAT_X_16 10
  #define I2C_LAT_X_8  11
  #define I2C_LAT_DIS  12
  #define I2C_LON_1 13
  #define I2C_LON_2 14
  #define I2C_LON_X_24 15
  #define I2C_LON_X_16 16
  #define I2C_LON_X_8  17
  #define I2C_LON_DIS  18
  #define I2C_USE_STAR 19
  #define I2C_ALT_H 20
  #define I2C_ALT_L 21
  #define I2C_ALT_X 22

  #define I2C_SOG_H 23
  #define I2C_SOG_L 24
  #define I2C_SOG_X 25
  #define I2C_COG_H 26
  #define I2C_COG_L 27
  #define I2C_COG_X 28

  #define I2C_START_GET 29
  #define I2C_ID 30
  #define I2C_DATA_LEN_H 31
  #define I2C_DATA_LEN_L 32
  #define I2C_ALL_DATA 33

  #define I2C_GNSS_MODE 34
  #define I2C_SLEEP_MODE 35
  #define I2C_RGB_MODE 36

  #define I2C_FLAG  1
  #define UART_FLAG 2
  #define TIME_OUT  500            ///< time out

  #define ENABLE_POWER 0
  #define DISABLE_POWER 1
  
  #define RGB_ON 0x05
  #define RGB_OFF 0x02


  DFRobot_GNSS();
  ~DFRobot_GNSS();
  uint8_t  uartI2CFlag = 0;

/**
 * @fn getUTC
 * @brief 获取utc 标准时间
 * @return sTim_t 类型，表示返回的时分秒
 * @retval sTim_t.hour 时
 * @retval sTim_t.minute 分
 * @retval sTim_t.second 秒
 */
  sTim_t getUTC(void);

/**
 * @fn getDate
 * @brief 获取年月日等日期
 * @return sTim_t 类型，表示返回的年月日
 * @retval sTim_t.year 年
 * @retval sTim_t.month 月
 * @retval sTim_t.month 日
 */
  sTim_t getDate(void);

/**
 * @fn getLat
 * @brief 获取纬度
 * @return sLonLat_t 类型，表示返回的经纬度
 * @retval sLonLat_t.latDD   纬度 度（0-90）
 * @retval sLonLat_t.latMM   纬度 分后0-2位小数
 * @retval sLonLat_t.latMMMMM 纬度 分后2-7位小数
 * @retval sLonLat_t.latitude 包含7位小数的纬度值
 * @retval sLonLat_t.latDirection 纬度的方向
 */
  sLonLat_t getLat(void);

/**
 * @fn getLon
 * @brief 获取经度
 * @return sLonLat_t 类型，表示返回的经度
 * @retval sLonLat_t.lonDDD  经度 度（0-90）
 * @retval sLonLat_t.lonMM   经度 分后0-2位小数
 * @retval sLonLat_t.lonMMMMM 经度 分后2-7位小数
 * @retval sLonLat_t.lonitude 包含7位小数的经度值
 * @retval sLonLat_t.lonDirection 经度的方向
 */
  sLonLat_t getLon(void);

/**
 * @fn getNumSatUsed
 * @brief 获取使用的卫星数
 * @return uint8_t 类型，表示使用的卫星数
 */
  uint8_t getNumSatUsed(void);

/**
 * @fn getAlt
 * @brief 获取大地的高度
 * @return double 类型，表示大地的高度
 */
  double getAlt(void);

/**
 * @fn getSog
 * @brief 获取对地速度
 * @return speed 浮点型数据 （单位 节）
 */
  double getSog(void);

/**
 * @fn getCog
 * @brief 获取对地真航向
 * @return 浮点型数据 （单位 度）
 */
  double getCog(void);

/**
 * @fn setGnss
 * @brief 设置星系
 * @param mode
 * @n   eGPS              使用 gps
 * @n   eBeiDou           使用 beidou
 * @n   eGPS_BeiDou       使用 gps + beidou
 * @n   eGLONASS          使用 glonass
 * @n   eGPS_GLONASS      使用 gps + glonass
 * @n   eBeiDou_GLONASS   使用 beidou +glonass
 * @n   eGPS_BeiDou_GLONASS 使用 gps + beidou + glonass
 * @return NULL
 */
  void setGnss(eGnssMode_t mode);

/**
 * @fn getGnssMode
 * @brief 获取使用的星系模式
 * @return mode
 * @retval 1 使用 gps
 * @retval 2 使用 beidou
 * @retval 3 使用 gps + beidou
 * @retval 4 使用 glonass
 * @retval 5 使用 gps + glonass
 * @retval 6 使用 beidou +glonass
 * @retval 7 使用 gps + beidou + glonass
 */
  uint8_t getGnssMode(void);

/**
 * @fn getAllGnss
 * @brief 获取gnss的数据,回调接收
 * @return null
 */
  void getAllGnss(void);

/**
 * @fn enablePower
 * @brief 使能gnss的电源
 * @return null
 */
void enablePower(void);

/**
 * @fn disablePower
 * @brief 失能gnss的电源
 * @return null
 */
void disablePower(void);

/**
 * @fn setRgbOn
 * @brief 开启 rgb 灯
 * @return null
 */
void setRgbOn(void);

/**
 * @fn setRgbOn
 * @brief 关闭 rgb 灯
 * @return null
 */
void setRgbOff(void);


/**
 * @fn setCallback
 * @brief 设置回调函数类型
 * @param  * call 函数名
 * @return null
 */
  void setCallback(void (*call)(char *, uint8_t));

  void (* callback)(char *data, uint8_t len);
private:
  uint8_t  _addr;
  uint8_t  _M_Flag = 0;

/**
 * @fn getGnssLen
 * @brief 获取gnss的数据长度
 * @return 长度
 */
  uint16_t getGnssLen(void);
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len) = 0;
};

class DFRobot_GNSS_I2C:public DFRobot_GNSS{
public:
  DFRobot_GNSS_I2C(TwoWire *pWire=&Wire, uint8_t addr = 0x75);
  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};

class DFRobot_GNSS_UART:public DFRobot_GNSS{
public:
#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  DFRobot_GNSS_UART(SoftwareSerial *sSerial, uint16_t Baud);
#else
  DFRobot_GNSS_UART(HardwareSerial *hSerial, uint16_t Baud ,uint8_t rxpin = 0, uint8_t txpin = 0);
#endif

  bool begin(void);
protected:
  virtual void writeReg(uint8_t reg, uint8_t *data, uint8_t len);
  virtual int16_t readReg(uint8_t reg, uint8_t *data, uint8_t len);
private:

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266)
  SoftwareSerial *_serial;
#else
  HardwareSerial *_serial;
#endif
  uint32_t _baud;
  uint8_t _rxpin;
  uint8_t _txpin;
};
#endif