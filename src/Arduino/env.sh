#!/bin/sh

#
# Normally there's no need to source this file.
# Variables are defined in makefiles
#

export ARDMK_DIR=./Makefile
case "$(uname -s)" in 
    "Darwin")
        export ARDUINO_DIR=$HOME/Applications/Arduino.app/Contents/Java
        ;;
    "Linux")
        export ARDUINO_DIR=/opt/arduino
        ;;
    *)
        echo 'other OS'
        ;;
esac
