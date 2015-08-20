SUBDIRS += \
    CustomDataSource \
    CustomItem \
    ItemModelDataSource \
    StringListDataSource \
    StringParameterDataSource \
    SimpleDemoApp \
    GraphDemo \
    SqlGraphDemo \
    ItemModelRelationDemo

contains(EXTENSIONS, designerlib): SUBDIRS += RunDesignerFromApp

TEMPLATE = subdirs
