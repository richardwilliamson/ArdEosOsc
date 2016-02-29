#ifndef EosOscChannel_h
#define EosOscChannel_h

#include <OSCMessage.h>
#include <EosOscHandler.h>

#define CHANNEL_DISPLAY_LENGTH 16 //two lines of 16

class EosOscChannel : public EosOscHandler
{
private:


public:
    EosOscChannel();
	
	void writeCommandLine(Stream &print);

    virtual void userChanged();
    virtual void routeOsc(OSCMessage &themessage);
    //void routeOsc(OSCMessage &themessage);

	static char channelDisplayLine[CHANNEL_DISPLAY_LENGTH+1]; //current command line
	static void routeCmd(OSCMessage &msg, int addrOffSet);

   
};





#endif
