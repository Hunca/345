all:
	g++ -Isfml/include -o app Main.cpp Ball.cpp Physics.cpp MovementManager.cpp PlayerManager.cpp GameManager.cpp Player.cpp -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system