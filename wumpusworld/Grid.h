#pragma once

enum grid {
	safe = 0,
	unknown = 1,
	wumpus = 2,
	stench = 3,
	pit = 4,
	breeze = 5,
	wall=6,
	gold=7
};
enum direction {
	east=0,
	south=1,
	west=2,
	north=3
};