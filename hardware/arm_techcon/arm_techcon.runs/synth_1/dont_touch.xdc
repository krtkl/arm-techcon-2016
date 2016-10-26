# This file is automatically generated.
# It contains project source information necessary for synthesis and implementation.

# XDC: new/snickerdoodle_constraints.xdc

# Block Designs: bd/base_block_design/base_block_design.bd
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design || ORIG_REF_NAME==base_block_design}]

# IP: bd/base_block_design/ip/base_block_design_processing_system7_0_0/base_block_design_processing_system7_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_processing_system7_0_0 || ORIG_REF_NAME==base_block_design_processing_system7_0_0}]

# IP: bd/base_block_design/ip/base_block_design_axi_gpio_0_0/base_block_design_axi_gpio_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_axi_gpio_0_0 || ORIG_REF_NAME==base_block_design_axi_gpio_0_0}]

# IP: bd/base_block_design/ip/base_block_design_processing_system7_0_axi_periph_0/base_block_design_processing_system7_0_axi_periph_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_processing_system7_0_axi_periph_0 || ORIG_REF_NAME==base_block_design_processing_system7_0_axi_periph_0}]

# IP: bd/base_block_design/ip/base_block_design_rst_processing_system7_0_50M_0/base_block_design_rst_processing_system7_0_50M_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_rst_processing_system7_0_50M_0 || ORIG_REF_NAME==base_block_design_rst_processing_system7_0_50M_0}]

# IP: bd/base_block_design/ip/base_block_design_axi_timer_0_0/base_block_design_axi_timer_0_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_axi_timer_0_0 || ORIG_REF_NAME==base_block_design_axi_timer_0_0}]

# IP: bd/base_block_design/ip/base_block_design_xbar_0/base_block_design_xbar_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_xbar_0 || ORIG_REF_NAME==base_block_design_xbar_0}]

# IP: bd/base_block_design/ip/base_block_design_auto_pc_0/base_block_design_auto_pc_0.xci
set_property DONT_TOUCH TRUE [get_cells -hier -filter {REF_NAME==base_block_design_auto_pc_0 || ORIG_REF_NAME==base_block_design_auto_pc_0}]

# XDC: bd/base_block_design/ip/base_block_design_processing_system7_0_0/base_block_design_processing_system7_0_0.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_processing_system7_0_0 || ORIG_REF_NAME==base_block_design_processing_system7_0_0}] {/inst }]/inst ]]

# XDC: bd/base_block_design/ip/base_block_design_axi_gpio_0_0/base_block_design_axi_gpio_0_0_board.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_axi_gpio_0_0 || ORIG_REF_NAME==base_block_design_axi_gpio_0_0}] {/U0 }]/U0 ]]

# XDC: bd/base_block_design/ip/base_block_design_axi_gpio_0_0/base_block_design_axi_gpio_0_0_ooc.xdc

# XDC: bd/base_block_design/ip/base_block_design_axi_gpio_0_0/base_block_design_axi_gpio_0_0.xdc
#dup# set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_axi_gpio_0_0 || ORIG_REF_NAME==base_block_design_axi_gpio_0_0}] {/U0 }]/U0 ]]

# XDC: bd/base_block_design/ip/base_block_design_rst_processing_system7_0_50M_0/base_block_design_rst_processing_system7_0_50M_0_board.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_rst_processing_system7_0_50M_0 || ORIG_REF_NAME==base_block_design_rst_processing_system7_0_50M_0}] {/U0 }]/U0 ]]

# XDC: bd/base_block_design/ip/base_block_design_rst_processing_system7_0_50M_0/base_block_design_rst_processing_system7_0_50M_0.xdc
#dup# set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_rst_processing_system7_0_50M_0 || ORIG_REF_NAME==base_block_design_rst_processing_system7_0_50M_0}] {/U0 }]/U0 ]]

# XDC: bd/base_block_design/ip/base_block_design_rst_processing_system7_0_50M_0/base_block_design_rst_processing_system7_0_50M_0_ooc.xdc

# XDC: bd/base_block_design/ip/base_block_design_axi_timer_0_0/base_block_design_axi_timer_0_0.xdc
set_property DONT_TOUCH TRUE [get_cells [split [join [get_cells -hier -filter {REF_NAME==base_block_design_axi_timer_0_0 || ORIG_REF_NAME==base_block_design_axi_timer_0_0}] {/U0 }]/U0 ]]

# XDC: bd/base_block_design/ip/base_block_design_axi_timer_0_0/base_block_design_axi_timer_0_0_ooc.xdc

# XDC: bd/base_block_design/ip/base_block_design_xbar_0/base_block_design_xbar_0_ooc.xdc

# XDC: bd/base_block_design/ip/base_block_design_auto_pc_0/base_block_design_auto_pc_0_ooc.xdc

# XDC: bd/base_block_design/base_block_design_ooc.xdc
