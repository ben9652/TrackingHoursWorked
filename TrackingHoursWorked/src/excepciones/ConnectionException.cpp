#include "ConnectionException.h"
#include <string.h>

ConnectionException::ConnectionException(const char8_t* mensaje)
{
	msj = (char*)malloc(300);
	memset(msj, 0, 300);
	size_t sizeMensaje = 0;
	for (char8_t* c = (char8_t*)mensaje; *c != 0; c++)
		sizeMensaje++;
	for (int i = 0; i < sizeMensaje; i++)
		msj[i] = mensaje[i];
}

const char* ConnectionException::what() const
{
	return msj;
}