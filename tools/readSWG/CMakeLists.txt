file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp *.cc)

GroupSourcesByFilesystem("${SOURCES}")

add_executable(readSWG
    ${SOURCES}
)

target_link_libraries(readSWG
    meshLib
)
