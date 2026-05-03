#include "Map.h"
#include "surface.h"
#include "template.h"
#include "game.h"
#include <random> //used for random seeds
#include <cstdio> //used for sprintf

namespace Tmpl8
{

	Surface tiles("assets/tilemap.png");

	static const int width = 60;
	static const int height = 48;

	char map[height][width * 4 + 1];

	//the left/right exit y-values depend on the map
	int leftexit = 0;
	int rightexit = 0;
	//the top/bottom x-values are constant but multiple for each map
	int topexit1 = 21;
	int topexit2 = 38;

	int roomx = 2;
	int roomy = 6;

	int biome = 0;
	bool firstrockroom = false;
	bool rockbiome = false;
	bool bossroom = false;


	char layout[9][14] = //checks for exits to reveal, X is unavailable, A is available
	{
		"-------------",
		"-------------",
		"------A------",
		"-----A-A-----",
		"----A-A-A----",
		"---A-A-A-A---",
		"--A-A-A-A-A--",
		"-------------",
		"-------------"
	};

	TileMap::TileMap()
	{
		if (StartRoom() == true)
		{
			roomx = 2;
			roomy = 6;
			biome = 1;
			bossroom = false;
			rockbiome = false;
			firstrockroom == false;
			for (int j = 0; j < 9; j++)
			{
				for (int i = 0; i < 14; i++)
				{
					layout[j][i] = '-';
					if (j == 2 && i == 6)
						layout[j][i] = 'A';
					else if (j == 3 && (i == 5 || i == 7))
						layout[j][i] = 'A';
					else if (j == 4 && (i == 4 || i == 6 || i == 8))
						layout[j][i] = 'A';
					else if (j == 5 && (i == 3 || i == 5 || i == 7 || i == 9))
						layout[j][i] = 'A';
					else if (j == 6 && (i == 2 || i == 4 || i == 6 || i == 8 || i == 10))
						layout[j][i] = 'A';
				}
			}
		}




		if (roomy > 4) { biome = 1, firstrockroom = false; }
		if (roomy < 5 && roomy > 2) { biome = 2; }
		if (roomy == 2) { biome = 3; }
		//if (roomy == 5) { biome = 3; }
		
		if (biome == 1)
		{

			std::random_device rd;
			std::mt19937 level(rd());
			std::uniform_int_distribution<> sand(1, 15);

			int SandLevel = sand(level); //randomly generates a number to load a random sand room

			//some air will not be collidable even though it cannot be access so that enemies dont spawn there
			
			if (SandLevel == 1) //slabs
			{

				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 25;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 2) //cliff
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  baX aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 3) //elevator
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 23;
				rightexit = 19;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 4) //stalactite
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 21;
				rightexit = 19;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 5) //platforms
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  baX baX baX aa  aa  baX aa  aa  aa  baX baX baX aa  aa  baX aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  baX baX baX baX aa  aa  baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 24;
				rightexit = 22;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 6) //skull
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aaX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aaX aaX aaX aaX aaX aaX baX baX aa  aa  aa  aa  baX baX aaX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX aa  baX baX baX aa  baX baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 17;
				rightexit = 17;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 7) //space
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 24;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 8) //waves
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX aa  aa  baX aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 9) //house
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aaX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aaX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 21;
				rightexit = 25;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 10) //stripes
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX baX aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  baX aa  baX baX baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  baX aa  baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  aa  baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  baX baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX aa  aa  baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX aa  aa  baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX aa  aa  aa  baX baX aa  baX aa  aa  baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  baX baX aa  baX aa  aa  baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  baX baX aa  baX aa  baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  baX aa  baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  baX baX baX aa  aa  aa  aa  baX baX aa  baX baX aa  aa  baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  baX baX aa  aa  aa  baX aa  baX baX aa  baX aa  aa  aa  baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  baX aa  aa  aa  baX baX aa  baX baX aa  baX aa  aa  baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX aa  baX aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 15;
				rightexit = 21;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 11) //symmetry
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 12) //iceberg
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 25;
				rightexit = 25;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 13) //ship
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX aa  baX aa  baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  baX baX baX baX aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  baX baX baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX baX baX aa  baX aa  aa  baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  baX baX baX aa  aa  aa  baX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX aa  baX aaX aaX aaX aaX baX aa  baX aa  aa  baX baX aa  aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  baX baX aa  baX aa  aa  baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 25;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 14) //volcano
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX aa  aa  aa  aa  baX aa  baX aaX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aaX aaX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX aaX aaX baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  baX aa  aa  baX aa  aa  aa  aa  baX aaX aaX aaX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX aa  aa  baX baX aa  aa  baX aa  aa  aa  baX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  baX aaX baX aa  baX baX aa  baX baX aa  aa  baX aa  aa  aa  baX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aaX baX aa  aa  aa  aa  aa  baX aa  aa  baX baX aa  aa  baX baX aa  baX baX aa  aa  baX aaX aaX aaX aaX aaX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX aa  aa  aa  baX aa  aa  aa  baX aaX aaX aaX baX aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX aa  aa  baX baX aa  aa  aa  baX aa  aa  aa  aa  baX baX baX aa  aa  aa  baX aaX baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aaX aaX baX aa  aa  aa  aa  baX aa  aa  baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aaX aaX baX aa  aa  aa  baX baX baX aa  baX baX aa  baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  baX baX aa  aa  aa  aa  baX baX aa  aa  baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aaX baX aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX baX aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aaX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  baX baX baX aa  baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  baX aaX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (SandLevel == 15) //jigsaw
			{
				char temp[height][width * 4 + 1] =
				{
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  baX aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  baX baX aa  baX baX aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX aa  aa  baX baX aa  aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  baX aa  aa  aa  baX baX baX aa  aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX aa  aa  aa  baX baX baX baX aa  aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  baX baX aa  aa  aa  baX baX baX aa  aa  baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  baX baX baX baX baX baX baX aa  aa  aa  baX aa  aa  aa  baX baX aa  aa  baX baX aa  aa  aa  aa  baX baX baX baX baX aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  baX baX aa  baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX baX ",
					"baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB baB "
				};
				leftexit = 26;
				rightexit = 25;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}
		}

		if (biome == 2)
		{

			std::random_device rd;
			std::mt19937 level(rd());
			std::uniform_int_distribution<> rock(1, 9);

			int RockLevel = rock(level); //randomly generates a number to load a random rock room

			if (RockLevel == 1) //these ones dont have their own names since their design is meant to be a maze rather than an open space
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 24;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 2)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 23;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 3)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 26;
				rightexit = 26;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 4)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX aa  aa  aa  abX abX abX aa  abX abX abX abX abX abX aa  abX abX abX aa  aa  aa  abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 25;
				rightexit = 25;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 5)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 26;
				rightexit = 21;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 6)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 25;
				rightexit = 23;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 7)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 23;
				rightexit = 23;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 8)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  abX aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX aa  aa  abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 26;
				rightexit = 22;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}

			if (RockLevel == 9)
			{
				char temp[height][width * 4 + 1] =
				{
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
					"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
				};
				leftexit = 26;
				rightexit = 8;
				for (int y = 0; y < height; y++)
					for (int x = 0; x < width * 4; x++)
						map[y][x] = temp[y][x];
			}
		}
		if (biome == 3) //the boss room
		{
			char temp[height][width * 4 + 1] =
			{
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  aa  abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX ",
				"abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX abX "
			};

			for (int y = 0; y < height; y++)
				for (int x = 0; x < width * 4; x++)
					map[y][x] = temp[y][x];
		}
	}


	void TileMap::DrawMap(Surface* screen, int charx, int chary) //draws tile on the screen
	{
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				int tx = map[y][x * 4] - 'a';
				int ty = map[y][x * 4 + 1] - 'a';
				
				int screenX = (x * 32) - charx;
				int screenY = (y * 32) + chary;

				// Skip entire tile if completely off-screen
				if (screenX + 32 <= 0 || screenX >= 800 ||
					screenY + 32 <= 0 || screenY >= 512)
				{
					continue;
				}

				Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 64;

				
				for (int i = 0; i < 32; i++)
				{
					int py = screenY + i;
					if (i != 0) src += 64;
					if (py < 0 || py >= 512) continue;

					for (int j = 0; j < 32; j++)
					{
						int px = screenX + j;
						if (px < 0 || px >= 800) continue;

						if ((map[y][x * 4] != 'a' || map[y][x * 4 + 1] != 'a'))
						{
							if ((map[y][x * 4] == 'b' && map[y][x * 4 + 1] == 'b') && src[j] == 0)
							{
								continue; //keeps empty chest space transparent
							}
							else
								screen->GetBuffer()[px + py * 800] = src[j];
						}
					}
				}
				
			}
	}

	bool Rockbiome()
	{
		return rockbiome;	
	}

	bool Bossroom()
	{
		return bossroom;
	}

	bool Collision(int x, int y, int charx, int chary) 
	{
		if (y > -1)
		{
			int tx = (x + charx) / 32, ty = (y - chary) / 32;
			if (tx > 59) tx = 59;
			if (ty > 65000) return true;
			return map[ty][tx * 4 + 2] == 'X'; //returns true if they collide aka solid object (not chest)
		}
	}

	bool CheckBoundary(int x, int y) //worm specific change, bottom of the map is a boundary so that it cant dig into it
	{
		
		int tx = (x) / 32, ty = (y) / 32;
		if (map[ty][tx * 4 + 2] == 'B')
		{
			return true;
		}
		return false;
	}
	





	void TileMap::CreateExits()
	{

		if (layout[roomy - 1][roomx - 1] == 'A') //creates top left exit
		{
			map[7][topexit1 * 4 + 2] = 'E';
			for (int i = 0; i < 8; i++)
			{
				map[i][topexit1 * 4] = 'a';
				map[i][topexit1 * 4 + 1] = 'a';
			}
		}

		if (layout[roomy - 1][roomx + 1] == 'A') //creates top right exit
		{
			map[7][topexit2 * 4 + 2] = 'E';
			for (int i = 0; i < 8; i++)
			{
				map[i][topexit2 * 4] = 'a';
				map[i][topexit2 * 4 + 1] = 'a';
			}
		}

		if (layout[roomy][roomx - 2] == 'A') //creates left exit
		{
			map[leftexit][12 * 4 + 2] = 'E';
			for (int i = 0; i < 13; i++)
			{
				map[leftexit][i * 4] = 'a';
				map[leftexit][i * 4 + 1] = 'a';
			}
		}

		if (layout[roomy][roomx + 2] == 'A') //creates right exit
		{
			map[rightexit][47 * 4 + 2] = 'E';
			for (int i = 0; i < 13; i++)
			{
				map[rightexit][(59 - i) * 4] = 'a';
				map[rightexit][(59 - i) * 4 + 1] = 'a';
			}
		}


	}

	int TileMap::Exit(int leftx, int rightx, int topy, int bottomy, int charx, int chary)
	{
		int lefttx = (leftx + charx) / 32;
		int righttx = (rightx + charx) / 32;
		int topty = (topy - chary) / 32;
		int bottomty = (bottomy - chary) / 32;

		bool TL = map[topty][lefttx * 4 + 2] == 'E';
		bool TR = map[topty][righttx * 4 + 2] == 'E';
		bool BL = map[bottomty][lefttx * 4 + 2] == 'E';
		bool BR = map[bottomty][righttx * 4 + 2] == 'E';

		//if the top of the character hits an exit but the bottom doesnt
		if (TL && TR && !BL && !BR && lefttx < 30)
		{
			layout[roomy][roomx] = 'X';
			if (roomy == 5) { firstrockroom = true, rockbiome = true; } //when moving up into the first rock layer, true
			if (roomy == 4) { firstrockroom = false; } //when moving up into the second rock layer, false
			if (roomy == 3) { bossroom = true; }
			roomx -= 1;
			roomy -= 1;
			return 1;
		}

		else if (TL && TR && !BL && !BR && righttx >= 30)
		{
			layout[roomy][roomx] = 'X';
			if (roomy == 5) { firstrockroom = true, rockbiome = true; } //when moving up into the first rock layer, true
			if (roomy == 4) { firstrockroom = false; } //when moving up into the second rock layer, false
			if (roomy == 3) { bossroom = true; }
			roomx += 1;
			roomy -= 1;
			return 2;
		}

		else if (!TL && TR && !BL && BR)
		{
			layout[roomy][roomx] = 'X';
			if (roomy == 4) { firstrockroom = false, rockbiome = true; } //when moving right while in the first rock layer, false
			roomx += 2;
			return 3;
		}

		else if (TL && !TR && BL && !BR)
		{
			layout[roomy][roomx] = 'X';
			if (roomy == 4) { firstrockroom = false, rockbiome = true; } //when moving left while in the first rock layer, false
			roomx -= 2;
			return 4;
		}

		else return 0;
	}

	void CreateTile(int x, int y) //boss attack
	{
		int tx = x / 32;
		int ty = y / 32;
		map[ty][tx * 4] = 'b';
		map[ty][tx * 4 + 1] = 'a';
		map[ty][tx * 4 + 2] = 'X';
	}

	void ClearMap() //boss attack
	{
		for (int j = 16; j < 40; j++)
		{
			for (int i = 21; i < 39; i++)
			{
				map[j][i * 4] = 'a';
				map[j][i * 4 + 1] = 'a';
				map[j][i * 4 + 2] = ' ';
			}
		}
	}

	bool TileMap::CreateChest(int x, int y, int charx, int chary)
	{
		bool chest = false;
		int tx = (x + charx) / 32, ty = (y - chary) / 32;
		if (map[ty + 1][tx * 4 + 2] == 'X')
		{
			map[ty][tx * 4] = 'b';
			map[ty][tx * 4 + 1] = 'b';
			chest = true;
		}
		return chest;
	}

	bool TileMap::ChestInteraction(int x, int y, int charx, int chary)
	{
		int tx = (x + charx) / 32, ty = (y - chary) / 32;
		if ((map[ty][tx * 4] == 'b' && map[ty][tx * 4 + 1] == 'b') || (map[ty][(tx - 1) * 4] == 'b' && map[ty][(tx - 1) * 4 + 1] == 'b') || (map[ty][(tx + 1) * 4] == 'b' && map[ty][(tx + 1) * 4 + 1] == 'b'))
			return true; //if within a tile of the chest it can be accessed
	}


	//upgrade offerings and selecting

	Sprite GunUpgrades(new Surface("assets/GunUpgrades.png"), 5);
	Sprite BulletUpgrades(new Surface("assets/BulletUpgrades.png"), 6);
	Sprite GunEvolutions(new Surface("assets/GunEvolutions.png"), 5);
	int offering[3] = { -1, -1, -1 };
	int weapontype = -1;

	std::random_device rd;
	std::mt19937 offer(rd());
	std::uniform_int_distribution<> gun(0, 4);
	std::uniform_int_distribution<> bullet(0, 5);

	void TileMap::OfferUpgrade(Surface* screen)
	{
		offering[0] = -1, offering[1] = -1, offering[2] = -1;
		if (roomx == 2 && roomy == 6) //if you're in the first room, offer gun change
		{
			
			while (offering[0] == offering[1] || offering[0] == offering[2] || offering[1] == offering[2])
			{
				for (int i = 0; i < 3; i++)
				{
					offering[i] = gun(offer);
				}
			}

			char text[]{ "SELECT YOUR GUN!" };
			screen->Print(text, 354, 70, 0xffffff);

			char element[]{ "Press Q to select gun elements" };
			screen->Print(element, 308, 450, 0xffffff);

			GunUpgrades.SetFrame(offering[0]);
			GunUpgrades.Draw(screen, 125, 106);
			GunUpgrades.SetFrame(offering[1]);
			GunUpgrades.Draw(screen, 325, 106);
			GunUpgrades.SetFrame(offering[2]);
			GunUpgrades.Draw(screen, 525, 106);
		}
		else if (firstrockroom == true) //if youre in the first rock room, evolved gun offer
		{
			while (offering[0] == offering[1] || offering[0] == offering[2] || offering[1] == offering[2] || weapontype == offering[0] || weapontype == offering[1] || weapontype == offering[2])
			{
				for (int i = 0; i < 3; i++)
				{
					offering[i] = gun(offer);
				}
			}

			char text[]{ "EVOLVE YOUR GUN!" };
			screen->Print(text, 354, 70, 0xffffff);

			GunEvolutions.SetFrame(offering[0]);
			GunEvolutions.Draw(screen, 125, 106);
			GunEvolutions.SetFrame(offering[1]);
			GunEvolutions.Draw(screen, 325, 106);
			GunEvolutions.SetFrame(offering[2]);
			GunEvolutions.Draw(screen, 525, 106);
		}
		else
		{

			while (offering[0] == offering[1] || offering[0] == offering[2] || offering[1] == offering[2])
			{
				for (int i = 0; i < 3; i++)
				{
					offering[i] = bullet(offer);
				}
			}

			char text[]{ "UPGRADE YOUR GUN!" };
			screen->Print(text, 354, 70, 0xffffff);

			BulletUpgrades.SetFrame(offering[0]);
			BulletUpgrades.Draw(screen, 125, 106);
			BulletUpgrades.SetFrame(offering[1]);
			BulletUpgrades.Draw(screen, 325, 106);
			BulletUpgrades.SetFrame(offering[2]);
			BulletUpgrades.Draw(screen, 525, 106);
		}

	}

	int TileMap::SelectUpgrade(int selection)
	{
		if (roomx == 2 && roomy == 6)
		{
			weapontype = offering[selection];
			return offering[selection];
		}
		else if (firstrockroom == true)
		{
			return (offering[selection] + 11);
		}
		else
		{
			return (offering[selection] + 101);
		}

	}

};

