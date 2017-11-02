# Designing a PCB
## ECE 3400, Fall 2017, Cornell University

*by Leah Forrest and Kirstin Petersen, Oct. 18th, 2017*

## Introduction

This semester, we will give every team the option of making one PCB for their robot. If the PCB doesn't work, you are not obligated to use it on your robot, and it certainly does not need to contain your entire circuit. Be aware, that making a PCB is NOT mandatory - you can do great in the class without it. But if you do want to try it out, there are two methods described below. 

Please keep in mind that any components that are not already in the lab will have to be ordered, and that cost will also count against your final budget. [Here is a list of some frequently used components](SuggestedComponents.md), and [how to import component libraries](ImportingComponents.md).

### Part of the Maker Space?

If you are already part of the Maker Space, trained on the PCB mill, and want to mill out your own PCB, we can provide you with 1- or 2-layer boards. The cost of these will count against your final budget. Please send Kirstin an email with the approximate size of the board you want, and how many layers of copper you need (1 or 2). 

### External Fabrication

We will make two bulk orders from Advanced PCB (Also called 4PCB). The first order will be made on Nov. 6th, the second Nov. 17th. That means you have to hand in your board design by Nov. 3rd @ noon (or Nov. 15th @ noon respectively) to give us time to help you fix any mistakes up front. *For this class we will ONLY accept designs made in Eagle!* 

The boards we will order will be [barebones PCBs](http://www.4pcb.com/pcb-prototype-2-4-layer-boards-specials.html), i.e. two raw copper planes on each side of an FR-4 board. We will try to save money by having every team submit their files to Kirstin first, then we will fit these onto a bigger PCB (maximum size 12x16"), have them externally fabricated, and then cut them out using a Dremel tool afterwards. 

Please keep in mind that the cost of the PCB will count against your final budget. If you want to do this, please send Kirstin a note with the approximate size you expect your PCB to be.

To make a PCB, it is very important that you follow the Barebones PCB requirements, listed here:

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

## Now what?!

1. Decide on what program to use. Altium is available in all the Phillips Labs. Or you can download a student version of [Eagle for free](https://www.autodesk.com/products/eagle/overview).

2. Check out this site we wrote up on [how to design a PCB](HowToDesignaPCB.md).

3. Be sure to check out [Leah's lecture slides](../../lectures/171018-PCBs_byLeahForrest.pdf). Also, here is a great [beginner's tutorial from Sparkfun](https://learn.sparkfun.com/tutorials/using-eagle-board-layout). And Chris has made a nice [tutorial on Eagle](../Eagle/Eagle_Tutorial.md), and an example of [laying out a board end to end](../Eagle/Eagle_Example.md)!

4. Check out the [Class Burn List](burnlist.md) for common mistakes, and please consider adding to it, if you find some of your own!
