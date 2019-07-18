all:
	g++ -Isfml\include -o app Main.cpp Ball.cpp Player.cpp -Lsfml\lib -lsfml-graphics -lsfml-window -lsfml-system
cue:
	g++ -Isfml\include -o app Main2.cpp Ball.cpp Player.cpp -Lsfml\lib -lsfml-graphics -lsfml-window -lsfml-system
liam:
	g++ -Isfml/include -o app Mainliam.cpp Ball.cpp -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system
dt:
	g++ -Isfml/include -o app DeltaTime.cpp -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system