#include "Gun.h"
#include "Enemy.h"
#include "surface.h"
#include "game.h"
#include <cstdio> //used for sprintf
#include <string>


namespace Tmpl8
{
	int weapon = 0;
	//weapon is different from guntype, which started at 0 for regular guns and at 10 for evolved guns for sprite convenience.
	//weapon starts at 1 for regular guns.
	//the evolved guns will use the first gun number for the tens digit (which wouldnt be possible if weapon started at 0) and the evolve in the ones digit
	//when the gun evolves, the only difference between 23 (sniper/shotgun) and 32 (shotgun/sniper) after the gun has evolved will be the decreased stat
	//gun's evolved with the pistol have no difference whether it was a pistol evolved with a new gun or an old gun evolved with the pistol

	int damage = 4, speed = 2, range = 60, reloadrate = 100, ammo = 4, firerate = 20;
	//damage is the amount of damage your bullet does
	//speed is how fast your bullet fires, measured in pixels/tick
	//range is how far your bullet fires, measured in pixels
	//reloadrate is how long it takes for your gun to reload, measured in ticks
	//ammo is the amount of times you can shoot before needing to reload
	//firerate is how long it takes before you can shoot again, measure in ticks

	int magazine = 0, cooldown = 0; //temporary variables for ammo, reload, and firerate respectively
	float reloading = 0;
	int barrelxleft = 0, barrelxright = 0, bheight1 = -1, bheight2 = -1; //bullet height and barrel x depends on the gun sprite, used to know where the bullet is firing from

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
	int pierce = 0 ;
	

