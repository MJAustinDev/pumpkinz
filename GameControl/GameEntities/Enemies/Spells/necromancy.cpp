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

#include "necromancy.h"
#include "skeleton.h"
#include "gravestone.h"

namespace shadow_pumpkin_caster {
namespace entity {
namespace enemy {
namespace spell {

void necromancy(b2World &p_world, LevelManager::LevelEntities &p_entities) {
    if (p_entities.m_gravestones.size() == 0) {
        return; // nothing to reanimate
    }

    auto gravestonePtr = std::move(p_entities.m_gravestones.front());
    p_entities.m_gravestones.pop_front();
    p_entities.m_skeletons.push_back(std::make_unique<Skeleton>(p_world,
                                                                gravestonePtr->getPosition(),
                                                                gravestonePtr->getRadius()));
}

}; // end of namespace spell
}; // end of namespace enemy
}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster