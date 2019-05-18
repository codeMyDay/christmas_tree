#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <time.h>
#include <unistd.h>
#include <cmath>

void lineTo(float x, float y, float len, float angle)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x+len*cos(angle), y+len*sin(angle));
    glEnd();
}

void tree(float x, float y, float len, float angle)
{
    const float strange_angle = M_PI/24.0;
    lineTo(x, y, len, angle+strange_angle);
    lineTo(x, y, -len, angle);
    lineTo(x, y, len, angle+2*M_PI/3.0+strange_angle);
    lineTo(x, y, len, angle-2*M_PI/3.0+strange_angle);

    const float len_min = 2.0;
    if(len > len_min)
    {
        const float len_div = 0.4;

        tree(x+len*cos(angle+strange_angle), y+len*sin(angle+strange_angle), 2*len*len_div, angle+strange_angle);
        tree(x+len*cos(angle+2*M_PI/3.0+strange_angle), y+len*sin(angle+2*M_PI/3.0+strange_angle), len*len_div, angle+2*M_PI/3.0+strange_angle);
        tree(x+len*cos(angle-2*M_PI/3.0+strange_angle), y+len*sin(angle-2*M_PI/3.0+strange_angle), len*len_div, angle-2*M_PI/3.0+strange_angle);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 600), "Tree");
    window.setFramerateLimit(30);
    glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        glColor3f(0.0, 1.0, 0.0);
        lineTo(210.0, 400.0, 160.0, M_PI/2.0);
        tree(210.0, 400.0, 75.0, -M_PI/2.0);

        window.display();
        usleep(10000);
    }
    return 0;
}