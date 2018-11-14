/*
  Studio Bakemono, 2018
*/

#include "MenuState.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "TestState.hpp"

MenuState::MenuState(sf::Font font) {
  //hello.setFont(font);
  //hello.setString("Hello, Sailor!");
  // hello.setCharacterSize(20);
  //hello.setFillColor(sf::Color::White);
  //hello.setFillColor(sf::Color::Red);

  this->font = font;

}


MenuState::~MenuState() {

}


void MenuState::onEnter(Game* game) {

  //Set up the title
  hello.setString("Chimeras");
  hello.setFont(font);
  hello.setCharacterSize(30);
 
  hello.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - hello.getLocalBounds().width/2,
				  game->window.getSize().y/2 - hello.getLocalBounds().height/2 ));
  
  //Create the menu options
  MenuItem option1;
  MenuItem option2;
  option1.name = "Option 1";
  option2.name = "Option 2";
  sf::RectangleShape option1rect;
  option1rect.setSize(sf::Vector2f(100,50));
  option1rect.setOutlineColor(sf::Color::Red);
  option1rect.setOutlineThickness(5);
  option1rect.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - option1rect.getLocalBounds().width/2, game->window.getSize().y/2  + 100));
  option1.rect = option1rect;
  sf::RectangleShape option2rect;
  option2rect.setSize(sf::Vector2f(100,50));
  option2rect.setOutlineColor(sf::Color::Red);
  option2rect.setOutlineThickness(5);
  option2rect.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - option2rect.getLocalBounds().width/2, game->window.getSize().y/2 + 200));
  option2.rect = option2rect;
  
  option1.menState =  new TestState(this->font);
  option2.menState =  new TestState(this->font);
  menuitems.push_back(option1);
  menuitems.push_back(option2);

}


void MenuState::onEvent() {

}


State* MenuState::update(sf::RenderWindow& window) {

  
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ){
    
  
    return menuitems[selected].menState;
    std::cout << "Entering state" <<std::endl;
  }
  //Cycle through the possible states
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    menuitems[selected].rect.setFillColor(sf::Color::Black);
    selected = (selected+1)%MenuLength;
    std::cout << "Downkey pressed, in state " << selected << std::endl;
    menuitems[selected].rect.setFillColor(sf::Color::Red);
  }
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    menuitems[selected].rect.setFillColor(sf::Color::Black);
    selected++;
    selected = (selected%MenuLength + MenuLength)%MenuLength;
    menuitems[selected].rect.setFillColor(sf::Color::Red);

    std::cout << "Upkey pressed, in state " << selected << std::endl;
  }
  
  return nullptr;
  
}

void MenuState::render(sf::RenderWindow& window) {

  window.draw(hello);
  for (std::vector<MenuItem>::const_iterator i = menuitems.begin(); i != menuitems.end(); ++i){
    window.draw(i->rect);
  }
  

}





