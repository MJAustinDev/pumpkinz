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

#include <vector>
#include <list>
#include "baseEntity.h"
#include "entityData.h"

namespace shadow_pumpkin_caster {
namespace entity {

/**
 * User data structure used to transfer information form the b2body to the class
 */
struct DynamicBodyData {
    std::list<float> m_energies;
};

/**
 * Movable & destructible entity
 */
class DynamicEntity : public BaseEntity {

public:

    /**
     * @param p_world box2d world that the entity exists within
     * @param p_position entity's position in the world
     * @param p_shape series of points that defines the entity's shape
     * @param p_fragility magnifies the damage dealt by energy transfer
     */
    DynamicEntity(b2World &p_world, b2Vec2 p_position, float p_fragility, float p_angle = 0.0f);
    ~DynamicEntity() = default;

    /**
     * See base class
     */
    void processEvents() override;

    /**
     * See base class
     */
    void draw(const io::visual::Camera &p_camera) = 0;

    /**
     * @return if the entity's hit points are less than zero
     */
    bool isDead() { return m_hp < 0.0f; };

    /**
     * @return entity's current hit points
     */
    float getHp() { return m_hp; };

    /**
     * Manually applies hp change to the entity
     * @param p_hpLoss hit points to remove from the entity
     */
    void applyHpChange(float p_hp) { m_hp += p_hp; };

protected:

    void setType(EntityType p_type) {
        m_bodyData.m_type = p_type;
    }

private:

    float m_hp = 100.0f;
    float m_fragility = 0.25f;
    EntityBodyData m_bodyData;

};

}; // end of namespace entity
}; // end of namespace shadow_pumpkin_caster
