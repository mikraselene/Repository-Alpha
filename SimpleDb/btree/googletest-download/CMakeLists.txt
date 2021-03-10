cmake_minimum_required(VERSION 3.15)
project(b_tree_v2_0)

include(ExternalProject)
ExternalProject_Add(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        SOURCE_DIR "/Users/mikraselene/statio-spatialis/code/Repository-Alpha/SimpleDb/btree/googletest-src"
        BINARY_DIR "/Users/mikraselene/statio-spatialis/code/Repository-Alpha/SimpleDb/btree/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )
