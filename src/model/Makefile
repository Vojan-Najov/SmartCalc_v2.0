TARGET = libsmartcalc.a
TEST = test

CXX = g++
AR = ar rcs
RMDIR = rm -rf
RM = rm -f
MKDIR = mkdir -p

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17
TEST_LIBS = -lgtest

INCLUDE_DIR = .
SRC_DIR = .
OBJ_DIR = ${SRC_DIR}/obj
TEST_SRC_DIR = $(SRC_DIR)/tests
TEST_OBJ_DIR = $(OBJ_DIR)/tests

INCLUDE = $(wildcard ${INCLUDE_DIR}/*.h)
SRC = $(wildcard ${SRC_DIR}/*.cc)
OBJ = $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))
TEST_SRC = $(wildcard ${TEST_SRC_DIR}/*.cc)
TEST_OBJ = $(addprefix ${TEST_OBJ_DIR}/, $(notdir ${TEST_SRC:.cc=.o}))

all: ${TARGET}

${TARGET}: ${OBJ}
	${AR} $@ $?

${TEST}: ${TARGET} ${INCLUDE} ${TEST_OBJ}
	${CXX} -o $@ ${TEST_OBJ} ${TARGET} ${TEST_LIBS} -I{INCLUDE_DIR}
	./${TEST}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CXX} ${CXX_FLAGS} -I${INCLUDE_DIR} -o $@ -c $<

${TEST_OBJ_DIR}/%.o: ${TEST_SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CXX} ${CXX_FLAGS} -I${INCLUDE_DIR} -o $@ -c $<

clean:
	${RMDIR} ${OBJ_DIR}
	${RM} ${TARGET}
	${RM} ${TEST}

format:
	cp ../../linters/.clang-format .
	clang-format -i ${SRC} ${INCLUDE}
	rm .clang-format

.PHONY: ${TEST} all clean format
