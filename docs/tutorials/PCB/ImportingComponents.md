# How to Import Components into Eagle

## ECE 3400, Fall 2017, Cornell University

*By Leah Forrest, Nov. 11th, 2017*

Some of the [class components](SuggestedComponents.md) do not have corresponding parts in the eagle library. A way to get around this is to click on the link which will take you to the Digikey page. Scrolling down on this page and click on 'Download from Ultra Librarian.' This will download a file to your computer. Unzip the file, and save it somewhere like your Desktop or Documents Folder. There is a file in the unziped folder called 'readme.' I have copied it here for easier access as well. 

To import your new library into Eagle:
1. Start Eagle.
2. Select File -> New -> Library from the menu.
3. In the blank library window, select File -> Execute Script from the menu.
5. Browse to your newly exported Eagle Script file (".scr" file extension)
6. After opening the file, the script will populate the new library.
7. Use File -> Save (or Save As..) to save the library to the desired location in Eagle native format.

For additional information, please visit this site:
(http://www.accelerated-designs.com/help/Eagle_import.html)

You may also find this video helpful:
(http://youtu.be/5jGuWY-Yy3Q)

Now when you open up your schematic and press 'add component' you should be able to access this new library after pressing 'Open Library Manager' and adding your new library to your active libraries folder. You can now add the part to your schematic. I sometimes find this quicker and easier than searching through the eagle folders for a component that I can't immediatly find. 

