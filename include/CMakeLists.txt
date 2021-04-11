cmake_minimum_required(VERSION 3.13.0)
project (CPP-React-Math)

set (PROJECT_SOURCES
	React-Math.h
	support/common.h
	support/vector.h
	vec2.h
	vec3.h
	vec4.h
)

target_sources(CPP-React-Math INTERFACE ${PROJECT_SOURCES})

add_custom_target(${PROJECT_NAME}_ SOURCES ${PROJECT_SOURCES})