	Firearm::Firearm(int guntype) //each gun, other than the pistol, doubles one stat (including upgrades) and halves another
	{
		if (guntype == 0 || StartRoom() == true) //pistol, basic gun
		{
			weapon = 1;
			damage = 4, speed = 2, range = 60, reloadrate = 100, ammo = 4, firerate = 20;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 255, bheight2 = -1;
		}

		if (guntype == 1) //sniper, increased range, decreased firerate
		{
			weapon = 2;
			damage = 4, speed = 2, range = 120, reloadrate = 100, ammo = 4, firerate = 40;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 255, bheight2 = -1;
		}

		if (guntype == 2) //shotgun, increased damage, decreased ammo. 
		{
			weapon = 3;
			damage = 8, speed = 2, range = 60, reloadrate = 100, ammo = 2, firerate = 20; 
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 255, bheight2 = -1;
		}

		if (guntype == 3) //minigun, increased firerate, decreased reload rate
		{
			weapon = 4;
			damage = 4, speed = 2, range = 60, reloadrate = 200, ammo = 4, firerate = 10;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 259, bheight2 = -1;
		}

		if (guntype == 4) //twin guns, increased ammo, decreased speed
		{
			weapon = 5;
			damage = 4, speed = 1, range = 60, reloadrate = 100, ammo = 8, firerate = 20;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 254, bheight2 = 252;
		}
		
		//evolved guns. Evolved guns boost the new gun's "increased" stat immediately, while evolving with a pistol boosts the old gun's "decreased" stat immediately
		//boosted stats are boosted by the difference between the new gun and "base" value (see pistol)
		//evolved guns give the new gun's positive multiplier, while evolving with the pistol removes the old gun's negative multiplier.
		//if an evolved gun would give the positive multiplier that the old gun has as a negative multiplier:
		//the strength of the only positive multiplier increases, and the evolved gun gains the new gun's negative multiplier

		if (guntype == 10) // pistol/sniper, increased range
		{
			if (weapon == 1) range += 60; //if the old gun is a pistol, boost range (due to evolving with sniper)
			if (weapon == 2) firerate -= 20; //if the old gun is a sniper, boost firerate (due to evolving with pistol)
			weapon = 12;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 255, bheight2 = -1;
		}
		
		if (guntype == 11) // pistol/shotgun, increased damage
		{
			if (weapon == 1) damage += 4; //if the old gun is a pistol, boost damage (due to evolving with shotgun)
			if (weapon == 3) ammo += 2; //if the old gun is a shotgun, boost ammo (due to evolving with pistol)
			weapon = 13;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 255, bheight2 = -1;
		}

		if (guntype == 12) // pistol/minigun, increased firerate
		{
			if (weapon == 1) firerate -= 10; //if the old gun is a pistol, boost firerate (due to evolving with minigun)
			if (weapon == 4) reloadrate -= 100; //if the old gun is a minigun, boost reloadrate (due to evolving with pistol)
			weapon = 14;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 259, bheight2 = -1;
		}

		if (guntype == 13) // pistol/twin guns, increased ammo
		{
			if (weapon == 1) ammo += 4; //if the old gun is a pistol, boost ammo (due to evolving with twin guns)
			if (weapon == 5) speed += 1; //if the old gun is twin guns, boost speed (due to evolving with pistol)
			weapon = 15;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 255, bheight2 = 253;
		}

		if (guntype == 14) // sniper/shotgun, increased range, increased damage, decreased firerate/ammo
		{
			if (weapon == 2) damage += 4, weapon = 23; //if the old gun is a sniper, boost damage (due to evolving with shotgun). decreased firerate
			if (weapon == 3) range += 60, weapon = 32; //if the old gun is a shotgun, boost range (due to evolving with sniper). decreased ammo
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 255, bheight2 = -1;
		}

		if (guntype == 15) // sniper/minigun, either increased range and firerate or greatly increased range, decreased reloadrate
		{
			if (weapon == 2) firerate -= 20, range += 60, reloadrate += 100, weapon = 24; //if the old gun is a sniper, increase range, boost firerate (due to evolving with minigun). decreased reloadrate
			if (weapon == 4) range += 60, weapon = 42; //if the old gun is a minigun, boost range (due to evolving with sniper). decreased reloadrate
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 259, bheight2 = -1;
		}

		if (guntype == 16) // sniper/twin guns, increased range, increased ammo, decreased firerate/speed
		{
			if (weapon == 2) ammo += 4, weapon = 25; //if the old gun is a sniper, boost ammo (due to evolving with twin guns). decreased firerate
			if (weapon == 5) range += 60, weapon = 52; //if the old gun is twin guns, boost range (due to evolving with sniper). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 255, bheight2 = 253;
		}

		if (guntype == 17) // shotgun/minigun, increased damage, increased firerate, decreased ammo/reloadrate
		{
			if (weapon == 3) firerate -= 10, weapon = 34; //if the old gun is a shotgun, boost firerate (due to evolving with minigun). decreased ammo
			if (weapon == 4) damage += 4, weapon = 43; //if the old gun is a minigun, boost damage (due to evolving with shotgun). decreased reloadrate
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 385, barrelxright = 414, bheight1 = 259, bheight2 = -1;
		}

		if (guntype == 18) // shotgun/twin guns, either increased damage and ammo or greatly increased damage, decreased speed
		{
			if (weapon == 3) ammo += 2, damage += 4, speed -= 1, weapon = 35; //if the old gun is a shotgun, boost ammo (due to evolving with twin guns). decreased speed
			if (weapon == 5) damage += 4, weapon = 53; //if the old gun is twin guns, boost damage (due to evolving with shotgun). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 255, bheight2 = 252;
		}

		if (guntype == 19) // minigun/twin guns, increased firerate, increased ammo, decreased speed/reloadrate
		{
			if (weapon == 4) ammo += 4, weapon = 45; //if the old gun is a minigun, boost ammo (due to evolving with twin guns). decreased reloadrate
			if (weapon == 5) firerate -= 10, weapon = 54; //if the old gun is twin guns, boost firerate (due to evolving with minigun). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 259, bheight2 = 263;
		}


		if (range >= 360) { range = 360; } //hardcap of 360 pixel range
		if (reloadrate < 1) { reloadrate = 1; } //hardcap of 1 tick reload
		if (firerate < 1) { firerate = 1; } //hardcap of 1 tick firerate
	}

	

