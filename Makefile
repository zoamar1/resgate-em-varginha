# Compilador e flags
CXX = g++
# Atualizado para C++17 (exigido pelo SFML 2.6 e para aceitar nullptr)
# -Iincludes e -Isrc mapeiam as pastas para simplificar os #include no código
CXXFLAGS = -std=c++17 -Wall -Wextra -Iincludes -Isrc
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Nome do executável
TARGET = app_sfml

# Encontra todos os arquivos .cpp na raiz de src e também nas subpastas (entidades, gerenciadores, etc.)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Regra principal
all: $(TARGET)

# Linkagem do executável final
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compilação dos arquivos fonte em objetos
# O comando 'mkdir -p' garante que se o arquivo estiver em src/entidades/, 
# a pasta build/entidades/ será criada antes da compilação.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpa os arquivos compilados e o executável
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Roda o projeto
run: all
	./$(TARGET)