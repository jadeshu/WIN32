// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

#import "C:\\Windows\\System32\\winhttp.dll" no_namespace
// CWinHttpRequest 包装类

class CWinHttpRequest : public COleDispatchDriver
{
public:
	CWinHttpRequest(){} // 调用 COleDispatchDriver 默认构造函数
	CWinHttpRequest(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWinHttpRequest(const CWinHttpRequest& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// IWinHttpRequest 方法
public:
	void SetProxy(long ProxySetting, VARIANT& ProxyServer, VARIANT& BypassList)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ProxySetting, &ProxyServer, &BypassList);
	}
	void SetCredentials(LPCTSTR UserName, LPCTSTR Password, long Flags)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, UserName, Password, Flags);
	}
	void Open(LPCTSTR Method, LPCTSTR Url, VARIANT& Async)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Method, Url, &Async);
	}
	void SetRequestHeader(LPCTSTR Header, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Header, Value);
	}
	CString GetResponseHeader(LPCTSTR Header)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Header);
		return result;
	}
	CString GetAllResponseHeaders()
	{
		CString result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void Send(VARIANT& Body)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Body);
	}
	long get_Status()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_StatusText()
	{
		CString result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ResponseText()
	{
		CString result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	VARIANT get_ResponseBody()
	{
		VARIANT result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_ResponseStream()
	{
		VARIANT result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Option(long Option)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Option);
		return result;
	}
	void put_Option(long Option, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Option, &newValue);
	}
	BOOL WaitForResponse(VARIANT& Timeout)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Timeout);
		return result;
	}
	void Abort()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetTimeouts(long ResolveTimeout, long ConnectTimeout, long SendTimeout, long ReceiveTimeout)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ResolveTimeout, ConnectTimeout, SendTimeout, ReceiveTimeout);
	}
	void SetClientCertificate(LPCTSTR ClientCertificate)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ClientCertificate);
	}
	void SetAutoLogonPolicy(long AutoLogonPolicy)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AutoLogonPolicy);
	}

	// IWinHttpRequest 属性
public:

};
