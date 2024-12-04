CXX = clang++
#must be c++17 to use variants
CXXFLAGS = -std=c++17
#compile
EXEC = calculator.exe
SRC = main.cpp tokenizer.cpp parser.cpp evaluator.cpp
OBJ = $(SRC:.cpp=.o)
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
#make clean
clean:
	del /Q $(OBJ) $(EXEC) 2> nul || exit 0
#make test
test: $(EXEC)
	./$(EXEC) --test
#make run
run: $(EXEC)
	./$(EXEC)
