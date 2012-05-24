file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp *.cc)

GroupSourcesByFilesystem("${SOURCES}")

add_executable(readLOD
    ${SOURCES}
)

target_link_libraries(readLOD
    meshLib
)
