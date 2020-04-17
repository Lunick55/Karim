/*
This is an example of a file that will interface with Unity!
This defines the functions that will interface with Unity!
*/

#include "PluginTemplateExample.h"

ExampleManager* ExampleManager::instance = NULL;

float FunctionExample(float x, float y)
{
	return x + y;
}

void AddNumToManagerStringA(int newNum)
{
	ExampleManager::getInstance()->exA->AddToNum(newNum);
}
void AddNumToManagerStringB(int newNum)
{
	ExampleManager::getInstance()->exB->AddToNum(newNum);
}

int PrintManagerString()
{
	return ExampleManager::getInstance()->GetNum();
}

//ExampleManager Functions
ExampleManager::ExampleManager()
{
	exA = new ExampleClass();
	exB = new ExampleClass();
}

int ExampleManager::GetNum()
{
	int newNum = exA->num + exB->num;

	return newNum;
}

//Example Class Functions
void ExampleClass::AddToNum(int newNum)
{
	num += newNum;
}