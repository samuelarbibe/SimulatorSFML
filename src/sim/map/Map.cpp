//
// Created by Samuel Arbibe on 28/12/2019.
//

#include <QStringList>
#include "Map.hpp"

int Map::MapCount = 0;

Map::Map(int mapNumber, int width, int height) {
	if (mapNumber == 0)
	{
		mapNumber = ++MapCount;
	}
	map_number_ = mapNumber;
	width_ = width;
	height_ = height;
	SelectedLane = nullptr;
	current_phase_index_ = 0;
	number_of_cycles_ = 0;
	number_of_intersections_ = 0;
}

Map::~Map() {
	for (Intersection *inter : intersections_)
	{
		delete inter;
	}

	for (Route *route : routes_)
	{
		delete route;
	}

	for (Cycle *cycle : cycles_)
	{
		delete cycle;
	}

	Route::RouteCount = 0;
	Lane::LaneCount = 0;
	Road::RoadCount = 0;
	Phase::PhaseCount = 0;
	Cycle::CycleCount = 0;
	Intersection::IntersectionCount = 0;

	if (Settings::DrawDelete)
		cout << "map " << map_number_ << " deleted" << endl;
}

/// add an intersection to the map
Intersection *Map::AddIntersection(int intersectionNumber, Vector2f position) {
	SelectedLane = nullptr;

	if (!intersectionNumber)
	{
		intersectionNumber = Intersection::IntersectionCount + 1;
	}

	intersections_.push_back(new Intersection(position, intersectionNumber));

	number_of_intersections_++;
	Intersection::IntersectionCount++;

	if (Settings::DrawAdded)
		std::cout << "Intersection " << intersectionNumber << " added" << endl;

	return intersections_[number_of_intersections_ - 1];
}

/// add a road to a specific intersection
Road *Map::AddRoad(int roadNumber,
                   int intersectionNumber,
                   int connectionSide,
                   float length) {
	SelectedLane = nullptr;

	Intersection *temp = GetIntersection(intersectionNumber);
	Road *tempRoad = nullptr;

	if (temp)
	{
		tempRoad = temp->AddRoad(roadNumber, connectionSide, length);
	}

	this->ReloadMap();

	return tempRoad;
}

/// add a lane to a specific road
Lane *Map::AddLane(int laneNumber, int roadNumber, bool isInRoadDirection) {
	SelectedLane = nullptr;

	Road *tempRoad = GetRoad(roadNumber);
	Intersection *temp = nullptr;
	Lane *tempLane = nullptr;

	if (tempRoad)
	{
		temp = GetIntersection(tempRoad->GetIntersectionNumber());
	}

	if (temp)
	{
		tempLane = temp->AddLane(laneNumber, roadNumber, isInRoadDirection);
	}

	this->ReloadMap();

	return tempLane;
}

