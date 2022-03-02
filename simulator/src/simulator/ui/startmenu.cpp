#include "simulator/ui/startmenu.h"

StartMenu::StartMenu(std::shared_ptr<sf::RenderWindow> App) {
	window_ = App;
	selected_button = PLAY;
	pressed_button = _NULL;
	Init();
}
	    

void StartMenu::Init()
{
	sf::Font font;
	font.loadFromFile("res/arial.ttf");
	title.setFont(font);
	title.setString("Sumo Match");
	title.setOrigin(title.getLocalBounds().width / 2,
	title.getLocalBounds().height / 2);
	title.setPosition(window_->getSize().x / 2, window_->getSize().y / 2);

	play_button.setFont(font);
	play_button.setString("Play");
	play_button.setOrigin(play_button.getLocalBounds().width / 2,
	play_button.getLocalBounds().height / 2);
	play_button.setPosition(window_->getSize().x / 2,10 + window_->getSize().y / 2);
	buttons.push_back(play_button);

	exit_button.setFont(font);
	exit_button.setString("Config");
	exit_button.setOrigin(exit_button.getLocalBounds().width / 2,
	exit_button.getLocalBounds().height / 2);
	exit_button.setPosition(window_->getSize().x / 2,20 + window_->getSize().y / 2);
	buttons.push_back(config_button);

	config_button.setFont(font);
	config_button.setString("Exit");
	config_button.setOrigin(config_button.getLocalBounds().width / 2,
	config_button.getLocalBounds().height / 2);
	config_button.setPosition(window_->getSize().x / 2,30 + window_->getSize().y / 2);
	buttons.push_back(exit_button);
}

void StartMenu::Draw() {
	window_->clear();
	window_->draw(title);
	for (auto it = std::begin(buttons); it != std::end(buttons); it++) {
		window_->draw(*it);
	}
	window_->display();
}

void StartMenu::ProcessInput() {
	sf::Event event;
	while (window_->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window_->close();
		} else if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
				case sf::Keyboard::Up:
					option += 1;
					if (option > NUM_BUTTONS - 1) {
						option = NUM_BUTTONS - 1;
					}
					selected_button = static_cast<Button>(option);
					break;
				case sf::Keyboard::Down:
					option -= 1;
					if (option < 0) {
						option = 0;
					}
					selected_button = static_cast<Button>(option); 
					break;
				case sf::Keyboard::Escape:
					window_->close();
					break;
				case sf::Keyboard::Return:
					pressed_button = selected_button;
					break;
				default:
					break;
			}
		}
	}

}

int StartMenu::Update() {
	for (int i = 0; i < buttons.size(); i++) {
		if (i == option) {
			buttons[i].setFillColor(sf::Color::Blue);
		} else {
			buttons[i].setFillColor(sf::Color::White);
		}
	}	
	if (pressed_button == PLAY) {
		return -1;
	} else {
		return 0;
	}
}