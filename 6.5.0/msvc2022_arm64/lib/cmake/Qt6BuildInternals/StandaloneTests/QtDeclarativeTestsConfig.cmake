# TODO: Ideally this should look for each Qt module separately, with each module's specific version,
# bypassing the Qt6 Config file, aka find_package(Qt6SpecificFoo) repated x times. But it's not
# critical.
find_package(Qt6 6.5.0
             REQUIRED COMPONENTS QmlTypeRegistrarPrivate QmlIntegration Qml QmlModels QmlCore QmlWorkerScript QmlLocalStorage QmlXmlListModel Quick QuickLayouts QuickTest QuickTestUtilsPrivate QuickParticlesPrivate QuickEffectsPrivate QuickShapesPrivate QuickWidgets QuickTemplates2 QuickControls2Impl QuickControls2 QuickDialogs2Utils QuickDialogs2QuickImpl QuickDialogs2 QuickControlsTestUtilsPrivate LabsSettings LabsQmlModels LabsFolderListModel LabsAnimation LabsWavefrontMesh LabsSharedImage QmlCompilerPrivate QmlDomPrivate PacketProtocolPrivate QmlDebugPrivate)
