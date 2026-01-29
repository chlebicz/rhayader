cmake_minimum_required(VERSION 3.20)
project(rhayader)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

set(
  filereader
  FileReader.cpp FileReader.hpp
)
FetchContent_Declare(
  replxx
  GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
  GIT_TAG master
)
FetchContent_MakeAvailable(replxx)

set(
  main
  main.cpp repl.cpp
  repl.hpp
)

set(
  util
  util/colors.cpp util/Error.cpp util/util.cpp
  util/colors.hpp util/Error.hpp util/util.hpp
)

set(
  tokenizer
  tokenizer/FileReadError.cpp tokenizer/NoTokensError.cpp tokenizer/Token.cpp tokenizer/Tokenizer.cpp tokenizer/TokenList.cpp tokenizer/TokenType.cpp
  tokenizer/FileReadError.hpp tokenizer/NoTokensError.hpp tokenizer/Token.hpp tokenizer/Tokenizer.hpp tokenizer/TokenList.hpp tokenizer/TokenType.hpp
)

set(
  parser
  parser/dumpNode.cpp parser/nodes.cpp parser/ParseError.cpp parser/Parser.cpp
  parser/dumpNode.hpp parser/nodes.hpp parser/ParseError.hpp parser/Parser.hpp
  parser/nodeCast.hpp
)

set(
  evaluator
  evaluator/EvaluateError.cpp evaluator/evaluator.cpp evaluator/GlobalScope.cpp evaluator/Scope.cpp evaluator/Thread.cpp
  evaluator/EvaluateError.cpp evaluator/evaluator.hpp evaluator/GlobalScope.hpp evaluator/Scope.hpp evaluator/Thread.hpp
)

set(
  modules
  evaluator/modules/Array.cpp evaluator/modules/IO.cpp evaluator/modules/Map.cpp evaluator/modules/Math.cpp evaluator/modules/String.cpp evaluator/modules/ThreadModule.cpp evaluator/modules/Validation.cpp evaluator/modules/File.cpp
  evaluator/modules/Array.hpp evaluator/modules/IO.hpp evaluator/modules/Map.hpp evaluator/modules/Math.hpp evaluator/modules/String.hpp evaluator/modules/ThreadModule.hpp evaluator/modules/Validation.hpp evaluator/modules/File.hpp
)

set(
  values
  evaluator/values/ArrayValue.cpp evaluator/values/BooleanValue.cpp evaluator/values/ExplicitReturnValue.cpp evaluator/values/FunctionValue.cpp evaluator/values/MapValue.cpp evaluator/values/ModuleValue.cpp evaluator/values/NullValue.cpp evaluator/values/NumberValue.cpp evaluator/values/RangeValue.cpp evaluator/values/StringValue.cpp evaluator/values/ValueType.cpp
  evaluator/values/ArrayValue.hpp evaluator/values/BooleanValue.hpp evaluator/values/ExplicitReturnValue.hpp evaluator/values/FunctionValue.hpp evaluator/values/MapValue.hpp evaluator/values/ModuleValue.hpp evaluator/values/NullValue.hpp evaluator/values/NumberValue.hpp evaluator/values/RangeValue.hpp evaluator/values/StringValue.hpp evaluator/values/ValueType.hpp
  evaluator/valueCast.hpp evaluator/values/Value.hpp evaluator/values/values.hpp
)

source_group("main" FILES ${main})
source_group("filereader" FILES ${filereader})
source_group("util" FILES ${util})
source_group("tokenizer" FILES ${tokenizer})
source_group("parser" FILES ${parser})
source_group("evaluator" FILES ${evaluator})
source_group("modules" FILES ${modules})
source_group("values" FILES ${values})

add_executable(
  rhayader
  ${main} ${filereader} ${util} ${tokenizer} ${parser} ${evaluator} ${modules} ${values}
)

add_executable(
  rhayader_tests
  test/test.cpp
  ${filereader} ${util} ${tokenizer} ${parser} ${evaluator} ${modules} ${values}
)

target_link_libraries(rhayader_tests PRIVATE Catch2::Catch2WithMain)

# Test Registration
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(rhayader_tests)
target_link_libraries(rhayader PRIVATE replxx)
