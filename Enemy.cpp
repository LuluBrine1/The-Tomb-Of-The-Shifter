#include "Enemy.h"
#include "surface.h"
#include "Map.h"
#include "game.h"
#include <random> //used for random seeds
#include <string>


namespace Tmpl8
{
	//main character variables
	int hp = 10;
	int maxhp = 10;
	bool RockBiome = false;
	bool BossRoom = false;
	int Space = 0;

	enum ENEMY
	{
		none = 0,
		skully = 11,
		cactus = 12,
		worm = 21,
		spitter = 22,
		scorpion = 31,
		armadillo = 32,
		bat = 101,
		spider = 102,
		skull = 201,
		raider = 202,
		boulder = 301,
		necromancer = 302,
		undead = 500,
		shifter = 999
	};
	ENEMY Enemies[124] = {none};

	//enemy basic variables
	int EnemyHp[124] = { 0 };
	float EnemyX[124] = { 0 };
	float EnemyY[124] = { 0 };
	int Width[124] = { 0 };
	int Height[124] = { 0 };
	int Xoffset[124] = { 0 };
	int Yoffset[124] = { 0 };

	//projectile basic variables
	int ProjectileType[20] = { 0 };
	float ProjectileX[20] = { 0 };
	float ProjectileY[20] = { 0 };
	int ProjectileWidth[20] = { 0 };
	int ProjectileHeight[20] = { 0 };
	int ProjectileXoffset[20] = { 0 };
	int ProjectileYoffset[20] = { 0 };

	//enemy moving variables
	bool moving[124] = { false };
	bool grounded[124] = { false };
	bool HasSpawned[124] = { false };
	bool Falling[124] = { false };
	bool Climbing[124] = { false };
	bool Burrowing[124] = { false };
	bool Static[124] = { false };
	int ForcedDirection[124] = { 0 };
	int EnemySpeed[124] = { 0 };
	float MoveTimer[124] = { 0 };
	float EnemyGravity[124] = { 0 };

	//projectile moving variables
	int ProjectileSpeed[20] = { 0 };
	float Lifetime[20] = { 0 };
	bool GravitationalProjectile[20] = { false }; //is the projectile affected by gravity
	int Bounces[20] = { 0 }; //if a projectile has -1 bounces it gets destroyed when hitting walls, while 0 lingers on the floor
	bool ProjectileLeft[20] = { false };
	float ProjectileGravity[20] = { 0 };

	//enemy attack variables
	float Attacking[124] = { 0 };
	int EnemyDamage[124] = { 0 };
	float AttackTimer[124] = { 0 };
	int attackchoice[124] = { 0 };
	int ProjectileDamage[20] = { 0 };
	int HitBulletNumber[124] = { -1 };
	float FreezeTimer[124] = { 0 };
	int ElementResistance[124] = { -1 };

	//enemy animation variables
	int FrameCount[124] = { 0 };
	int EnemyFrame[124] = { 0 };
	int EnemyLeftFrame[124] = { 0 };
	int EnemyLeft[124] = { 0 };
	int EnemyAttackFrame[124] = { 0 };
	int EnemyMoveFrame[124] = { 0 };
	int MovementFrames[124] = { 0 };
	int RepeatingStartFrame[124] = { 0 };
	int RepeatingEndFrame[124] = { 0 };
	bool MoveFrame[124] = { true };

	//projectile animation 
	int ProjectileFrame[20] = { 0 };
	int ProjectileFrameCount[20] = { 1 };

	int Spawn = 0;
	int Place = 0;
	int EnemySpawned = 0;
	float Iframes = 0;
	int BossAttackPity = 0;

	//hexcode for damage = #b61f1f

	//Enemy Sprites - Sand
	Sprite BrittleSkull(new Surface("assets/Enemies/BrittleSkull.png"), 4);
	Sprite BrittleCactus(new Surface("assets/Enemies/BrittleCactus.png"), 8);
	Sprite NormalWorm(new Surface("assets/Enemies/NormalWorm.png"), 21);
	Sprite NormalSpitter(new Surface("assets/Enemies/NormalSpitter.png"), 18);
	Sprite TankScorpion(new Surface("assets/Enemies/TankScorpion.png"), 40);
	Sprite TankArmadillo(new Surface("assets/Enemies/TankArmadillo.png"), 26);
	//Enemy Sprites - Rock
	Sprite BrittleBat(new Surface("assets/Enemies/BrittleBat.png"), 4);
	Sprite BrittleSpider(new Surface("assets/Enemies/BrittleSpider.png"), 8);
	Sprite NormalSkull(new Surface("assets/Enemies/NormalSkull.png"), 10);
	Sprite NormalRaider(new Surface("assets/Enemies/NormalRaider.png"), 6);
	Sprite TankBoulder(new Surface("assets/Enemies/TankBoulder.png"), 16);
	Sprite TankNecromancer(new Surface("assets/Enemies/TankNecromancer.png"), 12);
	//Enemy Sprites - Boss
	Sprite Boss(new Surface("assets/Enemies/Boss.png"), 13);
	Sprite Attack1(new Surface("assets/Projectiles/Attack1.png"), 2);
	Sprite Attack2(new Surface("assets/Projectiles/Attack2.png"), 2);
	Sprite Attack3(new Surface("assets/Projectiles/Attack3.png"), 1);

	//Projectile and Miscellaneous Sprites
	Sprite SpitterProjectile(new Surface("assets/Projectiles/SpitterProjectile.png"), 2);
	Sprite SkullProjectile(new Surface("assets/Projectiles/SkullProjectile.png"), 1);
	Sprite RaiderProjectile(new Surface("assets/Projectiles/RaiderProjectile.png"), 1);
	Sprite Undead(new Surface("assets/Enemies/Undead.png"), 6);
	Sprite Frozen(new Surface("assets/Frozen.png"), 1);

