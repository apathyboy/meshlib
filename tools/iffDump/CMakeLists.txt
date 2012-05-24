file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp *.cc)

GroupSourcesByFilesystem("${SOURCES}")

add_executable(iffDump
    ${SOURCES}
)

target_link_libraries(iffDump
    meshLib
)
