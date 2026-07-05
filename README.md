# Amiga 500 Super Selector (boot device/kickstart version)

If you have real Amiga 500 machine but don't have a wide collection of 3.5" floppies you probably would use Gotek drive. To do that, you need to have small device called boot selector that allows you to boot from Gotek instead of internal drive. This is usually done using small switch mounted somewhere in the case or switchless by pressing and keeping Ctrl-Amiga-Amiga key combination for longer time. Great! Next you may want to have Kickstart ROM selector that will allow you to have 2 or more versions of Kickstart e.g. Kickstart 3.1 for better Workbench and features and older Kickstart 1.3 for compatibility. Again, this can be switched by small switch mounted somewhere is the case or switchless by pressing and keeping Ctrl-A-A keys for longer time. The problem is when you want to use both and both switchless versions, because they will mix. There is no simply way to fix it as there is no possiblity to reprogram them.

## How it works

* If you press Ctrl-A-A briefly or press and release in less then 3 seconds, simple reset is exectuted. 
* If you keep Ctrl-A-A combination pressed beyond 3 seconds you will hear tick - now you are in boot selector mode. If you release keys now you will switch boot device. After releaseing you will hear one or two beeps meaning internal or external device.
* If you keep Ctrl-A-A pressed beyond 6 seconds you will hear another short tick meaning you are in kickstart selection mode. If you release keys now you switch kickstarts, you will hear longer beep (kickstart) and one or two beeps for first or second copy of kickstart.
* If you keep keys pressed for longer then 9s you will hear another tick meaning switching is over and simple rest will be done when keys are released.

At boot you will hear one or two beeps meaning boot is set to internal or external device.

There is also something called internal or external kickstart selector mode (jumper on bottom side of pcb). In internal mode selector direcly sets A18 line of ROM to choose required kickstart version. External mode is meant to cooperate with external kickstart switcher which is meant to switch kickstart after 3 second of holding Ctrl-A-A keys. You connect it as its reset line.

## Remarks:

* Kickstart pcb is able to choose from 4 kickstarts but this version of selector allows on 2 versions (not enough pins on ATtiny)
* To prepare two-kickstarts ROM you need 27C800 that can be programmed by popular TL-866 using 27C400/800/160 programmer you can buy online.

Have fun!

Tomek
