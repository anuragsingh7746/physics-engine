include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML"
    GIT_TAG 69ea0cd #2.6.1
)

add_subdirectory(sfml)

