CC := g++
TARGET := prog
SRC := ./src

all: funcoes camadaAplicacao camadaEnlace main $(TARGET)

$(TARGET): main.o camadaAplicacao.o camadaEnlace.o funcoes.o  
	$(CC) -o $(TARGET) main.o camadaAplicacao.o camadaEnlace.o funcoes.o 

main: $(SRC)/main.cpp
	$(CC) -c $(SRC)/main.cpp -o main.o

camadaAplicacao: $(SRC)/camadaAplicacao.cpp
	$(CC) -c $(SRC)/camadaAplicacao.cpp -o camadaAplicacao.o

camadaEnlace: $(SRC)/camadaEnlace.cpp
	$(CC) -c $(SRC)/camadaEnlace.cpp -o camadaEnlace.o

funcoes: $(SRC)/funcoes.cpp
	$(CC) -c $(SRC)/funcoes.cpp -o funcoes.o

run: 
	./$(TARGET)
