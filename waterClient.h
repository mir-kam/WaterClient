#ifndef _WATER_CLIENT_H
#define _WATER_CLIENT_H

#include "Arduino.h"

class WaterClient
{
public:

	typedef UserId int;
	typedef Pin int;
	typedef RfidId long long int;
	typedef Credit unsigned int;

	struct LoginReply
	{
		enum class Status
		{
			SUCCESS,
			INVALID_ID,
			INVALID_PIN,
			TIMEOUT
		};

		Status status;
		Credit creditAvail; // 0 if non-success status
	};

	WaterClient(HardwareSerial*, unsigned int slaveNum, unsigned int connectTimeoutSec);
	~WaterClient();

	// In every 'loop' call client code should call one of the following methods.
	// If client does not need to log in or log out currently, then noNeedToCommunicateInThisCycle should be repeated in every 'loop' call.
	// Please do not hang in some other operation without calling 'noNeedToCommunicateInThisCycle' for a long time because this will slow
	// down communication with other Arduino slave devices.

	LoginReply loginByUser(UserId, Pin);
	LoginReply loginByRfid(RfidId);
	void logout(Credit consumedCredit);

	void noNeedToCommunicateInThisCycle();

private:

	// ...

};

#endif
