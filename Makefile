CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O0 -Imodels -Icontrollers -Iviews
LDFLAGS = -lcurl
TARGET = blackjack

# Archivos fuente
MODEL_SRCS = models/Carta.cpp models/Mano.cpp models/Apuesta.cpp
CONTROLLER_SRCS = controllers/Jugador.cpp controllers/Crupier.cpp controllers/Juego.cpp
MAIN_SRC = main.cpp

SRCS = $(MODEL_SRCS) $(CONTROLLER_SRCS) $(MAIN_SRC)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

debug: all
	gdb ./$(TARGET)

gdbserver: all
	@echo "Iniciando gdbserver en puerto :2345"
	gdbserver :2345 ./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_BIN) $(OBJS)
	rm -f models/*.o controllers/*.o views/*.o

# GoogleTest build
TEST_SRC = tests/test_blackjack.cpp
TEST_BIN = test_runner
google-test: $(TEST_BIN)
	./$(TEST_BIN)
$(TEST_BIN): $(TEST_SRC) $(MODEL_SRCS) $(CONTROLLER_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgtest -lgtest_main -lpthread $(LDFLAGS)

.PHONY: all run debug gdbserver clean google-test