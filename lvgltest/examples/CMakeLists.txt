# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_examples_SRCS 变量
aux_source_directory(./src DIR_examples_SRCS)

include_directories(../lib/Config)
include_directories(../lib/LCD)
include_directories(../lib/QMI8658)
include_directories(../lib/Touch)
include_directories(../lib/lvgl)
include_directories(./inc)


# 生成链接库
add_library(examples ${DIR_examples_SRCS})
target_link_libraries(examples PUBLIC Config LCD Touch QMI8658 LVGL hardware_clocks hardware_rtc hardware_adc hardware_dma hardware_spi)
