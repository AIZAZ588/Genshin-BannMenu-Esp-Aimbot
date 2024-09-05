# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/frameworks/esp-idf-v5.3/components/bootloader/subproject"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/tmp"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/src/bootloader-stamp"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/src"
  "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Devomech/05-09-2024/Keyboard Inputs/KeyboardInputs/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
