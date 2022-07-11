#include <kernel.h>
#include <libsysmodule.h>
#include <display.h>
#include <libdbg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <fmod/fmod.h>
#include <fmod/fmod_output.h>
#include <fmod/fmod_errors.h>
#include <fmod/fmodngp.h>
#include <fmod/fmod.hpp>

unsigned int sceLibcHeapSize = SCE_KERNEL_32MiB;

#define SOUND_PATH "app0:test.wav"

//#define SOUND_PATH "https://file-examples.com/storage/fe0a8978a262cb51f92368e/2017/11/file_example_MP3_700KB.mp3"

FMOD_RESULT F_CALLBACK FMODSystemCallback(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACKTYPE type, void *commanddata1, void *commanddata2)
{
	FMOD::System *sys = (FMOD::System *)system;

	switch (type)
	{
		case FMOD_SYSTEM_CALLBACKTYPE_DEVICELISTCHANGED:
		{
			int numdrivers;
			sys->getNumDrivers(&numdrivers);
			SCE_DBG_LOG_INFO("FMOD_SYSTEM_CALLBACKTYPE_DEVICELISTCHANGED, Numdevices = %d\n", numdrivers);
			break;
		}
		case FMOD_SYSTEM_CALLBACKTYPE_MEMORYALLOCATIONFAILED:
		{
			SCE_DBG_LOG_ERROR("FMOD_SYSTEM_CALLBACKTYPE_MEMORYALLOCATIONFAILED\n%s.\n%d bytes.\n", commanddata1, commanddata2);
			abort();
			break;
		}
		case FMOD_SYSTEM_CALLBACKTYPE_THREADCREATED:
		{
			SCE_DBG_LOG_INFO("FMOD_SYSTEM_CALLBACKTYPE_THREADCREATED occured.\nThread ID = %d\nThread Name = %s\n", (int)commanddata1, (char *)commanddata2);
			break;
		}
		case FMOD_SYSTEM_CALLBACKTYPE_BADDSPCONNECTION:
		{
			FMOD::DSP *source = (FMOD::DSP *)commanddata1;
			FMOD::DSP *dest = (FMOD::DSP *)commanddata2;
			SCE_DBG_LOG_ERROR("FMOD_SYSTEM_CALLBACKTYPE_BADDSPCONNECTION\n");
			if (source)
			{
				char name[256];
				source->getInfo(name, 0,0,0,0);
				printf("SOURCE = %s\n", name);
			}
			if (dest)
			{
				char name[256];
				dest->getInfo(name, 0,0,0,0);
				printf("DEST = %s\n", name);
			}
			break;
		}
	}

	return FMOD_OK;
}float F_CALLBACK FMODRolloffCallback(FMOD_CHANNEL *channel, float distance){	return 1.0f;}

void bootTest()
{
	FMOD_SYSTEM *fsys;
	FMOD_RESULT err2;

	SCE_DBG_LOG_INFO("FMOD BOOT TEST: Begin C API test\n");

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

	SCE_DBG_LOG_INFO("FMOD BOOT TEST: system version is 0x%08X\n", ver);

	err2 = FMOD_System_Release(fsys);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD_System_Release: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD BOOT TEST: Begin CPP API test\n");

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

	SCE_DBG_LOG_INFO("FMOD BOOT TEST: system version is 0x%08X\n", ver);

	err2 = cpp_fsys->release();
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::release: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD BOOT TEST: All OK!\n");
}

