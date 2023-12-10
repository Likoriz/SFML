#include <SFML/Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>

using namespace sf;

int main()
{
    b2Vec2 gravity(0.0f, 1.0f);
    b2World world(gravity);

    RenderWindow window(VideoMode(400, 400), L"Новый проект", Style::Default);

    window.setVerticalSyncEnabled(true);

    CircleShape shape(100.f, 3);
    shape.setPosition(100, 100);
    shape.setFillColor(Color::Magenta);
	
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Blue);
        window.draw(shape);
        window.display();
    }
    return 0;
}