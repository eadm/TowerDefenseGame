//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_PLANE_H
#define CPHW_TD_PLANE_H

#include "Enemy.h"

class Plane : public Enemy {
public:
    Plane(int dx, int dy, TextureManager* texture_manager, unsigned char** distances, DIRECTION** paths);
};

#endif //CPHW_TD_PLANE_H
