#pragma once

namespace Tmpl8
{
	class Surface;
	void ManualReload();

	class Firearm
	{
	public:

		Firearm(int guntype);
		void upgrade(int damageU, int speedU, int rangeU, int reloadrateU, int ammoU, int firerateU);
		void Fire(Surface* screen, int mousex, int leftmouse, int closestwall, int left, int right, float charx, float chary, float TimeMultiplier);
		void reload(Surface* screen, float TimeMultiplier);
		void DisplayStats(Surface* screen);


	private:
	};
}