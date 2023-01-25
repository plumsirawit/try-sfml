#include "clicker.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int RADIUS = 40;

ClickerGame::ClickerGame()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
              "SFML ClickerGame Application"),
      mPlayer(), mouseX(0), mouseY(0), score(0) {
  std::string fontPath = (std::filesystem::path(CMAKE_SOURCE_DIR) / "assets" /
                          "Inconsolata-Regular.ttf")
                             .string();
  if (!font.loadFromFile(fontPath)) {
    throw "Font not found!";
  }
  mPlayer.setRadius(RADIUS);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(sf::Color::Cyan);
  scoreLabel.setFont(font);
  scoreLabel.setString("Score: 0");
  scoreLabel.setCharacterSize(24);
  scoreLabel.setFillColor(sf::Color::Red);
  scoreLabel.setStyle(sf::Text::Regular);
  scoreLabel.setPosition(10.f, 10.f);
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
          distSQ(mPlayer.getPosition() + sf::Vector2f({RADIUS, RADIUS}),
                 {(float)mouseX, (float)mouseY});
      if (distsq <= RADIUS * RADIUS) {
        score++;
        mPlayer.setPosition(rand() % (WINDOW_WIDTH - 2 * RADIUS),
                            rand() % (WINDOW_HEIGHT - 2 * RADIUS));
        scoreLabel.setString("Score: " + std::to_string(score));
      }
    }
  }
}
void ClickerGame::update() {}
void ClickerGame::render() {
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.draw(scoreLabel);
  mWindow.display();
}

int main() {
  ClickerGame game;
  game.run();
}