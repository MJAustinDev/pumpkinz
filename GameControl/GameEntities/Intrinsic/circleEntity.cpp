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

#include "circleEntity.h"

namespace shadow_pumpkin_caster {
namespace entity {

CircleEntity::CircleEntity(b2World &p_world, b2Vec2 p_position, float p_radius, float p_fragility):
    DynamicEntity(p_world, p_position, p_fragility),
    m_radius(p_radius) {

    b2CircleShape shape;
    shape.m_radius = m_radius;
    addFixture(shape, 1.0f);
}


void CircleEntity::draw(const io::visual::Camera &p_camera) {
    float fade = 0.3 + (0.7 * (getHp()/100.0f));
    glColor4f(0.1f, 0.9f, 0.9f, fade);
    p_camera.drawCircle(getPosition(), getAngle(), m_radius);
}

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
