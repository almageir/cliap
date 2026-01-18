# cliap

___
Небольшая библиотека для облегчения разбора аргументов командной строки для приложений.

## Пример использования

Смотрите полный пример в [`examples/basic_usage`](examples/basic_usage).

### Как подключить в CMake-проект

```cmake
include(FetchContent)
FetchContent_Declare(
    cliap
    GIT_REPOSITORY https://github.com/almageir/cliap.git
    GIT_TAG        master
)
option(CLIAP_STANDALONE_BUILD off)
FetchContent_MakeAvailable(cliap)

target_link_libraries(app PRIVATE cliap::cliap)
```

### Как использовать для разбора аргументов командной строки

```c++
#include <cliap/cliap.h>
#include <iostream>
#include <cstdint>

int main(int argc, char* argv[]) {
    using cliap::Arg;
    cliap::ArgParser argParser;

    argParser
        .add_parameter(Arg("h,help").flag().description("Show help message"))
        .add_parameter(Arg("p,target-port").required().description("Target port"))
        .add_parameter(Arg("t,target-host").required().set_default("127.0.0.1").description("Target host"));

    argParser.add_usage_string("./basic_usage_example --target-host=192.168.1.1 --target-port=8443");

    const auto err_msg = argParser.parse(argc, argv);
    if (argParser.arg("h").is_parsed()) {
        argParser.print_help();
        return 0;
    }

    if (err_msg.has_value()) {
        std::cout << *err_msg << std::endl;
        argParser.print_help();
        return 0;
    }

    const auto host = argParser.arg("target-host").get_value_as_str();
    const auto port = argParser.arg("p").get_value_as<std::uint16_t>();

    std::cout << "Target host: " << host << std::endl;
    std::cout << "Target port: " << port << std::endl;

    return 0;
}
```

Вывод программы с аргументом **-h (--help)**

```sh
Usage: 
    ./basic_usage_example --target-host=192.168.1.1 --target-port=8443
Parameters:
    -h [ --help        ] Show help message             
    -p [ --target-port ] Target port [required]
    -t [ --target-host ] Target host [required] (default: 127.0.0.1)
```

Вывод программы с аргументами **--target-host=192.168.1.1 --target-port=8443**

```sh
Target host: 192.168.1.1
Target port: 8443
```

Вывод программы с пропущенным обязательным параметром **--target-port**

```sh
Expected required parameter value: p [target-port]
Usage: 
    ./basic_usage_example --target-host=192.168.1.1 --target-port=8443
Parameters:
    -h [ --help        ] Show help message             
    -p [ --target-port ] Target port [required]             
    -t [ --target-host ] Target host [required] (default: 127.0.0.1)
```

## Требования

___

* CMake
* C++ 17
