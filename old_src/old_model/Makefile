TARGET = libscmodel.a

CXX = g++
AR = ar rcs
RMDIR = rm -rf
RM = rm -f
MKDIR = mkdir -p

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17

INCLUDE_DIR = .
SRC_DIR = .
OBJ_DIR = ${SRC_DIR}/obj

INCLUDE = $(wildcard ${INCLUDE_DIR}/*.h)
SRC = $(wildcard ${SRC_DIR}/*.cc)
OBJ = $(addprefix ${OBJ_DIR}/, $(notdir ${SRC:.cc=.o}))

${TARGET}: ${OBJ}
	${AR} $@ $?

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cc ${INCLUDE}
	${MKDIR} ${@D}
	${CXX} ${CXX_FLAGS} -I${INCLUDE_DIR} -o $@ -c $<

clean:
	${RMDIR} ${OBJ_DIR}
	${RM} ${TARGET}

format:
	cp ../../linters/.clang-format .
	clang-format -i ${SRC} ${INCLUDE}
	rm .clang-format
