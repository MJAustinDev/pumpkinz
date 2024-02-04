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

#include "box2d/box2d.h"
#include <vector>
#include <memory>
#include "camera.h"
#include "polygonProjectileEntity.h"
#include "explosionParticle.h"

namespace shadow_pumpkin_caster {

enum class RoundType {
    none = 0,
    basicSolidShot,
    basicBomb,

    totalRounds
};

class Player {

public:

    Player(b2World* p_world, b2Vec2 p_position);
    ~Player();

    void clearGasParticles();

    void processEvents();
    void draw(const io::visual::Camera &p_camera);
    std::shared_ptr<entity::DynamicEntity> fire();

private:

    b2World* m_world;
    b2Vec2 m_position;
    float m_angle = 0.0f;
    int m_barrelCooldown = 0;
    RoundType m_nextRound = RoundType::none;
    std::vector<b2Vec2> m_arrow = {b2Vec2(-0.5f, 0.5f), b2Vec2(-0.5f, -0.5f), b2Vec2(4.5f, 0.0f)};
    std::list<std::shared_ptr<entity::ExplosionParticle>> m_particles = {};

};

}; // end of namespace shadow_pumpkin_caster
