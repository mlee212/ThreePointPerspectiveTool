#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);

    float radius = 5.f;

    sf::CircleShape circle(200.f);
    circle.setRadius(radius);
    circle.setPointCount(100);
    circle.setFillColor(sf::Color(100, 250, 50));

    const int barrsize = 4;
    sf::Vector2i basepoints[barrsize];
    int bpindex = 0;

    bool linesdrawn = false;

    const int iarrsize = 3;
    sf::Vector2i interpoints[iarrsize];
    int ipindex = 0;

    while (window.isOpen()) {
        sf::Event event;
        sf::Mouse mouse;
        
        // Debug statements
        // std::cout << mouse.getPosition(window).x << "," << mouse.getPosition(window).y << std::endl;
        // std::cout << interpoints[0].x << "," << interpoints[0].y << std::endl;

        
        // Events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(bpindex < barrsize && !linesdrawn){
                    basepoints[bpindex] = mouse.getPosition(window);
                    bpindex++;
                }
                else {
                    interpoints[ipindex] = mouse.getPosition(window);
                    ipindex++;
                }
            }
        }

        window.clear();

        // Draw basepoints
        for(int i = 0; i < barrsize; i++) {
            circle.setPosition(basepoints[i].x - radius,basepoints[i].y - radius);
            window.draw(circle);
        }

        // Draw lines
        if (bpindex == barrsize) {
            for(int i = 0; i < barrsize - 1; i++) {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(basepoints[i])),
                    sf::Vertex(sf::Vector2f(basepoints[barrsize-1])),
                };
                
                window.draw(line, 2, sf::Lines);
            }
            linesdrawn = true;
        }

        // Draw interpoints
        if(linesdrawn) {
            for(int i = 0; i < iarrsize; i++) {
                circle.setPosition(interpoints[i].x - radius,interpoints[i].y - radius);
                window.draw(circle);
            }
        }

        // Draw interlines
        if(linesdrawn && ipindex == iarrsize) {
            for(int i = 0; i < barrsize - 1; i++) {
                for(int j = 0; j < iarrsize; j++) {
                    sf::Vertex line[] =
                    {
                        sf::Vertex(sf::Vector2f(basepoints[i])),
                        sf::Vertex(sf::Vector2f(interpoints[j])),
                    };
                
                    window.draw(line, 2, sf::Lines);
                }
            }
            linesdrawn = true;
        }

        // Draw Current position
        circle.setPosition(mouse.getPosition(window).x - radius, mouse.getPosition(window).y - radius);
        window.draw(circle);
        window.display();
    }

    return 0;
}