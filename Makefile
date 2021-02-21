LIBS =
OBJ = game.o main.o tview.o 
EXE = snake
CXXFLAGS += -Wall -g

all: $(EXE)

$(EXE) : $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJ) $(EXE)

depend:
	$(CXX) -MM$(OBJ:.o=.cc) >.depend

-include .depend
