#!/bin/bash
import os
import sys
import time

serialport = sys.argv[1]
print("OPENING PORT " + serialport)
with open(serialport, 'w') as port:

    loopcount = 0
    while(True):
        time.sleep(0.03)
        loopcount = loopcount + 1

        led_num = loopcount%9

        # if led_num == 0:
        #     command = "AT*LED=0,0,0,0\n"
        #     print(command)
        #     port.write(command)
        #     time.sleep(0.2)

        r = ( ((loopcount*7)/2) % 256) / 8
        g = ( ((loopcount*5)/2) % 256) / 8
        b = ( ((loopcount*3)/2) % 256) / 8

        command = "AT*LED=%d,%d,%d,%d\n" % (led_num, r,g,b)
        print(command)
        port.write(command)