	void Firearm::upgrade(int damageU, int speedU, int rangeU, int reloadrateU, int ammoU, int firerateU)
	{
		if (weapon == 3 || weapon == 13 || weapon == 23 || weapon == 32 || weapon == 34 || weapon == 43 || weapon == 53) { damage = damage + (damageU * 2); } //doubles damage upgrade amount if shotgun or shotgun variant
		else if (weapon == 35) { damage = damage + (damageU * 2.5); } //greatly doubles upgrade amount for shotgun/twin to make up for the fact it only has one "increased" stat
		else { damage = damage + damageU; } 

		if (weapon == 5 || weapon == 52 || weapon == 35 || weapon == 53 || weapon == 54) { speed = speed + (speedU / 2); } //halves speed upgrade amount if twin guns as first gun
		else { speed = speed + speedU; }

		if (range < 360)
		{
			if (weapon == 2 || weapon == 12 || weapon == 23 || weapon == 32 || weapon == 42 || weapon == 25 || weapon == 52) { range = range + (rangeU * 2); } //doubles range upgrade amount if sniper or sniper variant
			else if (weapon == 24) { range = range + (rangeU * 2.5); } //greatly doubles upgrade amount for sniper/minigun to make up for the fact it only has one "increased" stat
			else { range = range + rangeU; }

			if (range >= 360) { range = 360; } //hardcap of 360 pixel range
		}

		if (reloadrate > 1)
		{
			if (weapon == 4 || weapon == 24 || weapon == 42 || weapon == 43 || weapon == 45) { reloadrate = reloadrate - (reloadrateU / 2); } //halves reload upgrade amount if minigun as first gun
			else { reloadrate = reloadrate - reloadrateU; }

			if (reloadrate < 1) { reloadrate = 1; } //hardcap of 1 tick reload
		}

		if (weapon == 5 || weapon == 15 || weapon == 25 || weapon == 52 || weapon == 53 || weapon == 45 || weapon == 54) { ammo = ammo + (ammoU * 2); } //doubles ammo upgrade amount if twin guns or twin gun variant
		else if (weapon == 3 || weapon == 32 || weapon == 34) { ammo = ammo + (ammoU / 2); } //halves ammo upgrade amount if shotgun as first gun
		else { ammo = ammo + ammoU; }

		if (firerate > 1)
		{
			if (weapon == 4 || weapon == 14 || weapon == 42 || weapon == 34 || weapon == 43 || weapon == 45 || weapon == 54) { firerate = firerate - (firerateU * 2); } //doubles firerate upgrade amount if minigun or minigun variant
			else if (weapon == 2 || weapon == 23 || weapon == 25) { firerate = firerate - (firerateU / 2); } //halves firerate upgrade amount if sniper as first gun
			else { firerate = firerate - firerateU; }

			if (firerate < 1) { firerate = 1; } //hardcap of 1 tick firerate
		}

		magazine = ammo, reloading = reloadrate, cooldown = firerate;
	}

	void Firearm::reload(Surface* screen, float TimeMultiplier)
	{
		int Element = CheckElement();
		if (Element == 0)
		{ 
			colour = 15311424;
			AdditionalDamage = 0;
			pierce = 1;
			
		}
		if (Element == 1)
		{
			colour = 16731904;
			AdditionalDamage = damage / 2;
			pierce = 1;
			
		}
		if (Element == 2)
		{
			colour = 62719;
			AdditionalDamage = 0;
			pierce = 1;
			
		}
		if (Element == 3)
		{
			colour = 16769280;
			AdditionalDamage = 0;
			pierce = 3;
			
		}

		if (magazine == 0)
		{

			if (reloading > 0)
			{

				int j = ((reloading * 100) / reloadrate) * 14;
				screen->Bar(392, 235, 392 + (j / 100), 238, 14483456);

				reloading -= TimeMultiplier;

			}
			else //resets everything
			{
				reloading = reloadrate; 
				magazine = ammo;
				for (int i = 0; i < 10; i++)
				{
					distance[i] = 0;
					direction[i] = 0;
					verticality[i] = 0;
					wallx[i] = 0;
					stop[i] = false;
				}
				projectile = 0;
				BeingHit(screen, 0, 0, 0, 0, 0, 0, -1, 0); //resets projectile value
			}
		}

		//shows your ammo in the ammo bar, however the ammo bar stays the same size so every ammo has to be a correct percentage of the ammo bar, changing the size
		int AmmoBar = (150 - ammo*2) / ammo;

		screen->Bar(50, 410, 48 + (AmmoBar * (magazine)), 430, 1);
		for (int i = 0; i < magazine; i++)
		{
			int segment = 48 + (AmmoBar * i) + 2;
			screen->Bar(segment, 410, 48 + (AmmoBar * (i+1)), 430, colour);
		}
		std::string AmmoDisplay = "Ammo:" + std::to_string(magazine) + "/" + std::to_string(ammo);
		screen->Print(AmmoDisplay.c_str(), 50, 435, 0xE9A240);
	}

