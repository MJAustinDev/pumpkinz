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

#include <cmath>
#include "player.h"
#include "inputController.h"
#include "basicSolidShot.h"
#include "basicBomb.h"

namespace {

using input = io::input::InputController;
using DynamicEntity = shadow_pumpkin_caster::entity::DynamicEntity;
using BasicSolidShot = shadow_pumpkin_caster::entity::ammo::BasicSolidShot;
using BasicBomb = shadow_pumpkin_caster::entity::ammo::BasicBomb;
using ExplosionParticlePtr = std::shared_ptr<shadow_pumpkin_caster::entity::ExplosionParticle>;

constexpr float kBarrelLength() { return 4.5f; }
constexpr int kBarrelCooldownTime() { return 50; }

bool canFire(int p_cooldown, int p_button) {
    return (p_cooldown == 0) && (input::getMouseButtonPressed(p_button));
}

std::shared_ptr<DynamicEntity> createBasicSolidShot(b2World &p_world, b2Vec2 p_position,
                                                    float p_angle) {
    auto round = std::make_shared<BasicSolidShot>(p_world, p_position, p_angle, 35.0f);
    return static_cast<std::shared_ptr<DynamicEntity>>(std::move(round));
}


std::shared_ptr<DynamicEntity> createBasicBomb(b2World &p_world, b2Vec2 p_position, float p_angle,
                                               std::list<ExplosionParticlePtr> &p_particleList) {
    auto round = std::make_shared<BasicBomb>(p_world, p_position, p_angle, 135.0f, p_particleList);
    return static_cast<std::shared_ptr<DynamicEntity>>(std::move(round));
}

} // end of namespace

namespace shadow_pumpkin_caster{

Player::Player(b2World* p_world, b2Vec2 p_position):
    m_world(p_world), m_position(p_position) {

}

Player::~Player() {
    clearGasParticles();
}

void Player::processEvents() {
    b2Vec2 mouseDisplacement = input::getMousePositionInWorld() - m_position;
    m_angle = std::atan2(mouseDisplacement.y, mouseDisplacement.x);

    m_barrelCooldown = (--m_barrelCooldown < 0) ? 0 : m_barrelCooldown;
    if (canFire(m_barrelCooldown, GLFW_MOUSE_BUTTON_LEFT)) {
        m_nextRound = RoundType::basicSolidShot;
        m_barrelCooldown = kBarrelCooldownTime();
    }
    else if (canFire(m_barrelCooldown, GLFW_MOUSE_BUTTON_RIGHT)) {
        m_nextRound = RoundType::basicBomb;
        m_barrelCooldown = kBarrelCooldownTime();
    }

    // process events for all explosions
    for (auto it = m_particles.begin(); it != m_particles.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadObj = it--;
            m_particles.erase(deadObj);
        }
    }
}

void Player::draw(const io::visual::Camera &p_camera) {
    glColor4f(0.75f, 0.34f, 0.79f, 0.75f);
    p_camera.drawCircle(m_position, 0.0f, 1.0f);
    p_camera.drawPolygon(m_position, m_angle, m_arrow);

    for (auto &particle: m_particles) {
        particle->draw(p_camera);
    }
}

void Player::clearGasParticles() {
    m_particles.clear();
}

std::shared_ptr<DynamicEntity> Player::fire() {

    b2Vec2 barrelPosition(std::cos(m_angle) * kBarrelLength(),
                          std::sin(m_angle) * kBarrelLength());
    barrelPosition += m_position;

    std::shared_ptr<DynamicEntity> round;
    switch (m_nextRound) {
        case RoundType::none: {
            round = nullptr;
            break;
        }
        case RoundType::basicSolidShot: {
            round = createBasicSolidShot(*m_world, barrelPosition, m_angle);
            break;
        }
        case RoundType::basicBomb: {
            round = createBasicBomb(*m_world, barrelPosition, m_angle, m_particles);
            break;
        }

        case RoundType::totalRounds: [[fallthrough]];
        default: assert(false); // round has likely not been implemented yet!
    }

    m_nextRound = RoundType::none;
    return round;
}

}; // end of namespace shadow_pumpkin_caster
