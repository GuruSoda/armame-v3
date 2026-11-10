.SUFFIXES = .c .cpp

NOMBRE_EJECUTABLE=libarmamews.so
DIR_OBJETOS = ../build/linux/${NOMBRE_EJECUTABLE}/
MIS_DEFINE= -DSQLITE_THREADSAFE=1
MIS_LINKS=
CXXFLAGS=-fPIC -shared

LIBRERIAS=../../../Librerias

# CXX=/usr/bin/arm-linux-gnueabi-g++-4.6

SALIDA_EJECUTABLE=../../bin

VERSION=1.6

# Para compilar en 64 sobre 32, instalar el paquete g++-multilib
ifeq ($(BITS),64)
    CXXFLAGS+=-m64
else ifeq ($(BITS),32)
        CXXFLAGS+=-m32
endif

ifeq (${DEBUG},1)
 CXXFLAGS+=-ggdb -g3
else
 CXXFLAGS+=-s -O2
endif

# mismos parametros para compilar C/C++
CFLAGS=$(CXXFLAGS)

RAIZ=.
INCLUDED=${RAIZ}/ \
	${LIBRERIAS}/ \
	${LIBRERIAS}/GuruCompat/ \
	${LIBRERIAS}/sqlite/ \
	${LIBRERIAS}/jsoncpp/ \
	${RAIZ}/../libs

PARAM_INCLUDE:=$(addprefix "-I", ${INCLUDED})

VPATH=${INCLUDED}

MIS_LIBS := jsoncpp.o sqlite3.o GuruConfigV2.o GuruConfigLeer.o 
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${MIS_LIBS})

PROGRAMA := main.o
OBJETOS += $(addprefix ${DIR_OBJETOS}, ${PROGRAMA})

${NOMBRE_EJECUTABLE}: crear_directorios Makefile ${OBJETOS}
	@$(CXX) ${CXXFLAGS} $(LDFLAGS) -o $(SALIDA_EJECUTABLE)/$@ $(OBJETOS) ${MIS_LINKS}
	@echo "Todo terminado????"

${DIR_OBJETOS}%.o: %.cpp
	@echo "Compilando C++ $? -> $@"
	@${CXX} -std=c++11 -fPIC -O2 -x c++ -pipe ${CXXFLAGS} ${MIS_DEFINE} ${PARAM_INCLUDE} -c $? -o $@

${DIR_OBJETOS}%.o:%.c
	@echo "Compilando C $? -> $@"
	@${CC} -fPIC -O2 -s -pipe ${CFLAGS} ${PARAM_INCLUDE} ${MIS_DEFINE} -c $? -o $@

clean:
	@rm -f ${OBJETOS}

crear_directorios:
	@mkdir -p ${DIR_OBJETOS}

compilar:
	@echo ${VPATH} ${OBJETOS}

