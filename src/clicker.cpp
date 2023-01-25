#include "clicker.hpp"

ClickerGame::ClickerGame()
    : mWindow(sf::VideoMode(640, 480), "SFML ClickerGame Application"),
      mPlayer(), mouseX(0), mouseY(0), score(0) {
  mPlayer.setRadius(40.f);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(sf::Color::Cyan);
}
void ClickerGame::run() {
  while (mWindow.isOpen()) {
    processEvents();
    update();
    render();
  }
}
float distSQ(sf::Vector2f vec1, sf::Vector2f vec2) {
  std::cerr << "vec1(" << vec1.x << ", " << vec1.y << "); vec2(" << vec2.x
            << ", " << vec2.y << ");" << std::endl;
  float dx = vec1.x - vec2.x;
  float dy = vec1.y - vec2.y;
  return dx * dx + dy * dy;
}
void ClickerGame::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      mWindow.close();
    else if (event.type == sf::Event::MouseMoved) {
      mouseX = event.mouseMove.x;
      mouseY = event.mouseMove.y;
    } else if (event.type == sf::Event::MouseButtonPressed) {
      float distsq =
          distSQ(mPlayer.getPosition() +
                     sf::Vector2f({mPlayer.getRadius(), mPlayer.getRadius()}),
                 {(float)mouseX, (float)mouseY});
      if (distsq <= mPlayer.getRadius() * mPlayer.getRadius()) {
        score++;
        mPlayer.setPosition(rand() % 640, rand() % 480);
        std::cerr << "Score: " << score << std::endl;
      }
    }
  }
}
void ClickerGame::update() {}
void ClickerGame::render() {
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}

int main() {
  ClickerGame game;
  game.run();
}