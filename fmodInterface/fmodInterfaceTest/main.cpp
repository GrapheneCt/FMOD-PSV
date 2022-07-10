#include <kernel.h>
#include <libsysmodule.h>
#include <libdbg.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fmod/fmod.h>
#include <fmod/fmod_output.h>
#include <fmod/fmod_errors.h>
#include <fmod/fmod.hpp>

int main(int argc, char *argv[])
{
	int err = 0;

	SCE_DBG_LOG_INFO("FMOD: Begin module load\n");

	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	sceSysmoduleLoadModule(SCE_SYSMODULE_SSL);
	sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

	err = sceKernelLoadStartModule("app0:module/pthread_nexcp.suprx", 0, NULL, 0, NULL, NULL);
	if (err <= 0) {
		SCE_DBG_LOG_ERROR("sceKernelLoadStartModule for pthread_nexcp.suprx: 0x%08X\n", err);
		abort();
	}

	err = sceKernelLoadStartModule("app0:module/fmod.suprx", 0, NULL, 0, NULL, NULL);
	if (err <= 0) {
		SCE_DBG_LOG_ERROR("sceKernelLoadStartModule for fmod.suprx: 0x%08X\n", err);
		abort();
	}

	err = sceKernelLoadStartModule("app0:module/fmodInterface.suprx", sizeof(SceUID), &err, 0, NULL, NULL);
	if (err <= 0) {
		SCE_DBG_LOG_ERROR("sceKernelLoadStartModule for fmodInterface.suprx: 0x%08X\n", err);
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD: Begin C API test\n");

	FMOD_SYSTEM *fsys;
	FMOD_RESULT err2;

	err2 = FMOD_System_Create(&fsys);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD_System_Create: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	unsigned int ver = 0;

	err2 = FMOD_System_GetVersion(fsys, &ver);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD_System_GetVersion: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD: system version is 0x%08X\n", ver);

	err2 = FMOD_System_Release(fsys);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD_System_Release: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD: Begin CPP API test\n");

	FMOD::System *cpp_fsys;

	err2 = FMOD::System_Create(&cpp_fsys);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System_Create: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	ver = 0;

	err2 = cpp_fsys->getVersion(&ver);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getVersion: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD: system version is 0x%08X\n", ver);

	err2 = cpp_fsys->release();
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::release: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD: All OK!\n");

	return 0;
}