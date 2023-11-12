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

#include "necromancer.h"

namespace {

constexpr float kFragility() { return 0.05f; }
constexpr float kMinCastingSpeed() { return 0.1f; }
constexpr float kMaxCastingSpeed() { return 1.0f; }
constexpr float kCastingLimit() { return 100.0f; }
constexpr float kCooldownReduction() { return 1.0f; }
constexpr float kMinCooldownTime() { return 50.0f; }
constexpr float kMaxCooldownTime() { return 200.0f; }

float randZeroToOne() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float randRanged(float p_min, float p_max) {
    return ((p_max - p_min) * randZeroToOne()) + p_min;
}

}; // end of namespace

namespace shadow_pumpkin_caster {
namespace entity {
namespace enemy {

Necromancer::Necromancer(b2World &p_world, b2Vec2 p_position, float p_radius):
    TargetEntity(p_world, p_position, p_radius, kFragility()) {

}

void Necromancer::processEvents() {
    m_coolDown -= kCooldownReduction();
    if (m_isCasting) {
        m_spellProgress += m_castRate;
    }
    TargetEntity::processEvents();
}

void Necromancer::draw(const visual::Camera &p_camera) {
    float fade = 0.3 + (0.7 * (getHp()/100.0f));
    float spellSize = 2.0f * getRadius() * (m_spellProgress / kCastingLimit());

    glColor4f(0.2f, 0.9f, 0.2f, 0.9f);
    p_camera.drawCircle(getPosition() + b2Vec2(0.0f, 3.0f), getAngle(), spellSize);

    glColor4f(0.2f, 0.25f, 0.2f, fade);
    p_camera.drawCircle(getPosition(), getAngle(), getRadius());
}

void Necromancer::beginCasting() {
    if (!m_isCasting && m_coolDown <= 0.0f) {
        m_isCasting = true;
        m_castRate = randRanged(kMinCastingSpeed(), kMaxCastingSpeed());
    }
}

bool Necromancer::isSpellCasted() {
    if (m_spellProgress >= kCastingLimit()) {
        m_spellProgress = 0.0f;
        m_coolDown = randRanged(kMinCooldownTime(), kMaxCooldownTime());
        m_isCasting = false;
        return true;
    }
    return false;
}

}; // end of namespace enemy
}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
