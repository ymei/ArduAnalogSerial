OSTYPE = $(shell uname)
ARCH   = $(shell uname -m)
############################# OS & ARCH specifics #############################
ifneq ($(OSTYPE), Linux)
  ifeq ($(OSTYPE), Darwin)
    ARDUINO_DIR = $(HOME)/Applications/Arduino.app/Contents/Java
  else ifeq ($(OSTYPE), FreeBSD)
    CC      = clang
    GLLIBS += -lGL -lGLU -lglut
  else ifeq ($(OSTYPE), SunOS)
      CFLAGS := -c -Wall -std=c99 -pedantic
  else
      # Let's assume this is win32
      SHLIB_EXT           := .dll
  endif
else
  ARDUINO_DIR = /opt/arduino
endif
ARDMK_DIR     = ./Makefile
############################ Project Specific #################################
BOARD_TAG        = uno
ARDUINO_LIBS     =
USER_LIB_PATH   := lib
CFLAGS_STD       = -std=gnu11
CXXFLAGS_STD     = -std=gnu++11
CXXFLAGS        += -pedantic -Wall -Wextra
# The port the board is connected to.  Using an '*' tries all the ports and finds the right one.
MONITOR_PORT     = /dev/tty.usbmodem*
MONITOR_BAUDRATE = 9600
include $(ARDMK_DIR)/Arduino.mk
