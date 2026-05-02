#pragma once

namespace Tmpl8
{
	class Surface;

	void EnemyGeneration(int Space); 
	void EnemyAction(Surface* screen, int charx, int chary);
	void CheckDamage(Surface* screen, int charx, int chary, int Spawn);
	bool BeingHit(Surface* screen, int bulletX, int bulletY, int charx, int chary, int damage, int pierce, int Bullet);
	int EnemyCount(Surface* screen);
	void EnemyMovement(int charx, int chary, int Spawn);
	void UpdateHitbox(int Spawn);
	void EnemyAttack(int charx, int chary, int Spawn);
	void BossAttack(int charx, int chary, int Spawn);

	void ProjectileAction(Surface* screen, int charx, int chary);
	void ProjectileMovement(int Number);
	void CheckProjectileDamage(Surface* screen, int charx, int chary, int Number);
	void CreateEnemy(int type, int x, int y);

	bool CheckDeath();

	class Enemy
	{
	public:
		Enemy(int type, bool RockBiome, int RoomsCleared);
		void Draw(Surface* screen, int charx, int chary, int Spawn);
	private:

	};

	class Projectile
	{
	public:
		Projectile(int type, int EnemyX, int EnemyY, int Damage, int Left);
		void Draw(Surface* screen, int charx, int chary, int Number);
	};
}