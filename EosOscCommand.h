#ifndef EosOscCommand_h
#define EosOscCommand_h

#include <OSCMessage.h>
#include <EosOscHandler.h>

#define COMMAND_LINE_LENGTH 32 //two lines of 16

class EosOscCommand : public EosOscHandler
{
private:
    char cmdMessage[20]; //should allocate this dynamically?
    char newCmdMessage[20];
    char keyCmdMessage[20];
    char msgInMessage[20];
	
    void makeMessages();


public:
    EosOscCommand();

    void sendCommand(const char * cmd);
    void sendNewCommand(const char *cmd);
    void sendKey(const char *key);
	
	void writeCommandLine(Stream &print);

    virtual void userChanged();
    virtual void routeOsc(OSCMessage &themessage);
    //void routeOsc(OSCMessage &themessage);

	static char currentCmdLine[COMMAND_LINE_LENGTH+1]; //current command line
	static void routeCmd(OSCMessage &msg, int addrOffSet);

   
};





#endif
