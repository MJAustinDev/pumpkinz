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
using BlockEntity = shadow_pumpkin_caster::entity::BlockEntity;
using Pumpkin = shadow_pumpkin_caster::entity::enemy::Pumpkin;

}; // end of namespace

namespace shadow_pumpkin_caster::missions::pumpkin_patch {

/**
 * A strong wall with pumpkins on top and behind
 */
void setUpMission_5(MissionEntities_t &p_entities, b2World &p_world) {
    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(25.0f, -5.0f),
        b2Vec2(25.0f, 0.0f)
    };
    const std::vector<b2Vec2> kSlopeShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(25.0f, 10.0f),
        b2Vec2(25.0f, 15.0f)
    };
    auto ground = std::make_unique<StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(20.0f, 0.0f), kSlopeShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(45.0f, 15.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    ground = std::make_unique<StaticEntity>(p_world, b2Vec2(70.0f, 15.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));//rem later

    auto placeLengthOfWall = [&p_entities, &p_world](b2Vec2 p_position, unsigned int p_blocks) {
        const std::vector<b2Vec2> kBlockShape = {
            b2Vec2(0.0f, 1.0f),
            b2Vec2(0.0f, 0.0f),
            b2Vec2(2.0f, 0.0f),
            b2Vec2(2.0f, 1.0f)
        };

        for (int i = 0; i < p_blocks; i++) {
            auto position = p_position + b2Vec2(static_cast<float>(i) * 2.0f, 0.0f);
            auto block = std::make_shared<BlockEntity>(p_world, position, kBlockShape);
            p_entities.destructableBlocks.push_back(std::move(block));
        }
    };

    auto placeEndsOfWall = [&p_entities, &p_world](b2Vec2 p_position, unsigned int p_blocks) {
        const std::vector<b2Vec2> kSmallBlockShape = {
            b2Vec2(0.0f, 1.0f),
            b2Vec2(0.0f, 0.0f),
            b2Vec2(1.0f, 0.0f),
            b2Vec2(1.0f, 1.0f)
        };
        auto block = std::make_shared<BlockEntity>(p_world, p_position, kSmallBlockShape);
        p_entities.destructableBlocks.push_back(std::move(block));

        p_position.x += 1.0f + (2.0f * static_cast<float>(p_blocks));
        block = std::make_shared<BlockEntity>(p_world, p_position, kSmallBlockShape);
        p_entities.destructableBlocks.push_back(std::move(block));
    };

    auto placeWall = [&p_entities, &p_world, &placeLengthOfWall, &placeEndsOfWall]
                     (b2Vec2 p_position, unsigned int p_blocks, bool p_isSplit) {
        if (p_isSplit) {
            placeEndsOfWall(p_position, (--p_blocks));
            p_position.x += 1.0f;
        }
        placeLengthOfWall(p_position, p_blocks);
    };

    const unsigned int kWallLength = 4;
    const unsigned int kWallHeight = 12;
    for (int i = 0; i < kWallHeight; i++) {
        placeWall(b2Vec2(50.0f, 15.0f + (i * 2.0f)), kWallLength, true);
        placeWall(b2Vec2(50.0f, 16.0f + (i * 2.0f)), kWallLength, false);
    }

    auto pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(51.5f, 39.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));

    pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(54.0f, 39.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));

    pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(56.5f, 39.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));

    pumpkin = std::make_shared<Pumpkin>(p_world, b2Vec2(65.5f, 15.5f), 1.0f);
    p_entities.pumpkins.push_back(std::move(pumpkin));
}

}; // end of namespace shadow_pumpkin_caster::missions::pumpkin_patch
