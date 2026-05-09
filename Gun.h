#pragma once

namespace Tmpl8
{
	class Surface;

	class Firearm
	{
	public:

		Firearm();
		void change(int guntype);
		void evolve(int guntype);

		void upgrade(int damageU, float speedU, int rangeU, float reloadrateU, int ammoU, int firerateU);
		void reload(Surface* screen, float TimeMultiplier);
		void ManualReload();
		void Fire(Surface* screen, int mousex, int leftmouse, int closestwall, float charx, float chary, float TimeMultiplier);
		void DisplayStats(Surface* screen);


	private:

		void Shoot(Surface* screen, float charx, float chary, int Projectile, float TimeMultiplier);

		int weapon = 0;
		//weapon is different from guntype, which started at 0 for regular guns and at 10 for evolved guns for sprite convenience.
		//weapon starts at 1 for regular guns.
		//the evolved guns will use the first gun number for the tens digit (which wouldnt be possible if weapon started at 0) and the evolve in the ones digit
		//when the gun evolves, the only difference between 23 (sniper/shotgun) and 32 (shotgun/sniper) after the gun has evolved will be the decreased stat
		//gun's evolved with the pistol have no difference whether it was a pistol evolved with a new gun or an old gun evolved with the pistol

		int damage = 4, range = 60, ammo = 4, firerate = 20;
		float speed = 2, reloadrate = 100;
		//damage is the amount of damage your bullet does
		//speed is how fast your bullet fires, measured in pixels/tick
		//range is how far your bullet fires, measured in pixels
		//reloadrate is how long it takes for your gun to reload, measured in ticks
		//ammo is the amount of times you can shoot before needing to reload
		//firerate is how long it takes before you can shoot again, measure in ticks

		int magazine = 4, cooldown = 20; //temporary variables for ammo, reload, and firerate respectively
		float reloading = 100;

		int barrelxleft = 387, barrelxright = 412, bheight1 = 256, bheight2 = -1;; //bullet height and barrel x depends on the gun sprite, used to know where the bullet is firing from

		int Snipers[8] = { 2, 23, 24, 25, 12, 32, 42, 52 };
		int Shotguns[8] = { 3, 32, 34, 35, 13, 23, 43, 53 };
		int Miniguns[8] = { 4, 42, 43, 45, 14, 24, 34, 54 };
		int Twinguns[8] = { 5, 52, 53, 54, 15, 25, 35, 45 };

		float distance[20] = { 0 };   //variables for shooting distance, max projectiles is 20
		int direction[20] = { 0 }; //variables for direction, -1 is left, 1 is right, 0 is for projectiles that arent firing

		int verticality[20] = { 0 }; //make sure the projectile's y stays constant
		int initial[20] = { 0 };
		int horizontal[20] = { 0 }; //make sure the projectile covers the distance it has to, regardless of character movement
		int wallx[20] = { 0 };
		bool stop[20] = { false }; //walls and enemies stop bullets

		int projectile = 0;
		bool alternate[20] = { false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false, true }; //only for twin guns and its evolved versions
		bool firing = false;

		int colour = 0;
		int AdditionalDamage = 0;
		int pierce = 0;


	};
}