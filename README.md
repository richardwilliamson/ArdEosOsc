# ArdEosOsc
Arduino library for using OSC with ETC Eos lighting consoles - only currently tested using ESP8266 wifi chip but should be easily extendable to other arduino things

Communicates with console over TCP

Currently not fully librarised however eventually will be able to register different command types - currently can only register EosOscCommand which is the command line (/eos/cmd /eos/newcmd and /eos/key) but intend to expand this to allow more


Mainly developed/tested with my ArdR120 Eos remote (see https://github.com/richardwilliamson/ArdR120) 

Requires My BufferStore library (https://github.com/richardwilliamson/bufferStore)

