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
#include "player.h"
#include "inputController.h"

namespace {

using input = shadow_pumpkin_caster::InputController;

constexpr float kBarrelLength() { return 4.5f;}
constexpr int kBarrelCooldownTime() { return 50; }

bool canFire(int p_cooldown) {
    return (p_cooldown == 0) && (input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT));
}

b2Vec2 getMouseInWorld(b2Vec2 p_playerPosition) {
    b2Vec2 mousePosition = input::getMousePosition();
    mousePosition.x /= 0.01f; // TODO ASSUMING CONSTANT ZOOM, ADDRESS THIS LATER
    mousePosition.y /= 0.01f;
    return mousePosition - p_playerPosition;
}

} // end of namespace

namespace shadow_pumpkin_caster{

Player::Player(b2World* p_world, b2Vec2 p_position):
    m_world(p_world), m_position(p_position) {

}

Player::~Player() {
    m_firedRounds.clear();
}

void Player::processEvents() {
    b2Vec2 mousePosition = getMouseInWorld(m_position);
    m_angle = std::atan2(mousePosition.y, mousePosition.x);

    m_barrelCooldown = (--m_barrelCooldown < 0) ? 0 : m_barrelCooldown;
    if (canFire(m_barrelCooldown)) {
        fire(RoundType::basicSolidShot);
        m_barrelCooldown = kBarrelCooldownTime();
    }

    // process events for all fired rounds
    for (auto it = m_firedRounds.begin(); it != m_firedRounds.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadObj = it--;
            m_firedRounds.erase(deadObj);
        }
    }
}

void Player::draw(const visual::Camera &p_camera) {
    glColor4f(0.75f, 0.34f, 0.79f, 0.75f);
    p_camera.drawCircle(m_position, 0.0f, 1.0f);
    p_camera.drawPolygon(m_position, m_angle, m_arrow);

    for (auto &round : m_firedRounds) {
        round->draw(p_camera);
    }
}

void Player::fire(RoundType p_round) {
    assert(p_round < RoundType::totalRounds);

    std::vector<b2Vec2> basicShape = {b2Vec2(-0.4f, 0.4f),
                                      b2Vec2(-0.4f, -0.4f),
                                      b2Vec2(0.4f, -0.4f),
                                      b2Vec2(0.9f, 0.0f),
                                      b2Vec2(0.4f, 0.4f)};
    b2Vec2 barrelPosition(std::cos(m_angle) * kBarrelLength(),
                          std::sin(m_angle) * kBarrelLength());
    barrelPosition += m_position;
    m_firedRounds.push_back(std::make_unique<entity::ProjectileEntity>(*m_world, barrelPosition,
                                                                       basicShape, m_angle, 35.0f,
                                                                       0.01f));
}

}; // end of namespace shadow_pumpkin_caster
