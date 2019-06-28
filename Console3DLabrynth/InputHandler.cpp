#include "InputHandler.h"

#include <math.h>

#include <Windows.h>



InputHandler::InputHandler(PlayerData* player, MapData* map)
{
	mPlayer = player;
	mMap = map;

	last_time_point = std::chrono::system_clock::now();
	elapsed_time = 0.f;
}



InputHandler::~InputHandler()
{
	// does not have ownership over player and map
}



void InputHandler::updateElapsedTime()
{
	std::chrono::system_clock::time_point newTimePoint
		= std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedTime = newTimePoint - last_time_point;

	last_time_point = newTimePoint;

	elapsed_time = elapsedTime.count();
}



void InputHandler::handleUserInput() {
	updateElapsedTime();

	// rotate left
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)	{

		mPlayer->angle -= ROT_SPEED * elapsed_time;
	}

	// handle rotate right
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {

		mPlayer->angle += ROT_SPEED * elapsed_time;
	}

	// handle move foreward
	if (GetAsyncKeyState(VK_UP) & 0x8000) {

		mPlayer->pos.x += sinf(mPlayer->angle) * elapsed_time * MOV_SPEED;
		mPlayer->pos.y += cosf(mPlayer->angle) * elapsed_time * MOV_SPEED;

		if (mMap->data[MAP_DIMENSION * (int)mPlayer->pos.x + (int)mPlayer->pos.y] == '#') {

			mPlayer->pos.x -= sinf(mPlayer->angle) * elapsed_time * MOV_SPEED;
			mPlayer->pos.y -= cosf(mPlayer->angle) * elapsed_time * MOV_SPEED;
		} 
		else if (mMap->data[MAP_DIMENSION * (int)mPlayer->pos.x + (int)mPlayer->pos.y] == 'w') {
			win_condition = true;
		}
	}

	// handle move backward
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)	{

		mPlayer->pos.x -= sinf(mPlayer->angle) * elapsed_time * MOV_SPEED;
		mPlayer->pos.y -= cosf(mPlayer->angle) * elapsed_time * MOV_SPEED;

		if (mMap->data.c_str()[MAP_DIMENSION * (int)mPlayer->pos.x + (int)mPlayer->pos.y] == '#')
		{
			mPlayer->pos.x += sinf(mPlayer->angle) * elapsed_time * MOV_SPEED;
			mPlayer->pos.y += cosf(mPlayer->angle) * elapsed_time * MOV_SPEED;
		}
		else if (mMap->data[MAP_DIMENSION * (int)mPlayer->pos.x + (int)mPlayer->pos.y] == 'w') {

			win_condition = true;
		}
	}

	// handle escape
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		exit_condition = true;
	}
}


bool InputHandler::getExitCondition() {
	return exit_condition;
}

bool InputHandler::getWinCondition() {
	return win_condition;
}