	void ManualReload() //if you want to reload when your magazine isnt empty, you can
	{
		if (magazine > 0)
		{
			magazine = 0;
		}
	}

	void Firearm::Fire(Surface* screen, int mousex, int leftmouse, int closestwallx, int left, int right, float charx, float chary, float TimeMultiplier)
	{


		if (magazine > 0 && cooldown == 0 && leftmouse == 1)
		{
			//creates a projectile at the guns barrel
			if (projectile < 20) { projectile++; }
			distance[projectile - 1] = 0;
			if (mousex < 400) { direction[projectile - 1] = -1, initial[projectile - 1] = charx + (barrelxleft) - 1; } 
			if (mousex > 399) { direction[projectile - 1] = 1, initial[projectile - 1] = charx + (barrelxright) + 1; } 

			verticality[projectile - 1] = chary;
			wallx[projectile - 1] = closestwallx;

			firing = true;
			cooldown = firerate;
			magazine--;
			
			for (int i = 0; i < projectile; i++) 
			{
				if (distance[i] >= range) { firing = false; }
				if (distance[i] < range) { firing = true; }
			}
		}

		if (firing == true) //if any bullet is being fired, fires bullet
		{
			for (int i = 0; i < projectile; i++)
			{
				if (distance[i] < range)
				{


					if (stop[i] == false)
					{


						if (direction[i] == 1)
						{

							if (weapon != 5 && weapon != 15 && weapon != 25 && weapon != 35 && weapon != 45 && weapon != 52 && weapon != 53 && weapon != 54) //if the weapon is not a twin gun variant
							{ 
								screen->Line(initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], colour);
								if (BeingHit(screen, initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
								{
									stop[i] = true; //if the bullet hits the pierce cap, it gets removed
								}
							}

							if (weapon == 3 || weapon == 13 || weapon == 23 || weapon == 32 || weapon == 34 || weapon == 43) //any shotgun variant shoot a double bullet
							{ 
								screen->Line(initial[i] + distance[i] - charx, bheight1 + chary - verticality[i] - 1, initial[i] + distance[i] - charx, bheight1 + chary - verticality[i] - 1, colour);
							}

							if (weapon == 5 || weapon == 15 || weapon == 25 || weapon == 45 || weapon == 52 || weapon == 54) //any twin gun variant will alternate shots
							{
								if (alternate[i] == false) 
								{ 
									screen->Line(initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], colour);
									if (BeingHit(screen, initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
								if (alternate[i] == true) 
								{ 
									screen->Line(initial[i] + distance[i] - charx, bheight2 + chary - verticality[i], initial[i] + distance[i] - charx, bheight2 + chary - verticality[i], colour);
									if (BeingHit(screen, initial[i] + distance[i] - charx, bheight2 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
							}

							if (weapon == 35 || weapon == 53) //shotgun/twingun variant alternate shots and shoot a double bullet
							{
								if (alternate[i] == false) 
								{ 
									screen->Line(initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], initial[i] + distance[i] - charx, bheight1 + chary - verticality[i] - 1, colour);
									if (BeingHit(screen, initial[i] + distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
								if (alternate[i] == true) 
								{ 
									screen->Line(initial[i] + distance[i] - charx, bheight2 + chary - verticality[i], initial[i] + distance[i] - charx, bheight2 + chary - verticality[i] - 1, colour);
									if (BeingHit(screen, initial[i] + distance[i] - charx, bheight2 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
							}
							
							if (((barrelxright) + 1 + distance[i] + speed) >= wallx[i]) { stop[i] = true; }

						}


						if (direction[i] == -1)
						{

							if (weapon != 5 && weapon != 15 && weapon != 25 && weapon != 35 && weapon != 45 && weapon != 52 && weapon != 53 && weapon != 54) //if the weapon is not a twin gun variant
							{ 
								screen->Line(initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], colour);
								if (BeingHit(screen, initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
								{
									stop[i] = true;
								}
							}

							if (weapon == 3 || weapon == 13 || weapon == 23 || weapon == 32 || weapon == 34 || weapon == 43) //any shotgun variant shoot a double bullet
							{ 
								screen->Line(initial[i] - distance[i] - charx, bheight1 + chary - verticality[i] - 1, initial[i] - distance[i] - charx, bheight1 + chary - verticality[i] - 1, colour);
							}

							if (weapon == 5 || weapon == 15 || weapon == 25 || weapon == 45 || weapon == 52 || weapon == 54) //any twin gun variant will alternate shots
							{
								if (alternate[i] == false) 
								{ 
									screen->Line(initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], colour);
									if (BeingHit(screen, initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
								if (alternate[i] == true) 
								{ 
									screen->Line(initial[i] - distance[i] - charx, bheight2 + chary - verticality[i], initial[i] - distance[i] - charx, bheight2 + chary - verticality[i], colour);
									if (BeingHit(screen, initial[i] - distance[i] - charx, bheight2 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
							}

							if (weapon == 35 || weapon == 53) //shotgun/twingun variant alternate shots and shoot a double bullet
							{
								if (alternate[i] == false) 
								{ 
									screen->Line(initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], initial[i] - distance[i] - charx, bheight1 + chary - verticality[i] - 1, colour);
									if (BeingHit(screen, initial[i] - distance[i] - charx, bheight1 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
								if (alternate[i] == true) 
								{ 
									screen->Line(initial[i] - distance[i] - charx, bheight2 + chary - verticality[i], initial[i] - distance[i] - charx, bheight2 + chary - verticality[i] - 1, colour);
									if (BeingHit(screen, initial[i] - distance[i] - charx, bheight2 + chary - verticality[i], charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier) == true)
									{
										stop[i] = true;
									}
								}
							}

							if (((barrelxleft) - 1 - distance[i] - speed) <= wallx[i]) { stop[i] = true; }
						}

						distance[i] += (speed * TimeMultiplier);

						



					}
				}
			}
		}

		if (cooldown > 0)
		{
			cooldown--;
		}
	}

	void Firearm::DisplayStats(Surface* screen)
	{
		std::string Damage = "Damage:" + std::to_string(damage);
		std::string Speed = "Speed:" + std::to_string(speed) + "pixels/tick";
		std::string Range = "Range:" + std::to_string(range) + "pixels";
		std::string ReloadSpeed = "Reload Speed:" + std::to_string(reloadrate) + "ticks";
		std::string Ammo = "Ammo:" + std::to_string(ammo);
		std::string ROF = "Rate Of Fire:" + std::to_string(firerate) + "ticks";

		screen->Print(Damage.c_str(), 2, 10, 0xffffff);
		screen->Print(Speed.c_str(), 2, 20, 0xffffff);
		screen->Print(Range.c_str(), 2, 30, 0xffffff);
		screen->Print(ReloadSpeed.c_str(), 2, 40, 0xffffff);
		screen->Print(Ammo.c_str(), 2, 50, 0xffffff);
		screen->Print(ROF.c_str(), 2, 60, 0xffffff);
	}

};