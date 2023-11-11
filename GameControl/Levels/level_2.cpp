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

void setUpLevel_2(b2World &p_world, std::list<std::unique_ptr<entity::DynamicEntity>> &p_dynamic,
                  std::list<std::unique_ptr<entity::StaticEntity>> &p_static) {

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(100.0f, -5.0f),
        b2Vec2(100.0f, 0.0f)
    };

    p_static.push_back(std::make_unique<entity::StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape));

    const std::vector<b2Vec2> kVerticalBlock = {
        b2Vec2(-0.8f, 0.0f),
        b2Vec2(0.8f, 0.0f),
        b2Vec2(0.8f, 7.5f),
        b2Vec2(-0.8f, 7.5f)
    };

    const std::vector<b2Vec2> kHorizontalBlock = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(5.0f, 0.0f),
        b2Vec2(5.0f, 1.25f),
        b2Vec2(0.0f, 1.25f)
    };

    const std::vector<b2Vec2> kBlockLeft = {
        b2Vec2(-0.8f, 0.0f),
        b2Vec2(5.0f, 0.0f),
        b2Vec2(5.0f, 1.25f),
        b2Vec2(-1.3f, 1.25f),
    };

    const std::vector<b2Vec2> kBlockRight = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(5.8f, 0.0f),
        b2Vec2(6.3f, 1.25f),
        b2Vec2(0.0f, 1.25f)
    };

    const std::vector<b2Vec2> kRoofBlock = {
        b2Vec2(-0.9f, 0.0f),
        b2Vec2(5.8f, 0.0f),
        b2Vec2(6.3f, 1.25f),
        b2Vec2(-1.4f, 1.25f)
    };

    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(50.0f, 0.0f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(55.0f, 0.0f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(60.0f, 0.0f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(65.0f, 0.0f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(52.5f, 0.0f), 1.0f)); // TODO SKELETON
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(57.5f, 0.0f), 1.0f)); // TODO PUMPKIN
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(62.5f, 0.0f), 1.0f)); // TODO SKELETON

    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(50.0f, 7.5f), kBlockLeft));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(55.0f, 7.5f), kHorizontalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(60.0f, 7.5f), kBlockRight));
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(52.5f, 8.75f), 1.0f)); // TODO SKELETON
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(57.5f, 8.75f), 1.0f)); // TODO PUMPKIN
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(62.5f, 8.75f), 1.0f)); // TODO SKELETON

    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(55.0f, 8.75f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(60.0f, 8.75f), kVerticalBlock));
    addDynamic(p_dynamic, std::make_unique<entity::BlockEntity>(p_world, b2Vec2(55.0f, 16.25f), kRoofBlock));
    addDynamic(p_dynamic, std::make_unique<entity::TargetEntity>(p_world, b2Vec2(57.5f, 17.5f), 1.0f)); // TODO SKELETON

}

}; // end of namespace level
}; // end of namespace shadow_pumpkin_caster
