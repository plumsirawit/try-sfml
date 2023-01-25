#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

class ClickerGame {
public:
  enum GameState { PREGAME, INGAME, POSTGAME };
  ClickerGame();
  void run();

private:
  bool buttonPressed();
  void processEvents();
  void processGameEvents(sf::Event);
  void update(sf::Time);
  void render();

  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
  sf::Text scoreLabel;
  sf::Text timeLabel;
  sf::Text helloLabel;
  sf::Text resultLabel;
  sf::Text playLabel;
  sf::RectangleShape centerRect;
  sf::Font font;
  sf::Clock clock;
  int mouseX, mouseY;
  int score;
  GameState gameState;
};