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

#include <list>
#include <memory>
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
#include "gun.h"

namespace shadow_pumpkin_caster::missions {

class Mission {

public:

    Mission(b2World* p_world);
    ~Mission();

    void processEvents();

    void draw(const io::visual::Camera &p_camera);

    void addStaticGround(std::unique_ptr<entity::StaticEntity> p_ground);
    void addDestructableBlock(std::shared_ptr<entity::BlockEntity> p_block);
    void addProjectile(std::shared_ptr<entity::DynamicEntity> p_round);

    void addPumpkin(std::shared_ptr<entity::enemy::Pumpkin> p_pumpkin);
    void addSkeleton(std::shared_ptr<entity::enemy::Skeleton> p_skeleton);
    void addGhost(std::shared_ptr<entity::enemy::Ghost> p_ghost);
    void addNecromancer(std::shared_ptr<entity::enemy::Necromancer> p_necromancer);
    void addWitch(std::shared_ptr<entity::enemy::Witch> p_witch);
    void addVampire(std::shared_ptr<entity::enemy::Vampire> p_vampire);

private:

    b2World* m_world = nullptr;
    Gun m_playerGun;
    std::list<std::unique_ptr<entity::StaticEntity>> m_staticGround;
    std::list<std::shared_ptr<entity::BlockEntity>> m_destructableBlocks;
    std::list<std::shared_ptr<entity::DynamicEntity>> m_hurtEntities;
    std::list<std::shared_ptr<entity::DynamicEntity>> m_projectiles;

    std::list<std::shared_ptr<entity::enemy::Pumpkin>> m_pumpkins;
    std::list<std::shared_ptr<entity::enemy::Skeleton>> m_skeletons;
    std::list<std::shared_ptr<entity::enemy::Gravestone>> m_gravestones;
    std::list<std::shared_ptr<entity::enemy::Ghost>> m_ghosts;
    std::list<std::shared_ptr<entity::enemy::Necromancer>> m_necromancers;
    std::list<std::shared_ptr<entity::enemy::Witch>> m_witches;
    std::list<std::shared_ptr<entity::enemy::Vampire>> m_vampires;

};

}; // end of namespace shadow_pumpkin_caster::missions

