list(APPEND MAIN_FILE_LOCATION .)

file(GLOB MAIN_FILES ${MAIN_FILE_LOCATION}/*.cpp)
foreach (MAIN ${MAIN_FILES})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" NAME ${MAIN})
    add_executable (${NAME} ${MAIN})
endforeach ()