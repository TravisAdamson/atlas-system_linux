#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

void print_python_list(PyObject *p);

/**
 * print_python_list - FUnction for printing info of a python list
 * @p: pointer to the python list
*/
void print_python_list(PyObject *p)
{
	PyObject *item = NULL;
	PyListObject *list = NULL;
	Py_ssize_t length, i;
	const char *type = NULL;

	if (!p || !PyList_Check(p))
		return;
	length = PyObject_Length(p);
	list = (PyListObject *)p;
	printf("[*] Python list info\n"
			"[*] Size of the Python List = %ld\n"
			"[*] Allocated = %ld\n", length, list->allocated);
	for (i = 0; i < length; i++)
	{
		item = list->ob_item[i];
		type = item->ob_type->tp_name;
		printf("Element %ld: %s\n", i, type);
	}
}
