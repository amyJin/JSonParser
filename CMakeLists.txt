CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT(JSonParser)

# Check if the boost library has been set
SET ( BOOST $ENV{BOOST_DIR} )
IF (NOT BOOST)
    MESSAGE ("Boost library has not been set")
ENDIF (NOT BOOST)

# Define the boost envrionment so we don't get system libraries
set ( BOOST_ROOT       $ENV{BOOST_DIR} )
set ( BOOST_INCLUDEDIR $ENV{BOOST_INC} )
set ( BOOST_LIBRARYDIR $ENV{BOOST_LIB} )

# Boost version
SET ( BOOST_VER1  1  )
SET ( BOOST_VER2  42 )
SET ( BOOST_VER3  0  )

FIND_PACKAGE ( Boost ${BOOST_VER1}.${BOOST_VER2} REQUIRED ) 

# Project include directory
INCLUDE_DIRECTORIES (
    ${JSonParser_SOURCE_DIR}/interface
    ${Boost_INCLUDE_DIR}
    )

# Add source files in the src/ diretory
INCLUDE (src/CMakeLists.txt)

FOREACH (FILE ${FILES})
    SET (srcFiles ${srcFiles} src/${FILE})
ENDFOREACH (FILE)

ADD_LIBRARY (JSonParser SHARED ${srcFiles})  

SET_TARGET_PROPERTIES (JSonParser
    PROPERTIES OUTPUT_NAME jsoncpp
    )

# Check if the install prefix is set
IF (NOT CMAKE_INSTALL_PREFIX)
    SET ( CMAKE_INSTALL_PREFIX
        ${JSonParser_SOURCE_DIR}/install
        )
ENDIF(NOT CMAKE_INSTALL_PREFIX)


# Install files
SET ( CMAKE_INSTALL_PREFIX 
    ${JSonParser_BINARY_DIR}/install
    )

FILE (GLOB includeFiles
    ${JSonParser_SOURCE_DIR}/interface/*.h
    )

LIST (APPEND srcFiles
    src/CMakeLists.txt
    )

FILE (GLOB cmakeFiles
    ${JSonParser_SOURCE_DIR}/CMakeLists.txt
    )

INSTALL (FILES ${includeFiles}
    DESTINATION include/
    )

INSTALL (FILES ${includeFiles}
    DESTINATION src/JSONParser/interface
    )

INSTALL (FILES ${srcFiles}
    DESTINATION src/JSONParser/src
    )

INSTALL (FILES ${cmakeFiles}
    DESTINATION src/JSONParser
    )

INSTALL (TARGETS JSonParser 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    ) 

# Add subdirectories
ADD_SUBDIRECTORY (test)
