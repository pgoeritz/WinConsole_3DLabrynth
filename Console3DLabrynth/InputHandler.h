#pragma once

#include <chrono>

#include "settings.h"
#include "structs.h"

class InputHandler
{
public:
	InputHandler(PlayerData*, MapData*);
	~InputHandler();

	void handleUserInput();

	bool getExitCondition();
	bool getWinCondition();

private:
	PlayerData* mPlayer;
	MapData* mMap;

	bool exit_condition = false;
	bool win_condition = false;

	// mesuring elapsed time
	float elapsed_time;
	std::chrono::system_clock::time_point last_time_point;



	void updateElapsedTime();

};

