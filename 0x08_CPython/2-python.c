#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

/**
 * print_python_list - print python list
 * @p: pointer to the list
*/
void print_python_list(PyObject *p)
{
	PyObject *item = NULL;
	PyListObject *list = NULL;
	Py_ssize_t length, i;
	const char *type = NULL;

	printf("[*] Python list info\n");
	if (!p || !PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	length = PyObject_Length(p);
	list = (PyListObject *)p;
	printf("[*] Size of the Python List = %ld\n"
			"[*] Allocated = %ld\n", length, list->allocated);
	for (i = 0; i < length; i++)
	{
		item = list->ob_item[i];
		type = item->ob_type->tp_name;
		printf("Element %ld: %s\n", i, type);
		if (item->ob_type == &PyBytes_Type)
			print_python_bytes(item);
	}
}

/**
 * print_python_bytes - Prints the bytes
 * @p: pointer to an object
*/
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i;
	PyBytesObject *byte;

	printf("[.] bytes object info\n");
	if (!p || !PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	byte = (PyBytesObject *)p;
	size = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", byte->ob_sval);
	size = size < 9 ? size + 1 : 10;
	printf("  first %ld bytes: ", size);
	for (i = 0; i < size; i++)
		printf("%02hhx%c", byte->ob_sval[i], i + 1 == size ? '\n' : ' ');
}
