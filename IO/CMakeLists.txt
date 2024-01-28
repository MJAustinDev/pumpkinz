 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 # SOFTWARE.

add_library(input_output STATIC
    camera.cpp
    inputController.cpp
)

include_directories(input_output PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../GitMarsVolcanoDash/MarsVolcanoDash/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/include/
)

target_link_libraries(input_output
    OpenGL::GL
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/build/bin/libbox2d.a
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../StorageCompiledLibs/box2d/build/bin/libglfw.a
)

target_include_directories(input_output PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
