#ifndef __FOREACH__
#define __FOREACH__

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))

#define MAP_OUT

#define MAP_END(...)

#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(item, next, ...) next MAP_OUT
#define MAP_NEXT1(item, next) MAP_NEXT0(item, next, 0)
#define MAP_NEXT(item, next) MAP_NEXT1(MAP_GET_END item, next)

// map with constant
#define MAP0_C(f, rop, x, peek, ...) f(rop, x) MAP_NEXT(peek, MAP1_C)(f, rop, peek, __VA_ARGS__)
#define MAP1_C(f, rop, x, peek, ...) f(rop, x) MAP_NEXT(peek, MAP0_C)(f, rop, peek, __VA_ARGS__)

#define MAP_C(f, rop, ...) EVAL(MAP1_C(f, rop, __VA_ARGS__, (), 0))

// map without constant
#define MAP0(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP1)(f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT(peek, MAP0)(f, peek, __VA_ARGS__)

#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, (), 0))

#define OR(rop, op) || rop == op

#define FOREACH_OR(rop, op1, ...) rop == op1 MAP_C(OR, rop, __VA_ARGS__)

#define FILTER(x) FILTER_(x)
#define FILTER_(...) __VA_OPT__(, ) __VA_ARGS__
#define SEP TEMP MAP_OUT(0, 1, 2)
#define TEMP(...)

#define REMOVE_FIRST(first, ...) __VA_ARGS__
#define REMOVE_SEP(...) MAP(FILTER, __VA_ARGS__)

int main(int argc, char **argv)
{
	REMOVE_FIRST(REMOVE_SEP(3, 4, 5, SEP, 6, 7, 0))
	return 0;
}

#endif //__FOREACH__
