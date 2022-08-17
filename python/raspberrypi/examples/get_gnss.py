# -*- coding: utf-8 -*
'''!
  @file get_gnss.py
  @brief Reading gnss data
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license    The MIT License (MIT)
  @author     [ZhixinLiu](zhixin.liu@dfrobot.com)
  @version    V0.1
  @date       2022-8-15
  @url https://github.com/DFRobot/DFRobot_GNSS
'''
from __future__ import print_function
import sys
import os
sys.path.append("../")
import time
import RPi.GPIO as GPIO
from DFRobot_GNSS import *

'''
  选择使用i2c 或者 串口
  I2C_MODE
  UART_MODE
'''
ctype = I2C_MODE

if ctype == I2C_MODE:
  I2C_1 = 0x01
  gnss = DFRobot_GNSS_I2C (I2C_1, GNSS_DEVICE_ADDR)
elif ctype == UART_MODE:
  gnss = DFRobot_GNSS_UART(9600)

utc = struct_utc_tim()
lat_lon = struct_lat_lon()

def setup():
  while (gnss.begin() == False):
    print("Sensor initialize failed!!")
    time.sleep(1)
  gnss.enable_power()        # 使能gnss 电源
  '''
    GPS              使用 gps
    BeiDou           使用 beidou
    GPS_BeiDou       使用 gps + beidou
    GLONASS          使用 glonass
    GPS_GLONASS      使用 gps + glonass
    BeiDou_GLONASS   使用 beidou +glonass
    GPS_BeiDou_GLONASS 使用 gps + beidou + glonass
  '''
  gnss.set_gnss(GPS_BeiDou_GLONASS)
  #gnss.disable_power()        # 失能gnss 电源,此时gnss数据不更新

def loop():
  utc = gnss.get_date()
  utc = gnss.get_utc()
  lat_lon = gnss.get_lat()
  lat_lon = gnss.get_lon()
  alt = gnss.get_alt()
  cog = gnss.get_cog()
  sog = gnss.get_sog()
  num = gnss.get_num_sta_used()
  star = gnss.get_gnss_mode()
  print(str(utc.year) + "/" + str(utc.month) + "/" + str(utc.date) + "/" + str(utc.hour) + ":" + str(utc.minute) + ":" + str(utc.second))
  print("star used number = " + str(num))
  print("used star mode = " + str(star))
  print("latutide = " + str(lat_lon.latitude) + "   direction = " + lat_lon.lat_direction)
  print("lonutide = " + str(lat_lon.lonitude) + "   direction = " + lat_lon.lon_direction)
  print("alt = " + str(alt))
  print("sog = " + str(sog) + " N")
  print("cog = " + str(cog) + " T")
  print("")
  time.sleep(1)

if __name__ == "__main__":
  setup()
  while True:
    loop()