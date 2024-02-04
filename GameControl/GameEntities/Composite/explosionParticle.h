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

#pragma once

#include <list>
#include <memory>
#include "circleEntity.h"

namespace shadow_pumpkin_caster {
namespace entity {

class ExplosionParticle : public CircleEntity {

public:

    ExplosionParticle(b2World &p_world, b2Vec2 p_position, float p_radius, float p_angle,
                      float p_force, float p_dissipateRate);
    ~ExplosionParticle() = default;

    /**
     * @see base class
     */
    void processEvents() override;

    /**
     * @see base class
     */
    void draw(const io::visual::Camera &p_camera) override;

private:

    float m_dissipateRate;

};

class ParticleContainer {

using ParticleList = std::list<std::shared_ptr<ExplosionParticle>>;

public:

    ParticleContainer(b2World* p_world, ParticleList &p_particles):
        m_world(p_world), m_particles(&p_particles) {

    };
    ~ParticleContainer() = default;

    void addParticle(b2Vec2 p_position, float p_radius, float p_angle, float p_force,
                     float p_dissipateRate) {
        auto particle = std::make_shared<ExplosionParticle>(*m_world, p_position, p_radius,
                                                            p_angle, p_force, p_dissipateRate);
        m_particles->push_back(std::move(particle));
    };

private:

    b2World* m_world;
    ParticleList* m_particles;

};

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
