#ifndef CLIAP_ARG_H
#define CLIAP_ARG_H

#include <sstream>
#include <string>

namespace cliap
{
    class Arg {
    public:
        Arg() = default;
        explicit Arg(std::string name);
        Arg& short_name(std::string short_name);
        Arg& long_name(std::string long_name);
        Arg& set_default(std::string default_value);
        Arg& description(std::string description);
        Arg& value(std::string value);
        Arg& required();
        Arg& flag();

        void set_parsed(bool is_parsed) {
            is_parsed_ = is_parsed;
        }

        const std::string& short_name() const { return short_name_; }
        const std::string& long_name() const { return long_name_; }
        const std::string& default_value() const { return default_value_; }
        const std::string& description() const { return description_; }
        const std::string& value() const { return value_; }
        bool is_required() const { return is_required_; }
        bool is_flag() const { return is_flag_; }
        bool is_parsed() const { return is_parsed_; }

        template<typename T>
        T get_value_as() const {
            if (value_.empty())
                return {};

            T result{};
            std::stringstream ss{value_};
            ss >> result;
            return result;
        }

        const std::string& get_value_as_str() const { return value_; }

    private:
        std::string short_name_;
        std::string long_name_;
        std::string default_value_;
        std::string description_;
        std::string value_;
        bool is_required_{false};
        bool is_flag_{false};
        bool is_parsed_{false};
    };
}

#endif //CLIAP_ARG_H