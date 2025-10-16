add_library(ym3438-intf INTERFACE)
target_include_directories(
  ym3438-intf
  INTERFACE
  .
  device-config-intf
  micro-support-intf
)


add_library(ym3438 OBJECT)
target_sources(
  ym3438
  PRIVATE
  ym3438.c
)

target_link_libraries(
  ym3438
  PRIVATE
  device-config-intf
  micro-support-intf
)
