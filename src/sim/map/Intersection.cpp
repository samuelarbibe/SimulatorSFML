//
//  Intersection.cpp
//  SimulatorSFML
//
//  Created by Samuel Arbibe on 23/11/2019.
//  Copyright © 2019 Samuel Arbibe. All rights reserved.
//

#include "Intersection.hpp"

int Intersection::IntersectionCount = 0;

Intersection::Intersection(Vector2f position, int intersectionNumber)
	: RectangleShape() {

	intersection_number_ = intersectionNumber;
	position_ = position;
	width_ = 0;
	height_ = 0;
	current_vehicle_count_ = 0;
	total_vehicle_count_ = 0;
	number_of_roads_ = 0;

	this->setOrigin(width_ / 2.f, height_ / 2.f);
	this->setPosition(position_);
	this->setOutlineColor(WhiteColor);
	this->setFillColor(LaneColor);
	this->setOutlineThickness(0.f);
	this->setSize(Vector2f(width_, height_));
}

Intersection::~Intersection() {
	// every road belongs to 2 intersections
	// to avoid deleting them both, we make sure we delete it once
	for (Road *road : roads_)
	{
		if (road->GetIntersectionNumber(0) == this->intersection_number_)
		{
			delete road;
		}
	}

	if (Settings::DrawDelete)
		cout << "Intersection " << intersection_number_ << " deleted" << endl;
}

/// add a road to an intersection
Road *Intersection::AddRoad(int roadNumber, int connectionSide, float length) {
	if (!roadNumber)
	{
		roadNumber = Road::RoadCount + 1;
	}

	roads_.push_back(new Road(roadNumber,
	                          intersection_number_,
	                          connectionSide,
	                          GetPositionByConnectionSide(connectionSide),
	                          length,
	                          float(connectionSide - 1) * 90.f));

	number_of_roads_++;
	Road::RoadCount++;

	if (Settings::DrawAdded)
		std::cout << "Road " << roadNumber << " added" << endl;

	return roads_[number_of_roads_ - 1];
}

////////////////////////////////////////////////////////////
/// \brief Overload of binary operator !=
///
/// This function adds a new road connecting between 2 intersection.
/// The first intersection is this intersection, the second intersection is
/// passed through to this function.
///
/// \param roadNumber (int) - the ID of the road
/// \param connectionSide1 (int) - connection side to intersection 1
/// \param connectionSide2 (int) - connection side to intersection 2
/// \param connectedIntersection (* Intersection) - pointer to the connected intersection
///
///
/// \return a pointer to the added connecting road
///
////////////////////////////////////////////////////////////
Road *Intersection::AddConnectingRoad(int roadNumber,
                                      int connectionSide1,
                                      int connectionSide2,
                                      Intersection *connectedIntersection) {
	if (!roadNumber)
	{
		roadNumber = Road::RoadCount + 1;
	}

	roads_.push_back(new Road(roadNumber,
	                          this->intersection_number_,
	                          connectedIntersection->intersection_number_,
	                          connectionSide1,
	                          connectionSide2,
	                          this->GetPositionByConnectionSide(connectionSide1),
	                          connectedIntersection
		                          ->GetPositionByConnectionSide(connectionSide2),
	                          float(connectionSide1 - 1) * 90));

	connectedIntersection->roads_.push_back(roads_[number_of_roads_]);
	connectedIntersection->number_of_roads_++;

	number_of_roads_++;
	Road::RoadCount++;

	if (Settings::DrawAdded)
		std::cout << "Connecting Road " << roadNumber
		          << " added between intersections "
		          << this->intersection_number_ << " <--> "
		          << connectedIntersection->intersection_number_ << "" << endl;

	return roads_[number_of_roads_ - 1];
}

/// get a lane by laneNumber
Lane *Intersection::GetLane(int laneNumber) {
	Lane *temp;

	for (int i = 0; i < number_of_roads_; i++)
	{
		if ((temp = roads_[i]->GetLane(laneNumber)) != nullptr)
		{
			return temp;
		}
	}

	return nullptr;
}

/// get a road by roadNUmber
Road *Intersection::GetRoad(int roadNumber) {
	Road *temp;
	for (int i = 0; i < number_of_roads_; i++)
	{
		temp = roads_[i];
		if ((temp->GetRoadNumber()) == roadNumber)
		{
			return temp;
		}
	}

	return nullptr;
}

/// get road connected to an intersection by its connection side
Road *Intersection::GetRoadByConnectionSide(int connectionSide) {
	for (int i = 0; i < number_of_roads_; i++)
	{
		if (roads_[i]->GetConnectionSide(0) == connectionSide
			|| (roads_[i]->GetIsConnecting()
				&& roads_[i]->GetConnectionSide(1) == connectionSide))
		{
			return roads_[i];
		}

	}

	return nullptr;
}

/// add a regular lane to an intersection
Lane *Intersection::AddLane(int laneNumber,
                            int roadNumber,
                            bool isInRoadDirection) {
	Road *temp = GetRoad(roadNumber);
	Lane *l;

	l = temp->AddLane(laneNumber, isInRoadDirection);

	return l;
}

