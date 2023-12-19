TARGET = Smartcalc-v2.0

CXX = g++
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

DIR_LIBSMARTCALC = libsmartcalc
DIR_APPLICATION = appsmartcalc

ifeq (${PREFIX},)
  PREFIX := ~
endif

all:
	make -sC ${DIR_LIBSMARTCALC} all
	cd ${DIR_APPLICATION} && cmake -DCMAKE_CXX_COMPILER=g++ . && cmake --build .

install: all
	install -d ${DESTDIR}${PREFIX}
	install -m 755 ${DIR_APPLICATION}/smartcalc.app/Contents/*/smartcalc \
                   ${DESTDIR}${PREFIX}/${TARGET}

uninstall:
	${RM} ${DESTDIR}${PREFIX}/${TARGET}


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
