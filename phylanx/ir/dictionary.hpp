// Copyright (c) 2018 Weile Wei
// Copyright (c) 2018 Parsa Amini
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_DICTIONARY)
#define PHYLANX_DICTIONARY

#include <phylanx/config.hpp>

#include <hpx/include/serialization.hpp>

#include <unordered_map>

namespace phylanx { namespace execution_tree
{
    struct primitive_argument_type;
}}

namespace phylanx { namespace ir
{
    using dictionary = std::unordered_map<phylanx::execution_tree::primitive_argument_type, phylanx::execution_tree::primitive_argument_type>;
}}


#endif