/// get the position of an intersection connection by side
Vector2f Intersection::GetPositionByConnectionSide(int connectionSide) {
	switch (connectionSide)
	{
	case UP:return Vector2f(position_.x, position_.y - height_ / 2.f);

	case RIGHT:return Vector2f(position_.x + width_ / 2.f, position_.y);

	case DOWN:return Vector2f(position_.x, position_.y + height_ / 2.f);

	case LEFT:return Vector2f(position_.x - width_ / 2.f, position_.y);

	default:return position_;
	}
}

////////////////////////////////////////////////////////////
/// \brief
///
/// This function re-assigns road position if their sturcture has been changed.
/// When a lane is added or removed for example, the whole intersection's roads
/// need to be relocated
///
////////////////////////////////////////////////////////////
void Intersection::ReAssignRoadPositions() {
	for (int i = 0; i < number_of_roads_; i++)
	{
		// if road starts from this intersection, adjust start position
		if (roads_[i]->GetIntersectionNumber(0) == this->intersection_number_)
		{
			roads_[i]->UpdateStartPosition(GetPositionByConnectionSide(roads_[i]
				                                                           ->GetConnectionSide(
					                                                           0)));
		} else
		{
			if (roads_[i]->GetIsConnecting()
				&& roads_[i]->GetIntersectionNumber(1)
					== this->intersection_number_)
			{
				// if road connects this intersection to another
				roads_[i]
					->UpdateEndPosition(GetPositionByConnectionSide(roads_[i]
						                                                ->GetConnectionSide(
							                                                1)));
			}
		}
	}
}

/// Reload the intersection after any change
void Intersection::ReloadIntersection() {
	for (Road *r : roads_)
	{
		r->ReloadRoadDimensions();
	}

	// update intersection dimensions
	Road *r1 = GetRoadByConnectionSide(1);
	Road *r2 = GetRoadByConnectionSide(2);
	Road *r3 = GetRoadByConnectionSide(3);
	Road *r4 = GetRoadByConnectionSide(4);

	if (r1 != nullptr)
		width_ = r1->GetWidth();
	else if (r3 != nullptr)
		width_ = r3->GetWidth();
	if (r2 != nullptr)
		height_ = r2->GetWidth();
	else if (r4 != nullptr)
		height_ = r4->GetWidth();

	if (r3 != nullptr && r3->GetWidth() > width_)
	{
		width_ = r3->GetWidth();
	}

	if (r4 != nullptr && r4->GetWidth() > height_)
	{
		height_ = r4->GetWidth();
	}

	this->setSize(Vector2f(width_, height_));
	this->setOrigin(width_ / 2, height_ / 2);

	ReAssignRoadPositions();
}

/// check if a road in this intersection has been selected
Lane *Intersection::CheckSelection(Vector2f position) {
	// for each intersection in map
	Lane *temp;
	for (Road *road : roads_)
	{
		// if selection found
		temp = road->CheckSelection(position);
		if (temp != nullptr)
			return temp;
	}
	return nullptr;
}

/// return the lane count in this intersection
int Intersection::GetLaneCount() {
	int sum = 0;

	for (Road *road : roads_)
	{
		sum += road->GetLaneCount();
	}

	return sum;
}

/// update
void Intersection::Update(float elapsedTime) {
	current_vehicle_count_ = 0;
	total_vehicle_count_ = 0;

	for (Road *r : roads_)
	{
		r->Update(elapsedTime);
		current_vehicle_count_ += r->GetCurrentVehicleCount();
		total_vehicle_count_ += r->GetTotalVehicleCount();
	}
}

////////////////////////////////////////////////////////////
/// \brief
///
/// This delets a given lane by its ID from its intersection.
/// function sends down the order to delete a lane to its road,
/// and if that road is empty after the deletion,
/// delete that road from the intersection
///
/// \param laneNumber (int) - ID of the lane to delete
/// \param otherIntersection (* Interection) - if lane is connecting between 2
/// intersections, a pointer to the other intersection is passed here.
///
/// \return true if successfully deleted, else false.
///
////////////////////////////////////////////////////////////
bool Intersection::DeleteLane(int laneNumber, Intersection *otherIntersection) {
	Lane *targetLane = this->GetLane(laneNumber);
	if (targetLane != nullptr)
	{
		Road *targetRoad = this->GetRoad(targetLane->GetRoadNumber());
		if (targetRoad != nullptr)
		{
			targetRoad->DeleteLane(laneNumber);
			// check if no lanes are left in road.
			// if so, delete road as well
			if (targetRoad->GetLaneCount() == 0)
			{
				auto it = find(roads_.begin(), roads_.end(), targetRoad);
				this->roads_.erase(it);

				if (otherIntersection != nullptr)
				{
					auto xt = find(otherIntersection->roads_.begin(),
					               otherIntersection->roads_.end(),
					               targetRoad);
					otherIntersection->roads_.erase(xt);
					otherIntersection->number_of_roads_--;
				}

				delete targetRoad;
				number_of_roads_--;
			}
			return true;
		}
	}
	return false;
}

/// draw the intersection and everything that belongs to it
void Intersection::Draw(RenderWindow *window) {
	(*window).draw(*this);

	for (int i = 0; i < number_of_roads_; i++)
	{
		roads_[i]->Draw(window);
	}
}
