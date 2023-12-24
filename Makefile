TARGET = Smartcalc-v2.0
DIST_NAME = Smartcalc-2.0

CXX = g++
CP = cp -rf
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
TARGZ = tar -czvf

DIR_LIBSMARTCALC = libsmartcalc
DIR_APPSMARTCALC = appsmartcalc

ifeq (${PREFIX},)
  PREFIX := ~
endif

all:
	make -sC ${DIR_LIBSMARTCALC} all
	cd ${DIR_APPSMARTCALC} && cmake -DCMAKE_CXX_COMPILER=g++ . && cmake --build .

install: all
	install -d ${DESTDIR}${PREFIX}
	install -m 755 ${DIR_APPSMARTCALC}/smartcalc.app/Contents/*/smartcalc \
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
	${TARGZ} ${DIST_NAME}.tar.gz ${DIST_NAME}
	${RMDIR} ${DIST_NAME}


clean:
	make -sC ${DIR_LIBSMARTCALC} clean
	${RM} ${DIR_APPSMARTCALC}/CMakeCache.txt 
	${RMDIR} ${DIR_APPSMARTCALC}/CMakeFiles
	${RM} ${DIR_APPSMARTCALC}/Makefile
	${RM} ${DIR_APPSMARTCALC}/cmake_install.cmake
	${RMDIR} ${DIR_APPSMARTCALC}/smartcalc.app
	${RMDIR} ${DIR_APPSMARTCALC}/smartcalc_autogen
	${RMDIR} ${DIST_NAME}
	${RM} smartcalc.dvi smartcalc.pdf
 
format:
	make -C ${DIR_LIBSMARTCALC} format
	${CP} linters/.clang-format .
	clang-format -i ${DIR_APPSMARTCALC}/*.h ${DIR_APPSMARTCALC}/*.cc
	${RM} .clang-format

.PHONY: all clean install uninstall dvi dist tests format
