CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD -Iinclude -I/opt/X11/include
EXEC=raiinet
SRC=src
INCLUDE=include
CCFILES=$(SRC)/main.cc $(SRC)/controller.cc $(SRC)/board.cc $(SRC)/player.cc \
        $(SRC)/textdisplay.cc $(SRC)/view.cc $(SRC)/graphicdisplay.cc $(SRC)/window.cc \
        $(SRC)/basiclink.cc $(SRC)/tile.cc $(SRC)/subject.cc \
        $(SRC)/boostedlink.cc $(SRC)/weakenedlink.cc $(SRC)/knightedlink.cc \
        $(SRC)/firewall.cc $(SRC)/link.cc $(SRC)/linkboost.cc $(SRC)/linkdecorator.cc \
        $(SRC)/polarise.cc $(SRC)/weakenify.cc $(SRC)/warpify.cc $(SRC)/knightify.cc \
        $(SRC)/download.cc $(SRC)/uploadify.cc $(SRC)/scan.cc $(SRC)/ability.cc
OBJECTS=${CCFILES:.cc=.o}
DEPENDS=${CCFILES:.cc=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -L/opt/X11/lib -lX11

-include ${DEPENDS}

${SRC}/%.o: ${SRC}/%.cc
	${CXX} ${CXXFLAGS} -c $< -o $@

.PHONY: clean
clean:
	rm -f ${EXEC} ${SRC}/*.o ${SRC}/*.d