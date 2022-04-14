#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "clicker.h"

int main()
{
  const int        WIDTH  = 640;
  const int        HEIGHT = 480;
  sf::RenderWindow window( sf::VideoMode( WIDTH, HEIGHT ), "ToiletClicker" );
  sf::Event        event;

  sf::Font font;
  if( !font.loadFromFile( "resources/fonts/Roboto/Roboto-Regular.ttf" ) )
  {
    std::cout << "Error loading font Roboto-Black.ttf" << std::endl;
    return EXIT_FAILURE;
  }

  sf::Texture toiletTexture;
  sf::Sprite  toiletSprite;
  if( !toiletTexture.loadFromFile( "resources/toilet.png" ) )
  {
    std::cout << "Error loading toilet.png" << std::endl;
    return EXIT_FAILURE;
  }

  sf::Texture poopTexture;
  sf::Sprite  poopSprite;
  if( !poopTexture.loadFromFile( "resources/poop.png" ) )
  {
    std::cout << "Error loading poop.png" << std::endl;
    return EXIT_FAILURE;
  }

  toiletSprite.setTexture( toiletTexture );
  toiletSprite.setOrigin( sf::Vector2f( 490.0f, 666.0f ) );
  toiletSprite.setScale( sf::Vector2f( 0.2f, 0.2f ) );
  toiletSprite.setPosition( sf::Vector2f( 300.0f, 250.0f ) );

  poopSprite.setTexture( poopTexture );
  poopSprite.setOrigin( sf::Vector2f( 300.0f, 300.0f ) );
  poopSprite.setScale( sf::Vector2f( 0.1f, 0.1f ) );
  poopSprite.setPosition( sf::Vector2f( 200.0f, 200.0f ) );


  clicker   c;
  sf::Clock clock;
  float     clicksPerSecond = 0.0f;
  int       clickArray[5]   = { 0, 0, 0, 0, 0 };
  int       clickArrayIndex = 0;
  int       currentClicks   = 0;
  sf::Clock clickClock;

  std::vector<fallingPoop> fallingPoops;
  int                      max_num_falling = 100000;
  float                    rotation_rate   = 100;
  float                    fall_rate       = 100;

  while( window.isOpen() )
  {
    float elapsedTime = clock.restart().asSeconds();
    if( clickClock.getElapsedTime().asSeconds() >= 1.f )
    {
      clickArray[clickArrayIndex] = currentClicks;
      currentClicks               = 0;
      int click_sum               = 0;
      clickArrayIndex             = ( clickArrayIndex + 1 ) % 5;
      for( int x : clickArray ) { click_sum += x; }
      clicksPerSecond = click_sum / 5.0f;
      clickClock.restart();

      if( fallingPoops.size() < max_num_falling )
      {
        int cps = static_cast<int>( clicksPerSecond );
        for( int i = 0; i < cps; i++ )
        {
          float     x     = rand() % WIDTH;
          float     y     = -60.0f - ( rand() % 120 );
          bool      dir   = rand() % 2;
          sf::Angle angle = sf::degrees( rand() % 360 );
          fallingPoops.emplace_back( sf::Vector2f( x, y ), angle, dir );
        }
      }
    }

    while( window.pollEvent( event ) )
    {
      if( event.type == sf::Event::Closed ) window.close();
      if( event.type == sf::Event::MouseButtonPressed )
      {
        sf::Vector2f click_pos( static_cast<float>( event.mouseButton.x ), static_cast<float>( event.mouseButton.y ) );
        if( toiletSprite.getGlobalBounds().contains( click_pos ) )
        {
          c.click();
          currentClicks++;
        }
      }
    }

    //c.click();
    //currentClicks++;

    int                total_clicks = c.getTotalClicks();
    std::ostringstream out;
    out.precision( 1 );
    out << std::fixed << clicksPerSecond;

    std::string stats_str = "Total Clicks: ";
    stats_str.append( std::to_string( total_clicks ) );
    stats_str.append( " CPS: " );
    stats_str.append( out.str() );

    sf::Text stats( stats_str, font );

    window.clear( sf::Color::Black );
    for( fallingPoop & poop : fallingPoops )
    {
      int dir = poop.rotate_dir ? 1 : -1;
      poop.pos.y += fall_rate * elapsedTime;
      poop.rot = sf::degrees( poop.rot.asDegrees() + ( rotation_rate * elapsedTime * dir ) );
      poopSprite.setPosition( poop.pos );
      poopSprite.setRotation( poop.rot );
      window.draw( poopSprite );
    }

    window.draw( toiletSprite );
    window.draw( stats );
    window.display();

    auto it = fallingPoops.begin();
    while( it != fallingPoops.end() )
    {
      if( it->pos.y > HEIGHT + 60 ) { it = fallingPoops.erase( it ); }
      else
      {
        ++it;
      }
    }
  }

  return 0;
}