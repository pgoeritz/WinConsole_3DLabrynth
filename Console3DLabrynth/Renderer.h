#pragma once

#include <string>

#include <Windows.h>

#include "structs.h"


class Renderer
{
public:
	Renderer(PlayerData*, MapData*);
	~Renderer();

	void renderScreen();

private:
	PlayerData* mPlayer;
	MapData* mMap;

	std::wstring screen;
	HANDLE console;
};

