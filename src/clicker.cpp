//
// Created by CAD Station 2 on 4/14/2022.
//

#include "clicker.h"
int  clicker::getTotalClicks() const { return totalClicks; }
void clicker::click() { totalClicks++; }
fallingPoop::fallingPoop( sf::Vector2f pos, sf::Angle angle ) : pos( pos ), rot( angle ) {}
