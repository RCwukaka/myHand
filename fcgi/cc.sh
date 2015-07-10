#!/bin/sh
arm-linux-g++ main.cpp -o smartHome.fcgi -I/usr/local/fcgi/include -L../lib_arm -lfcgi -lcgi
