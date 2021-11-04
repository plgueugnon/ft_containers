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

#endif // __FT_ENABLE_IF_H__