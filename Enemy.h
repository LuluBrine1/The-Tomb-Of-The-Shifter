#pragma once

namespace Tmpl8
{
	class Surface;

	void EnemyGeneration(int Space); 
	void EnemyAction(Surface* screen, float charx, float chary, float TimeMultiplier);
	void CheckDamage(Surface* screen, float charx, float chary, int Spawn, float TimeMultiplier);
	bool BeingHit(Surface* screen, float bulletX, float bulletY, float charx, float chary, int damage, int pierce, int Bullet, float TimeMultiplier);
	int EnemyCount(Surface* screen);
	void EnemyMovement(float charx, float chary, int Spawn, float TimeMultiplier);
	void UpdateHitbox(int Spawn);
	void EnemyAttack(float charx, float chary, int Spawn, float TimeMultiplier);
	void BossAttack(float charx, float chary, int Spawn, float TimeMultiplier);


	void ProjectileAction(Surface* screen, float charx, float chary, float TimeMultiplier);
	void ProjectileMovement(int Number, float TimeMultiplier);
	void CheckProjectileDamage(Surface* screen, float charx, float chary, int Number, float TimeMultiplier);
	void CreateEnemy(int type, float x, float y);

	bool CheckDeath();

	class Enemy
	{
	public:
		Enemy(int type, bool RockBiome, int RoomsCleared);
		void Draw(Surface* screen, float charx, float chary, int Spawn);
	private:

	};

	class Projectile
	{
	public:
		Projectile(int type, float EnemyX, float EnemyY, int Damage, int Left, float TimeMultiplier);
		void Draw(Surface* screen, float charx, float chary, int Number);
	};
}