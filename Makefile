build:
	g++ -c *.cpp -I/usr/include/SFML/
	g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	g++ *.o -o sfml-app -L/usr/include/SFML/ -lsfml-graphics -lsfml-window -lsfml-system

run:
	./sfml-app

clean:
	rm *.o
	rm sfml-app	
