
set(_3RDPARTY_ROOT ${CMAKE_BINARY_DIR}/_3rdparty)


message (STATUS "-----------------------------------------------------------------------")
message (STATUS "NLOHMANN JSON ---------------------------------------------------------")
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.9.1
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

message (STATUS "-----------------------------------------------------------------------")
message (STATUS "WHOSHUU CPR -----------------------------------------------------------")
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/cppdvl/cpr.git
        GIT_TAG v.1.5.1.dvl.1
)
FetchContent_GetProperties(cpr)
if(NOT cpr_POPULATED)
    FetchContent_Populate(cpr)
    add_subdirectory(${cpr_SOURCE_DIR} ${cpr_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
set(cpr_INCLUDE_DIR ${cpr_SOURCE_DIR}/include)

message (STATUS "-----------------------------------------------------------------------")
message (STATUS "GLFW ------------------------------------------------------------------")

set(GLFW_NAME glfw)
set(GLFW_PREFIX ${_3RDPARTY_ROOT}/${GLFW_NAME})

ExternalProject_Add(
        ${GLFW_NAME}
        PREFIX ${GLFW_PREFIX}
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.2
        BINARY_DIR ${GLFW_PREFIX}/build
        SOURCE_DIR ${GLFW_PREFIX}/repocontent
        INSTALL_DIR ${GLFW_PREFIX}/bin
        CMAKE_ARGS -DCMAKE_VERBOSE_MAKEFILE=TRUE -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)

set(glfw_INCLUDE_DIR ${GLFW_PREFIX}/bin/include)
set(glfw_LIBRARY_DIR ${GLFW_PREFIX}/bin/lib)
message(STATUS "glfw_INCLUDE_DIR ${glfw_INCLUDE_DIR}")
message(STATUS "glfw_LIBRARY_DIR ${glfw_LIBRARY_DIR}")



message (STATUS "-----------------------------------------------------------------------")
message (STATUS "GLM -------------------------------------------------------------------")

set(GLM_NAME glm)
set(GLM_PREFIX ${_3RDPARTY_ROOT}/${GLM_NAME})
ExternalProject_Add(
        glm
        GIT_REPOSITORY  https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
        BINARY_DIR      ${GLM_PREFIX}/build
        SOURCE_DIR      ${GLM_PREFIX}/repocontent
        INSTALL_DIR     ${GLM_PREFIX}/bin
        INSTALL_COMMAND ""
        CMAKE_ARGS -DBUILD_STATIC_LIBS=TRUE -DBUILD_SHARED_LIBS=FALSE -DGLM_TEST_ENABLE=OFF -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
)
set(glm_INCLUDE_DIR ${GLM_PREFIX}/repocontent)
set(glm_LIBRARY_DIR ${GLM_PREFIX}/build/glm)
message(STATUS "glm_INCLUDE_DIR ${glm_INCLUDE_DIR}")
message(STATUS "glm_LIBRARY_DIR ${glm_LIBRARY_DIR}")

#[[
message (STATUS "-----------------------------------------------------------------------")
message (STATUS "LEARNOPENGL -----------------------------------------------------------")
set(LEARNOPENGL_NAME learnopengl)
set(LEARNOPENGL_PREFIX ${_3RDPARTY_ROOT}/${LEARNOPENGL_NAME})

ExternalProject_Add(
        learnopengl
        GIT_REPOSITORY https://github.com/JoeyDeVries/LearnOpenGL.git
        GIT_TAG master
        BINARY_DIR ${LEARNOPENGL_PREFIX}/build
        SOURCE_DIR ${LEARNOPENGL_PREFIX}/repocontent
        INSTALL_DIR ${LEARNOPENGL_PREFIX}/bin
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""

)
set(learnopengl_REPOCNT_DIR ${LEARNOPENGL_PREFIX}/repocontent)
set(learnopengl_INCLUDE_DIR ${LEARNOPENGL_PREFIX}/repocontent/includes)
set(learnopengl_LIBRARY_DIR ${LEARNOPENGL_PREFIX}/bin/lib)
message(STATUS "learnopengl_INCLUDE_DIR ${learnopengl_INCLUDE_DIR}")
message(STATUS "learnopengl_LIBRARY_DIR ${learnopengl_LIBRARY_DIR}")]]

message(STATUS "All dependencies are in place now.")
message(STATUS "------------------------------------------------------------------------")


#[[message (STATUS "-----------------------------------------------------------------------")
message (STATUS "LINMATH ---------------------------------------------------------------")

set(LINMATH_NAME linmath)
set(LINMATH_PREFIX ${_3RDPARTY_ROOT}/${LINMATH_NAME})

#As this is a header only file we do not set empty strings for configure, build and install commands.
ExternalProject_Add(

        ${LINMATH_NAME}
        PREFIX              ${LINMATH_PREFIX}
        GIT_REPOSITORY      https://github.com/datenwolf/linmath.h.git
        GIT_TAG             master
        BINARY_DIR          ${LINMATH_PREFIX}/build
        SOURCE_DIR          ${LINMATH_PREFIX}/repcontent
        INSTALL_DIR         ${LINMATH_PREFIX}/bin
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""

)

set(linmath_INCLUDE_DIR ${LINMATH_PREFIX}/repcontent)
message(STATUS "linmath_INCLUDE_DIR: ${linmath_INCLUDE_DIR}")
]]

message (STATUS "DEPENDENCIES DONE -----------------------------------------------------")
message (STATUS "-----------------------------------------------------------------------")
