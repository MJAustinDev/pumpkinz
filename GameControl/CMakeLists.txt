 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 # SOFTWARE.

add_library(bulk STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/levelManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Ammunition/basicBomb.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Ammunition/basicSolidShot.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite/blockEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite/circleProjectileEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite/explosionParticle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite/polygonProjectileEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite/targetEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/ghost.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/gravestone.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/necromancer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/pumpkin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/skeleton.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/vampire.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/witch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells/necromancy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells/restoration.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells/spellCaster.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells/vampirism.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Intrinsic/circleEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Intrinsic/dynamicEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Intrinsic/polygonEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Intrinsic/staticEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/level_1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/level_2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/level_3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/level_4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/level_5.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels/levelDemo.cpp
)

include_directories(bulk
    ${EXTERNAL_INCLUDES}
)

target_link_libraries(bulk user_interface)

target_include_directories(bulk PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Ammunition
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Composite
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Intrinsic
)

add_executable(shadow_pumpkin_caster entry.cpp)
target_link_libraries(shadow_pumpkin_caster bulk)

set_target_properties(shadow_pumpkin_caster PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
