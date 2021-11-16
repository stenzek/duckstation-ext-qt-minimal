QT.waylandclient.VERSION = 6.2.0
QT.waylandclient.name = QtWaylandClient
QT.waylandclient.module = Qt6WaylandClient
QT.waylandclient.libs = $$QT_MODULE_LIB_BASE
QT.waylandclient.ldflags = 
QT.waylandclient.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtWaylandClient
QT.waylandclient.frameworks = 
QT.waylandclient.bins = $$QT_MODULE_BIN_BASE
QT.waylandclient.plugin_types = wayland-graphics-integration-client wayland-inputdevice-integration wayland-decoration-client wayland-shell-integration
QT.waylandclient.depends =  core gui
QT.waylandclient.uses = wayland-client wayland-cursor
QT.waylandclient.module_config = v2
QT.waylandclient.DEFINES = QT_WAYLANDCLIENT_LIB
QT.waylandclient.enabled_features = 
QT.waylandclient.disabled_features = 
QT_CONFIG += 
QT_MODULES += waylandclient

