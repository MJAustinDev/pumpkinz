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

#include "vampirism.h"

namespace shadow_pumpkin_caster::entity::enemy::spell {

bool vampirismCanCast(missions::MissionEntities_t &p_entities) {
    return p_entities.projectiles.size() > 0;
}

void vampirism(b2World &p_world, missions::MissionEntities_t &p_entities) {
    if (!vampirismCanCast(p_entities)) {
        return; // nothing to drain
    }
    const float kDrain = 75.0f;
    p_entities.projectiles.front()->applyHpChange(-kDrain);
}

}; // end of namespace shadow_pumpkin_caster::entity::enemy::spell
