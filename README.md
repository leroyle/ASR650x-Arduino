#  leroyle NOTE: any changes to this fork may or may not end up in the offical Heltec release, consumer beware

The changes from the base code that you find here should be limited to the runtimes. This code base should work for 
both Arduino and Platformio.

These are not meant to be installable images, rather the idea is to clone a local version of this fork and copy the libraries and cores
over the top of an existing installation within the applicable directories in your local installation directory.

These can typically be found at:
Arduino:  Linux:  ls ~/.arduino15/packages/CubeCell/hardware/CubeCell/1.0.0
PlatformioL Linux:  ~/.platformio/packages/framework-arduinoasrmicro650x

We will periodically try to pull in any changes that Heltec commits, but no guarantees.

Sept 25 
 - merge in base fork changes

Sept 24 closed issue, added Helium Cubecell AB02 sample
  - #10 Network specfied Adaptive Data Rate changes were not being honored as expected

Sept 19  Closed issues
   - #8 Latest changes broke ADR resetting of DATA RATE

Sept 18  Closed issues
   - #2  LoRaWAN gives user false illusion of transmit success if payload exceeds max for DR
   - #5  LoRaWan: LoRaMac.c - ValidatePayloadLength( ) fails to catch too large payload if fOptsLen != 0
   - #6  Heltec added a set data rate API, need a get data rate api

Sept 14:  Closed issues
   - #4 Radio.SetTxConfig() preamble length param changed from 8 to 14, prevents joins
   - #3 The user should have a way to set the LoRaWAN Data Rate, either dynamically or via app sketch #define
   - #1 LoRaWAN::send() should notify caller of success/failure
 

End of updates from leroyle
# Heltec ASR650x Series Arduino Development Environment

