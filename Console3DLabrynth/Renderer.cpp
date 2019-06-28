#include "Renderer.h"

#include "settings.h"

Renderer::Renderer(PlayerData* player, MapData* map)
{
	mPlayer = player;
	mMap = map;

	screen = std::wstring(SCREEN_WIDTH * SCREEN_HEIGHT, '.');
	console = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	SetConsoleActiveScreenBuffer(console);
}


Renderer::~Renderer()
{

}


void Renderer::renderScreen() {

	// Ray Casting
	//-----------------------
	// for every screen column do:
	for (int i = 0; i < SCREEN_WIDTH; i++) {

		float distance = 0.f;
		float increment_size = 0.1f;
		bool wall_hit = false;


		// angle at which the ray is being cast (ith ray of fov/columns + offset)
		float fRayAngle = (float)i * (FOV / (float)SCREEN_WIDTH) + mPlayer->angle - FOV / 2.f;
		//(fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

		// calc unit vector
		Coordinate<float> unit_vec;
		unit_vec.x = sinf(fRayAngle);
		unit_vec.y = cosf(fRayAngle);

		// clac distance
		do {

			distance += increment_size;

			// coord I want to check for wall
			Coordinate<int> test_coord;
			test_coord.x = (int)(distance * unit_vec.x + mPlayer->pos.x);
			test_coord.y = (int)(distance * unit_vec.y + mPlayer->pos.y);

			// check bounds (or possible error)
			if (test_coord.x < 0 || test_coord.x > MAP_DIMENSION ||
				test_coord.y < 0 || test_coord.y > MAP_DIMENSION) {

				distance = RENDER_DISTANCE;
			}
			// check coord for wall
			else if (mMap->data.c_str()[MAP_DIMENSION * test_coord.x + test_coord.y] == '#') {
				wall_hit = true;
			}

		} while (!wall_hit && distance < VIEW_DISTANCE);


		// determin shade of wall based on distance
		short shade = ' ';
		if (distance <= RENDER_DISTANCE / 4.f)		shade = 0x2588;
		else if (distance <= RENDER_DISTANCE / 3.f)	shade = 0x2593;
		else if (distance <= RENDER_DISTANCE / 2.f)	shade = 0x2592;
		else if (distance < RENDER_DISTANCE)		shade = 0x2591;

		// render column for ray i
		// add cailing and floor
		float ceiling = (float)SCREEN_HEIGHT / 2.f - (float)SCREEN_HEIGHT / distance;
		float floor = (float)SCREEN_HEIGHT - ceiling;
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			if (j < ceiling) {
				screen[j * SCREEN_WIDTH + i] = ' ';
			}
			else if (j > ceiling && j <= floor) {
				screen[j * SCREEN_WIDTH + i] = shade;
			}
			else
			{
				// Shade floor based on distance
				float b = 1.0f - (((float)j - SCREEN_HEIGHT / 2.0f) / ((float)SCREEN_HEIGHT / 2.0f));
				if (b < 0.25)		shade = '#';
				else if (b < 0.5)	shade = 'x';
				else if (b < 0.75)	shade = '-';
				else if (b < 0.9)	shade = '.';
				else				shade = ' ';
				screen[j * SCREEN_WIDTH + i] = shade;
			}
		}
	}



	// Render Map
	//-----------------------
	for (int nx = 0; nx < mMap->dimensions; nx++)
		for (int ny = 0; ny < mMap->dimensions; ny++)
		{
			screen[(ny + 1) * SCREEN_WIDTH + nx]
				= mMap->data[ny * mMap->dimensions + nx];
		}
	screen[((int)mPlayer->pos.x + 1) * SCREEN_WIDTH + (int)mPlayer->pos.y] = 'P';

	// Draw screen to console
	//-------------------------
	screen[SCREEN_WIDTH * SCREEN_HEIGHT - 1] = '\0';
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(
		console,
		screen.c_str(),
		SCREEN_WIDTH * SCREEN_HEIGHT,
		{ 0,0 },
		&dwBytesWritten);
}
