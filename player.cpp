#include"player.h"
#include"actor.h"
#include"stack.h"
#include"list.h"
#include"point.h"
#include"aquarium.h"
#include<iostream>

//  Player( ... )
//		Constructs and initializes the Player/Actor and its member variables
//		Remembers and discovers the starting point.
Player::Player(Aquarium* aquarium, Point p, std::string name, char sprite)
	:Actor(aquarium, p, name, sprite),
	m_look(),
	m_discovered(),
	m_btQueue(),
	m_btStack(),
	m_toggleBackTracking(false) {

	// First two steps of searching algorithm
	// Discover the starting point 
	m_discovered.addToFront(p);
	m_look.push(p);
}

//  stuck() 
//		See if the player is stuck in the maze (no solution)
bool Player::stuck() const {
	return Actor::getState() == State::STUCK;
}

//  foundExit()
//		See if the player has found the exit
bool Player::foundExit() const {
	return Actor::getState() == State::FREEDOM;
}
//  toggleBackTrack( ... )
//		Turn on/off backtracking
void Player::toggleBackTrack(bool toggle) {
	m_toggleBackTracking = toggle;
}

//  getTargetPoint()
//		Get the point the player wants to look around next.
//      If m_look is empty then return an invalid point.
Point Player::getTargetPoint() const {
	if (m_look.isEmpty()) return Point(-1, -1);
	return m_look.peek();
}

// _discovered
//		returns true if the item is in the list
bool Player::_discovered(Point p) {
	return (m_discovered.findItem(p) != -1);
}

//  update() 
//		This function implements an algorithm to look through the maze
//      for places to move (STATE::LOOKING). update also handles moving the 
//		player as well, if there is an open undiscovered cell to move to the  
//		player just moves there.  However, there will be cases in the next 
//		desired point to look around is not adjacent (more than one cell away), 
//		at this point the player must backtrack (State::BACKTRACK) to a point 
//		that is adjacent to the next point the player was planning to visit
//
//		The player can only do one thing each call, they can either LOOK or 
//		BACKTRACK not both.  Nor should the player move more than one cell per
//		call to update.  If you examine the function calls for the entire game
//		you should observe that this is already being called within a loop. Your
//		Implementation should NOT have any loops that pertain to actual movement 
//		of the player.  
//
//		Backtracking is challenging, save it for the very very very last thing.
//		Make sure the Looking aspect compiles and works first.
void Player::update() {
	Point currPos;
	Point endPos = getAquarium()->getEndPoint();
	bool pause = false;
	int faullSurrounded;
	int x;
	int y;
	m_look.push(getPosition());         //m_look edited, getPosition        //push the starting point
	m_discovered.addToRear(getPosition());    //getPosition edited       //mark the starting point as discoverd

	if (m_look.isEmpty())				//m_look edited
	{
		std::cout << "There is No Solution.";
		return;
	}
	else
	{

		while (!m_look.isEmpty())
		{

			if (m_look.isEmpty())
			{
				std::cout << "There is No Solution.";
				return;
			}

			setPosition(m_look.peek());             
			currPos = getPosition();
			x = currPos.getX();
			y = currPos.getY();


			if (m_btStack.isEmpty() || !(m_btStack.peek() == getPosition()))
				m_btStack.push(getPosition());

			m_look.pop();                                      

			if (pause)
			{
				//m_discovered.deleteRear();
				return;
			}

			if (currPos.operator==(endPos))                             
			{
				std::cout << "You Win!!!!";
				return;
			}

			faullSurrounded = 4;

			currPos.set(x - 1, y);                            //check the left cell
			if (getAquarium()->isCellOpen(currPos) && !_discovered(currPos))
			{
				m_discovered.addToRear(currPos);                    
				m_look.push(currPos);                              
				currPos = getPosition();
				faullSurrounded--;
			}

			currPos.set(x + 1, y);                            //check the right cell
			if (getAquarium()->isCellOpen(currPos) && !_discovered(currPos))
			{
				m_discovered.addToRear(currPos);                     
				m_look.push(currPos);                               
				currPos = getPosition();
				faullSurrounded--;
			}

			currPos.set(x, y - 1);                       //check the cell above
			if (getAquarium()->isCellOpen(currPos) && !_discovered(currPos))
			{
				m_discovered.addToRear(currPos);                      
				m_look.push(currPos);                              
				currPos = getPosition();
				faullSurrounded--;
			}

			currPos.set(x, y + 1);                            //check the cell below
			if (getAquarium()->isCellOpen(currPos) && !_discovered(currPos))
			{
				m_discovered.addToRear(currPos);                     
				m_look.push(currPos);                         
				currPos = getPosition();
				faullSurrounded--;
			}



			if (faullSurrounded == 4)                   //be stucked, need to do back track
			{
				m_btStack.pop();
				if (!m_btStack.isEmpty())
				{
					m_look.push(m_btStack.peek());
					m_btStack.pop();
				}
			}

			pause = true;
		}
	}

}

// say()
//		What does the player say?
//		Already Implemented, nothing to do here
void Player::say() {

	// Freedom supercedes being eaten
	if (getState() == State::FREEDOM) {
		std::cout << getName() << ": WEEEEEEEEEEEEEEE!";
		return;
	}

	// Being eaten supercedes being lost
	switch (getInteract()) {
	case Interact::ATTACK:
		std::cout << getName() << ": OUCH!";
		break;
	case Interact::GREET:
		break;
	case Interact::ALONE:
	default:
		switch (getState()) {
		case State::LOOKING:
			std::cout << getName() << ": Where's the exit?";
			break;
		case State::STUCK:
			std::cout << getName() << ": Oh no! I'm Trapped!";
			break;
		case State::BACKTRACK:
			std::cout << getName() << ": Gotta backtrack...";
			break;
		default:
			break;
		}

		break;
	}
}


