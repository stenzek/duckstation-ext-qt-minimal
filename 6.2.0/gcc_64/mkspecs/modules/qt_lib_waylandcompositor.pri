QT.waylandcompositor.VERSION = 6.2.0
QT.waylandcompositor.name = QtWaylandCompositor
QT.waylandcompositor.module = Qt6WaylandCompositor
QT.waylandcompositor.libs = $$QT_MODULE_LIB_BASE
QT.waylandcompositor.ldflags = 
QT.waylandcompositor.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtWaylandCompositor
QT.waylandcompositor.frameworks = 
QT.waylandcompositor.bins = $$QT_MODULE_BIN_BASE
QT.waylandcompositor.plugin_types = wayland-graphics-integration-server wayland-hardware-layer-integration
QT.waylandcompositor.depends =  core gui opengl quick qml quick
QT.waylandcompositor.uses = wayland-server
QT.waylandcompositor.module_config = v2
QT.waylandcompositor.DEFINES = QT_WAYLANDCOMPOSITOR_LIB
QT.waylandcompositor.enabled_features = wayland-compositor-quick
QT.waylandcompositor.disabled_features = 
QT_CONFIG += wayland-compositor-quick
QT_MODULES += waylandcompositor

