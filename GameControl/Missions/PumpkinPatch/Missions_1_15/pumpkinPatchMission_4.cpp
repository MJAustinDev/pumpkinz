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
 * A tower on top of a bridge
 */
void setUpMission_4(MissionEntities_t &p_entities, b2World &p_world) {
    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(25.0f, -5.0f),
        b2Vec2(25.0f, 0.0f)
    };
    auto ground = std::make_unique<StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(20.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(55.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    const std::vector<b2Vec2> kWallShape = {
        b2Vec2(0.0f, 4.0f),
        b2Vec2(0.0f, 0.0f),
        b2Vec2(1.0f, 0.0f),
        b2Vec2(1.0f, 4.0f)
    };
    const std::vector<b2Vec2> kBridgeShape = {
        b2Vec2(0.0f, 1.0f),
        b2Vec2(0.0f, 0.0f),
        b2Vec2(16.0f, 0.0f),
        b2Vec2(16.0f, 1.0f)
    };

    // build the bridge
    auto block = std::make_shared<BlockEntity>(p_world, b2Vec2(43.0f, 0.0f), kWallShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    block = std::make_shared<BlockEntity>(p_world, b2Vec2(56.0f, 0.0f), kWallShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    block = std::make_shared<BlockEntity>(p_world, b2Vec2(42.0f, 4.0f), kBridgeShape);
    p_entities.destructableBlocks.push_back(std::move(block));

    auto placeTower = [&p_entities, &p_world, kWallShape](b2Vec2 p_position) {
        const std::vector<b2Vec2> kRoofShape = {
            b2Vec2(0.0f, 1.0f),
            b2Vec2(0.0f, 0.0f),
            b2Vec2(5.0f, 0.0f),
            b2Vec2(5.0f, 1.0f)
        };
        auto block = std::make_shared<BlockEntity>(p_world, p_position, kWallShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        block = std::make_shared<BlockEntity>(p_world, p_position + b2Vec2(4.0f, 0.0f), kWallShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        block = std::make_shared<BlockEntity>(p_world, p_position + b2Vec2(0.0f, 4.0f),
                                              kRoofShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        auto pumpkin = std::make_shared<Pumpkin>(p_world, p_position + b2Vec2(2.5f, 0.5f), 1.05f);
        p_entities.pumpkins.push_back(std::move(pumpkin));
    };

    for (int i = 0; i < 5; i++) { // build the tower
        placeTower(b2Vec2(45.0f, 5.0f + (static_cast<float>(i) * 5.0f)));
        placeTower(b2Vec2(50.0f, 5.0f + (static_cast<float>(i) * 5.0f)));
    }
};

};
