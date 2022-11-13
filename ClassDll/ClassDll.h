#pragma once

#ifndef _DLLCLASS_H
#define _DLLCLASS_H

#ifdef DLLCLASS_EXPORTS
#define EXT_CLASS _declspec(dllexport) // DLL
#else
#define EXT_CLASS _declspec(dllimport) // ʹ����
#endif

class EXT_CLASS CMath {
public:
	int Add(int add1, int add2);
	int Sub(int sub1, int sub2);
};

#endif