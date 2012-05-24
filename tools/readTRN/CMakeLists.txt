file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp *.cc)

GroupSourcesByFilesystem("${SOURCES}")

add_executable(readTRN
    ${SOURCES}
)

target_link_libraries(readTRN
    meshLib
)
