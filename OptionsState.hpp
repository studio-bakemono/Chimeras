/*
 Studio Bakemono, 2018
 */

#pragma once

#include "State.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics.hpp>

class MenuState;


class OptionsState : public MenuState{
  public:
  
    OptionsState();
    ~OptionsState();
  
    virtual void onEnter(Game &game) override;
  
    virtual void onEvent(sf::Event event) override;
  
    virtual std::shared_ptr<State> update(sf::RenderWindow& window) override;
  
    virtual void render(sf::RenderWindow& window) override;
};
