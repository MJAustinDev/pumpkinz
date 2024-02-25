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
#include <functional>

namespace shadow_pumpkin_caster {

namespace missions {
struct MissionEntities_t;
}

namespace entity::enemy {

/**
 * Inherited class that binds spell casting functionality
 */
class SpellCaster {

public:

    SpellCaster(std::function<bool(missions::MissionEntities_t &)> p_canCastSpell,
                std::function<void(b2World &, missions::MissionEntities_t &)> p_castSpell):
        m_canCastSpell(p_canCastSpell), m_castSpell(p_castSpell) {};
    virtual ~SpellCaster() = default;

    /**
     * Progresses with casting the spell
     */
    virtual void processEvents();

    /**
     * Starts to cast it's spell
     */
    void beginCasting();

    /**
     * Indicates if the spell has been fully cast or not
     * @return true iif the spell has completed
     */
    bool isSpellCasted();

    /**
     * Indicates if the caster has a valid target for their spell
     * @param p_entities All mission entities that the spell can effect
     * @return true iif the spells target exists within the mission
     */
    bool canCastSpell(missions::MissionEntities_t &p_entities);

    /**
     * Casts the casters spell, effecting mission entities
     * @param p_world box2d world that the entities exist within
     * @param p_entities All mission entities that the spell can effect
     */
    void castSpell(b2World &p_world, missions::MissionEntities_t &p_entities);

protected:

    /**
     * How far through casting the spell the spell caster is
     * @return spell progress ranged between 0.0f (none) and 1.0f (complete)
     */
    float getSpellProgress();

private:

    bool m_isCasting = false;
    float m_coolDown = 0.0f;
    float m_spellProgress = 0.0f;
    float m_castRate = 1.0f;
    std::function<bool(missions::MissionEntities_t &p_entities)> m_canCastSpell;
    std::function<void(b2World &, missions::MissionEntities_t &)> m_castSpell;

};

}; // end of namespace entity::enemy

}; // end of namespace shadow_pumpkin_caster
