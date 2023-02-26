simple2dgame: src/main.cpp
	c++ -c src/main.cpp -o build/main.o
	g++ build/main.o -o simple2dgameapp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
