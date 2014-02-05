CC=g++
CFLAGS=-c -Wall -Wextra \
	#-Weffc++ -Werror -pedantic -g \
	-Wdisabled-optimization -Wcast-align \
	-Wcast-qual -Wchar-subscripts -Wcomment -Wconversion \
	-Wfloat-equal -Wformat -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k -Wimport  -Winit-self  -Winline \
	-Winvalid-pch -Wunsafe-loop-optimizations  \
	-Wlong-long -Wmissing-braces -Wmissing-field-initializers \
	-Wmissing-format-attribute -Wmissing-include-dirs \
	-Wmissing-noreturn -Wpacked  -Wpadded -Wparentheses  \
	-Wpointer-arith -Wredundant-decls -Wreturn-type \
	-Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
	-Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
	-Wswitch-enum -Wtrigraphs  -Wuninitialized \
	-Wunknown-pragmas  -Wunreachable-code -Wunused \
	-Wunused-function  -Wunused-label  -Wunused-parameter \
	-Wunused-value  -Wunused-variable  -Wvariadic-macros \
	-Wvolatile-register-var  -Wwrite-strings

all: TicTacToeMonteCarlo

TicTacToeMonteCarlo: main.o TicTacToe.o 
	$(CC) main.o TicTacToe.o -o TicTacToeMonteCarlo

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

TicTacToe.o: TicTacToe.cpp
	$(CC) $(CFLAGS) TicTacToe.cpp

clean:
	rm -rf  *.o TicTacToeMonteCarlo
