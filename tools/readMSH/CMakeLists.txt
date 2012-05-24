file(GLOB_RECURSE SOURCES *.h *.hpp *.cpp *.cc)

GroupSourcesByFilesystem("${SOURCES}")

add_executable(readMSH
    ${SOURCES}
)

target_link_libraries(readMSH
    meshLib
)
