#ifndef TOILETCLICKER_SRC_CLICKER_H_
#define TOILETCLICKER_SRC_CLICKER_H_

#include <SFML/Graphics.hpp>

struct fallingPoop
{
  fallingPoop( sf::Vector2f vector_2, sf::Angle angle );
  sf::Vector2f pos;
  sf::Angle rot;
};

class clicker
{
private:
  int totalClicks = 0;

public:
  int  getTotalClicks() const;
  void click();
};


#endif    // TOILETCLICKER_SRC_CLICKER_H_
