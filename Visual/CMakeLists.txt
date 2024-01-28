 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 # SOFTWARE.

add_library(lib_visual STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../GameControl/inputController.cpp
    # TODO move into local lib and change to input/output
)

include_directories(lib_visual PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../GitMarsVolcanoDash/MarsVolcanoDash/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/include/
)

target_link_libraries(lib_visual
    OpenGL::GL
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/build/bin/libbox2d.a
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/build/bin/libglfw.a
)

target_include_directories(lib_visual PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../GameControl
)
