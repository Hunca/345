all:
	g++ -Isfml\include -o app Main.cpp Ball.cpp -Lsfml\lib -lsfml-graphics -lsfml-window -lsfml-system