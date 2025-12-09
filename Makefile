# Nome do executável final
TARGET = bin/sistema_hotel.exe

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Arquivos fonte
SRCS = src/main.cpp src/clientes.cpp src/funcionarios.cpp src/quartos.cpp src/estadias.cpp

# Regra principal
all: $(TARGET)

# Como criar o executável
$(TARGET): $(SRCS)
	@if not exist bin mkdir bin
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Regra para executar
run: $(TARGET)
	./$(TARGET)

# Regra para limpar
clean:
	@if exist bin\sistema_hotel.exe del bin\sistema_hotel.exe
	@echo Limpeza concluida.