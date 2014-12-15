#pragma once
#include "StationInterface.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
using namespace std;

class Station : public StationInterface
{
private:
	Stack stack;
	Queue queue;
	Deque deque;
public:
	int curr;
	Station(void)
	{
		curr = -1;
	}
	~Station(){}


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
			if(curr == -1 && car >= 0)
			{
				if(!stack.uniqueStack(curr))
				{
					return false;
				}
				if(!queue.uniqueQueue(curr))
				{
					return false;
				}
				if(!deque.uniqueDeque(curr))
				{
					return false;
				}

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
			if(curr != -1)
			{
				curr = -1;
				return true;
			}
			return false;
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
			if(stack.stackSize() < 5 && curr != -1)
			{
				stack.stackPush(curr);
				curr = -1;
				return true;
			}
			return false;
		}

		/**
		 * Removes the first car in the stack and makes it the current car.
		 * Does nothing if there is already a current car or if the stack already empty.
		 *
		 * @return true if the car is successfully removed from the stack; false otherwise
		 */
		bool removeFromStack()
		{
			if(stack.stackSize() > 0 && curr == -1)
			{
				curr = showTopOfStack();
				stack.stackPop();
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
			return stack.stackTop();
		}

		/**
		 * Returns the number of cars in the stack.
		 *
		 * @return the number of cars in the stack
		 */
		int showSizeOfStack()
		{
			return stack.stackSize();
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
			if(queue.queueSize() < 5 && curr != -1)
			{
				queue.queuePush(curr);
				curr = -1;
				return true;
			}
			return false;
		}
		/**
		 * Removes the first car in the queue and makes it the current car.
		 * Does nothing if there is already a current car or if the queue already empty.
		 *
		 * @return true if the car is successfully removed from the queue; false otherwise
		 */
		bool removeFromQueue()
		{
			if(queue.queueSize() > 0 && curr == -1)
			{
				curr = showTopOfQueue();
				queue.queuePop();
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
			return queue.queueTop();
		}

		/**
		 * Returns the number of cars in the queue.
		 *
		 * @return the number of cars in the queue
		 */
		int showSizeOfQueue()
		{
			return queue.queueSize();
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
			if(curr != -1 && deque.dequeSize() < 5)
			{
				deque.addLeft(curr);
				curr = -1;
				return true;
			}
			return false;
		}
		/**
		 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		bool addToDequeRight()
		{
			if(curr != -1 && deque.dequeSize() < 5)
			{
				deque.addRight(curr);
				curr = -1;
				return true;
			}
			return false;
		}

		/**
		 * Removes the leftmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		bool removeFromDequeLeft()
		{
			if(queue.queueSize() > 0 && curr == -1)
			{
				curr = showTopOfDequeLeft();
				deque.removeLeft();
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
			if(queue.queueSize() > 0 && curr == -1)
			{
				curr = showTopOfDequeRight();
				deque.removeRight();
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
			return deque.showLeft();
		}

		/**
		 * Returns the ID of the rightmost car in the deque.
		 *
		 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
		 */
		int showTopOfDequeRight()
		{
			return deque.showRight();
		}

		/**
		 * Returns the number of cars in the deque.
		 *
		 * @return the number of cars in the deque
		 */
		int showSizeOfDeque()
		{
			return deque.dequeSize();
		}
};
