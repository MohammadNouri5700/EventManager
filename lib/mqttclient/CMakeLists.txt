link_directories(${mosquitto_BINARY_DIR}/lib)

set(CPP_SRC mosquittopp.cpp mosquittopp.h mqttclient.cpp)

add_library(mosquittopp STATIC ${CPP_SRC})
set_target_properties(mosquittopp PROPERTIES
	POSITION_INDEPENDENT_CODE 1
)
target_link_libraries(mosquittopp mosquitto)

target_include_directories(mosquittopp PUBLIC ./)