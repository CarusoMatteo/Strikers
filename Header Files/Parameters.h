#pragma once

/**
 * @brief Static class that holds all adjustable parameters for the game.
 * This includes parameters for the spaceship, enemies, projectiles, and explosions.
 * The parameters can be adjusted based on difficulty levels: Easy, Medium, and Hard by calling the appropriate method when the game starts.
 */
class Parameters
{
public:
	// Currently active parameters that other classes will reference.
#pragma region Active
	// Spaceship
	static float spaceshipMaxHealth;
	static float spaceshipSpeed;
	static float spaceshipIvincibilityTime;
	static int spaceshipInvincibleBlinkFrequencyHz;

	// Enemy
	static float enemySpeed;
	static float pointMultiplier;
	// Projectile
	static float projectileSpeed;
	// Explosion
	static float explosionTimeToLiveSeconds;
	// - EnemyExplosion
	static float enemyExplosionMaxHorizontalSpeed;
	static float enemyExplosionMaxVerticalSpeed;
	// - Projectile Explosion (none)
#pragma endregion Active

	/// @brief Apply Easy difficulty parameters.
	static void applyEasy();
	/// @brief Apply Medium difficulty parameters.
	static void applyMedium();
	/// @brief Apply Hard difficulty parameters.
	static void applyHard();

private:
	Parameters() = default;
	~Parameters() = default;

	// Parameters for each difficulty level, this are constant and edited in Parameters.cpp by the developer.
#pragma region Easy
	// Spaceship
	static const float spaceshipMaxHealthEasy;
	static const float spaceshipSpeedEasy;
	static const float spaceshipIvincibilityTimeEasy;
	static const int spaceshipInvincibleBlinkFrequencyHzEasy;

	// Enemy
	static const float enemySpeedEasy;
	static const float pointMultiplierEasy;
	// Projectile
	static const float projectileSpeedEasy;
	// Explosion
	static const float explosionTimeToLiveSecondsEasy;
	// - EnemyExplosion
	static const float enemyExplosionMaxHorizontalSpeedEasy;
	static const float enemyExplosionMaxVerticalSpeedEasy;
	// - Projectile Explosion (none)
#pragma endregion Easy

#pragma region Medium
	// Spaceship
	static const float spaceshipMaxHealthMedium;
	static const float spaceshipSpeedMedium;
	static const float spaceshipIvincibilityTimeMedium;
	static const int spaceshipInvincibleBlinkFrequencyHzMedium;

	// Enemy
	static const float enemySpeedMedium;
	static const float pointMultiplierMedium;
	// Projectile
	static const float projectileSpeedMedium;
	// Explosion
	static const float explosionTimeToLiveSecondsMedium;
	// - EnemyExplosion
	static const float enemyExplosionMaxHorizontalSpeedMedium;
	static const float enemyExplosionMaxVerticalSpeedMedium;
	// - Projectile Explosion (none)
#pragma endregion Medium

#pragma region Hard
	// Spaceship
	static const float spaceshipMaxHealthHard;
	static const float spaceshipSpeedHard;
	static const float spaceshipIvincibilityTimeHard;
	static const int spaceshipInvincibleBlinkFrequencyHzHard;

	// Enemy
	static const float enemySpeedHard;
	static const float pointMultiplierHard;
	// Projectile
	static const float projectileSpeedHard;
	// Explosion
	static const float explosionTimeToLiveSecondsHard;
	// - EnemyExplosion
	static const float enemyExplosionMaxHorizontalSpeedHard;
	static const float enemyExplosionMaxVerticalSpeedHard;
	// - Projectile Explosion (none)
#pragma endregion Hard
};