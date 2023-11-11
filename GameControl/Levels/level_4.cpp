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

namespace shadow_pumpkin_caster {
namespace level {

void setUpLevel_4(b2World &p_world, std::list<std::unique_ptr<entity::DynamicEntity>> &p_dynamic,
                  std::list<std::unique_ptr<entity::StaticEntity>> &p_static) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(25.0f, -5.0f),
        b2Vec2(25.0f, 0.0f)
    };

    p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));
    p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(20.0f, 0.0f), kGroundShape));
    p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(45.0f, 0.0f), kGroundShape));
    //p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(70.0f, 0.0f), kGroundShape));
    p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(95.0f, 0.0f), kGroundShape));

    auto placeTower = [&p_world, &p_dynamic](b2Vec2 p_position) {

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

        addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, p_position, kVerticalBlock));
        addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, p_position + b2Vec2(5.0f, 0.0f), kVerticalBlock));
        addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, p_position + b2Vec2(0.0f, 7.5f), kHorizontalBlock));
        addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, p_position + b2Vec2(3.0f, 8.75f), 1.0f)); // TODO SKELETON
    };

    for (int i = 0; i < 4; i++) {
        placeTower(b2Vec2(35.0f + (6.0f * static_cast<float>(i)), 0.0f));
        addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(38.0f + (6.0f * static_cast<float>(i)), 0.0f), 1.0f)); // TODO NECROMANCER
    }

    for (int i = 0; i < 3; i++) {

        placeTower(b2Vec2(35.25f, static_cast<float>(i + 1) * 8.75f));
        placeTower(b2Vec2(52.75f, static_cast<float>(i + 1) * 8.75f));

        placeTower(b2Vec2(105.0f, static_cast<float>(i) * 8.75f));
    }
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(108.25f, 0.0f), 1.0f)); // TODO NECROMANCER
}

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
