//
// Created by Руслан Давлетшин on 24/03/16.
//

#ifndef CPHW_TD_GRAPHICOBJECT_H
#define CPHW_TD_GRAPHICOBJECT_H

#ifndef __SFML__
#define __SFML__
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../constants/Sizes.h"

#include <iostream>
#endif

#include <memory>
#include "../constants/SizeSettings.h"

#ifndef __MATH__
#define __MATH__
#include <cmath>

#define PI 3.14159265f
#endif

using namespace sf;
using namespace std;

class GraphicObject {
public:
    /**
     * Sprite of current object
     */
    Sprite sprite_body;
    explicit GraphicObject(const Texture& texture_body);

    /**
     * Returns vector that contains current position of object
     */
    Vector2f getPosition();
protected:

    /**
     * Returns distance from current object to given one
     */
    float getDistance(Vector2f target);

    /**
     * Returns direction in which object should rotate to reach specified angle
     */
    int getDirection(float cur_alpha, float dif_alpha, float alpha);
};


#endif //CPHW_TD_GRAPHICOBJECT_H
