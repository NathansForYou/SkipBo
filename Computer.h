#ifndef _COMPUTER_H
#define _COMPUTER_H

#include "Player.h"
#include <string>
#include <vector>

class Computer : public Player {

	public:
		Computer(std::string = "");
		bool isHuman() const;
		bool move();
};

#endif

