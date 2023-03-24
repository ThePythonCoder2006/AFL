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

#define MAP0(f, rop, x, peek, ...) f(rop, x) MAP_NEXT(peek, MAP1)(f, rop, peek, __VA_ARGS__)
#define MAP1(f, rop, x, peek, ...) f(rop, x) MAP_NEXT(peek, MAP0)(f, rop, peek, __VA_ARGS__)

#define MAP(f, rop, ...) EVAL(MAP1(f, rop, __VA_ARGS__, (), 0))

#define OR(rop, op) || rop == op

#define FOREACH_OR(rop, op1, ...) rop == op1 MAP(OR, rop, __VA_ARGS__)

#endif //__FOREACH__
