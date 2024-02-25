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

using MissionEntities_t = shadow_pumpkin_caster::missions::MissionEntities_t;
using DynamicEntity = shadow_pumpkin_caster::entity::DynamicEntity;
using Gavestone = shadow_pumpkin_caster::entity::enemy::Gravestone;

struct GraveData_t {
    b2Vec2 position;
    float radius;
};

/**
 * Indicates if the given entity is dead and if so deletes it
 * @param p_entities list of all entities of the same type
 * @param p_it iterator pointing to the entities ptr in the list
 * @return if the entity is dead or not
 */
template <typename T_list, typename T_it>
bool isEntityDead(T_list &p_entities, T_it &p_it) {
    if ((*p_it)->isDead()) {
        auto deadEntity = p_it--;
        p_entities.erase(deadEntity);
        return true;
    }
    return false;
}

template <typename T_it>
GraveData_t getGraveData(T_it &p_it) {
    return {.position = (*p_it)->getPosition(),
            .radius = (*p_it)->getRadius()};
}

void createGrave(b2World &p_world, std::list<std::shared_ptr<Gavestone>> &p_graves,
                 GraveData_t &p_data) {
    p_graves.push_back(std::make_unique<Gavestone>(p_world, p_data.position, p_data.radius));
}

/**
 * Checks if the given entity is hurt, and adds it to the hurt list if so
 * @param p_it iterator pointing to the entities ptr in the list
 * @param p_hurtEntities list of all entities that are currently hurt
 */
template <typename T_it>
void indicateHurt(T_it &p_it, std::list<std::shared_ptr<DynamicEntity>> &p_hurtEntities) {
    if ((*p_it)->getHp() < 100.0f) {
        p_hurtEntities.push_back(*p_it);
    }
}

/**
 * Process game events for entities with no special after death abilities
 * @param p_entities list of entities to process
 */
template<typename T>
void processBasicEntityList(std::list<std::shared_ptr<T>> &p_entities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        isEntityDead(p_entities, it);
    }
}

/**
 * Process game events for entities that are only healable
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all mission entities
 */
template<typename T>
void processHealableEnitityList(std::list<std::shared_ptr<T>> &p_entities,
                                std::list<std::shared_ptr<DynamicEntity>> &p_hurtEntities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        if (!isEntityDead(p_entities, it)) {
            indicateHurt(it, p_hurtEntities);
        }
    }
}

/**
 * Process game events for entities that become gravestones after death
 * @param p_world box2d world that all entities exist within
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all mission entities
 */
template<typename T>
void processResurrectableEntityList(b2World &p_world, std::list<std::shared_ptr<T>> &p_entities,
               MissionEntities_t &p_allEntities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        GraveData_t graveData = getGraveData(it);
        if (!isEntityDead(p_entities, it)) {
            indicateHurt(it, p_allEntities.hurtEntities);
        } else {
            createGrave(p_world, p_allEntities.gravestones, graveData);
        }
    }
}

/**
 * Process game events for spell casting entities
 * @param p_world box2d world that all entities exist within
 * @param p_entities list of entities to process
 * @param p_allEntities structure containing all mission entities
 */
template<typename T>
void procSpellCastingEntityList(b2World &p_world, std::list<std::shared_ptr<T>> &p_entities,
               MissionEntities_t &p_allEntities) {
    for (auto it = p_entities.begin(); it != p_entities.end(); it++) {
        (*it)->processEvents();
        GraveData_t graveData = getGraveData(it);
        if (!isEntityDead(p_entities, it)) {
            indicateHurt(it, p_allEntities.hurtEntities);
            if ((*it)->canCastSpell(p_allEntities)) {
                (*it)->beginCasting();
            }
            if ((*it)->isSpellCasted()) {
                (*it)->castSpell(p_world, p_allEntities);
            }
        } else {
            createGrave(p_world, p_allEntities.gravestones, graveData);
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

    processBasicEntityList(m_entities.projectiles);
    processHealableEnitityList(m_entities.destructableBlocks, m_entities.hurtEntities);
    processHealableEnitityList(m_entities.pumpkins, m_entities.hurtEntities);
    processResurrectableEntityList(m_world, m_entities.skeletons, m_entities);
    processHealableEnitityList(m_entities.gravestones, m_entities.hurtEntities);
    processHealableEnitityList(m_entities.ghosts, m_entities.hurtEntities);

    procSpellCastingEntityList(m_world, m_entities.necromancers, m_entities);
    procSpellCastingEntityList(m_world, m_entities.witches, m_entities);
    procSpellCastingEntityList(m_world, m_entities.vampires, m_entities);
    m_entities.hurtEntities.clear();
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

