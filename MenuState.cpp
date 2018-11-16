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


  menuItems.resize(MENU_LENGTH);

  // Grab option 1 and 2 from the vector to do specific operations
  
  MenuItem* option1 = &menuItems[0];
  MenuItem* option2 = &menuItems[1];

  option1->name = "Option 1";
  option2->name = "Option 2";

  option1->rect.setSize(sf::Vector2f(100,50));
  option1->rect.setOutlineColor(sf::Color::Red);
  option1->rect.setFillColor(sf::Color::Red);
  option1->rect.setOutlineThickness(5);
  option1->rect.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - option1->rect.getLocalBounds().width/2, game->window.getSize().y/2  + 100));

  option2->rect.setSize(sf::Vector2f(100,50));
  option2->rect.setOutlineColor(sf::Color::Red);
  option2->rect.setFillColor(sf::Color::Black);
  option2->rect.setOutlineThickness(5);
  option2->rect.setPosition(sf::Vector2f( game->window.getSize().x/2 - 10 - option2->rect.getLocalBounds().width/2, game->window.getSize().y/2 + 200));


  // If it has states to switch to give them it
  option1->menState =  new TestState(this->font);
  option2->menState =  new TestState(this->font);

  // Do menuItem text settings here to make positioning relative to rectShape's
  for ( auto& m : menuItems ) {
    m.updateDisplayText();
    m.displayText.setFont(font);
    m.displayText.setCharacterSize(17);
    m.displayText.setPosition( sf::Vector2f( m.rect.getPosition().x,
					     m.rect.getPosition().y+10));
    m.displayText.setFillColor(sf::Color::White);
  }
  
  option1 = nullptr;
  option2 = nullptr;
}


void MenuState::onEvent(sf::Event event) {
  //Cycle through the possible states
  if ( (event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Down)){
    menuItems[selected].rect.setFillColor(sf::Color::Black);
    selected = (selected+1)%MENU_LENGTH;
    std::cout << "Downkey pressed, in state " << selected << std::endl;
    menuItems[selected].rect.setFillColor(sf::Color::Red);
  }
  if ( (event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Up)){
    menuItems[selected].rect.setFillColor(sf::Color::Black);
    selected++;
    selected = (selected%MENU_LENGTH + MENU_LENGTH)%MENU_LENGTH;
    menuItems[selected].rect.setFillColor(sf::Color::Red);
    
    std::cout << "Upkey pressed, in state " << selected << std::endl;
  }
}


State* MenuState::update(sf::RenderWindow& window) {

  
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ){
    
  
    return menuItems[selected].menState;
    std::cout << "Entering state" <<std::endl;
  }
  
  
  return nullptr;
  
}

void MenuState::render(sf::RenderWindow& window) {

  window.draw(hello);
  
  for (std::vector<MenuItem>::const_iterator i = menuItems.begin(); i != menuItems.end(); ++i){
    window.draw(i->rect);    
    window.draw(i->displayText);
  }
  

}





