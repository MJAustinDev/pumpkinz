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

#include "menuPage.h"
#include "menuButton.h"
#include "pages.h"

namespace {

using ButtonCoords = shadow_pumpkin_caster::ButtonCoords;
using PageReturnData = shadow_pumpkin_caster::PageReturnData;
using PageAction = shadow_pumpkin_caster::PageAction;
using Regions = shadow_pumpkin_caster::Regions;

ButtonCoords shift(ButtonCoords p_coord, float p_shift) {
    p_coord.m_minY += p_shift;
    p_coord.m_maxY += p_shift;
    return p_coord;
}

constexpr ButtonCoords kButtonShape() {
    return {.m_minX = -0.5f, .m_maxX = 0.5f, .m_minY = -0.1f, .m_maxY = 0.1f};
}

constexpr float kPumpkinPatchPos() { return 0.75f; }
constexpr float kHauntedHousePos() { return 0.45f; }
constexpr float kCemeteryPos() { return 0.15f; }
constexpr float kCursedForestPos() { return -0.15f; }
constexpr float kVampireCastlePos() { return -0.45f; }
constexpr float kMainMenuPos() { return -0.75f; }

constexpr PageReturnData kMainMenuButtonData() {
    return {.m_action = PageAction::goMainMenu};
}

constexpr PageReturnData kPumpkinPatchButtonData() {
    return {.m_action = PageAction::goMissionSelect, .m_region = Regions::pumpkinPatch};
}


} // end of namespace

namespace shadow_pumpkin_caster {

void turnToLevelSelect(Page &p_page) {

    resetPage(p_page);

    MenuButton pumpkinPatch(shift(kButtonShape(), kPumpkinPatchPos()), kPumpkinPatchButtonData());
    addButton(p_page, pumpkinPatch);

    MenuButton hauntedHouse(shift(kButtonShape(), kHauntedHousePos()));
    addButton(p_page, hauntedHouse);

    MenuButton cemetery(shift(kButtonShape(), kCemeteryPos()));
    addButton(p_page, cemetery);

    MenuButton cursedForest(shift(kButtonShape(), kCursedForestPos()));
    addButton(p_page, cursedForest);

    MenuButton vampireCastle(shift(kButtonShape(), kVampireCastlePos()));
    addButton(p_page, vampireCastle); // TODO -- Pick better name

    MenuButton mainMenu(shift(kButtonShape(), kMainMenuPos()), kMainMenuButtonData());
    addButton(p_page, mainMenu);
}

}; // end of namespace shadow_pumpkin_caster
