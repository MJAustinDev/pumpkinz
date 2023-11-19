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
#include "skeleton.h"
#include "witch.h"

namespace shadow_pumpkin_caster {
namespace level {

void setUpLevel_5(b2World &p_world, LevelManager::LevelEntities &p_entities) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(150.0f, -5.0f),
        b2Vec2(150.0f, 0.0f)
    };

    p_entities.m_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));

    auto placeTower = [&p_world, &p_entities](b2Vec2 p_position) {

        const std::vector<b2Vec2> kVerticalBlock = {
            b2Vec2(0.0f, 0.0f),
            b2Vec2(1.0f, 0.0f),
            b2Vec2(1.0f, 7.5f),
            b2Vec2(0.0f, 7.5f)
        };

        const std::vector<b2Vec2> kHorizontalBlock = {
            b2Vec2(0.0f, 0.0f),
            b2Vec2(6.0f, 0.0f),
            b2Vec2(6.0f, 1.25f),
            b2Vec2(0.0f, 1.25f)
        };

        addDynamic(p_entities.m_dynamic, std::make_shared<entity::BlockEntity>(p_world, p_position, kVerticalBlock));
        addDynamic(p_entities.m_dynamic, std::make_shared<entity::BlockEntity>(p_world, p_position + b2Vec2(5.0f, 0.0f), kVerticalBlock));
        addDynamic(p_entities.m_dynamic, std::make_shared<entity::BlockEntity>(p_world, p_position + b2Vec2(0.0f, 7.5f), kHorizontalBlock));
        p_entities.m_skeletons.push_back(std::make_shared<entity::enemy::Skeleton>(p_world, p_position + b2Vec2(3.0f, 9.75f), 1.0f));
    };

    for (int i = 0; i < 8; i++) {
        placeTower(b2Vec2(50.0f + (6.0f * static_cast<float>(i)), 0.0f));
        placeTower(b2Vec2(50.0f + (6.0f * static_cast<float>(i)), 8.75f));
        p_entities.m_witches.push_back(std::make_shared<entity::enemy::Witch>(p_world, b2Vec2(53.0f + (6.0f * static_cast<float>(i)), 1.0f), 1.0f));
    }

    for (int i = 0; i < 3; i++) {
        placeTower(b2Vec2(50.0f, static_cast<float>(i + 2) * 8.75f));
        placeTower(b2Vec2(50.0f + 18.0f, static_cast<float>(i + 2) * 8.75f));
        placeTower(b2Vec2(50.0f + 24.0f, static_cast<float>(i + 2) * 8.75f));
        placeTower(b2Vec2(50.0f + 24.0f + 18.0f, static_cast<float>(i + 2) * 8.75f));

        placeTower(b2Vec2(115.0f, static_cast<float>(i) * 8.75f));
    }

    p_entities.m_vampires.push_back(std::make_shared<entity::enemy::Vampire>(p_world, b2Vec2(74.0f, (5.0f * 8.75f) + 1.0f), 1.0f));

    p_entities.m_necromancers.push_back(std::make_shared<entity::enemy::Necromancer>(p_world, b2Vec2(118.25f, 1.0f), 1.0f));
}

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
