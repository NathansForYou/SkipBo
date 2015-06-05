#include "Game.h"
#include <cstdlib>
#include <time.h>

int main (void) {
	srand(time(NULL));
	Game game;
	game.startGame();
	return 0;
}
