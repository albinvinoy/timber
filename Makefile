build:
	g++ -c *.cpp -std=c++11 -I/usr/include/SFML/
	g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	g++ *.o -o sfml-app -L/usr/include/SFML/ -lsfml-graphics -lsfml-window -lsfml-system

run:
	./sfml-app

clean:
	rm *.o
	rm sfml-app

frun:
	$(MAKE) clean
	$(MAKE) build
	$(MAKE) run	
