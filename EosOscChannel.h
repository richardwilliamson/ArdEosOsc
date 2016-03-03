#ifndef EosOscChannel_h
#define EosOscChannel_h

#include <OSCMessage.h>
#include <EosOscHandler.h>

#define CHANNEL_DISPLAY_LENGTH 16 //two lines of 16

class EosOscChannel : public EosOscHandler
{
private:

public:
	static EosOscChannel singleton;
	static bool madeSingleton;
	EosOscChannel(); //ideally hidden so can only get singleton
	void writeCommandLine(Stream &print);

    virtual void userChanged();
    virtual void routeOsc(OSCMessage &themessage);
    //void routeOsc(OSCMessage &themessage);

	static char channelDisplayLine[CHANNEL_DISPLAY_LENGTH+1]; //current command line
	static void routeCmd(OSCMessage &msg, int addrOffSet);
	
	static EosOscChannel * getInstance();
	/*
	{
		static EosOscChannel singleton;
		return &singleton;
	}*/

   
};





#endif
