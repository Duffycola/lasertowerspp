//
//  SpriteFactory.m
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//

#include "SpriteFactory.h"



Enemy* SpriteFactory::createEnemy(int level)
{
	Enemy* result = NULL;
	
	if (level == 1) {
		result = createFactoredEnemy(ENEMYID_LASER, 1.0, 1.0);
	} else if (level == 2) {
		result = createFactoredEnemy(ENEMYID_LASER2, 2.5, 1.5);
	} else if (level == 3) {
		result = createFactoredEnemy(ENEMYID_LASER3, 4.0, 2.0);
	}
	return result;
}

Tower* SpriteFactory::createTower(int level)
{
	Tower* result = NULL;
	
	if (level == 1) {
		result = createFactoredTower(TOWERID_LASER, 1.0, 1.0);
	} else if (level == 2) {
		result = createFactoredTower(TOWERID_LASER2, 2.0, 1.5);
	} else if (level == 3) {
		result = createFactoredTower(TOWERID_LASER3, 3.0, 2.0);
	}
	return result;
}

Enemy* SpriteFactory::createBasicEnemy()
{
	Enemy* sprite = new Enemy();
	
	sprite->setID(ENEMYID_LASER);
	sprite->setAttackPower(10);
	sprite->setStamina(100);
	sprite->setStaminaMax(100);
	sprite->setCost(50);
	sprite->setValue(25);
	
	return sprite;
}

Tower* SpriteFactory::createBasicTower()
{
	Tower* sprite = new Tower();
	
	sprite->setID(TOWERID_LASER);
	sprite->setAttackPower(40);
	sprite->setStamina(100);
	sprite->setStaminaMax(100);
	sprite->setCost(50);
	sprite->setValue(25);
	sprite->setRadius(3.0);
	sprite->setSpeed(1.0);
	
	return sprite;
}

Enemy* SpriteFactory::createFactoredEnemy(int id, float f_strength, float f_valor)
{
	Enemy* sprite = createBasicEnemy();
	
	sprite->setID(id);
	sprite->setAttackPower( sprite->getAttackPower() * f_strength);
	sprite->setStamina(     sprite->getStamina()     * f_strength);
	sprite->setStaminaMax(  sprite->getStaminaMax()  * f_strength);
	sprite->setSpeed(       sprite->getSpeed()       * f_strength);
	sprite->setCost(        sprite->getCost()        * f_valor);
	sprite->setValue(       sprite->getValue()       * f_valor);
	
	return sprite;
}

Tower* SpriteFactory::createFactoredTower(int id, float f_strength, float f_valor)
{
	Tower* sprite = createBasicTower();
	
	sprite->setID(id);
	sprite->setAttackPower( sprite->getAttackPower() * f_strength);
	sprite->setStamina(     sprite->getStamina()     * f_strength);
	sprite->setStaminaMax(  sprite->getStaminaMax()  * f_strength);
	sprite->setRadius(      sprite->getRadius()      * f_strength);
	sprite->setSpeed(       sprite->getSpeed()       * f_strength);
	sprite->setCost(        sprite->getCost()        * f_valor);
	sprite->setValue(       sprite->getValue()       * f_valor);
	
	return sprite;
}
