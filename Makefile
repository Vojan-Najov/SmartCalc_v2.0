TARGET = Smartcalc-v2.0

CXX = g++
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p

CXX_FLAGS = -Wall -Wextra -Werror -std=c++17
LIBS = -Llibsmartcalc -lsmartcalc
INCLUDE = -Ilibsmartcalc/

DIR_SRC = .
DIR_MODEL = ${DIR_SRC}/model
DIR_CONTROLLER = ${DIR_SRC}/controller

SRC_MODEL = $(wildcard ${DIR_MODEL}/*.cc)
SRC_CONTROLLER = $(wildcard ${DIR_CONTROLLER}/*.cc)


model: smartcalc ${SRC_MODEL}
	${CXX} ${CXX_FLAGS} ${INCLUDE} -o ${DIR_MODEL}/model.o \
                                   -c ${SRC_MODEL}

controller: model ${SRC_CONTROLLER}
	${CXX} ${CXX_FLAGS} ${INCLUDE} -o ${DIR_CONTROLLER}/controller.o \
                                   -c ${SRC_CONTROLLER}



smartcalc:
	make -sC libsmartcalc all
