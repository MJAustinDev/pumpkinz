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

#include "explosionParticle.h"

namespace {

constexpr float kFragility() { return 0.0f; }

} // end of namespace

namespace shadow_pumpkin_caster {
namespace entity {

ExplosionParticle::ExplosionParticle(b2World &p_world, b2Vec2 p_position, float p_radius,
                                     float p_angle, float p_force, float p_dissipateRate):
    CircleEntity(p_world, p_position, p_radius, kFragility()), m_dissipateRate(p_dissipateRate) {

    setType(EntityType::projectile);
    b2Vec2 force(std::cos(p_angle) * p_force, std::sin(p_angle) * p_force);
    applyImpulse(force);
}

void ExplosionParticle::processEvents() {
    applyDamage(m_dissipateRate);
    DynamicEntity::processEvents();
}


void ExplosionParticle::draw(const visual::Camera &p_camera) {
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    p_camera.drawCircle(getPosition(), 0.0f, getRadius());
}

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
