LDLIBS = -lwiringPi

OBJECTS := main.o shapecollection.o beziervisitor.o linevisitor.o circlevisitor.o hardwareconnector.o abstractvisitor.o
CXXFLAGS := -O2
run: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDLIBS) -o run

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

shapecollection.o: ../LaserPainter/shapecollection.cpp ../LaserPainter/shapecollection.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/shapecollection.cpp -o shapecollection.o

abstractvisitor.o: ../LaserPainter/abstractvisitor.cpp ../LaserPainter/abstractvisitor.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/abstractvisitor.cpp -o abstractvisitor.o

beziervisitor.o: ../LaserPainter/beziervisitor.cpp ../LaserPainter/beziervisitor.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/beziervisitor.cpp -o beziervisitor.o

linevisitor.o: ../LaserPainter/linevisitor.cpp ../LaserPainter/linevisitor.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/linevisitor.cpp -o linevisitor.o

circlevisitor.o: ../LaserPainter/circlevisitor.cpp ../LaserPainter/circlevisitor.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/circlevisitor.cpp -o circlevisitor.o

hardwareconnector.o: ../LaserPainter/hardwareconnector.cpp ../LaserPainter/hardwareconnector.h
	$(CXX) $(CXXFLAGS) -c ../LaserPainter/hardwareconnector.cpp -o hardwareconnector.o
