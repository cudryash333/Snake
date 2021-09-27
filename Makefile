CXXFLAGS += -Wall -g
OBJ = game.o main.o tview.o gview.o view.o ai_controller.o 
EXE = snake
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXE)

$(EXE) : $(OBJ)
	$(CXX) -o $@ $^ $(LIBS)

clear:
	$(RM) $(OBJ) $(EXE) 

depend:
	$(CXX) -MM $(OBJ:.o=.cpp) >.depend

-include .depend
