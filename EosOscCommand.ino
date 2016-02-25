#include "EosOscCommand.h"
#include "EosOscManager.h"

//private - configure all of the messages

void EosOscCommand::makeMessages()
{
  if (manager->getUser() == 255)
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
    sprintf(userNum, "%i", manager->getUser());

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

}
EosOscCommand::EosOscCommand(EosOscManager * theManager)
{
  manager = theManager;
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

  manager->sendOSCMessage(msg);
}
void EosOscCommand::sendNewCommand(const char *cmd)
{
  OSCMessage msg(newCmdMessage);
  if (strlen(cmd) > 0)
    msg.add(cmd);

  manager->sendOSCMessage(msg);
}
void EosOscCommand::sendKey(const char *key)
{

  //    cmd = strcat(cmd, key);
  char buffer[strlen(keyCmdMessage) + strlen(key) + 1];

  strcpy(buffer, keyCmdMessage);
  strcat(buffer, key);

  OSCMessage msg(buffer);

  manager->sendOSCMessage(msg);
}

void EosOscCommand::routeOsc(OSCMessage &message)
{
  message.route(msgInMessage, routeCmd);
  message.route(msgInMessage, manager->routeScreenNeedsUpdate);

}

void routeCmd(OSCMessage &msg, int addrOffset) {
  //Serial.println("route command");
  int length = msg.getDataLength(0);

  char cmdLine[length];
  msg.getString(0, cmdLine, length);

  String str = String(cmdLine);
  if (length > 29)
    str = str.substring(length - 29);

  str.toCharArray(commandInfo, 29);

}

