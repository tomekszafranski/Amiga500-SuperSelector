# Amiga 500 Super Selector (boot device/kickstart version)

If you have real Amiga 500 machine but don't have a wide collection of 3.5" floppies you probably would use Gotek drive. To do that, you need to have small device called boot selector that allows you to boot from Gotek instead of internal drive. This is usually done using small switch mounted somewhere in the case or switchless by pressing and keeping Ctrl-Amiga-Amiga key combination for longer time. Great! Next you may want to have Kickstart ROM selector that will allow you to have two or more versions of Kickstart e.g. Kickstart 3.1 for better Workbench and features and older Kickstart 1.3 for compatibility. Again, this can be switched by small switch mounted somewhere is the case or switchless by pressing and keeping Ctrl-A-A keys for longer time. The problem is when you want to use both solutions and both switchless versions, because they will mix and there is no simple way to fix it as there is no possiblity to reprogram/integrate those devices.

## How it works

* If you press Ctrl-A-A briefly or press and release in less then 3 seconds, simple reset is exectuted. 
* If you keep Ctrl-A-A combination pressed beyond 3 seconds you will hear short tick - now you are in boot selector mode. If you release keys now, you will switch boot device. After releasing you will hear one or two beeps meaning internal or external device is set.
* If you keep Ctrl-A-A pressed beyond 6 seconds you will hear another short tick meaning you are in kickstart selection mode. If you release keys now, you will switch kickstarts. You will hear longer beep (kickstart) and one or two beeps for first or second copy of kickstart.
* If you keep keys pressed for more then 9 seconds you will hear another tick meaning switching is over and simple reset will be done when keys are released.

At boot you will hear one or two beeps meaning boot is set to internal or external device.

There is also a jumper on bottom side of PCB called external kickstart selector mode. In internal mode (jumper open) selector direcly sets A18 line of ROM to choose required kickstart version. External mode (jumper closed) is meant to cooperate with external kickstart switcher which switches kickstart after 3 second of holding Ctrl-A-A keys. You connect it as its Reset line.

## Installations

You have two PCBs. Installation is easy but think about how to put wires first.

Kickstart ROM:
* remove your Kickstart ROM and mount this PCB with 27C800 or 27C160 EPROM (socket north).
* you should be able to close the shield, to make it easier you may want to install low profile precision pins
* as miniumum connect wire to A18. A19 can also be connected or set permanently to 0 or 1 if not used

Selector:
* remove Even CIA chip and mount it in a socket
* instal selector with CIA north
* Cconnect wire from K to A18 on kickstart
* connect wire from RST to pin 21 on Gary chip 

## Remarks

* Kickstart PCB has A18 and A19 lines available so is able to choose from 4 version of kickstarts but this version of selector allows only 2 versions (not enough pins on ATtiny)
* To prepare 2 kickstarts ROM you need 27C800 that can be programmed by popular TL-866 using 27C400/800/160 programmer you can buy online. Rember to swap bytes before burning.

Have fun!

Tomek
