cmake_minimum_required(VERSION 3.15)
project(RRMetaParams VERSION 0.1)

add_subdirectory(3d_party)

add_executable(RRMetaParams 
    "src/Source.cpp" 
    "src/Constraints.cpp"
    "src/Conditions.cpp"
    "src/Parameter.cpp"
    "src/Types.cpp"
    "src/ParamClass.cpp"
    "src/ParametersBlock.cpp"
    "src/ModuleGenerator.cpp")
target_link_libraries(RRMetaParams PRIVATE nlohmann::json)
target_link_libraries(RRMetaParams PRIVATE fmt::fmt)
target_include_directories(RRMetaParams PRIVATE include)