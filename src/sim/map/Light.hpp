//
// Created by Samuel Arbibe on 20/02/2020.
//

#ifndef SIMULATORSFML_LIGHT_HPP
#define SIMULATORSFML_LIGHT_HPP

#include <SFML/Graphics.hpp>
#include "Road.hpp"

using namespace sf;
using namespace std;

enum LightState
{
	GREEN, ORANGE, RED
};

class Light : public RectangleShape
{
  public:

	Light(int lightNumber, int phaseNumber, Lane *parentLane);
	~Light();

	void Draw(RenderWindow *window);
	void Update(float elapsedTime);

	// get
	int GetPhaseNumber() { return phase_number_; }
	int GetLightNumber() { return light_number_; }
	Lane * GetParentLane() { return parent_lane_; }


	// set
	void SetState(LightState state) { state_ = state; }
	void UpdatePosition();

	static int LightCount;
	
  private:
	// ID of this light
	int light_number_;
	// ID of the Phase this light represents
	int phase_number_;

	// The current state of the light.
	LightState state_;
	Lane *parent_lane_;
	DataBox *data_box_;

	vector<CircleShape *> circles_;
};

#endif //SIMULATORSFML_LIGHT_HPP
