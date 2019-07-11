#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RDV_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RDV_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RDV_EXPORTS
#define RDV_API __declspec(dllexport)
#define RDV_TEMPLATE_API __declspec(dllexport)
#else
#define RDV_API __declspec(dllimport)
#define RDV_TEMPLATE_API
#endif