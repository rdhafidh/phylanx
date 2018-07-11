// Copyright (c) 2018 Weile Wei
// Copyright (c) 2018 Parsa Amini
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_DICTIONARY)
#define PHYLANX_DICTIONARY

#include <phylanx/config.hpp>
#include <phylanx/util/variant.hpp>

#include <hpx/include/serialization.hpp>

#include <unordered_map>

namespace phylanx { namespace execution_tree
{
    struct primitive_argument_type;
}}

namespace phylanx { namespace ir
{
    using dictionary = std::unordered_map<phylanx::util::recursive_wrapper<phylanx::execution_tree::primitive_argument_type>, phylanx::util::recursive_wrapper<phylanx::execution_tree::primitive_argument_type>>;
}}

namespace std
{
    template<> struct hash<phylanx::util::recursive_wrapper<phylanx::execution_tree::primitive_argument_type>>
    {
        typedef phylanx::util::recursive_wrapper<phylanx::execution_tree::primitive_argument_type> argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& s) const noexcept
        {
            return 42;
        }
    };
}

#endif
