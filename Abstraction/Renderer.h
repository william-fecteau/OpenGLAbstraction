#include <glad/glad.h>

//Don't define DEBUG to be in PRODUCITON mode (No debug message in console)
#define DEBUG

#ifdef DEBUG
	#define GLCall(x) GLClearError();\
		x;\
		if(!GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
	#define GLCall(x) x
#endif

/**
*	Clears the OpenGL error flags
*/
void GLClearError();

/**
*	Loop through all the OpengGL error flags
*
*	@return Bool if there is an error
*/
bool GLLogCall(const char* function, const char* file, int line);
