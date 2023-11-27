CC := g++
TARGET := prog
SRC := ./src
OUTPUT := ./src/output

all: log funcoes meioTransmissao camadaAplicacao camadaEnlace main $(TARGET)

$(TARGET): $(OUTPUT)/main.o $(OUTPUT)/meioTransmissao.o $(OUTPUT)/camadaAplicacao.o $(OUTPUT)/camadaEnlace.o $(OUTPUT)/funcoes.o $(OUTPUT)/log.o
	$(CC) -o $(TARGET) $(OUTPUT)/main.o $(OUTPUT)/meioTransmissao.o $(OUTPUT)/camadaAplicacao.o $(OUTPUT)/camadaEnlace.o $(OUTPUT)/funcoes.o $(OUTPUT)/log.o

main: $(SRC)/main.cpp
	$(CC) -c $(SRC)/main.cpp -o $(OUTPUT)/main.o

meioTransmissao: $(SRC)/meioTransmissao.cpp
	$(CC) -c $(SRC)/meioTransmissao.cpp -o $(OUTPUT)/meioTransmissao.o

camadaAplicacao: $(SRC)/camadaAplicacao.cpp
	$(CC) -c $(SRC)/camadaAplicacao.cpp -o $(OUTPUT)/camadaAplicacao.o

camadaEnlace: $(SRC)/camadaEnlace.cpp
	$(CC) -c $(SRC)/camadaEnlace.cpp -o $(OUTPUT)/camadaEnlace.o

funcoes: $(SRC)/funcoes.cpp
	$(CC) -c $(SRC)/funcoes.cpp -o $(OUTPUT)/funcoes.o

log: $(SRC)/log.cpp
	$(CC) -c $(SRC)/log.cpp -o $(OUTPUT)/log.o

run: 
	./$(TARGET)

clean:
	rm *.o
