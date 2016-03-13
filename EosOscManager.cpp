#include <EosOscManager.h>
#include <BufferStore.h>

//define static vars

EosOscManager EosOscManager::manager;
bool EosOscManager::madeManager = false;

EosOscManager::EosOscManager() 
{
    //setUser(255);
}

void EosOscManager::setClient(WiFiClient &theClient)
{
	client = theClient;
}

void EosOscManager::registerHandler(EosOscHandler *theHandler)
//void EosOscManager::registerHandler(EosOscCommand * theHandler)
{
	if (handlerCount>= MAX_HANDLERS)
		return; //should throw an error or return -1?
	
	handlers[handlerCount] = theHandler;
	handlerCount++;
}


void EosOscManager::setUser(byte theUser)
{
    user=theUser;
    if (handlerCount>0)
	{
		for (byte i=0; i<handlerCount; i++)
			handlers[i]->userChanged();

	}
	
}

byte EosOscManager::getUser()
{
    return user; 
}



//route the incoming OSC
void EosOscManager::routeOSC(OSCMessage &theMessage)
{
  //lcd.clear();
  if (!theMessage.hasError()) //if the OSC is OK then act on it
  {
	
    if (handlerCount>0)
    {
		for (byte i=0; i<handlerCount; i++)
			handlers[i]->routeOsc(theMessage);
    }


  } else
  {
    Serial.println("error");
  }

}


void EosOscManager::sendOSCMessage(OSCMessage &message)
{

  if (client.connected())
  {
    //send out via TCP
    BufferStore(buf); //declare a buffer to send to
  
        //MsgLength mLen;
  
    message.send(buf); //send to the buffer
    buf.sendOut(client); //now transmit it en masse
  }

  message.empty(); // free space occupied by message

}




bool EosOscManager::getScreenNeedsUpdate()
{
  return screenNeedsUpdate;
}

void EosOscManager::setScreenNeedsUpdate(bool doesIt)
{
  screenNeedsUpdate = doesIt;
}



void EosOscManager::checkForIncomingTCP()
{
  if (!client.connected())
  {
    Serial.print("not connected");
	delay(500);
    return;
  }
    
  int rdS = 0;

  // read in the OSC From the client if we have it
  if ((rdS = client.available()) > 12) //must be more than 12 bytes available or we can't do anything
  {
    //Serial.println("Got stuff");
    MsgLength len;  //a struct for the length
    len.value = 0; //preset it to 0

    byte f4 = 4; //first 4 bytes are the size, then we have the actual message..
        
    //get the size
    while (f4--)
    {
      len.bytes[f4] = client.read();
      rdS--;
    }

    OSCMessage(rMsg); //initialize a new OSC message to put this in

    if (client.available() < len.value)
    {
      client.flush();
      return; //not enough data - should we wait??
    }

    while (len.value--)
      //str +=(char)client.read();
      rMsg.fill(client.read());

    // Serial.println(wheelC);


    if (!rMsg.hasError()) 
    { //is valid OSC
      //send out via SLIP
      delay(10); //this appears necessary!!
		yield();
		this->routeOSC(rMsg);
      //delay(1);
    } else
    {
      Serial.print("error");
    }

    rMsg.empty();
	  
	yield();

  } else {
    client.flush();//*/
  }

}

void EosOscManager::resetConnection()
{
    if (!client.connected())
      return; //don't try and connect if we aren't connected!
    //first reset the connection
    OSCMessage msg("/eos/reset");
    sendOSCMessage(msg);
    msg.empty();

    //now register which user we are
    if (user!=255)
    {
      //return; //don't need to register if we don't have a user
      char cmd[14];

      strcpy(cmd, "/eos/user/");
      char userNum[3];
      sprintf(userNum, "%i", user);
      strcat(cmd, userNum);
      OSCMessage msg2(cmd);
      this->sendOSCMessage(msg2); 
    }
    yield();
    

    //TODO should we transmit the current user so we remember what we are listening for?
}


//call this each time we have any OSC that might affect the output
void EosOscManager::routeScreenNeedsUpdate(OSCMessage &msg, int addrOffSet)
{
  //todo need to implement a singleton object for oscManager
    EosOscManager::getInstance()->setScreenNeedsUpdate(true);
}



EosOscManager* EosOscManager::getInstance() {
	if (!madeManager) EosOscManager(manager);
	madeManager = true;
	return &manager;
	//return NULL;
};





