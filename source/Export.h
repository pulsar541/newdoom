#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define NETWORK_API __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define NETWORK_API __declspec (dllimport)
#endif /* Not BUILDING_DLL */


#endif /* _DLL_H_ */
