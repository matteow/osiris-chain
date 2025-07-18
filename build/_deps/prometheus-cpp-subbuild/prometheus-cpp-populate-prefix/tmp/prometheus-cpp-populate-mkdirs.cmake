# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-src"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-build"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/tmp"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/src/prometheus-cpp-populate-stamp"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/src"
  "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/src/prometheus-cpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/src/prometheus-cpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mttw/Desktop/dev/osiris_chaind/project/osiris-core/build/_deps/prometheus-cpp-subbuild/prometheus-cpp-populate-prefix/src/prometheus-cpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
