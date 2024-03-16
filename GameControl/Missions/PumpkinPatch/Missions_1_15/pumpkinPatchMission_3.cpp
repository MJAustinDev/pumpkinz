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
 * Level contains a tower with 3 pumpkins on each level
 */
void setUpMission_3(MissionEntities_t &p_entities, b2World &p_world) {
    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(15.0f, -5.0f),
        b2Vec2(15.0f, 0.0f)
    };
    auto ground = std::make_unique<StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(75.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    auto placeTower = [&p_entities, &p_world](float p_positionY) {
        const std::vector<b2Vec2> kWallShape = {
            b2Vec2(0.0f, 8.0f),
            b2Vec2(0.0f, 0.0f),
            b2Vec2(2.0f, 0.0f),
            b2Vec2(2.0f, 8.0f)
        };
        const std::vector<b2Vec2> kRoofShape = {
            b2Vec2(0.0f, 2.0f),
            b2Vec2(0.0f, 0.0f),
            b2Vec2(13.0f, 0.0f),
            b2Vec2(13.0f, 2.0f)
        };

        auto block = std::make_shared<BlockEntity>(p_world, b2Vec2(76.0f, p_positionY), kWallShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        block = std::make_shared<BlockEntity>(p_world, b2Vec2(87.0f, p_positionY), kWallShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        block = std::make_shared<BlockEntity>(p_world, b2Vec2(76.0f, 8.0f + p_positionY),
                                              kRoofShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        auto pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(79.5f, 0.5f + p_positionY), 1.0f);
        p_entities.pumpkins.push_back(std::move(pumpkin));

        pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(85.5f, 0.5f + p_positionY), 1.0f);
        p_entities.pumpkins.push_back(std::move(pumpkin));

        pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(82.5f, 1.5f + p_positionY), 1.5f);
        p_entities.pumpkins.push_back(std::move(pumpkin));
    };

    for (int i = 0; i < 5; i++) {
        placeTower(static_cast<float>(i) * 10.0f);
    }
};

};
