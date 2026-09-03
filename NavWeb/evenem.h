
#include <exdispid.h>

// Définir les messages pour notre application:
#define BEFORENAVIGATE2       WM_USER
#define DOWNLOADBEGIN         WM_USER+1
#define DOWNLOADCOMPLETE      WM_USER+2
#define NAVIGATECOMPLETE2     WM_USER+3
#define DOCUMENTCOMPLETE      WM_USER+4
#define COMMANDSTATECHANGE    WM_USER+5

//************************* Classe de gestion des événements *****************************
class Evenem : public IDispatch 
{
	private:
	long ref;
	HWND fenetre;
	BSTR url;

	public:
	Evenem(HWND fenet)
	{
	fenetre=fenet;
	}

	~Evenem()
	{
	SysFreeString(url);
	}

	STDMETHODIMP QueryInterface(REFIID iid, void ** ppvObject)
	{
	if (iid==IID_IUnknown || iid==IID_IDispatch || iid==DIID_DWebBrowserEvents2)
		{
			*ppvObject=this; 
			AddRef(); 
			return S_OK;
		} 
	else return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{ 
	return InterlockedIncrement(&ref);  
	}

	ULONG STDMETHODCALLTYPE Release()
	{
	int tmp = InterlockedDecrement(&ref);
	if (tmp==0) delete this; 
	return tmp;
	}

	HRESULT STDMETHODCALLTYPE GetTypeInfoCount(unsigned int FAR* pctinfo)
	{ 
	return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetTypeInfo(unsigned int iTInfo, LCID  lcid, ITypeInfo FAR* FAR*  ppTInfo)
	{
	return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, unsigned int cNames, LCID lcid, DISPID FAR* rgDispId)
	{ 
	return E_NOTIMPL; 
	}

	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* parResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
	{
	IUnknown *pIUnk;
	VARIANT  *vurl ;

	if (!pDispParams) return E_INVALIDARG;
  
	switch (dispIdMember)
		{
		case DISPID_BEFORENAVIGATE2:
			// Détérminer l'objet courant:
			pIUnk=pDispParams->rgvarg[6].pdispVal;
			// Envoyer le message BEFORENAVIGATE2 à notre fenêtre:
			SendMessage(fenetre,BEFORENAVIGATE2,(WPARAM)pIUnk,0);
			break;

		case DISPID_DOWNLOADBEGIN:
			// Envoyer le message DOWNLOADBEGIN à notre fenêtre:
			SendMessage(fenetre,DOWNLOADBEGIN,0,0);
			break;

		case DISPID_DOWNLOADCOMPLETE:
			// Envoyer le message DOWNLOADCOMPLETE à notre fenêtre:
			SendMessage(fenetre,DOWNLOADCOMPLETE,0,0);
			break;

		case DISPID_NAVIGATECOMPLETE2:
			// Déterminer l'objet courant:
			pIUnk=pDispParams->rgvarg[1].pdispVal;
			// Récupérer l'URL courante:
			vurl= pDispParams->rgvarg[0].pvarVal;
			url = vurl->bstrVal;
			// Envoyer le message NAVIGATECOMPLETE2 à notre fenêtre:
			SendMessage(fenetre,NAVIGATECOMPLETE2,(WPARAM)pIUnk,(LPARAM)url);
			break;

		case DISPID_DOCUMENTCOMPLETE:
			// Déterminer l'objet courant:
			pIUnk=pDispParams->rgvarg[1].pdispVal;
			// Envoyer le message DOCUMENTCOMPLETE à notre fenêtre:
			SendMessage(fenetre,DOCUMENTCOMPLETE,(WPARAM)pIUnk,0);
			break;
			
		case DISPID_COMMANDSTATECHANGE:
			// Déterminer la commande dont l'état a changé:
			long command;
			command =pDispParams->rgvarg[1].lVal;
			// Déterminer le nouvel état de cette commande:
			VARIANT_BOOL etat;
			etat=pDispParams->rgvarg[0].boolVal;
			// Envoyer le message COMMANDESTATECHANGE à notre fenêtre:
			SendMessage(fenetre,COMMANDSTATECHANGE,(WPARAM)command,(LPARAM)etat);
			break;

		case DISPID_NEWWINDOW2:
			// Bloquer toutes les fenêtres popup:
			pDispParams->rgvarg[0].pvarVal->vt = VT_BOOL;
			pDispParams->rgvarg[0].pvarVal->boolVal = VARIANT_TRUE;
			break;

		default:
			break;
		}	
  return S_OK;
	}
};
//***********************************************************************************
