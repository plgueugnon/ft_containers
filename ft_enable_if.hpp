#ifndef __FT_ENABLE_IF_H__
#define __FT_ENABLE_IF_H__

namespace ft
{

	template<bool B, class T = void>
	struct enable_if {};

// au moment de la compilation le compilateur va essayer de constuire la struct
// avec les 2 templates donnes en arg, si cela echoue il renvoie un false au lieu de true
// si il renvoie true => le typedef T sera activé
	template<class T>
	struct enable_if<true, T> {typedef T type; };

}

// if needed use https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time
// and https://www.ibm.com/docs/en/xl-c-and-cpp-aix/12.1.0?topic=SSGH3R_12.1.0/com.ibm.xlcpp121.aix.doc/standlib/header_type_traits.html

#endif // __FT_ENABLE_IF_H__