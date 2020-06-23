# pi_ip_microview
This will show the IP address (updating) of the Raspberry Pi and display it when a Microview USB display is plugged in
Microview_pisound_ip.ino runs on the microview and waits for serial input to display
pisound_ip.py runs on the raspberry pi. This runs then sleeps for 5 seconds incase the ip address changes, but not too CPU intensive to slow down the pi

To make it start at reboot we create a bash shell script and add it to cron to start at reboot called launcher.sh
after launcher.sh is created we need to make it executable
chmod 755 launcher.sh

To add it to a crontab use the command
sudo contab -e

and add the line 
@reboot sh /home/pi/launcher.sh

