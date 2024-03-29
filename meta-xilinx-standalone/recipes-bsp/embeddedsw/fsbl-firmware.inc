DESCRIPTION = "First Stage Bootloader"

inherit xlnx-embeddedsw deploy

COMPATIBLE_HOST = ".*-(elf|eabi)"
COMPATIBLE_MACHINE = "none"
COMPATIBLE_MACHINE_zynq = ".*"
COMPATIBLE_MACHINE_zynqmp = ".*"

# Specify a default in case boardvariant isn't available
BOARDVARIANT_ARCH ??= "${MACHINE_ARCH}"
PACKAGE_ARCH = "${BOARDVARIANT_ARCH}"

S = "${WORKDIR}/git"

APP_DIR = "undefined"
APP_DIR_zynq = "zynq_fsbl"
APP_DIR_zynqmp = "zynqmp_fsbl"

B = "${S}/lib/sw_apps/${APP_DIR}/src"

# The makefile does not handle parallelization
PARALLEL_MAKE = "-j1"

do_configure() {
    :
}

COMPILER = "${CC}"
COMPILER_FLAGS = "-O2 -c"
EXTRA_COMPILER_FLAGS = "-g -Wall -Wextra -Os -flto -ffat-lto-objects"
ARCHIVER = "${AR}"

BSP_DIR ?= "${B}/../misc/undefined"
BSP_DIR_zynq   ?= "${B}/../misc/zynq_fsbl_bsp"
BSP_DIR_zynqmp ?= "${B}/../misc/zynqmp_fsbl_bsp"
BSP_TARGETS_DIR ?= "${BSP_DIR}/psu_cortexa53_0/libsrc"

# FSBL components expect AS to be CC.
AS = "${CC}"
LINKER = "${CC}"
DUMP = "${OBJDUMP} -xSD"

def bsp_make_vars(d):
    s = ["COMPILER", "CC", "COMPILER_FLAGS", "EXTRA_COMPILER_FLAGS", "ARCHIVER", "AR", "AS", "LINKER", "DUMP"]
    return " ".join(["\"%s=%s\"" % (v, d.getVar(v)) for v in s])

EXTRA_OEMAKE = "${@bsp_make_vars(d)}"

ARM_INSTRUCTION_SET_eabi_arm = "arm"
do_compile() {
    oe_runmake
}

do_install() {
    :
}

PACKAGES = ""

# This is the default in most BSPs.  A MACHINE.conf can override this!
FSBL_IMAGE_NAME ??= "fsbl"

inherit image-artifact-names

FSBL_BASE_NAME ?= "${FSBL_IMAGE_NAME}-${PKGE}-${PKGV}-${PKGR}-${MACHINE}${IMAGE_VERSION_SUFFIX}"

ESW_COMPONENT ??= "fsbl.elf"

do_deploy() {
    install -Dm 0644 ${B}/${ESW_COMPONENT} ${DEPLOYDIR}/${FSBL_BASE_NAME}.elf
    ln -sf ${FSBL_BASE_NAME}.elf ${DEPLOYDIR}/${FSBL_IMAGE_NAME}.elf
}

addtask deploy before do_build after do_install
