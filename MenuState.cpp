/*
  Studio Bakemono, 2018
*/

#include "MenuState.hpp"

#include "State.hpp"
#include "Game.hpp"
#include "TestState.hpp"
#include "TransitionState.hpp"
#include "OptionsState.hpp"

#include <cmath>
#include <cstdint>


MenuState::MenuState() {
}


MenuState::~MenuState() {

}


void MenuState::updateBreath(sf::Time timePassed) {

  
  
  uint8_t alpha = (uint8_t)(
			    minBreath + (1.0+sin(timePassed.asSeconds()*breathSpeedModifier*M_PI)
					 )*(
					    maxBreath-minBreath
					    )/2.0
			    );
				  
  
  breathAlpha.a = alpha;
  
  /*
  if (isIncreasing) {
    if (breathAlpha.a + 1 < maxBreath )
      breathAlpha.a++;
    else
      isIncreasing = false;
  }
  else {
    if (breathAlpha.a - 1 > minBreath )
      breathAlpha.a--;
    else
      isIncreasing = true;

  }
*/
  

  breathFader.setFillColor(breathAlpha);
  
}
void MenuState::onEnter(Game &game) {

  //Set up the title
  hello.setString("Chimeras");
  hello.setFont(game.font);
  hello.setCharacterSize(30);
  MENU_LENGTH = 2;
  hello.setPosition(sf::Vector2f( game.window.getSize().x/2 - 10 - hello.getLocalBounds().width/2,
				  game.window.getSize().y/2 - hello.getLocalBounds().height/2 ));
  


  // Load main menu
  //if ( !

  
  backgroundTex.loadFromFile("assets/main_menu.png");
  background.setTexture(backgroundTex);

  sf::Vector2f backgroundScale = sf::Vector2f(game.WINDOW_WIDTH/background.getLocalBounds().width,
					      game.WINDOW_HEIGHT/background.getLocalBounds().height);

  
  
  background.scale(backgroundScale );
//std::cout << "Error Loading main_menu.png!" << std::endl;


  breathClock.restart();
  
  breathFader.setPosition(0,0);
  breathFader.setSize(sf::Vector2f(game.WINDOW_WIDTH, game.WINDOW_HEIGHT));
  

  //Create the menu options


  menuItems.resize(MENU_LENGTH);

  // Grab option 1 and 2 from the vector to do specific operations
  
  MenuItem* option1 = &menuItems[0];
  MenuItem* option2 = &menuItems[1];

  option1->name = "Play";
  option2->name = "Options";

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


  // If it has states to switch to give them it
  option1->menState = [](MenuState *) { return std::make_shared<TransitionState>(std::make_shared<TestState>()); };
  option2->menState = [](MenuState *) { return std::make_shared<OptionsState>(); };

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
  if ( (event.type == sf::Event::KeyPressed)  && (event.key.code == sf::Keyboard::Enter)){
    transitioning = true;
    
    std::cout << "Enter key pressed, transitioning " << selected << std::endl;
  }
  if (
    event.type == sf::Event::MouseButtonPressed
    && event.mouseButton.button == sf::Mouse::Button::Left
  ){
    sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
    for(int i = 0; i<MENU_LENGTH; i++){
      if(menuItems[i].rect.getGlobalBounds().contains(mouse)){
        selected = i;
        std::cout << "LMB clicked, transitioning to " << selected << std::endl;
        transitioning = true;
        break;
      }
    }
  }
}


std::shared_ptr<State> MenuState::update(sf::RenderWindow& window) {


  updateBreath(breathClock.getElapsedTime());
  
  if ( transitioning == true ){
    std::cout << "Entering state" <<std::endl;
    transitioning=false;
    return menuItems[selected].menState(this);
  }
  
  
  return nullptr;
  
}

void MenuState::render(sf::RenderWindow& window) {

  window.draw(background);

  window.draw(breathFader);
  
  window.draw(hello);
  
  for (std::vector<MenuItem>::const_iterator i = menuItems.begin(); i != menuItems.end(); ++i){
    window.draw(i->rect);    
    window.draw(i->displayText);
  }


}





