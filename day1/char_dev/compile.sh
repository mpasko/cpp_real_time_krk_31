#!/bin/bash

make -C /lib/modules/`uname -r`/build modules M=$PWD

