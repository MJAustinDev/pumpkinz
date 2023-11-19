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

#pragma once

#include "circleProjectileEntity.h"
#include "explosionParticle.h"

namespace shadow_pumpkin_caster {
namespace entity {
namespace ammo {

class BasicBomb : public CircleProjectileEntity {

public:

    BasicBomb(b2World &p_world, b2Vec2 p_position, float p_angle, float p_force, std::list<std::shared_ptr<ExplosionParticle>> &p_particleList);
    ~BasicBomb();

    /**
     * See base class
     */
    void processEvents() override;

    /**
     * See base class
     */
    void draw(const visual::Camera &p_camera) override;

private:

    ParticleContainer m_explosionStorage; // not owning

};

}; // end of namespace ammo
}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
