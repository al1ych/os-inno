#!/bin/bash
#system_profiler | ./ex2 -a ex2.txt
system_profiler | grep Processor | ./ex2 -a ex2.txt 
#since there is no /proc/cpuinfo that is what i have found for mac os analog
