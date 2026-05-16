# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++03 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Nome do executável
TARGET = app_sfml

# Arquivos fonte e objetos
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Regra principal
all: dir $(TARGET)

# Cria o diretório de build se não existir
dir:
	mkdir -p $(BUILD_DIR)

# Linkagem
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilação dos arquivos fonte em objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos compilados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Roda o projeto
run: all
	./$(TARGET)