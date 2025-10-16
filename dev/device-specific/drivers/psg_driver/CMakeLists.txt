add_library(psg-intf INTERFACE)
target_include_directories(
  psg-intf
  INTERFACE
  .
  device-config-intf
  micro-support-intf
)


add_library(psg OBJECT)
target_sources(
  psg
  PRIVATE
  psg.c
)

target_link_libraries(
  psg
  PRIVATE
  device-config-intf
  micro-support-intf
)
