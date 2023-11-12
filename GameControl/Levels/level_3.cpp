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

#include "levels.h"
#include "blockEntity.h"
#include "targetEntity.h"
#include "pumpkin.h"

namespace shadow_pumpkin_caster {
namespace level {

void setUpLevel_3(b2World &p_world, LevelManager::LevelEntities &p_entities) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(70.0f, -5.0f),
        b2Vec2(70.0f, 0.0f)
    };

    p_entities.m_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));

    const std::vector<b2Vec2> kVerticalBlock = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(1.5f, 0.0f),
        b2Vec2(1.5f, 7.5f),
        b2Vec2(0.0f, 7.5f)
    };

    const std::vector<b2Vec2> kHorizontalBlock = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(7.5f, 0.0f),
        b2Vec2(7.5f, 1.25f),
        b2Vec2(0.0f, 1.25f)
    };

    addDynamic(p_entities.m_dynamic, std::make_unique<entity::enemy::Pumpkin>(p_world, b2Vec2(58.25f, 1.0f), 1.0f));
    const int kTowerHeight = 5;
    for (int i = 0; i < kTowerHeight; i++) {
        auto height = static_cast<float>(i) * 8.75f;
        addDynamic(p_entities.m_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(60.0f, height + 0.0f), kVerticalBlock));
        addDynamic(p_entities.m_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(55.0f, height + 0.0f), kVerticalBlock));
        addDynamic(p_entities.m_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(54.5f, height + 7.5f), kHorizontalBlock));
        addDynamic(p_entities.m_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(58.25f, height + 10.0f), 1.0f)); // TODO GHOST
    }
    addDynamic(p_entities.m_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(45.25f, 40.0f), 1.0f)); // TODO GHOST
    addDynamic(p_entities.m_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(70.0f, 40.0f), 1.0f)); // TODO GHOST
}

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
