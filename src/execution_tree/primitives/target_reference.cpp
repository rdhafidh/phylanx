//  Copyright (c) 2017-2018 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/target_reference.hpp>

#include <hpx/include/lcos.hpp>
#include <hpx/include/naming.hpp>
#include <hpx/include/util.hpp>
#include <hpx/throw_exception.hpp>

#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace phylanx { namespace execution_tree { namespace primitives
{
    ///////////////////////////////////////////////////////////////////////////
    match_pattern_type const target_reference::match_data =
    {
        hpx::util::make_tuple("target-reference",
            std::vector<std::string>{},
            nullptr, &create_primitive<target_reference>)
    };

    ///////////////////////////////////////////////////////////////////////////
    target_reference::target_reference(
            std::vector<primitive_argument_type>&& args, std::string const& name,
            std::string const& codename)
      : primitive_component_base(std::move(args), name, codename)
    {
        // operands_[0] holds the target function/variable
        if (operands_.empty() || !valid(operands_[0]))
        {
            HPX_THROW_EXCEPTION(hpx::bad_parameter,
                "target_reference::target_reference",
                generate_error_message("no target given"));
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    hpx::future<primitive_argument_type> target_reference::eval(
        std::vector<primitive_argument_type> const& params) const
    {
        if (operands_.size() > 1)
        {
            // the function has pre-bound arguments
            std::vector<primitive_argument_type> fargs;
            fargs.reserve(operands_.size() - 1 + params.size());

            for (auto it = operands_.begin() + 1; it != operands_.end(); ++it)
            {
                fargs.push_back(extract_ref_value(*it));
            }

            for (auto const& param : params)
            {
                fargs.push_back(extract_value(param));
            }

            return value_operand(
                operands_[0], std::move(fargs), name_, codename_);
        }

        return value_operand(
            operands_[0], params, name_, codename_, eval_dont_wrap_functions);
    }

    void target_reference::store(primitive_argument_type&& data)
    {
        primitive* p = util::get_if<primitive>(&operands_[0]);
        if (p != nullptr)
        {
            p->store(std::move(data));
        }
    }

    topology target_reference::expression_topology(
        std::set<std::string>&& functions,
        std::set<std::string>&& resolve_children) const
    {
        primitive const* p = util::get_if<primitive>(&operands_[0]);
        if (p != nullptr)
        {
            return p->expression_topology(hpx::launch::sync,
                std::move(functions), std::move(resolve_children));
        }
        return {};
    }
}}}

