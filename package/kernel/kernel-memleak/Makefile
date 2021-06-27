include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=kernel-memleak
PKG_VERSION:=0.0.1
PKG_LICENSE:=GPLv2
PKG_RELESE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
#include $(INCLUDE_DIR)/cmake.mk

## KernelPackage
define KernelPackage/kernel-memleak
  SUBMENU:=Other modules
  TITLE:=irene kernel packages
  DEPENDS:=
  KCONFIG:=CONFIG_DEBUG_KMEMLEAK
  FILES:=$(PKG_BUILD_DIR)/kernel-memleak.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoLoad,50,kernel-memleak)
endef

define KernelPackage/kernel-memleak/install
	$(INSTALL_DIR) $(1)/lib/modules/$(LINUX_VERSION)
endef

## Build
# define Build/Prepare \
	$(INSTALL_DIR) $(PKG_BUILD_DIR) \
	$(CP) ./src/* $(PKG_BUILD_DIR) \
endef

EXTRA_KCONFIG:= \
	CONFIG_KMEMLEAK_TEST=m

EXTRA_CFLAGS:= \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=m,%,$(filter %=m,$(EXTRA_KCONFIG)))) \
	$(patsubst CONFIG_%, -DCONFIG_%=1, $(patsubst %=y,%,$(filter %=y,$(EXTRA_KCONFIG)))) \

MAKE_OPTS:= \
	$(KERNEL_MAKE_FLAGS) \
	M="$(PKG_BUILD_DIR)" \
	EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
	$(EXTRA_KCONFIG)

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/kernel_memleak
	$(CP) $(PKG_BUILD_DIR)/*.h $(1)/usr/include/kernel_memleak/
endef

$(eval $(call KernelPackage,kernel-memleak))
