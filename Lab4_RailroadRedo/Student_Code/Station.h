#include <iostream>
#include <string>
#include <set>
#include "StationInterfaceExtra.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "IRDeque.h"
#include "ORDeque.h"
using namespace std;


class Station : public StationInterfaceExtra
{
	private:
		int curr;
		Stack stack;
		Queue queue;
		Deque deque;
		IRDeque irdeque;
		ORDeque ordeque;

	public:
		Station()
		{
			curr = -1;
		}
		virtual ~Station(){}

		//Part 1--------------------------------------------------------------
		/**
		 * Let another car arrive at the station and become the current car.
		 * Do not allow a new car to arrive if any of the following conditions apply:
		 * 1.	There is already a current car
		 * 2.	The new car's ID already exists in any structure
		 * 3.	The new car's ID is negative
		 *
		 * @param car the ID of the car arriving at the station
		 * @return true if the car successfully arrived; false otherwise
		 */
		bool addToStation(int car)
		{
			if(!stack.unique(car) || !queue.unique(car) || !deque.unique(car))
			{
				return false;
			}
			if(!irdeque.unique(car) || !ordeque.unique(car))
			{
				return false;
			}
			if(car >=0 && curr == -1)
			{
				curr = car;
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the current car.
		 * Return -1 if there is no current car.
		 *
		 * @return the ID of the current car; -1 if there is no current car
		 */
		int showCurrentCar()
		{
			return curr;
		}

		/**
		 * Removes the current car from the station.
		 * Does nothing if there is no current car.
		 *
		 * @return true if the current car successfully left; false otherwise
		 */
		bool removeFromStation()
		{
			if(curr == -1)
			{
				return false;
			}
			curr = -1;
			return true;
		}

		//Part 2--------------------------------------------------------------
		/**
		 * Adds the current car to the stack.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the stack is already full.
		 *
		 * @return true if the car is successfully added to the stack; false otherwise
		 */
		bool addToStack()
		{
			if(stack.size() == 5 || curr == -1)
			{
				return false;
			}
			stack.push(curr);
			curr = -1;
			return true;
		}

		/**
		 * Removes the first car in the stack and makes it the current car.
		 * Does nothing if there is already a current car or if the stack already empty.
		 *
		 * @return true if the car is successfully removed from the stack; false otherwise
		 */
		bool removeFromStack()
		{
			if(curr == -1 && stack.size() > 0)
			{
				curr = stack.top();
				stack.pop();
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the first car in the stack.
		 *
		 * @return the ID of the first car in the stack; -1 if the stack is empty
		 */
		int showTopOfStack()
		{
			return stack.top();
		}

		/**
		 * Returns the number of cars in the stack.
		 *
		 * @return the number of cars in the stack
		 */
		int showSizeOfStack()
		{
			return stack.size();
		}

		//Part 3--------------------------------------------------------------
		/**
		 * Adds the current car to the queue.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the queue is already full.
		 *
		 * @return true if the car is successfully added to the queue; false otherwise
		 */
		bool addToQueue()
		{
			if(queue.size() == 5 || curr == -1)
			{
				return false;
			}
			queue.push(curr);
			curr = -1;
			return true;
		}

		/**
		 * Removes the first car in the queue and makes it the current car.
		 * Does nothing if there is already a current car or if the queue already empty.
		 *
		 * @return true if the car is successfully removed from the queue; false otherwise
		 */
		bool removeFromQueue()
		{
			if(curr == -1 && queue.size() > 0)
			{
				curr = queue.top();
				queue.pop();
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the first car in the queue.
		 *
		 * @return the ID of the first car in the queue; -1 if the queue is empty
		 */
		int showTopOfQueue()
		{
			return queue.top();
		}

		/**
		 * Returns the number of cars in the queue.
		 *
		 * @return the number of cars in the queue
		 */
		int showSizeOfQueue()
		{
			return queue.size();
		}

		//Part 4--------------------------------------------------------------
		/**
		 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		bool addToDequeLeft()
		{
			if(deque.size() == 5 || curr == -1)
			{
				return false;
			}
			deque.pushLeft(curr);
			curr = -1;
			return true;
		}

		/**
		 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		bool addToDequeRight()
		{
			if(deque.size() == 5 || curr == -1)
			{
				return false;
			}
			deque.pushRight(curr);
			curr = -1;
			return true;
		}

		/**
		 * Removes the leftmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		bool removeFromDequeLeft()
		{
			if(curr == -1 && deque.size() > 0)
			{
				curr = deque.topLeft();
				deque.popLeft();
				return true;
			}
			return false;
		}

		/**
		 * Removes the rightmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		bool removeFromDequeRight()
		{
			if(curr == -1 && deque.size() > 0)
			{
				curr = deque.topRight();
				deque.popRight();
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the leftmost car in the deque.
		 *
		 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
		 */
		int showTopOfDequeLeft()
		{
			return deque.topLeft();
		}

		/**
		 * Returns the ID of the rightmost car in the deque.
		 *
		 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
		 */
		int showTopOfDequeRight()
		{
			return deque.topRight();
		}

		/**
		 * Returns the number of cars in the deque.
		 *
		 * @return the number of cars in the deque
		 */
		int showSizeOfDeque()
		{
			return deque.size();
		}


		//Input-Restricted Deque----------------------------------------------
		/**
		 * Adds the current car to the IRDeque on the left side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the IRDeque is already full.
		 *
		 * @return true if the car is successfully added to the IRDeque; false otherwise
		 */
		bool addToIRDequeLeft()
		{
			if(irdeque.size() == 5 || curr == -1)
			{
				return false;
			}
			irdeque.push(curr);
			curr = -1;
			return true;
		}

		/**
		 * Removes the leftmost car in the IRDeque and makes it the current car.
		 * Does nothing if there is already a current car or if the IRDeque already empty.
		 *
		 * @return true if the car is successfully removed from the IRDeque; false otherwise
		 */
		bool removeFromIRDequeLeft()
		{
			if(curr == -1 && irdeque.size() > 0)
			{
				curr = irdeque.topLeft();
				irdeque.popLeft();
				return true;
			}
			return false;
		}

		/**
		 * Removes the rightmost car in the IRDeque and makes it the current car.
		 * Does nothing if there is already a current car or if the IRDeque already empty.
		 *
		 * @return true if the car is successfully removed from the IRDeque; false otherwise
		 */
		bool removeFromIRDequeRight()
		{
			if(curr == -1 && irdeque.size() > 0)
			{
				curr = irdeque.topRight();
				irdeque.popRight();
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the leftmost car in the IRDeque.
		 *
		 * @return the ID of the leftmost car in the IRDeque; -1 if the IRDeque is empty
		 */
		int showTopOfIRDequeLeft()
		{
			return irdeque.topLeft();
		}

		/**
		 * Returns the ID of the rightmost car in the IRDeque.
		 *
		 * @return the ID of the rightmost car in the IRDeque; -1 if the IRDeque is empty
		 */
		int showTopOfIRDequeRight()
		{
			return irdeque.topRight();
		}

		/**
		 * Returns the number of cars in the IRDeque.
		 *
		 * @return the number of cars in the IRDeque
		 */
		int showSizeOfIRDeque()
		{
			return irdeque.size();
		}

		//Output-Restricted Deque---------------------------------------------
		/**
		 * Adds the current car to the ORDeque on the left side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the ORDeque is already full.
		 *
		 * @return true if the car is successfully added to the ORDeque; false otherwise
		 */
		bool addToORDequeLeft()
		{
			if(ordeque.size() == 5 || curr == -1)
			{
				return false;
			}
			ordeque.pushLeft(curr);
			curr = -1;
			return true;
		}

		/**
		 * Adds the current car to the ORDeque on the right side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the ORDeque is already full.
		 *
		 * @return true if the car is successfully added to the ORDeque; false otherwise
		 */
		bool addToORDequeRight()
		{
			if(ordeque.size() == 5 || curr == -1)
			{
				return false;
			}
			ordeque.pushRight(curr);
			curr = -1;
			return true;
		}

		/**
		 * Removes the leftmost car in the ORDeque and makes it the current car.
		 * Does nothing if there is already a current car or if the ORDeque already empty.
		 *
		 * @return true if the car is successfully removed from the ORDeque; false otherwise
		 */
		bool removeFromORDequeLeft()
		{
			if(curr == -1 && ordeque.size() > 0)
			{
				curr = ordeque.topLeft();
				ordeque.pop();
				return true;
			}
			return false;
		}

		/**
		 * Returns the ID of the leftmost car in the ORDeque.
		 *
		 * @return the ID of the leftmost car in the ORDeque; -1 if the ORDeque is empty
		 */
		int showTopOfORDequeLeft()
		{
			return ordeque.topLeft();
		}

		/**
		 * Returns the number of cars in the ORDeque.
		 *
		 * @return the number of cars in the ORDeque
		 */
		int showSizeOfORDeque()
		{
			return ordeque.size();
		}
};
