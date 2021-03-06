//
// Created by Samuel Arbibe on 20/02/2020.
//


#include "Light.hpp"

int Light::LightCount = 0;

Light::Light(int lightNumber, int phaseNumber, Lane *parentLane) {
	parent_lane_ = parentLane;
	phase_number_ = phaseNumber;
	light_number_ = lightNumber;
	state_ = RED;

	circles_.push_back(new CircleShape());
	circles_.push_back(new CircleShape());
	circles_.push_back(new CircleShape());

	this->setOutlineColor(Color(169, 169, 169, 255));
	this->setOutlineThickness(4.f);

	UpdatePosition();

	data_box_ = new DataBox(this->getPosition());
	data_box_->AddData("ID", light_number_);
	data_box_->AddData("Phase", phase_number_);
	data_box_->AddData("State", state_);
}

Light::~Light() {
	delete data_box_;

	if (Settings::DrawDelete)
		cout << "Light " << light_number_ << " deleted" << endl;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Function makes sure a light is always on the side of it's parent road.
/// when a road changes position, this light is moved accordingly
///
////////////////////////////////////////////////////////////
void Light::UpdatePosition() {
	Vector2f lanePos = parent_lane_->GetEndPosition();
	float direction = parent_lane_->GetDirection() - 180;

	Transform t;
	t.rotate(direction - 90);
	float margin = parent_lane_->getSize().x / 2 + 30;
	t.scale(margin, margin);
	Vector2f sideVector = t.transformPoint(Settings::BaseVec);

	t = Transform();
	t.rotate(direction);
	t.scale(20, 20);
	Vector2f marginVector = t.transformPoint(Settings::BaseVec);
	Vector2f position = lanePos + sideVector + marginVector;

	direction -= 180;

	this->setSize(Vector2f(40, 100));
	this->setOrigin(getSize().x / 2, 0);
	this->setPosition(position);
	this->setFillColor(Color::Black);
	this->setRotation(direction);

	float radius = this->getSize().x / 2 - 7;

	Vector2f basePos = this->getPosition();

	t = Transform();
	t.rotate(direction - 180);
	// set axis relative to basePos and direction
	Vector2f yDir = t.transformPoint(Settings::BaseVec);

	// set location relative to new axis
	Vector2f yMargin = Vector2f(radius * 2 + 7, radius * 2 + 7);
	t = Transform();
	t.scale(yMargin);
	yMargin = t.transformPoint(yDir);

	t = Transform();
	t.scale(0.5, 0.5);

	Vector2f first = basePos + t.transformPoint(yMargin);

	circles_[0]->setOrigin(radius, radius);
	circles_[0]->setFillColor(Color::Black);
	circles_[0]->setPosition(first);
	circles_[0]->setRadius(radius);

	circles_[1]->setOrigin(radius, radius);
	circles_[1]->setFillColor(Color::Black);
	circles_[1]->setPosition(first + yMargin);
	circles_[1]->setRadius(radius);

	circles_[2]->setOrigin(radius, radius);
	circles_[2]->setFillColor(Color::Black);
	circles_[2]->setPosition(first + yMargin + yMargin);
	circles_[2]->setRadius(radius);
}

/// update
void Light::Update(float elapsedTime) {
	circles_[0]->setFillColor(Color::Black);
	circles_[1]->setFillColor(Color::Black);
	circles_[2]->setFillColor(Color::Black);

	switch (state_)
	{
	case RED:circles_[0]->setFillColor(Color::Red);
		break;
	case ORANGE:circles_[1]->setFillColor(Color::Yellow);
		break;
	case GREEN:circles_[2]->setFillColor(Color::Green);
		break;
	}

	if (Settings::DrawLightDataBoxes)
		data_box_->SetData("State", state_);
}

/// draw
void Light::Draw(RenderWindow *window) {
	window->draw(*this);

	for (int i = 0; i < 3; i++)
	{
		window->draw(*circles_[i]);
	}

	if (Settings::DrawLightDataBoxes)
		data_box_->Draw(window);
}




