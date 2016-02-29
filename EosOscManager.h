#ifndef EosOscManager_h
#define EosOscManager_h

#include <OSCMessage.h>
#include <ESP8266WiFi.h>

#include <EosOscHandler.h>

#define MAX_HANDLERS 5 //could we do this dynamicly? avoid having lots of un-needed space? Maybe declare when we initialise class?


union MsgLength   //this means I can acces the bytes and the long value for a 4 didgit int (long)
{
	unsigned long value;
	byte bytes[4];
};


class EosOscManager
{

private:
	

/*==== PRIVATE VARIABLES
 * 
 */
	

byte user; //the user number, if 255 then no user
WiFiClient client;
bool screenNeedsUpdate;

EosOscHandler *handlers[MAX_HANDLERS];
byte handlerCount = 0;
	
//EosOscCommand *handler;// = NULL;



public:
	static EosOscManager manager;
	static bool madeManager;
	EosOscManager(); //ideally this would be private but it can't be due to no _Gate thing  //to make it singleton

		
	// initializes the OscManager

	void sendOSCMessage(OSCMessage &theMessage);




	void setUser(byte theUser);
	void setClient(WiFiClient &theClient);
	byte getUser();

	void resetConnection();

	void routeOSC(OSCMessage &theMessage);

	bool getScreenNeedsUpdate();
	void setScreenNeedsUpdate(bool doesIt);

	void checkForIncomingTCP();

	void registerHandler(EosOscHandler * handler);

	static void routeScreenNeedsUpdate(OSCMessage &msg, int addrOffSet);

	static EosOscManager &singleton;
	
	static EosOscManager* getInstance();

  
};




#endif
