#pragma once

#include <SFML/Graphics.hpp>
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
  int mouseX, mouseY;
  int score;
};