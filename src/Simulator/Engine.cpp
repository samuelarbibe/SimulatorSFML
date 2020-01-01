//
//  Engine.cpp
//  SimulatorSFML
//
//  Created by Samuel Arbibe on 22/11/2019.
//  Copyright © 2019 Samuel Arbibe. All rights reserved.
//

#include "Engine.hpp"

int Vehicle::VehicleCount = 0;
list<Vehicle*> Vehicle::ActiveVehicles;

Engine::Engine(QWidget *Parent, const QPoint &Position, const QSize &Size) : QSFMLCanvas(Parent, Position, Size, 1000.f/MAX_FPS)
{

}

void Engine::OnInit()
{
    cout << "Setting up max speeds..." << endl;
    Vehicle::SetMaxSpeed(VehicleTypeOptions::CAR, 100.f, 1.5f);
    Vehicle::SetMaxSpeed(VehicleTypeOptions::TRUCK, 80.f, 1.f);

    cout << "Setting up weather conditions..." << endl;
    //Vehicle::SetWeatherCondition(WeatherCondition::DRY);

    map = new Map(0, Vector2f(this->width()/2, this->height()/2), this->width(), this->height());

    map->AddIntersection(0,Vector2f(this->width()/2, this->height()/2));

    map->AddIntersection(0,Vector2f(this->width()/2, this->height()/2));

    map->AddConnectingRoad(1, 1, 2, ConnectionSides::RIGHT, ConnectionSides::LEFT);

    map->AddRoad(2, 1, ConnectionSides::UP, 200);
    map->AddRoad(3, 1, ConnectionSides::DOWN, 200);

    map->AddRoad(4, 2, ConnectionSides::UP, 200);
    map->AddRoad(5, 2, ConnectionSides::DOWN, 200);


    map->AddLane(0, 1, false);
    map->AddLane(0, 1, false);
    map->AddLane(0, 1, true);
    map->AddLane(0, 1, true);

    map->AddLane(0, 2, false);
    map->AddLane(0, 2, true);

    map->AddLane(0, 3, false);
    map->AddLane(0, 3, true);

    map->AddLane(0, 4, false);
    map->AddLane(0, 4, true);

    map->AddLane(0, 5, false);
    map->AddLane(0, 5, true);
}

void Engine::input(){
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        Vehicle::AddVehicle(map->GetLane(1), map->GetLane(1), map->GetIntersection(1));
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //Vehicle::AddVehicle(inter->GetLane(2), inter->GetLane(7), inter);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //inter->GetLane(2)->SetIsBlocked(true);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //inter->GetLane(2)->SetIsBlocked(false);
    }
}

void Engine::OnUpdate()
{
    if(DRAW_FPS)cout << "FPS : " << 1.f/myTimer.interval() * 1000 << endl;
    input();
    update((myTimer.interval()/1000.f) / (float)SCALE * (float)SPEED);
    OnDraw();
}

void Engine::update(float elapsedTime)
{
    map->Update(elapsedTime);

    for (Vehicle *v : Vehicle::ActiveVehicles)
    {
        v->Update(elapsedTime);
    }

    //clear all cars to be deleted
    Vehicle::ClearVehicles();

    OnDraw();
}

void Engine::OnDraw()
{
    // Clean out the last frame
    clear(BackgroundColor);
 
    // Draw the objects
    this->map->Draw(this);

    for(Vehicle * v : Vehicle::ActiveVehicles)
    {
        v->Draw(this);
    }
}
