#!/bin/sh

#(sleep 60; kill -ALRM $$) &

taskset -p 1 $$

while true; do
    true ;
done

