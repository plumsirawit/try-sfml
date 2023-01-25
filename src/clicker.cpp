#include "clicker.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int RADIUS = 40;

ClickerGame::ClickerGame()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
              "SFML ClickerGame Application"),
      mPlayer(), mouseX(0), mouseY(0), score(0), gameState(PREGAME) {
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
  scoreLabel.setFillColor(sf::Color::White);
  scoreLabel.setStyle(sf::Text::Regular);
  scoreLabel.setPosition(10.f, 10.f);
  clock.restart();
  timeLabel.setFont(font);
  timeLabel.setString("Time Remaining: 30.00 seconds");
  timeLabel.setCharacterSize(24);
  timeLabel.setFillColor(sf::Color::White);
  timeLabel.setStyle(sf::Text::Regular);
  timeLabel.setPosition(10.f, 40.f);
  helloLabel.setFont(font);
  helloLabel.setString("Welcome to ClickerGame!");
  helloLabel.setCharacterSize(24);
  helloLabel.setStyle(sf::Text::Regular);
  sf::FloatRect helloBounds = helloLabel.getLocalBounds();
  sf::FloatRect helloGlobalBounds = helloLabel.getGlobalBounds();
  helloLabel.setOrigin(helloGlobalBounds.width / 2.f + helloBounds.left,
                       helloGlobalBounds.height / 2.f + helloBounds.top);
  helloLabel.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
  helloLabel.setFillColor(sf::Color::White);
  playLabel.setFont(font);
  playLabel.setString("PLAY");
  playLabel.setCharacterSize(24);
  playLabel.setStyle(sf::Text::Regular);
  sf::FloatRect playBounds = playLabel.getLocalBounds();
  sf::FloatRect playGlobalBounds = playLabel.getGlobalBounds();
  playLabel.setOrigin(playGlobalBounds.width / 2.f + playBounds.left,
                      playGlobalBounds.height / 2.f + playBounds.top);
  playLabel.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50.f);
  playLabel.setFillColor(sf::Color::Black);
  resultLabel.setFont(font);
  centerRect.setPosition(WINDOW_WIDTH / 2 - RADIUS,
                         WINDOW_HEIGHT / 2 - RADIUS / 2 + 50.f);
  centerRect.setSize({2 * RADIUS, RADIUS});
  centerRect.setFillColor(sf::Color::Green);
}
void ClickerGame::run() {
  while (mWindow.isOpen()) {
    processEvents();
    update(clock.getElapsedTime());
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
void ClickerGame::processGameEvents(sf::Event event) {
  float distsq = distSQ(mPlayer.getPosition() + sf::Vector2f({RADIUS, RADIUS}),
                        {(float)mouseX, (float)mouseY});
  if (distsq <= RADIUS * RADIUS) {
    score++;
    mPlayer.setPosition(rand() % (WINDOW_WIDTH - 2 * RADIUS),
                        rand() % (WINDOW_HEIGHT - 2 * RADIUS));
    scoreLabel.setString("Score: " + std::to_string(score));
  }
}
bool ClickerGame::buttonPressed() {
  sf::FloatRect rect = centerRect.getGlobalBounds();
  return rect.left <= mouseX && mouseX <= rect.left + rect.width &&
         rect.top <= mouseY && mouseY <= rect.top + rect.height;
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
      switch (gameState) {
      case PREGAME:
        if (buttonPressed())
          gameState = INGAME;
        break;
      case INGAME:
        processGameEvents(event);
        break;
      case POSTGAME:
        if (buttonPressed()) {
          gameState = INGAME;
          score = 0;
          scoreLabel.setString("Score: " + std::to_string(score));
          clock.restart();
        }
        break;
      }
    }
  }
}
void ClickerGame::update(sf::Time elapsedTime) {
  if (elapsedTime.asSeconds() > 30.0) {
    gameState = POSTGAME;
    resultLabel.setString("Score: " + std::to_string(score) + "!");
    resultLabel.setCharacterSize(24);
    resultLabel.setStyle(sf::Text::Regular);
    sf::FloatRect resultBounds = resultLabel.getLocalBounds();
    sf::FloatRect resultGlobalBounds = resultLabel.getGlobalBounds();
    resultLabel.setOrigin(resultGlobalBounds.width / 2.f + resultBounds.left,
                          resultGlobalBounds.height / 2.f + resultBounds.top);
    resultLabel.setPosition(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
    resultLabel.setFillColor(sf::Color::White);
    playLabel.setString("RETRY");
    playLabel.setCharacterSize(24);
    playLabel.setStyle(sf::Text::Regular);
    sf::FloatRect playBounds = playLabel.getLocalBounds();
    sf::FloatRect playGlobalBounds = playLabel.getGlobalBounds();
    playLabel.setOrigin(playGlobalBounds.width / 2.f + playBounds.left,
                        playGlobalBounds.height / 2.f + playBounds.top);
    playLabel.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50.f);
    playLabel.setFillColor(sf::Color::Black);
  }
  timeLabel.setString(
      "Time Remaining: " + std::to_string(30.0 - elapsedTime.asSeconds()) +
      " seconds");
}
void ClickerGame::render() {
  mWindow.clear();
  switch (gameState) {
  case PREGAME:
    mWindow.draw(helloLabel);
    mWindow.draw(centerRect);
    mWindow.draw(playLabel);
    break;
  case INGAME:
    mWindow.draw(mPlayer);
    mWindow.draw(scoreLabel);
    mWindow.draw(timeLabel);
    break;
  case POSTGAME:
    mWindow.draw(resultLabel);
    mWindow.draw(centerRect);
    mWindow.draw(playLabel);
    break;
  }
  mWindow.display();
}

int main() {
  ClickerGame game;
  game.run();
}