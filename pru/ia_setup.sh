#!/bin/bash

export TARGET=imageAcquisition.pru1
echo TARGET = $TARGET

# Configure the PRU pins on the BeagleBone Black
machine=$(awk '{print $NF}' /proc/device-tree/model)

# Configure DATA[7:0] and DCLK 
config-pin P8_45 pruin
config-pin P8_46 pruin
config-pin P8_43 pruin
config-pin P8_44 pruin
config-pin P8_41 pruin
config-pin P8_42 pruin
config-pin P8_39 pruin
config-pin P8_40 pruin
config-pin P8_29 pruin


# Configure pin for SHUTTER
config-pin P8_30 pruout
