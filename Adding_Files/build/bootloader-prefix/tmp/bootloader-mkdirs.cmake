# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/aizaz/esp/esp-idf/components/bootloader/subproject"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/tmp"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/src/bootloader-stamp"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/src"
  "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/aizaz/Downloads/Devomech/learning/esp32/Adding_Files/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
