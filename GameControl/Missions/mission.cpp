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
#include "implementedMissions.h"

namespace {

/**
 * Process game events for entities with no special after death abilities
 * @param p_entities list of entities to process
 */
template <typename T>
void processEntityList(std::list<std::shared_ptr<T>> &p_entities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if ((*it)->isDead()) {
            auto deadEntity = it--;
            p_entities.erase(deadEntity);
        }
    }
}

/**
 * Draws all entities within an entity list
 * @param p_entities list of entities contains within unique pointers
 * @param p_camera camera used to draw each entity
 */
template <typename T>
void drawEntityList(std::list<T> &p_entities, const io::visual::Camera &p_camera) {
    for (auto &entity : p_entities) {
        entity->draw(p_camera);
    }
}

}; // end of namespace

namespace shadow_pumpkin_caster::missions {

Mission::Mission(Regions p_region, unsigned int p_mission):
    m_world(b2Vec2(0.0f, -9.81f)),
    m_playerGun(&m_world, b2Vec2(0.0f, 5.0f))
{
    m_world.SetContactListener(&m_collisionListener);
    auto setUpMission = getMission(p_region, p_mission);
    setUpMission(*this, m_world);
}

Mission::~Mission() {

}

void Mission::processEvents() {
    const float kTimeStep = 1.0f/60.0f;
    const int kVelocityIterations = 8;
    const int kPositionIterations = 3;
    m_world.Step(kTimeStep, kVelocityIterations, kPositionIterations);

    m_playerGun.processEvents();
    auto round = m_playerGun.fire();
    if (round != nullptr) {
        addProjectile(round);
    }

    processEntityList(m_projectiles);
    processEntityList(m_destructableBlocks);
    processEntityList(m_pumpkins);
    processEntityList(m_skeletons);
    processEntityList(m_gravestones);
    processEntityList(m_ghosts);
    processEntityList(m_necromancers);
    processEntityList(m_witches);
    processEntityList(m_vampires);
}

void Mission::draw(const io::visual::Camera &p_camera) {
    drawEntityList(m_staticGround, p_camera);
    drawEntityList(m_destructableBlocks, p_camera);
    drawEntityList(m_hurtEntities, p_camera);
    drawEntityList(m_projectiles, p_camera);
    drawEntityList(m_pumpkins, p_camera);
    drawEntityList(m_skeletons, p_camera);
    drawEntityList(m_gravestones, p_camera);
    drawEntityList(m_ghosts, p_camera);
    drawEntityList(m_necromancers, p_camera);
    drawEntityList(m_witches, p_camera);
    drawEntityList(m_vampires, p_camera);

    m_playerGun.draw(p_camera);
}

void Mission::addStaticGround(std::unique_ptr<entity::StaticEntity> p_ground) {
    m_staticGround.push_back(std::move(p_ground));
}

void Mission::addDestructableBlock(std::shared_ptr<entity::BlockEntity> p_block) {
    m_destructableBlocks.push_back(std::move(p_block));
}

void Mission::addProjectile(std::shared_ptr<entity::DynamicEntity> p_round) {
    m_projectiles.push_back(std::move(p_round));
}

void Mission::addPumpkin(std::shared_ptr<entity::enemy::Pumpkin> p_pumpkin) {
    m_pumpkins.push_back(std::move(p_pumpkin));
}

void Mission::addSkeleton(std::shared_ptr<entity::enemy::Skeleton> p_skeleton) {
    m_skeletons.push_back(std::move(p_skeleton));
}

void Mission::addGhost(std::shared_ptr<entity::enemy::Ghost> p_ghost) {
    m_ghosts.push_back(std::move(p_ghost));
}

void Mission::addNecromancer(std::shared_ptr<entity::enemy::Necromancer> p_necromancer) {
    m_necromancers.push_back(std::move(p_necromancer));
}

void Mission::addWitch(std::shared_ptr<entity::enemy::Witch> p_witch) {
    m_witches.push_back(std::move(p_witch));
}

void Mission::addVampire(std::shared_ptr<entity::enemy::Vampire> p_vampire) {
    m_vampires.push_back(std::move(p_vampire));
}

}; // end of namespace shadow_pumpkin_caster::missions