English | [简体中文](#简体中文) &nbsp;&nbsp; [![Build Status](https://travis-ci.org/HelTecAutomation/ASR650x-Arduino.png?branch=master)](https://travis-ci.org/HelTecAutomation/ASR650x-Arduino "Build Status")

This project makes ASR650x (ASR6501, ASR6502) series fully Arduino-Compatible. For [Heltec](https://heltec.org/) [CubeCell](https://heltec.org/proudct_center/lora/cubecell/) series.

Based on the ASR650x series of chips, we have done a lot of migration and development, made it perfectly support **Arduino<sup>®</sup>**, can run the LoRaWAN-Node protocol stably, and can easily connect lithium batteries and solar panels… This is the CubeCell series.

Cube — Means modular design and easy assembly;

Cell —  Is the product positioning, as a unit of the IoT series, working like a cell.

CubeCell series LoRaWAN-Node stack is migration form [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node) V4.4.0, based on "LoRaWAN specification 1.0.2" and "LoRaWAN Regional Parameters v1.0.2rB".

&nbsp;

For more details, please refer to **[CubeCell Documents Page](https://heltec-automation-docs.readthedocs.io/en/latest/cubecell/index.html).**

&nbsp;

## Instructions

The currently supported ASR650x chip product models are:

|   MCU   |                       Relative boards                        |
| :-----: | :----------------------------------------------------------: |
| ASR6501 | [CubeCell-Board](https://heltec.org/project/htcc-ab01/), [CubeCell-Module](https://heltec.org/project/htcc-am01/), [CubeCell-Capsule](https://heltec.org/project/htcc-ac01/) |
| ASR6502 | [CubeCell-Board Plus](https://heltec.org/project/htcc-ab02/), [CubeCell GPS-6502](https://heltec.org/project/htcc-ab02s/), [CubeCell 1/2AA Node](https://heltec.org/project/htcc-ab02a/), [CubeCell-Module Plus](https://heltec.org/project/htcc-am02/), [CubeCell-Capsule Solar Sensor](https://heltec.org/project/htcc-ac02/)  |

&nbsp;

## Installation Instructions

Make sure you have the latest Arduino IDE installed on your computer. If not installed, please refer to this documents:

- [How to Install Git and Arduino](https://heltec-automation-docs.readthedocs.io/en/latest/general/how_to_install_git_and_arduino.html)
- [Establish Serial Connection](https://heltec-automation-docs.readthedocs.io/en/latest/general/establish_serial_connection.html)

&nbsp;

- **Via Arduino IDE Boards Manager (Recommend)**
  - [Install ASR650x-Arduino(CubeCell) via Arduino Boards Manager](https://heltec-automation-docs.readthedocs.io/en/latest/cubecell/quick_start.html)
  
- **Use Git with the development repository**
  + [Instructions for Windows](InstallGuide/windows.md)
  + [Instructions for Mac](InstallGuide/mac.md)
  + [Instructions for Debian/Ubuntu Linux](InstallGuide/debian_ubuntu.md)

&nbsp;

Linux may have serial port can't link problem, please refer to this page:[https://playground.arduino.cc/Linux/All/#Permission](https://playground.arduino.cc/Linux/All/#Permission)

&nbsp;

## Issue/Bug report template
Before reporting an issue, make sure you've searched for similar one that was already created. Also make sure to go through all the issues labelled as [for reference](https://github.com/HelTecAutomation/ASR650x-Arduino/issues).

Also you can talk in our forum: [http://community.heltec.cn/](http://community.heltec.cn/)

&nbsp;

## Contact us
- **Website：[https://heltec.org](https://heltec.org/)**
- **Document Page: [https://docs.heltec.cn](https://docs.heltec.cn)**
- **Forum: [http://community.heltec.cn/](http://community.heltec.cn/)**
- **Twitter: [https://twitter.com/HeltecOrg](https://twitter.com/HeltecOrg)**
- **Face Book: [https://www.facebook.com/heltec.automation.5](https://www.facebook.com/heltec.automation.5)**

&nbsp;
## 简体中文

本项目由成都惠利特自动化科技有限公司开发。

* 本项目旨在为ASR650x系列芯片提供Arduino便利的开发环境与例程库，方便用户完成对ASR650x系列芯片的快速部署与开发。


## 说明
产品型号列表：

|   MCU   |                       Relative boards                        |
| :-----: | :----------------------------------------------------------: |
| ASR6501 | [CubeCell-Board](https://heltec.org/project/htcc-ab01/), [CubeCell-Module](https://heltec.org/project/htcc-am01/), [CubeCell-Cuapsule](https://heltec.org/project/htcc-ac01/) |
| ASR6502 |                         Coming soon                          |



## 安装指南

首先，确保你的电脑上已经安装了最新的Arduino IDE。如果没有安装，请参考这篇文档：[https://docs.heltec.cn/#/zh_CN/user_manual/how_to_install_git_and_arduino](https://docs.heltec.cn/#/zh_CN/user_manual/how_to_install_git_and_arduino)
- **通过Arduino IDE的开发板理器安装**
  - [通过开发板管理器安装ASR650x芯片的Arduino开发环境](https://heltec-automation.readthedocs.io/zh_CN/latest/cubecell/quick_start.html#arduino-board-manager)
- **通过Git从源码进行安装**
  - [Windows操作系统 -- 安装方法](InstallGuide/windows.md)
  - [MacOS操作系统 -- 安装方法](InstallGuide/mac.md)
  - [Linux操作系统(debian,ubuntu) -- 安装方法](InstallGuide/debian_ubuntu.md)

&nbsp;

## 问题讨论 & BUG报告

如果串口不能连接,请参考：[https://playground.arduino.cc/Linux/All/#Permission](https://playground.arduino.cc/Linux/All/#Permission)

在报告BUG之前，请先做详细的测试，如果问题真的存在，您可以通过以下方式报告或者讨论：

- [GitHub问题报告页](https://github.com/HelTecAutomation/ASR650x-Arduino/issues)
- [Heltec论坛 (仅英语交流)](http://community.heltec.cn/)

## 联系我们
- **官网：[https://heltec.org](https://heltec.org/)**
- **Heltec文档页: [https://docs.heltec.cn](https://docs.heltec.cn)**
- **Heltec论坛 (仅英语): [http://community.heltec.cn/](http://community.heltec.cn/)**
- **QQ群: 799093974(中文)**
