//
//  SpriteFactory.h
//  LaserTowers
//
//  Created by Eduard Feicho <eduard.feicho@rwth-aachen.de> on 23.03.12.
//  Copyright 2012 Eduard Feicho. All rights reserved.
//

#ifndef __SPRITEFACTORY_H
#define __SPRITEFACTORY_H

#include "SpriteFactoryAbstract.h"

#include "Enemy.h"
#include "Tower.h"

/**
 * class SpriteFactory creates and configures sprite objects.
 * 
 * <Factory>
 */
class SpriteFactory : public SpriteFactoryAbstract {
public:
	SpriteFactory() {};
	
	virtual ~SpriteFactory() {};
	virtual Enemy* createEnemy(int level);
	virtual Tower* createTower(int level);
	
private:
	
	Enemy* createBasicEnemy();
	Enemy* createFactoredEnemy(int id, float f_strength, float f_valor);
	
	Tower* createBasicTower();
	Tower* createFactoredTower(int id, float f_strength, float f_valor);
};


#endif
