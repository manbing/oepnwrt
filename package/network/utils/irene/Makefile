include $(TOPDIR)/rules.mk

PKG_NAME:=irene
PKG_VERSION:=1.0.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

TARGET_CFLAGS += -ggdb3

TARGET_LDFLAGS +=

## Package
define Package/irene
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Irene network shark
endef

define Package/irene/description
  It's irene description
endef

define Package/irene/install
	@echo "irene isntall"
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME) $(1)/bin/
endef

## Build
define Build/Prepare
	@echo "irene build prepare"
	$(CP) -rf ./src/* $(PKG_BUILD_DIR)
endef

define Build/Compile
	@echo "irene compile"
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) $(PKG_BUILD_DIR)/*.c -o $(PKG_BUILD_DIR)/$(PKG_NAME) -I$(PKG_BUILD_DIR)/include/
endef

$(eval $(call BuildPackage,irene))
