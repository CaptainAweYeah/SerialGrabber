Welcome to ACSGrab!

IMPORTANT:
This application only recognizes serial strings with the filename
contained in <> brackets. the CCW(Connected components workbench)
program provided does exactly that
and the filenames are formatted like this:
<test1YYYY_MM_DD>

Because this program is only intended for CCW the buffer size is
limited to 82 bytes.

adding the characters EOF (as provided) will signal the end of a
test and send the file to wait for a usb to be plugged in and recieve
the files.
This program is also solely built for linux, specifically a raspberry pi.
/*----------------------------------------------------------------*/
Installation instructions!

Please place ALL OF THE FILES PROVIDED(
grabber.h
serial_mount.c
buffer.c
usb_read.c
main.c
tools.c
install.c
ACSInstall)
into a folder called "grabber" directly onto your desktop (the path
will be /home/pi/desktop/grabber).

Afterwards double click on the executable provided (ACSInstall) and
ensure that it is compiled correctly. (if not compiled correctly,
follow the COMPILATION instructions at the end of this file)

installing will place 2 separate executable files into a new path:
"/home/pi/grabber" as well as a directory inside called usb_staging

/*----------------------------------------------------------------*/
When all of the files are in the correct place, open your terminal
and enter these command lines below (copy and paste if you'd like!):
1 (confirm you are in the correct directory)
cd grabber

2 (Grant exec permission on the file)
sudo chmod +x ACSGrab
sudo chmod +x ACSRead

3 (Return home)
cd ~

4 (open crontab)
sudo crontab -e
/*----------------------------------------------------------------*/
CRONTAB
crontab is a program pre-installed on linux that allows you to run
programs at specified times (since we are running on startup, this
is perfect for us)

1 enter the number suggested to open nano and create a new crontab

2 scroll to the bottom with the arrow keys to a line with a '#'
(pound sign)

3 Type this:
@reboot /home/pi/grabber/ACSGrab
@reboot /home/pi/grabber/ACSRead

4 Press ctrl-o to save and then ctrl-x to exit crontab

This should take you back to the terminal, the line above your
command line should say "installing new crontab" which lets you know
that you were successful.

Your final step will be to type in this command:
sudo reboot

and you're done!

/*----------------------------------------------------------------*/
COMPILATION
PLEASE ENSURE THAT ALL FILES LISTED ABOVE ARE PRESENT AND IN THE
CORRECT LOCATION
/*----------------------------------------------------------------*/
The simplest way to go about this procedure is to open main.c (in the
directory (/home/pi/Desktop/grabber) in geany. right click on main.c 
and select geany then follow these instructions

1 Select the terminal tab from the bottom window

2 compile with gcc using this command:
gcc -o ACSInstall grabber.h install.c tools.c

if no errors show, you are done! continue with the rest of the
setup above.

STILL SEEING ERRORS?
email me!
willard@willardsoftware.com
