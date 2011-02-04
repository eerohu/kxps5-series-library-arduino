/*
 *  KXPS5.h
 *  KXPS5
 *
 *  Created by Ujwal Shrestha on 12/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef KXPS5_h
#define KXPS5_h

#include "WProgram.h"

#define ACC_GRAVITY 513

//register definations
#define XOUT 0x00
#define YOUT 0x02
#define ZOUT 0x04
#define Reset_write 0x06
#define FF_INT 0x08
#define FF_DELAY 0x09
#define MOT_INT 0x0A
#define MOT_DELAY 0x0B
#define CTRL_REGC 0x0C
#define CTRL_REGB 0x0D
#define CTRL_REGA 0x0E

//register parameters

#define Default_Reset_write 0xCA  //b11001010
#define IntSpd250 0
#define IntSpd1K 1
#define IntSpd4K 2
#define IntSpd16K 3

#define DEFAULT_ACCELERO_ADDRESS 0x19


class KXPS5 {
public:
	KXPS5();
	KXPS5(int addr);
	void resetWrite();
	boolean isMotionInterrupt();
	boolean isFreeFallInterrupt();
	void clockHold(boolean set);
	void powerEnable(boolean set);
	void selfTest(boolean set);
	void freeFallInterruptEnable(boolean set);
	void freeFallLatch(boolean set);
	void motionLatch(boolean set);
	void setInterruptFrequency(int intspd);
	void motionInterrupt(byte moti); //b01010101
	void motionDelay(byte motd);
	void freeFallInterrupt(byte ffi); //b00001110
	void freeFallDelay(byte ffd);
	int x();
	int y();
	int z();
	void xyz(int *x,int *y,int *z);
private:
	int _device_address;
	int _data[6];
	void writeRegister(byte addr, byte data);
	void readRegisters(byte baseaddr,  int _data[], int size);
};
#endif