/// add a cycle of phases and attach it to an intersecion
Cycle *Map::AddCycle(int cycleNumber, int intersectionNumber) {
	if (cycleNumber == 0)
	{
		cycleNumber = Cycle::CycleCount + 1;
	}

	Intersection *inter = nullptr;

	if (intersectionNumber != 0)
	{
		inter = GetIntersection(intersectionNumber);
	}

	Cycle *temp = new Cycle(cycleNumber, inter);
	cycles_.push_back(temp);

	++Cycle::CycleCount;
	++number_of_cycles_;

	cout << "Cycle number " << cycleNumber << " added successfully" << endl;

	return temp;

	cout << "could not add cycle as intersection " << intersectionNumber
	     << " wasnt found." << endl;

	return nullptr;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Creates a new road connecting between 2 given intersections
///
/// \param roadNumber (int) - the ID of the road to be added.
/// \param intersectionNumber1 (int) - ID of the first intersection
/// \param intersectionNumber2 (int) - ID of the second intersection
///
/// \return the connecting road added
///
////////////////////////////////////////////////////////////
Road *Map::AddConnectingRoad(int roadNumber,
                             int intersectionNumber1,
                             int intersectionNumber2) {
	SelectedLane = nullptr;

	Intersection *inter1 = GetIntersection(intersectionNumber1);
	Intersection *inter2 = GetIntersection(intersectionNumber2);

	if (inter1 == nullptr || inter2 == nullptr)
	{
		cerr << "one of the given intersections was not found..." << endl;
		return nullptr;
	}

	// if intersection do not align on one of the axis, return error
	if ((int(inter1->getPosition().x) != int(inter2->getPosition().x) &&
		int(inter1->getPosition().y) != int(inter2->getPosition().y))
		|| (int(inter1->getPosition().x) == int(inter2->getPosition().x) &&
			int(inter1->getPosition().y) == int(inter2->getPosition().y)))
	{
		cerr << "the intersections must align on one of the axis" << endl;
		return nullptr;
	}

	pair<ConnectionSides, ConnectionSides> connections;
	connections =
		AssignConnectionSides(inter1->getPosition(), inter2->getPosition());

	Road *temp = inter1->AddConnectingRoad(roadNumber,
	                                       connections.first,
	                                       connections.second,
	                                       inter2);

	this->ReloadMap();
	return temp;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Creates a new route between 2 given lanes
///
/// \param from (int) - the source lane
/// \paramto (int) - the target lane
///
/// \return a pointer to the created route
///
////////////////////////////////////////////////////////////
Route *Map::AddRoute(int from, int to) {
	Lane *fromLane = GetLane(from);
	Lane *toLane = GetLane(to);

	if (fromLane != nullptr && toLane != nullptr)
	{
		Route *r = new Route(fromLane, toLane);
		routes_.emplace_back(r);

		if (Settings::DrawAdded)
			cout << "Route added from " << r->FromLane->GetLaneNumber()
			     << " to " << r->ToLane->GetLaneNumber() << endl;
		return r;
	} else
	{
		cout
			<< "could not create possible route, as one of the roads was not found"
			<< endl;
		return nullptr;
	}
}

/// add a phase to the mac
Phase *Map::AddPhase(int phaseNumber, int cycleNumber, float cycleTime) {

	Cycle *cycle = GetCycle(cycleNumber);
	Phase *temp = nullptr;

	if (cycle != nullptr)
	{
		if ((temp = cycle->AddPhase(phaseNumber, cycleTime)) != nullptr)
		{
			return temp;
		}
	}

	cout << "Could not add phase as the given cycle doesnt exist." << endl;

	return nullptr;
}

/// assign a light to a phase to attach to road
Light *Map::AddLight(int lightNumber, int phaseNumber, int parentLaneNumber) {
	Light *temp = nullptr;
	Phase *myPhase = GetPhase(phaseNumber);
	Lane *parentLane = GetLane(parentLaneNumber);

	// assign position relative to parent road
	if (myPhase != nullptr && parentLane != nullptr)
	{
		temp = myPhase->AddLight(lightNumber, parentLane);
		if (Settings::DrawAdded)
			cout << "light " << temp->GetLightNumber() << " added to phase "
			     << phaseNumber << endl;
		return temp;
	}

	cout << "could not add light as phase or parent lane don't exist" << endl;
	return temp;
}

/// set the phase time of a given phase
bool Map::SetPhaseTime(int phaseNumber, float phaseTime) {
	Phase *phase = GetPhase(phaseNumber);

	if (phase != nullptr)
	{
		phase->SetCycleTime(phaseTime);
		cout << "Phase time of phase " << phaseNumber << " successfully set."
		     << endl;
		return true;
	}

	cout << "Could not set phase time as phase doesnt exist." << endl;
	return false;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Assign a lane to a phase, to make the lane depend on
/// the phase status.
///
/// \param phaseNumber (int) - the phase ID
/// \param laneNumber (int) - the lane ID to assign to the phase
///
/// \return true if successful, else false
///
////////////////////////////////////////////////////////////
bool Map::AssignLaneToPhase(int phaseNumber, int laneNumber) {
	Phase *temp = GetPhase(phaseNumber);
	Lane *lane = GetLane(laneNumber);

	if (temp != nullptr && lane != nullptr)
	{
		temp->AddLane(lane);
		if (Settings::DrawAdded)
			cout << "lane " << lane->GetLaneNumber()
			     << " added to phase " << temp->GetPhaseNumber() << endl;
		return true;
	}
	cout << "could not add lane to phase as phase or lane don't exist." << endl;
	return false;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Removes a route by a lane number/
/// If the given lane is a part of sum routes, as source or as target,
/// delete it from the routes array.
/// This function is when a lane is deleted
///
/// \param laneNumber (int) - the lane to remove the routes including it
///
/// \return true if sucessfull, else false
///
////////////////////////////////////////////////////////////
bool Map::RemoveRouteByLaneNumber(int laneNumber) {
	Lane *laneToRemove = GetLane(laneNumber);

	if (laneToRemove != nullptr)
	{
		auto it = routes_.begin();

		// while there are cars to delete;
		while (it != routes_.end())
		{
			// if is to be deleted
			if ((*it)->FromLane->GetLaneNumber() == laneNumber ||
				(*it)->ToLane->GetLaneNumber() == laneNumber)
			{
				Route *temp = (*it);
				int routeNumber = temp->GetRouteNumber();
				it = routes_.erase(it);

				delete temp;

				if (Settings::DrawActive)
					cout << "route " << routeNumber << " deleted." << endl;
			} else
			{
				it++;
			}
		}

		return true;
	} else
	{
		//cout << "could not delete this route. the deleted lane could not be found." << endl;
		return false;
	}

}

/// remove a lane from the control of a phase
bool Map::UnassignLaneFromPhase(int laneNumber) {

	Lane *lane = GetLane(laneNumber);

	if (lane->GetPhaseNumber() != 0)
	{
		if (lane != nullptr)
		{
			Phase *phase = GetPhase(lane->GetPhaseNumber());

			if (phase->UnassignLane(lane))
			{
				return true;
			}

		} else
		{
			cout
				<< "could not Unassign lane from phase, as lane does not belong to any phase"
				<< endl;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Finds all the starting lanes and assign them to the starting_lane array.
/// A starting lane is one that its road is not connecting,
/// and it is against the road direction.
///
////////////////////////////////////////////////////////////
void Map::FindStartingLanes() {
	// for a lane to be a starting lane, it has to be in a non-connecting road,
	// and it has to have isInRoadDirection = false;
	starting_lanes_.clear();

	for (Intersection *inter : intersections_)
	{
		for (Road *road  : *inter->GetRoads())
		{
			if (!road->GetIsConnecting())
			{
				for (Lane *lane : *road->GetLanes())
				{
					if (!lane->GetIsInRoadDirection())
					{
						starting_lanes_.push_back(lane);
					}
				}
			}
		}
	}
}

/// returns a possible starting lane
Lane *Map::GetPossibleStartingLane() {
	if (starting_lanes_.empty())
		return nullptr;
	int randomIndex = rand() % starting_lanes_.size();
	return starting_lanes_[randomIndex];
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Selects all the routes where a vehicle is about to pass through
///
/// \param instructionSet (list<Lane *>) - a list of the lanes the vehicle is
/// going to pass through
///
////////////////////////////////////////////////////////////
void Map::SelectRoutesByVehicle(list<Lane *> *instructionSet) {
	Route *r = nullptr;
	std::list<Lane *>::const_iterator to = instructionSet->begin();
	std::list<Lane *>::const_iterator from = to;
	to++;
	for (; to != instructionSet->end(); ++to)
	{
		r = GetRouteByStartEnd((*from)->GetLaneNumber(),
		                       (*to)->GetLaneNumber());
		if (r != nullptr)
		{
			selected_routes_.push_back(r);
			r->SetSelected(true);
		}
		from = to;
	}
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Creates a random track composed of a chain of routes
///
/// \return a list of lane, that will act as an instruction
/// set for a vehicle
///
////////////////////////////////////////////////////////////
list<Lane *> *Map::GenerateRandomTrack() {
	// find a random starting point
	Lane *l = GetPossibleStartingLane();
	if (l == nullptr)
	{
		cout << "no starting lanes available." << endl;
		return nullptr;
	}
	// find a starting route from starting lane
	Route *r = GetPossibleRoute(l->GetLaneNumber());

	if (r == nullptr)
	{
		cout << "no routes available. please add them to the map" << endl;
		return nullptr;
	}

	// while new routes to append are available
	// new routes will be searched starting from the previous route end
	list<Lane *> *track = new list<Lane *>();
	Lane *lastLane = nullptr;

	while (r != nullptr)
	{
		track->push_back(r->FromLane);
		lastLane = r->ToLane;
		r = GetPossibleRoute(r->ToLane->GetLaneNumber());
	}
	if (lastLane != nullptr)
	{
		track->push_back(lastLane);
	}

	return track;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Return a random possible route that sources from a given lane
///
/// \param fromLane (int) - source lane ID
///
/// \return pointer to a randomaly chosen possible route
///
////////////////////////////////////////////////////////////
Route *Map::GetPossibleRoute(int fromLane) {
	Lane *myLane = GetLane(fromLane);
	vector<Route *> possibleRoutes;

	if (myLane != nullptr)
	{
		for (Route *r : routes_)
		{
			if (r->FromLane->GetLaneNumber() == myLane->GetLaneNumber())
			{
				possibleRoutes.push_back(r);
			}
		}
	}
	if (possibleRoutes.empty())
	{
		return nullptr;
	}
	int randomIndex = rand() % possibleRoutes.size();
	return possibleRoutes[randomIndex];
}

////////////////////////////////////////////////////////////
/// \brief
///
/// return a route that starts and ends from given lanes
///
/// \param from (int) - source lane ID
/// \param to (int) - target lane ID
///
/// \return a pointer to a corresponding route
///
////////////////////////////////////////////////////////////
Route *Map::GetRouteByStartEnd(int from, int to) {
	for (Route *r : routes_)
	{
		if (r->FromLane->GetLaneNumber() == from &&
			r->ToLane->GetLaneNumber() == to)
		{
			return r;
		}
	}
	return nullptr;
}

/// get intersection by intersectionNumber
Intersection *Map::GetIntersection(int intersectionNumber) {
	Intersection *temp;

	for (Intersection *inter : intersections_)
	{
		if ((temp = inter)->GetIntersectionNumber() == intersectionNumber)
		{
			return temp;
		}
	}

	cout << "error : intersection not found in map..." << endl;

	return nullptr;
}

/// get intersection by lane number
vector<Intersection *> Map::GetIntersectionByLaneNumber(int laneNumber) {
	Lane *l = this->GetLane(laneNumber);
	Road *r = this->GetRoad(l->GetRoadNumber());

	vector<Intersection *> retVal;

	if (r->GetIsConnecting())
	{
		retVal.push_back(this->GetIntersection(r->GetIntersectionNumber(1)));
	}
	retVal.push_back(this->GetIntersection(r->GetIntersectionNumber(0)));
	return retVal;
}

/// get road by roadNumber
Road *Map::GetRoad(int roadNumber) {
	Road *temp;

	for (Intersection *inter : intersections_)
	{
		if ((temp = inter->GetRoad(roadNumber)) != nullptr)
		{
			return temp;
		}
	}

	cout << "error : road not found in map..." << endl;

	return nullptr;
}

/// get lane by lane number
Lane *Map::GetLane(int laneNumber) {
	Lane *temp;

	for (Intersection *inter : intersections_)
	{
		if ((temp = inter->GetLane(laneNumber)) != nullptr)
		{
			return temp;
		}
	}

	cout << "error : lane not found in map..." << endl;

	return nullptr;
}

// get cycle by cycle number
Cycle *Map::GetCycle(int cycleNumber) {

	for (Cycle *cycle : cycles_)
	{
		if (cycle->GetCycleNumber() == cycleNumber)
		{
			return cycle;
		}
	}

	cout << "error : lane not found in map..." << endl;

	return nullptr;
}

/// get phase by phase number
Phase *Map::GetPhase(int phaseNumber) {

	for (Cycle *c : cycles_)
	{
		for (Phase *p : *c->GetPhases())
		{
			if (p->GetPhaseNumber() == phaseNumber)
			{
				return p;
			}
		}
	}

	cout << "error : phase not found in map..." << endl;
	return nullptr;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// return the according connection sides to the given intersection positions.
///
/// \param pos1 (int) - intersection 1 position
/// \param pos2 (int) - intersection 2 position
///
/// \return a pair of connection sides
///
////////////////////////////////////////////////////////////
pair<ConnectionSides, ConnectionSides> Map::AssignConnectionSides(Vector2f pos1,
                                                                  Vector2f pos2) {
	ConnectionSides con1, con2;
	if (pos1.x > pos2.x)
	{
		con1 = ConnectionSides::LEFT;
		con2 = ConnectionSides::RIGHT;
	} else if (pos1.x < pos2.x)
	{
		con1 = ConnectionSides::RIGHT;
		con2 = ConnectionSides::LEFT;
	} else if (pos1.y > pos2.y)
	{
		con1 = ConnectionSides::UP;
		con2 = ConnectionSides::DOWN;
	} else if (pos1.y < pos2.y)
	{
		con1 = ConnectionSides::DOWN;
		con2 = ConnectionSides::UP;
	}

	pair<ConnectionSides, ConnectionSides> connections(con1, con2);
	return connections;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// check if given position is inside the bounds of a lane object
///
/// \param position (int) - the mouse position
///
/// \return a pointer to a selected lane. nullptr if none selected
///
////////////////////////////////////////////////////////////
Lane *Map::CheckSelection(Vector2f position) {
	// for each intersection in map
	Lane *temp;
	for (Intersection *inter : intersections_)
	{
		// if selection found
		temp = inter->CheckSelection(position);
		if (temp != nullptr)
			return temp;
	}
	return nullptr;
}

/// Reload all intersection in this map
void Map::ReloadMap() {

	// unselect all the selected lanes
	UnselectAll();

	for (Intersection *i : intersections_)
	{
		i->ReloadIntersection();
	}

	for (Cycle *c : cycles_)
	{
		c->ReloadCycle();
	}

	for (Route *r : routes_)
	{
		r->ReloadRoute();
	}

	FindStartingLanes();
}

/// update, for future use
void Map::Update(float elapsedTime) {
	for (Intersection *i : intersections_)
	{
		i->Update(elapsedTime);
	}

	for (Cycle *c : cycles_)
	{
		c->Update(elapsedTime);
	}
}

/// select all the lanes that were assigned to a given phase
void Map::SelectLanesByPhase(int phaseNumber) {
	Phase *p = GetPhase(phaseNumber);

	if (p != nullptr)
	{
		UnselectAll();

		for (Lane *l : *p->GetAssignedLanes())
		{
			selected_lanes_.push_back(l);
			l->Select();
		}
	}
}

/// unselect al selected items
void Map::UnselectAll() {
	// unselect selected lane
	if (SelectedLane != nullptr)
	{
		SelectedLane->Unselect();
		SelectedLane = nullptr;
	}

	for (Lane *l : selected_lanes_)
	{
		l->Unselect();
	}

	for (Route *r : selected_routes_)
	{
		r->SetSelected(false);
	}

	selected_lanes_.clear();
	selected_routes_.clear();
}

/// return road count in this map
int Map::GetRoadCount() {
	int sum = 0;

	for (Intersection *inter : intersections_)
	{
		sum += inter->GetRoadCount();
	}

	return sum;
}

/// return lane count int this map
int Map::GetLaneCount() {
	int sum = 0;

	for (Intersection *inter : intersections_)
	{
		sum += inter->GetLaneCount();
	}

	return sum;
}

/// return a vector of all the existing lanes
vector<Phase *> *Map::GetPhases() {
	vector<Phase *> *phases = new vector<Phase *>();

	for (Cycle *cycle : cycles_)
	{
		for (Phase *p : *cycle->GetPhases())
		{
			phases->push_back(p);
		}
	}

	return phases;
}

/// return a vector of all the existing lanes
vector<Lane *> *Map::GetLanes() {
	vector<Lane *> *lanes = new vector<Lane *>();

	for (Intersection *inter : intersections_)
	{
		for (Road *road : *inter->GetRoads())
		{
			for (Lane *lane : *road->GetLanes())
			{
				lanes->push_back(lane);
			}
		}
	}

	return lanes;
}

/// return a vector of all the existing lights
vector<Light *> *Map::GetLights() {
	vector<Light *> *lights = new vector<Light *>();

	for (Phase *p : *GetPhases())
	{
		for (Light *l : *p->GetLights())
		{
			lights->push_back(l);
		}
	}

	return lights;
}

////////////////////////////////////////////////////////////
/// \brief
///
/// Delete a lane from the map.
/// this funciton has to make sure everything that uses this lane, is deleted as well.
///
/// \param laneNumber (int) - the ID of the lane to be deleted
///
/// \return true if successful, else false
////////////////////////////////////////////////////////////

bool Map::DeleteLane(int laneNumber) {

	vector<Intersection *>
		targetIntersections = GetIntersectionByLaneNumber(laneNumber);
	Lane *lane = GetLane(laneNumber);

	if (!targetIntersections.empty())
	{
		// delete all routes that go through this lane
		RemoveRouteByLaneNumber(laneNumber);

		// delete this lane from all phases it belongs to
		UnassignLaneFromPhase(laneNumber);
		// delete the given lane
		// if lane's road is connecting, send other intersection as well to handle deletion
		if (targetIntersections.size() > 1)
		{
			targetIntersections[0]
				->DeleteLane(laneNumber, targetIntersections[1]);
		} else
		{
			targetIntersections[0]->DeleteLane(laneNumber);
		}

		// if intersection has no roads left, delete it as well
		if (targetIntersections[0]->GetRoadCount() == 0)
		{
			auto it = find(intersections_.begin(),
			               intersections_.end(),
			               targetIntersections[0]);
			it = intersections_.erase(it);
			delete (*it);
			number_of_intersections_--;
		}

		// if road was connecting, check if the connected intersection needs to be deleted as well
		if (targetIntersections.size() > 1)
		{
			if (targetIntersections[1]->GetRoadCount() == 0)
			{
				auto it = find(intersections_.begin(),
				               intersections_.end(),
				               targetIntersections[1]);
				int intersection_number = (*it)->GetIntersectionNumber();
				intersections_.erase(it);
				delete (*it);
				// if exists, delete a cycle that was attached to this intersection;
				for (Cycle *c : cycles_)
				{
					if (c->GetIntersection()->GetIntersectionNumber()
						== intersection_number)
					{
						auto it2 = find(cycles_.begin(), cycles_.end(), c);
						cycles_.erase(it2);
						delete (*it);
						number_of_cycles_--;
					}
				}
				number_of_intersections_--;
			}
		}

		// set selected as nullptr
		this->SelectedLane = nullptr;

		// reload the map to display the changes
		this->ReloadMap();

		return true;
	}
	return false;
}

/// draw the map, and all of its belongings
void Map::Draw(RenderWindow *window) {
	// Draw all intersections
	for (Intersection *inter : intersections_)
	{
		inter->Draw(window);
	}

	// draw all routes

	for (auto &route : routes_)
	{
		route->Draw(window);
	}

	for (Cycle *c : cycles_)
	{
		c->Draw(window);
	}
}

/// return a list of all the lanes' id's
set<QString> Map::GetLaneIdList(int phaseNumber) {
	set<QString> idList = set<QString>();

	if (phaseNumber != 0)
	{
		Phase *p = GetPhase(phaseNumber);
		for (Lane *lane : *p->GetAssignedLanes())
		{
			idList.insert(QString::number(lane->GetLaneNumber()));
		}
	} else
	{
		for (Intersection *inter : intersections_)
		{
			for (Road *road : *inter->GetRoads())
			{
				for (Lane *lane : *road->GetLanes())
				{

					idList.insert(QString::number(lane->GetLaneNumber()));
				}
			}
		}
	}

	return idList;
}

/// return a list of all the roads' id's
set<QString> Map::GetRoadIdList() {
	set<QString> idList = set<QString>();
	for (Intersection *inter : intersections_)
	{
		for (Road *road : *inter->GetRoads())
		{
			idList.insert(QString::number(road->GetRoadNumber()));
		}
	}

	return idList;
}

/// return a list of all the intersections' id's
set<QString> Map::GetIntersectionIdList() {
	set<QString> idList = set<QString>();
	for (Intersection *inter : intersections_)
	{
		idList.insert(QString::number(inter->GetIntersectionNumber()));
	}

	return idList;
}

/// return a list of all the intersections' id's
set<QString> Map::GetPhaseIdList() {
	set<QString> idList = set<QString>();
	for (Phase *p : *GetPhases())
	{
		idList.insert(QString::number(p->GetPhaseNumber()));
	}

	return idList;
}

/// return a list of all the cycles' id's
set<QString> Map::GetCycleIdList() {
	set<QString> idList = set<QString>();
	for (Cycle *c : cycles_)
	{
		idList.insert(QString::number(c->GetCycleNumber()));
	}

	return idList;
}

/// return a list of all the intersections' id's
set<QString> Map::GetLightIdList() {
	set<QString> idList = set<QString>();
	for (Phase *p : *GetPhases())
	{
		for (Light *l : *p->GetLights())
		{
			idList.insert(QString::number(l->GetLightNumber()));
		}
		idList.insert(QString::number(p->GetPhaseNumber()));
	}

	return idList;
}
