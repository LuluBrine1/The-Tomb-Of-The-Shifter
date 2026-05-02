#include "game.h"
#include "surface.h"
#include "template.h"
#include "Map.h"
#include "Gun.h"
#include "Enemy.h"
#include <windows.h> //used for sleep
#include <cstdio> //used for sprintf
#include <SDL.h> //used for keyboard and mouse input

namespace Tmpl8
{
	int GameState = 1; //1 = main menu, 2 = shop, 0 = actual game, -1 = upgrade intermission, -2 = element choice, 3 is win screen, 4 is loss screen

	//keybinds
	int leftmouse = 0, rightmouse = 0;
	int left = 0, right = 0, space = 0, Ekey = 0, Rkey = 0, Qkey = 0, Reset = 0;

	//loading sprites
	Sprite ElementWheel(new Surface("assets/ElementWheel.png"), 5);
	Sprite MainCharacter(new Surface("assets/MainCharacter.png"), 6);
	Sprite Gun(new Surface("assets/Guns.png"), 10);
	Sprite EvolvedGun(new Surface("assets/EvolvedGuns.png"), 20); //later in the game, you can combine a second gun with your current one
	int guntype = 0; //0 is pistol, 1 is sniper, 2 is shotgun, 3 is minigun, 4 is twin guns. two digit numbers will be evolved guns
	//10 is pistol/sniper, 11 is pistol/shotgun, 12 is pistol/minigun, 13 is pistol/twin, 14 is sniper/shotgun
	//15 is sniper/minigun, 16 is sniper/twin, 17 is shotgun/minigun, 18 is shotgun/twin, 19 is minigun/twin

	TileMap Level;
	Firearm weapon(guntype);

	//hitboxes for the player character. the character never moves so these are important values
	int leftx = 391, rightx = 408, centrex = 400, centrey = 256;
	int topy = 240, bottomy = 271;
	int spritex = 384, spritey = 240;

	//used for movement and animations
	int MoveSpeed = 1;
	float moving = 0;
	float gravity = 0;
	int jumps = 1;

	//shop variables
	int ExtraHealth = 0;
	int Lifesteal = 0;
	int MaxJumps = 1;
	int Money = 0;

	//variables that deal with the map
	int enemies = 0;
	int enter = 0;
	bool ChestCreated = false;
	bool OfferedUpgrade = false;
	int RoomsCleared = 0;

	//element variables
	bool PickElement = false;
	int Element = 0;

	float TimeTaken = 0;
	float GameSpeed = 13.333333333; //caps the game at 75 fps. this is because thats the refresh rate of my monitor
	
	//functions used in other files
	int CheckElement()
	{
		return Element;
	}

	bool StartRoom()
	{
		if (RoomsCleared == 0)
		{
			return true;
		}
		else
			return false;
	}

	int ExtraStartingHealth()
	{
		return ExtraHealth;
	}

	int LifeStealAmount()
	{
		return Lifesteal;
	}

	//keyboard and mouse functions
	void Game::MouseDown(int button)
	{
		if (button == SDL_BUTTON_LEFT)
		{
			leftmouse = 1;
		}
		else if (button == SDL_BUTTON_RIGHT)
		{
			rightmouse = 1;
		}
	}

	void Game::MouseUp(int button)
	{
		if (button == SDL_BUTTON_LEFT)
		{
			leftmouse = 0;
		}
		else if (button == SDL_BUTTON_RIGHT)
		{
			rightmouse = 0;
		}
	}

	void Game::KeyDown(int button)
	{
		if (button == SDL_SCANCODE_A)
		{
			left = 1;
		}
		else if (button == SDL_SCANCODE_D)
		{
			right = 1;
		}
		else if ((button == SDL_SCANCODE_SPACE)|| (button == SDL_SCANCODE_W))
		{
			space = 1;
		}
		else if (button == SDL_SCANCODE_E)
		{
			Ekey = 1;
		}
		else if (button == SDL_SCANCODE_R)
		{
			Rkey = 1;
		}
		else if (button == SDL_SCANCODE_Q)
		{
			Qkey = 1;
		}
		else if (button == SDL_SCANCODE_BACKSPACE)
		{
			Reset += 1;
		}
	}

