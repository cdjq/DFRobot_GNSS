# DFRobot_GNSS
- [中文版](./README_CN.md)


![效果图](../../resources/images/TEL0157.jpg)

## Product Link(https://www.dfrobot.com)

    SKU：TEL0157

## Table of Contents

* [Summary](#Summary)
* [Installation](#Installation)
* [Methods](#Methods)
* [Compatibility](#Compatibility)
* [History](#History)
* [Credits](#Credits)

## Summary


## Installation
Download the library file before use, paste it into the custom directory for Raspberry Pi, then open the examples folder and run the demo in the folder.

## Methods

```python
  '''!
    @brief 初始化传感器
  '''
  def begin(self):

  '''!
    @brief 获取年月日等日期
    @return struct_utc_tim 类型，表示返回的年月日
  '''
  def get_date(self):

  '''!
    @brief 获取年月日等日期
    @return struct_utc_tim 类型，表示返回的时分秒
  '''
  def get_utc(self):

  '''!
    @brief 获取纬度
    @return struct_lat_lon 类型，表示返回的纬度
  '''
  def get_lat(self):

  '''!
    @brief 获取经度
    @return struct_lat_lon 类型，表示返回的经度
  '''
  def get_lon(self):

  '''!
    @brief 获取使用的卫星数
    @return 表示使用的卫星数
  '''
  def get_num_sta_used(self):

  '''!
    @brief 获取大地的高度
    @return double 类型，表示大地的高度
  '''
  def get_alt(self):

  '''!
    @brief 获取对地真航向
    @return 浮点型数据 （单位 度）
  '''
  def get_cog(self):

  '''!
    @brief 获取对地速度
    @return speed 浮点型数据 （单位 节）
  '''
  def get_sog(self):

  '''!
    @brief 获取使用的星系模式
    @return mode
    @retval 1 使用 gps
    @retval 2 使用 beidou
    @retval 3 使用 gps + beidou
    @retval 4 使用 glonass
    @retval 5 使用 gps + glonass
    @retval 6 使用 beidou +glonass
    @retval 7 使用 gps + beidou + glonass
  '''
  def get_gnss_mode(self):

  '''!
    @brief 设置星系
    @param mode
    @n   GPS              使用 gps
    @n   BeiDou           使用 beidou
    @n   GPS_BeiDou       使用 gps + beidou
    @n   GLONASS          使用 glonass
    @n   GPS_GLONASS      使用 gps + glonass
    @n   BeiDou_GLONASS   使用 beidou +glonass
    @n   GPS_BeiDou_GLONASS 使用 gps + beidou + glonass
  '''
  def set_gnss(self, mode):

  '''!
    @brief 获取gnss的数据
  '''
  def get_all_gnss(self):

  '''!
    @brief 使能gnss 电源
  '''
  def enable_power(self):

  '''!
    @brief 失能gnss 电源,此时gnss不更新数据
  '''
  def disable_power(self):
```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |    √     |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2022/8/17 - V0.0.1 Version

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
