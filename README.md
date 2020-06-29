# pi_ip_microview
When connecting to a pi via VNC or ssh it sometimes is a pain to find the IP address of the pi if the pi is sitting on a network with DHCP that assigns IP addresses. 
You can scan the ip address using Angry IP Scanner or similar but it would be easier to plug in a Arduino Microview USB and have it automatically display the IP. You can either leave it plugged in or move it to other pis on the network.
The code has references to PiSound which is a sound effects unit that runs on the pi. It has a hostname but sometimes it doesn't register on my network so I plug in the microview if i can't find it. 

It can also run on any pi as I have a few others on my network.

This will show the IP addresses of first 3 network interfaces (updating) of the Raspberry Pi and display it when a Microview USB display is plugged in.

Microview_pisound_ip.ino runs on the microview and waits for serial input to display

pisound_ip.py runs on the raspberry pi. This runs then sleeps for 5 seconds incase the ip address changes, but not too CPU intensive to slow down the pi

To make it start at reboot we create a bash shell script and add it to cron to start at reboot called launcher.sh
after launcher.sh is created we need to make it executable
chmod 755 launcher.sh

To add it to a crontab use the command
sudo crontab -e

and add the line 
@reboot sh /home/pi/launcher.sh

