cmake_minimum_required(VERSION 3.0)



STRING(APPEND CMAKE_C_FLAGS " -DGITREPOINFO_BRANCH='\"${gitrepoinfo_branch}\"'  ")
STRING(APPEND CMAKE_C_FLAGS " -DGITREPOINFO_SHORTSHA='\"${gitrepoinfo_shortsha}\"'  ")

include_directories(src)

add_subdirectory(test)



