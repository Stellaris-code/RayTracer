file(GLOB_RECURSE source_files "*.cpp")
file(GLOB_RECURSE header_files "../include/*.hpp" "../include/*.tpp")

add_executable(${PROJECT_NAME} ${header_files} ${source_files})

find_package(SFML 2 REQUIRED system graphics window)
include_directories(${SFML_INCLUDE_DIR})
find_package(Thor REQUIRED)
include_directories(${Thor_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${THOR_LIBRARY})

if (USE_CLANG_TIDY)
    set(DO_CLANG_TIDY "clang-tidy" "-checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*,cppcoreguidelines-*,llvm-include-order")
    set_target_properties(
      ${PROJECT_NAME} PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
endif()
