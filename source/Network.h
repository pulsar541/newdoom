#ifndef NETWORK_H
#define NETWORK_H

#include "Export.h"

/* StringName */
#define NETWORK_ERROR       0x0001
#define NETWORK_DESCRIPTION 0x0002

/* Common funcs*/
//NETWORK_API unsigned int getError();
NETWORK_API const char* getString(unsigned int name);
bool NETWORK_API initialize();
bool NETWORK_API uninitialize();

/* Server funcs*/
bool NETWORK_API host();
bool NETWORK_API srv_disconnect();
bool NETWORK_API sendTo(const char* buff, int len);
bool NETWORK_API receiveFrom(char* buf, int len);

/* Client funcs */
bool NETWORK_API connect(const char* serverAddress);
bool NETWORK_API cl_disconnect();
bool NETWORK_API send(const char* buff, int len);
bool NETWORK_API receive(char* buf, int len);

#endif
