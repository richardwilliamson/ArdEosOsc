#ifndef EosOscHandler_h
#define EosOscHandler_h

#include "OSCMessage.h"

class EosOscHandler
{
  public:

  virtual void routeOsc(OSCMessage &themessage) = 0 ;
  virtual void userChanged() = 0;
  
};

#endif
