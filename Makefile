TARGET = Smartcalc-v2.0
DIST_NAME = Smartcalc-2.0

CXX = g++
RM = rm -f
CP = cp -rf
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

tests:
	make -C ${DIR_LIBSMARTCALC} test

uninstall:
	${RM} ${DESTDIR}${PREFIX}/${TARGET}

dvi: docs/smartcalc.texi
	texi2dvi $<
	${RM} smartcalc.aux smartcalc.cp smartcalc.log smartcalc.toc smartcalc.cps
	dvipdfmx ./smartcalc.dvi

dist:
	${MKDIR} ${DIST_NAME}
	${MKDIR} ${DIST_NAME}/${DIR_LIBSMARTCALC}
	${MKDIR} ${DIST_NAME}/${DIR_APPSMARTCALC}
	${CP} Makefile ${DIST_NAME}
	${CP} docs ${DIST_NAME}
	${CP} ${DIR_LIBSMARTCALC}/*.cc ${DIST_NAME}/${DIR_LIBSMARTCALC}
	${CP} ${DIR_LIBSMARTCALC}/*.h ${DIST_NAME}/${DIR_LIBSMARTCALC}
	${CP} ${DIR_LIBSMARTCALC}/tests ${DIST_NAME}/${DIR_LIBSMARTCALC}
	${CP} ${DIR_LIBSMARTCALC}/Makefile ${DIST_NAME}/${DIR_LIBSMARTCALC}
	${CP} ${DIR_APPSMARTCALC}/*.cc ${DIST_NAME}/${DIR_APPSMARTCALC}
	${CP} ${DIR_APPSMARTCALC}/*.h ${DIST_NAME}/${DIR_APPSMARTCALC}
	${CP} ${DIR_APPSMARTCALC}/*.ui ${DIST_NAME}/${DIR_APPSMARTCALC}
	${CP} ${DIR_APPSMARTCALC}/CMakeLists.txt ${DIST_NAME}/${DIR_APPSMARTCALC}



clean:
	make -sC ${DIR_LIBSMARTCALC} clean
	make -sC ${DIR_APPLICATION} clean
	${RM} ${DIR_APPLICATION}/CMakeCache.txt 
	${RMDIR} ${DIR_APPLICATION}/CMakeFiles
	${RM} ${DIR_APPLICATION}/Makefile
	${RM} ${DIR_APPLICATION}/cmake_install.cmake
	${RMDIR} ${DIR_APPLICATION}/smartcalc.app
	${RMDIR} ${DIR_APPLICATION}/smartcalc_autogen
	${RMDIR} ${DIST_NAME}
 

.PHONY: all clean install uninstall dvi dist tests
