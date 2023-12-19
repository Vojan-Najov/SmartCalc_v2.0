TARGET = Smartcalc-v2.0

CXX = g++
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

DIR_LIBSMARTCALC = libsmartcalc
DIR_APPLICATION = smartcalc

all:
	make -sC ${DIR_LIBSMARTCALC} all
	cd ${DIR_APPLICATION} && cmake . && cmake --build .

clean:
	make -sC ${DIR_LIBSMARTCALC} clean
	make -sC ${DIR_APPLICATION} clean
	${RM} ${DIR_APPLICATION}/CMakeCache.txt 
	${RMDIR} ${DIR_APPLICATION}/CMakeFiles
	${RM} ${DIR_APPLICATION}/Makefile
	${RM} ${DIR_APPLICATION}/cmake_install.cmake
	${RMDIR} ${DIR_APPLICATION}/smartcalc.app
	${RMDIR} ${DIR_APPLICATION}/smartcalc_autogen
 
	 
	

.PHONY: all clean install uninstall dvi dist test
