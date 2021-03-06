// Python27.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Windows.h"
#include "Python.h"
using namespace std;
int main()
{
	//初始化python
	//在使用python系统前，必须使用Py_Initialize对其
	//进行初始化。它会载入python的内嵌模块并添加系统
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
	//PyRun_SimpleString("addpath='.\+++++====='");//Pyhton的字符串不能以"\"结尾，所以需要处理一下，但这个并未能影响本项目的正常运行
	//PyRun_SimpleString("addpath=addpath[0:2]");
	PyRun_SimpleString("sys.path.append('.\')");
	//PyRun_SimpleString("sys.path.append(addpath)");
	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue;
	//载入脚本
	//注意调用Python2脚本里面不能有中文，因为python2脚本默认保存为ASCII码，而一旦有中文字符的时候就会保存成UTF-8格式
	//当保存成了UTF-8的模式时，就会出现打开出错的情况
	//pName = PyUnicode_FromString("python2cppV2");
	//pName = PyString_FromString("python2cppV2");
	pName = PyString_FromString("python2cpp");
	pModule = PyImport_Import(pName);
	//pModule = PyImport_AddModule("python2cpp");
	//pModule = PyImport_ImportModule("python2cpp");
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
	pValue = PyObject_CallObject(pFunc, pArgs);//用pValue保存返回值
	int result = 0;
	result = PyLong_AsLong(pValue);//解析返回值
	printf("Cpp received result = %d\n", result);//输出返回值
	printf("\n");
	//下面这段是查找函数foo，并执行foo
	pFunc = PyDict_GetItemString(pDict, "foo");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		printf("can't find function [foo]");
		getchar();
		return -1;
	}
	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
	pValue = PyObject_CallObject(pFunc, pArgs);
	result = PyLong_AsLong(pValue);
	printf("Cpp received result = %d\n", result);
	printf("\n");
	//下面这段是查找函数returnList，并执行returnList
	pFunc = PyDict_GetItemString(pDict, "returnList");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		printf("can't find function [returnList]");
		getchar();
		return -1;
	}
	pArgs = NULL;//无参函数的参数列表定义为NULL
	pValue = PyObject_CallObject(pFunc, pArgs);
	int ListLen = PyObject_Size(pValue);//列表长度

	PyObject *list_item = NULL;//python类型的列表元素
	Py_UNICODE *str_item = NULL;//c类型的列表元素

	list_item = PyList_GetItem(pValue, 0);//根据下标取出python列表中的元素
	str_item = PyUnicode_AsUnicode(list_item);//取出字符串
	wprintf(L"%ls\n", str_item);

	list_item = PyList_GetItem(pValue, 1);//根据下标取出python列表中的元素
	int r1 = PyLong_AsLong(list_item);//取出数值
	printf("%d\n", r1);

	//Py_ssize_t i = 3;
	//str_item = PyUnicode_AsWideCharString(list_item, &i);
	//PyObject *pTuple = PyList_AsTuple(pValue);
	//PyArg_ParseTuple(pTuple, "s|i|f", str_item, &r1, &r2);//分析返回的元组值  

	list_item = PyList_GetItem(pValue, 2);//根据下标取出python列表中的元素
	double r2 = PyFloat_AsDouble(list_item);//取出数值
	printf("%f\n", r2);

	printf("\n");

	//下面这段是查找函数returnDict，并执行returnDict
	pFunc = PyDict_GetItemString(pDict, "returnDict");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		printf("can't find function [returnDict]");
		getchar();
		return -1;
	}
	pArgs = NULL;//无参函数的参数列表定义为NULL
	pValue = PyObject_CallObject(pFunc, pArgs);

	int DictLen = PyObject_Size(pValue);//字典长度
	PyObject *Dict_item = NULL;//python类型的列表元素
	str_item = NULL;//c类型的列表元素
	Dict_item = PyDict_GetItem(pValue, PyUnicode_FromString("Open"));
	double Open = PyFloat_AsDouble(Dict_item);//取出数值
	printf("Open = %7.2f\n", Open);
	Dict_item = PyDict_GetItem(pValue, PyUnicode_FromString("High"));
	double High = PyFloat_AsDouble(Dict_item);//取出数值
	printf("High = %7.2f\n", High);
	Dict_item = PyDict_GetItem(pValue, PyUnicode_FromString("Low"));
	double Low = PyFloat_AsDouble(Dict_item);//取出数值
	printf("Low = %7.2f\n", Low);
	Dict_item = PyDict_GetItem(pValue, PyUnicode_FromString("Close"));
	double Close = PyFloat_AsDouble(Dict_item);//取出数值
	printf("Close = %7.2f\n", Close);

	Py_DECREF(pName);
	//Py_DECREF(pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pDict);
	Py_DECREF(pFunc);
	//Py_DECREF(list_item);
	//关闭Python
	Py_Finalize();

	getchar();
	return 0;
}

