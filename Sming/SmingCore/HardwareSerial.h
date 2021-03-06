/****
 * Sming Framework Project - Open Source framework for high efficiency native ESP8266 development.
 * Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "../Wiring/WiringFrameworkDependencies.h"
#include "../Wiring/Stream.h"
#include "../SmingCore/Delegate.h"

#define UART_ID_0   0
#define UART_ID_1   1

#define NUMBER_UARTS 2

// Delegate constructor usage: (&YourClass::method, this)
typedef Delegate<void(Stream &source, char arrivedChar, uint16_t availableCharsCount)> StreamDataReceivedDelegate;

typedef struct
{
	StreamDataReceivedDelegate HWSDelegate;
	bool useRxBuff;
} HWSerialMemberData;

class HardwareSerial : public Stream
{
public:
	HardwareSerial(const int uartPort);
	~HardwareSerial() {}

	void begin(const uint32_t baud = 9600);

	int available();
	int read();
	int readMemoryBlock(char* buf, int max_len);
	int peek();
	void flush();
	size_t write(uint8_t oneChar);

	//void printf(const char *fmt, ...);
	void systemDebugOutput(bool enabled);
	void setCallback(StreamDataReceivedDelegate reqCallback, bool useSerialRxBuffer = true);
	void resetCallback();

	static void IRAM_ATTR uart0_rx_intr_handler(void *para);

private:
	int uart;
	static HWSerialMemberData memberData[NUMBER_UARTS];

};

extern HardwareSerial Serial;

#endif /* _HARDWARESERIAL_H_ */
