cmake_minimum_required(VERSION 3.13.0)
project (CPP-React-Math)

set (PROJECT_SOURCES
	React-Math.h
	support/common.h
	support/vector.h
	support/matrix.h
	vec2.h
	vec3.h
	vec4.h
	mat2.h
	mat3.h
	mat4.h
)

target_sources(CPP-React-Math INTERFACE ${PROJECT_SOURCES})

add_custom_target(${PROJECT_NAME}_ SOURCES ${PROJECT_SOURCES})