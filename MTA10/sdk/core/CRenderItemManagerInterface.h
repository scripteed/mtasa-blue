/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        CRenderItemManagerInterface.h
*  PURPOSE:
*  DEVELOPERS:  idiot
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

struct ID3DXFont;
struct IDirect3DTexture9;
class CGUIFont;
struct SRenderItem;
struct SFontItem;
struct STextureItem;


//
// CRenderItemManagerInterface
//
// Interface for client module
//
class CRenderItemManagerInterface
{
public:
    virtual                     ~CRenderItemManagerInterface    ( void ) {}

    // CRenderItemManagerInterface
    virtual SFontItem*          CreateFont                  ( const SString& strFullFilePath, const SString& strFontName, uint uiSize, bool bBold ) = 0;
    virtual STextureItem*       CreateTexture               ( const SString& strFullFilePath ) = 0;
    virtual void                ReleaseRenderItem           ( SRenderItem* pItem ) = 0;
};



//
// SRenderItem + derived class
//
// Render item is the core's version of something renderable
//
enum eRenderItemClassTypes
{
    CLASS_SRenderItem,
    CLASS_SFontItem,
    CLASS_SMaterialItem,
    CLASS_STextureItem,
};

struct SRenderItem
{
    DECLARE_BASE_CLASS( SRenderItem )
    SRenderItem  ( void ) : ClassInit ( this ) {}
    void Release ( void ) { pManager->ReleaseRenderItem ( this ); }
    void AddRef  ( void ) { ++iRefCount; }

    CRenderItemManagerInterface* pManager;
    int             iRefCount;
};

struct SFontItem : public SRenderItem
{
    DECLARE_CLASS( SFontItem, SRenderItem )
    SFontItem ( void ) : ClassInit ( this ) {}

    SString         strCEGUIFontName;
    CGUIFont*       pFntCEGUI;
    SString         strFullFilePath;
    ID3DXFont*      pFntNormal;
    ID3DXFont*      pFntBig;
};

struct SMaterialItem : public SRenderItem
{
    DECLARE_CLASS( SMaterialItem, SRenderItem )
    SMaterialItem ( void ) : ClassInit ( this ) {}
};

struct STextureItem : public SMaterialItem
{
    DECLARE_CLASS( STextureItem, SMaterialItem )
    STextureItem ( void ) : ClassInit ( this ) {}

    IDirect3DTexture9* pD3DTexture;
    uint uiFileWidth;
    uint uiFileHeight;
    uint uiSurfaceWidth;
    uint uiSurfaceHeight;
};
