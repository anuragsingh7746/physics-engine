#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <bits/stdc++.h>
#include <cmath>

struct VerletObject{

    sf::Vector2f curr_pos = sf::Vector2f(480.f, 0.f);
    sf::Vector2f prev_pos = sf::Vector2f(480.f, 0.f);
    sf::Vector2f acc = sf::Vector2f(0.f, 0.f);
    
    void updatePosition(float dt){
        sf::Vector2f displacement = curr_pos - prev_pos;
        prev_pos = curr_pos;
        curr_pos = curr_pos + displacement + (acc * dt * dt); //verlet integration: x(n+1) = 2x(n) - x(n-1) + a*dt*dt;
        //reset acceleration
        acc = {};
    }


    void accelerate(sf::Vector2f a){
        acc += a;
    }
};

void update(VerletObject& obj, float dt){
    float sub_dt = dt /static_cast<float>(8);

    sf::Vector2f g = {0.0f, 1000.0f};
    for(int i=8; i>=1; i--){
        obj.accelerate(g);
        if(obj.curr_pos.y > 880){
            obj.curr_pos.y = 880;
        }
        obj.updatePosition(sub_dt);
    }
}

void renderobject(sf::RenderWindow &window, VerletObject& obj){

    //object geometry
    sf::RectangleShape shape1(sf::Vector2f(100.f, 100.f));
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition(obj.curr_pos);
    window.draw(shape1);

}

int main(){
    
    //taget window
    sf::RenderWindow window(sf::VideoMode(960, 1080), "Engine");
    int framelimit = 60;
    window.setFramerateLimit(framelimit);

    //constraint
    sf::RectangleShape ground(sf::Vector2f(960.f, 100.f));
    ground.setFillColor(sf::Color::White);
    ground.setPosition(sf::Vector2f(sf::Vector2f(0.f, 980.f)));


    VerletObject obj;

    float fps;
    float lastTime = 0;

    float dt = 1.0f / static_cast<float>(framelimit);

    sf::Clock clock;

    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        update(obj, dt);

        window.clear();
        window.draw(ground);
        renderobject(window, obj);
        window.display();
        
        float curr = clock.restart().asSeconds();
        float fps = 1.0f / curr;
        std::cout<<fps<<std::endl;

    }

    return 0;
}

