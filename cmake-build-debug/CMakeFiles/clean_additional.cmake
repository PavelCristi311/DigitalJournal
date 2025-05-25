# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DigitalJournal_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DigitalJournal_autogen.dir/ParseCache.txt"
  "DigitalJournal_autogen"
  )
endif()
