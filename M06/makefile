CXX=g++

FLTK_LIB_DIR=../fltk/lib
FLTK_INCLUDE_DIR=../fltk
GUI_DIR=../GUI

GUI_O=Graph.o GUI.o Simple_window.o Window.o
PROJECT_O= Matrices.o PolygonMatrix.o

OPTIM= -Os -Wall -Wunused -Wno-format-y2k  -fno-exceptions -fno-strict-aliasing -ffunction-sections -fdata-sections
CXXFLAGS= -I/usr/include/freetype2 -I/usr/include/libpng16 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
CXXFLAGS2= -c -Wall -g -std=c++14 -I $(FLTK_INCLUDE_DIR) -I $(GUI_DIR)
#LDLIBS= -lfltk -lfltk_forms -lfltk_gl -lfltk_images -lfltk_jpeg -lXrender -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11
LDLIBS= -lfltk -lfltk_forms -lfltk_gl -lfltk_images -lfltk_jpeg -lXrender -lXft -lfontconfig -lpthread -ldl -lm -lX11
LDFLAGS= -L $(FLTK_LIB_DIR)

EXE=M06

default : main.o $(PROJECT_O) $(GUI_O)
	$(CXX) -g main.o $(PROJECT_O) $(GUI_O) $(LDFLAGS) $(LDLIBS) -o $(EXE)
main.o : main.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) main.cpp
Graph.o : $(GUI_DIR)/Graph.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) $(GUI_DIR)/Graph.cpp
GUI.o : $(GUI_DIR)/GUI.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) $(GUI_DIR)/GUI.cpp
Simple_window.o : $(GUI_DIR)/Simple_window.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) $(GUI_DIR)/Simple_window.cpp
Window.o : $(GUI_DIR)/Window.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) $(GUI_DIR)/Window.cpp
Matrices.o : Matrices.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) Matrices.cpp
PolygonMatrix.o : PolygonMatrix.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS2) PolygonMatrix.cpp

clean:
	rm *.o $(EXE)
run:
	./$(EXE)
