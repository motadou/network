TOPDIR=../..

## INCLUDE RULES
TARGET:= ./test_client

## fix top makerules options

INCLUDE += -I${TOPDIR}
LIB += ${TOPDIR}/thirdparty/libutil.a

all: server client

server:server.cpp
	g++ -o server server.cpp ${INCLUDE} ${LIB}

client:client.cpp
	g++ -o client client.cpp ${INCLUDE} ${LIB}

clean:
	rm -rf client server