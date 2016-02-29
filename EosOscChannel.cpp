#include <EosOscChannel.h>
#include <EosOscManager.h>

//initialize static variables

char EosOscChannel::channelDisplayLine[CHANNEL_DISPLAY_LENGTH+1]; //current command line

EosOscChannel::EosOscChannel()
{
 // manager->registerHandler(this);
}

void EosOscChannel::userChanged()
{
	//don't need to do anything
}

void EosOscChannel::routeOsc(OSCMessage &message)
{
  message.route("/eos/out/active/chan", this->routeCmd);
  message.route("/eos/out/active/chan", EosOscManager::getInstance()->routeScreenNeedsUpdate);

}

//TODO THIS SHOULD BE IN SEPARATE CLASS FOR THE CHANNEL
void EosOscChannel::writeCommandLine(Stream &print)
{
	print.print(EosOscChannel::channelDisplayLine);
}


//ROUTINGS???

void EosOscChannel::routeCmd(OSCMessage &msg, int addrOffSet) {
	/// recieves eos/out/active/chan
	// the info is in the description
	//which is a String
	
	//so get the description
	byte descLength = msg.getDataLength(0);
	
	if (descLength > CHANNEL_DISPLAY_LENGTH +1)
		descLength = CHANNEL_DISPLAY_LENGTH +1;
	
 // Serial.println("route channel");
	msg.getString(0, EosOscChannel::channelDisplayLine, descLength);
	
	//Serial.println(descC);
	
}

