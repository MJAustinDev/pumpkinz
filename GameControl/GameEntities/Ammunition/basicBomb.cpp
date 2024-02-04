/**
 * MIT License
 *
 * Copyright (c) 2023-2024 Matthew James Austin
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

#include "basicBomb.h"

namespace {

constexpr float kFragility() { return 0.01f; }
constexpr float kRadius() { return 1.0f; }
constexpr float kGasRadius() { return 0.2f; }
constexpr float kAnglePerParticle() {return 0.1f; }
constexpr float kExplosiveForce() { return 50.0f; }
constexpr float kDissipateRate() { return 9.0f; }

} // end of namespace

namespace shadow_pumpkin_caster {
namespace entity {
namespace ammo {

BasicBomb::BasicBomb(b2World &p_world, b2Vec2 p_position, float p_angle, float p_force,
                     std::list<std::shared_ptr<ExplosionParticle>> &p_particleList):
    CircleProjectileEntity(p_world, p_position, kRadius(), p_angle, p_force, kFragility()),
    m_explosionStorage(&p_world, p_particleList) {

}

BasicBomb::~BasicBomb() {
    float angle = 0.0f;
    while (angle <= 2.0f * M_PI) {
        b2Vec2 position(std::cos(angle) * kRadius(), std::sin(angle) * kRadius());
        position += getPosition();
        m_explosionStorage.addParticle(position, kGasRadius(), angle, kExplosiveForce(),
                                       kDissipateRate());
        angle += kAnglePerParticle();
    }
}

void BasicBomb::processEvents() {
    CircleProjectileEntity::processEvents();
}

void BasicBomb::draw(const io::visual::Camera &p_camera) {
    glColor4f(0.64f, 0.24f, 0.44f, (getHp()/100.0f));
    p_camera.drawCircle(getPosition(), getAngle(), kRadius());
}

}; // end of namespace ammo
}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
