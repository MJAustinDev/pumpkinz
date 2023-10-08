/**
 * MIT License
 *
 * Copyright (c) 2023 Matthew James Austin
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

#include "box2d/box2d.h"

#include "camera.h"

namespace entity {

/**
 * Base that all game entities inherit from
 */
class BaseEntity {

public:

    /**
     * Defines the entities body in the world
     * @param p_world box2d world that the entity exists within
     * @param p_position entity's position in the world
     * @param p_type box2d body type, dynamic/static
     * @param p_dataPtr User data ptr for passing information between b2Bodies and game classes
     */
    BaseEntity(b2World &p_world, b2Vec2 p_position, b2BodyType p_type, void* p_dataPtr = nullptr) {
        b2BodyDef bodyDef;
        bodyDef.position = p_position;
        bodyDef.type = p_type;
        if (p_dataPtr != nullptr) {
            bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(p_dataPtr);
        }

        m_body = p_world.CreateBody(&bodyDef);
    };

    /**
     * Handles box2d deallocation
     */
    ~BaseEntity() {
        if (m_body != nullptr) {
            m_body->GetWorld()->DestroyBody(m_body);
        }
    }

    /**
     * Process end of tick events for the entity
     */
    virtual void processEvents() = 0;

    /**
     * Draws the entity to the screen
     * @param p_camera camera that draws the world to the screen
     */
    virtual void draw(const visual::Camera &p_camera) = 0;

protected:

    /**
     * @return position of the entity in the world
     */
    b2Vec2 getPosition() { return m_body->GetPosition(); };

    /**
     * @return the entity's angle
     */
    float getAngle() { return m_body->GetAngle(); };

    /**
     * Adds a new fixture to the entity's body
     * @param p_shape shape that the fixture has
     * @param p_density density of the fixture
     */
    void addFixture(b2Shape &p_shape, float p_density) {
        m_body->CreateFixture(&p_shape, p_density);
    };

private:

    b2Body* m_body = nullptr;

};

}; // end of namespace entity
