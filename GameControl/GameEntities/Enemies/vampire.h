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

#include "targetEntity.h"
#include "spellCaster.h"

namespace shadow_pumpkin_caster {
namespace entity {
namespace enemy {

/**
 * Specialist enemy, damages projectile entities and is immune to impact damage
 */
class Vampire : public TargetEntity, public SpellCaster {

public:

    /**
     * @param p_world box2d world that the vampire exists within
     * @param p_position vampire's position in the world
     * @param p_radius radius of the vampire
     */
    Vampire(b2World &p_world, b2Vec2 p_position, float p_radius);
    ~Vampire() = default;

    /**
     * @see base class
     */
    void processEvents() override;

    /**
     * @see base class
     */
    void draw(const io::visual::Camera &p_camera) override;

};

}; // end of namespace enemy
}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster

