#!/usr/bin/env python
import sys,os
import time
import serial
import time
import socket
import fcntl
import struct
import glob
baud=9600
sleep_time=5
# 1. determine IP address of all network interfaces
# 2. determine PORT of microview display
# 3. start periodic loop checking the ip and outputting this string to the microview

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', bytes(ifname[:15], 'utf-8')))[20:24])
#print ("IP address is ",ip)
def get_ip():
    ip_list=[]
    interfaces=os.listdir('/sys/class/net/') #lists all network interfaces as a list eg ['lo','etho','wlan0','wlan1']
    for iface in interfaces:
        try:
            ip=get_ip_address(iface)
            ip_list.append(iface+"="+ip)
        except:
            #print("Not IP address" on interface",iface)
            ip=None
    my_ips ='<'+','.join(ip_list)+'>'
    return my_ips
if __name__ == "__main__"  :
    args = sys.argv

while True :
    ips=get_ip() 
    if len(ips)>0:
        ports = glob.glob('/dev/tty[A-Za-z]*')
        for prt in ports:
            if 'USB' in prt:
                uview = prt
                try:
                    ser = serial.Serial(uview,baud)
                    
                    new_ip_s=ips.encode('utf-8')
                    ser.write(new_ip_s)
                except:
                    ser.write("No microview found".encode('utf-8'))
                    #print (str("NO USB DEVICE CONECTED TO " + PORT))
    time.sleep(sleep_time)

