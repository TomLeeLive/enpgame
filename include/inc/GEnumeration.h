#pragma once
//#include "GDefine.h"
#include "GUtils.h"
#include "GDxHelper.h"
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class GEnumOutput
{
public:
    ~GEnumOutput();
	void						Set(UINT iIndex, IDXGIOutput* pAdapter);
    UINT						m_Output;
    IDXGIOutput*				m_pOutput;
    DXGI_OUTPUT_DESC			m_Desc;
	vector<DXGI_MODE_DESC>		m_DisplayModeList;    
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class GEnumDevice
{
public:

public:
    ~GEnumDevice();
    UINT						m_AdapterOrdinal;
	vector<GEnumOutput*>		m_OutputInfoList;
    D3D_DRIVER_TYPE				DeviceType;
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class GEnumAdapter
{  
public:
    ~GEnumAdapter();
	void					Set(UINT iIndex, IDXGIAdapter* pAdapter);
    UINT					m_AdapterOrdinal;
    DXGI_ADAPTER_DESC		m_AdapterDesc;
    IDXGIAdapter*			m_pAdapter;
    vector<GEnumOutput*>	m_OutputInfoList;
	vector<GEnumDevice*>	m_DeviceInfoList;
};
/*--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------*/
class GEnumeration
{
public:
	vector<GEnumAdapter*>	m_AdapterInfoList;	
public:
	HRESULT Enumerate(IDXGIFactory* pFactory);
	HRESULT EnumerateDevices( GEnumAdapter* pAdapterInfo );
	HRESULT EnumerateDisplayModes( GEnumOutput* pOutputInfo );
	HRESULT EnumerateOutputs( GEnumAdapter* pAdapterInfo );
	void	ClearAdapterInfoList();
public:
	GEnumeration(void);
	virtual ~GEnumeration(void);
};
