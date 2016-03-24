//
// Created by Руслан Давлетшин on 24/03/16.
//
#include "../../include/objects/GraphicObject.h"

GraphicObject::GraphicObject(Texture& texture_body) {
    sprite_body.setTexture(texture_body);
}

float GraphicObject::getDistance(Vector2f target) {
    Vector2f pos = sprite_body.getPosition();
    return static_cast<float>(sqrt(pow((target.x - pos.x) / tileW + 0.5, 2) + pow((target.y - pos.y) / tileH + 0.5, 2)));
}

int GraphicObject::getDirection(float cur_alpha, float dif_alpha, float alpha) {
    if (dif_alpha <= 180) {
        return alpha > cur_alpha ? 1 : -1;
    } else {
        return alpha > cur_alpha ? -1 : 1;
    }
}

Vector2f GraphicObject::getPosition() {
    return sprite_body.getPosition();
}