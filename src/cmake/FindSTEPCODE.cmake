# - Try to find the STEPCode library
#
#   TODO: Use find_path and find_library

if(VSP_USE_SYSTEM_STEPCODE)
    set( STEPCODE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")
ENDIF()

IF(NOT WIN32)
    IF(NOT VSP_USE_SYSTEM_STEPCODE)
        set( STEPCODE_LIBRARIES
        ${STEPCODE_INSTALL_DIR}/lib/libsdai_ap203-static.a
        ${STEPCODE_INSTALL_DIR}/lib/libstepeditor-static.a
        ${STEPCODE_INSTALL_DIR}/lib/libstepcore-static.a
        ${STEPCODE_INSTALL_DIR}/lib/libstepdai-static.a
        ${STEPCODE_INSTALL_DIR}/lib/libsteputils-static.a
        # ${STEPCODE_INSTALL_DIR}/lib/libbase.a removed in 0.8.2
        )
    ELSE()
        set( STEPCODE_LIBRARIES
        ${STEPCODE_INSTALL_DIR}/lib64/libsdai_ap203.so.0
        ${STEPCODE_INSTALL_DIR}/lib64/libstepeditor.so.0
        ${STEPCODE_INSTALL_DIR}/lib64/libstepcore.so.0
        ${STEPCODE_INSTALL_DIR}/lib64/libstepdai.so.0
        ${STEPCODE_INSTALL_DIR}/lib64/libsteputils.so.0
        # ${STEPCODE_INSTALL_DIR}/lib/libbase.a removed in 0.8.2
        )
    ENDIF()
ELSE()
    # Necessary for static libs in STEPCode
    add_compile_definitions(SC_STATIC)
    set( STEPCODE_LIBRARIES
    ${STEPCODE_INSTALL_DIR}/lib/express-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/libexppp-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/sdai_ap203-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/stepeditor-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/stepcore-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/stepdai-static.lib
    ${STEPCODE_INSTALL_DIR}/lib/steputils-static.lib
    # ${STEPCODE_INSTALL_DIR}/lib/libbase.lib removed in 0.8.2
    shlwapi.lib )
ENDIF()

#${STEPCODE_INSTALL_DIR}/lib/libbase-static.a

set( STEPCODE_INCLUDE_DIR
${STEPCODE_INSTALL_DIR}/include/stepcode
${STEPCODE_INSTALL_DIR}/include/stepcode/base
${STEPCODE_INSTALL_DIR}/include/stepcode/clstepcore
${STEPCODE_INSTALL_DIR}/include/stepcode/cldai
${STEPCODE_INSTALL_DIR}/include/stepcode/clutils
${STEPCODE_INSTALL_DIR}/include/stepcode/cleditor
${STEPCODE_INSTALL_DIR}/include/schemas/sdai_ap203 )

# MESSAGE( STATUS "STEPCODE_INCLUDE_DIR: " ${STEPCODE_INCLUDE_DIR} )
# MESSAGE( STATUS "STEPCODE_LIBRARIES: " ${STEPCODE_LIBRARIES} )
