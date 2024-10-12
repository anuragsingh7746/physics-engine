message(STATUS "Fetching SFML...")

#no need to build audio and network modules rightnow
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)

FetchContent_MakeAvailable(sfml)



