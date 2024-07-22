#include <Python.h>
#include <stdlib.h>
#include <stdio.h>

void print_python_string(PyObject *p);

/**
 * print_python_string - Function to print strings
 * @p: pointer to object
*/
void print_python_string(PyObject *p)
{
	PyASCIIObject *str;

	str = (PyASCIIObject *)p;
	wprintf(L"[.] string object info\n");
	if (!p || !PyUnicode_Check(p))
	{
		wprintf(L"  [ERROR] Invalid String Object\n");
		return;
	}
	if (str->state.ascii)
		wprintf(L"  type: compact ascii\n");
	else
		wprintf(L"  type: compact unicode object\n");
	wprintf(L"  length: %ld\n", str->length);
	wprintf(L"  value: %ls\n", PyUnicode_AS_UNICODE(p));
}
