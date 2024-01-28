 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 # SOFTWARE.

add_subdirectory(GameEntities)

add_executable(shadow_pumpkin_caster
    entry.cpp
    levelManager.cpp
    player.cpp
    GameEntities/Enemies/Spells/necromancy.cpp
    GameEntities/Enemies/Spells/restoration.cpp
    GameEntities/Enemies/Spells/vampirism.cpp
    Levels/level_1.cpp
    Levels/level_2.cpp
    Levels/level_3.cpp
    Levels/level_4.cpp
    Levels/level_5.cpp
    Levels/levelDemo.cpp
)

include_directories(shadow_pumpkin_caster
    ${EXTERNAL_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEntities/Enemies/Spells
    ${CMAKE_CURRENT_SOURCE_DIR}/Levels
)

target_link_libraries(shadow_pumpkin_caster entities user_interface)

set_target_properties(shadow_pumpkin_caster PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
