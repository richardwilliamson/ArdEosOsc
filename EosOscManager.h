#ifndef EosOscManager_h
#define EosOscManager_h

#include "OSCMessage.h"
#include <ESP8266WiFi.h>

#include "EosOscHandler.h"


class EosOscManager
{

private:
/*==== PRIVATE VARIABLES
 * 
 */

byte user; //the user number, if 255 then no user
WiFiClient client;
bool screenNeedsUpdate;

EosOscHandler *handler = NULL;
bool setHandler = false;
//EosOscCommand *handler;// = NULL;

public:

void sendOSCMessage(OSCMessage &theMessage);


EosOscManager(); //makes a blank object
EosOscManager(byte theUser, WiFiClient &client);

void setUser(byte theUser);
byte getUser();

void resetConnection();

void routeOSC(OSCMessage &theMessage);

bool getScreenNeedsUpdate();
void setScreenNeedsUpdate(bool doesIt);

void checkForIncomingTCP();

void registerHandler(EosOscHandler * handler);
//void registerHandler(EosOscCommand *handler);

static void routeScreenNeedsUpdate(OSCMessage &msg, int addrOffSet);



  
};

void routeChannel(OSCMessage &msg, int addrOffSet); 

#endif
