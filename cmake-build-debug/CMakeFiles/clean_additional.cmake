# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PasswordManagerCppQT_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PasswordManagerCppQT_autogen.dir\\ParseCache.txt"
  "PasswordManagerCppQT_autogen"
  )
endif()
