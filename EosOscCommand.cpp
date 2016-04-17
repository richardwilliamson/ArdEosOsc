#include <EosOscCommand.h>
#include <EosOscManager.h>

//initialize static variables

char EosOscCommand::currentCmdLine[COMMAND_LINE_LENGTH+1]; //current command line


//private - configure all of the messages

void EosOscCommand::makeMessages()
{
  if (EosOscManager::getInstance()->getUser() == 255 || EosOscManager::getInstance()->getUser() ==0)
  { //no user
    strcpy(cmdMessage, "/eos/");
    strcpy(newCmdMessage, cmdMessage);
    strcpy(keyCmdMessage, cmdMessage);
    strcpy(msgInMessage, cmdMessage);
    strcat(msgInMessage, "out/cmd");
  } else
  { //use usernumber
    //strcpy(preMessage, );
    char userNum[3];
    sprintf(userNum, "%i", EosOscManager::getInstance()->getUser());

    strcpy(cmdMessage, "/eos/user/");
    strcat(cmdMessage, userNum);
    strcat(cmdMessage, "/");

    strcpy(newCmdMessage, cmdMessage);

    strcpy(keyCmdMessage, cmdMessage);

    strcpy(msgInMessage, "/eos/out/user/");
    strcat(msgInMessage, userNum);
  }

  strcat(newCmdMessage, "newcmd");
  strcat(cmdMessage, "cmd");
  strcat(keyCmdMessage, "key/");

}

EosOscCommand::EosOscCommand()
{
 // manager->registerHandler(this);
  makeMessages();
}

void EosOscCommand::userChanged()
{
  makeMessages();
}

void EosOscCommand::sendCommand(const char * cmd)
{
  
  OSCMessage msg(cmdMessage);
  msg.add(cmd);
  
  EosOscManager::getInstance()->sendOSCMessage(msg);
}
void EosOscCommand::sendNewCommand(const char *cmd)
{
  OSCMessage msg(newCmdMessage);
  if (strlen(cmd) > 0)
    msg.add(cmd);

  EosOscManager::getInstance()->sendOSCMessage(msg);
}
void EosOscCommand::sendKey(const char *key)
{

  //    cmd = strcat(cmd, key);
  char buffer[strlen(keyCmdMessage) + strlen(key) + 1];

  strcpy(buffer, keyCmdMessage);
  strcat(buffer, key);

  OSCMessage msg(buffer);

  EosOscManager::getInstance()->sendOSCMessage(msg);
}

void EosOscCommand::routeOsc(OSCMessage &message)
{
  message.route(msgInMessage, this->routeCmd);
  message.route(msgInMessage, EosOscManager::getInstance()->routeScreenNeedsUpdate);

}

void EosOscCommand::writeCommandLine(Stream &print)
{
	print.print(EosOscCommand::currentCmdLine);
}

void EosOscCommand::routeCmd(OSCMessage &msg, int addrOffset) {
  //Serial.println("route command");
  int length = msg.getDataLength(0);

  char cmdLine[length];
  msg.getString(0, cmdLine, length);

  if (length > COMMAND_LINE_LENGTH +1) //extra byte for the /0
  {
	  memcpy(EosOscCommand::currentCmdLine, cmdLine +(length - COMMAND_LINE_LENGTH+1), COMMAND_LINE_LENGTH+1);
	  
  } else
  {
	  strcpy(EosOscCommand::currentCmdLine, cmdLine);
  }
}

