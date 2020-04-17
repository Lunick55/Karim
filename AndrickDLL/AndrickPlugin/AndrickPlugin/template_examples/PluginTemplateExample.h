/*
This is an example of a file that will interface with Unity!
This uses the functions defined below to talk to Unity.
*/

#ifndef PLUGIN_TEMPLATE_H_
#define PLUGIN_TEMPLATE_H_

//Any file of this type needs to include lib.h
#include "../main/lib.h"
#include <string>

// If C++ is being used in the DLL
#ifdef __cplusplus
extern "C"
{
#else

// C code

#endif // End __cplusplus

// C++ code exposed to user program.
ANDRICK_PLUGIN_SYMBOL float FunctionExample(float x, float y);
ANDRICK_PLUGIN_SYMBOL void AddNumToManagerStringA(int newNum);
ANDRICK_PLUGIN_SYMBOL void AddNumToManagerStringB(int newNum);
ANDRICK_PLUGIN_SYMBOL int PrintManagerString();

#ifdef __cplusplus // Start __cplusplus
}
#else

// C code

#endif // End __cplusplus

// C++ Mode

#endif // End PLUGIN_TEMPLATE_H_

//Some example Classes
class ExampleClass
{
public:
	ExampleClass() {};

	float AddNumbers(float x, float y) { return (x + y); };

	int getNumI() { return 5; };
	float getNumF() { return 5.5f; };

	void AddToNum(int newNum);

	int num = 0;
};

class ExampleManager
{
public:
	static ExampleManager* getInstance()
	{
		if (!instance)
			instance = new ExampleManager();
		return instance;
	}

	ExampleClass* exA;
	ExampleClass* exB;

	int GetNum();

private:
	ExampleManager();

	static ExampleManager* instance;

};