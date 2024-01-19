
if(BUILD_TESTING)
  include(FetchContent)
  FetchContent_Declare(
    googletest
#   URL https://github.com/google/googletest/archive/c875c4e2249ec124c24f72141b3780c22256fd44.zip
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.0
  # URL_HASH  SHA256=${FILE_HASH}
  ) 
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif(BUILD_TESTING)

