/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2009 Ferdinando Ametrano
 Copyright (C) 2009 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/cashflow.hpp>
#include <ql/settings.hpp>
#include <ql/patterns/visitor.hpp>

namespace QuantLib {

    bool CashFlow::hasOccurred(const Date& refDate,
                               boost::optional<bool> includeRefDate) const {

        // easy and quick handling of most cases
        if (refDate != Date()) {
            Date cf = date();
            if (refDate < cf)
                return false;
            if (cf < refDate)
                return true;
        }

        if (refDate == Date() ||
            refDate == Settings::instance().evaluationDate()) {
            // today's date; we override the bool with the one
            // specified in the settings (if any)
            boost::optional<bool> includeToday =
                Settings::instance().includeTodaysCashFlows();
            if (includeToday)
                includeRefDate = *includeToday;
        }
        return Event::hasOccurred(refDate, includeRefDate);
    }

    bool CashFlow::tradingExCoupon(const Date& refDate) const {

        Date ecd = exCouponDate();
        if (ecd == Date())
            return false;

        Date ref =
            refDate != Date() ? refDate : Settings::instance().evaluationDate();

        return ecd <= ref;
    }
   
   
    void CashFlow::accept(AcyclicVisitor& v) {
        Visitor<CashFlow>* v1 = dynamic_cast<Visitor<CashFlow>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            Event::accept(v);
    }
 
    void test(){
     std::cout<<" Le fameux Bonjour "<<std::endl;
    }

}

