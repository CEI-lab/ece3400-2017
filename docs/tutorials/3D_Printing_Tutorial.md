# 3D Printing Tutorial
## Uses for 3D printing
3D printing is good for quickly making 3 dimensional objects out of plastic. While slower and less accurate than the laser cutter, the 3D printer allows you to design and make almost any object that fits inside the printing space. The printer works by laying down layers of plastic on top of each other, which makes the part stronger along its vertical axis.
## Preparing Your Files
### 1. Make sure it is physically possible to 3D print your parts
3D printers often have physical limits on the size of the part they can print and the accuracy with which they can print. The limits for the ZYYX+ printer are:
* Maximum dimensions: 265x225x195 mm
* Accuracy: 50&mu;m layer thickness, 11&mu;m XY positioning

Also be aware that 3D printers print in layers. This means that any overhangs may need support material during printing. A general rule is that overhangs  with slopes of 45&deg; or higher can be printed without supports.

### 2. Export your part as a .stl file
Solidworks and Autodesk both allow you to export your designs as .stl files.
## Printing Your Part
### 1. Run the Simplify3D program
This program lets you preview and layout your prints.
### 2. Import the part/parts to be printed
You can import multiple parts at once by ctrl clicking.
### 3. Arrange the parts for optimal speed/material usage
Make sure the parts you are printing have the orientation you want. By double clicking on a part, you can change its displacement and angle in any direction. For prints with multiple parts, try placing all the parts close to each other, as this minimizes the time the printer spends moving between parts.
### 4. Check the process
The process controls how accurately and quickly your part will be printed. You can also adjust the infill percentage, which determines how much plastic is used to make the structure of your part. Higher infill results in a more solid part, but uses up more material and takes longer to print. Process also lets you add automatically generated supports and rafts. The raft is a flat layer of material laid down at the base of the part to allow for a level building surface. The supports will be automatically placed under any overhangs and unsupported strutctures. **When using the raft, it is highly recommended to use supports and place your part some distance above the base of the printer, which will automatically generate supports between the raft and the part.** This is because it is very difficult to separate a part from the raft, but easy to seperate a part from its supports.
### 5. Preview the print
This lets you see what will actually be printed by the printer. Everything is color coded based on how fast the printer can print it. The auto generated supports and raft are also shown here. Once you are satisfied with how everything appears in the preview, you can move on to printing.
### 6. Begin the print
1. Make sure the printer is turned on. There is an on/off switch at the back of the printer.
2. Check to see if the printer has enough filament. If the printer is low on filament, load a new spool into the printer.
3. If you are printing over USB, click begin printing over USB. There may be an error that says: "This machine does not support binary .x3g files." If you get this error, just click begin printing again, and the 3D printer will start working.
4. Once the printer starts printing, do not leave it unattended for extended periods of time.

### 7. Removing your print
After the printer has completed use a scraper to get under the base of the part and separate it from the base of the printer. Be careful not to damage the printer's base, as the scraper is very sharp.

## Common Problems
### Reloading filament
To reload the filament, use the buttons on the face of the 3D printer to select utilities, then select filament reloading. Next, select whether you want to load or unload filament.
#### Loading
Place the spool of filament you want to use on the back of the printer. Be sure that the filament will come off of the spool in the counter clockwise direction. Make sure that all the filament is wrapped around the spool, as any stray loops could cause the printer to jam. Once the spool is in place, feed the filament up the small plastic tube in the back of the printer. It may require some force to initially get the filament through the tube. Feed the filament until it comes out of the other end of the tube, then feed that into the hole in the top of the extruder. Once the filament is in the extruder, press down on the latch on the right side of the extruder and feed the filament in until it reaches the nozzle. Once you can see the filament coming out of the nozzle, you are finished, and can stop the loading process.  
#### Unloading
Pull back the plastic tube that covers the filament as it enters the extruder and grab the filament. Pull on the filament until it comes free of the extruder. After this, pull the filament out of the printer from the plastic tube on the back. Once all the filament is out, you are done.
### Cannot connect with printer
When the Simplify3D software cannot connect to the printer, the error is usually due either the printer being physically disconnected from the computer or the computer communicating through the wrong COM port. For the first case, simply plug the printer into the computer using a USB A to B cable. For the other case, select the machine control panel in the Tools menu in Simplify3D program. From here, you can see the COM port being used to connect to the printer and a communication log between the printer and computer. Select the COM port the printer is connected to and click connect to connect to it. If you do not know which COM port the printer is on, try to connect to all the ports listed. When a connection is successful, there will be several "READ:" and " SENT:" messages in the log, otherwise it will print "failed to connect."
### Aborting print
To abort a print, you can either hit "EMERGENCY STOP" on the machine control panel under Tools in the Simplify3D program or pause the print from the 3D printer itself. To pause the print, press the center button on the printer, then use the down arrow to select pause, then press the center button again to stop the print.
