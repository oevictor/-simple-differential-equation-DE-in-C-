# Definições de variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I/usr/include/gtest -g -pthread
LDFLAGS = -L/usr/lib -lgtest -lgtest_main

# Definições de arquivos fonte
SRCS = src/main.cpp src/populacao.cpp src/mutacao.cpp src/selecao.cpp src/resultado.cpp
TEST_SRCS = src/test_main.cpp src/populacao.cpp src/mutacao.cpp src/selecao.cpp src/resultado.cpp

# Definições de arquivos objeto
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Definições de executáveis
TARGET = bin/main
TEST_TARGET = bin/test_main

# Compilação dos alvos
all: $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Linkagem do executável principal
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Linkagem do executável de teste
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Limpeza dos arquivos objeto e executáveis
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

.PHONY: clean all run test
