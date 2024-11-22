// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Font myfont;
	if (!myfont.loadFromFile("./Arial.ttf"))
	{
		cerr << "error loading";
	}

	Text text;
	text.setFont(myfont);
	text.setString("Click three times for the shape and one more to start");
	text.setCharacterSize(40);
	text.setFillColor(Color::Blue);
	text.setPosition(20, 20);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/	
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
					if(vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if(points.size() == 0)
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
			if(points.size() < 10000)
			{
				int randomIndex = rand() % vertices.size();
				Vector2f midpoint = (vertices[randomIndex] + points.back()) / 2.0f;
				points.push_back(midpoint);
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/	
		window.clear();
		window.draw(text);
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}
		for (int i = 0; i < points.size(); i++)
		{
			CircleShape point(2);
			point.setPosition(points[i]);
			point.setFillColor(Color::Green);
			window.draw(point);
		}
		window.display();
	}
}
