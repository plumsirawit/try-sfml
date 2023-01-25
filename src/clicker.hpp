#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

class ClickerGame {
public:
  ClickerGame();
  void run();

private:
  void processEvents();
  void update();
  void render();

  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
  sf::Text scoreLabel;
  sf::Font font;
  int mouseX, mouseY;
  int score;
};