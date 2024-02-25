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
    setUpMission(m_entities, m_world);
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

    processEntityList(m_entities.projectiles);
    processEntityList(m_entities.destructableBlocks);
    processEntityList(m_entities.pumpkins);
    processEntityList(m_entities.skeletons);
    processEntityList(m_entities.gravestones);
    processEntityList(m_entities.ghosts);
    processEntityList(m_entities.necromancers);
    processEntityList(m_entities.witches);
    processEntityList(m_entities.vampires);
}

void Mission::draw(const io::visual::Camera &p_camera) {
    drawEntityList(m_entities.staticGround, p_camera);
    drawEntityList(m_entities.destructableBlocks, p_camera);
    drawEntityList(m_entities.hurtEntities, p_camera);
    drawEntityList(m_entities.projectiles, p_camera);
    drawEntityList(m_entities.pumpkins, p_camera);
    drawEntityList(m_entities.skeletons, p_camera);
    drawEntityList(m_entities.gravestones, p_camera);
    drawEntityList(m_entities.ghosts, p_camera);
    drawEntityList(m_entities.necromancers, p_camera);
    drawEntityList(m_entities.witches, p_camera);
    drawEntityList(m_entities.vampires, p_camera);

    m_playerGun.draw(p_camera);
}

void Mission::addProjectile(std::shared_ptr<entity::DynamicEntity> p_round) {
    m_entities.projectiles.push_back(std::move(p_round));
}

}; // end of namespace shadow_pumpkin_caster::missions

