/*++
  Copyright (c) 2017 Microsoft Corporation

  Module Name:

  <name>

  Abstract:

  <abstract>

  Author:
  Nikolaj Bjorner (nbjorner)
  Lev Nachmanson (levnach)

  Revision History:


  --*/
#pragma once

#include "math/lp/nla_common.h"
#include "math/lp/nla_intervals.h"
#include "math/lp/nex.h"
#include "math/lp/cross_nested.h"

namespace nla {
class core;


class horner : common {
    intervals m_intervals;
public:
    typedef intervals::interval interv;
    horner(core *core);
    void horner_lemmas();
    template <typename T> // T has an iterator of (coeff(), var())
    bool lemmas_on_row(const T&);
    template <typename T>  bool row_is_interesting(const T&) const;
    template <typename T>
    nex_sum* create_sum_from_row(const T&, cross_nested&);
    intervals::interval interval_of_expr(const nex* e);
    
    nex* nexvar(lpvar j, cross_nested& cn) const;
    intervals::interval interval_of_sum(const nex_sum*);
    intervals::interval interval_of_sum_no_terms(const nex_sum*);
    intervals::interval interval_of_mul(const nex_mul*);
    void set_interval_for_scalar(intervals::interval&, const rational&);
    void set_var_interval(lpvar j, intervals::interval&) const;
    bool lemmas_on_expr(nex_sum* , cross_nested&);
    
    template <typename T> // T has an iterator of (coeff(), var())
    bool row_has_monomial_to_refine(const T&) const;
    lpvar find_term_column(const nex* e, rational& a, rational& b) const;
    static lp::lar_term expression_to_normalized_term(const nex_sum*, rational& a, rational & b);
    static void add_linear_to_vector(const nex*, vector<std::pair<rational, lpvar>> &);
    static void add_mul_to_vector(const nex_mul*, vector<std::pair<rational, lpvar>> &);
    bool interval_from_term(const nex* e, interv&) const;
}; // end of horner
}