	void Game::KeyUp(int button)
	{
		if (button == SDL_SCANCODE_A)
		{
			left = 0;
		}
		else if (button == SDL_SCANCODE_D)
		{
			right = 0;
		}
		else if ((button == SDL_SCANCODE_SPACE) || (button == SDL_SCANCODE_W))
		{
			space = 0;
		}
		else if (button == SDL_SCANCODE_E)
		{
			Ekey = 0;
		}
		else if (button == SDL_SCANCODE_R)
		{
			Rkey = 0;
		}
		else if (button == SDL_SCANCODE_Q)
		{
			Qkey = 0;
		}
		else if (button == SDL_SCANCODE_BACKSPACE)
		{
			Reset = 0;
		}
	}

	

	void Game::Init()
	{
		Surface* menu = new Surface("assets/menu-screen.png"); //loads menu screen on game launch
		Pixel* dst = screen->GetBuffer();
		Pixel* src = menu->GetBuffer();
		for (int x = 0; x < ScreenWidth; x++)
			for (int y = 0; y < ScreenHeight; y++)
			{
				dst[x + y * ScreenWidth] = src[x + y * ScreenWidth];
			}

		MainCharacter.SetFrame(0); 
		charx = 32;
		chary = -1056;

		FILE* f = fopen("_ShopInformation.txt", "r");
		fscanf(f, "%d\n%d\n%d\n%d", &ExtraHealth, &Lifesteal, &MaxJumps, &Money);
		fclose(f);
	}
	

