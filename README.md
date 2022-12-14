# HSS Automation
 
 C/C++ code for use on a pre-designed ATMEGA168 board. The program 
 is to be used with sensors that can detect faults in a Yardmaster
 Separator and trigger relays which will shutdown the machine. 

Includes functionality for communicating to other controllers
via SPI protocol. This can either be done live or via storing data
into EEPROM memory then being sent at a later time. A python script can 
be used to proccess and plot the data copied from an Arduino serial monitor. 
This data comes from the Slave SPI program formatted to show the flow and proximity
readings separetly. 
