#include "game.h"
#include "surface.h"
#include "template.h"
#include "Map.h"
#include "Gun.h"
#include "Enemy.h"
#include <windows.h> //used for sleep
#include <cstdio> //used for sprintf
#include <SDL.h> //used for keyboard and mouse input
#include <string>

namespace Tmpl8
{
	enum GameState
	{
		MainMenu,
		Shop,
		Run,
		Upgrade,
		ElementSelect,
		Win,
		Loss
	};
	GameState gameState = MainMenu;

	//keybinds
	int leftmouse = 0, rightmouse = 0;
	bool left = 0, right = 0, space = 0, Ekey = 0, Rkey = 0, Qkey = 0;
	int Reset = 0;

	//loading sprites
	Sprite ElementWheel(new Surface("assets/ElementWheel.png"), 5);
	Sprite MainCharacter(new Surface("assets/MainCharacter.png"), 6);
	Sprite Gun(new Surface("assets/Guns.png"), 10);
	Sprite EvolvedGun(new Surface("assets/EvolvedGuns.png"), 20); //later in the game, you can combine a second gun with your current one
	enum GunType
	{
		pistol = 0,
		sniper = 1,
		shotgun = 2,
		minigun = 3,
		twinguns = 4,
		pistolsniper = 10,
		pistolshotgun = 11,
		pistolminigun = 12,
		pistoltwin = 13,
		snipershotgun = 14,
		sniperminigun = 15,
		snipertwin = 16,
		shotgunminigun = 17,
		shotguntwin = 18,
		miniguntwin = 19
	};
	GunType guntype = pistol; 

	Surface* menu = new Surface("assets/menu-screen.png");

	TileMap Level;
	Firearm weapon{ 0 };

	//hitboxes for the player character. the character never moves so these are important values
	const int leftx = 391, rightx = 408, centrex = 400, centrey = 256;
	const int topy = 240, bottomy = 271;
	const int spritex = 384, spritey = 240;

	//used for movement and animations
	float MoveSpeed = 1;
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
	//float GameSpeed = 23.333333333;

	//functions used in other files
	int CheckElement()
	{
		return Element;
	}

