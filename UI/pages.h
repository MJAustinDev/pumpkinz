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

namespace shadow_pumpkin_caster {

struct Page;

enum class PageAction {
    none = 0,
    goMainMenu,
    goLevelSelect,
    goMissionSelect,
    goHelp,
    quit,
    startLevel
};

enum class Regions {
    none = 0,
    pumpkinPatch
};

struct PageReturnData {
    PageAction m_action = PageAction::none;
    Regions m_region = Regions::none;
    unsigned int m_mission = 0;

    bool operator != (PageReturnData const &p_rhs) const {
        return m_action != p_rhs.m_action || m_region != p_rhs.m_region || m_mission != p_rhs.m_mission;
    }
};

constexpr PageReturnData kEmptyPageData() { return {}; };

void turnToMainMenu(Page &p_page);

void turnToLevelSelect(Page &p_page);

void turnToMissionSelect(Page &p_page);

void turnToHelp(Page &p_page);

}; // end of namespace shadow_pumpkin_caster
