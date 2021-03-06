//
//  Vehicle.hpp
//  SimulatorSFML
//
//  Created by Samuel Arbibe on 11/12/2019.
//  Copyright © 2019 Samuel Arbibe. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <iostream>
#include <cstring>
#include <queue>

#include <SFML/Graphics.hpp>

#include "../map/Map.hpp"
#include "Settings.hpp"
#include "DataBox.hpp"

using namespace std;
using namespace sf;

enum State
{
	STOP, DRIVE, TURN, DELETE
};

typedef struct
{
	VehicleTypeOptions Type;
	string VehicleTypeName;
	string ImageDir;
	int ImageCount;
	Vector2f Size;
	vector<Texture> *Textures;
}
	VehicleType;

class Vehicle : public RectangleShape
{

  public:

	Vehicle(VehicleTypeOptions vehicleType,
	        int vehicleNumber,
	        list<Lane *> *instructionSet,
	        Map *map);
	~Vehicle();

	void Draw(RenderWindow *window);
	void Update(float elapsedTime);

	// add entities
	static Vehicle *AddVehicle(list<Lane *> *instructionSet,
	                           Map *map,
	                           VehicleTypeOptions vehicleType = SMALL_CAR,
	                           int vehicleNumber = VehicleCount + 1);

	// get
	int GetVehicleNumber() { return vehicle_number_; }
	bool GetIsActive() { return active_; }
	Lane *GetSourceLane() { return source_lane_; }
	Lane *GetTargetLane() { return dest_lane_; }
	Lane *GetCurrentLane() { return source_lane_; }
	State GetState() { return state_; }
	//Vector2f GetPosition() { return GetPosition(); }
	list<Lane *> *GetInstructionSet() { return instruction_set_; }
	static VehicleType *GetVehicleTypeByOption(VehicleTypeOptions vehicleTypeOptions);
	static Vehicle *GetVehicle(int vehicleNumber);

	// set
	void Select();
	void Unselect();

	static Vehicle *CheckSelection(Vector2f position);

	static void DeleteAllVehicles();
	static void ClearVehicles();

	static bool LoadVehicleTextures(VehicleType *vehicleType);

	static list<Vehicle *> ActiveVehicles;
	static int GetActiveVehicleCount() { return ActiveVehiclesCount; }
	static int VehicleCount;
	static Vehicle *SelectedVehicle;
	static int VehiclesToDeploy;

  private:

	State drive(float elapsedTime);
	void apply_changes(float elapsedTime);
	void transfer_vehicle(Lane *toLane);

	// A Count of vehicles due to be deleted
	static int to_be_deleted_;
	// The Count of the active running vehicles
	static int ActiveVehiclesCount;

	static VehicleType SmallCar;
	static VehicleType MediumCar;
	static VehicleType LongCar;
	static VehicleType Truck;

	// ID of this vehicle
	int vehicle_number_;
	VehicleType *vehicle_type_;

	// The movement vector of this vehicle
	Vector2f movement_vec_;

	float speed_;
	float acc_;
	float max_speed_;
	float acceleration;
	float deceleration;
	float angular_vel_;
	float time_turning_;
	bool turning_;
	bool active_;

	Vehicle *vehicle_in_front_;

	list<Lane *> *instruction_set_;

	Map *curr_map_;
	Lane *source_lane_;
	Lane *dest_lane_;
	Intersection *curr_intersection_;
	Intersection *prev_intersection_;

	State state_;

	DataBox *data_box_;
};

#endif /* Vehicle_hpp */

