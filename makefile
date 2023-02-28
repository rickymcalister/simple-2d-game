simple2dgame: src/main.cpp src/Game.cpp assets/fonts/Dosis-Light.ttf
	c++ -c src/main.cpp src/Game.cpp
	g++ main.o Game.o -o simple2dgameapp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
