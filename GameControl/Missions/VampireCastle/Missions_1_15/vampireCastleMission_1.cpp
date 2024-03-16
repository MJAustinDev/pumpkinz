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
using Skeleton = shadow_pumpkin_caster::entity::enemy::Skeleton;
using Ghost = shadow_pumpkin_caster::entity::enemy::Ghost;
using Necromancer = shadow_pumpkin_caster::entity::enemy::Necromancer;
using Witch= shadow_pumpkin_caster::entity::enemy::Witch;
using Vampire= shadow_pumpkin_caster::entity::enemy::Vampire;

}; // end of namespace

namespace shadow_pumpkin_caster::missions::vampire_castle {

/// TODO -- IMPLEMENT ACTUAL MISSION, THIS IS DEMO LEVEL 5 (HAS ALL ENTITY TYPES)
void setUpMission_1(MissionEntities_t &p_entities, b2World &p_world) {
    auto placeTower = [&p_entities, &p_world](b2Vec2 p_position) {
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

        auto roof = std::make_shared<BlockEntity>(p_world, p_position, kVerticalBlock);
        auto wallLeft = std::make_shared<BlockEntity>(p_world, p_position + b2Vec2(5.0f, 0.0f),
                                                      kVerticalBlock);
        auto wallRight = std::make_shared<BlockEntity>(p_world, p_position + b2Vec2(0.0f, 7.5f),
                                                       kHorizontalBlock);

        p_entities.destructableBlocks.push_back(std::move(wallLeft));
        p_entities.destructableBlocks.push_back(std::move(wallRight));
        p_entities.destructableBlocks.push_back(std::move(roof));

        if (rand() % 10 <= 4) { // 50/50 of skeleton or pumpkin
            auto pumpkin = std::make_shared<Pumpkin>(p_world, p_position + b2Vec2(3.0f, 9.75f),
                                                     1.0f);
            p_entities.pumpkins.push_back(std::move(pumpkin));
        } else {
            auto skeleton = std::make_shared<Skeleton>(p_world, p_position + b2Vec2(3.0f, 9.75f),
                                                       1.0f);
            p_entities.skeletons.push_back(std::move(skeleton));
        }
    };

    const std::vector<b2Vec2> kGroundShape = {
        b2Vec2(0.0f, 0.0f),
        b2Vec2(0.0f, -5.0f),
        b2Vec2(150.0f, -5.0f),
        b2Vec2(150.0f, 0.0f)
    };
    auto ground = std::make_unique<StaticEntity>(p_world, b2Vec2(-5.0f, 0.0f), kGroundShape);
    p_entities.staticGround.push_back(std::move(ground));

    for (int i = 0; i < 8; i++) {
        auto xShift = static_cast<float>(i) * 6.0f;;
        placeTower(b2Vec2(50.0f + xShift, 0.0f));
        placeTower(b2Vec2(50.0f + xShift, 8.75f));
        auto witch = std::make_shared<Witch>(p_world, b2Vec2(53.0f + xShift, 1.0f), 1.0f);
        p_entities.witches.push_back(std::move(witch));
    }

    for (int i = 0; i < 3; i++) {
        auto yShift = static_cast<float>(i + 2);
        placeTower(b2Vec2(50.0f, yShift * 8.75f));
        placeTower(b2Vec2(68.0f, yShift * 8.75f));
        placeTower(b2Vec2(74.0f, yShift * 8.75f));
        placeTower(b2Vec2(92.0f, yShift * 8.75f));
        placeTower(b2Vec2(115.0f, (yShift - 2.0f) * 8.75f));
    }

    auto vampire = std::make_shared<Vampire>(p_world, b2Vec2(74.0f, (5.0f * 8.75f) + 1.0f), 1.0f);
    auto necromancer = std::make_shared<Necromancer>(p_world, b2Vec2(118.25f, 1.0f), 1.0f);
    auto ghost = std::make_shared<Ghost>(p_world, b2Vec2(25.0f, 100.0f), 1.0f);

    p_entities.vampires.push_back(std::move(vampire));
    p_entities.necromancers.push_back(std::move(necromancer));
    p_entities.ghosts.push_back(std::move(ghost));
}

}; // end of namespace shadow_pumpkin_caster::missions::vampire_castle
