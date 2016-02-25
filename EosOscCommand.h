#ifndef EosOscCommand_h
#define EosOscCommand_h

#include "OSCMessage.h"
#include "EosOscHandler.h"
class EosOscManager;

class EosOscCommand : public EosOscHandler
{
private:
    char cmdMessage[20]; //should allocate this dynamically?
    char newCmdMessage[20];
    char keyCmdMessage[20];
    char msgInMessage[20];

    EosOscManager * manager;

    void makeMessages();

public:
    EosOscCommand();
    EosOscCommand(EosOscManager * manager);

    void sendCommand(const char * cmd);
    void sendNewCommand(const char *cmd);
    void sendKey(const char *key);

    virtual void userChanged();
    virtual void routeOsc(OSCMessage &themessage);
    //void routeOsc(OSCMessage &themessage);

   
};

void routeCmd(OSCMessage &msg, int addrOffSet);


#endif
