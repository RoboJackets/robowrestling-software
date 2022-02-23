#include <simulator/ui/startmenu.h>

StartMenu::StartMenu(std::shared_ptr<sf::RenderWindow> App);
	    window_ = App;
		bool title_selected = false;
		bool title_pressed = false;
		bool play_selected = false;
		bool play_pressed = false;
		bool exit_selected = false;
		bool exit_pressed = false;
		bool config_selected = false;
		bool config_pressed = false;

int StartMenu::Init()
{
	title.setString("Sumo Match");
	title.setOrigin(title.getLocalBounds().width / 2,
	 title.getLocalBounds().height / 2);
	title.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);

	play_button.setString("Play");
	play_button.setOrigin(play_button.getLocalBounds().width / 2,
	 play_button.getLocalBounds().height / 2);
	play_button.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);

	exit_button.setString("Sumo Match");
	exit_button.setOrigin(exit_button.getLocalBounds().width / 2,
	 exit_button.getLocalBounds().height / 2);
	exit_button.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);

	config_button.setString("Sumo Match");
	config_button.setOrigin(config_button.getLocalBounds().width / 2,
	 config_button.getLocalBounds().height / 2);
	config_button.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);
}

StartMenu::Draw() {
	window_->clear();
	window_->draw(title);
	window_->draw(play_button);
	window_->draw(config_button);
	window_->draw(exit_button);
	window_->display();
}

StartMenu::ProcessInput() {
	sf::Event event;
	while (window_->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		} else if (event.type == sf::Event::KeyPressed) {
			switch(event.key.code) {
				case sf::Keyboard::Up:
					option += 1;
					if (option > NUM_BUTTONS) {
						option = NUM_BUTTONS;
					}
					break;
				case sf::Keyboard::Down:
					option -= 1;
					if (option < 0) {
						option = 0;
					}
					break;
			}
		}
	}

}

StartMenu::Update() {


}