#include "Gun.h"
#include "Enemy.h"
#include "surface.h"
#include "game.h"
#include <cstdio> //used for sprintf
#include <string>


namespace Tmpl8
{
	Firearm::Firearm() 
	{}

	void Firearm::change(int guntype) //each gun, other than the pistol, doubles one stat (including upgrades) and halves another
	{
		switch (guntype)
		{
		case 0: //pistol, basic gun
			weapon = 1;
			damage = 4, speed = 2, range = 60, reloadrate = 100, ammo = 4, firerate = 20;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 256, bheight2 = -1;
			break;

		case 1: //sniper, increased range, decreased firerate
			weapon = 2;
			damage = 4, speed = 2, range = 120, reloadrate = 100, ammo = 4, firerate = 40;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 256, bheight2 = -1;
			break;

		case 2: //shotgun, increased damage, decreased ammo.
			weapon = 3;
			damage = 8, speed = 2, range = 60, reloadrate = 100, ammo = 2, firerate = 20;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 256, bheight2 = -1;
			break;

		case 3: //minigun, increased firerate, decreased reload rate
			weapon = 4;
			damage = 4, speed = 2, range = 60, reloadrate = 200, ammo = 4, firerate = 10;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 260, bheight2 = -1;
			break;

		case 4: //twin guns, increased ammo, decreased speed
			weapon = 5;
			damage = 4, speed = 1, range = 60, reloadrate = 100, ammo = 8, firerate = 20;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 255, bheight2 = 253;
			break;
		}
	}

	void Firearm::evolve(int guntype)
	{
		//evolved guns. Evolved guns boost the new gun's "increased" stat immediately, while evolving with a pistol boosts the old gun's "decreased" stat immediately
		//boosted stats are boosted by the difference between the new gun and "base" value (see pistol)
		//evolved guns give the new gun's positive multiplier, while evolving with the pistol removes the old gun's negative multiplier.
		//if an evolved gun would give the positive multiplier that the old gun has as a negative multiplier:
		//the strength of the only positive multiplier increases, and the evolved gun gains the new gun's negative multiplier
		switch (guntype)
		{
		case 10: // pistol/sniper, increased range
			if (weapon == 1) range += 60; //if the old gun is a pistol, boost range (due to evolving with sniper)
			if (weapon == 2) firerate -= 20; //if the old gun is a sniper, boost firerate (due to evolving with pistol)
			weapon = 12;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 256, bheight2 = -1;
			break;

		case 11: // pistol/shotgun, increased damage
			if (weapon == 1) damage += 4; //if the old gun is a pistol, boost damage (due to evolving with shotgun)
			if (weapon == 3) ammo += 2; //if the old gun is a shotgun, boost ammo (due to evolving with pistol)
			weapon = 13;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 256, bheight2 = -1;
			break;

		case 12: // pistol/minigun, increased firerate
			if (weapon == 1) firerate -= 10; //if the old gun is a pistol, boost firerate (due to evolving with minigun)
			if (weapon == 4) reloadrate -= 100; //if the old gun is a minigun, boost reloadrate (due to evolving with pistol)
			weapon = 14;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 260, bheight2 = -1;
			break;

		case 13: // pistol/twin guns, increased ammo
			if (weapon == 1) ammo += 4; //if the old gun is a pistol, boost ammo (due to evolving with twin guns)
			if (weapon == 5) speed += 1; //if the old gun is twin guns, boost speed (due to evolving with pistol)
			weapon = 15;
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 387, barrelxright = 412, bheight1 = 256, bheight2 = 254;
			break;

		case 14: // sniper/shotgun, increased range, increased damage, decreased firerate/ammo
			if (weapon == 2) damage += 4, weapon = 23; //if the old gun is a sniper, boost damage (due to evolving with shotgun). decreased firerate
			if (weapon == 3) range += 60, weapon = 32; //if the old gun is a shotgun, boost range (due to evolving with sniper). decreased ammo
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 256, bheight2 = -1;
			break;

		case 15: // sniper/minigun, either increased range and firerate or greatly increased range, decreased reloadrate
			if (weapon == 2) firerate -= 20, range += 60, reloadrate += 100, weapon = 24; //if the old gun is a sniper, increase range, boost firerate (due to evolving with minigun). decreased reloadrate
			if (weapon == 4) range += 60, weapon = 42; //if the old gun is a minigun, boost range (due to evolving with sniper). decreased reloadrate
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 260, bheight2 = -1;
			break;

		case 16: // sniper/twin guns, increased range, increased ammo, decreased firerate/speed
			if (weapon == 2) ammo += 4, weapon = 25; //if the old gun is a sniper, boost ammo (due to evolving with twin guns). decreased firerate
			if (weapon == 5) range += 60, weapon = 52; //if the old gun is twin guns, boost range (due to evolving with sniper). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 384, barrelxright = 415, bheight1 = 256, bheight2 = 254;
			break;

		case 17: // shotgun/minigun, increased damage, increased firerate, decreased ammo/reloadrate
			if (weapon == 3) firerate -= 10, weapon = 34; //if the old gun is a shotgun, boost firerate (due to evolving with minigun). decreased ammo
			if (weapon == 4) damage += 4, weapon = 43; //if the old gun is a minigun, boost damage (due to evolving with shotgun). decreased reloadrate
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 385, barrelxright = 414, bheight1 = 260, bheight2 = -1;
			break;

		case 18: // shotgun/twin guns, either increased damage and ammo or greatly increased damage, decreased speed
			if (weapon == 3) ammo += 2, damage += 4, speed -= 1, weapon = 35; //if the old gun is a shotgun, boost ammo (due to evolving with twin guns). decreased speed
			if (weapon == 5) damage += 4, weapon = 53; //if the old gun is twin guns, boost damage (due to evolving with shotgun). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 256, bheight2 = 253;
			break;

		case 19: // minigun/twin guns, increased firerate, increased ammo, decreased speed/reloadrate
			if (weapon == 4) ammo += 4, weapon = 45; //if the old gun is a minigun, boost ammo (due to evolving with twin guns). decreased reloadrate
			if (weapon == 5) firerate -= 10, weapon = 54; //if the old gun is twin guns, boost firerate (due to evolving with minigun). decreased speed
			magazine = ammo, reloading = reloadrate, cooldown = firerate;
			barrelxleft = 386, barrelxright = 413, bheight1 = 260, bheight2 = 264;
			break;
		}

		if (range >= 360) { range = 360; } //hardcap of 360 pixel range
		if (reloadrate < 1) { reloadrate = 1; } //hardcap of 1 tick reload
		if (firerate < 1) { firerate = 1; } //hardcap of 1 tick firerate
	}

	

