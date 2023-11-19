/**
 * MIT License
 *
 * Copyright (c) 2023 Matthew James Austin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cmath>
#include "polygonProjectileEntity.h"

namespace {

constexpr float kDegradeRate() { return 0.3f; };

}; //end of namespace

namespace shadow_pumpkin_caster {
namespace entity {

PolygonProjectileEntity::PolygonProjectileEntity(b2World &p_world, b2Vec2 p_position,
                                                 std::vector<b2Vec2> p_shape, float p_angle,
                                                 float p_force, float p_fragility):
    PolygonEntity(p_world, p_position, p_shape, p_angle, p_fragility) {

    setType(EntityType::projectile);
    b2Vec2 force(std::cos(p_angle) * p_force, std::sin(p_angle) * p_force);
    applyImpulse(force);
}

void PolygonProjectileEntity::processEvents() {
    DynamicEntity::processEvents();
    if (getHp() < 100.0f) {
        applyHpChange(-kDegradeRate());
    }
}

void PolygonProjectileEntity::draw(const visual::Camera &p_camera) {
    PolygonEntity::draw(p_camera);
}

bool PolygonProjectileEntity::isDead() {
    return DynamicEntity::isDead();
};

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
