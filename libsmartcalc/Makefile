TARGET = libsmartcalc.a
TEST = test
REPORT = gcov_report

CXX = g++
AR = ar rcs
RMDIR = rm -rf
RM = rm -f
MKDIR = mkdir -p

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17 -O3
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -g -O0
TEST_LIBS = -lgtest

INCLUDE_DIR = .
SRC_DIR = .
OBJ_DIR = ${SRC_DIR}/obj
TEST_SRC_DIR = $(SRC_DIR)/tests
TEST_OBJ_DIR = $(OBJ_DIR)/tests
GCOV_DIR = ${SRC_DIR}/gcov_report
GCOV_OBJ_DIR = ${GCOV_DIR}/objs

INCLUDE = $(wildcard ${INCLUDE_DIR}/*.h)
SRC = $(wildcard ${SRC_DIR}/*.cc)
OBJ = $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))
TEST_SRC = $(wildcard ${TEST_SRC_DIR}/*.cc)
TEST_OBJ = $(addprefix ${TEST_OBJ_DIR}/, $(notdir ${TEST_SRC:.cc=.o}))
GCOV_OBJ = $(addprefix ${GCOV_OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))

all: ${TARGET}

${TARGET}: ${OBJ}
	${AR} $@ $?

${TEST}: ${TARGET} ${TEST_OBJ}
	${CXX} -o $@ ${TEST_OBJ} ${TARGET} ${TEST_LIBS} -I${INCLUDE_DIR}
	./${TEST}

$(REPORT): ${GCOV_OBJ} ${TEST_OBJ}
	${CXX} ${GCOV_FLAGS} -o ${TEST} $? ${TEST_LIBS}
	./${TEST} 2>/dev/null
	gcov ${GCOV_OBJ_DIR}/*.gcno
	mv *.gcov ${GCOV_OBJ_DIR}
	lcov -c -t "libsmartcalc" -o ${GCOV_DIR}/report.info -d ${GCOV_OBJ_DIR}
	genhtml -o ${GCOV_DIR} ${GCOV_DIR}/report.info

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CXX} ${CXX_FLAGS} -I${INCLUDE_DIR} -o $@ -c $<

${TEST_OBJ_DIR}/%.o: ${TEST_SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CXX} ${CXX_FLAGS} -I${INCLUDE_DIR} -o $@ -c $<

${GCOV_OBJ_DIR}/%.o: ${SRC_DIR}/%.cc
	@${MKDIR} ${@D}
	${CXX} ${GCOV_FLAGS} -c $< -o $@

clean:
	${RMDIR} ${OBJ_DIR}
	${RMDIR} ${GCOV_DIR}
	${RM} ${TARGET}
	${RM} ${TEST}

re: clean all

format:
	cp ../linters/.clang-format .
	clang-format -i ${SRC} ${INCLUDE} ${TEST_SRC}
	rm .clang-format

.PHONY: ${TEST} ${REPORT} all clean format re
