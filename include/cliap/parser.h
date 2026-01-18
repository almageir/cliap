#ifndef CLIAP_PARSER_H
#define CLIAP_PARSER_H

#include <cliap/arg.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

namespace cliap
{
    class ArgParser {
        using ArgPtr = std::shared_ptr<Arg>;
    public:
        ArgParser& add_parameter(Arg parm);

        std::optional<std::string> parse(const std::vector<std::string>& args);

        std::optional<std::string> parse(int argc, char* argv[]);

        void add_usage_string(std::string usage_string);

        void print_help();

        const Arg& arg(const std::string& arg_name) const;

        std::size_t parameters_count() const { return all_params().size(); }

        void reset();

        std::vector<ArgPtr> all_params() const;

    private:
        void print_usage_examples() const;

        void adjust_fmt_max_field_lengths(const ArgPtr& p);

        std::size_t required_args_count() const {
            const auto params = all_params();
            return static_cast<std::size_t>(std::count_if(
                std::cbegin(params),
                std::cend(params),
                [](const auto& ptr) mutable { return ptr->is_required() && ptr->value().empty(); }
            ));
        }

        std::optional<std::string> check_required_args() const;

        std::unordered_map<std::string, ArgPtr> params_map_;
        std::vector<std::string> usage_examples_;

        int max_long_param_name_length_{};
        int max_short_param_name_length_{};
        int max_default_param_value_length_{};

        Arg empty_arg_{};
    };
}

#endif //CLIAP_PARSER_H