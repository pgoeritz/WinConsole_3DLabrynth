// Console3DLabrynth.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>

#include <Windows.h>

#include "settings.h"
#include "structs.h"

#include "InputHandler.h"
#include "Renderer.h"


int main()
{
	MapData* map = new MapData();
	map->dimensions = MAP_DIMENSION;
	map->data += "################";
	map->data += "#.....#..#.....#";
	map->data += "###.#..#...###.#";
	map->data += "#.# .#.#.#..#..#";
	map->data += "#.##.#...#.#####";
	map->data += "#.....#.##.....#";
	map->data += "#.#####..#####.#";
	map->data += "#...#..........#";
	map->data += "#.#..........#.#";
	map->data += "#.##.#######.#.#";
	map->data += "#.#.......#..#.#";
	map->data += "#...##.#.#####.#";
	map->data += "#.#.#..#.......#";
	map->data += "#.##############";
	map->data += "#..............#";
	map->data += "######wwww######";

	PlayerData* player = new PlayerData();
	player->angle = 0.f;
	player->pos.x = 8.f;
	player->pos.y = 8.f;

	InputHandler input_handler(player, map);
	Renderer renderer(player, map);

	// Main Loop
	//-------------------------
	bool exitCondition = false;
	do {
		input_handler.handleUserInput();
		renderer.renderScreen();
	} while (!input_handler.getExitCondition() && !input_handler.getWinCondition());

	if (input_handler.getWinCondition() == true) {
		std::cout << "You Won!!\n";
	}

	delete player;
	delete map;

	std::cout << "All Heap-Objects deleted!\n";
}