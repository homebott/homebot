#############################################################################
#
# Makefile for librf24 examples on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/02/07 (version 1.0)
#
# Description:
# ------------
# use make all and make install to install the examples
# You can change the install directory by editing the prefix line
#
prefix := /usr/local

# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
#CCFLAGS=
# define all programs
#PROGRAMS = scanner pingtest gettingstarted
PROGRAMS =remote_car rpi-hub scanner turtle_car gettingstarted gettingstarted_call_response transfer pingpair_dyn
SOURCES = ${PROGRAMS:=.cpp}

all: ${PROGRAMS}

${PROGRAMS}: ${SOURCES}
	g++ ${CCFLAGS} -Wall -I../../repos/RF24/ -L../../repos/RF24/ -lrf24-bcm $@.cpp -o ../bin/$@

clean:
	rm -rf ../bin/$(PROGRAMS)