	bool StartRoom()
	{
		return (RoomsCleared == 0);
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
			leftmouse = true;
		}
		else if (button == SDL_BUTTON_RIGHT)
		{
			rightmouse = true;
		}
	}

	void Game::MouseUp(int button)
	{
		if (button == SDL_BUTTON_LEFT)
		{
			leftmouse = false;
		}
		else if (button == SDL_BUTTON_RIGHT)
		{
			rightmouse = false;
		}
	}

	void Game::KeyDown(int button)
	{
		if (button == SDL_SCANCODE_A)
		{
			left = true;
		}
		else if (button == SDL_SCANCODE_D)
		{
			right = true;
		}
		else if ((button == SDL_SCANCODE_SPACE) || (button == SDL_SCANCODE_W))
		{
			space = true;
		}
		else if (button == SDL_SCANCODE_E)
		{
			Ekey = true;
		}
		else if (button == SDL_SCANCODE_R)
		{
			Rkey = true;
		}
		else if (button == SDL_SCANCODE_Q)
		{
			Qkey = true;
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
			left = false;
		}
		else if (button == SDL_SCANCODE_D)
		{
			right = false;
		}
		else if ((button == SDL_SCANCODE_SPACE) || (button == SDL_SCANCODE_W))
		{
			space = false;
		}
		else if (button == SDL_SCANCODE_E)
		{
			Ekey = false;
		}
		else if (button == SDL_SCANCODE_R)
		{
			Rkey = false;
		}
		else if (button == SDL_SCANCODE_Q)
		{
			Qkey = false;
		}
		else if (button == SDL_SCANCODE_BACKSPACE)
		{
			Reset = 0;
		}
	}

	void Game::SetStart()
	{
		//sets up all the variables for when entering the game (works on death and winning if you want to do another run)
		gameState = MainMenu;
		MainCharacter.SetFrame(0);
		charx = 32;
		chary = -1056;
		guntype = pistol;
		Firearm weapon{ 0 };
		PickElement = false;
		Element = 0;
		RoomsCleared = 0;
	}

	void Game::TickMainMenu()
	{
		Pixel* dst = screen->GetBuffer();
		Pixel* src = menu->GetBuffer();
		for (int x = 0; x < ScreenWidth; x++)
			for (int y = 0; y < ScreenHeight; y++)
			{
				dst[x + y * ScreenWidth] = src[x + y * ScreenWidth];
			}

		std::string money = "Money:" + std::to_string(Money);
		screen->Print(money.c_str(), 66, 320, 0xFFFFFF);

		if (leftmouse)
		{
			if ((mousex > 41) && (mousex < 166) && (mousey > 139) && (mousey < 214)) //when the game button is clicked, start game
			{
				//prepares the game for runs
				screen->Clear(0);
				gameState = Run;
				TileMap Level;
				EnemyGeneration(RoomsCleared);
				TimeTaken = 0;
				RoomsCleared = 0;
			}
			if ((mousex > 41) && (mousex < 166) && (mousey > 268) && (mousey < 343)) //when the shop button is clicked, enter shop
			{
				gameState = Shop;
			}
		}
	}

	void Game::TickShop()
	{
		screen->Clear(0x996200);

		std::string extrahealth = "Extra Health:" + std::to_string(ExtraHealth);
		std::string lifesteal = "Lifesteal:" + std::to_string(Lifesteal);
		std::string maxjumps = "Jumps:" + std::to_string(MaxJumps);
		std::string money = "Money:" + std::to_string(Money);
		std::string resettext = "Hold BackSpace to clear your progress!";
		std::string backbutton = "BACK";

		screen->Print(extrahealth.c_str(), 50, 100, 0xFFFFFF);
		screen->Print(lifesteal.c_str(), 50, 200, 0xFFFFFF);
		screen->Print(maxjumps.c_str(), 50, 300, 0xFFFFFF);
		screen->Print(money.c_str(), 600, 250, 0xFFFFFF);

		screen->Print(resettext.c_str(), 500, 50, 0xFFFFFF);
		screen->Bar(0, 0, 50, 50, 0x888888);
		screen->Print(backbutton.c_str(), 16, 22, 0xFFFFFF);

		screen->Bar(575, 60, 650, 65, 0x0);
		screen->Bar(575, 60, 575 + Reset, 65, 0xFF0000);


		screen->Bar(50, 110, 300, 170, 1);
		for (int i = 0; i < ExtraHealth / 2; i++)
		{
			int segment = 48 + 50 * i;
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

		int HealthPrice[6] = { 100, 200, 300, 400, 500, 9999 };
		int LifestealPrice[6] = { 300, 350, 400, 450, 500, 9999 };
		int MaxjumpPrice[6] = { 500, 550, 600, 650, 700, 9999 };

		if (ExtraHealth < 10)
		{
			std::string BuyHealth = std::to_string(HealthPrice[ExtraHealth / 2]);
			screen->Bar(375, 130, 425, 150, 0x888888);
			screen->Print(BuyHealth.c_str(), 392, 138, 0xFFFFFF);
		}

		if (Lifesteal < 5)
		{
			std::string BuyLifesteal = std::to_string(LifestealPrice[Lifesteal]);
			screen->Bar(375, 230, 425, 250, 0x888888);
			screen->Print(BuyLifesteal.c_str(), 392, 238, 0xFFFFFF);
		}

		if (MaxJumps - 1 < 5)
		{
			std::string BuyJumps = std::to_string(MaxjumpPrice[MaxJumps - 1]);
			screen->Bar(375, 330, 425, 350, 0x888888);
			screen->Print(BuyJumps.c_str(), 392, 338, 0xFFFFFF);
		}

		if (Reset > 74)
		{
			ExtraHealth = 0;
			MaxJumps = 1;
			Lifesteal = 0;
			Money = 0;
			Reset = 0;
		}

		if (leftmouse)
		{
			if ((mousex > 0) && (mousex < 50) && (mousey > 0) && (mousey < 50))
			{
				gameState = MainMenu;
			}
			else if ((mousex > 375) && (mousex < 425) && (mousey > 130) && (mousey < 150) && (ExtraHealth / 2) < 5)
			{
				if (Money > HealthPrice[(ExtraHealth / 2)])
				{
					Money -= HealthPrice[(ExtraHealth / 2)];
					ExtraHealth += 2;
				}
			}
			else if ((mousex > 375) && (mousex < 425) && (mousey > 230) && (mousey < 250) && Lifesteal < 5)
			{
				if (Money > LifestealPrice[Lifesteal])
				{
					Money -= LifestealPrice[Lifesteal];
					Lifesteal += 1;
				}
			}
			else if ((mousex > 375) && (mousex < 425) && (mousey > 330) && (mousey < 350) && MaxJumps - 1 < 5)
			{
				if (Money > MaxjumpPrice[MaxJumps - 1])
				{
					Money -= MaxjumpPrice[MaxJumps - 1];
					MaxJumps += 1;
				}
			}
		}
	}

	void Game::TickWin()
	{
		screen->Clear(0x00CC00);
		std::string Wintext = "YOU WIN!";
		screen->Print(Wintext.c_str(), 384, 256, 0xFFFFFF);

		if (leftmouse)
		{
			SetStart();
			Sleep(50);
		}
	}

	void Game::TickLoss()
	{
		screen->Clear(0x000001);
		std::string Death = "YOU DIED";
		screen->Print(Death.c_str(), 384, 256, 0xFF0000);
		if (leftmouse)
		{
			SetStart();
			Sleep(50);
		}
	}

	void Game::TickGunUpgrade()
	{
		if (!OfferedUpgrade)
		{
			screen->Clear(0xBCBB25);
			Level.OfferUpgrade(screen);
			weapon.DisplayStats(screen);
			OfferedUpgrade = true;
		}
		if (OfferedUpgrade)
		{
			int selection = -1;
			if (leftmouse)
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
					switch (Level.SelectUpgrade(selection))
					{
					case 0:
						guntype = pistol;
						break;

					case 1:
						guntype = sniper;
						break;

					case 2:
						guntype = shotgun;
						break;

					case 3:
						guntype = minigun;
						break;

					case 4:
						guntype = twinguns;
						break;

					case 11:
						if (guntype == sniper)
							guntype = pistolsniper;
						else if (guntype == shotgun)
							guntype = pistolshotgun;
						else if (guntype == minigun)
							guntype = pistolminigun;
						else if (guntype == twinguns)
							guntype = pistoltwin;
						break;

					case 12:
						if (guntype == pistol)
							guntype = pistolsniper;
						else if (guntype == shotgun)
							guntype = snipershotgun;
						else if (guntype == minigun)
							guntype = sniperminigun;
						else if (guntype == twinguns)
							guntype = snipertwin;
						break;

					case 13:
						if (guntype == pistol)
							guntype = pistolshotgun;
						else if (guntype == sniper)
							guntype = snipershotgun;
						else if (guntype == minigun)
							guntype = shotgunminigun;
						else if (guntype == twinguns)
							guntype = shotguntwin;
						break;

					case 14:
						if (guntype == pistol)
							guntype = pistolminigun;
						else if (guntype == sniper)
							guntype = sniperminigun;
						else if (guntype == shotgun)
							guntype = shotgunminigun;
						else if (guntype == twinguns)
							guntype = miniguntwin;
						break;

					case 15:
						if (guntype == pistol)
							guntype = pistoltwin;
						else if (guntype == sniper)
							guntype = snipertwin;
						else if (guntype == shotgun)
							guntype = shotguntwin;
						else if (guntype == minigun)
							guntype = miniguntwin;
						break;

						//gun upgrades
					case 101:
						weapon.upgrade(2, 0, 0, 0, 0, 0);
						break;

					case 102:
						weapon.upgrade(0, 1, 0, 0, 0, 0);
						break;

					case 103:
						weapon.upgrade(0, 0, 30, 0, 0, 0);
						break;

					case 104:
						weapon.upgrade(0, 0, 0, 10, 0, 0);
						break;

					case 105:
						weapon.upgrade(0, 0, 0, 0, 2, 0);
						break;

					case 106:
						weapon.upgrade(0, 0, 0, 0, 0, 2);
						break;

					}
					if (Level.SelectUpgrade(selection) < 100) 
					{
						Firearm weapon{ guntype };
					}
				
					//game back to main run
					gameState = Run;
				}


				Sleep(20);
			}
		}
	}

	void Game::TickElementSelect()
	{
		ElementWheel.Draw(screen, 144, 0);
		if (mousex > 144 && mousex < 207 + 144 && mousey < 207)
		{
			ElementWheel.SetFrame(1);
			if (leftmouse)
				gameState = Run, Element = 0;
		}
		else if (mousex > 304 + 144 && mousex < 512 + 144 && mousey < 207)
		{
			ElementWheel.SetFrame(2);
			if (leftmouse)
				gameState = Run, Element = 1;
		}
		else if (mousex > 304 + 144 && mousex < 512 + 144 && mousey > 304)
		{
			ElementWheel.SetFrame(3);
			if (leftmouse)
				gameState = Run, Element = 2;
		}
		else if (mousex > 144 && mousex < 207 + 144 && mousey > 304)
		{
			ElementWheel.SetFrame(4);
			if (leftmouse)
				gameState = Run, Element = 3;
		}
		else
			ElementWheel.SetFrame(0);

		leftmouse = false;
	}

	void Game::CharacterMovement(float TimeMultiplier)
	{
		//character movement and spritework
		if (left)
		{
			if (!Collision(leftx - MoveSpeed, topy, charx, chary) && !Collision(leftx - MoveSpeed, bottomy, charx, chary)) //prevents walking into walls
			{
				charx -= (MoveSpeed * TimeMultiplier);
			}
			moving += 0.1;
		}

		if (right)
		{
			if (!Collision(rightx + MoveSpeed, topy, charx, chary) && !Collision(rightx + MoveSpeed, bottomy, charx, chary)) //prevents walking into walls
			{
				charx += (MoveSpeed * TimeMultiplier);
			}
			moving += 0.1;
		}

		if (space)
		{
			if (Collision(leftx, bottomy + 1, charx, chary) || Collision(rightx, bottomy + 1, charx, chary) || jumps > 0) //you can only jump if youre on the floor or have more jumps
				gravity = 4.7, jumps -= 1, space = 0;
		}

		if (!space)
		{
			if (Collision(leftx, bottomy + 1, charx, chary) || Collision(rightx, bottomy + 1, charx, chary)) //when grounded, reset jumps and gravity
				if (gravity < 0) gravity = 0, jumps = MaxJumps;
		}

		chary += (gravity * TimeMultiplier);
		gravity -= (0.1 * TimeMultiplier);

		//facing direction independent of moving direction direction so you can shoot whichever direction while moving
		if (mousex < centrex)
		{
			if (left || right)
			{
				MainCharacter.SetFrame(4 + ((int)moving % 2));
			}
			
			if ((!left && !right) || (!Collision(leftx, bottomy + 1, charx, chary) && !Collision(rightx, bottomy + 1, charx, chary)))
			{
				MainCharacter.SetFrame(3);
			}

			if (guntype < 10) { Gun.SetFrame(5 + guntype); }
			if (guntype >= 10) { EvolvedGun.SetFrame(guntype); }
		}

		if (mousex >= centrex)
		{
			if (left || right)
			{
				MainCharacter.SetFrame(1 + ((int)moving % 2));
			}

			if ((!left && !right) || (!Collision(leftx, bottomy + 1, charx, chary) && !Collision(rightx, bottomy + 1, charx, chary)))
			{
				MainCharacter.SetFrame(0);
			}

			if (guntype < 10) { Gun.SetFrame(guntype); }
			if (guntype >= 10) { EvolvedGun.SetFrame(guntype - 10); }
		}

		//if you are in the floor somehow, fixes it
		while (Collision(leftx, bottomy, charx, chary) || Collision(rightx, bottomy, charx, chary))
		{
			chary++;
		}
		while (Collision(leftx, topy, charx, chary) || Collision(rightx, topy, charx, chary))
		{
			chary--;
			gravity = 0;
		}
	}

	void Game::ClearedRoom()
	{
		if (Bossroom()) //win condition
		{
			Sleep(150);
			gameState = Win;
		}
		else
		{

			if (!ChestCreated) //chest can only be created on solid ground
			{
				Level.CreateChest(centrex, centrey, charx, chary);
				ChestCreated = Level.CreateChest(centrex, centrey, charx, chary);
			}

			if (Ekey && !OfferedUpgrade) //you cannot open a chest youve already opened
			{
				if (Level.ChestInteraction(centrex, centrey, charx, chary))
				{
					Money += (20 + (RoomsCleared * 8));
					RoomsCleared += 1;
					gameState = Upgrade;
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


	void Game::Init()
	{
		SetStart();

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

		delete(menu);
	}



	void Game::Tick(float DeltaTime)
	{
		float TimeMultiplier = DeltaTime / GameSpeed;

		switch (gameState)
		{
		case MainMenu: //while in the main menu	
			TickMainMenu();
			break;

		case Shop: //the way to permanently upgrade your character to make your future runs easier
			TickShop();
			break;

		case Win: //win
			TickWin();
			break;

		case Loss: //death
			TickLoss();
			break;

		case Upgrade: //negative gamestates happen during the main run, this one offers upgrades
			TickGunUpgrade();
			break;

		case ElementSelect: //selecting your element. different gamestate to be able to pause your game
			TickElementSelect();
			break;

		case Run: //during the actual game


			CharacterMovement(TimeMultiplier);

			if (Element == 0 && PickElement) //if you have no element active, your move speed is doubled.
			{
				MoveSpeed = 2; //this is because i wanted there to be a reason to not have an element, and also to make it quicker to exit a room and such
			}
			else
			{
				MoveSpeed = 1;
			}

			int closestwallx = centrex; //needed for bullet collision values

			while (!Collision(closestwallx, 255, charx, chary))
			{
				if (mousex < 400) { closestwallx--; }
				if (mousex > 399) { closestwallx++; }
			}

			if (Rkey)
			{
				ManualReload();
			}


			//main gameplay loop: clear and draw map, move and draw character and gun, Enemies and projectile act, check if gun is reloading and firing

			screen->Clear(0x0056CE);
			Level.DrawMap(screen, charx, chary);
			MainCharacter.Draw(screen, spritex, spritey);
			if (guntype < 10) { Gun.Draw(screen, spritex, spritey); }
			if (guntype >= 10) { EvolvedGun.Draw(screen, spritex, spritey); }
			EnemyAction(screen, charx, chary, TimeMultiplier);
			ProjectileAction(screen, charx, chary, TimeMultiplier);
			weapon.reload(screen, TimeMultiplier);
			weapon.Fire(screen, mousex, leftmouse, closestwallx, left, right, charx, chary, TimeMultiplier);
			enemies = EnemyCount(screen);


			if (CheckDeath())
			{
				gameState = Loss;
			}

			if (Qkey && PickElement)
			{
				gameState = ElementSelect;
			}

			if (enemies == 0)
			{
				ClearedRoom();
			}



			break;
		}

		
	}
};
