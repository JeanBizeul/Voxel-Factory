add_library(logger
    Logger.cpp
)

target_compile_definitions(logger PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
)
