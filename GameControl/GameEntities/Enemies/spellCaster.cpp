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

#include <random>
#include "spellCaster.h"

namespace {

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

namespace shadow_pumpkin_caster::entity::enemy {

void SpellCaster::beginCasting() {
    if (!m_isCasting && m_coolDown <= 0.0f) {
        m_isCasting = true;
        m_castRate = randRanged(kMinCastingSpeed(), kMaxCastingSpeed());
    }
}

void SpellCaster::processEvents() {
    m_coolDown -= (m_coolDown > 0.0f) ? kCooldownReduction() : 0.0f;
    if (m_isCasting) {
        m_spellProgress += m_castRate;
    }
}

bool SpellCaster::isSpellCasted() {
    if (m_spellProgress >= kCastingLimit()) {
        m_spellProgress = 0.0f;
        m_coolDown = randRanged(kMinCooldownTime(), kMaxCooldownTime());
        m_isCasting = false;
        return true;
    }
    return false;
}

float SpellCaster::getSpellProgress() {
    return m_spellProgress / kCastingLimit();
}

void SpellCaster::castSpell(b2World &p_world, missions::MissionEntities_t &p_entities) {
    m_castSpell(p_world, p_entities);
}

bool SpellCaster::canCastSpell(missions::MissionEntities_t &p_entities) {
    return m_canCastSpell(p_entities);
}

}; // end of namespace shadow_pumpkin_caster::entity::enemy
