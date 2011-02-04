/*
 *  KXPS5.cpp
 *  KXPS5
 *
 *  Created by Ujwal Shrestha on 12/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include <Wire.h>
#include <KXPS5.h>

KXPS5::KXPS5(){
	_device_address = 0x19;
	Wire.begin();
}
KXPS5::KXPS5(int addr){
	_device_address = addr;
	Wire.begin();
}

int KXPS5::x(){
	readRegisters(XOUT, _data, 2);
	return (_data[0] << 4)+(_data[1] >> 4);
}
int KXPS5::y(){
	readRegisters(YOUT, _data, 2);
	return (_data[0] << 4)+(_data[1] >> 4);
}
int KXPS5::z(){
	readRegisters(ZOUT, _data, 2);
	return (_data[0] << 4)+(_data[1] >> 4);
}
void KXPS5::xyz(int *x,int *y, int *z){
	readRegisters(XOUT, _data, 6);
	*x = (_data[0] << 4)+(_data[1] >> 4);
	*y = (_data[2] << 4)+(_data[3] >> 4);
	*z = (_data[4] << 4)+(_data[5] >> 4);
}

void KXPS5::writeRegister(byte addr, byte data){
	Wire.beginTransmission(_device_address);
	Wire.send(addr);
	Wire.send(data);
	Wire.endTransmission();
}

void KXPS5::readRegisters(byte baseaddr, int _data[], int size){
	Wire.beginTransmission(_device_address);
	Wire.send(baseaddr);
	Wire.endTransmission();
	Wire.requestFrom(_device_address,size);
	int i=0;
	while (Wire.available()) {
			_data[i]=Wire.receive();
	i++;
	}
	Wire.endTransmission();
}

void KXPS5::resetWrite(){
	Wire.beginTransmission(_device_address);
	Wire.send(0x00);
	Wire.endTransmission();
	writeRegister(Reset_write,Default_Reset_write);
}

boolean KXPS5::isMotionInterrupt(){
	readRegisters(CTRL_REGA, _data, 1);
	return _data[0] & 0x2;
}

boolean KXPS5::isFreeFallInterrupt(){
	readRegisters(CTRL_REGA, _data, 1);
	return _data[0] & 0x1;
}

void KXPS5::clockHold(boolean set){
	readRegisters(CTRL_REGB, _data, 1);
	int flag = set << 7;
	writeRegister(CTRL_REGB, _data[0] | flag);
}
void KXPS5::powerEnable(boolean set){
	readRegisters(CTRL_REGB, _data, 1);
	int flag = set << 6;
	writeRegister(CTRL_REGB, _data[0] | flag);
}
void KXPS5::selfTest(boolean set){
	readRegisters(CTRL_REGB, _data, 1);
	int flag = set << 5;
	writeRegister(CTRL_REGB, _data[0] | flag);
}
void KXPS5::freeFallInterruptEnable(boolean set){
	readRegisters(CTRL_REGB, _data, 1);
	int flag = set << 1;
	writeRegister(CTRL_REGB, _data[0] | flag);
}
void KXPS5::freeFallLatch(boolean set){
	readRegisters(CTRL_REGC, _data, 1);
	int flag = set << 4;
	writeRegister(CTRL_REGC, _data[0] | flag);
}
void KXPS5::motionLatch(boolean set){
	readRegisters(CTRL_REGC, _data, 1);
	int flag = set << 3;
	writeRegister(CTRL_REGC, _data[0] | flag);
}
void KXPS5::setInterruptFrequency(int intspd){
	readRegisters(CTRL_REGC, _data, 1);
	writeRegister(CTRL_REGC, _data[0] | intspd);
}
void KXPS5::motionInterrupt(byte moti){
	writeRegister(MOT_INT, moti);
}
void KXPS5::motionDelay(byte motd){
	writeRegister(MOT_DELAY, motd);
}
void KXPS5::freeFallInterrupt(byte ffi){
	writeRegister(FF_INT, ffi);
}
void KXPS5::freeFallDelay(byte ffd){
	writeRegister(FF_DELAY, ffd);
}
