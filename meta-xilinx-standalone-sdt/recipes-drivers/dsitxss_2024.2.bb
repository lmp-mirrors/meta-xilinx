
inherit features_check

REQUIRED_MACHINE_FEATURES = "dsitxss"

inherit esw python3native

DEPENDS += "xilstandalone dsi dphy"

ESW_COMPONENT_SRC = "/XilinxProcessorIPLib/drivers/dsitxss/src/"
ESW_COMPONENT_NAME = "libdsitxss.a"

addtask do_generate_driver_data before do_configure after do_prepare_recipe_sysroot
do_prepare_recipe_sysroot[rdeptask] = "do_unpack"