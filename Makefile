CC := g++
TARGET := prog
SRC := ./src
OUTPUT := ./src/output
CFLAGS := -march=native -O3 -Wall -g3

all: log funcoes meioTransmissao camadaAplicacao camadaEnlace main $(TARGET)

$(TARGET): $(OUTPUT)/main.o $(OUTPUT)/meioTransmissao.o $(OUTPUT)/camadaAplicacao.o $(OUTPUT)/camadaEnlace.o $(OUTPUT)/funcoes.o $(OUTPUT)/log.o
	$(CC) $(CFLAGS) -o $(TARGET) $(OUTPUT)/main.o $(OUTPUT)/meioTransmissao.o $(OUTPUT)/camadaAplicacao.o $(OUTPUT)/camadaEnlace.o $(OUTPUT)/funcoes.o $(OUTPUT)/log.o

main: $(SRC)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OUTPUT)/main.o

meioTransmissao: $(SRC)/meioTransmissao.cpp
	$(CC) $(CFLAGS) -c $(SRC)/meioTransmissao.cpp -o $(OUTPUT)/meioTransmissao.o

camadaAplicacao: $(SRC)/camadaAplicacao.cpp
	$(CC) $(CFLAGS) -c $(SRC)/camadaAplicacao.cpp -o $(OUTPUT)/camadaAplicacao.o

camadaEnlace: $(SRC)/camadaEnlace.cpp
	$(CC) $(CFLAGS) -c $(SRC)/camadaEnlace.cpp -o $(OUTPUT)/camadaEnlace.o

funcoes: $(SRC)/funcoes.cpp
	$(CC) $(CFLAGS) -c $(SRC)/funcoes.cpp -o $(OUTPUT)/funcoes.o

log: $(SRC)/log.cpp
	$(CC) $(CFLAGS) -c $(SRC)/log.cpp -o $(OUTPUT)/log.o

run: 
	./$(TARGET)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(TARGET)

clean:
	rm $(OUTPUT)/*.o
