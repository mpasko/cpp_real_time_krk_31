#!/bin/bash

make -C /lib/modules/`uname -r`/build modules M=$PWD

sudo rmmod char_test.ko
sudo insmod char_test.ko
sudo chmod 777 /dev/char_test