	//remembers the carry over variables
	void Game::Shutdown()
	{
		FILE* f = fopen("_ShopInformation.txt", "w");
		fprintf(f, "%d\n%d\n%d\n%d\n", ExtraHealth, Lifesteal, MaxJumps, Money);
		fclose(f);
	}
	

	
	void Game::Tick(float DeltaTime)
	{

		if (GameState == 1) //while in the main menu
		{
			Surface* menu = new Surface("assets/menu-screen.png"); //loads menu screen on game launch
			Pixel* dst = screen->GetBuffer();
			Pixel* src = menu->GetBuffer();
			for (int x = 0; x < ScreenWidth; x++)
				for (int y = 0; y < ScreenHeight; y++)
				{
					dst[x + y * ScreenWidth] = src[x + y * ScreenWidth];
				}

			//sets up all the variables for when entering the game (works on death and winning if you want to do another run)
			MainCharacter.SetFrame(0);
			charx = 32;
			chary = -1056;
			guntype = 0;
			Firearm weapon(0);
			PickElement = false;
			Element = 0;

			char money[300];
			sprintf(money, "Money: % d", Money);
			screen->Print(money, 66, 320, 0xFFFFFF);

			if (leftmouse == 1)
			{
				if ((mousex > 41) && (mousex < 166) && (mousey > 139) && (mousey < 214)) //when the game button is clicked, start game
				{
					//prepares the game for runs
					screen->Clear(0);
					GameState = 0;
					TileMap Level;
					EnemyGeneration(RoomsCleared);
					TimeTaken = 0;
					RoomsCleared = 0;
				}
				if ((mousex > 41) && (mousex < 166) && (mousey > 268) && (mousey < 343)) //when the shop button is clicked, enter shop
				{
					screen->Clear(10052096);
					GameState = 2;
				}
			}
		}

		if (GameState == 2) //the way to permanently upgrade your character to make your future runs easier
		{
			screen->Clear(10052096);

			char extrahealth[300];
			char lifesteal[300];
			char maxjumps[300];
			char money[300];
			char resettext[300];
			char backbutton[16];

			sprintf(extrahealth, "Extra Health: % d", ExtraHealth);
			sprintf(lifesteal, "LifeSteal: % d", Lifesteal);
			sprintf(maxjumps, "Jumps: % d", MaxJumps);
			sprintf(money, "Money: % d", Money);
			sprintf(resettext, "Hold BackSpace to clear your progress!");
			sprintf(backbutton, "BACK");

			screen->Print(extrahealth, 50, 100, 0xFFFFFF);
			screen->Print(lifesteal, 50, 200, 0xFFFFFF);
			screen->Print(maxjumps, 50, 300, 0xFFFFFF);
			screen->Print(money, 600, 250, 0xFFFFFF);
			screen->Print(resettext, 500, 50, 0xFFFFFF);

			screen->Bar(0, 0, 50, 50, 0x888888);
			screen->Print(backbutton, 16, 22, 0xFFFFFF);

			screen->Bar(575, 60, 650, 65, 0x0);
			screen->Bar(575, 60, 575 + Reset, 65, 0xFF0000);


			screen->Bar(50, 110, 300, 170, 1);
			for (int i = 0; i < ExtraHealth/2; i++)
			{
				int segment = 48 + 50*i;
				screen->Bar(segment + 2, 110, segment + 50, 170, 0x00dd00);
			}
			
			screen->Bar(50, 210, 300, 270, 1);
			for (int i = 0; i < Lifesteal; i++)
			{
				int segment = 48 + 50 * i;
				screen->Bar(segment + 2, 210, segment + 50, 270, 0x00dd00);
			}

			screen->Bar(50, 310, 300, 370, 1);
			for (int i = 0; i < MaxJumps - 1; i++)
			{
				int segment = 48 + 50 * i;
				screen->Bar(segment + 2, 310, segment + 50, 370, 0x00dd00);
			}

			int HealthPrice[5] = { 100, 200, 300, 400, 500 };
			int LifestealPrice[5] = { 300, 350, 400, 450, 500 };
			int MaxjumpPrice[5] = { 500, 550, 600, 650, 700 };

		
			if (ExtraHealth < 10)
			{
				char BuyHealth[300];
				sprintf(BuyHealth, "%d", HealthPrice[ExtraHealth / 2]);
				screen->Bar(375, 130, 425, 150, 0x888888);
				screen->Print(BuyHealth, 392, 138, 0xFFFFFF);
			}

			if (Lifesteal < 5)
			{
				char BuyLifesteal[300];
				sprintf(BuyLifesteal, "%d", LifestealPrice[Lifesteal]);
				screen->Bar(375, 230, 425, 250, 0x888888);
				screen->Print(BuyLifesteal, 392, 238, 0xFFFFFF);
			}

			if (MaxJumps - 1 < 5)
			{
				char BuyJumps[300];
				sprintf(BuyJumps, "%d", MaxjumpPrice[MaxJumps - 1]);
				screen->Bar(375, 330, 425, 350, 0x888888);
				screen->Print(BuyJumps, 392, 338, 0xFFFFFF);
			}



			if (Reset > 74)
			{
				ExtraHealth = 0;
				MaxJumps = 1;
				Lifesteal = 0;
				Money = 0;
				Reset = 0;
			}

			
			if (leftmouse == 1)
			{
				if ((mousex > 0) && (mousex < 50) && (mousey > 0) && (mousey < 50))
				{
					GameState = 1;
				}
				else if ((mousex > 375) && (mousex < 425) && (mousey > 130) && (mousey < 150) && (ExtraHealth / 2) < 5)
				{
					if (Money > HealthPrice[(ExtraHealth / 2)])
					{
						Money -= HealthPrice[(ExtraHealth / 2)];
						ExtraHealth += 2;
						Sleep(2000 / DeltaTime);
					}
				}
				else if ((mousex > 375) && (mousex < 425) && (mousey > 230) && (mousey < 250) && Lifesteal < 5)
				{
					if (Money > LifestealPrice[Lifesteal])
					{
						Money -= LifestealPrice[Lifesteal];
						Lifesteal += 1;
						Sleep(2000 / DeltaTime);
					}
				}
				else if ((mousex > 375) && (mousex < 425) && (mousey > 330) && (mousey < 350) && MaxJumps - 1 < 5)
				{
					if (Money > MaxjumpPrice[MaxJumps - 1])
					{
						Money -= MaxjumpPrice[MaxJumps - 1];
						MaxJumps += 1;
						Sleep(2000 / DeltaTime);
					}
				}
			}

		}

		if (GameState == 3) //win
		{
			screen->Clear(52224);
			char Win[32];
			sprintf(Win, "YOU WIN!");
			screen->Print(Win, 384, 256, 0xFFFFFF);

			if (leftmouse == 1)
			{
				GameState = 1;
				RoomsCleared = 0;
				Sleep(50);
			}
			else
				GameState = 3;

		}

		if (GameState == 4) //death
		{
			screen->Clear(1);
			char Death[32];
			sprintf(Death, "YOU DIED");
			screen->Print(Death, 384, 256, 0xFF0000);
			if (leftmouse == 1)
			{
				GameState = 1;
				RoomsCleared = 0;
				Sleep(50);
			}
		}

		if (GameState == -1) //negative gamestates happen during the main run, this one offers upgrades
		{

			if (OfferedUpgrade == false)
			{
				screen->Clear(12368677);
				Level.OfferUpgrade(screen);
				weapon.DisplayStats(screen);
				OfferedUpgrade = true;
			}
			if (OfferedUpgrade == true);
			{
				int selection = -1;
				if (leftmouse == 1)
				{
					if ((mousex > 125) && (mousex < 275) && (mousey > 106) && (mousey < 406))
					{
						selection = 0;
					}
					else if ((mousex > 325) && (mousex < 475) && (mousey > 106) && (mousey < 406))
					{
						selection = 1;
					}
					else if ((mousex > 525) && (mousex < 675) && (mousey > 106) && (mousey < 406))
					{
						selection = 2;
					}
					//once youve selected your upgrade, the game will upgrade/change your gun
					if (selection != -1)
					{
						Level.SelectUpgrade(selection);
						if (Level.SelectUpgrade(selection) < 10) //less than 10 is basic guns, 10-100 is upgraded guns
						{
							guntype = Level.SelectUpgrade(selection);
							Firearm weapon(guntype);
						}
						else if (Level.SelectUpgrade(selection) < 100 && Level.SelectUpgrade(selection) > 10)
						{
							if (guntype == 0)
							{
								if (Level.SelectUpgrade(selection) == 12) { guntype = 10; }
								if (Level.SelectUpgrade(selection) == 13) { guntype = 11; }
								if (Level.SelectUpgrade(selection) == 14) { guntype = 12; }
								if (Level.SelectUpgrade(selection) == 15) { guntype = 13; }
							}
							if (guntype == 1)
							{
								if (Level.SelectUpgrade(selection) == 11) { guntype = 10; }
								if (Level.SelectUpgrade(selection) == 13) { guntype = 14; }
								if (Level.SelectUpgrade(selection) == 14) { guntype = 15; }
								if (Level.SelectUpgrade(selection) == 15) { guntype = 16; }
							}
							if (guntype == 2)
							{
								if (Level.SelectUpgrade(selection) == 11) { guntype = 11; }
								if (Level.SelectUpgrade(selection) == 12) { guntype = 14; }
								if (Level.SelectUpgrade(selection) == 14) { guntype = 17; }
								if (Level.SelectUpgrade(selection) == 15) { guntype = 18; }
							}
							if (guntype == 3)
							{
								if (Level.SelectUpgrade(selection) == 11) { guntype = 12; }
								if (Level.SelectUpgrade(selection) == 12) { guntype = 15; }
								if (Level.SelectUpgrade(selection) == 13) { guntype = 17; }
								if (Level.SelectUpgrade(selection) == 15) { guntype = 19; }
							}
							if (guntype == 4)
							{
								if (Level.SelectUpgrade(selection) == 11) { guntype = 13; }
								if (Level.SelectUpgrade(selection) == 12) { guntype = 16; }
								if (Level.SelectUpgrade(selection) == 13) { guntype = 18; }
								if (Level.SelectUpgrade(selection) == 14) { guntype = 19; }
							}

							Firearm weapon(guntype);
						}
						//gun upgrades
						else if (Level.SelectUpgrade(selection) == 101) { weapon.upgrade(2, 0, 0, 0, 0, 0); }
						else if (Level.SelectUpgrade(selection) == 102) { weapon.upgrade(0, 1, 0, 0, 0, 0); }
						else if (Level.SelectUpgrade(selection) == 103) { weapon.upgrade(0, 0, 30, 0, 0, 0); }
						else if (Level.SelectUpgrade(selection) == 104) { weapon.upgrade(0, 0, 0, 10, 0, 0); }
						else if (Level.SelectUpgrade(selection) == 105) { weapon.upgrade(0, 0, 0, 0, 2, 0); }
						else if (Level.SelectUpgrade(selection) == 106) { weapon.upgrade(0, 0, 0, 0, 0, 2); }
						//game back to main run
						GameState = 0;
					}


					Sleep(20);
				}
			}

		}

		if (GameState == -2) //selecting your element. different gamestate to be able to pause your game
		{
			ElementWheel.Draw(screen, 144, 0);
			if (mousex > 144 && mousex < 207 + 144 && mousey < 207)
			{
				ElementWheel.SetFrame(1);
				if (leftmouse == 1)
					GameState = 0, Element = 0;
			}
			else if (mousex > 304 + 144 && mousex < 512 + 144 && mousey < 207)
			{
				ElementWheel.SetFrame(2);
				if (leftmouse == 1)
					GameState = 0, Element = 1;
			}
			else if (mousex > 304 + 144 && mousex < 512 + 144 && mousey > 304)
			{
				ElementWheel.SetFrame(3);
				if (leftmouse == 1)
					GameState = 0, Element = 2;
			}
			else if (mousex > 144 && mousex < 207 + 144 && mousey > 304)
			{
				ElementWheel.SetFrame(4);
				if (leftmouse == 1)
					GameState = 0, Element = 3;
			}
			else
				ElementWheel.SetFrame(0);

			leftmouse = 0;
		}
		
		if (GameState == 0) //during the actual game
		{

			if (int(TimeTaken / GameSpeed) > int((TimeTaken - DeltaTime) / GameSpeed)) //next movement only happens if the frame coincides with the 75 fps rate
			{


				if (Element == 0 && PickElement == true) //if you have no element active, your move speed is doubled.
				{
					MoveSpeed = 2; //this is because i wanted there to be a reason to not have an element, and also to make it quicker to exit a room and such
				}
				else
				{
					MoveSpeed = 1;
				}

				//character movement and spritework
				if (left == 1)
				{
					if (Collision(leftx - MoveSpeed, topy, charx, chary) == false && Collision(leftx - MoveSpeed, bottomy, charx, chary) == false) //prevents walking into walls
					{
						charx -= MoveSpeed;
					}
					moving += 0.1;
				}

				if (right == 1)
				{
					if (Collision(rightx + MoveSpeed, topy, charx, chary) == false && Collision(rightx + MoveSpeed, bottomy, charx, chary) == false) //prevents walking into walls
					{
						charx += MoveSpeed;
					}
					moving += 0.1;
				}

				if (space == 1)
				{
					if (Collision(leftx, bottomy + 1, charx, chary) == true || Collision(rightx, bottomy + 1, charx, chary) == true || jumps > 0) //you can only jump if youre on the floor or have more jumps
						gravity = 4.7, jumps -= 1, space = 0;
				}

				if (space == 0)
				{
					if (Collision(leftx, bottomy + 1, charx, chary) == true || Collision(rightx, bottomy + 1, charx, chary) == true) //when grounded, reset jumps and gravity
						if (gravity < 0) gravity = 0, jumps = MaxJumps;
				}

				chary += gravity;
				gravity -= 0.1;

				//facing direction independent of moving direction direction so you can shoot whichever direction while moving
				if (mousex < 400) 
				{
					if (left == 1 || right == 1)
					{
						MainCharacter.SetFrame(4 + ((int)moving % 2));
					}

					if ((left == 0 && right == 0) || (Collision(leftx, bottomy + 1, charx, chary) == false && Collision(rightx, bottomy + 1, charx, chary) == false))
					{
						MainCharacter.SetFrame(3);
					}

					if (guntype < 10) { Gun.SetFrame(5 + guntype); }
					if (guntype >= 10) { EvolvedGun.SetFrame(guntype); }
				}

				if (mousex > 399)
				{
					if (left == 1 || right == 1)
					{
						MainCharacter.SetFrame(1 + ((int)moving % 2));
					}

					if ((left == 0 && right == 0) || (Collision(leftx, bottomy + 1, charx, chary) == false && Collision(rightx, bottomy + 1, charx, chary) == false))
					{
						MainCharacter.SetFrame(0);
					}

					if (guntype < 10) { Gun.SetFrame(guntype); }
					if (guntype >= 10) { EvolvedGun.SetFrame(guntype - 10); }
				}

				//if you are in the floor somehow, fixes it
				while (Collision(leftx, bottomy, charx, chary) == true || Collision(rightx, bottomy, charx, chary) == true)
				{
					chary++;
				}
				while (Collision(leftx, topy, charx, chary) == true || Collision(rightx, topy, charx, chary) == true)
				{
					chary--;
					gravity = 0;
				}


				int closestwallx = centrex; //needed for bullet collision values

				while (Collision(closestwallx, 255, charx, chary) == false)
				{
					if (mousex < 400) { closestwallx--; }
					if (mousex > 399) { closestwallx++; }
				}

				if (Rkey == 1)
				{
					ManualReload();
				}


				//main gameplay loop: clear and draw map, draw character and gun, Enemies and projectile act, check if gun is reloading and firing

				screen->Clear(22222);
				Level.DrawMap(screen, charx, chary);
				MainCharacter.Draw(screen, spritex, spritey);
				if (guntype < 10) { Gun.Draw(screen, spritex, spritey); }
				if (guntype >= 10) { EvolvedGun.Draw(screen, spritex, spritey); }
				EnemyAction(screen, charx, chary);
				ProjectileAction(screen, charx, chary);
				weapon.reload(screen);
				weapon.Fire(screen, mousex, leftmouse, closestwallx, left, right, charx, chary);
				enemies = EnemyCount(screen);






				if (CheckDeath() == true)
				{
					GameState = 4;
				}

				if (Qkey == 1 && PickElement == true) 
				{
					GameState = -2;
				}


				if (enemies == 0)
				{
					if (Bossroom() == true) //win condition
					{
						Sleep(150);
						GameState = 3;
					}
					else
					{


						if (ChestCreated == false) //chest can only be created on solid ground
						{
							Level.CreateChest(centrex, centrey, charx, chary);
							ChestCreated = Level.CreateChest(centrex, centrey, charx, chary);
						}

						if (Ekey == 1 && OfferedUpgrade == false) //you cannot open a chest youve already opened
						{
							if (Level.ChestInteraction(centrex, centrey, charx, chary) == true)
							{
								Money += (20 + (RoomsCleared * 8));
								RoomsCleared += 1;
								GameState = -1;
								PickElement = true;
							}
						}

						Level.CreateExits(); //you can leave without opening the chest if you want to
						enter = Level.Exit(leftx, rightx, topy, bottomy, charx, chary);

						if (enter != 0) //sets up the next room
						{
							TileMap Level;
							if (enter == 1) { charx = 26 * 32, chary = -31 * 32; }
							if (enter == 2) { charx = 9 * 32, chary = -31 * 32; }
							if (enter == 3) { charx = 1 * 32, chary = -18 * 32 - 16; }
							if (enter == 4) { charx = 34 * 32, chary = -18 * 32 - 16; }
							ChestCreated = false;
							OfferedUpgrade = false;
							EnemyGeneration(RoomsCleared);
						}
					}
				}
			}
			

			TimeTaken += DeltaTime;
		}
		
	}
};
