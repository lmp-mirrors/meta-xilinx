inherit esw

ESW_COMPONENT_SRC = "/lib/sw_services/xilfpga/src/"
ESW_COMPONENT_NAME = "libxilfpga.a"

DEPENDS += "libxil xilsecure"
DEPENDS += "libxil ${@'xilmailbox' if d.getVar('MACHINE') == 'versal-generic' else ''}"

