CC=g++

all: GameServer.o Main.o
	$(CC) -o MicroMUD.exe GameServer.o Main.o