	bool BottomCollision(float Offset, int Spawn)
	{
		return (Collision(EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] + Offset, 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + (Width[Spawn] / 2), EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] + Offset, 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] + Offset, 0, 0));
	}

	bool TopCollision(float Offset, int Spawn)
	{
		return (Collision(EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Offset, 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + (Width[Spawn] / 2), EnemyY[Spawn] + Yoffset[Spawn] + Offset, 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Offset, 0, 0));
	}

	bool LeftCollision(float Offset, int Spawn)
	{
		return (Collision(EnemyX[Spawn] + Xoffset[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn], 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn] + (Height[Spawn] / 2), 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0));
	}

	bool RightCollision(float Offset, int Spawn)
	{
		return (Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn], 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn] + (Height[Spawn] / 2), 0, 0)
			|| Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + Offset, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0));
	}


	Enemy::Enemy(int type, bool RockBiome, int RoomsCleared)
	{
		std::random_device rd;
		std::mt19937 opponent(rd());
		std::mt19937 Map(rd());
		std::uniform_int_distribution<> sand(1, 2);
		std::uniform_int_distribution<> rock(1, 2);
		int SetHp = 0;
		int EnemyType = 0;

		Spawn = 0;
		while (Enemies[Spawn] != none && Spawn < 124)
		{
			Spawn += 1;
		}

		//gives each enemy their values
		if (type == 1) //brittle enemies
		{
			if (!RockBiome)
			{
				EnemyType = sand(opponent) + 10;
				SetHp = 6 + (RoomsCleared); //each enemy scales with rooms cleared to add some sort of extra difficulty to each room
				if (EnemyType == 11) 
				{ 
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 17, Height[Spawn] = 21, grounded[Spawn] = false;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 2;
					MovementFrames[Spawn] = 1, EnemyLeftFrame[Spawn] = 2, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 4;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = skully;
				}
				else if (EnemyType == 12)
				{
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 13, Height[Spawn] = 20, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 2;
					MovementFrames[Spawn] = 1, EnemyLeftFrame[Spawn] = 4, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 8;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = cactus;
				}
			}
			else if (RockBiome)
			{
				EnemyType = rock(opponent) + 100;
				SetHp = 20 + (RoomsCleared); //each enemy type (brittle, normal, tank) have the same scaling
				if (EnemyType == 101) //the bat is immune to the ice element
				{
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 15, Height[Spawn] = 16, grounded[Spawn] = false;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 2;
					MovementFrames[Spawn] = 1, EnemyLeftFrame[Spawn] = 2, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 4;
					ElementResistance[Spawn] = 2;
					Enemies[Spawn] = bat;
				}
				else if (EnemyType == 102)
				{
					Xoffset[Spawn] = 6, Yoffset[Spawn] = 10, Width[Spawn] = 19, Height[Spawn] = 21, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 3;
					MovementFrames[Spawn] = 3, EnemyLeftFrame[Spawn] = 4, RepeatingStartFrame[Spawn] = 1, RepeatingEndFrame[Spawn] = 3, FrameCount[Spawn] = 8;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = spider;
				}
			}
		}
		else if (type == 2) //normal enemies
		{
			if (!RockBiome)
			{
				EnemyType = sand(opponent) + 20;
				SetHp = 12 + (RoomsCleared * 2);
				if (EnemyType == 21) 
				{ 
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 63, Height[Spawn] = 20, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 2, EnemySpeed[Spawn] = 3;
					MovementFrames[Spawn] = 9, EnemyLeftFrame[Spawn] = 11, RepeatingStartFrame[Spawn] = 5, RepeatingEndFrame[Spawn] = 8, FrameCount[Spawn] = 21;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = worm;
				}
				else if (EnemyType == 22)
				{
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 13, Height[Spawn] = 10, grounded[Spawn] = false;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 2;
					MovementFrames[Spawn] = 4, EnemyLeftFrame[Spawn] = 9, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 3, FrameCount[Spawn] = 18;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = spitter;
				}
			}
			else if (RockBiome)
			{
				EnemyType = rock(opponent) + 200;
				SetHp = 20 + (RoomsCleared * 2);
				if (EnemyType == 201)
				{
					Xoffset[Spawn] = 7, Yoffset[Spawn] = 0, Width[Spawn] = 25, Height[Spawn] = 29, grounded[Spawn] = false;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 1;
					MovementFrames[Spawn] = 1, EnemyLeftFrame[Spawn] = 5, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 10;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = skull;
				}
				else if (EnemyType == 202)
				{
					Xoffset[Spawn] = 7, Yoffset[Spawn] = 0, Width[Spawn] = 17, Height[Spawn] = 31, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 1;
					MovementFrames[Spawn] = 3, EnemyLeftFrame[Spawn] = 3, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 6;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = raider;
				}
			}
		}
		else if (type == 3) //tank enemies
		{
			if (!RockBiome)
			{
				EnemyType = sand(opponent) + 30;
				SetHp = 20 + (RoomsCleared * 4);
				if (EnemyType == 31) 
				{ 
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 37, Height[Spawn] = 31, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 2, EnemySpeed[Spawn] = 1;
					MovementFrames[Spawn] = 2, EnemyLeftFrame[Spawn] = 20, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 40;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = scorpion;
				}
				else if (EnemyType == 32)
				{ 
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 31, Height[Spawn] = 16, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 3;
					MovementFrames[Spawn] = 2, EnemyLeftFrame[Spawn] = 13, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 26;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = armadillo;
				}
			}
			else if (RockBiome)
			{
				EnemyType = rock(opponent) + 300;
				SetHp = 40 + (RoomsCleared * 4);
				if (EnemyType == 301) //the boulder is immune to the fire element
				{
					Xoffset[Spawn] = 0, Yoffset[Spawn] = 0, Width[Spawn] = 47, Height[Spawn] = 47, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 2;
					MovementFrames[Spawn] = 8, EnemyLeftFrame[Spawn] = 8, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 7, FrameCount[Spawn] = 16;
					ElementResistance[Spawn] = 1;
					Enemies[Spawn] = boulder;
				}
				else if (EnemyType == 302)
				{
					Xoffset[Spawn] = 8, Yoffset[Spawn] = 0, Width[Spawn] = 15, Height[Spawn] = 31, grounded[Spawn] = true;
					EnemyDamage[Spawn] = 1, EnemySpeed[Spawn] = 1;
					MovementFrames[Spawn] = 1, EnemyLeftFrame[Spawn] = 6, RepeatingStartFrame[Spawn] = 0, RepeatingEndFrame[Spawn] = 0, FrameCount[Spawn] = 12;
					ElementResistance[Spawn] = -1;
					Enemies[Spawn] = necromancer;
				}
			}
		}

		EnemyFrame[Spawn] = 0;
		MoveFrame[Spawn] = true;
		EnemyHp[Spawn] = SetHp;


		std::uniform_int_distribution<> MapWidth(512, 1408); 
		std::uniform_int_distribution<> MapHeight(256, 1184); //makes sure the enemies dont spawn where the character is
		
		EnemyX[Spawn] = (float)MapWidth(Map);
		EnemyY[Spawn] = (float)MapHeight(Map); //randomizes the spawn location for the enemy
		while ( TopCollision(0, Spawn) || BottomCollision(0, Spawn) || (grounded[Spawn] && !BottomCollision(1, Spawn)))//repeats until the enemy doesnt spawn in a wall or in the air as a grounded enemy
		{
			EnemyX[Spawn] = (float)MapWidth(Map);
			EnemyY[Spawn] = (float)MapHeight(Map);
		}

		HasSpawned[Spawn] = true;
		


	}

	void CreateEnemy(int type, float x, float y) //when the enemy that isspawning isnt random, aka undead or the boss, who have a set spawn location aswell
	{
		Spawn = 0;
		while (Enemies[Spawn] != none && Spawn < 124)
		{
			Spawn += 1;
		}

		if (Spawn > 123) { type = 0; }

		if (type == 500) 
		{
			Enemies[Spawn] = undead;
			EnemyHp[Spawn] = 1;
			Xoffset[Spawn] = 6;
			Yoffset[Spawn] = 0;
			Width[Spawn] = 13;
			Height[Spawn] = 31;
			grounded[Spawn] = true;
			EnemyDamage[Spawn] = 1;
			EnemySpeed[Spawn] = 2;
			MovementFrames[Spawn] = 3;
			EnemyLeftFrame[Spawn] = 3;
			RepeatingStartFrame[Spawn] = 0;
			RepeatingEndFrame[Spawn] = 0;
			FrameCount[Spawn] = 6;
			ElementResistance[Spawn] = 3;
			HasSpawned[Spawn] = true;

			EnemyX[Spawn] = x;
			EnemyY[Spawn] = y;
		}

		if (type == 999)
		{
			Enemies[Spawn] = shifter;
			EnemyHp[Spawn] = 1000;
			Xoffset[Spawn] = 12;
			Yoffset[Spawn] = 0;
			Width[Spawn] = 29;
			Height[Spawn] = 29;
			grounded[Spawn] = false;
			Static[Spawn] = true;
			EnemyDamage[Spawn] = 0;
			EnemySpeed[Spawn] = 0;
			MovementFrames[Spawn] = 0;
			EnemyLeftFrame[Spawn] = 0;
			RepeatingStartFrame[Spawn] = 0;
			RepeatingEndFrame[Spawn] = 0;
			FrameCount[Spawn] = 13;
			ElementResistance[Spawn] = -1;
			EnemyAttackFrame[Spawn] = 10;
			EnemyFrame[Spawn] = 10;
			HasSpawned[Spawn] = true;

			EnemyX[Spawn] = x;
			EnemyY[Spawn] = y;
		}
	}

	Projectile::Projectile(int type, float EnemyX, float EnemyY, int Damage, int Left, float TimeMultiplier) //creation of projectiles, same as creating enemies, minus randomness
	{
		Place = 0;
		while (ProjectileType[Place] != 0)
		{
			Place += 1;
		}

		if (Place < 20 && type != 0)
		{
			ProjectileX[Place] = EnemyX;
			ProjectileY[Place] = EnemyY;
			if (Left == 0) ProjectileLeft[Place] = false;
			else if (Left != 0) ProjectileLeft[Place] = true;
			ProjectileDamage[Place] = Damage;

			if (type == 22)
			{
				ProjectileType[Place] = 22, ProjectileWidth[Place] = 3, ProjectileHeight[Place] = 3, ProjectileXoffset[Place] = 0, ProjectileYoffset[Place] = 0, ProjectileSpeed[Place] = 2, Lifetime[Place] = 300 / TimeMultiplier, GravitationalProjectile[Place] = true, Bounces[Place] = 3, ProjectileFrame[Place] = 0, ProjectileFrameCount[Place] = 2;
			}
			if (type == 201)
			{
				ProjectileType[Place] = 201, ProjectileWidth[Place] = 7, ProjectileHeight[Place] = 3, ProjectileXoffset[Place] = 0, ProjectileYoffset[Place] = 0, ProjectileSpeed[Place] = 1, Lifetime[Place] = 100 / TimeMultiplier, GravitationalProjectile[Place] = false, Bounces[Place] = -1, ProjectileFrame[Place] = 0, ProjectileFrameCount[Place] = 1;
			}
			if (type == 202)
			{
				ProjectileType[Place] = 202, ProjectileWidth[Place] = 3, ProjectileHeight[Place] = 1, ProjectileXoffset[Place] = 0, ProjectileYoffset[Place] = 0, ProjectileSpeed[Place] = 3, Lifetime[Place] = 40 / TimeMultiplier, GravitationalProjectile[Place] = false, Bounces[Place] = -1, ProjectileFrame[Place] = 0, ProjectileFrameCount[Place] = 1;
			}

			if (type == 901)
			{
				ProjectileType[Place] = 901, ProjectileWidth[Place] = 31, ProjectileHeight[Place] = 31, ProjectileXoffset[Place] = 0, ProjectileYoffset[Place] = 0, ProjectileSpeed[Place] = 0, Lifetime[Place] = 300 / TimeMultiplier, GravitationalProjectile[Place] = true, Bounces[Place] = -1, ProjectileFrame[Place] = 0, ProjectileFrameCount[Place] = 1;
			}
			
			if (type == 902)
			{
				ProjectileType[Place] = 902, ProjectileX[Place] = EnemyX / 32, ProjectileY[Place] = 39 * 32, Lifetime[Place] = 50, GravitationalProjectile[Place] = false, Bounces[Place] = -1, ProjectileWidth[Place] = 31, ProjectileHeight[Place] = 31;
				if (Place + 1 < 20) ProjectileType[Place + 1] = 902, ProjectileX[Place + 1] = EnemyX / 32, ProjectileY[Place + 1] = 38 * 32, Lifetime[Place + 1] = 50 / TimeMultiplier, GravitationalProjectile[Place + 1] = false, Bounces[Place + 1] = -1, ProjectileWidth[Place + 1] = 31, ProjectileHeight[Place + 1] = 31;
				if (Place + 2 < 20) ProjectileType[Place + 2] = 902, ProjectileX[Place + 2] = EnemyX / 32, ProjectileY[Place + 2] = 37 * 32, Lifetime[Place + 2] = 50 / TimeMultiplier, GravitationalProjectile[Place + 2] = false, Bounces[Place + 2] = -1, ProjectileWidth[Place + 2] = 31, ProjectileHeight[Place + 2] = 31;
				if (Place + 3 < 20) ProjectileType[Place + 3] = 902, ProjectileX[Place + 3] = EnemyX / 32, ProjectileY[Place + 3] = 36 * 32, Lifetime[Place + 3] = 50 / TimeMultiplier, GravitationalProjectile[Place + 3] = false, Bounces[Place + 3] = -1, ProjectileWidth[Place + 3] = 31, ProjectileHeight[Place + 3] = 31;
				if (Place + 4 < 20) ProjectileType[Place + 4] = 902, ProjectileX[Place + 4] = (EnemyX / 32) - 1, ProjectileY[Place + 4] = 39 * 32, Lifetime[Place + 4] = 50 / TimeMultiplier, GravitationalProjectile[Place + 4] = false, Bounces[Place + 4] = -1, ProjectileWidth[Place + 4] = 31, ProjectileHeight[Place + 4] = 31;
				if (Place + 5 < 20) ProjectileType[Place + 5] = 902, ProjectileX[Place + 5] = (EnemyX / 32) + 1, ProjectileY[Place + 5] = 39 * 32, Lifetime[Place + 5] = 50 / TimeMultiplier, GravitationalProjectile[Place + 5] = false, Bounces[Place + 5] = -1, ProjectileWidth[Place + 5] = 31, ProjectileHeight[Place + 5] = 31;
				if (Place + 6 < 20) ProjectileType[Place + 6] = 902, ProjectileX[Place + 6] = (EnemyX / 32) - 1, ProjectileY[Place + 6] = 38 * 32, Lifetime[Place + 6] = 50 / TimeMultiplier, GravitationalProjectile[Place + 6] = false, Bounces[Place + 6] = -1, ProjectileWidth[Place + 6] = 31, ProjectileHeight[Place + 6] = 31;
				if (Place + 7 < 20) ProjectileType[Place + 7] = 902, ProjectileX[Place + 7] = (EnemyX / 32) + 1, ProjectileY[Place + 7] = 38 * 32, Lifetime[Place + 7] = 50 / TimeMultiplier, GravitationalProjectile[Place + 7] = false, Bounces[Place + 7] = -1, ProjectileWidth[Place + 7] = 31, ProjectileHeight[Place + 7] = 31;

				for (int i = 0; i < 7; i++)
				{
					if (Place + i < 20)
					{
						ProjectileFrame[Place + i] = 1;
						ProjectileFrameCount[Place + i] = 1;
						ProjectileX[Place + i] = ProjectileX[Place + i] * 32;
					}
				}
			}

			if (type == 903)
			{
				ProjectileType[Place] = 903, ProjectileWidth[Place] = 575, ProjectileHeight[Place] = 31, ProjectileXoffset[Place] = 0, ProjectileYoffset[Place] = 0, ProjectileSpeed[Place] = 0, Lifetime[Place] = 300, GravitationalProjectile[Place] = false, Bounces[Place] = -1, ProjectileFrame[Place] = 0, ProjectileFrameCount[Place] = 1;
			}


		}
	}

	void Enemy::Draw(Surface* screen, float charx, float chary, int Spawn)
	{
		//draws the enemies if they are alive, falling is false so that enemies that are falling disappear off the screen
		if (HasSpawned[Spawn] && EnemyHp[Spawn] > 0 && (EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] + chary < 512 || !Falling[Spawn]))
		{
			if (Enemies[Spawn] > 500) //boss has set frames
				EnemyFrame[Spawn] = EnemyAttackFrame[Spawn];
			else if (RepeatingEndFrame[Spawn] > 0 && EnemyFrame[Spawn] - EnemyLeft[Spawn] <= RepeatingEndFrame[Spawn] && EnemyFrame[Spawn] - EnemyLeft[Spawn] >= RepeatingStartFrame[Spawn] && moving[Spawn]) //roll through movement sprites if there is a repetitive movement
				EnemyFrame[Spawn] = EnemyLeft[Spawn] + (EnemyMoveFrame[Spawn] % (RepeatingEndFrame[Spawn] - RepeatingStartFrame[Spawn])) + RepeatingStartFrame[Spawn] + EnemyAttackFrame[Spawn];
			else if (!MoveFrame[Spawn] && ForcedDirection[Spawn] == 0) //if they cant move, such as scorpion or cactus attacks
				EnemyFrame[Spawn] = EnemyLeft[Spawn] + EnemyAttackFrame[Spawn];
			else if (!MoveFrame[Spawn] && ForcedDirection[Spawn] != 0) //if theyre stuck to a directon
				EnemyFrame[Spawn] = EnemyAttackFrame[Spawn];
			else //when they dont have repeating move frames
				EnemyFrame[Spawn] = EnemyLeft[Spawn] + (EnemyMoveFrame[Spawn] % MovementFrames[Spawn]) + EnemyAttackFrame[Spawn];

			//asserting frame values
			if (EnemyFrame[Spawn] < 0) { EnemyFrame[Spawn] = 0; }
			if (EnemyFrame[Spawn] >= FrameCount[Spawn]) { EnemyFrame[Spawn] = FrameCount[Spawn] - 1; }

			//drawing based off enemy type
			switch (Enemies[Spawn])
			{
			case skully:
				BrittleSkull.SetFrame(EnemyFrame[Spawn]), BrittleSkull.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case cactus:
				BrittleCactus.SetFrame(EnemyFrame[Spawn]), BrittleCactus.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case worm:
				NormalWorm.SetFrame(EnemyFrame[Spawn]), NormalWorm.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case spitter:
				NormalSpitter.SetFrame(EnemyFrame[Spawn]), NormalSpitter.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case scorpion:
				TankScorpion.SetFrame(EnemyFrame[Spawn]), TankScorpion.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case armadillo:
				TankArmadillo.SetFrame(EnemyFrame[Spawn]), TankArmadillo.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case bat:
				BrittleBat.SetFrame(EnemyFrame[Spawn]), BrittleBat.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case spider:
				BrittleSpider.SetFrame(EnemyFrame[Spawn]), BrittleSpider.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case skull:
				NormalSkull.SetFrame(EnemyFrame[Spawn]), NormalSkull.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case raider:
				NormalRaider.SetFrame(EnemyFrame[Spawn]), NormalRaider.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case boulder:
				TankBoulder.SetFrame(EnemyFrame[Spawn]), TankBoulder.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case necromancer:
				TankNecromancer.SetFrame(EnemyFrame[Spawn]), TankNecromancer.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case undead:
				Undead.SetFrame(EnemyFrame[Spawn]), Undead.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;

			case shifter:
				Boss.SetFrame(EnemyFrame[Spawn]), Boss.Draw(screen, static_cast<int>(EnemyX[Spawn] - charx), static_cast<int>(EnemyY[Spawn] + chary));
				break;
			};

			//if enemy is frozen
			if (FreezeTimer[Spawn] > 0)
			{
				Frozen.Draw(screen, static_cast<int>(EnemyX[Spawn] + Xoffset[Spawn] + (Width[Spawn]/2) - 6 - charx), static_cast<int>(EnemyY[Spawn] + Yoffset[Spawn] + (Height[Spawn]/2) - 6 + chary));
			}
		}

		
	}

	void Projectile::Draw(Surface* screen, float charx, float chary, int Number)
	{
		ProjectileFrame[Number] += 1;
		ProjectileFrame[Number] = ProjectileFrame[Number] % ProjectileFrameCount[Number];
		//almost done
		if (ProjectileType[Number] == 22) { SpitterProjectile.SetFrame(ProjectileFrame[Number]), SpitterProjectile.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary)); }
		if (ProjectileType[Number] == 201) { SkullProjectile.SetFrame(ProjectileFrame[Number]), SkullProjectile.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary)); }
		if (ProjectileType[Number] == 202) { RaiderProjectile.SetFrame(ProjectileFrame[Number]), RaiderProjectile.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary)); }
		
		if (ProjectileType[Number] == 901) 
		{ 
			Attack1.SetFrame(0), Attack1.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary));

			float TempY = 39;
			while (Collision(ProjectileX[Number], TempY * 32, 0, 0)) { TempY -= 1; }

			Attack1.SetFrame(1), Attack1.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(TempY*32 + chary)); //creates a warning block at the landing position
		}
		if (ProjectileType[Number] == 902) 
		{
			if (Lifetime[Number] > 10) Attack2.SetFrame(1), Attack2.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary));
			else Attack2.SetFrame(0), Attack2.Draw(screen, static_cast<int>(ProjectileX[Number] - charx), static_cast<int>(ProjectileY[Number] + chary)); //turns warning block into actual block
		}
		if (ProjectileType[Number] == 903) { Attack3.SetFrame(0), Attack3.Draw(screen, static_cast<int>(21 * 32 - charx), static_cast<int>(39 * 32 + chary)); }

	}

	Enemy Monster(0, false, 0);
	Projectile Object(0, 0, 0, 0, false, 0);

	void EnemyGeneration(int RoomsCleared)
	{
		hp = 10 + ExtraStartingHealth() + 2 * RoomsCleared;
		maxhp = hp;

		RockBiome = Rockbiome();
		BossRoom = Bossroom();

		if (RoomsCleared == 0) //for game reset
			BossRoom = false, RockBiome = false;

		
		for (int i = 0; i < 124; i++) //resets all values
		{
			Enemies[i] = { none };
			EnemyHp[i] = { 0 };
			EnemyX[i] = { 0 };
			EnemyY[i] = { 0 };
			Width[i] = { 0 };
			Height[i] = { 0 };
			Xoffset[i] = { 0 };
			Yoffset[i] = { 0 };
			EnemyFrame[i] = { 0 };
			EnemyLeftFrame[i] = { 0 };
			EnemyLeft[i] = { 0 };
			EnemyAttackFrame[i] = { 0 };
			EnemyMoveFrame[i] = { 0 };
			MovementFrames[i] = { 0 };
			RepeatingStartFrame[i] = { 0 };
			RepeatingEndFrame[i] = { 0 };
			Static[i] = { false };
			grounded[i] = { false };
			ForcedDirection[i] = { 0 };
			Attacking[i] = { 0 };
			ElementResistance[i] = { -1 };
			HasSpawned[i] = false;
		}
		Spawn = 0;


		if (!BossRoom)
		{

			int Brittle = 0, Normal = 0, Tank = 0, TotalEnemies = 0;

			Space = 20 + (8 * RoomsCleared); //space is independent to enemies, as some enemies weigh differently, due to their hp numbers
			//brittle enemies count as 1, normal enemies count as 2, tank enemies count as 4.

			std::random_device rd;
			std::mt19937 type(rd());
			std::uniform_int_distribution<> wave(1, 5);

			int WaveType = wave(type);

			int RegularWave[14][3] = { { 4, 4, 2 }, { 10, 5, 2 }, { 8, 6, 4 }, { 14, 7, 4 }, { 12, 8, 6 }, { 18, 9, 6 }, { 16, 10, 8 }, { 22, 11, 8 }, { 20, 12, 10 }, { 26, 13, 10 }, { 24, 14, 12 }, { 30, 15, 12 }, { 28, 16, 14 }, { 34, 17, 14 } };
			int HordeWave[14][3] = { { 14, 1, 1 }, { 20, 2, 1 }, { 22, 3, 2 }, { 28, 4, 2 }, { 30, 5, 3 }, { 36, 6, 3 }, { 38, 7, 4 }, { 44, 8, 4 }, { 46, 9, 5 }, { 52, 10, 5 }, { 58, 11, 6 }, { 60, 12, 6 }, { 62, 13, 7 }, { 68, 14, 7 } };
			int NormalWave[14][3] = { { 2, 7, 1 }, { 4, 10, 1 }, { 6, 13, 1 }, { 4, 16, 2 }, { 6, 19, 2 }, { 8, 22, 2 }, { 6, 25, 3 }, { 8, 28, 3 }, { 10, 31, 3 }, { 8, 34, 4}, { 10, 37, 4 }, { 12, 40, 4 }, { 10, 43, 5 }, { 12, 46, 5 } };
			int EliteWave[14][3] = { { 2, 1, 4 }, { 4, 2, 5 }, { 6, 3, 6 }, { 8, 4, 7 }, { 10, 5, 8 }, { 12, 6, 9 }, { 14, 7, 10 }, { 16, 8, 11 }, { 18, 9, 12 }, { 20, 10, 13}, { 22, 11, 14 }, { 24, 12, 15 }, { 26, 13, 16 }, { 28, 14, 17 } };


			if (WaveType == 1) //regular generation
			{
				Brittle = RegularWave[RoomsCleared][0];
				Normal = RegularWave[RoomsCleared][1];
				Tank = RegularWave[RoomsCleared][2];
			}
			else if (WaveType == 2) //horde generation
			{
				Brittle = HordeWave[RoomsCleared][0];
				Normal = HordeWave[RoomsCleared][1];
				Tank = HordeWave[RoomsCleared][2];
			}
			else if (WaveType == 3) //normal generation
			{
				Brittle = NormalWave[RoomsCleared][0];
				Normal = NormalWave[RoomsCleared][1];
				Tank = NormalWave[RoomsCleared][2];
			}
			else if (WaveType == 4) //elite generation
			{
				Brittle = EliteWave[RoomsCleared][0];
				Normal = EliteWave[RoomsCleared][1];
				Tank = EliteWave[RoomsCleared][2];
			}
			if (WaveType == 5) //random generation
			{
				std::mt19937 creation(rd());
				std::uniform_int_distribution<> tank(0, Space / 4);
				Tank = tank(creation);
				std::uniform_int_distribution<> normal(0, (Space-(Tank*4))/2 );
				Normal = normal(creation);
				//Brittle enemies are filled up later
			}

			TotalEnemies = Brittle + Normal + Tank;

			while (Brittle + Normal * 2 + Tank * 4 < Space) //just incase my math is wrong
			{
				Brittle += 1;
				TotalEnemies += 1;
			}

			for (int i = 0; i < Tank; i++)
			{
				Enemy Monster(3, RockBiome, RoomsCleared);
			}
			for (int i = 0; i < Normal; i++)
			{
				Enemy Monster(2, RockBiome, RoomsCleared);
			}
			for (int i = 0; i < Brittle; i++)
			{
				Enemy Monster(1, RockBiome, RoomsCleared);
			}
			printf("loaded all\n");
		}
		if (BossRoom)
		{
			CreateEnemy(999, 29 * 32 + 5, 39 * 32 + 2);
		}
		

	}

	void EnemyAction(Surface* screen, float charx, float chary, float TimeMultiplier)
	{

		for (int i = 0; i < 124; i++) //loops through every enemy value
		{
			if (EnemyHp[i] > 0) //skips dead enemies and empty slots
			{
				if (AttackTimer[i] <= 0)
				{
					if (Enemies[i] == 999)
					{
						BossAttack(charx, chary, i, TimeMultiplier);
					}
					else
					{
						EnemyAttack(charx, chary, i, TimeMultiplier);
					}
				}
				else
					AttackTimer[i] -= 1 * TimeMultiplier;


				UpdateHitbox(i);

				printf("Preparing Movement -% d\n", Enemies[i]);
				EnemyMovement(charx, chary, i, TimeMultiplier);
				printf("Movement Done -% d\n", Enemies[i]);

				if (MoveTimer[i] > 0) //if moving regularly, enemies can only move every 4th frame. this means that i can have slower enemies than 1 pixel/frame
					MoveTimer[i] -= 1 * TimeMultiplier; //if direction is forced, move every frame because forced direction is part of an attack for fast enemies

				Monster.Draw(screen, charx, chary, i);

				if (Iframes <= 0)
				{
					CheckDamage(screen, charx, chary, i, TimeMultiplier);
				}

				if (EnemyHp[i] <= 600 && Enemies[i] == 999) //boss changes immunity very often
				{
					screen->Bar(100, 5, 700, 15, 0x550000);
					screen->Bar(100, 5, 100 + EnemyHp[i], 15, 0xFF0000);

					std::string ElementalImmunity = "Current Immunity: ";

					if (ElementResistance[i] == 1) {  ElementalImmunity += "Fire"; };
					if (ElementResistance[i] == 2) {  ElementalImmunity += "Ice"; };
					if (ElementResistance[i] == 3) {  ElementalImmunity += "Electric";  };

					screen->Print(ElementalImmunity.c_str(), 340, 20, 0x888888);
				}
				
				//EnemyHp[i] = 0;
			}
		}

		printf("enemies looped through\n");

		Iframes -= 1 * TimeMultiplier;


		screen->Bar(50, 460, 50 + (hp * 10), 480, 14483456);
		std::string HPdisplay = "Health:" + std::to_string(hp) + "/" + std::to_string(maxhp);
		screen->Print(HPdisplay.c_str(), 50, 485, 0xdd0000);

	}

	void ProjectileAction(Surface* screen, float charx, float chary, float TimeMultiplier)
	{
		for (int i = 0; i < 20; i++)
		{

			if (Lifetime[i] <= 0) //projectiles that are 'dead' are removed
			{
				ProjectileType[i] = { 0 };
				ProjectileX[i] = { 0 };
				ProjectileY[i] = { 0 };
				ProjectileWidth[i] = { 0 };
				ProjectileHeight[i] = { 0 };
				ProjectileXoffset[i] = { 0 };
				ProjectileYoffset[i] = { 0 };
				ProjectileSpeed[i] = { 0 };
				Lifetime[i] = { 0 };
				GravitationalProjectile[i] = { false };
				Bounces[i] = { 0 };
				ProjectileGravity[i] = { 0 };
				ProjectileLeft[i] = { false };
				ProjectileDamage[i] = { 0 };
				ProjectileFrame[i] = { 0 };
				ProjectileFrameCount[i] = { 1 };
			}
			else
			{
				ProjectileMovement(i, TimeMultiplier);
				Object.Draw(screen, charx, chary, i);
				Lifetime[i] -= 1 * TimeMultiplier;
				if (Iframes < 1)
				{
					CheckProjectileDamage(screen, charx, chary, i, TimeMultiplier);
				}
			}
		}
	}

	void CheckDamage(Surface* screen, float charx, float chary, int Spawn, float TimeMultiplier)
	{
		bool hurt = false;
		bool touchingplayer = false;
		float ScreenX = EnemyX[Spawn] + Xoffset[Spawn] - charx;
		float ScreenY = EnemyY[Spawn] + Yoffset[Spawn] + chary;
		
		for (int j = 0; j < Height[Spawn]; j++)
		{
			for (int i = 0; i < Width[Spawn]; i++)
			{
				if (ScreenX + i < 409 && ScreenX + i > 391 && ScreenY + j < 272 && ScreenY + j > 240)
					touchingplayer = true;
				
			}
		}

		if (touchingplayer)
		{
			for (int j = 0; j < 32; j++)
			{
				for (int i = 0; i < 18; i++)
				{
					int colour = screen->GetBuffer()[(391 + i) + (240 + j) * 800];

					if (colour == -4841697 && !hurt)         //damage dealing colour. i dont know why its negative but i found this value by creating
					{                                        //a pure (damage dealing colour) 32x32 enemy, then printing the colour value of (391, 240)
						hp -= EnemyDamage[Spawn];            //which is the top left of my main character, which gave me this value
						Iframes = 50 * TimeMultiplier;
						hurt = true; //makes it so that the same enemy cant deal damage multiple times as i and j increase
							
					}

				}
			}
		}
	}

	void CheckProjectileDamage(Surface* screen, float charx, float chary, int Number, float TimeMultiplier)
	{
		bool hurt = false;
		float ScreenX = ProjectileX[Number] + ProjectileXoffset[Number] - charx;
		float ScreenY = ProjectileY[Number] + ProjectileYoffset[Number] + chary;

		for (int j = 0; j < ProjectileHeight[Number]; j++)
		{
			for (int i = 0; i < ProjectileWidth[Number]; i++)
			{
				//projectiles also have the damage dealing colour but its used more as an indicator because a projectile will deal a constant amount of damage, so projectiles that dont deal damage will just be 0
				if ((ScreenX + i < 409) && (ScreenX + i > 391) && (ScreenY + j < 272) && (ScreenY + j) > 240 && !hurt && ProjectileDamage[Number] > 0)
				{ 
					hp -= ProjectileDamage[Number];
					Iframes = 50 * TimeMultiplier;
					hurt = true;
				}
			}
		}

	}

	bool BeingHit(Surface* screen, float bulletX, float bulletY, float charx, float chary, int damage, int pierce, int Bullet, float TimeMultiplier)
	{
		int Pierce = pierce;

		std::string Resisted = "Element Immune!";
		
		int Element = CheckElement();

		for (int e = 0; e < 124; e++) //using e for enemy because i and j are used later for width and height
		{
			if (Bullet == -1) //resets the most recent bullet that hits. this is so when the pierce is greater than 1, an enemy doesnt get hit multiple times by the same bullet
			{
				HitBulletNumber[e] = -1;
			}
			else
			{
				for (int j = 0; j < Height[e]; j++)
				{
					for (int i = 0; i < Width[e]; i++)
					{
						if (static_cast<int>(EnemyX[e] + Xoffset[e] + i - charx) == static_cast<int>(bulletX) && static_cast<int>(EnemyY[e] + Yoffset[e] + j + chary) == static_cast<int>(bulletY))
						{
							if (HitBulletNumber[e] != Bullet) //if the bullet hasnt already hit
							{
								if (ElementResistance[e] == Element) //enemies in the rock room have elemental resistances
								{
									screen->Print(Resisted.c_str(), static_cast<int>(EnemyX[e] + Xoffset[e] + (Width[e] / 2) - 30 - charx), static_cast<int>(EnemyY[e] + Yoffset[e] + (Height[e] / 2) + chary), 0xFFFFFF);
									if (Element == 3) //enemies that are immune to electric will stop the bullet completely
									{
										Pierce = 0;
									}
								}
								else
								{
									EnemyHp[e] -= damage;
									if (EnemyHp[e] < 1 && Enemies[e] < 500)
									{
										hp += LifeStealAmount(); //gain health on kill
										if (hp > maxhp)
											hp = maxhp;
									}
									if (Element == 2) 
									{ 
										Static[e] = true;
										FreezeTimer[e] = 30 * TimeMultiplier;
										if (EnemySpeed[Spawn] > 1)
											EnemySpeed[Spawn] -= 1;
									}


									if (Enemies[e] > 500) //every time you do damage to the boss, he changes element immunity
									{
										std::random_device rd;
										std::mt19937 Immunity(rd());
										std::uniform_int_distribution<> Random(1, 3);
										
										ElementResistance[e] = Random(Immunity);
										if (ElementResistance[e] == 0) ElementResistance[e] = -1;
									}


								}

								HitBulletNumber[e] = Bullet; //makes it so a 1< pierce enemy doesnt get hit multiple times.
								Pierce -= 1;
								e += 1;
							}
							if (Pierce < 1)
							{
								return true; //immediatly deletes the bullet
								break;
							}
							else
								return false;
						}

					}
				}
			}

		}
		return false;
	}

	bool CheckDeath()
	{
		return hp < 1;
	}

	int EnemyCount(Surface* screen)
	{
		EnemySpawned = 0;

		for (int i = 0; i < 124; i++)
		{
			if (HasSpawned[i])
			{
				if (EnemyHp[i] < 1)
				{
					EnemyX[i] = 0;
					EnemyY[i] = 0;
				}
				else
					EnemySpawned += 1;
			}

		}
		//prints enemy count, colour changes based off biome so its more readable
		std::string EnemiesRemaining = "Enemies Remaining:" + std::to_string(EnemySpawned);
		if (!Rockbiome())
			screen->Print(EnemiesRemaining.c_str(), 50, 20, 0x888888);
		else
			screen->Print(EnemiesRemaining.c_str(), 50, 20, 0xccc324);

		if (EnemySpawned == 0)
		{
			std::string ExitTheRoom = "Claim your treasure and Exit the room!";
			if (!Rockbiome())
				screen->Print(ExitTheRoom.c_str(), 50, 40, 0x888888);
			else
				screen->Print(ExitTheRoom.c_str(), 50, 40, 0xccc324);
		}

		return EnemySpawned; 
	}

	void EnemyMovement(float charx, float chary, int Spawn, float TimeMultiplier)
	{
		if (Enemies[Spawn] > 0)
		{
			float Xlocation = EnemyX[Spawn] + (Xoffset[Spawn] + Width[Spawn]) / 2 - charx;
			float Ylocation = EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] + chary;
			bool Above = false, Below = false, Left = false, Right = false, OnScreen = false;
			if (Xlocation >= 0 && Xlocation < 800 && Ylocation >= 0 && Ylocation < 512)
			{
				OnScreen = true;
				if (Xlocation < 384)
					Left = true;
				else if (Xlocation > 415)
					Right = true;

				if (Ylocation < 260)
					Above = true;
				else if (Ylocation > 264)
					Below = true;
			}

			if (OnScreen && !Static[Spawn] && ForcedDirection[Spawn] == 0 && MoveTimer[Spawn] <= 0) //if the enemy is free to move
			{
				if (Below && grounded[Spawn] && !Falling[Spawn])
				{
					//grounded enemies can climb up one tile if the tile infront is a block and above and above infront is air
					if (Left)
					{
						if (Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0) && !Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] - 32, 0, 0) && !Collision(EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] - 32, 0, 0))
						{
							Climbing[Spawn] = true;
						}
						else
							Climbing[Spawn] = false;
					}
					if (Right)
					{
						if (Collision(EnemyX[Spawn] + Xoffset[Spawn] - 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0 ) && !Collision(EnemyX[Spawn] + Xoffset[Spawn] - 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] - 32, 0, 0) && !Collision(EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn] - 32, 0, 0))
						{
							Climbing[Spawn] = true;
						}
						else
							Climbing[Spawn] = false;
					}

					if (Climbing[Spawn])
						EnemyY[Spawn] -= (EnemySpeed[Spawn] * TimeMultiplier);
				}

				if (Above && grounded[Spawn])
				{
					Climbing[Spawn] = false;
				}

				//regular movement
				if (Left)
				{
					if (!RightCollision(static_cast<float>(EnemySpeed[Spawn]), Spawn))
					{
						EnemyX[Spawn] += EnemySpeed[Spawn] * TimeMultiplier;
						EnemyMoveFrame[Spawn] += 1;
						EnemyLeft[Spawn] = EnemyLeftFrame[Spawn];
						moving[Spawn] = true;
					}
					else if (!RightCollision(1, Spawn))
						EnemyX[Spawn] += 1, moving[Spawn] = true;
					else
						moving[Spawn] = false;
				}
				if (Right)
				{
					if (!LeftCollision(static_cast<float>(-EnemySpeed[Spawn]), Spawn))
					{
						EnemyX[Spawn] -= EnemySpeed[Spawn] * TimeMultiplier;
						EnemyMoveFrame[Spawn] += 1;
						EnemyLeft[Spawn] = 0;
						moving[Spawn] = true;
					}
					else if (!LeftCollision(-1, Spawn))
						EnemyX[Spawn] -= 1, moving[Spawn] = true;
					else
					{
						moving[Spawn] = false;
					}

				}

				//floating enemies float. if they go up/down into a block, prevent them from doing so
				//i had an issue where floating enemies would somehow spawn inside a block and float into infinity (only in the rock biome for some reason)
				//and hence the coordinate fix to the center of the map if they attempt to escape
				if (Above && !grounded[Spawn])
				{
					EnemyY[Spawn] += EnemySpeed[Spawn] * TimeMultiplier;
					while (BottomCollision(0, Spawn))
					{
						EnemyY[Spawn] -= 1 * TimeMultiplier;
						if (EnemyY[Spawn] / 32 < 6)
						{
							EnemyY[Spawn] = 23 * 32;
							EnemyX[Spawn] = 29 * 32;
						}
					}
				}
				if (Below && !grounded[Spawn])
				{
					EnemyY[Spawn] -= EnemySpeed[Spawn] * TimeMultiplier;
					while (TopCollision(0, Spawn))
					{
						EnemyY[Spawn] += 1 * TimeMultiplier;
						if (EnemyY[Spawn] / 32 > 42)
						{
							EnemyY[Spawn] = 23 * 32;
							EnemyX[Spawn] = 29 * 32;
						}
					}
				}




				MoveTimer[Spawn] = 4 * TimeMultiplier;
			}

			if (OnScreen && grounded[Spawn] && Climbing[Spawn])
			{
				if (!LeftCollision(-1, Spawn) && !RightCollision(1, Spawn))
					Climbing[Spawn] = false;
			}
			//gravity
			if (grounded[Spawn] && !Climbing[Spawn])
			{

				if (!BottomCollision(1, Spawn))
				{
					Falling[Spawn] = true;
					EnemyY[Spawn] -= EnemyGravity[Spawn] * TimeMultiplier;
					(EnemyGravity[Spawn]) -= static_cast<float>(0.1 * TimeMultiplier);
					while (BottomCollision(1 - EnemyGravity[Spawn], Spawn))
					{
						(EnemyGravity[Spawn]) += static_cast<float>(0.1 * TimeMultiplier);
					}
				}
				else
				{
					Falling[Spawn] = false;
					EnemyGravity[Spawn] = 0;
				}

			}
			if (Falling[Spawn])
			{
				while (TopCollision(1 - EnemyGravity[Spawn], Spawn))
				{
					(EnemyGravity[Spawn]) -= static_cast<float>(0.1 * TimeMultiplier);
				}
			}


			//some attacks force an enemy into one direction, 1 is to the right (+x) and -1 is to the left (-x). 5 is up and down
			if (OnScreen && ForcedDirection[Spawn] == 1)
			{
				if (!RightCollision(static_cast<float>(EnemySpeed[Spawn]), Spawn))
				{
					EnemyX[Spawn] += EnemySpeed[Spawn] * TimeMultiplier;
				}
				else if (!RightCollision(1, Spawn))
					EnemyX[Spawn] += 1;
			}
			if (OnScreen && ForcedDirection[Spawn] == -1)
			{
				if (!LeftCollision(static_cast<float>(-EnemySpeed[Spawn]), Spawn))
				{
					EnemyX[Spawn] -= EnemySpeed[Spawn] * TimeMultiplier;
				}
				else if (!LeftCollision(-1, Spawn))
					EnemyX[Spawn] -= 1;
			}
			if (OnScreen && ForcedDirection[Spawn] == 5)
			{
				if (Ylocation < 266 && !grounded[Spawn])
				{
					EnemyY[Spawn] += EnemySpeed[Spawn] * TimeMultiplier;
					while (BottomCollision(0, Spawn))
						EnemyY[Spawn] -= 1;
				}
				if (Ylocation > 260 && !grounded[Spawn])
				{
					EnemyY[Spawn] -= EnemySpeed[Spawn] * TimeMultiplier;
					while (TopCollision(0, Spawn))
						EnemyY[Spawn] += 1;
				}
				if (Ylocation > 260 && grounded[Spawn] && Enemies[Spawn] != worm) //used for the spider, because forced directions are every frame, the spider climbs incredibly fast
				{
					EnemyY[Spawn] -= EnemySpeed[Spawn] * TimeMultiplier;
					while (TopCollision(0, Spawn))
						EnemyY[Spawn] += 1;
				}


				if (Enemies[Spawn] == worm) //Worm's burrowing mechanic
				{
					bool Air = false;
					bool Boundary = false;
					float BurrowY = EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn];
					bool InGround = false;

					while (!Air && !Boundary) //finds whether it can burrow through an object, which is only when air is below
					{
						if (!Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] / 2, BurrowY, 0, 0))
						{
							if (CheckBoundary(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] / 2, BurrowY))
								Boundary = true;
							else
								Air = true;
						}
						else
							BurrowY += 1;
					}

					if (Boundary) //escapes
					{
						MoveFrame[Spawn] = true, EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0;
					}
					if (Air)
					{
						Burrowing[Spawn] = true;
						EnemyY[Spawn] += 1 * TimeMultiplier;

					}

					//checks for whether the full body could unburrow
					for (int i = 0; i < 16; i++)
					{
						for (int j = 0; j < 64; j++)
						{
							InGround = Collision(EnemyX[Spawn] + Xoffset[Spawn] + (Width[Spawn] / 2) - 32 + j, EnemyY[Spawn] + i, 0, 0);
							if (InGround)
								break;
						}
						if (InGround)
							break;
					}

					if (!InGround)
						MoveFrame[Spawn] = true, EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0;

				}

				
			}

			if (FreezeTimer[Spawn] > 0) //enemies hit by the ice element are slowed and temporarily frozen
			{
				Static[Spawn] = true;
				FreezeTimer[Spawn] -= 1 * TimeMultiplier;
				if (FreezeTimer[Spawn] <= 0)
				{
					Static[Spawn] = false;
					if (EnemySpeed[Spawn] > 1)
						EnemySpeed[Spawn] = 1;
				}
			}


			if (EnemyY[Spawn] < 0 || EnemyY[Spawn] > 32 * 47 || EnemyX[Spawn] < 0 || EnemyX[Spawn] > 32 * 59) //corrects out of bound enemies
			{
				EnemyY[Spawn] = 23 * 32;
				EnemyX[Spawn] = 29 * 32;
			}


		}
		else
		{
			EnemyY[Spawn] = 0;
			EnemyX[Spawn] = 0;
		}
	
	}

	void ProjectileMovement(int Number, float TimeMultiplier)
	{
		//projectile direction
		if (!ProjectileLeft[Number]) 
		{ 
			ProjectileX[Number] -= ProjectileSpeed[Number] * TimeMultiplier;
			if (Collision(ProjectileX[Number] + ProjectileXoffset[Number] - ProjectileSpeed[Number], ProjectileY[Number] + ProjectileYoffset[Number], 0, 0) 
				|| Collision(ProjectileX[Number] + ProjectileXoffset[Number] - ProjectileSpeed[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number], 0, 0))
			{
				if (Bounces[Number] > 0)
				{
					ProjectileSpeed[Number] = ProjectileSpeed[Number] * -1;
					Bounces[Number] -= 1;
				}
				else Lifetime[Number] = 0;
			}
		}
		if (ProjectileLeft[Number]) 
		{ 
			ProjectileX[Number] += ProjectileSpeed[Number] * TimeMultiplier;
			if (Collision(ProjectileX[Number] + ProjectileXoffset[Number] + ProjectileWidth[Number] + ProjectileSpeed[Number], ProjectileY[Number] + ProjectileYoffset[Number], 0, 0) 
				|| Collision(ProjectileX[Number] + ProjectileXoffset[Number] + ProjectileWidth[Number] + ProjectileSpeed[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number], 0, 0))
			{ 
				if (Bounces[Number] != -1)
				{
					ProjectileSpeed[Number] = ProjectileSpeed[Number] * -1;
					if (Bounces[Number] > 0) Bounces[Number] -= 1;
				}
				else Lifetime[Number] = 0;
			}

		}

		//gravity
		if (GravitationalProjectile[Number])
		{
			ProjectileY[Number] -= ProjectileGravity[Number] * TimeMultiplier;
			ProjectileGravity[Number] -= static_cast<float>(0.05 * TimeMultiplier);

			if (Collision(ProjectileX[Number] + ProjectileXoffset[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number] + 1, 0, 0) 
				|| Collision(ProjectileX[Number] + ProjectileXoffset[Number] + ProjectileWidth[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number] + 1, 0, 0))
			{
				ProjectileGravity[Number] = 0;
				if (Bounces[Number] == -1)
					Lifetime[Number] = 0;
				else if (Bounces[Number] > 0)
				{
					if (ProjectileGravity[Number] > 1) ProjectileGravity[Number] = static_cast<float>(ProjectileGravity[Number] * -0.8);
					else ProjectileGravity[Number] += 1;
					while (Collision(ProjectileX[Number] + ProjectileXoffset[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number], 0, 0) 
						|| Collision(ProjectileX[Number] + ProjectileXoffset[Number] + ProjectileWidth[Number], ProjectileY[Number] + ProjectileYoffset[Number] + ProjectileHeight[Number], 0, 0))
					{
						ProjectileY[Number] -= 1;
					}
					Bounces[Number] -= 1;
				}
			}
		}
		if (ProjectileType[Number] == 902)
		{
			if (Lifetime[Number] <= 10 * TimeMultiplier)
			{
				ProjectileFrame[Number] = 0;
				ProjectileDamage[Number] = (int)(maxhp * 0.2);
				if (Attacking[Spawn] < 80)
				{
					CreateTile(static_cast<int>(ProjectileX[Number]), static_cast<int>(ProjectileY[Number])); //at the end of its lifespan, the projectile creates permanent blocks for you to attack the enemy
				}
			}

		}


	}

	void UpdateHitbox(int Spawn)
	{
		if (Enemies[Spawn] == cactus)
		{
			int Hitbox[8][4] = { {13, 20, 9, 0}, {13, 20, 9, 0}, {19, 19, 4, 0}, {21, 13, 0, 0}, {13, 20, 9, 0}, {13, 20, 9, 0}, {19, 19, 8, 0}, {21, 13, 10, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == worm)
		{
			int Hitbox[21][4] = { {63, 20, 0, 0}, {60, 19, 3, 1}, {62, 19, 1, 1}, {62, 19, 0, 1}, {62, 19, 0, 1}, {44, 19, 0, 1}, {44, 19, 0, 1}, {44, 19, 0, 1}, {44, 19, 0, 1}, {63, 20, 0, 0}, 
								  {7, 13, 28, 18}, {63, 20, 0, 0}, {60, 19, 0, 1}, {62, 19, 0, 1}, {62, 19, 1, 1}, {62, 19, 1, 1}, {44, 19, 19, 1}, {44, 19, 19, 1}, {44, 19, 19, 1}, {44, 19, 19, 1}, 
								  {63, 20, 0, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == spitter)
		{
			int Hitbox[18][4] = { {13, 10, 8, 0}, {10, 10, 8, 0}, {10, 10, 8, 0}, {10, 10, 8, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {13, 10, 8, 0}, {13, 10, 9, 0}, 
				                  {10, 10, 12, 0}, {10, 10, 12, 0}, {10, 10, 12, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {12, 10, 9, 0}, {13, 10, 9, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == scorpion)
		{
			int Hitbox[40][4] = { {37, 31, 13, 0}, {36, 31, 13, 0}, {37, 31, 13, 0}, {36, 30, 13, 1}, {35, 30, 13, 1}, {35, 28, 13, 3}, {37, 27, 10, 4}, {38, 27, 9, 4}, {35, 28, 13, 3}, {36, 30, 13, 1}, 
								  {37, 31, 13, 0}, {37, 31, 13, 0}, {39, 31, 11, 0}, {39, 31, 11, 0}, {37, 31, 13, 0}, {37, 31, 13, 0}, {37, 31, 13, 0}, {39, 31, 11, 0}, {37, 31, 13, 0}, {37, 31, 13, 0}, 
				                  {37, 31, 13, 0}, {36, 31, 14, 0}, {37, 31, 13, 0}, {36, 30, 14, 1}, {35, 30, 15, 1}, {35, 28, 15, 3}, {37, 27, 16, 4}, {38, 27, 16, 4}, {35, 28, 15, 3}, {36, 30, 14, 1}, 
				                  {37, 31, 13, 0}, {37, 31, 13, 0}, {39, 31, 11, 0}, {39, 31, 11, 0}, {37, 31, 13, 0}, {37, 31, 13, 0}, {37, 31, 13, 0}, {39, 31, 11, 0}, {37, 31, 13, 0}, {37, 31, 13, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == armadillo) //-1 Yoffset to make it easier to hit
		{
			int Hitbox[26][4] = { {31, 17, 0, -1}, {31, 17, 0, -1}, {31, 15, 0, 0}, {29, 14, 1, 0}, {27, 14, 2, 0}, {25, 15, 3, 0}, {23, 16, 4, 0}, {22, 17, 5, 0}, {21, 17, 6, 0}, {20, 18, 7, 0},
								  {20, 18, 7, 0}, {20, 18, 7, 0}, {20, 18, 7, 0}, {31, 17, 0, -1}, {31, 17, 0, -1}, {31, 15, 0, 0}, {29, 14, 1, 0}, {27, 14, 2, 0}, {25, 15, 3, 0}, {23, 16, 4, 0}, 
								  {22, 17, 4, 0}, {21, 17, 4, 0}, {20, 18, 4, 0}, {20, 18, 4, 0}, {20, 18, 4, 0}, {20, 18, 4, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == skull)
		{
			int Hitbox[10][4] = { {0, 29, 0, 0}, {0, 30, 0, 0}, {0, 31, 0, 0}, {0, 32, 0, 0}, {0, 33, 0, 0}, {0, 29, 0, 0}, {0, 30, 0, 0}, {0, 31, 0, 0}, {0, 32, 0, 0}, {0, 33, 0, 0} };
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
		}
		if (Enemies[Spawn] == necromancer)
		{
			int Hitbox[12][4] = { {15, 31, 8, 0}, {20, 31, 3, 0}, {20, 31, 3, 0}, {21, 31, 2, 0}, {20, 31, 3, 0}, {20, 31, 3, 0}, {15, 31, 8, 0}, {20, 31, 8, 0}, {20, 31, 8, 0}, {21, 31, 8, 0}, 
								  {20, 31, 8, 0}, {20, 31, 8, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		if (Enemies[Spawn] == undead)
		{
			int Hitbox[6][4] = { {13, 31, 6, 0}, {13, 31, 6, 0}, {13, 31, 6, 0}, {13, 31, 12, 0}, {13, 31, 12, 0}, {13, 31, 12, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}

		if (Enemies[Spawn] == shifter)
		{
			int Hitbox[13][4] = { {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, {53, 127, 0, 0}, 
										 {29, 29, 12, 0}, {29, 29, 12, 0}, {29, 29, 12, 0} };
			Width[Spawn] = Hitbox[EnemyFrame[Spawn]][0];
			Height[Spawn] = Hitbox[EnemyFrame[Spawn]][1];
			Xoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][2];
			Yoffset[Spawn] = Hitbox[EnemyFrame[Spawn]][3];
		}
		
		//if the enemy hitbox change puts them in a wall, it lets them out
		if (BottomCollision(0, Spawn) && !Burrowing[Spawn])
		{
			for (int i = 0; i < Height[Spawn]; i++)
			{
				if (BottomCollision(0, Spawn) && !Burrowing[Spawn])
				{
					EnemyY[Spawn] -= 1;
				}
			}
		}

		while (Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0) && !Burrowing[Spawn])
		{
			EnemyX[Spawn] -= 1;
		}
		while (Collision(EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0) && !Burrowing[Spawn])
		{
			EnemyX[Spawn] += 1;
		}

	}

	void EnemyAttack(float charx, float chary, int Spawn, float TimeMultiplier)
	{
		float Xlocation = EnemyX[Spawn] + (Xoffset[Spawn] + Width[Spawn]) / 2 - charx;
		float Ylocation = EnemyY[Spawn] + (Yoffset[Spawn] + Height[Spawn]) / 2 + chary;
		bool OnScreen = false;
		if (Xlocation >= 0 && Xlocation < 800 && Ylocation >= 0 && Ylocation < 512)
		{ OnScreen = true; }
		//enemy attacks
		if (OnScreen)
		{
			if (Enemies[Spawn] == skully) //the brittle skull will reel back, align Y value, and dash forward
			{
				if (Attacking[Spawn] <= 0 && Xlocation < 500 && Xlocation > 300 && Ylocation < 290 && Ylocation > 230)
				{
					Attacking[Spawn] = 175 * TimeMultiplier;
					MoveFrame[Spawn] = false;
				}
				else if (Attacking[Spawn] > 0)
				{
					if (Attacking[Spawn] > 125 * TimeMultiplier)
					{
						if (EnemyLeft[Spawn] == 0)
						{
							ForcedDirection[Spawn] = 1;
							EnemySpeed[Spawn] = 1; //slows down to make up for the forced direction happening every frame
							EnemyAttackFrame[Spawn] = 1;
						}
						else if (EnemyLeft[Spawn] != 0)
						{
							ForcedDirection[Spawn] = -1;
							EnemySpeed[Spawn] = 1;
							EnemyAttackFrame[Spawn] = 3;
						}
					}
					if (Attacking[Spawn] <= 125 * TimeMultiplier && Attacking[Spawn] > 75 * TimeMultiplier)
					{
						ForcedDirection[Spawn] = 5;
						EnemySpeed[Spawn] = 1;
					}
					if (Attacking[Spawn] <= 75 * TimeMultiplier)
					{
						if (EnemyLeft[Spawn] == 0)
						{
							ForcedDirection[Spawn] = -1;
							EnemySpeed[Spawn] = 2;
						}
						else if (EnemyLeft[Spawn] != 0)
						{
							ForcedDirection[Spawn] = 1;
							EnemySpeed[Spawn] = 2;
						}
					}



					Attacking[Spawn] -= 1 * TimeMultiplier;
					if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 750 * TimeMultiplier, EnemySpeed[Spawn] = 2, MoveFrame[Spawn] = true; }
				}
			}





			if (Enemies[Spawn] == cactus) //the brittle cactus enemy will speed up, prepare, and jump at you
			{
				if (Attacking[Spawn] <= 0 && Xlocation < 600 && Xlocation > 200 && Ylocation < 370 && Ylocation > 200)
				{
					Attacking[Spawn] = 175 * TimeMultiplier;
					EnemySpeed[Spawn] = 3;
					EnemyAttackFrame[Spawn] = 1;
				}
				else if (Attacking[Spawn] > 0)
				{
					
					if (Xlocation < 475 && Xlocation > 325 && Ylocation < 350 && Ylocation > 230 && Attacking[Spawn] > 40 * TimeMultiplier)
					{
						Static[Spawn] = true;
						EnemyAttackFrame[Spawn] = 2;
						Attacking[Spawn] = 40;
					}
					if (Attacking[Spawn] < 21 * TimeMultiplier && Attacking[Spawn] > 3 * TimeMultiplier)
					{
						Static[Spawn] = true;
						EnemyAttackFrame[Spawn] = 2;
						EnemySpeed[Spawn] = 1;
					}
					if (Attacking[Spawn] <= 3 * TimeMultiplier && Attacking[Spawn] >= 2 * TimeMultiplier)
					{
						Static[Spawn] = false;
						MoveFrame[Spawn] = false;
						EnemyGravity[Spawn] = 5;
						EnemyY[Spawn] -= 2;
						if (EnemyLeft[Spawn] == 0)
						{
							ForcedDirection[Spawn] = -1;
							EnemySpeed[Spawn] = 1;
							EnemyAttackFrame[Spawn] = 3;
						}
						else if (EnemyLeft[Spawn] != 0)
						{
							ForcedDirection[Spawn] = 1;
							EnemySpeed[Spawn] = 1;
							EnemyAttackFrame[Spawn] = 7;
						}
						if (!BottomCollision(2, Spawn))
						{
							Falling[Spawn] = true;
							Attacking[Spawn] = 2 * TimeMultiplier;
						}
					}
					if (Attacking[Spawn] <= 1 * TimeMultiplier)
					{
						if (!BottomCollision(2, Spawn))
						{
							Falling[Spawn] = true;
							Attacking[Spawn] = 2 * TimeMultiplier;
						}
						else
							Attacking[Spawn] = 0;
					}
					


					Attacking[Spawn] -= 1 * TimeMultiplier;
					if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 600 * TimeMultiplier, EnemySpeed[Spawn] = 2, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
				}
			}

			if (Enemies[Spawn] == worm) //the normal worm will burrow and, when nearby, attack the enemy
			{
				if (Ylocation < 208 && Attacking[Spawn] <= 0)
				{
					if (Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] / 2, EnemyY[Spawn] + 13 + 18, 0, 0))
						ForcedDirection[Spawn] = 5, MoveFrame[Spawn] = false, EnemyAttackFrame[Spawn] = 10;
				}

				if (ForcedDirection[Spawn] == 0)
				{
					if (Attacking[Spawn] <= 0 && Xlocation < 450 && Xlocation > 350 && Ylocation < 320 && Ylocation > 208)
					{
						MoveFrame[Spawn] = false;
						Attacking[Spawn] = 25 * TimeMultiplier;
					}
					if (Attacking[Spawn] < 25 * TimeMultiplier && Attacking[Spawn] > 10 * TimeMultiplier)
					{
						EnemyAttackFrame[Spawn] = (static_cast<int>(Attacking[Spawn]) - 10) / 3;
					}
					if (Attacking[Spawn] <= 10 * TimeMultiplier && Attacking[Spawn] > 0)
					{
						EnemyAttackFrame[Spawn] = 9;
					}

					Attacking[Spawn] -= 1 * TimeMultiplier;
					if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 600 * TimeMultiplier, EnemySpeed[Spawn] = 2, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
				}
			}

			if (Enemies[Spawn] == spitter) //the normal spitter will spit at you
			{
				if (Attacking[Spawn] <= 0 && Xlocation < 500 && Xlocation > 300 && Ylocation < 320 && Ylocation > 200)
				{
					Attacking[Spawn] = 100 * TimeMultiplier;
				}
				if (Attacking[Spawn] < 15 * TimeMultiplier && Attacking[Spawn] > 0)
				{
					moving[Spawn] = false;
					if (Attacking[Spawn] > 12 * TimeMultiplier)
						EnemyAttackFrame[Spawn] = 4;
					else if (Attacking[Spawn] > 9 * TimeMultiplier)
						EnemyAttackFrame[Spawn] = 5;
					else if (Attacking[Spawn] > 6 * TimeMultiplier)
						EnemyAttackFrame[Spawn] = 6;
					else if (Attacking[Spawn] > 3 * TimeMultiplier)
						EnemyAttackFrame[Spawn] = 7;
					else if (Attacking[Spawn] > 0 * TimeMultiplier)
						EnemyAttackFrame[Spawn] = 8;
					
				}
				if (Attacking[Spawn] <= 1 * TimeMultiplier)
				{
					if (EnemyLeft[Spawn] == 0) Projectile Object(22, EnemyX[Spawn] + 4, EnemyY[Spawn] + 6, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
					if (EnemyLeft[Spawn] != 0) Projectile Object(22, EnemyX[Spawn] + 23, EnemyY[Spawn] + 6, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
				}

				Attacking[Spawn] -= 1 * TimeMultiplier;
				if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 600 * TimeMultiplier, EnemySpeed[Spawn] = 2, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
			}



			if (Enemies[Spawn] == scorpion) //the tank scorpion will either sting you are run and claw at you
			{
				std::random_device rd;
				std::mt19937 attack(rd());
				std::uniform_int_distribution<> pick(1, 2);

				if (Attacking[Spawn] <= 0 && Xlocation < 500 && Xlocation > 300 && Ylocation < 320 && Ylocation > 200)
				{
					attackchoice[Spawn] = pick(attack);
					if (attackchoice[Spawn] == 1)
						Attacking[Spawn] = 200 * TimeMultiplier;
					if (attackchoice[Spawn] == 2)
						Attacking[Spawn] = 300 * TimeMultiplier;
					
				}
				if (Attacking[Spawn] > 0 && attackchoice != 0)
				{
					if (attackchoice[Spawn] == 1)
					{
						if (Attacking[Spawn] > 35 * TimeMultiplier)
						{
							EnemySpeed[Spawn] = 2;
						}
						if (Attacking[Spawn] <= 35 * TimeMultiplier)
						{
							MoveFrame[Spawn] = false;
							EnemySpeed[Spawn] = 1;
							Static[Spawn] = true;
							EnemyAttackFrame[Spawn] = 10-(static_cast<int>(Attacking[Spawn])/4);

							if (Attacking[Spawn] > 31 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 2;
							else if (Attacking[Spawn] > 27 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 3;
							else if (Attacking[Spawn] > 23 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 4;
							else if (Attacking[Spawn] > 19 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 5;
							else if (Attacking[Spawn] > 15 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 6;
							else if (Attacking[Spawn] > 11 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 7;
							else if (Attacking[Spawn] > 7 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 8;
							else if (Attacking[Spawn] > 3 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 9;
							else if (Attacking[Spawn] > 0 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 10;
						}

					}
					if (attackchoice[Spawn] == 2)
					{
						if (Attacking[Spawn] > 150 * TimeMultiplier)
						{
							EnemySpeed[Spawn] = 3;
						}
						if (Attacking[Spawn] <= 150 * TimeMultiplier && Attacking[Spawn] > 90 * TimeMultiplier)
						{
							MoveFrame[Spawn] = false;
							EnemySpeed[Spawn] = 2;

							if (Attacking[Spawn] > 140 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 10;
							else if (Attacking[Spawn] > 130 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 11;
							else if (Attacking[Spawn] > 120 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 12;
							else if (Attacking[Spawn] > 110 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 13;
							else if (Attacking[Spawn] > 100 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 14;
							else if (Attacking[Spawn] > 90 * TimeMultiplier)
								EnemyAttackFrame[Spawn] = 15;

						}
						if (Attacking[Spawn] <= 90 * TimeMultiplier && Attacking[Spawn] > 30 * TimeMultiplier)
						{
							EnemySpeed[Spawn] = 1;
						}
						if (Attacking[Spawn] <= 30 * TimeMultiplier)
						{
							Static[Spawn] = true;
						}
						if (Attacking[Spawn] < 16 * TimeMultiplier)
						{
							Static[Spawn] = true;
							EnemyAttackFrame[Spawn] = 19 - (static_cast<int>(Attacking[Spawn]) / 4);
						}
					}



					Attacking[Spawn] -= 1 * TimeMultiplier;
					if (Attacking[Spawn] <= 0) { MoveFrame[Spawn] = true, EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 400 * TimeMultiplier, EnemySpeed[Spawn] = 1, Static[Spawn] = false; }
				}
			}

			if (Enemies[Spawn] == armadillo) //the tank armadillo will ball up and rush at you
			{
				if (Attacking[Spawn] < 1 && Xlocation < 800 && Xlocation > 0 && Ylocation < 304 && Ylocation > 208)
				{
					Attacking[Spawn] = 224;
				}
				if (Attacking[Spawn] > 199)
				{
					MoveFrame[Spawn] = false;
					Static[Spawn] = true;
					EnemyAttackFrame[Spawn] = 9 - ((static_cast<int>(Attacking[Spawn]) - 200) / 3);
				}
				if ((Attacking[Spawn] < 200 && Attacking[Spawn] > 150 ) || (Attacking[Spawn] < 150 && Attacking[Spawn] > 100) || (Attacking[Spawn] < 100 && Attacking[Spawn] > 50) || (Attacking[Spawn] < 50 && Attacking[Spawn] > 0))
				{
					Static[Spawn] = false;
					if (EnemyLeft[Spawn] == 0)
					{
						ForcedDirection[Spawn] = -1;
						EnemySpeed[Spawn] = 3;
						EnemyAttackFrame[Spawn] = 22 + (static_cast<int>(Attacking[Spawn]) % 4);
					}
					if (EnemyLeft[Spawn] != 0)
					{
						ForcedDirection[Spawn] = 1;
						EnemySpeed[Spawn] = 3;
						EnemyAttackFrame[Spawn] = 9 + (static_cast<int>(Attacking[Spawn]) % 4);
					}
				}
				if (Attacking[Spawn] == 150 || Attacking[Spawn] == 100 || Attacking[Spawn] == 50)
				{
					ForcedDirection[Spawn] = 0;
				}
			

				Attacking[Spawn] -= 1;
				if (Attacking[Spawn] == 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 800 * TimeMultiplier, EnemySpeed[Spawn] = 3, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
			}

			//the brittle bat does not have an attack

			if (Enemies[Spawn] == spider) //the spider doesnt have an attack, but can climb any wall height at 4 times its usual speed
			{
				if (Ylocation > 239)
				{
					if (Collision(EnemyX[Spawn] + Xoffset[Spawn] - 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0) || Collision(EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] + 1, EnemyY[Spawn] + Yoffset[Spawn] + Height[Spawn], 0, 0))
					{
						ForcedDirection[Spawn] = 5;
						Climbing[Spawn] = true;
					}
					else
					{
						ForcedDirection[Spawn] = 0;
						Climbing[Spawn] = false;
					}
				}
				else
				{
					ForcedDirection[Spawn] = 0;
					Climbing[Spawn] = false;
				}
			}

			if (Enemies[Spawn] == skull) //the normal skull will reel back, and shoot a laser at you
			{
				if (Attacking[Spawn] <= 0 && Xlocation < 500 && Xlocation > 300 && Ylocation < 320 && Ylocation > 200)
				{
					Attacking[Spawn] = 300 * TimeMultiplier;
				}
				if (Attacking[Spawn] < 300 * TimeMultiplier && Attacking[Spawn] > 100 * TimeMultiplier)
				{
					if (Xlocation > 350 && Xlocation < 400)
						ForcedDirection[Spawn] = -1;
					else if (Xlocation > 400 && Xlocation < 450)
						ForcedDirection[Spawn] = 1;
					else
						ForcedDirection[Spawn] = 0;
				}
				if (Attacking[Spawn] <= 100 * TimeMultiplier && Attacking[Spawn] > 0)
				{
					ForcedDirection[Spawn] = 5;
					EnemyAttackFrame[Spawn] = 4 - static_cast<int>(Attacking[Spawn]) / 25;
				}
				if (Attacking[Spawn] <= 1 * TimeMultiplier)
				{
					if (EnemyLeft[Spawn] == 0) Projectile Object(201, EnemyX[Spawn] + Xoffset[Spawn], EnemyY[Spawn] + 26, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
					if (EnemyLeft[Spawn] != 0) Projectile Object(201, EnemyX[Spawn] + Xoffset[Spawn] + Width[Spawn] - 3, EnemyY[Spawn] + 26, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
				}

				Attacking[Spawn] -= 1 * TimeMultiplier;
				if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 600 * TimeMultiplier, EnemySpeed[Spawn] = 1, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
			}

			if (Enemies[Spawn] == raider) //the normal raider will always shoot bullets
			{
				if (Attacking[Spawn] <= 0)
				{
					Attacking[Spawn] = 75 * TimeMultiplier;
				}
				if (Attacking[Spawn] <= 1 * TimeMultiplier)
				{
					if (EnemyLeft[Spawn] == 0) Projectile Object(202, EnemyX[Spawn] + 1, EnemyY[Spawn] + 15, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
					if (EnemyLeft[Spawn] != 0) Projectile Object(202, EnemyX[Spawn] + 29, EnemyY[Spawn] + 15, EnemyDamage[Spawn], EnemyLeft[Spawn], TimeMultiplier);
				}

				Attacking[Spawn] -= 1 * TimeMultiplier;
				if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 150 * TimeMultiplier, EnemySpeed[Spawn] = 1, Falling[Spawn] = false, MoveFrame[Spawn] = true; }
			}


			if (Enemies[Spawn] == boulder) //the tank boulder will always roll, but wont change direction until later
			{
				if (Xlocation < 400 && ForcedDirection[Spawn] != -1)
				{
					ForcedDirection[Spawn] = 1;
				}
				if (Xlocation > 400 && ForcedDirection[Spawn] != 1)
				{
					ForcedDirection[Spawn] = -1;
				}

				if (Xlocation < 400 && Xlocation > 300 && ForcedDirection[Spawn] == -1)
				{
					ForcedDirection[Spawn] = -1;
				}
				else if (Xlocation > 400 && Xlocation < 500 && ForcedDirection[Spawn] == 1)
				{
					ForcedDirection[Spawn] = 1;
				}
				else if (Xlocation < 300)
					ForcedDirection[Spawn] = 1;
				else if (Xlocation > 500)
					ForcedDirection[Spawn] = -1;
				
				Attacking[Spawn] += 1;
				Attacking[Spawn] = static_cast<float>(static_cast<int>(Attacking[Spawn]) % 3);

				if (Attacking[Spawn] == 0)
				{
					EnemyAttackFrame[Spawn] += 1;
					if (ForcedDirection[Spawn] == 1) EnemyAttackFrame[Spawn] = EnemyLeftFrame[Spawn] + (EnemyAttackFrame[Spawn] % 8);
					if (ForcedDirection[Spawn] == -1) EnemyAttackFrame[Spawn] = (EnemyAttackFrame[Spawn] % 8);
				}
			}

			if (Enemies[Spawn] == necromancer) //the tank necromancer will summon the undead when onscreen
			{
				
				if (Attacking[Spawn] <= 0)
				{
					Attacking[Spawn] = 75 * TimeMultiplier;
				}
				if (Attacking[Spawn] > 0)
				{
					EnemyAttackFrame[Spawn] = 5 - (static_cast<int>(Attacking[Spawn]) / 15);
				}
				if (Attacking[Spawn] <= 1 * TimeMultiplier)
				{
					if (EnemyLeft[Spawn] == 0) { CreateEnemy(500, EnemyX[Spawn] - 32, EnemyY[Spawn]); } //undead are immune to the electric element
					if (EnemyLeft[Spawn] != 0) { CreateEnemy(500, EnemyX[Spawn] + 32, EnemyY[Spawn]); }
				}

				Attacking[Spawn] -= 1 * TimeMultiplier;
				if (Attacking[Spawn] <= 0) { EnemyAttackFrame[Spawn] = 0, ForcedDirection[Spawn] = 0, AttackTimer[Spawn] = 450 * TimeMultiplier, EnemySpeed[Spawn] = 1, Falling[Spawn] = false, MoveFrame[Spawn] = true; }

			}

		}
	}

	void BossAttack(float charx, float chary, int Spawn, float TimeMultiplier)
	{
		if (EnemyHp[Spawn] < 1000 && EnemyHp[Spawn] > 600) //the sleep sequence, damage you do here does not matter unless you can do over 400 damage before he is out of range
		{
			EnemyAttackFrame[Spawn] = 10;
			if (EnemyY[Spawn] > 960)
			{
				if (EnemyY[Spawn] <= 1230) EnemyAttackFrame[Spawn] = 11;
				EnemyY[Spawn] -= 2;
				if (EnemyY[Spawn] <= 960) EnemyAttackFrame[Spawn] = 0, EnemyHp[Spawn] = 600, Attacking[Spawn] = 150, attackchoice[Spawn] = 0;
			}
		}
		else if (EnemyHp[Spawn] < 601 && EnemyHp[Spawn] > 0)
		{
			std::random_device rd;
			std::mt19937 attack(rd());
			std::mt19937 Placing(rd());
			std::uniform_int_distribution<> pick(1, 3); //boss has 3 attacks
			std::uniform_int_distribution<> Block(0, 576);
			

			if (Attacking[Spawn] <= 0)
			{
				if (BossAttackPity < 5) //the 'spike' attack is needed to damage the boss, so to prevent bad luck, the spikes attack will happen at worst every 5 attacks
					attackchoice[Spawn] = pick(attack);
				else
					attackchoice[Spawn] = 2;



				if (attackchoice[Spawn] == 1) //dropping blocks
					Attacking[Spawn] = 300 * TimeMultiplier, BossAttackPity += 1;
				if (attackchoice[Spawn] == 2) //summon spikes
					Attacking[Spawn] = 300 * TimeMultiplier, BossAttackPity = 0;
				if (attackchoice[Spawn] == 3) //summon undead
					Attacking[Spawn] = 300 * TimeMultiplier, BossAttackPity += 1;

			}
			
			
			
			if (attackchoice[Spawn] == 1 && Attacking[Spawn] <= 300 * TimeMultiplier && Attacking[Spawn] > 0)
			{
				if (Attacking[Spawn] == 300 * TimeMultiplier)
				{
					for (int i = 0; i < 10; i++) //creates 10 falling blocks
					{
						int tempX = Block(Placing);
						Projectile Object(901, static_cast<float>(21 * 32 + tempX), 16 * 32, 5, 0, TimeMultiplier);
					}
				}
				if (Attacking[Spawn] > 200 * TimeMultiplier && Attacking[Spawn] < 250 * TimeMultiplier)
				{
					EnemyAttackFrame[Spawn] = (static_cast<int>(Attacking[Spawn]) - 200) / 5; //fall animation is delayed because the falling blocks cant be seen untill later
				}
			}
			if (attackchoice[Spawn] == 2)
			{
				if (Attacking[Spawn] > 200 * TimeMultiplier && Attacking[Spawn] < 250 * TimeMultiplier)
				{
					EnemyAttackFrame[Spawn] = 9 - (static_cast<int>(Attacking[Spawn] - 200) / 5);
				}
				if (static_cast<int>(Attacking[Spawn]) % 80 == 0 && Attacking[Spawn] > 59 * TimeMultiplier) //creates spikes every 80 frames
				{
					EnemyAttackFrame[Spawn] = 9;
					Projectile Object(902, 12*32 + charx, 39 * 32, 0, 0, TimeMultiplier);
				}
			}
			if (attackchoice[Spawn] == 3)
			{
				if (Attacking[Spawn] == 300 * TimeMultiplier)
				{
					ClearMap();
					Projectile Object(903, 22 * 32, 39 * 32, 0, 0, TimeMultiplier); //creates sand cloud and then summons undead
				}
				if (Attacking[Spawn] <= 1 * TimeMultiplier)
				{
					CreateEnemy(500, 22 * 32, 39 * 32);
					CreateEnemy(500, 24 * 32, 39 * 32);
					CreateEnemy(500, 26 * 32, 39 * 32);
					CreateEnemy(500, 21 * 32 + 403, 39 * 32);
					CreateEnemy(500, 21 * 32 + 467, 39 * 32);
					CreateEnemy(500, 21 * 32 + 530, 39 * 32);
				}
			}

			Attacking[Spawn] -= 1 * TimeMultiplier;
			if (Attacking[Spawn] <= 0)
			{
				AttackTimer[Spawn] = 225 * TimeMultiplier, attackchoice[Spawn] = 0, EnemyAttackFrame[Spawn] = 0;
			}
		}
	}


};
