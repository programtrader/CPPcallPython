// CPPcallPython.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Python.h"

int main()
{
	//初始化python
	//在使用python系统前，必须使用Py_Initialize对其
	//进行初始化。它会载入python的内奸模块并添加系统
	//路径模块搜索路径中。这个函数没有返回值，检查系统
	//是否初始化成功需要使用Py_IsInitialized.
	//添加C:\Program Files\Python36\include到系统路径中
	Py_Initialize();
	if (!Py_IsInitialized()) {
	}
	//添加当前路径
	//把输入的字符串作为python代码直接运行，返回0
	//表示成功，-1表示有错。大多时候错误都是因为字符串中
	//有语法错误。
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./'");
	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs;
	//载入脚本
	pName = PyUnicode_FromString("python2cpp");
	pModule = PyImport_Import(pName);
	if (!pModule) {
		printf("can't find python2cpp.py");
		getchar();
		return -1;
	}
	pDict = PyModule_GetDict(pModule);
	if (!pDict) {
		return -1;
	}
	//找出函数名为add的函数
	pFunc = PyDict_GetItemString(pDict, "add");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		printf("can't find function [add]");
		getchar();
		return -1;
	}
	//参数进栈
	pArgs = PyTuple_New(2);
	//PyObject* Py_BuildValue(char *format,……）
	//把C++变量转换成一个Python对象。当需要从
	//C++传递变量到Python时，就会使用这个函数。此函数
	//有点类似C的printf,但格式不同。常用的格式有
	//s表示字符串
	//i表示整形变量
	//f表示浮点数
	//O表示一个Python对象
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 3));
	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));
	//调用Python函数
	PyObject_CallObject(pFunc, pArgs);
	//下面这段是查找函数foo，并执行foo
	pFunc = PyDict_GetItemString(pDict, "foo");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		printf("can't find function [foo]");
		getchar();
		return -1;
	}
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
	PyObject_CallObject(pFunc, pArgs);
	Py_DECREF(pName);
	Py_DECREF(pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pDict);
	Py_DECREF(pFunc);
	//关闭Python
	Py_Finalize();
    return 0;
}

