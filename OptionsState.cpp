/*
 Studio Bakemono, 2018
 */


#include "MenuState.hpp"
#include "Game.hpp"
#include "TestState.hpp"
#include "TransitionState.hpp"
#include "OptionsState.hpp"
#include "GameOverState.hpp"

OptionsState::OptionsState() {
}


OptionsState::~OptionsState() {
  
}


void OptionsState::onEnter(Game &game) {
  
  //Set up the title
  hello.setString("Chimeras");
  hello.setFont(game.font);
  hello.setCharacterSize(30);
  MENU_LENGTH = 3;
  hello.setPosition(sf::Vector2f( game.window.getSize().x/2 - 10 - hello.getLocalBounds().width/2,
                                 game.window.getSize().y/2 - hello.getLocalBounds().height/2 ));
  
  //Create the menu options
  
  
  menuItems.resize(MENU_LENGTH);
  
  // Grab option 1 and 2 from the vector to do specific operations
  
  MenuItem* option1 = &menuItems[0];
  MenuItem* option2 = &menuItems[1];
  MenuItem* option3 = &menuItems[2];
  
  option1->name = "Options";
  option2->name = "Play";
  option3->name = "Temporary Game Over Test";
  
  option1->rect.setSize(sf::Vector2f(100,50));
  option1->rect.setOutlineColor(sf::Color::Red);
  option1->rect.setFillColor(sf::Color::Red);
  option1->rect.setOutlineThickness(5);
  option1->rect.setPosition(sf::Vector2f( game.window.getSize().x/2 - 10 - option1->rect.getLocalBounds().width/2, game.window.getSize().y/2  + 100));
  
  option2->rect.setSize(sf::Vector2f(100,50));
  option2->rect.setOutlineColor(sf::Color::Red);
  option2->rect.setFillColor(sf::Color::Black);
  option2->rect.setOutlineThickness(5);
  option2->rect.setPosition(sf::Vector2f( game.window.getSize().x/2 - 10 - option2->rect.getLocalBounds().width/2, game.window.getSize().y/2 + 200));


  option3->rect.setSize(sf::Vector2f(100,50));
  option3->rect.setOutlineColor(sf::Color::Red);
  option3->rect.setFillColor(sf::Color::Black);
  option3->rect.setOutlineThickness(5);
  option3->rect.setPosition(sf::Vector2f( game.window.getSize().x/2 - 10 - option3->rect.getLocalBounds().width/2 - 200, game.window.getSize().y/2 + 250));
  
  
  // If it has states to switch to give them it
  option1->menState = [](State *) { return std::make_shared<OptionsState>(); };
  option2->menState = [](State *) { return std::make_shared<TransitionState> (std::make_shared<TestState>()); };
  option3->menState = [](State *) { return std::make_shared<GameOverState>("Game over test works!"); };
  
  // Do menuItem text settings here to make positioning relative to rectShape's
  for ( auto& m : menuItems ) {
    m.updateDisplayText();
    m.displayText.setFont(game.font);
    m.displayText.setCharacterSize(17);
    m.displayText.setPosition( sf::Vector2f( m.rect.getPosition().x,
                                            m.rect.getPosition().y+10));
    m.displayText.setFillColor(sf::Color::White);
  }
  
  option1 = nullptr;
  option2 = nullptr;
}


void OptionsState::onEvent(sf::Event event) {
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
  
  if ( (event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Enter)){
    transitioning = true;
    
    std::cout << "Enter key pressed, transitioning " << selected << std::endl;
  }
  
}

std::shared_ptr<State> OptionsState::update(sf::RenderWindow& window) {
  
  
  if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)  && (transitioning == true)){
    std::cout << "Entering state" <<std::endl;
    return menuItems[selected].menState(this);
  }
  
  
  return nullptr;
  
}

void OptionsState::render(sf::RenderWindow& window) {
  
  window.draw(hello);
  
  for (std::vector<MenuItem>::const_iterator i = menuItems.begin(); i != menuItems.end(); ++i){
    window.draw(i->rect);
    window.draw(i->displayText);
  }
  
  
}
