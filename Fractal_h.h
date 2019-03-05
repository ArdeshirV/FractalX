// Copyright (c) 2002-2004 ardeshirv@protonmail.com, Licensed Under GPLv3+

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Mar 01 17:32:43 2012
 */
/* Compiler settings for Fractal.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Fractal_h_h__
#define __Fractal_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFractal_FWD_DEFINED__
#define __IFractal_FWD_DEFINED__
typedef interface IFractal IFractal;
#endif 	/* __IFractal_FWD_DEFINED__ */


#ifndef __CFractalDoc_FWD_DEFINED__
#define __CFractalDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFractalDoc CFractalDoc;
#else
typedef struct CFractalDoc CFractalDoc;
#endif /* __cplusplus */

#endif 	/* __CFractalDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Fractal_LIBRARY_DEFINED__
#define __Fractal_LIBRARY_DEFINED__

/* library Fractal */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Fractal;

#ifndef __IFractal_DISPINTERFACE_DEFINED__
#define __IFractal_DISPINTERFACE_DEFINED__

/* dispinterface IFractal */
/* [uuid] */ 


EXTERN_C const IID DIID_IFractal;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DF116BC7-030F-47DE-A348-CA46EA558694")
    IFractal : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IFractalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFractal * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFractal * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFractal * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFractal * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFractal * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFractal * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFractal * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IFractalVtbl;

    interface IFractal
    {
        CONST_VTBL struct IFractalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFractal_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFractal_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFractal_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFractal_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFractal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFractal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFractal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IFractal_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CFractalDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("7AB65EA6-7E41-4B14-896C-F570BA5747EC")
CFractalDoc;
#endif
#endif /* __Fractal_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


