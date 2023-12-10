#include <SFML/Graphics.hpp>
#include <box2d\box2d.h>
#include <iostream>

using namespace sf;

int main()
{
    b2Vec2 gravity(0.0f, 1.0f);
    b2World world(gravity);

    Vector2i screenSize(800, 600);

    RenderWindow window;
    window.create(VideoMode(screenSize.x, screenSize.y), "Game");

    View view;
    view.reset(FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
    view.setViewport(FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

    window.setVerticalSyncEnabled(true);
	
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::W://jump

                    break;
                case Keyboard::D://left

                    break;
                case Keyboard::A://right

                    break;
                case Keyboard::E://menu

                    break;
                case Event::MouseButtonPressed:
                    switch (event.MouseButtonPressed)
                    {
                    case Mouse::Left://attack

                        break;
                    case Mouse::Right://shoot

                        break;
                    }
                }
            }
        }

        world.Step(1.0f / 60.0f, 1, 1);

        window.clear(Color::White);
        manager->lvl.draw(window);
        //window.draw(shape);
        window.display();
    }
    return 0;
}