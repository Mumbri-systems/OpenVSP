# - Try to find the STEPCode library using find_path and find_library

set( STEPCODE_SEARCH_HINTS ${STEPCODE_INSTALL_DIR} )

find_path( STEPCODE_INCLUDE_DIR
    NAMES stepcore/stepcore.h  # Check for a representative header
    HINTS ${STEPCODE_SEARCH_HINTS}
    PATH_SUFFIXES include/stepcode include
    DOC "STEPCode include directory"
)

set( STEPCODE_INCLUDE_DIRS
    ${STEPCODE_INCLUDE_DIR}
    ${STEPCODE_INCLUDE_DIR}/base
    ${STEPCODE_INCLUDE_DIR}/clstepcore
    ${STEPCODE_INCLUDE_DIR}/cldai
    ${STEPCODE_INCLUDE_DIR}/clutils
    ${STEPCODE_INCLUDE_DIR}/cleditor
    ${STEPCODE_INSTALL_DIR}/include/schemas/sdai_ap203
)

if(NOT WIN32)
    # Unix/Linux/macOS Static Libraries
    find_library( STEPCODE_SDAI_AP203_LIB
        NAMES libsdai_ap203.a libsdai_ap203-static.a sdai_ap203 sdai_ap203-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EDITOR_LIB
        NAMES libstepeditor.a libstepeditor-static.a stepeditor stepeditor-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_CORE_LIB
        NAMES libstepcore.a libstepcore-static.a stepcore stepcore-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_DAI_LIB
        NAMES libstepdai.a libstepdai-static.a stepdai stepdai-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_UTILS_LIB
        NAMES libsteputils.a libsteputils-static.a steputils steputils-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )

    set( STEPCODE_LIBRARIES
        ${STEPCODE_SDAI_AP203_LIB}
        ${STEPCODE_EDITOR_LIB}
        ${STEPCODE_CORE_LIB}
        ${STEPCODE_DAI_LIB}
        ${STEPCODE_UTILS_LIB}
    )

else()
    # Windows Static Libraries
    # NOTE: Windows Shared Libraries not currently supported
    add_compile_definitions(SC_STATIC)

    find_library( STEPCODE_EXPRESS_LIB
        NAMES express-static.lib express-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EXPPP_LIB
        NAMES libexppp-static.lib exppp-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_SDAI_AP203_LIB
        NAMES sdai_ap203-static.lib sdai_ap203-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EDITOR_LIB
        NAMES stepeditor-static.lib stepeditor-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_CORE_LIB
        NAMES stepcore-static.lib stepcore-static
        HINT# - Try to find the STEPCode library using find_path and find_library

set( STEPCODE_SEARCH_HINTS ${STEPCODE_INSTALL_DIR} )

find_path( STEPCODE_INCLUDE_DIR
    NAMES stepcore/stepcore.h  # Check for a representative header
    HINTS ${STEPCODE_SEARCH_HINTS}
    PATH_SUFFIXES include/stepcode include
    DOC "STEPCode include directory"
)

set( STEPCODE_INCLUDE_DIRS
    ${STEPCODE_INCLUDE_DIR}
    ${STEPCODE_INCLUDE_DIR}/base
    ${STEPCODE_INCLUDE_DIR}/clstepcore
    ${STEPCODE_INCLUDE_DIR}/cldai
    ${STEPCODE_INCLUDE_DIR}/clutils
    ${STEPCODE_INCLUDE_DIR}/cleditor
    ${STEPCODE_INSTALL_DIR}/include/schemas/sdai_ap203
)

if(NOT WIN32)
    # Unix/Linux/macOS Static Libraries
    find_library( STEPCODE_SDAI_AP203_LIB
        NAMES libsdai_ap203.a libsdai_ap203-static.a sdai_ap203 sdai_ap203-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EDITOR_LIB
        NAMES libstepeditor.a libstepeditor-static.a stepeditor stepeditor-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_CORE_LIB
        NAMES libstepcore.a libstepcore-static.a stepcore stepcore-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_DAI_LIB
        NAMES libstepdai.a libstepdai-static.a stepdai stepdai-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_UTILS_LIB
        NAMES libsteputils.a libsteputils-static.a steputils steputils-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )

    set( STEPCODE_LIBRARIES
        ${STEPCODE_SDAI_AP203_LIB}
        ${STEPCODE_EDITOR_LIB}
        ${STEPCODE_CORE_LIB}
        ${STEPCODE_DAI_LIB}
        ${STEPCODE_UTILS_LIB}
    )

else()
    # Windows Static Libraries
    # NOTE: Windows Shared Libraries not currently supported
    add_compile_definitions(SC_STATIC)

    find_library( STEPCODE_EXPRESS_LIB
        NAMES express-static.lib express-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EXPPP_LIB
        NAMES libexppp-static.lib exppp-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_SDAI_AP203_LIB
        NAMES sdai_ap203-static.lib sdai_ap203-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_EDITOR_LIB
        NAMES stepeditor-static.lib stepeditor-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_CORE_LIB
        NAMES stepcore-static.lib stepcore-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_DAI_LIB
        NAMES stepdai-static.lib stepdai-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )
    find_library( STEPCODE_UTILS_LIB
        NAMES steputils-static.lib steputils-static
        HINTS ${STEPCODE_SEARCH_HINTS}
        PATH_SUFFIXES lib
    )

    # System library required on Windows
    set( STEPCODE_SYSTEM_LIBS shlwapi.lib )

    set( STEPCODE_LIBRARIES
        ${STEPCODE_EXPRESS_LIB}
        ${STEPCODE_EXPPP_LIB}
        ${STEPCODE_SDAI_AP203_LIB}
        ${STEPCODE_EDITOR_LIB}
        ${STEPCODE_CORE_LIB}
        ${STEPCODE_DAI_LIB}
        ${STEPCODE_UTILS_LIB}
        ${STEPCODE_SYSTEM_LIBS}
    )
endif()

# --- Validation ---
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(STEPCode
    REQUIRED_VARS STEPCODE_LIBRARIES STEPCODE_INCLUDE_DIR
)

