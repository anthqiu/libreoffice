/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/document/XExporter.hpp>
#include <com/sun/star/document/XFilter.hpp>
#include <com/sun/star/document/XImporter.hpp>
#include <com/sun/star/io/WrongFormatException.hpp>
#include <com/sun/star/lang/WrappedTargetRuntimeException.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <cppuhelper/exc_hlp.hxx>
#include <cppuhelper/supportsservice.hxx>
#include <rtl/ustring.hxx>
#include <unotools/mediadescriptor.hxx>
#include <comphelper/scopeguard.hxx>
#include <dmapper/DomainMapperFactory.hxx>

using namespace ::com::sun::star;

namespace
{
class MarkdownFilter
    : public cppu::WeakImplHelper<document::XFilter, document::XImporter, document::XExporter,
                                  lang::XInitialization, lang::XServiceInfo>
{
    uno::Reference<uno::XComponentContext> m_xContext;

public:
    explicit MarkdownFilter(uno::Reference<uno::XComponentContext> xContext)
        : m_xContext(std::move(xContext))
    {
    }

    // XFilter
    sal_Bool SAL_CALL filter(const uno::Sequence<beans::PropertyValue>& rDescriptor) override;
    void SAL_CALL cancel() override;

    // XImporter
    void SAL_CALL setTargetDocument(const uno::Reference<lang::XComponent>& xDoc) override;

    // XExporter
    void SAL_CALL setSourceDocument(const uno::Reference<lang::XComponent>& xDoc) override;

    // XInitialization
    void SAL_CALL initialize(const uno::Sequence<uno::Any>& rArguments) override;

    // XServiceInfo
    OUString SAL_CALL getImplementationName() override;
    sal_Bool SAL_CALL supportsService(const OUString& rServiceName) override;
    uno::Sequence<OUString> SAL_CALL getSupportedServiceNames() override;
};
}

sal_Bool SAL_CALL MarkdownFilter::filter(const uno::Sequence<beans::PropertyValue>& rDescriptor)
{
    return true;
}

void SAL_CALL MarkdownFilter::cancel() {}

void SAL_CALL MarkdownFilter::setTargetDocument(const uno::Reference<lang::XComponent>& xDoc) {}

void SAL_CALL MarkdownFilter::setSourceDocument(const uno::Reference<lang::XComponent>& xDoc) {}

void SAL_CALL MarkdownFilter::initialize(const uno::Sequence<uno::Any>& rArguments) {}

OUString SAL_CALL MarkdownFilter::getImplementationName() { return OUString(); }

sal_Bool SAL_CALL MarkdownFilter::supportsService(const OUString& rServiceName) { return true; }

uno::Sequence<OUString> SAL_CALL MarkdownFilter::getSupportedServiceNames()
{
    uno::Sequence<OUString> aRet = { u"com.sun.star.document.ImportFilter"_ustr,
                                     u"com.sun.star.document.ExportFilter"_ustr };
    return aRet;
}

extern "C" SAL_DLLPUBLIC_EXPORT uno::XInterface*
com_sun_star_comp_Writer_MarkdownFilter_get_implementation(
    uno::XComponentContext* pComponent, uno::Sequence<uno::Any> const& /*rSequence*/)
{
    return cppu::acquire(new MarkdownFilter(pComponent));
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
