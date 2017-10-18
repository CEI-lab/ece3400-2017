# Designing a PCB

*by Leah Forrest and Kirstin Petersen, Oct. 18th, 2017* (In progress...)

## Introduction

This semester, we will give every team the option of making one PCB for their robot. Be aware, that this is NOT mandatory - you can do great in the class without making a PCB. If you do want to try it out, there are two methods:

1) If you are already part of the Maker Space and trained on the PCB mill, and want to mill out your own PCB, we can provide you with 1- and 2-layer boards. The cost of these will count against your final budget. Please send Kirstin an email with the approximate size of the board you want, and how many layers of copper you need (1 or 2). 

2) We will make two bulk orders from Advanced PCB (Also called 4PCB). 
These will be barebones PCBs (http://www.4pcb.com/pcb-prototype-2-4-layer-boards-specials.html), i.e. two raw copper planes on each side of the FR-4 board. We will try to save money by having every team submit their files to Kirstin first, then we will fit these onto a bigger PCB (maximum size 12x16"), and cut them out afterwards. Again, this cost will count against your final budget. If you want to do this, please send Kirstin a note with the approximate size you expect your PCB to be. Also, there are several special requirements that apply to this process. Please read the section on designing for External Fabrication below. 

Finally, please remember that any components that are not already in the lab will have to be ordered, and that cost will also count against your final budget.

## Designing a PCB

Here is the general process for PCB design

1. Test your circuit on a breadboard. 
2. When it works, draw it up on a schematic. Be very sure that you pick the correct components. 
3. Then transfer the schematic to a PCB.
3.a First, draw the outline of your PCB given the dimensions of your robot, mechanical constraints, etc. Mark up if there are any places where there are height restrictions for the components as well
3.b Second, add in your interfaces - i.e. all connectors that needs to sit at the periphery of the board
3.c Add in mounting holes, and be sure they fit screws that are in the lab.
3.d	Route your wires given the constraints of the PCB manufacturer
3.e Consider minimizing the size of your board. Can you place components on both sides of the board for example?
3.f When you are finished, try printing it out on paper (be sure to print it un-scaled). That way you can easily test if everything fits on your robot/components. 
3.g Finally, make a zip file and send it to kirstin@cornell.edu. Use the following naming scheme: Date_TeamX_PCBrevX.zip. I.e. Team 1, sending this today would send 171018_Team1_PCBrev1.zip.
3.h Alternatively, if you are making the PCB on your own in the mill, generate Gerber files and follow your own usual procedures. 

Here are several helpful hints to remember when designing your PCB:

* Add a power-on LED to visually indicate when your board is powered
* Always double- and triple check the footprints of your components, this is the number one cause of failures in PCB design.
* Print out the PCB top and bottom (unscaled) on paper first. That will allow you to test if it fits on your robot, if the components fit the footprints, if the connectors are in the right spot, etc.
* Never make right-angle traces. They do not conduct high frequencies well, they present a different impedance to your signals, and the sharp angle may slowly break the trace when the board experiences many vibrations.
* If your circuit consist of many parts, consider adding in jumpers that can be removed in case you only want to test parts of your circuit. This can help debugging
* Add in extra measurement pads to ease debugging
* Choose components that are easy to solder. It takes some time to get really good at soldering small SMD components, so it you don't need them, don't bother using them. Through-hole resisters, and DIP-chips are handy - they also minimize the number of additional vias that you need to add to route traces on both sides of the PCB. 
* more...?
* The PCBs that we will make in this class will not have silk-screens. However, you can still add text (like your team number/date) as copper traces on the board. We highly recommend doing this, so that we can tell all the boards apart.
* Everyone makes mistakes on their first board, don't worry if yours needs some hacks too. It is part of the learning process!
* We will start a class burn-list. This will include a brief description of all the things that didn't work. In other words, if you learn something, please share it with us and we will add it to the burn-list to help future students!

## Designing for External Fabrication

As previously mentioned we will make two orders from Advanced PCB this semester. The first order will be XXX, the second XXX. That means, you have to hand in your board design by XXX noon (or XXX noon) to give us time to help you fix any mistakes up front. Once all boards are approved by us, we will put them on the same PCB in Eagle, and order them in bulk. Afterwards we will cut them apart usign a dremel. Remember the smaller you make them, the cheaper we can make it. 

It is very important that you follow the Barebones PCB requirements, listed here:

* 2-layer, FR-4, 0.062" thick
* Plated holes
* 6-mil line/gap minimum
* Tin finish over 1-oz Copper
* No internal routing (cutouts) and no scoring, tab rout, or drilled hole board separations.
* Cut to rectangle shape only
* No mask, no legend
* Min size 1.0" X 1.0" (this does not matter, as we are joining together several boards)
* Max size 12" X 16" (192 sq. in.)
* Excellon drill (English Units)
* Minimum hole size 0.015
* Maximum 35 drilled holes per sq. inch
* Don't place holes/pads within 0.1" of the boundary of your PCB
