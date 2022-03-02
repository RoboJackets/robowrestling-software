#include <iostream>
#include <memory>
#include "screen.h"

#include <SFML/Graphics/Text.hpp>
enum Button {
	PLAY,
	EXIT,
	CONFIG,
	_NULL
};
class StartMenu : public Screen {
    private:
		std::shared_ptr<sf::RenderWindow> window_;
		std::vector<sf::Text> buttons; 
		sf::Text title;
		sf::Text play_button;
		sf::Text exit_button;
		sf::Text config_button;

		Button selected_button;
		Button pressed_button;

		int option = 0;
		const int NUM_BUTTONS = 3; 
    public:
	    StartMenu(std::shared_ptr<sf::RenderWindow> App);
	    void Init() override;
		void Draw() override;
		void ProcessInput() override;
		int Update() override;
};