	void Firearm::upgrade(int damageU, float speedU, int rangeU, float reloadrateU, int ammoU, int firerateU)
	{
		bool upgraded = false;

		for (int w = 0; w < 8; w++) //checks for boosted or nerfed upgrades
		{
			if (!upgraded)
			{
				if (weapon == Shotguns[w] && damageU > 0)
				{
					damage = damage + (damageU * 2); //doubles damage upgrade amount if shotgun or shotgun variant
					if (weapon == 35) { damage = damage + (damageU * 0.5); } //greatly doubles upgrade amount for shotgun/twin to make up for the fact it only has one "increased" stat
					upgraded = true;
				}

				if (((weapon == Twinguns[w] && w < 4) || weapon == 35) && speedU > 0) //halves speed upgrade amount if twin guns as first gun or your gun is shotgun/twin
				{
					speed = speed + (speedU / 2);
					upgraded = true;
				}

				if (weapon == Snipers[w] && rangeU > 0)
				{
					range = range + (rangeU * 2); //doubles range upgrade amount if sniper or sniper variant
					if (weapon == 24) { range = range + (rangeU * 0.5); } //greatly doubles upgrade amount for sniper/minigun to make up for the fact it only has one "increased" stat
					upgraded = true;
				}

				if (((weapon == Miniguns[w] && w < 4) || weapon == 24) && reloadrateU > 0) //halves reload upgrade amount if minigun as first gun or your gun is sniper/minigun
				{
					reloadrate = reloadrate - (reloadrateU / 2);
					upgraded = true;
				}

				if (weapon == Twinguns[w] && weapon != 35 && ammoU > 0) //doubles ammo upgrade amount if twin guns or twin gun variant but not for shotgun/twin
				{
					ammo = ammo + (ammoU * 2);
					upgraded = true;
				}
				else if (weapon == Shotguns[w] && w < 3 && ammoU > 0) //halves ammo upgrade amount if shotgun as first gun, w < 3 not 4 to exclude shotgun/twin
				{
					ammo = ammo + (ammoU / 2);
					upgraded = true;
				}

				if (weapon == Miniguns[w] && weapon != 24 && firerateU > 0) //doubles firerate upgrade amount if minigun or minigun variant but not for sniper/minigun
				{
					firerate = firerate - (firerateU * 2);
					upgraded = true;
				}
				else if (weapon == Snipers[w] && w < 4 && weapon != 24 && firerateU > 0) //halves firerate upgrade amount if sniper as first gun but not for sniper/minigun
				{
					firerate = firerate - (firerateU / 2);
					upgraded = true;
				}
			}
		}

		if (!upgraded)
		{
			damage = damage + damageU;
			speed = speed + speedU;
			range = range + rangeU;
			reloadrate = reloadrate - reloadrateU;
			ammo = ammo + ammoU;
			firerate = firerate - firerateU;
		}

		if (range >= 360) { range = 360; } //hardcap of 360 pixel range
		if (reloadrate < 1) { reloadrate = 1; } //hardcap of 1 tick reload
		if (firerate < 1) { firerate = 1; } //hardcap of 1 tick firerate

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

				float j = ((reloading * 100) / reloadrate) * 14;
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

	void Firearm::ManualReload() //if you want to reload when your magazine isnt empty, you can
	{
		if (magazine > 0)
		{
			magazine = 0;
		}
	}

	void Firearm::Shoot(Surface* screen, float charx, float chary, int i, float TimeMultiplier)
	{
		float x = initial[i] - charx + (distance[i] * direction[i]); //when the bullet is shooting to the right, +distance, when shooting to the left, -distance
		float y1 = bheight1 + chary - verticality[i];
		float y2 = bheight2 + chary - verticality[i];
		bool shotgun = false;
		bool twinguns = false;
		
		for (int w = 0; w < 8; w++)
		{
			if (weapon == Shotguns[w]) { shotgun = true; } //any shotgun variant shoot a double bullet
			if (weapon == Twinguns[w]) { twinguns = true; }
		}

		if (twinguns && alternate[i]) //any twin gun variant will alternate shots
		{
			screen->Line(x, y2, x, y2 - shotgun, colour);
			if (BeingHit(screen, x, y2, charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier)) { stop[i] = true; }//if the bullet hits the pierce cap, it gets removed
		}
		else
		{
			screen->Line(x, y1, x, y1 - shotgun, colour);
			if (BeingHit(screen, x, y1, charx, chary, damage + AdditionalDamage, pierce, i, TimeMultiplier)) { stop[i] = true; }//if the bullet hits the pierce cap, it gets removed
		}

	}

	void Firearm::Fire(Surface* screen, int mousex, int leftmouse, int closestwallx, float charx, float chary, float TimeMultiplier)
	{


		if (magazine > 0 && cooldown == 0 && leftmouse)
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
					if (!stop[i])
					{
						Shoot(screen, charx, chary, i, TimeMultiplier);

						if ((barrelxright + 1 + distance[i] + speed) >= wallx[i] && direction[i] == 1) { stop[i] = true; }
						if ((barrelxleft - 1 - distance[i] - speed) <= wallx[i] && direction[i] == -1) { stop[i] = true; }
						
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
		std::string Speed = "Speed:" + std::to_string(speed) + " pixels/tick";
		std::string Range = "Range:" + std::to_string(range) + " pixels";
		std::string ReloadSpeed = "Reload Speed:" + std::to_string(reloadrate) + " ticks";
		std::string Ammo = "Ammo:" + std::to_string(ammo);
		std::string ROF = "Rate Of Fire:" + std::to_string(firerate) + " ticks";

		screen->Print(Damage.c_str(), 2, 10, 0xffffff);
		screen->Print(Speed.c_str(), 2, 20, 0xffffff);
		screen->Print(Range.c_str(), 2, 30, 0xffffff);
		screen->Print(ReloadSpeed.c_str(), 2, 40, 0xffffff);
		screen->Print(Ammo.c_str(), 2, 50, 0xffffff);
		screen->Print(ROF.c_str(), 2, 60, 0xffffff);
	}

};