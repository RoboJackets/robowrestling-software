#include <simulator/sim.h>

#include <iostream>
#include <string>
#include "imgui.h"



#include <chrono>
#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


void draw_field() {
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)); //make a rectangle to add background color
    background.setFillColor(sf::Color(141, 158, 196));
    background.setPosition(0, 0);
    window_->draw(background);
    sf::CircleShape dohyo; //create the circle that represents the dohyo. Input is radius
    dohyoRadius = 75 * vis_scale; 
    dohyo.setRadius(CMToPixel(dohyoRadius));
    dohyo.setFillColor(sf::Color(0, 0, 0)); //color the dohyo black
    dohyo.setOutlineThickness(vis_scale*2.f); //give dohyo an outline
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); //make the outline white
    dohyo.setPosition((EFFECTIVE_CENTER_X)-CMToPixel(dohyoRadius), (EFFECTIVE_CENTER_Y)-CMToPixel(dohyoRadius));
    window_->draw(dohyo);
    float lineWidth = CMToPixel(2) * vis_scale; 
    float lineHeight = CMToPixel(20) * vis_scale; 
    float spacing = CMToPixel(10) * vis_scale; 
    sf::RectangleShape start_line1(sf::Vector2f(lineWidth, lineHeight));
    start_line1.setFillColor(sf::Color(255, 69, 0));
    start_line1.setPosition(EFFECTIVE_CENTER_X - spacing - lineWidth, EFFECTIVE_CENTER_Y - lineHeight / 2);
    window_->draw(start_line1);
    sf::RectangleShape start_line2(sf::Vector2f(lineWidth, lineHeight));
    start_line2.setFillColor(sf::Color(255, 69, 0));
    start_line2.setPosition(EFFECTIVE_CENTER_X + spacing, EFFECTIVE_CENTER_Y - lineHeight / 2);
    window_->draw(start_line2);
}

void draw_robot(std::shared_ptr<Robot> robot) {
    sf::Sprite sprite(robot_texture);
    sprite.setScale(vis_scale*robot->width_/50.0, vis_scale*robot->length_/50.0);
    double shift_magnitude = vis_scale*sqrt(pow(robot->width_/2, 2) + pow(robot->length_/2, 2));
    double homogenous_x = vis_scale*(robot->x_pos_ - WINDOW_WIDTH/2) + WINDOW_WIDTH/2 + shift_magnitude*cos(robot->angle_ - .75 * M_PI);
    double homogenous_y = vis_scale*(robot->y_pos_ - WINDOW_HEIGHT/2) + WINDOW_HEIGHT/2 + shift_magnitude*sin(robot->angle_ - .75 * M_PI);
    sprite.setPosition(homogenous_x, homogenous_y);
    sprite.setRotation(robot->angle_*180/M_PI);
    window_->draw(sprite);
}	

void update() {
	sf::Event event;
    window_->clear(sf::Color::White); // clear the window with white color
    while (window_->pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window_->close();
        } 
    }

    // need to redraw things
    draw_field();
    draw_robot(robot1_);
    draw_robot(robot2_);
    window_->display();
}

void DrawRigidBody(RigidBody2d &body) {
    BoxShape shape = body.GetShape();
    double width = CMToPixel(shape.width * 100.0) * vis_scale; 
    double height = CMToPixel(shape.height * 100.0) * vis_scale;
    auto [x, y] = body.GetPos(); 
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f((x + EFFECTIVE_ZERO_X) - (width / 2),(EFFECTIVE_HEIGHT - y) - (height / 2))); 
    rect.setFillColor(sf::Color::Green); 
    window_->draw(rect); 
}

int main(int argc, char *argv[]) { // ./sim.sw (r1 x left of 0) (r1 y up of 0) (r1 angle in rad cw) (r2 x right of 0) (r2 y down of 0) (r2 angle in rad cw) (duration for sim: 0 = realtime elapsed)
    sf::Vertex xAxis[] = {
        sf::Vertex(sf::Vector2f(0,EFFECTIVE_CENTER_Y)),
        sf::Vertex(sf::Vector2f(WINDOW_WIDTH, EFFECTIVE_CENTER_Y))
    };

    sf::Vertex yAxis[] = {
        sf::Vertex(sf::Vector2f(EFFECTIVE_CENTER_X, 0)),
        sf::Vertex(sf::Vector2f(EFFECTIVE_CENTER_X, WINDOW_HEIGHT))
    };
    
    window_ = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sim");
    _manager = std::make_shared<ImguiManager>(2);
    _fpsPane = std::make_shared<Pane>(1180*vis_scale, 0, 100*vis_scale, 25*vis_scale, "FPS");
    _bottomPane = std::make_shared<Pane>(300 * vis_scale, 420 * vis_scale, 980 * vis_scale, 300 * vis_scale, "Logs");
    _leftPane = std::make_shared<Pane>(0, 0, 300*vis_scale, 720 * vis_scale, "Test");
    _fpsPane->SetOpacity(0.35);
    _fpsPane->SetFlags(ImGuiWindowFlags_NoDecoration);
    _fpsWidget = std::make_shared<FPSWidget>();
    _qWidget = std::make_shared<QuickWidget>(); 
    _qWidget->SetRenderCallback([](){
        ImVec2 pos = ImGui::GetIO().MousePos;
        ImGui::Text("Mouse: (%.2f, %.2f)", pos.x, pos.y);
    });
    _qWidget->SetGetNameCallback([](){
        return "Mouse Pos";
    });
    _qWidget->SetActivatedCallback([](){
        return true; 
    });
    _manager->AddPane(_fpsPane);
    _manager->AddPane(_leftPane);
    _manager->AddPane(_bottomPane);
    _leftPane->AddWidget(_qWidget);
    _fpsPane->AddWidget(_fpsWidget);
    window_->setFramerateLimit(60);

    sf::Clock clock;
    sf::CircleShape shape(100.f);

    BoxShape boxShape; 
    boxShape.width = 0.2; 
    boxShape.height = 0.2; 
    boxShape.mass = 1; 
    boxShape.momentOfInertia = 0;

    RigidBody2d body(100 * vis_scale, 100 * vis_scale, boxShape);

    Dohyo dohyo(790 - 200 , 10, 200); 

    shape.setFillColor(sf::Color::Green);
    shape.setPosition(EFFECTIVE_CENTER_X - 100, EFFECTIVE_CENTER_Y - 100);
    while (window_->isOpen()) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            _manager->ProcessEvent(event); 
            if (event.type == sf::Event::Closed) {
                window_->close();
            }
        }

        
        window_->clear();
        sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        background.setFillColor(sf::Color(141, 158, 196));
        background.setPosition(0, 0);
        window_->draw(background); 
        dohyo.Render(*window_, vis_scale);  
        window_->draw(yAxis, 2, sf::Lines);
        window_->draw(xAxis, 2, sf::Lines);

        _manager->Render(clock, *window_);
        window_->display();
    }


	return 0;
}


