#!/usr/bin/env python
import sys
import time
import serial
import time
import socket
import fcntl
import struct
import glob
baud=9600
sleep_time=5
# 1. determine IP address
# 2. determine PORT of microview

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', bytes(ifname[:15], 'utf-8')))[20:24])
#print ("IP address is ",ip)
def get_ip():
    ip=0
    try:
        ip=get_ip_address('eth0')
    except:
        #print("Not eth0 IP address")
        ip=0
    
    try:
        ip=get_ip_address('wlan0')
    except:
        #print("Not wlan0 IP address")
        ip=0
    
if __name__ == "__main__"  :
    args = sys.argv

while True :
    new_ip=get_ip()
    if new_ip !=0:
        ports = glob.glob('/dev/tty[A-Za-z]*')
        for prt in ports:
            if 'USB' in prt:
                uview = prt
                try:
                    ser = serial.Serial(uview,baud)
                    new_ip_s=new_ip.encode('utf-8')
                    ser.write(new_ip_s)
                except:
                    ser.write("No microview found".encode('utf-8'))
                    #print (str("NO USB DEVICE CONECTED TO " + PORT))
    time.sleep(sleep_time)
