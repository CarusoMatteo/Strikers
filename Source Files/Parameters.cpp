#include "../Header Files/Parameters.h"

#include <iostream>
using namespace std;

#pragma region Active

float Parameters::spaceshipMaxHealth = 0.0f;
float Parameters::spaceshipSpeed = 0.0f;
float Parameters::spaceshipIvincibilityTime = 0.0f;
int Parameters::spaceshipInvincibleBlinkFrequencyHz = 0;

// Enemy
float Parameters::enemySpeed = 0.0f;
float Parameters::pointMultiplier = 0.0f;
// Projectile
float Parameters::projectileSpeed = 0.0f;
// Explosion
float Parameters::explosionTimeToLiveSeconds = 0.0f;
// - EnemyExplosion
float Parameters::enemyExplosionMaxHorizontalSpeed = 0.0f;
float Parameters::enemyExplosionMaxVerticalSpeed = 0.0f;
// - Projectile Explosion (none)

#pragma endregion Active

#pragma region Easy
const float Parameters::spaceshipMaxHealthEasy = 10.0f;
const float Parameters::spaceshipSpeedEasy = 800.0f;
const float Parameters::spaceshipIvincibilityTimeEasy = 3.0f;
const int Parameters::spaceshipInvincibleBlinkFrequencyHzEasy = 3;

// Enemy
const float Parameters::enemySpeedEasy = 800.0f;
const float Parameters::pointMultiplierEasy = 1.0f;
// Projectile
const float Parameters::projectileSpeedEasy = 2500.0f;
// Explosion
const float Parameters::explosionTimeToLiveSecondsEasy = 0.5f;
// - EnemyExplosion
const float Parameters::enemyExplosionMaxHorizontalSpeedEasy = 1000.0f;
const float Parameters::enemyExplosionMaxVerticalSpeedEasy = 50.0f;
// - Projectile Explosion (none)

#pragma endregion Easy
#pragma region Medium

const float Parameters::spaceshipMaxHealthMedium = 7.0f;
const float Parameters::spaceshipSpeedMedium = 700.0f;
const float Parameters::spaceshipIvincibilityTimeMedium = 2.0f;
const int Parameters::spaceshipInvincibleBlinkFrequencyHzMedium = 3;

// Enemy
const float Parameters::enemySpeedMedium = 1000.0f;
const float Parameters::pointMultiplierMedium = 2.0f;
// Projectile
const float Parameters::projectileSpeedMedium = 2500.0f;
// Explosion
const float Parameters::explosionTimeToLiveSecondsMedium = 0.5f;
// - EnemyExplosion
const float Parameters::enemyExplosionMaxHorizontalSpeedMedium = 1000.0f;
const float Parameters::enemyExplosionMaxVerticalSpeedMedium = 50.0f;
// - Projectile Explosion (none)

#pragma endregion Medium
#pragma region Hard

const float Parameters::spaceshipMaxHealthHard = 5.0f;
const float Parameters::spaceshipSpeedHard = 600.0f;
const float Parameters::spaceshipIvincibilityTimeHard = 1.0f;
const int Parameters::spaceshipInvincibleBlinkFrequencyHzHard = 3;

// Enemy
const float Parameters::enemySpeedHard = 1000.0f;
const float Parameters::pointMultiplierHard = 3.0f;
// Projectile
const float Parameters::projectileSpeedHard = 2500.0f;
// Explosion
const float Parameters::explosionTimeToLiveSecondsHard = 0.5f;
// - EnemyExplosion
const float Parameters::enemyExplosionMaxHorizontalSpeedHard = 1000.0f;
const float Parameters::enemyExplosionMaxVerticalSpeedHard = 50.0f;
// - Projectile Explosion (none)

#pragma endregion Hard

#pragma region Apply Parameters
void Parameters::applyEasy()
{
	cout << "Applying EASY parameters." << endl;
	Parameters::spaceshipMaxHealth = Parameters::spaceshipMaxHealthEasy;
	Parameters::spaceshipSpeed = Parameters::spaceshipSpeedEasy;
	Parameters::spaceshipIvincibilityTime = Parameters::spaceshipIvincibilityTimeEasy;
	Parameters::spaceshipInvincibleBlinkFrequencyHz = Parameters::spaceshipInvincibleBlinkFrequencyHzEasy;
	Parameters::enemySpeed = Parameters::enemySpeedEasy;
	Parameters::pointMultiplier = Parameters::pointMultiplierEasy;
	Parameters::projectileSpeed = Parameters::projectileSpeedEasy;
	Parameters::explosionTimeToLiveSeconds = Parameters::explosionTimeToLiveSecondsEasy;
	Parameters::enemyExplosionMaxHorizontalSpeed = Parameters::enemyExplosionMaxHorizontalSpeedEasy;
	Parameters::enemyExplosionMaxVerticalSpeed = Parameters::enemyExplosionMaxVerticalSpeedEasy;
}

void Parameters::applyMedium()
{
	cout << "Applying MEDIUM parameters." << endl;
	Parameters::spaceshipMaxHealth = Parameters::spaceshipMaxHealthMedium;
	Parameters::spaceshipSpeed = Parameters::spaceshipSpeedMedium;
	Parameters::spaceshipIvincibilityTime = Parameters::spaceshipIvincibilityTimeMedium;
	Parameters::spaceshipInvincibleBlinkFrequencyHz = Parameters::spaceshipInvincibleBlinkFrequencyHzMedium;
	Parameters::enemySpeed = Parameters::enemySpeedMedium;
	Parameters::pointMultiplier = Parameters::pointMultiplierMedium;
	Parameters::projectileSpeed = Parameters::projectileSpeedMedium;
	Parameters::explosionTimeToLiveSeconds = Parameters::explosionTimeToLiveSecondsMedium;
	Parameters::enemyExplosionMaxHorizontalSpeed = Parameters::enemyExplosionMaxHorizontalSpeedMedium;
	Parameters::enemyExplosionMaxVerticalSpeed = Parameters::enemyExplosionMaxVerticalSpeedMedium;
}

void Parameters::applyHard()
{
	cout << "Applying HARD parameters." << endl;
	Parameters::spaceshipMaxHealth = Parameters::spaceshipMaxHealthHard;
	Parameters::spaceshipSpeed = Parameters::spaceshipSpeedHard;
	Parameters::spaceshipIvincibilityTime = Parameters::spaceshipIvincibilityTimeHard;
	Parameters::spaceshipInvincibleBlinkFrequencyHz = Parameters::spaceshipInvincibleBlinkFrequencyHzHard;
	Parameters::enemySpeed = Parameters::enemySpeedHard;
	Parameters::pointMultiplier = Parameters::pointMultiplierHard;
	Parameters::projectileSpeed = Parameters::projectileSpeedHard;
	Parameters::explosionTimeToLiveSeconds = Parameters::explosionTimeToLiveSecondsHard;
	Parameters::enemyExplosionMaxHorizontalSpeed = Parameters::enemyExplosionMaxHorizontalSpeedHard;
	Parameters::enemyExplosionMaxVerticalSpeed = Parameters::enemyExplosionMaxVerticalSpeedHard;
}
#pragma endregion Apply Parameters