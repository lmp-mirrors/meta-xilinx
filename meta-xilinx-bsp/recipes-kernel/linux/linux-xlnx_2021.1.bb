LINUX_VERSION = "5.10"
KBRANCH="master"
SRCREV = "5db91ec53100477ab552583e5629f91ac02f998e"

KCONF_AUDIT_LEVEL="0"

include linux-xlnx.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
