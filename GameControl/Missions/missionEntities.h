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

#pragma once

#include<memory>
#include<list>
#include "staticEntity.h"
#include "dynamicEntity.h"
#include "blockEntity.h"
#include "pumpkin.h"
#include "skeleton.h"
#include "gravestone.h"
#include "ghost.h"
#include "necromancer.h"
#include "witch.h"
#include "vampire.h"

namespace shadow_pumpkin_caster::missions {

/**
 * Binds all mission entity lists in one easy access structure
 */
struct MissionEntities_t {
    std::list<std::unique_ptr<entity::StaticEntity>> staticGround;
    std::list<std::shared_ptr<entity::BlockEntity>> destructableBlocks;
    std::list<std::shared_ptr<entity::DynamicEntity>> hurtEntities;
    std::list<std::shared_ptr<entity::DynamicEntity>> projectiles;

    std::list<std::shared_ptr<entity::enemy::Pumpkin>> pumpkins;
    std::list<std::shared_ptr<entity::enemy::Skeleton>> skeletons;
    std::list<std::shared_ptr<entity::enemy::Gravestone>> gravestones;
    std::list<std::shared_ptr<entity::enemy::Ghost>> ghosts;
    std::list<std::shared_ptr<entity::enemy::Necromancer>> necromancers;
    std::list<std::shared_ptr<entity::enemy::Witch>> witches;
    std::list<std::shared_ptr<entity::enemy::Vampire>> vampires;
};

}; // end of namespace shadow_pumpkin_caster::missions
