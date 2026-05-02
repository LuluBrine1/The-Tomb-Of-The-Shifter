#pragma once

namespace Tmpl8
{
	bool Rockbiome();
	bool Bossroom();
	bool Collision(int x, int y, int charx, int chary);
	bool CheckBoundary(int x, int y);

	void CreateTile(int x, int y);
	void ClearMap();

	class Surface;
	class TileMap
	{
	public:
		TileMap();
		void DrawMap(Surface* screen, int charx, int chary);
		void CreateExits();
		int Exit(int leftx, int rightx, int topy, int bottomy, int charx, int chary);
		bool CreateChest(int x, int y, int charx, int chary);
		bool ChestInteraction(int x, int y, int charx, int chary);
		//will handle the gun upgrading aswell since the Map knows the layout and so can generate the correct chest loot, eg gun or upgrade.
		void OfferUpgrade(Surface* screen);
		int SelectUpgrade(int selection);


	private:
	};
}