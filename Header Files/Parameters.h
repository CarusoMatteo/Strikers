#pragma once

class Parameters
{
public:
	// Spaceship
	static const float spaceshipMaxHealth;
	static const float spaceshipSpeed;
	static const float spaceshipIvincibilityTime;
	static const int spaceshipInvincibleBlinkFrequencyHz;

	// Enemy
	static const float enemySpeed;
	// Projectile
	static const float projectileSpeed;
	// Explosion
	static const float explosionTimeToLiveSeconds;
	// - EnemyExplosion
	static const float enemyExplosionMaxHorizontalSpeed;
	static const float enemyExplosionMaxVerticalSpeed;
	// - Projectile Explosion (none)

private:
	Parameters() = default;
	~Parameters() = default;
};