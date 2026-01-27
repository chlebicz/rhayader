# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/app/_deps/catch2-src"
  "/app/_deps/catch2-build"
  "/app/_deps/catch2-subbuild/catch2-populate-prefix"
  "/app/_deps/catch2-subbuild/catch2-populate-prefix/tmp"
  "/app/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
  "/app/_deps/catch2-subbuild/catch2-populate-prefix/src"
  "/app/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/app/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/app/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