void playTest(const char *path)
{
	FMOD::System *fsys;
	FMOD_RESULT err2;

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: Begin init\n");

	err2 = FMOD::System_Create(&fsys);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System_Create: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	/*
	err2 = fsys->setFileSystem(FMODFileOpen, FMODFileClose, FMODFileRead, FMODFileSeek, NULL, NULL, -1);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setFileSystem: %s\n", FMOD_ErrorString(err2));
		abort();
	}
	*/

	err2 = fsys->setStreamBufferSize(SCE_KERNEL_64KiB, FMOD_TIMEUNIT_RAWBYTES);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setStreamBufferSize: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	err2 = fsys->setCallback(FMODSystemCallback);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setCallback: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	err2 = fsys->set3DRolloffCallback(FMODRolloffCallback);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::set3DRolloffCallback: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	err2 = fsys->setOutput(FMOD_OUTPUTTYPE_NGP);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setOutput: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	int numdrivers = 0;

	err2 = fsys->getNumDrivers(&numdrivers);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getNumDrivers: %s\n", FMOD_ErrorString(err2));
		abort();
	}
	if (numdrivers == 0) {
		SCE_DBG_LOG_ERROR("FMOD::System::getNumDrivers: no drivers detected\n");
		abort();
	}

	int driver = 0;
	int freq = 0;
	FMOD_CAPS caps = FMOD_CAPS_NONE;
	FMOD_SPEAKERMODE spmode = FMOD_SPEAKERMODE_FORCEINT;
	FMOD_GUID guid;
	char name[256];

	err2 = fsys->getDriver(&driver);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getDriver: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	err2 = fsys->getDriverCaps(driver, &caps, &freq, &spmode);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getDriverCaps: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	err2 = fsys->getDriverInfo(driver, name, sizeof(name), &guid);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getDriverInfo: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: Driver info\n");
	printf("name: %s\n", name);
	printf("frequency: %d\n", freq);
	printf("speaker mode: ");
	switch (spmode)
	{
	case FMOD_SPEAKERMODE_RAW:
		printf("FMOD_SPEAKERMODE_RAW");
		break;
	case FMOD_SPEAKERMODE_MONO:
		printf("FMOD_SPEAKERMODE_MONO");
		break;
	case FMOD_SPEAKERMODE_STEREO:
		printf("FMOD_SPEAKERMODE_STEREO");
		break;
	case FMOD_SPEAKERMODE_QUAD:
		printf("FMOD_SPEAKERMODE_QUAD");
		break;
	case FMOD_SPEAKERMODE_SURROUND:
		printf("FMOD_SPEAKERMODE_SURROUND");
		break;
	case FMOD_SPEAKERMODE_5POINT1:
		printf("FMOD_SPEAKERMODE_5POINT1");
		break;
	case FMOD_SPEAKERMODE_7POINT1:
		printf("FMOD_SPEAKERMODE_7POINT1");
		break;
	case FMOD_SPEAKERMODE_SRS5_1_MATRIX:
		printf("FMOD_SPEAKERMODE_SRS5_1_MATRIX");
		break;
	case FMOD_SPEAKERMODE_DOLBY5_1_MATRIX:
		printf("FMOD_SPEAKERMODE_DOLBY5_1_MATRIX");
		break;
	case FMOD_SPEAKERMODE_MYEARS:
		printf("FMOD_SPEAKERMODE_MYEARS");
		break;
	}
	printf("\n");

	printf("caps: ");
	if (caps & FMOD_CAPS_HARDWARE) {
		printf("FMOD_CAPS_HARDWARE | ");
	}
	if (caps & FMOD_CAPS_HARDWARE_EMULATED) {
		printf("FMOD_CAPS_HARDWARE_EMULATED | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_MULTICHANNEL) {
		printf("FMOD_CAPS_OUTPUT_MULTICHANNEL | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_FORMAT_PCM8) {
		printf("FMOD_CAPS_OUTPUT_FORMAT_PCM8 | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_FORMAT_PCM16) {
		printf("FMOD_CAPS_OUTPUT_FORMAT_PCM16 | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_FORMAT_PCM24) {
		printf("FMOD_CAPS_OUTPUT_FORMAT_PCM24 | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_FORMAT_PCM32) {
		printf("FMOD_CAPS_OUTPUT_FORMAT_PCM32 | ");
	}
	if (caps & FMOD_CAPS_OUTPUT_FORMAT_PCMFLOAT) {
		printf("FMOD_CAPS_OUTPUT_FORMAT_PCMFLOAT | ");
	}
	if (caps & FMOD_CAPS_LOOPBACK) {
		printf("FMOD_CAPS_LOOPBACK");
	}
	printf("\n\n");

	err2 = fsys->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setSpeakerMode: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	unsigned int bufferlength = 0;
	int numbuffers = 0;

	err2 = fsys->getDSPBufferSize(&bufferlength, &numbuffers);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getDSPBufferSize: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: DSP buffer info\n");
	printf("bufferlength: %d\n", bufferlength);
	printf("numbuffers: %d\n\n", numbuffers);

	int samplerate = 0;
	int numoutputchannels = 0;
	int maxinputchannels = 0;
	int bits = 0;
	FMOD_SOUND_FORMAT format = FMOD_SOUND_FORMAT_NONE;
	FMOD_DSP_RESAMPLER resamplemethod = FMOD_DSP_RESAMPLER_FORCEINT;

	err2 = fsys->getSoftwareFormat(&samplerate, &format, &numoutputchannels, &maxinputchannels, &resamplemethod, &bits);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getSoftwareFormat: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: Software format info\n");
	printf("samplerate: %d\n", samplerate);
	printf("numoutputchannels: %d\n", numoutputchannels);
	printf("maxinputchannels: %d\n", maxinputchannels);
	printf("bits: %d\n", bits);

	printf("format: ");
	switch (format)
	{
	case FMOD_SOUND_FORMAT_PCM8:
		printf("FMOD_SOUND_FORMAT_PCM8");
		break;
	case FMOD_SOUND_FORMAT_PCM16:
		printf("FMOD_SOUND_FORMAT_PCM16");
		break;
	case FMOD_SOUND_FORMAT_PCM24:
		printf("FMOD_SOUND_FORMAT_PCM24");
		break;
	case FMOD_SOUND_FORMAT_PCM32:
		printf("FMOD_SOUND_FORMAT_PCM32");
		break;
	case FMOD_SOUND_FORMAT_PCMFLOAT:
		printf("FMOD_SOUND_FORMAT_PCMFLOAT");
		break;
	case FMOD_SOUND_FORMAT_GCADPCM:
		printf("FMOD_SOUND_FORMAT_GCADPCM");
		break;
	case FMOD_SOUND_FORMAT_IMAADPCM:
		printf("FMOD_SOUND_FORMAT_IMAADPCM");
		break;
	case FMOD_SOUND_FORMAT_VAG:
		printf("FMOD_SOUND_FORMAT_VAG");
		break;
	case FMOD_SOUND_FORMAT_HEVAG:
		printf("FMOD_SOUND_FORMAT_HEVAG");
		break;
	case FMOD_SOUND_FORMAT_XMA:
		printf("FMOD_SOUND_FORMAT_XMA");
		break;
	case FMOD_SOUND_FORMAT_MPEG:
		printf("FMOD_SOUND_FORMAT_MPEG");
		break;
	case FMOD_SOUND_FORMAT_CELT:
		printf("FMOD_SOUND_FORMAT_CELT");
		break;
	case FMOD_SOUND_FORMAT_AT9:
		printf("FMOD_SOUND_FORMAT_AT9");
		break;
	case FMOD_SOUND_FORMAT_XWMA:
		printf("FMOD_SOUND_FORMAT_XWMA");
		break;
	case FMOD_SOUND_FORMAT_VORBIS:
		printf("FMOD_SOUND_FORMAT_VORBIS");
		break;
	}
	printf("\n");

	printf("resamplemethod: ");
	switch (resamplemethod)
	{
	case FMOD_DSP_RESAMPLER_NOINTERP:
		printf("FMOD_DSP_RESAMPLER_NOINTERP");
		break;
	case FMOD_DSP_RESAMPLER_LINEAR:
		printf("FMOD_DSP_RESAMPLER_LINEAR");
		break;
	case FMOD_DSP_RESAMPLER_CUBIC:
		printf("FMOD_DSP_RESAMPLER_CUBIC");
		break;
	case FMOD_DSP_RESAMPLER_SPLINE:
		printf("FMOD_DSP_RESAMPLER_SPLINE");
		break;
	}
	printf("\n\n");

	err2 = fsys->setSoftwareFormat(samplerate, format, 0, 2, resamplemethod);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::setSoftwareFormat: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	int numsoftwarechannels = 0;

	err2 = fsys->getSoftwareChannels(&numsoftwarechannels);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getSoftwareChannels: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: Software channel num: %d\n", numsoftwarechannels);

	err2 = fsys->init(30, FMOD_INIT_NORMAL, NULL);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::init: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	FMOD::ChannelGroup *mastergroup;

	err2 = fsys->getMasterChannelGroup(&mastergroup);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getMasterChannelGroup: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	int codecNum = 0;

	err2 = fsys->getNumPlugins(FMOD_PLUGINTYPE_CODEC, &codecNum);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::getNumPlugins: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: Codec info\n");

	unsigned int handle = 0;
	unsigned int ver = 0;
	FMOD_PLUGINTYPE type;

	for (int i = 0; i < codecNum; i++) {
		memset(name, 0, sizeof(name));
		fsys->getPluginHandle(FMOD_PLUGINTYPE_CODEC, i, &handle);
		fsys->getPluginInfo(handle, &type, name, sizeof(name), &ver);
		printf("name: %s\n", name);
		printf("ver: 0x%08X\n", ver);
	}

	printf("\n\n");

	FMOD::Sound *snd;

	err2 = fsys->createSound(path, FMOD_DEFAULT, NULL, &snd);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::createSound: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	FMOD::Channel *ch;

	err2 = fsys->playSound(FMOD_CHANNEL_FREE, snd, false, &ch);
	if (err2 != FMOD_OK) {
		SCE_DBG_LOG_ERROR("FMOD::System::playSound: %s\n", FMOD_ErrorString(err2));
		abort();
	}

	SCE_DBG_LOG_INFO("FMOD PLAY TEST: All OK! Begin sound playback\n");

	while (1) {
		fsys->update();
		sceDisplayWaitVblankStart();
	}
}

int main(int argc, char *argv[])
{
	int err = 0;

	SCE_DBG_LOG_INFO("FMOD: Begin module load\n");

	err = sceKernelLoadStartModule("app0:module/fmodex.suprx", 0, NULL, 0, NULL, NULL);
	if (err <= 0) {
		SCE_DBG_LOG_ERROR("sceKernelLoadStartModule for fmodex.suprx: 0x%08X\n", err);
		abort();
	}

	err = sceKernelLoadStartModule("app0:module/fmodInterface.suprx", sizeof(SceUID), &err, 0, NULL, NULL);
	if (err <= 0) {
		SCE_DBG_LOG_ERROR("sceKernelLoadStartModule for fmodInterface.suprx: 0x%08X\n", err);
		abort();
	}

	bootTest();
	playTest(SOUND_PATH);

	return 0;
}