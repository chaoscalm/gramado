/*
 version.h
 Product configuration.
 Created by Fred Nora.
*/

#ifndef __PRODUCT_VERSION_H
#define __PRODUCT_VERSION_H  1

// Current build number
// Updated by the builder
#define __CURRENT_BUILD_NUMBER    337

// Version
#define VERSION_MAJOR    1
#define VERSION_MINOR    1
#define VERSION_BUILD    __CURRENT_BUILD_NUMBER
// Version word
// Two bytes.
#define VERSION_WORD    0x0101
// Strings
#define VERSION_STRING    "1.1"
#define BUILD_STRING      "337"
#define BUILD_CODENAME_STRING  "Amazing"
#define RELEASE_STRING    PRODUCT_TYPE_STRING

#endif



