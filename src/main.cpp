#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
  sf::CircleShape shape;
  shape.setRadius(40.f);
  int x = 100;
  shape.setPosition(100.f, 100.f);
  shape.setFillColor(sf::Color::Cyan);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    x++;
    x %= 500;
    shape.setPosition(x, 100.f);
    window.clear();
    window.draw(shape);
    window.display();
  }
}