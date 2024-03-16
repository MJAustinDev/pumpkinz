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

#include "mission.h"

namespace {

using StaticEntity = shadow_pumpkin_caster::entity::StaticEntity;
using Pumpkin = shadow_pumpkin_caster::entity::enemy::Pumpkin;
using BlockEntity = shadow_pumpkin_caster::entity::BlockEntity;

}; // end of namespace

namespace shadow_pumpkin_caster::missions::pumpkin_patch {

/**
 * 3 Pumpkins laying on top of a small structure
 */
void setUpMission_2(MissionEntities_t &p_entities, b2World &p_world) {
    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(100.0f, -5.0f),
        b2Vec2(100.0f, 0.0f)
    };
    auto ground = std::make_unique<StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    const std::vector<b2Vec2> kBlockShape = {
        b2Vec2(0.0f, 5.0f),
        b2Vec2(0.0f, 0.0f),
        b2Vec2(15.0f, 0.0f),
        b2Vec2(15.0f, 5.0f)
    };

    auto block = std::make_shared<BlockEntity>(p_world, b2Vec2(50.0f, 0.0f), kBlockShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    block = std::make_shared<BlockEntity>(p_world, b2Vec2(65.0f, 0.0f), kBlockShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    block = std::make_shared<BlockEntity>(p_world, b2Vec2(55.0f, 5.0f), kBlockShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    auto pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(45.0f, 0.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));

    pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(52.0f, 5.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));

    pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(60.0f, 10.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));
};

};
