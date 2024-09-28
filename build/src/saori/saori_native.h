//---------------------------------------------------------------------------
//
// "������" for ����ʳ��β����ʳ��β���
// SAORI ���󥿡��ե�����(native�⥸�塼��)
//
//      Programed by Suikyo.
//
//  2003.02.25  Phase 8.1.0   Ƴ��
//
//---------------------------------------------------------------------------
#ifndef SAORI_NATIVE_H
#define SAORI_NATIVE_H
//---------------------------------------------------------------------------
#include "config.h"
#include "saori/saori_module.h"
#include "include/shiori.h"
//---------------------------------------------------------------------------
#include <string>
#include <map>
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(__CYGWIN__)
#else
#include <cstring>
#include <libgen.h>
#endif // Windows
//---------------------------------------------------------------------------
namespace saori{
//---------------------------------------------------------------------------
class TModuleFactoryNative : public IModuleFactory{
public:
	// �⥸�塼��θ���������
	// �����: ����������������硢���󥹥��󥹡����Ԥ�����硢NULL��
	virtual TModule *CreateModule(const std::string &path);

	// �⥸�塼��δ����˴�
	virtual void DeleteModule(TModule *module);

	// ���󥹥ȥ饯��
	TModuleFactoryNative(class TKawariLogger &lgr);

	// �ǥ��ȥ饯��
	virtual ~TModuleFactoryNative(void);
};
//---------------------------------------------------------------------------
class TModuleNative : public TModule{
public:
	// �����
	virtual bool Initialize(void);
	// SAORI/1.0 Load
	virtual bool Load(void);
	// SAORI/1.0 Unload
	virtual bool Unload(void);
	// SAORI/1.0 Request
	virtual std::string Request(const std::string &reqstr);

protected:
	TModuleNative(TModuleFactoryNative &fac, const std::string &p, SAORI_HANDLE handle)
		 : TModule(fac, p, handle) {
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(__CYGWIN__)
#else
         char *path = strdup(p.c_str());
         filename = basename(path);
         free(path);
         auto pos = filename.rfind(".dll");
         if (pos != decltype(filename)::npos) {
             filename = filename.substr(0, pos);
         }
#endif // Windows
     }

#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(__CYGWIN__)
	BOOL	(SHIORI_CALL *func_load)(MEMORY_HANDLE, long);
	BOOL	(SHIORI_CALL *func_unload)(void);
	MEMORY_HANDLE	(SHIORI_CALL *func_request)(MEMORY_HANDLE, long *);
#else
	long	(SHIORI_CALL *func_load)(MEMORY_HANDLE, long);
	int	(SHIORI_CALL *func_unload)(long);
	MEMORY_HANDLE	(SHIORI_CALL *func_request)(long, MEMORY_HANDLE, long *);
#endif // Windows

	friend class TModuleFactoryNative;
#if defined(WIN32)||defined(_WIN32)||defined(_Windows)||defined(__CYGWIN__)
#else
private:
    long id;
    std::string filename;
#endif // Windows
};
//---------------------------------------------------------------------------
} // namespace saori
//---------------------------------------------------------------------------
#endif // SAORI_NATIVE_H
//---------------------------------------------------------------------------
