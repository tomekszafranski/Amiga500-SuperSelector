# Super Selector for Amiga 500

## Story

If you have real Amiga 500 machine but don't have a wide collection of 3.5" floppies you probably would use Gotek drive. To do that, you need a device called boot selector that allows to boot from Gotek instead of internal drive. This is usually done using small switch mounted somewhere in the case or switchless by pressing and keeping Ctrl-Amiga-Amiga key combination for longer time. Great! Next you may want to have Kickstart ROM selector that allows to have two or more versions of Kickstart e.g. Kickstart 3.1 for better Workbench and features and older Kickstart 1.3 for compatibility. Again, this can be switched by small switch mounted somewhere is the case or switchless by pressing and keeping Ctrl-A-A keys for longer time. The problem is when you want to use both solutions and both switchless, because they will mix and there is no simple way to fix it as there is no possiblity to reprogram/integrate those devices.

## How it works

* If you press Ctrl-A-A briefly or press and release in less then 3 seconds, simple reset is exectuted. 
* If you keep Ctrl-A-A combination pressed beyond 3 seconds you will hear short tick - now you are in boot selector mode. If you release keys now, you will switch boot device. After releasing you will hear one or two beeps meaning internal or external device is set.
* If you keep Ctrl-A-A pressed beyond 6 seconds you will hear another short tick meaning you are in kickstart selection mode. If you release keys now, you will switch kickstarts. You will hear longer beep (kickstart) and one or two beeps for first or second copy of kickstart.
* If you keep keys pressed for more then 9 seconds you will hear another tick meaning switching is over and simple reset will be done when keys are released.

At boot you will hear one or two beeps meaning boot is set to internal or external device.

There is also a jumper on bottom side of PCB called external kickstart selector mode. In internal mode (jumper open) selector direcly sets A18 line of ROM to choose required kickstart version. External mode (jumper closed) is meant to cooperate with external kickstart switcher which switches kickstart after 3 second of holding Ctrl-A-A keys. You connect it as its Reset line.

<img width="1444" height="962" alt="smd" src="https://github.com/user-attachments/assets/107dd6bb-68ff-4730-81b7-1525fd2abe8e" />
<img width="1444" height="1010" alt="tht" src="https://github.com/user-attachments/assets/9b51eb3c-cfcf-43ee-b2a0-1d2f6bb81153" />
<img width="1411" height="511" alt="kick" src="https://github.com/user-attachments/assets/e964858a-7cee-4796-beb5-9cd7326b2015" />

## Installation

You have two PCBs. Installation is easy but think about how to put wires first.

Kickstart ROM:
* remove original Kickstart ROM and mount this PCB with 27C800 or 27C160 EPROM (socket facing north)
* you should be able to close the shield, to make it easier install low profile precision pins
* as miniumum mount pin on A18. A19 can also be installed or set permanently to 0 or 1 if not used

Selector itself (two version available mostly-SMD and THT-only):
* before you install selector in you Amiga it is needed to program ATtiny chip using programmer like USBasp. If you're building THT version you can program controller before putting in in a socket, for SMD version - use provided ICSP pins 
* remove Even CIA chip and mount it in a selector's socket (I recomend using precision sockets for original chips)
* install selector PCB in CIA socket on board with CIA chip facing north
* connect wire from selector's pin KS to A18 on kickstart ROM 
* connect wire from selector's pin RST to pin 21 of Gary chip

<img width="1748" height="1150" alt="smd" src="https://github.com/user-attachments/assets/03f10641-e78b-4f7a-986a-0ed970236c97" />
<img width="1868" height="1300" alt="board" src="https://github.com/user-attachments/assets/623d7f23-73c6-4cdf-b8e0-c566d5559642" />

## Remarks

* Kickstart PCB has A18 and A19 address lines available so it is possible to choose from 4 version of kickstarts however this version of selector allows switching between only 2 versions (not enough pins on ATtiny)
* To prepare 2 kickstarts ROM you need 27C800 that can be programmed by popular TL-866Plus using 27C400/800/160 programmer adapter you can buy online. Rember to swap bytes before burning!


Have fun!

Tomek


> [!NOTE]
> **Disclaimer**: This is my project that I’ve built and it works for me. You can do it as well but remember, you’re responsible for your own doings 
