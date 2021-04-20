set(TGENBASE_VERSION 64ccb8622cbdc20bd930394446c394316c061e21) # commit hash
set(TGENBASE_SRC_URL "https://git.cbm.gsi.de/TGenBase/CxxClient.git")
set(TGENBASE_DESTDIR "${CMAKE_BINARY_DIR}/external/TGENBASE-prefix")
set(TGENBASE_LIBNAME "${CMAKE_SHARED_LIBRARY_PREFIX}TGenBase${CMAKE_SHARED_LIBRARY_SUFFIX}")

download_project_if_needed(PROJECT         TGenBase_source
                           GIT_REPOSITORY  ${TGENBASE_SRC_URL}
                           GIT_TAG         ${TGENBASE_VERSION}
                           SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/TGenBase
                           TEST_FILE       CMakeLists.txt
                          )

If(ProjectUpdated)
  File(REMOVE_RECURSE ${TGENBASE_DESTDIR})
  Message("TGenBase source directory was changed so build directory was deleted")
EndIf()

ExternalProject_Add(TGENBASE
  BUILD_IN_SOURCE 0
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/TGenBase
  BUILD_BYPRODUCTS ${TGENBASE_LIBRARY}
  LOG_DOWNLOAD 1 LOG_CONFIGURE 1 LOG_BUILD 1 LOG_INSTALL 1
  CMAKE_ARGS -G ${CMAKE_GENERATOR}
             -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
             -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
             -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
             -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
             -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
             -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON
  INSTALL_COMMAND  ${CMAKE_COMMAND} --build . --target install
)

add_library(TGenBase SHARED IMPORTED)
set_target_properties(TGenBase PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/lib)
add_dependencies(TGenBase TGENBASE)

set(TGENBASE_LIB_DIR ${CMAKE_BINARY_DIR}/lib CACHE STRING "TGenBase library directory")
set(TGENBASE_LIBRARIES ${TGENBASE_LIBNAME} CACHE STRING "TGenBase libraries")
set(TGENBASE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include" CACHE STRING "TGenBase include directory")
set(TGENBASE_FOUND TRUE CACHE BOOL "TGenBase found")
