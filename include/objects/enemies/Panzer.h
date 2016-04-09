//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_PANZER_H
#define CPHW_TD_PANZER_H

#include "Enemy.h"

class Panzer : public Enemy {
public:
    Panzer(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths);
    EnemyType getType();
};

#endif //CPHW_TD_PANZER_H
