#include <moduleinfo.h>
#include <kernel.h>
#include <stdbool.h>

#include <fmod/fmod.h>
#include <fmod/fmod_output.h>

#include "init_array.h"

#define MODULE_BASE_ADDRESS		(0x81000000)
#define DECODE_OFFSET(x)		(s_textBase + x)

static SceUInt32 s_textBase;

FMOD_RESULT(*cFMOD_Memory_Initialize)(void *poolmem, int poollen, FMOD_MEMORY_ALLOCCALLBACK useralloc, FMOD_MEMORY_REALLOCCALLBACK userrealloc, FMOD_MEMORY_FREECALLBACK userfree, FMOD_MEMORY_TYPE memtypeflags);
FMOD_RESULT(*cFMOD_Memory_GetStats)(int *currentalloced, int *maxalloced, FMOD_BOOL blocking);
FMOD_RESULT(*cFMOD_Debug_SetLevel)(FMOD_DEBUGLEVEL level);
FMOD_RESULT(*cFMOD_Debug_GetLevel)(FMOD_DEBUGLEVEL *level);
FMOD_RESULT(*cFMOD_File_SetDiskBusy)(int busy);
FMOD_RESULT(*cFMOD_File_GetDiskBusy)(int *busy);

FMOD_RESULT(*cFMOD_System_Create)(FMOD_SYSTEM **system);
FMOD_RESULT(*cFMOD_System_Release)(FMOD_SYSTEM *system);

FMOD_RESULT(*cFMOD_System_SetOutput)(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output);
FMOD_RESULT(*cFMOD_System_GetOutput)(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output);
FMOD_RESULT(*cFMOD_System_GetNumDrivers)(FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT(*cFMOD_System_GetDriverInfo)(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cFMOD_System_GetDriverInfoW)(FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cFMOD_System_GetDriverCaps)(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *controlpaneloutputrate, FMOD_SPEAKERMODE *controlpanelspeakermode);
FMOD_RESULT(*cFMOD_System_SetDriver)(FMOD_SYSTEM *system, int driver);
FMOD_RESULT(*cFMOD_System_GetDriver)(FMOD_SYSTEM *system, int *driver);
FMOD_RESULT(*cFMOD_System_SetHardwareChannels)(FMOD_SYSTEM *system, int numhardwarechannels);
FMOD_RESULT(*cFMOD_System_SetSoftwareChannels)(FMOD_SYSTEM *system, int numsoftwarechannels);
FMOD_RESULT(*cFMOD_System_GetSoftwareChannels)(FMOD_SYSTEM *system, int *numsoftwarechannels);
FMOD_RESULT(*cFMOD_System_SetSoftwareFormat)(FMOD_SYSTEM *system, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod);
FMOD_RESULT(*cFMOD_System_GetSoftwareFormat)(FMOD_SYSTEM *system, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits);
FMOD_RESULT(*cFMOD_System_SetDSPBufferSize)(FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers);
FMOD_RESULT(*cFMOD_System_GetDSPBufferSize)(FMOD_SYSTEM *system, unsigned int *bufferlength, int *numbuffers);
FMOD_RESULT(*cFMOD_System_SetFileSystem)(FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, FMOD_FILE_ASYNCREADCALLBACK userasyncread, FMOD_FILE_ASYNCCANCELCALLBACK userasynccancel, int blockalign);
FMOD_RESULT(*cFMOD_System_AttachFileSystem)(FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek);
FMOD_RESULT(*cFMOD_System_SetAdvancedSettings)(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT(*cFMOD_System_GetAdvancedSettings)(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT(*cFMOD_System_SetSpeakerMode)(FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode);
FMOD_RESULT(*cFMOD_System_GetSpeakerMode)(FMOD_SYSTEM *system, FMOD_SPEAKERMODE *speakermode);
FMOD_RESULT(*cFMOD_System_SetCallback)(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK callback);

FMOD_RESULT(*cFMOD_System_SetPluginPath)(FMOD_SYSTEM *system, const char *path);
FMOD_RESULT(*cFMOD_System_LoadPlugin)(FMOD_SYSTEM *system, const char *filename, unsigned int *handle, unsigned int priority);
FMOD_RESULT(*cFMOD_System_UnloadPlugin)(FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT(*cFMOD_System_GetNumPlugins)(FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int *numplugins);
FMOD_RESULT(*cFMOD_System_GetPluginHandle)(FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle);
FMOD_RESULT(*cFMOD_System_GetPluginInfo)(FMOD_SYSTEM *system, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version);
FMOD_RESULT(*cFMOD_System_SetOutputByPlugin)(FMOD_SYSTEM *system, unsigned int handle);
FMOD_RESULT(*cFMOD_System_GetOutputByPlugin)(FMOD_SYSTEM *system, unsigned int *handle);
FMOD_RESULT(*cFMOD_System_CreateDSPByPlugin)(FMOD_SYSTEM *system, unsigned int handle, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_System_RegisterCodec)(FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority);
FMOD_RESULT(*cFMOD_System_RegisterDSP)(FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, unsigned int *handle);

FMOD_RESULT(*cFMOD_System_Init)(FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT(*cFMOD_System_Close)(FMOD_SYSTEM *system);

FMOD_RESULT(*cFMOD_System_Update)(FMOD_SYSTEM *system);

FMOD_RESULT(*cFMOD_System_Set3DSettings)(FMOD_SYSTEM *system, float dopplerscale, float distancefactor, float rolloffscale);
FMOD_RESULT(*cFMOD_System_Get3DSettings)(FMOD_SYSTEM *system, float *dopplerscale, float *distancefactor, float *rolloffscale);
FMOD_RESULT(*cFMOD_System_Set3DNumListeners)(FMOD_SYSTEM *system, int numlisteners);
FMOD_RESULT(*cFMOD_System_Get3DNumListeners)(FMOD_SYSTEM *system, int *numlisteners);
FMOD_RESULT(*cFMOD_System_Set3DListenerAttributes)(FMOD_SYSTEM *system, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT(*cFMOD_System_Get3DListenerAttributes)(FMOD_SYSTEM *system, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT(*cFMOD_System_Set3DRolloffCallback)(FMOD_SYSTEM *system, FMOD_3D_ROLLOFFCALLBACK callback);
FMOD_RESULT(*cFMOD_System_Set3DSpeakerPosition)(FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float x, float y, FMOD_BOOL active);
FMOD_RESULT(*cFMOD_System_Get3DSpeakerPosition)(FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float *x, float *y, FMOD_BOOL *active);

FMOD_RESULT(*cFMOD_System_SetStreamBufferSize)(FMOD_SYSTEM *system, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
FMOD_RESULT(*cFMOD_System_GetStreamBufferSize)(FMOD_SYSTEM *system, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);

FMOD_RESULT(*cFMOD_System_GetVersion)(FMOD_SYSTEM *system, unsigned int *version);
FMOD_RESULT(*cFMOD_System_GetOutputHandle)(FMOD_SYSTEM *system, void **handle);
FMOD_RESULT(*cFMOD_System_GetChannelsPlaying)(FMOD_SYSTEM *system, int *channels);
FMOD_RESULT(*cFMOD_System_GetHardwareChannels)(FMOD_SYSTEM *system, int *numhardwarechannels);
FMOD_RESULT(*cFMOD_System_GetCPUUsage)(FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total);
FMOD_RESULT(*cFMOD_System_GetSoundRAM)(FMOD_SYSTEM *system, int *currentalloced, int *maxalloced, int *total);
FMOD_RESULT(*cFMOD_System_GetNumCDROMDrives)(FMOD_SYSTEM *system, int *numdrives);
FMOD_RESULT(*cFMOD_System_GetCDROMDriveName)(FMOD_SYSTEM *system, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen);
FMOD_RESULT(*cFMOD_System_GetSpectrum)(FMOD_SYSTEM *system, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cFMOD_System_GetWaveData)(FMOD_SYSTEM *system, float *wavearray, int numvalues, int channeloffset);

FMOD_RESULT(*cFMOD_System_CreateSound)(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT(*cFMOD_System_CreateStream)(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT(*cFMOD_System_CreateDSP)(FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_System_CreateDSPByType)(FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_System_CreateChannelGroup)(FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT(*cFMOD_System_CreateSoundGroup)(FMOD_SYSTEM *system, const char *name, FMOD_SOUNDGROUP **soundgroup);
FMOD_RESULT(*cFMOD_System_CreateReverb)(FMOD_SYSTEM *system, FMOD_REVERB **reverb);

FMOD_RESULT(*cFMOD_System_PlaySound)(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT(*cFMOD_System_PlayDSP)(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_DSP *dsp, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT(*cFMOD_System_GetChannel)(FMOD_SYSTEM *system, int channelid, FMOD_CHANNEL **channel);
FMOD_RESULT(*cFMOD_System_GetMasterChannelGroup)(FMOD_SYSTEM *system, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT(*cFMOD_System_GetMasterSoundGroup)(FMOD_SYSTEM *system, FMOD_SOUNDGROUP **soundgroup);

FMOD_RESULT(*cFMOD_System_SetReverbProperties)(FMOD_SYSTEM *system, const FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cFMOD_System_GetReverbProperties)(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cFMOD_System_SetReverbAmbientProperties)(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cFMOD_System_GetReverbAmbientProperties)(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);

FMOD_RESULT(*cFMOD_System_GetDSPHead)(FMOD_SYSTEM *system, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_System_AddDSP)(FMOD_SYSTEM *system, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);
FMOD_RESULT(*cFMOD_System_LockDSP)(FMOD_SYSTEM *system);
FMOD_RESULT(*cFMOD_System_UnlockDSP)(FMOD_SYSTEM *system);
FMOD_RESULT(*cFMOD_System_GetDSPClock)(FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo);

FMOD_RESULT(*cFMOD_System_GetRecordNumDrivers)(FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT(*cFMOD_System_GetRecordDriverInfo)(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cFMOD_System_GetRecordDriverInfoW)(FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cFMOD_System_GetRecordDriverCaps)(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency);
FMOD_RESULT(*cFMOD_System_GetRecordPosition)(FMOD_SYSTEM *system, int id, unsigned int *position);

FMOD_RESULT(*cFMOD_System_RecordStart)(FMOD_SYSTEM *system, int id, FMOD_SOUND *sound, FMOD_BOOL loop);
FMOD_RESULT(*cFMOD_System_RecordStop)(FMOD_SYSTEM *system, int id);
FMOD_RESULT(*cFMOD_System_IsRecording)(FMOD_SYSTEM *system, int id, FMOD_BOOL *recording);

FMOD_RESULT(*cFMOD_System_CreateGeometry)(FMOD_SYSTEM *system, int maxpolygons, int maxvertices, FMOD_GEOMETRY **geometry);
FMOD_RESULT(*cFMOD_System_SetGeometrySettings)(FMOD_SYSTEM *system, float maxworldsize);
FMOD_RESULT(*cFMOD_System_GetGeometrySettings)(FMOD_SYSTEM *system, float *maxworldsize);
FMOD_RESULT(*cFMOD_System_LoadGeometry)(FMOD_SYSTEM *system, const void *data, int datasize, FMOD_GEOMETRY **geometry);
FMOD_RESULT(*cFMOD_System_GetGeometryOcclusion)(FMOD_SYSTEM *system, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb);

FMOD_RESULT(*cFMOD_System_SetNetworkProxy)(FMOD_SYSTEM *system, const char *proxy);
FMOD_RESULT(*cFMOD_System_GetNetworkProxy)(FMOD_SYSTEM *system, char *proxy, int proxylen);
FMOD_RESULT(*cFMOD_System_SetNetworkTimeout)(FMOD_SYSTEM *system, int timeout);
FMOD_RESULT(*cFMOD_System_GetNetworkTimeout)(FMOD_SYSTEM *system, int *timeout);

FMOD_RESULT(*cFMOD_System_SetUserData)(FMOD_SYSTEM *system, void *userdata);
FMOD_RESULT(*cFMOD_System_GetUserData)(FMOD_SYSTEM *system, void **userdata);

FMOD_RESULT(*cFMOD_System_GetMemoryInfo)(FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_Sound_Release)(FMOD_SOUND *sound);
FMOD_RESULT(*cFMOD_Sound_GetSystemObject)(FMOD_SOUND *sound, FMOD_SYSTEM **system);

FMOD_RESULT(*cFMOD_Sound_Lock)(FMOD_SOUND *sound, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
FMOD_RESULT(*cFMOD_Sound_Unlock)(FMOD_SOUND *sound, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
FMOD_RESULT(*cFMOD_Sound_SetDefaults)(FMOD_SOUND *sound, float frequency, float volume, float pan, int priority);
FMOD_RESULT(*cFMOD_Sound_GetDefaults)(FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority);
FMOD_RESULT(*cFMOD_Sound_SetVariations)(FMOD_SOUND *sound, float frequencyvar, float volumevar, float panvar);
FMOD_RESULT(*cFMOD_Sound_GetVariations)(FMOD_SOUND *sound, float *frequencyvar, float *volumevar, float *panvar);
FMOD_RESULT(*cFMOD_Sound_Set3DMinMaxDistance)(FMOD_SOUND *sound, float min, float max);
FMOD_RESULT(*cFMOD_Sound_Get3DMinMaxDistance)(FMOD_SOUND *sound, float *min, float *max);
FMOD_RESULT(*cFMOD_Sound_Set3DConeSettings)(FMOD_SOUND *sound, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT(*cFMOD_Sound_Get3DConeSettings)(FMOD_SOUND *sound, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT(*cFMOD_Sound_Set3DCustomRolloff)(FMOD_SOUND *sound, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT(*cFMOD_Sound_Get3DCustomRolloff)(FMOD_SOUND *sound, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT(*cFMOD_Sound_SetSubSound)(FMOD_SOUND *sound, int index, FMOD_SOUND *subsound);
FMOD_RESULT(*cFMOD_Sound_GetSubSound)(FMOD_SOUND *sound, int index, FMOD_SOUND **subsound);
FMOD_RESULT(*cFMOD_Sound_GetSubSoundParent)(FMOD_SOUND *sound, FMOD_SOUND **parentsound);
FMOD_RESULT(*cFMOD_Sound_SetSubSoundSentence)(FMOD_SOUND *sound, int *subsoundlist, int numsubsounds);
FMOD_RESULT(*cFMOD_Sound_GetName)(FMOD_SOUND *sound, char *name, int namelen);
FMOD_RESULT(*cFMOD_Sound_GetLength)(FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);
FMOD_RESULT(*cFMOD_Sound_GetFormat)(FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
FMOD_RESULT(*cFMOD_Sound_GetNumSubSounds)(FMOD_SOUND *sound, int *numsubsounds);
FMOD_RESULT(*cFMOD_Sound_GetNumTags)(FMOD_SOUND *sound, int *numtags, int *numtagsupdated);
FMOD_RESULT(*cFMOD_Sound_GetTag)(FMOD_SOUND *sound, const char *name, int index, FMOD_TAG *tag);
FMOD_RESULT(*cFMOD_Sound_GetOpenState)(FMOD_SOUND *sound, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, FMOD_BOOL *starving, FMOD_BOOL *diskbusy);
FMOD_RESULT(*cFMOD_Sound_ReadData)(FMOD_SOUND *sound, void *buffer, unsigned int lenbytes, unsigned int *read);
FMOD_RESULT(*cFMOD_Sound_SeekData)(FMOD_SOUND *sound, unsigned int pcm);

FMOD_RESULT(*cFMOD_Sound_SetSoundGroup)(FMOD_SOUND *sound, FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT(*cFMOD_Sound_GetSoundGroup)(FMOD_SOUND *sound, FMOD_SOUNDGROUP **soundgroup);

FMOD_RESULT(*cFMOD_Sound_GetNumSyncPoints)(FMOD_SOUND *sound, int *numsyncpoints);
FMOD_RESULT(*cFMOD_Sound_GetSyncPoint)(FMOD_SOUND *sound, int index, FMOD_SYNCPOINT **point);
FMOD_RESULT(*cFMOD_Sound_GetSyncPointInfo)(FMOD_SOUND *sound, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
FMOD_RESULT(*cFMOD_Sound_AddSyncPoint)(FMOD_SOUND *sound, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
FMOD_RESULT(*cFMOD_Sound_DeleteSyncPoint)(FMOD_SOUND *sound, FMOD_SYNCPOINT *point);

FMOD_RESULT(*cFMOD_Sound_SetMode)(FMOD_SOUND *sound, FMOD_MODE mode);
FMOD_RESULT(*cFMOD_Sound_GetMode)(FMOD_SOUND *sound, FMOD_MODE *mode);
FMOD_RESULT(*cFMOD_Sound_SetLoopCount)(FMOD_SOUND *sound, int loopcount);
FMOD_RESULT(*cFMOD_Sound_GetLoopCount)(FMOD_SOUND *sound, int *loopcount);
FMOD_RESULT(*cFMOD_Sound_SetLoopPoints)(FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cFMOD_Sound_GetLoopPoints)(FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

FMOD_RESULT(*cFMOD_Sound_GetMusicNumChannels)(FMOD_SOUND *sound, int *numchannels);
FMOD_RESULT(*cFMOD_Sound_SetMusicChannelVolume)(FMOD_SOUND *sound, int channel, float volume);
FMOD_RESULT(*cFMOD_Sound_GetMusicChannelVolume)(FMOD_SOUND *sound, int channel, float *volume);
FMOD_RESULT(*cFMOD_Sound_SetMusicSpeed)(FMOD_SOUND *sound, float speed);
FMOD_RESULT(*cFMOD_Sound_GetMusicSpeed)(FMOD_SOUND *sound, float *speed);

FMOD_RESULT(*cFMOD_Sound_SetUserData)(FMOD_SOUND *sound, void *userdata);
FMOD_RESULT(*cFMOD_Sound_GetUserData)(FMOD_SOUND *sound, void **userdata);

FMOD_RESULT(*cFMOD_Sound_GetMemoryInfo)(FMOD_SOUND *sound, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_Channel_GetSystemObject)(FMOD_CHANNEL *channel, FMOD_SYSTEM **system);

FMOD_RESULT(*cFMOD_Channel_Stop)(FMOD_CHANNEL *channel);
FMOD_RESULT(*cFMOD_Channel_SetPaused)(FMOD_CHANNEL *channel, FMOD_BOOL paused);
FMOD_RESULT(*cFMOD_Channel_GetPaused)(FMOD_CHANNEL *channel, FMOD_BOOL *paused);
FMOD_RESULT(*cFMOD_Channel_SetVolume)(FMOD_CHANNEL *channel, float volume);
FMOD_RESULT(*cFMOD_Channel_GetVolume)(FMOD_CHANNEL *channel, float *volume);
FMOD_RESULT(*cFMOD_Channel_SetFrequency)(FMOD_CHANNEL *channel, float frequency);
FMOD_RESULT(*cFMOD_Channel_GetFrequency)(FMOD_CHANNEL *channel, float *frequency);
FMOD_RESULT(*cFMOD_Channel_SetPan)(FMOD_CHANNEL *channel, float pan);
FMOD_RESULT(*cFMOD_Channel_GetPan)(FMOD_CHANNEL *channel, float *pan);
FMOD_RESULT(*cFMOD_Channel_SetDelay)(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo);
FMOD_RESULT(*cFMOD_Channel_GetDelay)(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo);
FMOD_RESULT(*cFMOD_Channel_SetSpeakerMix)(FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
FMOD_RESULT(*cFMOD_Channel_GetSpeakerMix)(FMOD_CHANNEL *channel, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright);
FMOD_RESULT(*cFMOD_Channel_SetSpeakerLevels)(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cFMOD_Channel_GetSpeakerLevels)(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cFMOD_Channel_SetInputChannelMix)(FMOD_CHANNEL *channel, float *levels, int numlevels);
FMOD_RESULT(*cFMOD_Channel_GetInputChannelMix)(FMOD_CHANNEL *channel, float *levels, int numlevels);
FMOD_RESULT(*cFMOD_Channel_SetMute)(FMOD_CHANNEL *channel, FMOD_BOOL mute);
FMOD_RESULT(*cFMOD_Channel_GetMute)(FMOD_CHANNEL *channel, FMOD_BOOL *mute);
FMOD_RESULT(*cFMOD_Channel_SetPriority)(FMOD_CHANNEL *channel, int priority);
FMOD_RESULT(*cFMOD_Channel_GetPriority)(FMOD_CHANNEL *channel, int *priority);
FMOD_RESULT(*cFMOD_Channel_SetPosition)(FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);
FMOD_RESULT(*cFMOD_Channel_GetPosition)(FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);
FMOD_RESULT(*cFMOD_Channel_SetReverbProperties)(FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cFMOD_Channel_GetReverbProperties)(FMOD_CHANNEL *channel, FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cFMOD_Channel_SetLowPassGain)(FMOD_CHANNEL *channel, float gain);
FMOD_RESULT(*cFMOD_Channel_GetLowPassGain)(FMOD_CHANNEL *channel, float *gain);

FMOD_RESULT(*cFMOD_Channel_SetChannelGroup)(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT(*cFMOD_Channel_GetChannelGroup)(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT(*cFMOD_Channel_SetCallback)(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACK callback);

FMOD_RESULT(*cFMOD_Channel_Set3DAttributes)(FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT(*cFMOD_Channel_Get3DAttributes)(FMOD_CHANNEL *channel, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT(*cFMOD_Channel_Set3DMinMaxDistance)(FMOD_CHANNEL *channel, float mindistance, float maxdistance);
FMOD_RESULT(*cFMOD_Channel_Get3DMinMaxDistance)(FMOD_CHANNEL *channel, float *mindistance, float *maxdistance);
FMOD_RESULT(*cFMOD_Channel_Set3DConeSettings)(FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT(*cFMOD_Channel_Get3DConeSettings)(FMOD_CHANNEL *channel, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT(*cFMOD_Channel_Set3DConeOrientation)(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT(*cFMOD_Channel_Get3DConeOrientation)(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT(*cFMOD_Channel_Set3DCustomRolloff)(FMOD_CHANNEL *channel, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT(*cFMOD_Channel_Get3DCustomRolloff)(FMOD_CHANNEL *channel, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT(*cFMOD_Channel_Set3DOcclusion)(FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion);
FMOD_RESULT(*cFMOD_Channel_Get3DOcclusion)(FMOD_CHANNEL *channel, float *directocclusion, float *reverbocclusion);
FMOD_RESULT(*cFMOD_Channel_Set3DSpread)(FMOD_CHANNEL *channel, float angle);
FMOD_RESULT(*cFMOD_Channel_Get3DSpread)(FMOD_CHANNEL *channel, float *angle);
FMOD_RESULT(*cFMOD_Channel_Set3DPanLevel)(FMOD_CHANNEL *channel, float level);
FMOD_RESULT(*cFMOD_Channel_Get3DPanLevel)(FMOD_CHANNEL *channel, float *level);
FMOD_RESULT(*cFMOD_Channel_Set3DDopplerLevel)(FMOD_CHANNEL *channel, float level);
FMOD_RESULT(*cFMOD_Channel_Get3DDopplerLevel)(FMOD_CHANNEL *channel, float *level);
FMOD_RESULT(*cFMOD_Channel_Set3DDistanceFilter)(FMOD_CHANNEL *channel, FMOD_BOOL custom, float customLevel, float centerFreq);
FMOD_RESULT(*cFMOD_Channel_Get3DDistanceFilter)(FMOD_CHANNEL *channel, FMOD_BOOL *custom, float *customLevel, float *centerFreq);

FMOD_RESULT(*cFMOD_Channel_GetDSPHead)(FMOD_CHANNEL *channel, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_Channel_AddDSP)(FMOD_CHANNEL *channel, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);

FMOD_RESULT(*cFMOD_Channel_IsPlaying)(FMOD_CHANNEL *channel, FMOD_BOOL *isplaying);
FMOD_RESULT(*cFMOD_Channel_IsVirtual)(FMOD_CHANNEL *channel, FMOD_BOOL *isvirtual);
FMOD_RESULT(*cFMOD_Channel_GetAudibility)(FMOD_CHANNEL *channel, float *audibility);
FMOD_RESULT(*cFMOD_Channel_GetCurrentSound)(FMOD_CHANNEL *channel, FMOD_SOUND **sound);
FMOD_RESULT(*cFMOD_Channel_GetSpectrum)(FMOD_CHANNEL *channel, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cFMOD_Channel_GetWaveData)(FMOD_CHANNEL *channel, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT(*cFMOD_Channel_GetIndex)(FMOD_CHANNEL *channel, int *index);

FMOD_RESULT(*cFMOD_Channel_SetMode)(FMOD_CHANNEL *channel, FMOD_MODE mode);
FMOD_RESULT(*cFMOD_Channel_GetMode)(FMOD_CHANNEL *channel, FMOD_MODE *mode);
FMOD_RESULT(*cFMOD_Channel_SetLoopCount)(FMOD_CHANNEL *channel, int loopcount);
FMOD_RESULT(*cFMOD_Channel_GetLoopCount)(FMOD_CHANNEL *channel, int *loopcount);
FMOD_RESULT(*cFMOD_Channel_SetLoopPoints)(FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cFMOD_Channel_GetLoopPoints)(FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

FMOD_RESULT(*cFMOD_Channel_SetUserData)(FMOD_CHANNEL *channel, void *userdata);
FMOD_RESULT(*cFMOD_Channel_GetUserData)(FMOD_CHANNEL *channel, void **userdata);

FMOD_RESULT(*cFMOD_Channel_GetMemoryInfo)(FMOD_CHANNEL *channel, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_ChannelGroup_Release)(FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT(*cFMOD_ChannelGroup_GetSystemObject)(FMOD_CHANNELGROUP *channelgroup, FMOD_SYSTEM **system);

FMOD_RESULT(*cFMOD_ChannelGroup_SetVolume)(FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT(*cFMOD_ChannelGroup_GetVolume)(FMOD_CHANNELGROUP *channelgroup, float *volume);
FMOD_RESULT(*cFMOD_ChannelGroup_SetPitch)(FMOD_CHANNELGROUP *channelgroup, float pitch);
FMOD_RESULT(*cFMOD_ChannelGroup_GetPitch)(FMOD_CHANNELGROUP *channelgroup, float *pitch);
FMOD_RESULT(*cFMOD_ChannelGroup_Set3DOcclusion)(FMOD_CHANNELGROUP *channelgroup, float directocclusion, float reverbocclusion);
FMOD_RESULT(*cFMOD_ChannelGroup_Get3DOcclusion)(FMOD_CHANNELGROUP *channelgroup, float *directocclusion, float *reverbocclusion);
FMOD_RESULT(*cFMOD_ChannelGroup_SetPaused)(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused);
FMOD_RESULT(*cFMOD_ChannelGroup_GetPaused)(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *paused);
FMOD_RESULT(*cFMOD_ChannelGroup_SetMute)(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL mute);
FMOD_RESULT(*cFMOD_ChannelGroup_GetMute)(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *mute);

FMOD_RESULT(*cFMOD_ChannelGroup_Stop)(FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT(*cFMOD_ChannelGroup_OverrideVolume)(FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT(*cFMOD_ChannelGroup_OverrideFrequency)(FMOD_CHANNELGROUP *channelgroup, float frequency);
FMOD_RESULT(*cFMOD_ChannelGroup_OverridePan)(FMOD_CHANNELGROUP *channelgroup, float pan);
FMOD_RESULT(*cFMOD_ChannelGroup_OverrideReverbProperties)(FMOD_CHANNELGROUP *channelgroup, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cFMOD_ChannelGroup_Override3DAttributes)(FMOD_CHANNELGROUP *channelgroup, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT(*cFMOD_ChannelGroup_OverrideSpeakerMix)(FMOD_CHANNELGROUP *channelgroup, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);

FMOD_RESULT(*cFMOD_ChannelGroup_AddGroup)(FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP *group);
FMOD_RESULT(*cFMOD_ChannelGroup_GetNumGroups)(FMOD_CHANNELGROUP *channelgroup, int *numgroups);
FMOD_RESULT(*cFMOD_ChannelGroup_GetGroup)(FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNELGROUP **group);
FMOD_RESULT(*cFMOD_ChannelGroup_GetParentGroup)(FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP **group);

FMOD_RESULT(*cFMOD_ChannelGroup_GetDSPHead)(FMOD_CHANNELGROUP *channelgroup, FMOD_DSP **dsp);
FMOD_RESULT(*cFMOD_ChannelGroup_AddDSP)(FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection);

FMOD_RESULT(*cFMOD_ChannelGroup_GetName)(FMOD_CHANNELGROUP *channelgroup, char *name, int namelen);
FMOD_RESULT(*cFMOD_ChannelGroup_GetNumChannels)(FMOD_CHANNELGROUP *channelgroup, int *numchannels);
FMOD_RESULT(*cFMOD_ChannelGroup_GetChannel)(FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNEL **channel);
FMOD_RESULT(*cFMOD_ChannelGroup_GetSpectrum)(FMOD_CHANNELGROUP *channelgroup, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cFMOD_ChannelGroup_GetWaveData)(FMOD_CHANNELGROUP *channelgroup, float *wavearray, int numvalues, int channeloffset);

FMOD_RESULT(*cFMOD_ChannelGroup_SetUserData)(FMOD_CHANNELGROUP *channelgroup, void *userdata);
FMOD_RESULT(*cFMOD_ChannelGroup_GetUserData)(FMOD_CHANNELGROUP *channelgroup, void **userdata);

FMOD_RESULT(*cFMOD_ChannelGroup_GetMemoryInfo)(FMOD_CHANNELGROUP *channelgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_SoundGroup_Release)(FMOD_SOUNDGROUP *soundgroup);
FMOD_RESULT(*cFMOD_SoundGroup_GetSystemObject)(FMOD_SOUNDGROUP *soundgroup, FMOD_SYSTEM **system);

FMOD_RESULT(*cFMOD_SoundGroup_SetMaxAudible)(FMOD_SOUNDGROUP *soundgroup, int maxaudible);
FMOD_RESULT(*cFMOD_SoundGroup_GetMaxAudible)(FMOD_SOUNDGROUP *soundgroup, int *maxaudible);
FMOD_RESULT(*cFMOD_SoundGroup_SetMaxAudibleBehavior)(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR behavior);
FMOD_RESULT(*cFMOD_SoundGroup_GetMaxAudibleBehavior)(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR *behavior);
FMOD_RESULT(*cFMOD_SoundGroup_SetMuteFadeSpeed)(FMOD_SOUNDGROUP *soundgroup, float speed);
FMOD_RESULT(*cFMOD_SoundGroup_GetMuteFadeSpeed)(FMOD_SOUNDGROUP *soundgroup, float *speed);
FMOD_RESULT(*cFMOD_SoundGroup_SetVolume)(FMOD_SOUNDGROUP *soundgroup, float volume);
FMOD_RESULT(*cFMOD_SoundGroup_GetVolume)(FMOD_SOUNDGROUP *soundgroup, float *volume);
FMOD_RESULT(*cFMOD_SoundGroup_Stop)(FMOD_SOUNDGROUP *soundgroup);

FMOD_RESULT(*cFMOD_SoundGroup_GetName)(FMOD_SOUNDGROUP *soundgroup, char *name, int namelen);
FMOD_RESULT(*cFMOD_SoundGroup_GetNumSounds)(FMOD_SOUNDGROUP *soundgroup, int *numsounds);
FMOD_RESULT(*cFMOD_SoundGroup_GetSound)(FMOD_SOUNDGROUP *soundgroup, int index, FMOD_SOUND **sound);
FMOD_RESULT(*cFMOD_SoundGroup_GetNumPlaying)(FMOD_SOUNDGROUP *soundgroup, int *numplaying);

FMOD_RESULT(*cFMOD_SoundGroup_SetUserData)(FMOD_SOUNDGROUP *soundgroup, void *userdata);
FMOD_RESULT(*cFMOD_SoundGroup_GetUserData)(FMOD_SOUNDGROUP *soundgroup, void **userdata);

FMOD_RESULT(*cFMOD_SoundGroup_GetMemoryInfo)(FMOD_SOUNDGROUP *soundgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cFMOD_DSP_Release)(FMOD_DSP *dsp);
FMOD_RESULT(*cFMOD_DSP_GetSystemObject)(FMOD_DSP *dsp, FMOD_SYSTEM **system);

FMOD_RESULT(*cFMOD_DSP_AddInput)(FMOD_DSP *dsp, FMOD_DSP *target, FMOD_DSPCONNECTION **connection);
FMOD_RESULT(*cFMOD_DSP_DisconnectFrom)(FMOD_DSP *dsp, FMOD_DSP *target);
FMOD_RESULT(*cFMOD_DSP_DisconnectAll)(FMOD_DSP *dsp, FMOD_BOOL inputs, FMOD_BOOL outputs);
FMOD_RESULT(*cFMOD_DSP_Remove)(FMOD_DSP *dsp);
FMOD_RESULT(*cFMOD_DSP_GetNumInputs)(FMOD_DSP *dsp, int *numinputs);
FMOD_RESULT(*cFMOD_DSP_GetNumOutputs)(FMOD_DSP *dsp, int *numoutputs);
FMOD_RESULT(*cFMOD_DSP_GetInput)(FMOD_DSP *dsp, int index, FMOD_DSP **input, FMOD_DSPCONNECTION **inputconnection);
FMOD_RESULT(*cFMOD_DSP_GetOutput)(FMOD_DSP *dsp, int index, FMOD_DSP **output, FMOD_DSPCONNECTION **outputconnection);

FMOD_RESULT(*cFMOD_DSP_SetActive)(FMOD_DSP *dsp, FMOD_BOOL active);
FMOD_RESULT(*cFMOD_DSP_GetActive)(FMOD_DSP *dsp, FMOD_BOOL *active);
FMOD_RESULT(*cFMOD_DSP_SetBypass)(FMOD_DSP *dsp, FMOD_BOOL bypass);
FMOD_RESULT(*cFMOD_DSP_GetBypass)(FMOD_DSP *dsp, FMOD_BOOL *bypass);
FMOD_RESULT(*cFMOD_DSP_SetSpeakerActive)(FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL active);
FMOD_RESULT(*cFMOD_DSP_GetSpeakerActive)(FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL *active);
FMOD_RESULT(*cFMOD_DSP_Reset)(FMOD_DSP *dsp);

FMOD_RESULT(*cFMOD_DSP_SetParameter)(FMOD_DSP *dsp, int index, float value);
FMOD_RESULT(*cFMOD_DSP_GetParameter)(FMOD_DSP *dsp, int index, float *value, char *valuestr, int valuestrlen);
FMOD_RESULT(*cFMOD_DSP_GetNumParameters)(FMOD_DSP *dsp, int *numparams);
FMOD_RESULT(*cFMOD_DSP_GetParameterInfo)(FMOD_DSP *dsp, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max);
FMOD_RESULT(*cFMOD_DSP_ShowConfigDialog)(FMOD_DSP *dsp, void *hwnd, FMOD_BOOL show);

FMOD_RESULT(*cFMOD_DSP_GetInfo)(FMOD_DSP *dsp, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
FMOD_RESULT(*cFMOD_DSP_GetType)(FMOD_DSP *dsp, FMOD_DSP_TYPE *type);
FMOD_RESULT(*cFMOD_DSP_SetDefaults)(FMOD_DSP *dsp, float frequency, float volume, float pan, int priority);
FMOD_RESULT(*cFMOD_DSP_GetDefaults)(FMOD_DSP *dsp, float *frequency, float *volume, float *pan, int *priority);

FMOD_RESULT(*cFMOD_DSP_SetUserData)(FMOD_DSP *dsp, void *userdata);
FMOD_RESULT(*cFMOD_DSP_GetUserData)(FMOD_DSP *dsp, void **userdata);

FMOD_RESULT(*cFMOD_DSP_GetMemoryInfo)(FMOD_DSP *dsp, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_DSPConnection_GetInput)(FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **input);
FMOD_RESULT(*cFMOD_DSPConnection_GetOutput)(FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **output);
FMOD_RESULT(*cFMOD_DSPConnection_SetMix)(FMOD_DSPCONNECTION *dspconnection, float volume);
FMOD_RESULT(*cFMOD_DSPConnection_GetMix)(FMOD_DSPCONNECTION *dspconnection, float *volume);
FMOD_RESULT(*cFMOD_DSPConnection_SetLevels)(FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cFMOD_DSPConnection_GetLevels)(FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels);

FMOD_RESULT(*cFMOD_DSPConnection_SetUserData)(FMOD_DSPCONNECTION *dspconnection, void *userdata);
FMOD_RESULT(*cFMOD_DSPConnection_GetUserData)(FMOD_DSPCONNECTION *dspconnection, void **userdata);

FMOD_RESULT(*cFMOD_DSPConnection_GetMemoryInfo)(FMOD_DSPCONNECTION *dspconnection, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_Geometry_Release)(FMOD_GEOMETRY *geometry);

FMOD_RESULT(*cFMOD_Geometry_AddPolygon)(FMOD_GEOMETRY *geometry, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
FMOD_RESULT(*cFMOD_Geometry_GetNumPolygons)(FMOD_GEOMETRY *geometry, int *numpolygons);
FMOD_RESULT(*cFMOD_Geometry_GetMaxPolygons)(FMOD_GEOMETRY *geometry, int *maxpolygons, int *maxvertices);
FMOD_RESULT(*cFMOD_Geometry_GetPolygonNumVertices)(FMOD_GEOMETRY *geometry, int index, int *numvertices);
FMOD_RESULT(*cFMOD_Geometry_SetPolygonVertex)(FMOD_GEOMETRY *geometry, int index, int vertexindex, const FMOD_VECTOR *vertex);
FMOD_RESULT(*cFMOD_Geometry_GetPolygonVertex)(FMOD_GEOMETRY *geometry, int index, int vertexindex, FMOD_VECTOR *vertex);
FMOD_RESULT(*cFMOD_Geometry_SetPolygonAttributes)(FMOD_GEOMETRY *geometry, int index, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided);
FMOD_RESULT(*cFMOD_Geometry_GetPolygonAttributes)(FMOD_GEOMETRY *geometry, int index, float *directocclusion, float *reverbocclusion, FMOD_BOOL *doublesided);

FMOD_RESULT(*cFMOD_Geometry_SetActive)(FMOD_GEOMETRY *geometry, FMOD_BOOL active);
FMOD_RESULT(*cFMOD_Geometry_GetActive)(FMOD_GEOMETRY *geometry, FMOD_BOOL *active);
FMOD_RESULT(*cFMOD_Geometry_SetRotation)(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT(*cFMOD_Geometry_GetRotation)(FMOD_GEOMETRY *geometry, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT(*cFMOD_Geometry_SetPosition)(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *position);
FMOD_RESULT(*cFMOD_Geometry_GetPosition)(FMOD_GEOMETRY *geometry, FMOD_VECTOR *position);
FMOD_RESULT(*cFMOD_Geometry_SetScale)(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *scale);
FMOD_RESULT(*cFMOD_Geometry_GetScale)(FMOD_GEOMETRY *geometry, FMOD_VECTOR *scale);
FMOD_RESULT(*cFMOD_Geometry_Save)(FMOD_GEOMETRY *geometry, void *data, int *datasize);

FMOD_RESULT(*cFMOD_Geometry_SetUserData)(FMOD_GEOMETRY *geometry, void *userdata);
FMOD_RESULT(*cFMOD_Geometry_GetUserData)(FMOD_GEOMETRY *geometry, void **userdata);

FMOD_RESULT(*cFMOD_Geometry_GetMemoryInfo)(FMOD_GEOMETRY *geometry, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

FMOD_RESULT(*cFMOD_Reverb_Release)(FMOD_REVERB *reverb);

FMOD_RESULT(*cFMOD_Reverb_Set3DAttributes)(FMOD_REVERB *reverb, const FMOD_VECTOR *position, float mindistance, float maxdistance);
FMOD_RESULT(*cFMOD_Reverb_Get3DAttributes)(FMOD_REVERB *reverb, FMOD_VECTOR *position, float *mindistance, float *maxdistance);
FMOD_RESULT(*cFMOD_Reverb_SetProperties)(FMOD_REVERB *reverb, const FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT(*cFMOD_Reverb_GetProperties)(FMOD_REVERB *reverb, FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT(*cFMOD_Reverb_SetActive)(FMOD_REVERB *reverb, FMOD_BOOL active);
FMOD_RESULT(*cFMOD_Reverb_GetActive)(FMOD_REVERB *reverb, FMOD_BOOL *active);

FMOD_RESULT(*cFMOD_Reverb_SetUserData)(FMOD_REVERB *reverb, void *userdata);
FMOD_RESULT(*cFMOD_Reverb_GetUserData)(FMOD_REVERB *reverb, void **userdata);

FMOD_RESULT(*cFMOD_Reverb_GetMemoryInfo)(FMOD_REVERB *reverb, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

/* PSP2-specific */

FMOD_RESULT(*cFMOD_ChannelGroup_SetAudibilityFactor)(FMOD_CHANNELGROUP *channelgroup, float factor);
FMOD_RESULT(*cFMOD_ChannelGroup_GetAudibilityFactor)(FMOD_CHANNELGROUP *channelgroup, float *factor);

/* CPP */

FMOD_RESULT(*cpp_ZN4FMOD6System7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System9setOutputE15FMOD_OUTPUTTYPE)(void *instance, FMOD_OUTPUTTYPE output);
FMOD_RESULT(*cpp_ZN4FMOD6System9getOutputEP15FMOD_OUTPUTTYPE)(void *instance, FMOD_OUTPUTTYPE *output);
FMOD_RESULT(*cpp_ZN4FMOD6System13getNumDriversEPi)(void *instance, int *numdrivers);
FMOD_RESULT(*cpp_ZN4FMOD6System13getDriverInfoEiPciP9FMOD_GUID)(void *instance, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cpp_ZN4FMOD6System14getDriverInfoWEiPsiP9FMOD_GUID)(void *instance, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cpp_ZN4FMOD6System13getDriverCapsEiPjPiP16FMOD_SPEAKERMODE)(void *instance, int id, FMOD_CAPS *caps, int *controlpaneloutputrate, FMOD_SPEAKERMODE *controlpanelspeakermode);
FMOD_RESULT(*cpp_ZN4FMOD6System9setDriverEi)(void *instance, int driver);
FMOD_RESULT(*cpp_ZN4FMOD6System9getDriverEPi)(void *instance, int *driver);
FMOD_RESULT(*cpp_ZN4FMOD6System19setHardwareChannelsEi)(void *instance, int numhardwarechannels);
FMOD_RESULT(*cpp_ZN4FMOD6System19setSoftwareChannelsEi)(void *instance, int numsoftwarechannels);
FMOD_RESULT(*cpp_ZN4FMOD6System19getSoftwareChannelsEPi)(void *instance, int *numsoftwarechannels);
FMOD_RESULT(*cpp_ZN4FMOD6System17setSoftwareFormatEi17FMOD_SOUND_FORMATii18FMOD_DSP_RESAMPLER)(void *instance, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod);
FMOD_RESULT(*cpp_ZN4FMOD6System17getSoftwareFormatEPiP17FMOD_SOUND_FORMATS1_S1_P18FMOD_DSP_RESAMPLERS1_)(void *instance, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits);
FMOD_RESULT(*cpp_ZN4FMOD6System16setDSPBufferSizeEji)(void *instance, unsigned int bufferlength, int numbuffers);
FMOD_RESULT(*cpp_ZN4FMOD6System16getDSPBufferSizeEPjPi)(void *instance, unsigned int *bufferlength, int *numbuffers);
FMOD_RESULT(*cpp_ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESA_i)(void *instance, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, FMOD_FILE_ASYNCREADCALLBACK userasyncread, FMOD_FILE_ASYNCCANCELCALLBACK userasynccancel, int blockalign);
FMOD_RESULT(*cpp_ZN4FMOD6System16attachFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_E)(void *instance, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek);
FMOD_RESULT(*cpp_ZN4FMOD6System19setAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS)(void *instance, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT(*cpp_ZN4FMOD6System19getAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS)(void *instance, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT(*cpp_ZN4FMOD6System14setSpeakerModeE16FMOD_SPEAKERMODE)(void *instance, FMOD_SPEAKERMODE speakermode);
FMOD_RESULT(*cpp_ZN4FMOD6System14getSpeakerModeEP16FMOD_SPEAKERMODE)(void *instance, FMOD_SPEAKERMODE *speakermode);
FMOD_RESULT(*cpp_ZN4FMOD6System11setCallbackEPF11FMOD_RESULTP11FMOD_SYSTEM24FMOD_SYSTEM_CALLBACKTYPEPvS5_E)(void *instance, FMOD_SYSTEM_CALLBACK callback);
FMOD_RESULT(*cpp_ZN4FMOD6System13setPluginPathEPKc)(void *instance, const char *path);
FMOD_RESULT(*cpp_ZN4FMOD6System10loadPluginEPKcPjj)(void *instance, const char *filename, unsigned int *handle, unsigned int priority);
FMOD_RESULT(*cpp_ZN4FMOD6System12unloadPluginEj)(void *instance, unsigned int handle);
FMOD_RESULT(*cpp_ZN4FMOD6System13getNumPluginsE15FMOD_PLUGINTYPEPi)(void *instance, FMOD_PLUGINTYPE plugintype, int *numplugins);
FMOD_RESULT(*cpp_ZN4FMOD6System15getPluginHandleE15FMOD_PLUGINTYPEiPj)(void *instance, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle);
FMOD_RESULT(*cpp_ZN4FMOD6System13getPluginInfoEjP15FMOD_PLUGINTYPEPciPj)(void *instance, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version);
FMOD_RESULT(*cpp_ZN4FMOD6System17setOutputByPluginEj)(void *instance, unsigned int handle);
FMOD_RESULT(*cpp_ZN4FMOD6System17getOutputByPluginEPj)(void *instance, unsigned int *handle);
FMOD_RESULT(*cpp_ZN4FMOD6System17createDSPByPluginEjPPNS_3DSPE)(void *instance, unsigned int handle, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD6System13registerCodecEP22FMOD_CODEC_DESCRIPTIONPjj)(void *instance, FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority);
FMOD_RESULT(*cpp_ZN4FMOD6System11registerDSPEP20FMOD_DSP_DESCRIPTIONPj)(void *instance, FMOD_DSP_DESCRIPTION *description, unsigned int *handle);
FMOD_RESULT(*cpp_ZN4FMOD6System4initEijPv)(void *instance, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT(*cpp_ZN4FMOD6System5closeEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System6updateEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System13set3DSettingsEfff)(void *instance, float dopplerscale, float distancefactor, float rolloffscale);
FMOD_RESULT(*cpp_ZN4FMOD6System13get3DSettingsEPfS1_S1_)(void *instance, float *dopplerscale, float *distancefactor, float *rolloffscale);
FMOD_RESULT(*cpp_ZN4FMOD6System17set3DNumListenersEi)(void *instance, int numlisteners);
FMOD_RESULT(*cpp_ZN4FMOD6System17get3DNumListenersEPi)(void *instance, int *numlisteners);
FMOD_RESULT(*cpp_ZN4FMOD6System23set3DListenerAttributesEiPK11FMOD_VECTORS3_S3_S3_)(void *instance, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT(*cpp_ZN4FMOD6System23get3DListenerAttributesEiP11FMOD_VECTORS2_S2_S2_)(void *instance, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT(*cpp_ZN4FMOD6System20set3DRolloffCallbackEPFfP12FMOD_CHANNELfE)(void *instance, FMOD_3D_ROLLOFFCALLBACK callback);
FMOD_RESULT(*cpp_ZN4FMOD6System20set3DSpeakerPositionE12FMOD_SPEAKERffb)(void *instance, FMOD_SPEAKER speaker, float x, float y, bool active);
FMOD_RESULT(*cpp_ZN4FMOD6System20get3DSpeakerPositionE12FMOD_SPEAKERPfS2_Pb)(void *instance, FMOD_SPEAKER speaker, float *x, float *y, bool *active);
FMOD_RESULT(*cpp_ZN4FMOD6System19setStreamBufferSizeEjj)(void *instance, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
FMOD_RESULT(*cpp_ZN4FMOD6System19getStreamBufferSizeEPjS1_)(void *instance, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);
FMOD_RESULT(*cpp_ZN4FMOD6System10getVersionEPj)(void *instance, unsigned int *version);
FMOD_RESULT(*cpp_ZN4FMOD6System15getOutputHandleEPPv)(void *instance, void **handle);
FMOD_RESULT(*cpp_ZN4FMOD6System18getChannelsPlayingEPi)(void *instance, int *channels);
FMOD_RESULT(*cpp_ZN4FMOD6System19getHardwareChannelsEPi)(void *instance, int *numhardwarechannels);
FMOD_RESULT(*cpp_ZN4FMOD6System11getCPUUsageEPfS1_S1_S1_S1_)(void *instance, float *dsp, float *stream, float *geometry, float *update, float *total);
FMOD_RESULT(*cpp_ZN4FMOD6System11getSoundRAMEPiS1_S1_)(void *instance, int *currentalloced, int *maxalloced, int *total);
FMOD_RESULT(*cpp_ZN4FMOD6System17getNumCDROMDrivesEPi)(void *instance, int *numdrives);
FMOD_RESULT(*cpp_ZN4FMOD6System17getCDROMDriveNameEiPciS1_iS1_i)(void *instance, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen);
FMOD_RESULT(*cpp_ZN4FMOD6System11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW)(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cpp_ZN4FMOD6System11getWaveDataEPfii)(void *instance, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT(*cpp_ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE)(void *instance, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, void **sound);
FMOD_RESULT(*cpp_ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE)(void *instance, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, void **sound);
FMOD_RESULT(*cpp_ZN4FMOD6System9createDSPEP20FMOD_DSP_DESCRIPTIONPPNS_3DSPE)(void *instance, FMOD_DSP_DESCRIPTION *description, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD6System15createDSPByTypeE13FMOD_DSP_TYPEPPNS_3DSPE)(void *instance, FMOD_DSP_TYPE type, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE)(void *instance, const char *name, void **channelgroup);
FMOD_RESULT(*cpp_ZN4FMOD6System16createSoundGroupEPKcPPNS_10SoundGroupE)(void *instance, const char *name, void **soundgroup);
FMOD_RESULT(*cpp_ZN4FMOD6System12createReverbEPPNS_6ReverbE)(void *instance, void **reverb);
FMOD_RESULT(*cpp_ZN4FMOD6System9playSoundE17FMOD_CHANNELINDEXPNS_5SoundEbPPNS_7ChannelE)(void *instance, FMOD_CHANNELINDEX channelid, void *sound, bool paused, void **channel);
FMOD_RESULT(*cpp_ZN4FMOD6System7playDSPE17FMOD_CHANNELINDEXPNS_3DSPEbPPNS_7ChannelE)(void *instance, FMOD_CHANNELINDEX channelid, void *dsp, bool paused, void **channel);
FMOD_RESULT(*cpp_ZN4FMOD6System10getChannelEiPPNS_7ChannelE)(void *instance, int channelid, void **channel);
FMOD_RESULT(*cpp_ZN4FMOD6System21getMasterChannelGroupEPPNS_12ChannelGroupE)(void *instance, void **channelgroup);
FMOD_RESULT(*cpp_ZN4FMOD6System19getMasterSoundGroupEPPNS_10SoundGroupE)(void *instance, void **soundgroup);
FMOD_RESULT(*cpp_ZN4FMOD6System19setReverbPropertiesEPK22FMOD_REVERB_PROPERTIES)(void *instance, const FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD6System19getReverbPropertiesEP22FMOD_REVERB_PROPERTIES)(void *instance, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD6System26setReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES)(void *instance, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD6System26getReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES)(void *instance, FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD6System10getDSPHeadEPPNS_3DSPE)(void *instance, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD6System6addDSPEPNS_3DSPEPPNS_13DSPConnectionE)(void *instance, void *dsp, void **connection);
FMOD_RESULT(*cpp_ZN4FMOD6System7lockDSPEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System9unlockDSPEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System11getDSPClockEPjS1_)(void *instance, unsigned int *hi, unsigned int *lo);
FMOD_RESULT(*cpp_ZN4FMOD6System19getRecordNumDriversEPi)(void *instance, int *numdrivers);
FMOD_RESULT(*cpp_ZN4FMOD6System19getRecordDriverInfoEiPciP9FMOD_GUID)(void *instance, int id, char *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cpp_ZN4FMOD6System20getRecordDriverInfoWEiPsiP9FMOD_GUID)(void *instance, int id, short *name, int namelen, FMOD_GUID *guid);
FMOD_RESULT(*cpp_ZN4FMOD6System19getRecordDriverCapsEiPjPiS2_)(void *instance, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency);
FMOD_RESULT(*cpp_ZN4FMOD6System17getRecordPositionEiPj)(void *instance, int id, unsigned int *position);
FMOD_RESULT(*cpp_ZN4FMOD6System11recordStartEiPNS_5SoundEb)(void *instance, int id, void *sound, bool loop);
FMOD_RESULT(*cpp_ZN4FMOD6System10recordStopEi)(void *instance, int id);
FMOD_RESULT(*cpp_ZN4FMOD6System11isRecordingEiPb)(void *instance, int id, bool *recording);
FMOD_RESULT(*cpp_ZN4FMOD6System14createGeometryEiiPPNS_8GeometryE)(void *instance, int maxpolygons, int maxvertices, void **geometry);
FMOD_RESULT(*cpp_ZN4FMOD6System19setGeometrySettingsEf)(void *instance, float maxworldsize);
FMOD_RESULT(*cpp_ZN4FMOD6System19getGeometrySettingsEPf)(void *instance, float *maxworldsize);
FMOD_RESULT(*cpp_ZN4FMOD6System12loadGeometryEPKviPPNS_8GeometryE)(void *instance, const void *data, int datasize, void **geometry);
FMOD_RESULT(*cpp_ZN4FMOD6System20getGeometryOcclusionEPK11FMOD_VECTORS3_PfS4_)(void *instance, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb);
FMOD_RESULT(*cpp_ZN4FMOD6System15setNetworkProxyEPKc)(void *instance, const char *proxy);
FMOD_RESULT(*cpp_ZN4FMOD6System15getNetworkProxyEPci)(void *instance, char *proxy, int proxylen);
FMOD_RESULT(*cpp_ZN4FMOD6System17setNetworkTimeoutEi)(void *instance, int timeout);
FMOD_RESULT(*cpp_ZN4FMOD6System17getNetworkTimeoutEPi)(void *instance, int *timeout);
FMOD_RESULT(*cpp_ZN4FMOD6System11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD6System11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD6System13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD6System14registerOutputEP23FMOD_OUTPUT_DESCRIPTIONPj)(void *instance, FMOD_OUTPUT_DESCRIPTION *description, unsigned int *handle);
FMOD_RESULT(*cpp_ZN4FMOD6System16getCurrentOutputEPjPPvP15FMOD_OUTPUTTYPE)(void *instance, unsigned int *handle, void **a2, FMOD_OUTPUTTYPE *type);
FMOD_RESULT(*cpp_ZN4FMOD6System12createOutputEjPPvP15FMOD_OUTPUTTYPE)(void *instance, unsigned int handle, void **a2, FMOD_OUTPUTTYPE *type);
FMOD_RESULT(*cpp_ZN4FMOD6System13hotswapOutputEjPv15FMOD_OUTPUTTYPE)(void *instance, unsigned int handle, void *a2, FMOD_OUTPUTTYPE type);
FMOD_RESULT(*cpp_ZN4FMOD6System11startOutputEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6System10stopOutputEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD5Sound7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD5Sound15getSystemObjectEPPNS_6SystemE)(void *instance, void **system);
FMOD_RESULT(*cpp_ZN4FMOD5Sound4lockEjjPPvS2_PjS3_)(void *instance, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
FMOD_RESULT(*cpp_ZN4FMOD5Sound6unlockEPvS1_jj)(void *instance, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11setDefaultsEfffi)(void *instance, float frequency, float volume, float pan, int priority);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11getDefaultsEPfS1_S1_Pi)(void *instance, float *frequency, float *volume, float *pan, int *priority);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13setVariationsEfff)(void *instance, float frequencyvar, float volumevar, float panvar);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13getVariationsEPfS1_S1_)(void *instance, float *frequencyvar, float *volumevar, float *panvar);
FMOD_RESULT(*cpp_ZN4FMOD5Sound19set3DMinMaxDistanceEff)(void *instance, float min, float max);
FMOD_RESULT(*cpp_ZN4FMOD5Sound19get3DMinMaxDistanceEPfS1_)(void *instance, float *min, float *max);
FMOD_RESULT(*cpp_ZN4FMOD5Sound17set3DConeSettingsEfff)(void *instance, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT(*cpp_ZN4FMOD5Sound17get3DConeSettingsEPfS1_S1_)(void *instance, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT(*cpp_ZN4FMOD5Sound18set3DCustomRolloffEP11FMOD_VECTORi)(void *instance, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT(*cpp_ZN4FMOD5Sound18get3DCustomRolloffEPP11FMOD_VECTORPi)(void *instance, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11setSubSoundEiPS0_)(void *instance, int index, void *subsound);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11getSubSoundEiPPS0_)(void *instance, int index, void **subsound);
FMOD_RESULT(*cpp_ZN4FMOD5Sound17getSubSoundParentEPPS0_)(void *instance, void **parentsound);
FMOD_RESULT(*cpp_ZN4FMOD5Sound19setSubSoundSentenceEPii)(void *instance, int *subsoundlist, int numsubsounds);
FMOD_RESULT(*cpp_ZN4FMOD5Sound7getNameEPci)(void *instance, char *name, int namelen);
FMOD_RESULT(*cpp_ZN4FMOD5Sound9getLengthEPjj)(void *instance, unsigned int *length, FMOD_TIMEUNIT lengthtype);
FMOD_RESULT(*cpp_ZN4FMOD5Sound9getFormatEP15FMOD_SOUND_TYPEP17FMOD_SOUND_FORMATPiS5_)(void *instance, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
FMOD_RESULT(*cpp_ZN4FMOD5Sound15getNumSubSoundsEPi)(void *instance, int *numsubsounds);
FMOD_RESULT(*cpp_ZN4FMOD5Sound10getNumTagsEPiS1_)(void *instance, int *numtags, int *numtagsupdated);
FMOD_RESULT(*cpp_ZN4FMOD5Sound6getTagEPKciP8FMOD_TAG)(void *instance, const char *name, int index, FMOD_TAG *tag);
FMOD_RESULT(*cpp_ZN4FMOD5Sound12getOpenStateEP14FMOD_OPENSTATEPjPbS4_)(void *instance, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, bool *starving, bool *diskbusy);
FMOD_RESULT(*cpp_ZN4FMOD5Sound8readDataEPvjPj)(void *instance, void *buffer, unsigned int lenbytes, unsigned int *read);
FMOD_RESULT(*cpp_ZN4FMOD5Sound8seekDataEj)(void *instance, unsigned int pcm);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE)(void *instance, void *soundgroup);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13getSoundGroupEPPNS_10SoundGroupE)(void *instance, void **soundgroup);
FMOD_RESULT(*cpp_ZN4FMOD5Sound16getNumSyncPointsEPi)(void *instance, int *numsyncpoints);
FMOD_RESULT(*cpp_ZN4FMOD5Sound12getSyncPointEiPP14FMOD_SYNCPOINT)(void *instance, int index, FMOD_SYNCPOINT **point);
FMOD_RESULT(*cpp_ZN4FMOD5Sound16getSyncPointInfoEP14FMOD_SYNCPOINTPciPjj)(void *instance, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
FMOD_RESULT(*cpp_ZN4FMOD5Sound12addSyncPointEjjPKcPP14FMOD_SYNCPOINT)(void *instance, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
FMOD_RESULT(*cpp_ZN4FMOD5Sound15deleteSyncPointEP14FMOD_SYNCPOINT)(void *instance, FMOD_SYNCPOINT *point);
FMOD_RESULT(*cpp_ZN4FMOD5Sound7setModeEj)(void *instance, FMOD_MODE mode);
FMOD_RESULT(*cpp_ZN4FMOD5Sound7getModeEPj)(void *instance, FMOD_MODE *mode);
FMOD_RESULT(*cpp_ZN4FMOD5Sound12setLoopCountEi)(void *instance, int loopcount);
FMOD_RESULT(*cpp_ZN4FMOD5Sound12getLoopCountEPi)(void *instance, int *loopcount);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13setLoopPointsEjjjj)(void *instance, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13getLoopPointsEPjjS1_j)(void *instance, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cpp_ZN4FMOD5Sound19getMusicNumChannelsEPi)(void *instance, int *numchannels);
FMOD_RESULT(*cpp_ZN4FMOD5Sound21setMusicChannelVolumeEif)(void *instance, int channel, float volume);
FMOD_RESULT(*cpp_ZN4FMOD5Sound21getMusicChannelVolumeEiPf)(void *instance, int channel, float *volume);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13setMusicSpeedEf)(void *instance, float speed);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13getMusicSpeedEPf)(void *instance, float *speed);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD5Sound11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD5Sound13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15getSystemObjectEPPNS_6SystemE)(void *instance, void **system);
FMOD_RESULT(*cpp_ZN4FMOD7Channel4stopEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9setPausedEb)(void *instance, bool paused);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9getPausedEPb)(void *instance, bool *paused);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9setVolumeEf)(void *instance, float volume);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9getVolumeEPf)(void *instance, float *volume);
FMOD_RESULT(*cpp_ZN4FMOD7Channel12setFrequencyEf)(void *instance, float frequency);
FMOD_RESULT(*cpp_ZN4FMOD7Channel12getFrequencyEPf)(void *instance, float *frequency);
FMOD_RESULT(*cpp_ZN4FMOD7Channel6setPanEf)(void *instance, float pan);
FMOD_RESULT(*cpp_ZN4FMOD7Channel6getPanEPf)(void *instance, float *pan);
FMOD_RESULT(*cpp_ZN4FMOD7Channel8setDelayE14FMOD_DELAYTYPEjj)(void *instance, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo);
FMOD_RESULT(*cpp_ZN4FMOD7Channel8getDelayE14FMOD_DELAYTYPEPjS2_)(void *instance, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13setSpeakerMixEffffffff)(void *instance, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13getSpeakerMixEPfS1_S1_S1_S1_S1_S1_S1_)(void *instance, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright);
FMOD_RESULT(*cpp_ZN4FMOD7Channel16setSpeakerLevelsE12FMOD_SPEAKERPfi)(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD7Channel16getSpeakerLevelsE12FMOD_SPEAKERPfi)(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD7Channel18setInputChannelMixEPfi)(void *instance, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD7Channel18getInputChannelMixEPfi)(void *instance, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD7Channel7setMuteEb)(void *instance, bool mute);
FMOD_RESULT(*cpp_ZN4FMOD7Channel7getMuteEPb)(void *instance, bool *mute);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11setPriorityEi)(void *instance, int priority);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11getPriorityEPi)(void *instance, int *priority);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11setPositionEjj)(void *instance, unsigned int position, FMOD_TIMEUNIT postype);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11getPositionEPjj)(void *instance, unsigned int *position, FMOD_TIMEUNIT postype);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19setReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES)(void *instance, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19getReverbPropertiesEP29FMOD_REVERB_CHANNELPROPERTIES)(void *instance, FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD7Channel14setLowPassGainEf)(void *instance, float gain);
FMOD_RESULT(*cpp_ZN4FMOD7Channel14getLowPassGainEPf)(void *instance, float *gain);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15setChannelGroupEPNS_12ChannelGroupE)(void *instance, void *channelgroup);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15getChannelGroupEPPNS_12ChannelGroupE)(void *instance, void **channelgroup);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11setCallbackEPF11FMOD_RESULTP12FMOD_CHANNEL25FMOD_CHANNEL_CALLBACKTYPEPvS5_E)(void *instance, FMOD_CHANNEL_CALLBACK callback);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15set3DAttributesEPK11FMOD_VECTORS3_)(void *instance, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15get3DAttributesEP11FMOD_VECTORS2_)(void *instance, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19set3DMinMaxDistanceEff)(void *instance, float mindistance, float maxdistance);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19get3DMinMaxDistanceEPfS1_)(void *instance, float *mindistance, float *maxdistance);
FMOD_RESULT(*cpp_ZN4FMOD7Channel17set3DConeSettingsEfff)(void *instance, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT(*cpp_ZN4FMOD7Channel17get3DConeSettingsEPfS1_S1_)(void *instance, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT(*cpp_ZN4FMOD7Channel20set3DConeOrientationEP11FMOD_VECTOR)(void *instance, FMOD_VECTOR *orientation);
FMOD_RESULT(*cpp_ZN4FMOD7Channel20get3DConeOrientationEP11FMOD_VECTOR)(void *instance, FMOD_VECTOR *orientation);
FMOD_RESULT(*cpp_ZN4FMOD7Channel18set3DCustomRolloffEP11FMOD_VECTORi)(void *instance, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT(*cpp_ZN4FMOD7Channel18get3DCustomRolloffEPP11FMOD_VECTORPi)(void *instance, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT(*cpp_ZN4FMOD7Channel14set3DOcclusionEff)(void *instance, float directocclusion, float reverbocclusion);
FMOD_RESULT(*cpp_ZN4FMOD7Channel14get3DOcclusionEPfS1_)(void *instance, float *directocclusion, float *reverbocclusion);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11set3DSpreadEf)(void *instance, float angle);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11get3DSpreadEPf)(void *instance, float *angle);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13set3DPanLevelEf)(void *instance, float level);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13get3DPanLevelEPf)(void *instance, float *level);
FMOD_RESULT(*cpp_ZN4FMOD7Channel17set3DDopplerLevelEf)(void *instance, float level);
FMOD_RESULT(*cpp_ZN4FMOD7Channel17get3DDopplerLevelEPf)(void *instance, float *level);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19set3DDistanceFilterEbff)(void *instance, bool custom, float customLevel, float centerFreq);
FMOD_RESULT(*cpp_ZN4FMOD7Channel19get3DDistanceFilterEPbPfS2_)(void *instance, bool *custom, float *customLevel, float *centerFreq);
FMOD_RESULT(*cpp_ZN4FMOD7Channel10getDSPHeadEPPNS_3DSPE)(void *instance, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD7Channel6addDSPEPNS_3DSPEPPNS_13DSPConnectionE)(void *instance, void *dsp, void **connection);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9isPlayingEPb)(void *instance, bool *isplaying);
FMOD_RESULT(*cpp_ZN4FMOD7Channel9isVirtualEPb)(void *instance, bool *isvirtual);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13getAudibilityEPf)(void *instance, float *audibility);
FMOD_RESULT(*cpp_ZN4FMOD7Channel15getCurrentSoundEPPNS_5SoundE)(void *instance, void **sound);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW)(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11getWaveDataEPfii)(void *instance, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT(*cpp_ZN4FMOD7Channel8getIndexEPi)(void *instance, int *index);
FMOD_RESULT(*cpp_ZN4FMOD7Channel7setModeEj)(void *instance, FMOD_MODE mode);
FMOD_RESULT(*cpp_ZN4FMOD7Channel7getModeEPj)(void *instance, FMOD_MODE *mode);
FMOD_RESULT(*cpp_ZN4FMOD7Channel12setLoopCountEi)(void *instance, int loopcount);
FMOD_RESULT(*cpp_ZN4FMOD7Channel12getLoopCountEPi)(void *instance, int *loopcount);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13setLoopPointsEjjjj)(void *instance, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13getLoopPointsEPjjS1_j)(void *instance, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD7Channel11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD7Channel13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup15getSystemObjectEPPNS_6SystemE)(void *instance, void **system);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup9setVolumeEf)(void *instance, float volume);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup9getVolumeEPf)(void *instance, float *volume);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup8setPitchEf)(void *instance, float pitch);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup8getPitchEPf)(void *instance, float *pitch);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup14set3DOcclusionEff)(void *instance, float directocclusion, float reverbocclusion);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup14get3DOcclusionEPfS1_)(void *instance, float *directocclusion, float *reverbocclusion);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup9setPausedEb)(void *instance, bool paused);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup9getPausedEPb)(void *instance, bool *paused);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup7setMuteEb)(void *instance, bool mute);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup7getMuteEPb)(void *instance, bool *mute);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup4stopEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup14overrideVolumeEf)(void *instance, float volume);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup17overrideFrequencyEf)(void *instance, float frequency);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup11overridePanEf)(void *instance, float pan);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup24overrideReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES)(void *instance, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup20override3DAttributesEPK11FMOD_VECTORS3_)(void *instance, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup18overrideSpeakerMixEffffffff)(void *instance, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup8addGroupEPS0_)(void *instance, void *group);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup12getNumGroupsEPi)(void *instance, int *numgroups);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup8getGroupEiPPS0_)(void *instance, int index, void **group);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup14getParentGroupEPPS0_)(void *instance, void **group);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup10getDSPHeadEPPNS_3DSPE)(void *instance, void **dsp);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup6addDSPEPNS_3DSPEPPNS_13DSPConnectionE)(void *instance, void *dsp, void **connection);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup7getNameEPci)(void *instance, char *name, int namelen);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup14getNumChannelsEPi)(void *instance, int *numchannels);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup10getChannelEiPPNS_7ChannelE)(void *instance, int index, void **channel);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW)(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup11getWaveDataEPfii)(void *instance, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup19setAudibilityFactorEf)(void *instance, float factor);
FMOD_RESULT(*cpp_ZN4FMOD12ChannelGroup19getAudibilityFactorEPf)(void *instance, float *factor);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup15getSystemObjectEPPNS_6SystemE)(void *instance, void **system);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup13setMaxAudibleEi)(void *instance, int maxaudible);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup13getMaxAudibleEPi)(void *instance, int *maxaudible);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup21setMaxAudibleBehaviorE24FMOD_SOUNDGROUP_BEHAVIOR)(void *instance, FMOD_SOUNDGROUP_BEHAVIOR behavior);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup21getMaxAudibleBehaviorEP24FMOD_SOUNDGROUP_BEHAVIOR)(void *instance, FMOD_SOUNDGROUP_BEHAVIOR *behavior);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup16setMuteFadeSpeedEf)(void *instance, float speed);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup16getMuteFadeSpeedEPf)(void *instance, float *speed);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup9setVolumeEf)(void *instance, float volume);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup9getVolumeEPf)(void *instance, float *volume);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup4stopEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup7getNameEPci)(void *instance, char *name, int namelen);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup12getNumSoundsEPi)(void *instance, int *numsounds);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup8getSoundEiPPNS_5SoundE)(void *instance, int index, void **sound);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup13getNumPlayingEPi)(void *instance, int *numplaying);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD10SoundGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD3DSP7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD3DSP15getSystemObjectEPPNS_6SystemE)(void *instance, void **system);
FMOD_RESULT(*cpp_ZN4FMOD3DSP8addInputEPS0_PPNS_13DSPConnectionE)(void *instance, void *target, void **connection);
FMOD_RESULT(*cpp_ZN4FMOD3DSP14disconnectFromEPS0_)(void *instance, void *target);
FMOD_RESULT(*cpp_ZN4FMOD3DSP13disconnectAllEbb)(void *instance, bool inputs, bool outputs);
FMOD_RESULT(*cpp_ZN4FMOD3DSP6removeEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD3DSP12getNumInputsEPi)(void *instance, int *numinputs);
FMOD_RESULT(*cpp_ZN4FMOD3DSP13getNumOutputsEPi)(void *instance, int *numoutputs);
FMOD_RESULT(*cpp_ZN4FMOD3DSP8getInputEiPPS0_PPNS_13DSPConnectionE)(void *instance, int index, void **input, void **inputconnection);
FMOD_RESULT(*cpp_ZN4FMOD3DSP9getOutputEiPPS0_PPNS_13DSPConnectionE)(void *instance, int index, void **output, void **outputconnection);
FMOD_RESULT(*cpp_ZN4FMOD3DSP9setActiveEb)(void *instance, bool active);
FMOD_RESULT(*cpp_ZN4FMOD3DSP9getActiveEPb)(void *instance, bool *active);
FMOD_RESULT(*cpp_ZN4FMOD3DSP9setBypassEb)(void *instance, bool bypass);
FMOD_RESULT(*cpp_ZN4FMOD3DSP9getBypassEPb)(void *instance, bool *bypass);
FMOD_RESULT(*cpp_ZN4FMOD3DSP16setSpeakerActiveE12FMOD_SPEAKERb)(void *instance, FMOD_SPEAKER speaker, bool active);
FMOD_RESULT(*cpp_ZN4FMOD3DSP16getSpeakerActiveE12FMOD_SPEAKERPb)(void *instance, FMOD_SPEAKER speaker, bool *active);
FMOD_RESULT(*cpp_ZN4FMOD3DSP5resetEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD3DSP12setParameterEif)(void *instance, int index, float value);
FMOD_RESULT(*cpp_ZN4FMOD3DSP12getParameterEiPfPci)(void *instance, int index, float *value, char *valuestr, int valuestrlen);
FMOD_RESULT(*cpp_ZN4FMOD3DSP16getNumParametersEPi)(void *instance, int *numparams);
FMOD_RESULT(*cpp_ZN4FMOD3DSP16getParameterInfoEiPcS1_S1_iPfS2_)(void *instance, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max);
FMOD_RESULT(*cpp_ZN4FMOD3DSP16showConfigDialogEPvb)(void *instance, void *hwnd, bool show);
FMOD_RESULT(*cpp_ZN4FMOD3DSP7getInfoEPcPjPiS3_S3_)(void *instance, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
FMOD_RESULT(*cpp_ZN4FMOD3DSP7getTypeEP13FMOD_DSP_TYPE)(void *instance, FMOD_DSP_TYPE *type);
FMOD_RESULT(*cpp_ZN4FMOD3DSP11setDefaultsEfffi)(void *instance, float frequency, float volume, float pan, int priority);
FMOD_RESULT(*cpp_ZN4FMOD3DSP11getDefaultsEPfS1_S1_Pi)(void *instance, float *frequency, float *volume, float *pan, int *priority);
FMOD_RESULT(*cpp_ZN4FMOD3DSP11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD3DSP11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD3DSP13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD3DSP11getCPUUsageEPt)(void *instance, unsigned short *usage);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection8getInputEPPNS_3DSPE)(void *instance, void **input);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection9getOutputEPPNS_3DSPE)(void *instance, void **output);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection6setMixEf)(void *instance, float volume);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection6getMixEPf)(void *instance, float *volume);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection9setLevelsE12FMOD_SPEAKERPfi)(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection9getLevelsE12FMOD_SPEAKERPfi)(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD13DSPConnection13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb7releaseEv)(void *instance);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb15set3DAttributesEPK11FMOD_VECTORff)(void *instance, const FMOD_VECTOR *position, float mindistance, float maxdistance);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb15get3DAttributesEP11FMOD_VECTORPfS3_)(void *instance, FMOD_VECTOR *position, float *mindistance, float *maxdistance);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb13setPropertiesEPK22FMOD_REVERB_PROPERTIES)(void *instance, const FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb13getPropertiesEP22FMOD_REVERB_PROPERTIES)(void *instance, FMOD_REVERB_PROPERTIES *properties);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb9setActiveEb)(void *instance, bool active);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb9getActiveEPb)(void *instance, bool *active);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb11setUserDataEPv)(void *instance, void *userdata);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb11getUserDataEPPv)(void *instance, void **userdata);
FMOD_RESULT(*cpp_ZN4FMOD6Reverb13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS)(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details);

int module_start(SceSize args, const void * argp)
{
	SceInt32 ret = SCE_OK;
	SceKernelModuleInfo moduleInfo;

	if (args != sizeof(SceUID) || argp == SCE_NULL) {
		sceClibPrintf("[fmodIf] Invalid argument to module_start\n");
		return SCE_KERNEL_START_NO_RESIDENT;
	}

	SceUID modid = *(SceUID *)argp;

	sceClibMemset(&moduleInfo, 0, sizeof(SceKernelModuleInfo));
	moduleInfo.size = sizeof(SceKernelModuleInfo);

	ret = sceKernelGetModuleInfo(modid, &moduleInfo);
	if (ret < 0) {
		sceClibPrintf("[fmodIf] sceKernelGetModuleInfo: 0x%08X\n", ret);
		return SCE_KERNEL_START_NO_RESIDENT;
	}

	s_textBase = moduleInfo.segments[0].vaddr;

	uint32_t of = 0;
	void(*initXX)() = 0;

	for (int i = 0; i < sizeof(s_initArray); i += 4) {
		of = *(uint32_t *)(s_initArray + i) - MODULE_BASE_ADDRESS;
		initXX = DECODE_OFFSET(of);
		initXX();
	}

	cFMOD_Memory_Initialize = DECODE_OFFSET(0x00A909E1);
	cFMOD_Memory_GetStats = DECODE_OFFSET(0x00A90ADB);
	cFMOD_Debug_SetLevel = DECODE_OFFSET(0x00A900E9);
	cFMOD_Debug_GetLevel = DECODE_OFFSET(0x00A900ED);
	cFMOD_File_SetDiskBusy = DECODE_OFFSET(0x00AF48E1);
	cFMOD_File_GetDiskBusy = DECODE_OFFSET(0x00AF491F);

	cFMOD_System_Create = DECODE_OFFSET(0x00A90B51);
	cFMOD_System_Release = DECODE_OFFSET(0x00A90C8D);

	cFMOD_System_SetOutput = DECODE_OFFSET(0x00A90CA3);
	cFMOD_System_GetOutput = DECODE_OFFSET(0x00A90CDD);
	cFMOD_System_GetNumDrivers = DECODE_OFFSET(0x00A90D17);
	cFMOD_System_GetDriverInfo = DECODE_OFFSET(0x00A90D51);
	cFMOD_System_GetDriverInfoW = DECODE_OFFSET(0x00A90D91);
	cFMOD_System_GetDriverCaps = DECODE_OFFSET(0x00A90DD1);
	cFMOD_System_SetDriver = DECODE_OFFSET(0x00A90E11);
	cFMOD_System_GetDriver = DECODE_OFFSET(0x00A90E4B);
	cFMOD_System_SetHardwareChannels = DECODE_OFFSET(0x00A90E85);
	cFMOD_System_SetSoftwareChannels = DECODE_OFFSET(0x00A90EBF);
	cFMOD_System_GetSoftwareChannels = DECODE_OFFSET(0x00A90EF9);
	cFMOD_System_SetSoftwareFormat = DECODE_OFFSET(0x00A90F33);
	cFMOD_System_GetSoftwareFormat = DECODE_OFFSET(0x00A90F81);
	cFMOD_System_SetDSPBufferSize = DECODE_OFFSET(0x00A90FD3);
	cFMOD_System_GetDSPBufferSize = DECODE_OFFSET(0x00A91011);
	cFMOD_System_SetFileSystem = DECODE_OFFSET(0x00A9104F);
	cFMOD_System_AttachFileSystem = DECODE_OFFSET(0x00A910AD);
	cFMOD_System_SetAdvancedSettings = DECODE_OFFSET(0x00A910ED);
	cFMOD_System_GetAdvancedSettings = DECODE_OFFSET(0x00A91127);
	cFMOD_System_SetSpeakerMode = DECODE_OFFSET(0x00A91161);
	cFMOD_System_GetSpeakerMode = DECODE_OFFSET(0x00A9119B);
	cFMOD_System_SetCallback = DECODE_OFFSET(0x00A911D5);

	cFMOD_System_SetPluginPath = DECODE_OFFSET(0x00A9120F);
	cFMOD_System_LoadPlugin = DECODE_OFFSET(0x00A91249);
	cFMOD_System_UnloadPlugin = DECODE_OFFSET(0x00A91281);
	cFMOD_System_GetNumPlugins = DECODE_OFFSET(0x00A912BB);
	cFMOD_System_GetPluginHandle = DECODE_OFFSET(0x00A912F9);
	cFMOD_System_GetPluginInfo = DECODE_OFFSET(0x00A91331);
	cFMOD_System_SetOutputByPlugin = DECODE_OFFSET(0x00A9137F);
	cFMOD_System_GetOutputByPlugin = DECODE_OFFSET(0x00A913B9);
	cFMOD_System_CreateDSPByPlugin = DECODE_OFFSET(0x00A913F3);
	cFMOD_System_RegisterCodec = DECODE_OFFSET(0x00A91431);
	cFMOD_System_RegisterDSP = DECODE_OFFSET(0x00A91469);

	cFMOD_System_Init = DECODE_OFFSET(0x00A914A7);
	cFMOD_System_Close = DECODE_OFFSET(0x00A914DF);

	cFMOD_System_Update = DECODE_OFFSET(0x00A91515);
	cFMOD_System_Set3DSettings = DECODE_OFFSET(0x00A9154B);
	cFMOD_System_Get3DSettings = DECODE_OFFSET(0x00A91581);
	cFMOD_System_Set3DNumListeners = DECODE_OFFSET(0x00A915B9);
	cFMOD_System_Get3DNumListeners = DECODE_OFFSET(0x00A915F3);
	cFMOD_System_Set3DListenerAttributes = DECODE_OFFSET(0x00A9162D);
	cFMOD_System_Get3DListenerAttributes = DECODE_OFFSET(0x00A9167B);
	cFMOD_System_Set3DRolloffCallback = DECODE_OFFSET(0x00A916C9);
	cFMOD_System_Set3DSpeakerPosition = DECODE_OFFSET(0x00A91703);
	cFMOD_System_Get3DSpeakerPosition = DECODE_OFFSET(0x00A9174D);
	cFMOD_System_SetStreamBufferSize = DECODE_OFFSET(0x00A917CB);
	cFMOD_System_GetStreamBufferSize = DECODE_OFFSET(0x00A91809);
	cFMOD_System_GetVersion = DECODE_OFFSET(0x00A91847);
	cFMOD_System_GetOutputHandle = DECODE_OFFSET(0x00A91881);
	cFMOD_System_GetChannelsPlaying = DECODE_OFFSET(0x00A918BB);
	cFMOD_System_GetHardwareChannels = DECODE_OFFSET(0x00A918F5);
	cFMOD_System_GetCPUUsage = DECODE_OFFSET(0x00A9192F);
	cFMOD_System_GetSoundRAM = DECODE_OFFSET(0x00A9197D);
	cFMOD_System_GetNumCDROMDrives = DECODE_OFFSET(0x00A919B5);
	cFMOD_System_GetCDROMDriveName = DECODE_OFFSET(0x00A919EF);
	cFMOD_System_GetSpectrum = DECODE_OFFSET(0x00A91A4D);
	cFMOD_System_GetWaveData = DECODE_OFFSET(0x00A91A8D);
	cFMOD_System_CreateSound = DECODE_OFFSET(0x00A91AC5);
	cFMOD_System_CreateStream = DECODE_OFFSET(0x00A91B05);
	cFMOD_System_CreateDSP = DECODE_OFFSET(0x00A91B45);
	cFMOD_System_CreateDSPByType = DECODE_OFFSET(0x00A91B83);
	cFMOD_System_CreateChannelGroup = DECODE_OFFSET(0x00A91BC1);
	cFMOD_System_CreateSoundGroup = DECODE_OFFSET(0x00A91BFF);
	cFMOD_System_CreateReverb = DECODE_OFFSET(0x00A91C3D);
	cFMOD_System_PlaySound = DECODE_OFFSET(0x00A91C77);
	cFMOD_System_PlayDSP = DECODE_OFFSET(0x00A91CC7);
	cFMOD_System_GetChannel = DECODE_OFFSET(0x00A91D17);
	cFMOD_System_GetMasterChannelGroup = DECODE_OFFSET(0x00A91D55);
	cFMOD_System_GetMasterSoundGroup = DECODE_OFFSET(0x00A91D8F);
	cFMOD_System_SetReverbProperties = DECODE_OFFSET(0x00A91DC9);
	cFMOD_System_GetReverbProperties = DECODE_OFFSET(0x00A91E03);
	cFMOD_System_SetReverbAmbientProperties = DECODE_OFFSET(0x00A91E3D);
	cFMOD_System_GetReverbAmbientProperties = DECODE_OFFSET(0x00A91E77);
	cFMOD_System_GetDSPHead = DECODE_OFFSET(0x00A91EB1);
	cFMOD_System_AddDSP = DECODE_OFFSET(0x00A91EEB);
	cFMOD_System_LockDSP = DECODE_OFFSET(0x00A91F29);
	cFMOD_System_UnlockDSP = DECODE_OFFSET(0x00A91F5F);
	cFMOD_System_GetDSPClock = DECODE_OFFSET(0x00A91F95);
	cFMOD_System_GetRecordNumDrivers = DECODE_OFFSET(0x00A91FD3);
	cFMOD_System_GetRecordDriverInfo = DECODE_OFFSET(0x00A9200D);
	cFMOD_System_GetRecordDriverInfoW = DECODE_OFFSET(0x00A9204D);
	cFMOD_System_GetRecordDriverCaps = DECODE_OFFSET(0x00A9208D);
	cFMOD_System_GetRecordPosition = DECODE_OFFSET(0x00A920CD);
	cFMOD_System_RecordStart = DECODE_OFFSET(0x00A9210B);
	cFMOD_System_RecordStop = DECODE_OFFSET(0x00A92151);
	cFMOD_System_IsRecording = DECODE_OFFSET(0x00A9218B);
	cFMOD_System_CreateGeometry = DECODE_OFFSET(0x00A921FD);
	cFMOD_System_SetGeometrySettings = DECODE_OFFSET(0x00A92235);
	cFMOD_System_GetGeometrySettings = DECODE_OFFSET(0x00A9226B);
	cFMOD_System_LoadGeometry = DECODE_OFFSET(0x00A922A5);
	cFMOD_System_GetGeometryOcclusion = DECODE_OFFSET(0x00A922DD);
	cFMOD_System_SetNetworkProxy = DECODE_OFFSET(0x00A9231D);
	cFMOD_System_GetNetworkProxy = DECODE_OFFSET(0x00A92357);
	cFMOD_System_SetNetworkTimeout = DECODE_OFFSET(0x00A92395);
	cFMOD_System_GetNetworkTimeout = DECODE_OFFSET(0x00A923CF);
	cFMOD_System_SetUserData = DECODE_OFFSET(0x00A92409);
	cFMOD_System_GetUserData = DECODE_OFFSET(0x00A92443);
	cFMOD_System_GetMemoryInfo = DECODE_OFFSET(0x00A9247D);
	cFMOD_Sound_Release = DECODE_OFFSET(0x00A924BD);
	cFMOD_Sound_GetSystemObject = DECODE_OFFSET(0x00A924D1);
	cFMOD_Sound_Lock = DECODE_OFFSET(0x00A924E5);
	cFMOD_Sound_Unlock = DECODE_OFFSET(0x00A9250D);
	cFMOD_Sound_SetDefaults = DECODE_OFFSET(0x00A9252D);
	cFMOD_Sound_GetDefaults = DECODE_OFFSET(0x00A92541);
	cFMOD_Sound_SetVariations = DECODE_OFFSET(0x00A92561);
	cFMOD_Sound_GetVariations = DECODE_OFFSET(0x00A92575);
	cFMOD_Sound_Set3DMinMaxDistance = DECODE_OFFSET(0x00A92589);
	cFMOD_Sound_Get3DMinMaxDistance = DECODE_OFFSET(0x00A9259D);
	cFMOD_Sound_Set3DConeSettings = DECODE_OFFSET(0x00A925B1);
	cFMOD_Sound_Get3DConeSettings = DECODE_OFFSET(0x00A925C5);
	cFMOD_Sound_Set3DCustomRolloff = DECODE_OFFSET(0x00A925D9);
	cFMOD_Sound_Get3DCustomRolloff = DECODE_OFFSET(0x00A925ED);
	cFMOD_Sound_SetSubSound = DECODE_OFFSET(0x00A92601);
	cFMOD_Sound_GetSubSound = DECODE_OFFSET(0x00A92615);
	cFMOD_Sound_GetSubSoundParent = DECODE_OFFSET(0x00A92629);
	cFMOD_Sound_SetSubSoundSentence = DECODE_OFFSET(0x00A9263D);
	cFMOD_Sound_GetName = DECODE_OFFSET(0x00A92651);
	cFMOD_Sound_GetLength = DECODE_OFFSET(0x00A92665);
	cFMOD_Sound_GetFormat = DECODE_OFFSET(0x00A92679);
	cFMOD_Sound_GetNumSubSounds = DECODE_OFFSET(0x00A92699);
	cFMOD_Sound_GetNumTags = DECODE_OFFSET(0x00A926AD);
	cFMOD_Sound_GetTag = DECODE_OFFSET(0x00A926C1);
	cFMOD_Sound_GetOpenState = DECODE_OFFSET(0x00A926D5);
	cFMOD_Sound_ReadData = DECODE_OFFSET(0x00A92735);
	cFMOD_Sound_SeekData = DECODE_OFFSET(0x00A92749);
	cFMOD_Sound_SetSoundGroup = DECODE_OFFSET(0x00A9275D);
	cFMOD_Sound_GetSoundGroup = DECODE_OFFSET(0x00A92771);
	cFMOD_Sound_GetNumSyncPoints = DECODE_OFFSET(0x00A92785);
	cFMOD_Sound_GetSyncPoint = DECODE_OFFSET(0x00A92799);
	cFMOD_Sound_GetSyncPointInfo = DECODE_OFFSET(0x00A927AD);
	cFMOD_Sound_AddSyncPoint = DECODE_OFFSET(0x00A927D1);
	cFMOD_Sound_DeleteSyncPoint = DECODE_OFFSET(0x00A927F1);
	cFMOD_Sound_SetMode = DECODE_OFFSET(0x00A92805);
	cFMOD_Sound_GetMode = DECODE_OFFSET(0x00A92819);
	cFMOD_Sound_SetLoopCount = DECODE_OFFSET(0x00A9282D);
	cFMOD_Sound_GetLoopCount = DECODE_OFFSET(0x00A92841);
	cFMOD_Sound_SetLoopPoints = DECODE_OFFSET(0x00A92855);
	cFMOD_Sound_GetLoopPoints = DECODE_OFFSET(0x00A92875);
	cFMOD_Sound_GetMusicNumChannels = DECODE_OFFSET(0x00A92895);
	cFMOD_Sound_SetMusicChannelVolume = DECODE_OFFSET(0x00A928A9);
	cFMOD_Sound_GetMusicChannelVolume = DECODE_OFFSET(0x00A928BD);
	cFMOD_Sound_SetMusicSpeed = DECODE_OFFSET(0x00A928D1);
	cFMOD_Sound_GetMusicSpeed = DECODE_OFFSET(0x00A928E5);
	cFMOD_Sound_SetUserData = DECODE_OFFSET(0x00A928F9);
	cFMOD_Sound_GetUserData = DECODE_OFFSET(0x00A9290D);
	cFMOD_Sound_GetMemoryInfo = DECODE_OFFSET(0x00A92921);
	cFMOD_Channel_GetSystemObject = DECODE_OFFSET(0x00A92941);
	cFMOD_Channel_Stop = DECODE_OFFSET(0x00A92955);
	cFMOD_Channel_SetPaused = DECODE_OFFSET(0x00A92969);
	cFMOD_Channel_GetPaused = DECODE_OFFSET(0x00A92987);
	cFMOD_Channel_SetVolume = DECODE_OFFSET(0x00A929CF);
	cFMOD_Channel_GetVolume = DECODE_OFFSET(0x00A929E3);
	cFMOD_Channel_SetFrequency = DECODE_OFFSET(0x00A929F7);
	cFMOD_Channel_GetFrequency = DECODE_OFFSET(0x00A92A0B);
	cFMOD_Channel_SetPan = DECODE_OFFSET(0x00A92A1F);
	cFMOD_Channel_GetPan = DECODE_OFFSET(0x00A92A33);
	cFMOD_Channel_SetDelay = DECODE_OFFSET(0x00A92A47);
	cFMOD_Channel_GetDelay = DECODE_OFFSET(0x00A92A5B);
	cFMOD_Channel_SetSpeakerMix = DECODE_OFFSET(0x00A92A6F);
	cFMOD_Channel_GetSpeakerMix = DECODE_OFFSET(0x00A92A83);
	cFMOD_Channel_SetSpeakerLevels = DECODE_OFFSET(0x00A92AB9);
	cFMOD_Channel_GetSpeakerLevels = DECODE_OFFSET(0x00A92ACD);
	cFMOD_Channel_SetInputChannelMix = DECODE_OFFSET(0x00A92AE1);
	cFMOD_Channel_GetInputChannelMix = DECODE_OFFSET(0x00A92AF5);
	cFMOD_Channel_SetMute = DECODE_OFFSET(0x00A92B09);
	cFMOD_Channel_GetMute = DECODE_OFFSET(0x00A92B27);
	cFMOD_Channel_SetPriority = DECODE_OFFSET(0x00A92B6F);
	cFMOD_Channel_GetPriority = DECODE_OFFSET(0x00A92B83);
	cFMOD_Channel_SetPosition = DECODE_OFFSET(0x00A92B97);
	cFMOD_Channel_GetPosition = DECODE_OFFSET(0x00A92BAB);
	cFMOD_Channel_SetReverbProperties = DECODE_OFFSET(0x00A92BBF);
	cFMOD_Channel_GetReverbProperties = DECODE_OFFSET(0x00A92BD3);
	cFMOD_Channel_SetLowPassGain = DECODE_OFFSET(0x00A92BE7);
	cFMOD_Channel_GetLowPassGain = DECODE_OFFSET(0x00A92BFB);
	cFMOD_Channel_SetChannelGroup = DECODE_OFFSET(0x00A92C0F);
	cFMOD_Channel_GetChannelGroup = DECODE_OFFSET(0x00A92C23);
	cFMOD_Channel_SetCallback = DECODE_OFFSET(0x00A92C37);
	cFMOD_Channel_Set3DAttributes = DECODE_OFFSET(0x00A92C4B);
	cFMOD_Channel_Get3DAttributes = DECODE_OFFSET(0x00A92C5F);
	cFMOD_Channel_Set3DMinMaxDistance = DECODE_OFFSET(0x00A92C73);
	cFMOD_Channel_Get3DMinMaxDistance = DECODE_OFFSET(0x00A92C87);
	cFMOD_Channel_Set3DConeSettings = DECODE_OFFSET(0x00A92C9B);
	cFMOD_Channel_Get3DConeSettings = DECODE_OFFSET(0x00A92CAF);
	cFMOD_Channel_Set3DConeOrientation = DECODE_OFFSET(0x00A92CC3);
	cFMOD_Channel_Get3DConeOrientation = DECODE_OFFSET(0x00A92CD7);
	cFMOD_Channel_Set3DCustomRolloff = DECODE_OFFSET(0x00A92CEB);
	cFMOD_Channel_Get3DCustomRolloff = DECODE_OFFSET(0x00A92CFF);
	cFMOD_Channel_Set3DOcclusion = DECODE_OFFSET(0x00A92D13);
	cFMOD_Channel_Get3DOcclusion = DECODE_OFFSET(0x00A92D27);
	cFMOD_Channel_Set3DSpread = DECODE_OFFSET(0x00A92D3B);
	cFMOD_Channel_Get3DSpread = DECODE_OFFSET(0x00A92D4F);
	cFMOD_Channel_Set3DPanLevel = DECODE_OFFSET(0x00A92D63);
	cFMOD_Channel_Get3DPanLevel = DECODE_OFFSET(0x00A92D77);
	cFMOD_Channel_Set3DDopplerLevel = DECODE_OFFSET(0x00A92D8B);
	cFMOD_Channel_Get3DDopplerLevel = DECODE_OFFSET(0x00A92D9F);
	cFMOD_Channel_Set3DDistanceFilter = DECODE_OFFSET(0x00A92DB3);
	cFMOD_Channel_Get3DDistanceFilter = DECODE_OFFSET(0x00A92DD1);
	cFMOD_Channel_GetDSPHead = DECODE_OFFSET(0x00A92E19);
	cFMOD_Channel_AddDSP = DECODE_OFFSET(0x00A92E2D);
	cFMOD_Channel_IsPlaying = DECODE_OFFSET(0x00A92E41);
	cFMOD_Channel_IsVirtual = DECODE_OFFSET(0x00A92E89);
	cFMOD_Channel_GetAudibility = DECODE_OFFSET(0x00A92ED1);
	cFMOD_Channel_GetCurrentSound = DECODE_OFFSET(0x00A92EE5);
	cFMOD_Channel_GetSpectrum = DECODE_OFFSET(0x00A92EF9);
	cFMOD_Channel_GetWaveData = DECODE_OFFSET(0x00A92F19);
	cFMOD_Channel_GetIndex = DECODE_OFFSET(0x00A92F2D);
	cFMOD_Channel_SetMode = DECODE_OFFSET(0x00A92F41);
	cFMOD_Channel_GetMode = DECODE_OFFSET(0x00A92F55);
	cFMOD_Channel_SetLoopCount = DECODE_OFFSET(0x00A92F69);
	cFMOD_Channel_GetLoopCount = DECODE_OFFSET(0x00A92F7D);
	cFMOD_Channel_SetLoopPoints = DECODE_OFFSET(0x00A92F91);
	cFMOD_Channel_GetLoopPoints = DECODE_OFFSET(0x00A92FB1);
	cFMOD_Channel_SetUserData = DECODE_OFFSET(0x00A92FD1);
	cFMOD_Channel_GetUserData = DECODE_OFFSET(0x00A92FE5);
	cFMOD_Channel_GetMemoryInfo = DECODE_OFFSET(0x00A92FF9);
	cFMOD_ChannelGroup_Release = DECODE_OFFSET(0x00A93019);
	cFMOD_ChannelGroup_GetSystemObject = DECODE_OFFSET(0x00A9302D);
	cFMOD_ChannelGroup_SetVolume = DECODE_OFFSET(0x00A93069);
	cFMOD_ChannelGroup_GetVolume = DECODE_OFFSET(0x00A9307D);
	cFMOD_ChannelGroup_SetPitch = DECODE_OFFSET(0x00A93091);
	cFMOD_ChannelGroup_GetPitch = DECODE_OFFSET(0x00A930A5);
	cFMOD_ChannelGroup_Set3DOcclusion = DECODE_OFFSET(0x00A930B9);
	cFMOD_ChannelGroup_Get3DOcclusion = DECODE_OFFSET(0x00A930CD);
	cFMOD_ChannelGroup_SetPaused = DECODE_OFFSET(0x00A930E1);
	cFMOD_ChannelGroup_GetPaused = DECODE_OFFSET(0x00A930FF);
	cFMOD_ChannelGroup_SetMute = DECODE_OFFSET(0x00A93149);
	cFMOD_ChannelGroup_GetMute = DECODE_OFFSET(0x00A93167);
	cFMOD_ChannelGroup_Stop = DECODE_OFFSET(0x00A931B1);
	cFMOD_ChannelGroup_OverrideVolume = DECODE_OFFSET(0x00A931C5);
	cFMOD_ChannelGroup_OverrideFrequency = DECODE_OFFSET(0x00A931D9);
	cFMOD_ChannelGroup_OverridePan = DECODE_OFFSET(0x00A931ED);
	cFMOD_ChannelGroup_OverrideReverbProperties = DECODE_OFFSET(0x00A93201);
	cFMOD_ChannelGroup_Override3DAttributes = DECODE_OFFSET(0x00A93215);
	cFMOD_ChannelGroup_OverrideSpeakerMix = DECODE_OFFSET(0x00A93229);
	cFMOD_ChannelGroup_AddGroup = DECODE_OFFSET(0x00A9323D);
	cFMOD_ChannelGroup_GetNumGroups = DECODE_OFFSET(0x00A93251);
	cFMOD_ChannelGroup_GetGroup = DECODE_OFFSET(0x00A93265);
	cFMOD_ChannelGroup_GetParentGroup = DECODE_OFFSET(0x00A93279);
	cFMOD_ChannelGroup_GetDSPHead = DECODE_OFFSET(0x00A9328D);
	cFMOD_ChannelGroup_AddDSP = DECODE_OFFSET(0x00A932A1);
	cFMOD_ChannelGroup_GetName = DECODE_OFFSET(0x00A932B5);
	cFMOD_ChannelGroup_GetNumChannels = DECODE_OFFSET(0x00A932C9);
	cFMOD_ChannelGroup_GetChannel = DECODE_OFFSET(0x00A932DD);
	cFMOD_ChannelGroup_GetSpectrum = DECODE_OFFSET(0x00A932F1);
	cFMOD_ChannelGroup_GetWaveData = DECODE_OFFSET(0x00A93311);
	cFMOD_ChannelGroup_SetUserData = DECODE_OFFSET(0x00A93325);
	cFMOD_ChannelGroup_GetUserData = DECODE_OFFSET(0x00A93339);
	cFMOD_ChannelGroup_GetMemoryInfo = DECODE_OFFSET(0x00A9334D);
	cFMOD_SoundGroup_Release = DECODE_OFFSET(0x00A9336D);
	cFMOD_SoundGroup_GetSystemObject = DECODE_OFFSET(0x00A93381);
	cFMOD_SoundGroup_SetMaxAudible = DECODE_OFFSET(0x00A93395);
	cFMOD_SoundGroup_GetMaxAudible = DECODE_OFFSET(0x00A933A9);
	cFMOD_SoundGroup_SetMaxAudibleBehavior = DECODE_OFFSET(0x00A933BD);
	cFMOD_SoundGroup_GetMaxAudibleBehavior = DECODE_OFFSET(0x00A933D1);
	cFMOD_SoundGroup_SetMuteFadeSpeed = DECODE_OFFSET(0x00A933E5);
	cFMOD_SoundGroup_GetMuteFadeSpeed = DECODE_OFFSET(0x00A933F9);
	cFMOD_SoundGroup_SetVolume = DECODE_OFFSET(0x00A9340D);
	cFMOD_SoundGroup_GetVolume = DECODE_OFFSET(0x00A93421);
	cFMOD_SoundGroup_Stop = DECODE_OFFSET(0x00A93435);
	cFMOD_SoundGroup_GetName = DECODE_OFFSET(0x00A93449);
	cFMOD_SoundGroup_GetNumSounds = DECODE_OFFSET(0x00A9345D);
	cFMOD_SoundGroup_GetSound = DECODE_OFFSET(0x00A93471);
	cFMOD_SoundGroup_GetNumPlaying = DECODE_OFFSET(0x00A93485);
	cFMOD_SoundGroup_SetUserData = DECODE_OFFSET(0x00A93499);
	cFMOD_SoundGroup_GetUserData = DECODE_OFFSET(0x00A934AD);
	cFMOD_SoundGroup_GetMemoryInfo = DECODE_OFFSET(0x00A934C1);
	cFMOD_DSP_Release = DECODE_OFFSET(0x00A934E1);
	cFMOD_DSP_GetSystemObject = DECODE_OFFSET(0x00A934F5);
	cFMOD_DSP_AddInput = DECODE_OFFSET(0x00A93509);
	cFMOD_DSP_DisconnectFrom = DECODE_OFFSET(0x00A9351D);
	cFMOD_DSP_DisconnectAll = DECODE_OFFSET(0x00A93531);
	cFMOD_DSP_Remove = DECODE_OFFSET(0x00A9355D);
	cFMOD_DSP_GetNumInputs = DECODE_OFFSET(0x00A93571);
	cFMOD_DSP_GetNumOutputs = DECODE_OFFSET(0x00A93585);
	cFMOD_DSP_GetInput = DECODE_OFFSET(0x00A93599);
	cFMOD_DSP_GetOutput = DECODE_OFFSET(0x00A935AD);
	cFMOD_DSP_SetActive = DECODE_OFFSET(0x00A935C1);
	cFMOD_DSP_GetActive = DECODE_OFFSET(0x00A935DF);
	cFMOD_DSP_SetBypass = DECODE_OFFSET(0x00A93629);
	cFMOD_DSP_GetBypass = DECODE_OFFSET(0x00A93647);
	cFMOD_DSP_SetSpeakerActive = DECODE_OFFSET(0x00A93691);
	cFMOD_DSP_GetSpeakerActive = DECODE_OFFSET(0x00A936AF);
	cFMOD_DSP_Reset = DECODE_OFFSET(0x00A936F9);
	cFMOD_DSP_SetParameter = DECODE_OFFSET(0x00A9370D);
	cFMOD_DSP_GetParameter = DECODE_OFFSET(0x00A93721);
	cFMOD_DSP_GetNumParameters = DECODE_OFFSET(0x00A93741);
	cFMOD_DSP_GetParameterInfo = DECODE_OFFSET(0x00A93755);
	cFMOD_DSP_ShowConfigDialog = DECODE_OFFSET(0x00A9377F);
	cFMOD_DSP_GetInfo = DECODE_OFFSET(0x00A9379D);
	cFMOD_DSP_GetType = DECODE_OFFSET(0x00A937C1);
	cFMOD_DSP_SetDefaults = DECODE_OFFSET(0x00A937D5);
	cFMOD_DSP_GetDefaults = DECODE_OFFSET(0x00A937E9);
	cFMOD_DSP_SetUserData = DECODE_OFFSET(0x00A93809);
	cFMOD_DSP_GetUserData = DECODE_OFFSET(0x00A9381D);
	cFMOD_DSP_GetMemoryInfo = DECODE_OFFSET(0x00A93831);
	cFMOD_DSPConnection_GetInput = DECODE_OFFSET(0x00A93851);
	cFMOD_DSPConnection_GetOutput = DECODE_OFFSET(0x00A93865);
	cFMOD_DSPConnection_SetMix = DECODE_OFFSET(0x00A93879);
	cFMOD_DSPConnection_GetMix = DECODE_OFFSET(0x00A9388D);
	cFMOD_DSPConnection_SetLevels = DECODE_OFFSET(0x00A938A1);
	cFMOD_DSPConnection_GetLevels = DECODE_OFFSET(0x00A938B5);
	cFMOD_DSPConnection_SetUserData = DECODE_OFFSET(0x00A938C9);
	cFMOD_DSPConnection_GetUserData = DECODE_OFFSET(0x00A938DD);
	cFMOD_DSPConnection_GetMemoryInfo = DECODE_OFFSET(0x00A938F1);
	cFMOD_Geometry_Release = DECODE_OFFSET(0x00A93911);
	cFMOD_Geometry_AddPolygon = DECODE_OFFSET(0x00A93915);
	cFMOD_Geometry_GetNumPolygons = DECODE_OFFSET(0x00A93919);
	cFMOD_Geometry_GetMaxPolygons = DECODE_OFFSET(0x00A9391D);
	cFMOD_Geometry_GetPolygonNumVertices = DECODE_OFFSET(0x00A93921);
	cFMOD_Geometry_SetPolygonVertex = DECODE_OFFSET(0x00A93925);
	cFMOD_Geometry_GetPolygonVertex = DECODE_OFFSET(0x00A93929);
	cFMOD_Geometry_SetPolygonAttributes = DECODE_OFFSET(0x00A9392D);
	cFMOD_Geometry_GetPolygonAttributes = DECODE_OFFSET(0x00A93931);
	cFMOD_Geometry_SetActive = DECODE_OFFSET(0x00A93935);
	cFMOD_Geometry_GetActive = DECODE_OFFSET(0x00A93939);
	cFMOD_Geometry_SetRotation = DECODE_OFFSET(0x00A9393D);
	cFMOD_Geometry_GetRotation = DECODE_OFFSET(0x00A93941);
	cFMOD_Geometry_SetPosition = DECODE_OFFSET(0x00A93945);
	cFMOD_Geometry_GetPosition = DECODE_OFFSET(0x00A93949);
	cFMOD_Geometry_SetScale = DECODE_OFFSET(0x00A9394D);
	cFMOD_Geometry_GetScale = DECODE_OFFSET(0x00A93951);
	cFMOD_Geometry_Save = DECODE_OFFSET(0x00A93955);
	cFMOD_Geometry_SetUserData = DECODE_OFFSET(0x00A93959);
	cFMOD_Geometry_GetUserData = DECODE_OFFSET(0x00A9395D);
	cFMOD_Geometry_GetMemoryInfo = DECODE_OFFSET(0x00A93961);
	cFMOD_Reverb_Release = DECODE_OFFSET(0x00A93965);
	cFMOD_Reverb_Set3DAttributes = DECODE_OFFSET(0x00A93979);
	cFMOD_Reverb_Get3DAttributes = DECODE_OFFSET(0x00A9398D);
	cFMOD_Reverb_SetProperties = DECODE_OFFSET(0x00A939A1);
	cFMOD_Reverb_GetProperties = DECODE_OFFSET(0x00A939B5);
	cFMOD_Reverb_SetActive = DECODE_OFFSET(0x00A939C9);
	cFMOD_Reverb_GetActive = DECODE_OFFSET(0x00A939E7);
	cFMOD_Reverb_SetUserData = DECODE_OFFSET(0x00A93A31);
	cFMOD_Reverb_GetUserData = DECODE_OFFSET(0x00A93A45);
	cFMOD_Reverb_GetMemoryInfo = DECODE_OFFSET(0x00A93A59);

	/* PSP2-specific */

	cFMOD_ChannelGroup_SetAudibilityFactor = DECODE_OFFSET(0x00A93041);
	cFMOD_ChannelGroup_GetAudibilityFactor = DECODE_OFFSET(0x00A93055);

	/* CPP */

	cpp_ZN4FMOD6System7releaseEv = DECODE_OFFSET(0x00A8E235);
	cpp_ZN4FMOD6System9setOutputE15FMOD_OUTPUTTYPE = DECODE_OFFSET(0x00A8E273);
	cpp_ZN4FMOD6System9getOutputEP15FMOD_OUTPUTTYPE = DECODE_OFFSET(0x00A8E2B5);
	cpp_ZN4FMOD6System13getNumDriversEPi = DECODE_OFFSET(0x00A8E2F7);
	cpp_ZN4FMOD6System13getDriverInfoEiPciP9FMOD_GUID = DECODE_OFFSET(0x00A8E339);
	cpp_ZN4FMOD6System14getDriverInfoWEiPsiP9FMOD_GUID = DECODE_OFFSET(0x00A8E38F);
	cpp_ZN4FMOD6System13getDriverCapsEiPjPiP16FMOD_SPEAKERMODE = DECODE_OFFSET(0x00A8E3E5);
	cpp_ZN4FMOD6System9setDriverEi = DECODE_OFFSET(0x00A8E43B);
	cpp_ZN4FMOD6System9getDriverEPi = DECODE_OFFSET(0x00A8E47D);
	cpp_ZN4FMOD6System19setHardwareChannelsEi = DECODE_OFFSET(0x00A8E4BF);
	cpp_ZN4FMOD6System19setSoftwareChannelsEi = DECODE_OFFSET(0x00A8E501);
	cpp_ZN4FMOD6System19getSoftwareChannelsEPi = DECODE_OFFSET(0x00A8E543);
	cpp_ZN4FMOD6System17setSoftwareFormatEi17FMOD_SOUND_FORMATii18FMOD_DSP_RESAMPLER = DECODE_OFFSET(0x00A8E585);
	cpp_ZN4FMOD6System17getSoftwareFormatEPiP17FMOD_SOUND_FORMATS1_S1_P18FMOD_DSP_RESAMPLERS1_ = DECODE_OFFSET(0x00A8E5E3);
	cpp_ZN4FMOD6System16setDSPBufferSizeEji = DECODE_OFFSET(0x00A8E6D5);
	cpp_ZN4FMOD6System16getDSPBufferSizeEPjPi = DECODE_OFFSET(0x00A8E71B);
	cpp_ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESA_i = DECODE_OFFSET(0x00A8E761);
	cpp_ZN4FMOD6System16attachFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_E = DECODE_OFFSET(0x00A8E7D1);
	cpp_ZN4FMOD6System19setAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS = DECODE_OFFSET(0x00A8E827);
	cpp_ZN4FMOD6System19getAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS = DECODE_OFFSET(0x00A8E869);
	cpp_ZN4FMOD6System14setSpeakerModeE16FMOD_SPEAKERMODE = DECODE_OFFSET(0x00A8E8AB);
	cpp_ZN4FMOD6System14getSpeakerModeEP16FMOD_SPEAKERMODE = DECODE_OFFSET(0x00A8E8ED);
	cpp_ZN4FMOD6System11setCallbackEPF11FMOD_RESULTP11FMOD_SYSTEM24FMOD_SYSTEM_CALLBACKTYPEPvS5_E = DECODE_OFFSET(0x00A8E931);
	cpp_ZN4FMOD6System13setPluginPathEPKc = DECODE_OFFSET(0x00A8E973);
	cpp_ZN4FMOD6System10loadPluginEPKcPjj = DECODE_OFFSET(0x00A8E9B5);
	cpp_ZN4FMOD6System12unloadPluginEj = DECODE_OFFSET(0x00A8E9FF);
	cpp_ZN4FMOD6System13getNumPluginsE15FMOD_PLUGINTYPEPi = DECODE_OFFSET(0x00A8EA41);
	cpp_ZN4FMOD6System15getPluginHandleE15FMOD_PLUGINTYPEiPj = DECODE_OFFSET(0x00A8EA87);
	cpp_ZN4FMOD6System13getPluginInfoEjP15FMOD_PLUGINTYPEPciPj = DECODE_OFFSET(0x00A8EAD1);
	cpp_ZN4FMOD6System17setOutputByPluginEj = DECODE_OFFSET(0x00A8EB2F);
	cpp_ZN4FMOD6System17getOutputByPluginEPj = DECODE_OFFSET(0x00A8EB71);
	cpp_ZN4FMOD6System17createDSPByPluginEjPPNS_3DSPE = DECODE_OFFSET(0x00A8EBB3);
	cpp_ZN4FMOD6System13registerCodecEP22FMOD_CODEC_DESCRIPTIONPjj = DECODE_OFFSET(0x00A8EBF9);
	cpp_ZN4FMOD6System11registerDSPEP20FMOD_DSP_DESCRIPTIONPj = DECODE_OFFSET(0x00A8EC43);
	cpp_ZN4FMOD6System4initEijPv = DECODE_OFFSET(0x00A8EDAD);
	cpp_ZN4FMOD6System5closeEv = DECODE_OFFSET(0x00A8EDF7);
	cpp_ZN4FMOD6System6updateEv = DECODE_OFFSET(0x00A8EE35);
	cpp_ZN4FMOD6System13set3DSettingsEfff = DECODE_OFFSET(0x00A8EEEF);
	cpp_ZN4FMOD6System13get3DSettingsEPfS1_S1_ = DECODE_OFFSET(0x00A8EF4D);
	cpp_ZN4FMOD6System17set3DNumListenersEi = DECODE_OFFSET(0x00A8EF97);
	cpp_ZN4FMOD6System17get3DNumListenersEPi = DECODE_OFFSET(0x00A8EFD9);
	cpp_ZN4FMOD6System23set3DListenerAttributesEiPK11FMOD_VECTORS3_S3_S3_ = DECODE_OFFSET(0x00A8F01B);
	cpp_ZN4FMOD6System23get3DListenerAttributesEiP11FMOD_VECTORS2_S2_S2_ = DECODE_OFFSET(0x00A8F079);
	cpp_ZN4FMOD6System20set3DRolloffCallbackEPFfP12FMOD_CHANNELfE = DECODE_OFFSET(0x00A8F0D7);
	cpp_ZN4FMOD6System20set3DSpeakerPositionE12FMOD_SPEAKERffb = DECODE_OFFSET(0x00A8F119);
	cpp_ZN4FMOD6System20get3DSpeakerPositionE12FMOD_SPEAKERPfS2_Pb = DECODE_OFFSET(0x00A8F177);
	cpp_ZN4FMOD6System19setStreamBufferSizeEjj = DECODE_OFFSET(0x00A8F1CD);
	cpp_ZN4FMOD6System19getStreamBufferSizeEPjS1_ = DECODE_OFFSET(0x00A8F213);
	cpp_ZN4FMOD6System10getVersionEPj = DECODE_OFFSET(0x00A8F259);
	cpp_ZN4FMOD6System15getOutputHandleEPPv = DECODE_OFFSET(0x00A8F29B);
	cpp_ZN4FMOD6System18getChannelsPlayingEPi = DECODE_OFFSET(0x00A8F2DD);
	cpp_ZN4FMOD6System19getHardwareChannelsEPi = DECODE_OFFSET(0x00A8F31F);
	cpp_ZN4FMOD6System11getCPUUsageEPfS1_S1_S1_S1_ = DECODE_OFFSET(0x00A8F361);
	cpp_ZN4FMOD6System11getSoundRAMEPiS1_S1_ = DECODE_OFFSET(0x00A8F3BF);
	cpp_ZN4FMOD6System17getNumCDROMDrivesEPi = DECODE_OFFSET(0x00A8F409);
	cpp_ZN4FMOD6System17getCDROMDriveNameEiPciS1_iS1_i = DECODE_OFFSET(0x00A8F44B);
	cpp_ZN4FMOD6System11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW = DECODE_OFFSET(0x00A8F4BB);
	cpp_ZN4FMOD6System11getWaveDataEPfii = DECODE_OFFSET(0x00A8F511);
	cpp_ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE = DECODE_OFFSET(0x00A8F55B);
	cpp_ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE = DECODE_OFFSET(0x00A8F5B1);
	cpp_ZN4FMOD6System9createDSPEP20FMOD_DSP_DESCRIPTIONPPNS_3DSPE = DECODE_OFFSET(0x00A8F607);
	cpp_ZN4FMOD6System15createDSPByTypeE13FMOD_DSP_TYPEPPNS_3DSPE = DECODE_OFFSET(0x00A8F64D);
	cpp_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE = DECODE_OFFSET(0x00A8F693);
	cpp_ZN4FMOD6System16createSoundGroupEPKcPPNS_10SoundGroupE = DECODE_OFFSET(0x00A8F6D9);
	cpp_ZN4FMOD6System12createReverbEPPNS_6ReverbE = DECODE_OFFSET(0x00A8F71F);
	cpp_ZN4FMOD6System9playSoundE17FMOD_CHANNELINDEXPNS_5SoundEbPPNS_7ChannelE = DECODE_OFFSET(0x00A8F761);
	cpp_ZN4FMOD6System7playDSPE17FMOD_CHANNELINDEXPNS_3DSPEbPPNS_7ChannelE = DECODE_OFFSET(0x00A8F7B7);
	cpp_ZN4FMOD6System10getChannelEiPPNS_7ChannelE = DECODE_OFFSET(0x00A8F80D);
	cpp_ZN4FMOD6System21getMasterChannelGroupEPPNS_12ChannelGroupE = DECODE_OFFSET(0x00A8F853);
	cpp_ZN4FMOD6System19getMasterSoundGroupEPPNS_10SoundGroupE = DECODE_OFFSET(0x00A8F895);
	cpp_ZN4FMOD6System19setReverbPropertiesEPK22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8F8D7);
	cpp_ZN4FMOD6System19getReverbPropertiesEP22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8F91B);
	cpp_ZN4FMOD6System26setReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8F95D);
	cpp_ZN4FMOD6System26getReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8F99F);
	cpp_ZN4FMOD6System10getDSPHeadEPPNS_3DSPE = DECODE_OFFSET(0x00A8F9E1);
	cpp_ZN4FMOD6System6addDSPEPNS_3DSPEPPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8FA23);
	cpp_ZN4FMOD6System7lockDSPEv = DECODE_OFFSET(0x00A8FA69);
	cpp_ZN4FMOD6System9unlockDSPEv = DECODE_OFFSET(0x00A8FAA7);
	cpp_ZN4FMOD6System11getDSPClockEPjS1_ = DECODE_OFFSET(0x00A8FAE5);
	cpp_ZN4FMOD6System19getRecordNumDriversEPi = DECODE_OFFSET(0x00A8FB2B);
	cpp_ZN4FMOD6System19getRecordDriverInfoEiPciP9FMOD_GUID = DECODE_OFFSET(0x00A8FB6D);
	cpp_ZN4FMOD6System20getRecordDriverInfoWEiPsiP9FMOD_GUID = DECODE_OFFSET(0x00A8FBC3);
	cpp_ZN4FMOD6System19getRecordDriverCapsEiPjPiS2_ = DECODE_OFFSET(0x00A8FC19);
	cpp_ZN4FMOD6System17getRecordPositionEiPj = DECODE_OFFSET(0x00A8FC6F);
	cpp_ZN4FMOD6System11recordStartEiPNS_5SoundEb = DECODE_OFFSET(0x00A8FCB5);
	cpp_ZN4FMOD6System10recordStopEi = DECODE_OFFSET(0x00A8FCFF);
	cpp_ZN4FMOD6System11isRecordingEiPb = DECODE_OFFSET(0x00A8FD41);
	cpp_ZN4FMOD6System14createGeometryEiiPPNS_8GeometryE = DECODE_OFFSET(0x00A8FD87);
	cpp_ZN4FMOD6System19setGeometrySettingsEf = DECODE_OFFSET(0x00A8FDD1);
	cpp_ZN4FMOD6System19getGeometrySettingsEPf = DECODE_OFFSET(0x00A8FE1F);
	cpp_ZN4FMOD6System12loadGeometryEPKviPPNS_8GeometryE = DECODE_OFFSET(0x00A8FE61);
	cpp_ZN4FMOD6System20getGeometryOcclusionEPK11FMOD_VECTORS3_PfS4_ = DECODE_OFFSET(0x00A8FEAB);
	cpp_ZN4FMOD6System15setNetworkProxyEPKc = DECODE_OFFSET(0x00A8FF01);
	cpp_ZN4FMOD6System15getNetworkProxyEPci = DECODE_OFFSET(0x00A8FF43);
	cpp_ZN4FMOD6System17setNetworkTimeoutEi = DECODE_OFFSET(0x00A8FF89);
	cpp_ZN4FMOD6System17getNetworkTimeoutEPi = DECODE_OFFSET(0x00A8FFCB);
	cpp_ZN4FMOD6System11setUserDataEPv = DECODE_OFFSET(0x00A9000D);
	cpp_ZN4FMOD6System11getUserDataEPPv = DECODE_OFFSET(0x00A9004F);
	cpp_ZN4FMOD6System13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A90091);
	cpp_ZN4FMOD6System14registerOutputEP23FMOD_OUTPUT_DESCRIPTIONPj = DECODE_OFFSET(0x00A8EC89);
	cpp_ZN4FMOD6System16getCurrentOutputEPjPPvP15FMOD_OUTPUTTYPE = DECODE_OFFSET(0x00A8ECCF);
	cpp_ZN4FMOD6System12createOutputEjPPvP15FMOD_OUTPUTTYPE = DECODE_OFFSET(0x00A8ED19);
	cpp_ZN4FMOD6System13hotswapOutputEjPv15FMOD_OUTPUTTYPE = DECODE_OFFSET(0x00A8ED63);
	cpp_ZN4FMOD6System11startOutputEv = DECODE_OFFSET(0x00A8EE73);
	cpp_ZN4FMOD6System10stopOutputEv = DECODE_OFFSET(0x00A8EEB1);
	cpp_ZN4FMOD5Sound7releaseEv = DECODE_OFFSET(0x00A8D141);
	cpp_ZN4FMOD5Sound15getSystemObjectEPPNS_6SystemE = DECODE_OFFSET(0x00A8D17D);
	cpp_ZN4FMOD5Sound4lockEjjPPvS2_PjS3_ = DECODE_OFFSET(0x00A8D1BB);
	cpp_ZN4FMOD5Sound6unlockEPvS1_jj = DECODE_OFFSET(0x00A8D22D);
	cpp_ZN4FMOD5Sound11setDefaultsEfffi = DECODE_OFFSET(0x00A8D297);
	cpp_ZN4FMOD5Sound11getDefaultsEPfS1_S1_Pi = DECODE_OFFSET(0x00A8D305);
	cpp_ZN4FMOD5Sound13setVariationsEfff = DECODE_OFFSET(0x00A8D36F);
	cpp_ZN4FMOD5Sound13getVariationsEPfS1_S1_ = DECODE_OFFSET(0x00A8D3D9);
	cpp_ZN4FMOD5Sound19set3DMinMaxDistanceEff = DECODE_OFFSET(0x00A8D43D);
	cpp_ZN4FMOD5Sound19get3DMinMaxDistanceEPfS1_ = DECODE_OFFSET(0x00A8D49F);
	cpp_ZN4FMOD5Sound17set3DConeSettingsEfff = DECODE_OFFSET(0x00A8D4F5);
	cpp_ZN4FMOD5Sound17get3DConeSettingsEPfS1_S1_ = DECODE_OFFSET(0x00A8D563);
	cpp_ZN4FMOD5Sound18set3DCustomRolloffEP11FMOD_VECTORi = DECODE_OFFSET(0x00A8D5CD);
	cpp_ZN4FMOD5Sound18get3DCustomRolloffEPP11FMOD_VECTORPi = DECODE_OFFSET(0x00A8D623);
	cpp_ZN4FMOD5Sound11setSubSoundEiPS0_ = DECODE_OFFSET(0x00A8D679);
	cpp_ZN4FMOD5Sound11getSubSoundEiPPS0_ = DECODE_OFFSET(0x00A8D6CB);
	cpp_ZN4FMOD5Sound17getSubSoundParentEPPS0_ = DECODE_OFFSET(0x00A8D72D);
	cpp_ZN4FMOD5Sound19setSubSoundSentenceEPii = DECODE_OFFSET(0x00A8D77B);
	cpp_ZN4FMOD5Sound7getNameEPci = DECODE_OFFSET(0x00A8D7CD);
	cpp_ZN4FMOD5Sound9getLengthEPjj = DECODE_OFFSET(0x00A8D81F);
	cpp_ZN4FMOD5Sound9getFormatEP15FMOD_SOUND_TYPEP17FMOD_SOUND_FORMATPiS5_ = DECODE_OFFSET(0x00A8D871);
	cpp_ZN4FMOD5Sound15getNumSubSoundsEPi = DECODE_OFFSET(0x00A8D8DB);
	cpp_ZN4FMOD5Sound10getNumTagsEPiS1_ = DECODE_OFFSET(0x00A8D929);
	cpp_ZN4FMOD5Sound6getTagEPKciP8FMOD_TAG = DECODE_OFFSET(0x00A8D97B);
	cpp_ZN4FMOD5Sound12getOpenStateEP14FMOD_OPENSTATEPjPbS4_ = DECODE_OFFSET(0x00A8D9DF);
	cpp_ZN4FMOD5Sound8readDataEPvjPj = DECODE_OFFSET(0x00A8DA31);
	cpp_ZN4FMOD5Sound8seekDataEj = DECODE_OFFSET(0x00A8DA95);
	cpp_ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE = DECODE_OFFSET(0x00A8DAE3);
	cpp_ZN4FMOD5Sound13getSoundGroupEPPNS_10SoundGroupE = DECODE_OFFSET(0x00A8DB33);
	cpp_ZN4FMOD5Sound16getNumSyncPointsEPi = DECODE_OFFSET(0x00A8DB83);
	cpp_ZN4FMOD5Sound12getSyncPointEiPP14FMOD_SYNCPOINT = DECODE_OFFSET(0x00A8DBD3);
	cpp_ZN4FMOD5Sound16getSyncPointInfoEP14FMOD_SYNCPOINTPciPjj = DECODE_OFFSET(0x00A8DC27);
	cpp_ZN4FMOD5Sound12addSyncPointEjjPKcPP14FMOD_SYNCPOINT = DECODE_OFFSET(0x00A8DC99);
	cpp_ZN4FMOD5Sound15deleteSyncPointEP14FMOD_SYNCPOINT = DECODE_OFFSET(0x00A8DD0D);
	cpp_ZN4FMOD5Sound7setModeEj = DECODE_OFFSET(0x00A8DD5D);
	cpp_ZN4FMOD5Sound7getModeEPj = DECODE_OFFSET(0x00A8DDAD);
	cpp_ZN4FMOD5Sound12setLoopCountEi = DECODE_OFFSET(0x00A8DDFD);
	cpp_ZN4FMOD5Sound12getLoopCountEPi = DECODE_OFFSET(0x00A8DE4D);
	cpp_ZN4FMOD5Sound13setLoopPointsEjjjj = DECODE_OFFSET(0x00A8DE9D);
	cpp_ZN4FMOD5Sound13getLoopPointsEPjjS1_j = DECODE_OFFSET(0x00A8DF07);
	cpp_ZN4FMOD5Sound19getMusicNumChannelsEPi = DECODE_OFFSET(0x00A8DF71);
	cpp_ZN4FMOD5Sound21setMusicChannelVolumeEif = DECODE_OFFSET(0x00A8DFC5);
	cpp_ZN4FMOD5Sound21getMusicChannelVolumeEiPf = DECODE_OFFSET(0x00A8E029);
	cpp_ZN4FMOD5Sound13setMusicSpeedEf = DECODE_OFFSET(0x00A8E081);
	cpp_ZN4FMOD5Sound13getMusicSpeedEPf = DECODE_OFFSET(0x00A8E0E1);
	cpp_ZN4FMOD5Sound11setUserDataEPv = DECODE_OFFSET(0x00A8E135);
	cpp_ZN4FMOD5Sound11getUserDataEPPv = DECODE_OFFSET(0x00A8E189);
	cpp_ZN4FMOD5Sound13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A8E1C9);
	cpp_ZN4FMOD7Channel15getSystemObjectEPPNS_6SystemE = DECODE_OFFSET(0x00A8A67D);
	cpp_ZN4FMOD7Channel4stopEv = DECODE_OFFSET(0x00A8A6C7);
	cpp_ZN4FMOD7Channel9setPausedEb = DECODE_OFFSET(0x00A8A705);
	cpp_ZN4FMOD7Channel9getPausedEPb = DECODE_OFFSET(0x00A8A747);
	cpp_ZN4FMOD7Channel9setVolumeEf = DECODE_OFFSET(0x00A8A791);
	cpp_ZN4FMOD7Channel9getVolumeEPf = DECODE_OFFSET(0x00A8A7E1);
	cpp_ZN4FMOD7Channel12setFrequencyEf = DECODE_OFFSET(0x00A8A82B);
	cpp_ZN4FMOD7Channel12getFrequencyEPf = DECODE_OFFSET(0x00A8A879);
	cpp_ZN4FMOD7Channel6setPanEf = DECODE_OFFSET(0x00A8A8C3);
	cpp_ZN4FMOD7Channel6getPanEPf = DECODE_OFFSET(0x00A8A913);
	cpp_ZN4FMOD7Channel8setDelayE14FMOD_DELAYTYPEjj = DECODE_OFFSET(0x00A8A95D);
	cpp_ZN4FMOD7Channel8getDelayE14FMOD_DELAYTYPEPjS2_ = DECODE_OFFSET(0x00A8A9A7);
	cpp_ZN4FMOD7Channel13setSpeakerMixEffffffff = DECODE_OFFSET(0x00A8A9FF);
	cpp_ZN4FMOD7Channel13getSpeakerMixEPfS1_S1_S1_S1_S1_S1_S1_ = DECODE_OFFSET(0x00A8AA87);
	cpp_ZN4FMOD7Channel16setSpeakerLevelsE12FMOD_SPEAKERPfi = DECODE_OFFSET(0x00A8AB4B);
	cpp_ZN4FMOD7Channel16getSpeakerLevelsE12FMOD_SPEAKERPfi = DECODE_OFFSET(0x00A8AB99);
	cpp_ZN4FMOD7Channel18setInputChannelMixEPfi = DECODE_OFFSET(0x00A8ABEB);
	cpp_ZN4FMOD7Channel18getInputChannelMixEPfi = DECODE_OFFSET(0x00A8AC31);
	cpp_ZN4FMOD7Channel7setMuteEb = DECODE_OFFSET(0x00A8AC7F);
	cpp_ZN4FMOD7Channel7getMuteEPb = DECODE_OFFSET(0x00A8ACC1);
	cpp_ZN4FMOD7Channel11setPriorityEi = DECODE_OFFSET(0x00A8AD0B);
	cpp_ZN4FMOD7Channel11getPriorityEPi = DECODE_OFFSET(0x00A8AD4D);
	cpp_ZN4FMOD7Channel11setPositionEjj = DECODE_OFFSET(0x00A8AD97);
	cpp_ZN4FMOD7Channel11getPositionEPjj = DECODE_OFFSET(0x00A8ADDD);
	cpp_ZN4FMOD7Channel19setReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES = DECODE_OFFSET(0x00A8AE2B);
	cpp_ZN4FMOD7Channel19getReverbPropertiesEP29FMOD_REVERB_CHANNELPROPERTIES = DECODE_OFFSET(0x00A8AE6D);
	cpp_ZN4FMOD7Channel14setLowPassGainEf = DECODE_OFFSET(0x00A8AEAF);
	cpp_ZN4FMOD7Channel14getLowPassGainEPf = DECODE_OFFSET(0x00A8AEFD);
	cpp_ZN4FMOD7Channel15setChannelGroupEPNS_12ChannelGroupE = DECODE_OFFSET(0x00A8AF47);
	cpp_ZN4FMOD7Channel15getChannelGroupEPPNS_12ChannelGroupE = DECODE_OFFSET(0x00A8AF89);
	cpp_ZN4FMOD7Channel11setCallbackEPF11FMOD_RESULTP12FMOD_CHANNEL25FMOD_CHANNEL_CALLBACKTYPEPvS5_E = DECODE_OFFSET(0x00A8AFD3);
	cpp_ZN4FMOD7Channel15set3DAttributesEPK11FMOD_VECTORS3_ = DECODE_OFFSET(0x00A8B015);
	cpp_ZN4FMOD7Channel15get3DAttributesEP11FMOD_VECTORS2_ = DECODE_OFFSET(0x00A8B05B);
	cpp_ZN4FMOD7Channel19set3DMinMaxDistanceEff = DECODE_OFFSET(0x00A8B0B7);
	cpp_ZN4FMOD7Channel19get3DMinMaxDistanceEPfS1_ = DECODE_OFFSET(0x00A8B10D);
	cpp_ZN4FMOD7Channel17set3DConeSettingsEfff = DECODE_OFFSET(0x00A8B161);
	cpp_ZN4FMOD7Channel17get3DConeSettingsEPfS1_S1_ = DECODE_OFFSET(0x00A8B1BF);
	cpp_ZN4FMOD7Channel20set3DConeOrientationEP11FMOD_VECTOR = DECODE_OFFSET(0x00A8B21D);
	cpp_ZN4FMOD7Channel20get3DConeOrientationEP11FMOD_VECTOR = DECODE_OFFSET(0x00A8B25F);
	cpp_ZN4FMOD7Channel18set3DCustomRolloffEP11FMOD_VECTORi = DECODE_OFFSET(0x00A8B2AD);
	cpp_ZN4FMOD7Channel18get3DCustomRolloffEPP11FMOD_VECTORPi = DECODE_OFFSET(0x00A8B2F3);
	cpp_ZN4FMOD7Channel14set3DOcclusionEff = DECODE_OFFSET(0x00A8B347);
	cpp_ZN4FMOD7Channel14get3DOcclusionEPfS1_ = DECODE_OFFSET(0x00A8B39D);
	cpp_ZN4FMOD7Channel11set3DSpreadEf = DECODE_OFFSET(0x00A8B3F1);
	cpp_ZN4FMOD7Channel11get3DSpreadEPf = DECODE_OFFSET(0x00A8B43F);
	cpp_ZN4FMOD7Channel13set3DPanLevelEf = DECODE_OFFSET(0x00A8B489);
	cpp_ZN4FMOD7Channel13get3DPanLevelEPf = DECODE_OFFSET(0x00A8B4D7);
	cpp_ZN4FMOD7Channel17set3DDopplerLevelEf = DECODE_OFFSET(0x00A8B521);
	cpp_ZN4FMOD7Channel17get3DDopplerLevelEPf = DECODE_OFFSET(0x00A8B56F);
	cpp_ZN4FMOD7Channel19set3DDistanceFilterEbff = DECODE_OFFSET(0x00A8B5B9);
	cpp_ZN4FMOD7Channel19get3DDistanceFilterEPbPfS2_ = DECODE_OFFSET(0x00A8B613);
	cpp_ZN4FMOD7Channel10getDSPHeadEPPNS_3DSPE = DECODE_OFFSET(0x00A8B671);
	cpp_ZN4FMOD7Channel6addDSPEPNS_3DSPEPPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8B6BB);
	cpp_ZN4FMOD7Channel9isPlayingEPb = DECODE_OFFSET(0x00A8B701);
	cpp_ZN4FMOD7Channel9isVirtualEPb = DECODE_OFFSET(0x00A8B74B);
	cpp_ZN4FMOD7Channel13getAudibilityEPf = DECODE_OFFSET(0x00A8B795);
	cpp_ZN4FMOD7Channel15getCurrentSoundEPPNS_5SoundE = DECODE_OFFSET(0x00A8B7DF);
	cpp_ZN4FMOD7Channel11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW = DECODE_OFFSET(0x00A8B829);
	cpp_ZN4FMOD7Channel11getWaveDataEPfii = DECODE_OFFSET(0x00A8B887);
	cpp_ZN4FMOD7Channel8getIndexEPi = DECODE_OFFSET(0x00A8B8D9);
	cpp_ZN4FMOD7Channel7setModeEj = DECODE_OFFSET(0x00A8B923);
	cpp_ZN4FMOD7Channel7getModeEPj = DECODE_OFFSET(0x00A8B965);
	cpp_ZN4FMOD7Channel12setLoopCountEi = DECODE_OFFSET(0x00A8B9AF);
	cpp_ZN4FMOD7Channel12getLoopCountEPi = DECODE_OFFSET(0x00A8B9F1);
	cpp_ZN4FMOD7Channel13setLoopPointsEjjjj = DECODE_OFFSET(0x00A8BA3B);
	cpp_ZN4FMOD7Channel13getLoopPointsEPjjS1_j = DECODE_OFFSET(0x00A8BA91);
	cpp_ZN4FMOD7Channel11setUserDataEPv = DECODE_OFFSET(0x00A8BAF5);
	cpp_ZN4FMOD7Channel11getUserDataEPPv = DECODE_OFFSET(0x00A8BB37);
	cpp_ZN4FMOD7Channel13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A8BB81);
	cpp_ZN4FMOD12ChannelGroup7releaseEv = DECODE_OFFSET(0x00A8BBE1);
	cpp_ZN4FMOD12ChannelGroup15getSystemObjectEPPNS_6SystemE = DECODE_OFFSET(0x00A8BC1F);
	cpp_ZN4FMOD12ChannelGroup9setVolumeEf = DECODE_OFFSET(0x00A8BCF1);
	cpp_ZN4FMOD12ChannelGroup9getVolumeEPf = DECODE_OFFSET(0x00A8BD3F);
	cpp_ZN4FMOD12ChannelGroup8setPitchEf = DECODE_OFFSET(0x00A8BD81);
	cpp_ZN4FMOD12ChannelGroup8getPitchEPf = DECODE_OFFSET(0x00A8BDCF);
	cpp_ZN4FMOD12ChannelGroup14set3DOcclusionEff = DECODE_OFFSET(0x00A8BE11);
	cpp_ZN4FMOD12ChannelGroup14get3DOcclusionEPfS1_ = DECODE_OFFSET(0x00A8BE67);
	cpp_ZN4FMOD12ChannelGroup9setPausedEb = DECODE_OFFSET(0x00A8BEAD);
	cpp_ZN4FMOD12ChannelGroup9getPausedEPb = DECODE_OFFSET(0x00A8BEF1);
	cpp_ZN4FMOD12ChannelGroup7setMuteEb = DECODE_OFFSET(0x00A8BF33);
	cpp_ZN4FMOD12ChannelGroup7getMuteEPb = DECODE_OFFSET(0x00A8BF77);
	cpp_ZN4FMOD12ChannelGroup4stopEv = DECODE_OFFSET(0x00A8BFB9);
	cpp_ZN4FMOD12ChannelGroup14overrideVolumeEf = DECODE_OFFSET(0x00A8BFF7);
	cpp_ZN4FMOD12ChannelGroup17overrideFrequencyEf = DECODE_OFFSET(0x00A8C045);
	cpp_ZN4FMOD12ChannelGroup11overridePanEf = DECODE_OFFSET(0x00A8C093);
	cpp_ZN4FMOD12ChannelGroup24overrideReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES = DECODE_OFFSET(0x00A8C0E1);
	cpp_ZN4FMOD12ChannelGroup20override3DAttributesEPK11FMOD_VECTORS3_ = DECODE_OFFSET(0x00A8C123);
	cpp_ZN4FMOD12ChannelGroup18overrideSpeakerMixEffffffff = DECODE_OFFSET(0x00A8C169);
	cpp_ZN4FMOD12ChannelGroup8addGroupEPS0_ = DECODE_OFFSET(0x00A8C1EF);
	cpp_ZN4FMOD12ChannelGroup12getNumGroupsEPi = DECODE_OFFSET(0x00A8C231);
	cpp_ZN4FMOD12ChannelGroup8getGroupEiPPS0_ = DECODE_OFFSET(0x00A8C273);
	cpp_ZN4FMOD12ChannelGroup14getParentGroupEPPS0_ = DECODE_OFFSET(0x00A8C2B9);
	cpp_ZN4FMOD12ChannelGroup10getDSPHeadEPPNS_3DSPE = DECODE_OFFSET(0x00A8C2FB);
	cpp_ZN4FMOD12ChannelGroup6addDSPEPNS_3DSPEPPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8C33D);
	cpp_ZN4FMOD12ChannelGroup7getNameEPci = DECODE_OFFSET(0x00A8C383);
	cpp_ZN4FMOD12ChannelGroup14getNumChannelsEPi = DECODE_OFFSET(0x00A8C3C9);
	cpp_ZN4FMOD12ChannelGroup10getChannelEiPPNS_7ChannelE = DECODE_OFFSET(0x00A8C40B);
	cpp_ZN4FMOD12ChannelGroup11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW = DECODE_OFFSET(0x00A8C451);
	cpp_ZN4FMOD12ChannelGroup11getWaveDataEPfii = DECODE_OFFSET(0x00A8C4A7);
	cpp_ZN4FMOD12ChannelGroup11setUserDataEPv = DECODE_OFFSET(0x00A8C4F1);
	cpp_ZN4FMOD12ChannelGroup11getUserDataEPPv = DECODE_OFFSET(0x00A8C533);
	cpp_ZN4FMOD12ChannelGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A8C575);
	cpp_ZN4FMOD12ChannelGroup19setAudibilityFactorEf = DECODE_OFFSET(0x00A8BC61);
	cpp_ZN4FMOD12ChannelGroup19getAudibilityFactorEPf = DECODE_OFFSET(0x00A8BCAF);
	cpp_ZN4FMOD10SoundGroup7releaseEv = DECODE_OFFSET(0x00AF3BB5);
	cpp_ZN4FMOD10SoundGroup15getSystemObjectEPPNS_6SystemE = DECODE_OFFSET(0x00AF3BF3);
	cpp_ZN4FMOD10SoundGroup13setMaxAudibleEi = DECODE_OFFSET(0x00AF3C35);
	cpp_ZN4FMOD10SoundGroup13getMaxAudibleEPi = DECODE_OFFSET(0x00AF3C77);
	cpp_ZN4FMOD10SoundGroup21setMaxAudibleBehaviorE24FMOD_SOUNDGROUP_BEHAVIOR = DECODE_OFFSET(0x00AF3CB9);
	cpp_ZN4FMOD10SoundGroup21getMaxAudibleBehaviorEP24FMOD_SOUNDGROUP_BEHAVIOR = DECODE_OFFSET(0x00AF3CFB);
	cpp_ZN4FMOD10SoundGroup16setMuteFadeSpeedEf = DECODE_OFFSET(0x00AF3D3D);
	cpp_ZN4FMOD10SoundGroup16getMuteFadeSpeedEPf = DECODE_OFFSET(0x00AF3D8B);
	cpp_ZN4FMOD10SoundGroup9setVolumeEf = DECODE_OFFSET(0x00AF3DCD);
	cpp_ZN4FMOD10SoundGroup9getVolumeEPf = DECODE_OFFSET(0x00AF3E1B);
	cpp_ZN4FMOD10SoundGroup4stopEv = DECODE_OFFSET(0x00AF3E5D);
	cpp_ZN4FMOD10SoundGroup7getNameEPci = DECODE_OFFSET(0x00AF3E9B);
	cpp_ZN4FMOD10SoundGroup12getNumSoundsEPi = DECODE_OFFSET(0x00AF3EE1);
	cpp_ZN4FMOD10SoundGroup8getSoundEiPPNS_5SoundE = DECODE_OFFSET(0x00AF3F23);
	cpp_ZN4FMOD10SoundGroup13getNumPlayingEPi = DECODE_OFFSET(0x00AF3F69);
	cpp_ZN4FMOD10SoundGroup11setUserDataEPv = DECODE_OFFSET(0x00AF3FAB);
	cpp_ZN4FMOD10SoundGroup11getUserDataEPPv = DECODE_OFFSET(0x00AF3FED);
	cpp_ZN4FMOD10SoundGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00AF402F);
	cpp_ZN4FMOD3DSP7releaseEv = DECODE_OFFSET(0x00A8C5CD);
	cpp_ZN4FMOD3DSP15getSystemObjectEPPNS_6SystemE = DECODE_OFFSET(0x00A8C609);
	cpp_ZN4FMOD3DSP8addInputEPS0_PPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8C647);
	cpp_ZN4FMOD3DSP14disconnectFromEPS0_ = DECODE_OFFSET(0x00A8C689);
	cpp_ZN4FMOD3DSP13disconnectAllEbb = DECODE_OFFSET(0x00A8C6CD);
	cpp_ZN4FMOD3DSP6removeEv = DECODE_OFFSET(0x00A8C713);
	cpp_ZN4FMOD3DSP12getNumInputsEPi = DECODE_OFFSET(0x00A8C74D);
	cpp_ZN4FMOD3DSP13getNumOutputsEPi = DECODE_OFFSET(0x00A8C791);
	cpp_ZN4FMOD3DSP8getInputEiPPS0_PPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8C7D5);
	cpp_ZN4FMOD3DSP9getOutputEiPPS0_PPNS_13DSPConnectionE = DECODE_OFFSET(0x00A8C823);
	cpp_ZN4FMOD3DSP9setActiveEb = DECODE_OFFSET(0x00A8C871);
	cpp_ZN4FMOD3DSP9getActiveEPb = DECODE_OFFSET(0x00A8C8C3);
	cpp_ZN4FMOD3DSP9setBypassEb = DECODE_OFFSET(0x00A8C90F);
	cpp_ZN4FMOD3DSP9getBypassEPb = DECODE_OFFSET(0x00A8C961);
	cpp_ZN4FMOD3DSP16setSpeakerActiveE12FMOD_SPEAKERb = DECODE_OFFSET(0x00A8C9AD);
	cpp_ZN4FMOD3DSP16getSpeakerActiveE12FMOD_SPEAKERPb = DECODE_OFFSET(0x00A8CA01);
	cpp_ZN4FMOD3DSP5resetEv = DECODE_OFFSET(0x00A8CA4F);
	cpp_ZN4FMOD3DSP12setParameterEif = DECODE_OFFSET(0x00A8CA89);
	cpp_ZN4FMOD3DSP12getParameterEiPfPci = DECODE_OFFSET(0x00A8CAD7);
	cpp_ZN4FMOD3DSP16getNumParametersEPi = DECODE_OFFSET(0x00A8CB29);
	cpp_ZN4FMOD3DSP16getParameterInfoEiPcS1_S1_iPfS2_ = DECODE_OFFSET(0x00A8CB67);
	cpp_ZN4FMOD3DSP16showConfigDialogEPvb = DECODE_OFFSET(0x00A8CBD3);
	cpp_ZN4FMOD3DSP7getInfoEPcPjPiS3_S3_ = DECODE_OFFSET(0x00A8CC15);
	cpp_ZN4FMOD3DSP7getTypeEP13FMOD_DSP_TYPE = DECODE_OFFSET(0x00A8CC6F);
	cpp_ZN4FMOD3DSP11setDefaultsEfffi = DECODE_OFFSET(0x00A8CCAD);
	cpp_ZN4FMOD3DSP11getDefaultsEPfS1_S1_Pi = DECODE_OFFSET(0x00A8CD0B);
	cpp_ZN4FMOD3DSP11setUserDataEPv = DECODE_OFFSET(0x00A8CD5D);
	cpp_ZN4FMOD3DSP11getUserDataEPPv = DECODE_OFFSET(0x00A8CD9F);
	cpp_ZN4FMOD3DSP13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A8CDE1);
	cpp_ZN4FMOD3DSP11getCPUUsageEPt = DECODE_OFFSET(0x00A8CE37);
	cpp_ZN4FMOD13DSPConnection8getInputEPPNS_3DSPE = DECODE_OFFSET(0x00A88FC1);
	cpp_ZN4FMOD13DSPConnection9getOutputEPPNS_3DSPE = DECODE_OFFSET(0x00A89003);
	cpp_ZN4FMOD13DSPConnection6setMixEf = DECODE_OFFSET(0x00A89045);
	cpp_ZN4FMOD13DSPConnection6getMixEPf = DECODE_OFFSET(0x00A89093);
	cpp_ZN4FMOD13DSPConnection9setLevelsE12FMOD_SPEAKERPfi = DECODE_OFFSET(0x00A890D5);
	cpp_ZN4FMOD13DSPConnection9getLevelsE12FMOD_SPEAKERPfi = DECODE_OFFSET(0x00A8911F);
	cpp_ZN4FMOD13DSPConnection11setUserDataEPv = DECODE_OFFSET(0x00A89169);
	cpp_ZN4FMOD13DSPConnection11getUserDataEPPv = DECODE_OFFSET(0x00A891AB);
	cpp_ZN4FMOD13DSPConnection13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A891ED);
	cpp_ZN4FMOD6Reverb7releaseEv = DECODE_OFFSET(0x00A8CE79);
	cpp_ZN4FMOD6Reverb15set3DAttributesEPK11FMOD_VECTORff = DECODE_OFFSET(0x00A8CEB9);
	cpp_ZN4FMOD6Reverb15get3DAttributesEP11FMOD_VECTORPfS3_ = DECODE_OFFSET(0x00A8CF13);
	cpp_ZN4FMOD6Reverb13setPropertiesEPK22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8CF5D);
	cpp_ZN4FMOD6Reverb13getPropertiesEP22FMOD_REVERB_PROPERTIES = DECODE_OFFSET(0x00A8CF9F);
	cpp_ZN4FMOD6Reverb9setActiveEb = DECODE_OFFSET(0x00A8CFE1);
	cpp_ZN4FMOD6Reverb9getActiveEPb = DECODE_OFFSET(0x00A8D023);
	cpp_ZN4FMOD6Reverb11setUserDataEPv = DECODE_OFFSET(0x00A8D065);
	cpp_ZN4FMOD6Reverb11getUserDataEPPv = DECODE_OFFSET(0x00A8D0A7);
	cpp_ZN4FMOD6Reverb13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS = DECODE_OFFSET(0x00A8D0E9);

	return SCE_KERNEL_START_SUCCESS;
}

FMOD_RESULT FMOD_Memory_Initialize(void *poolmem, int poollen, FMOD_MEMORY_ALLOCCALLBACK useralloc, FMOD_MEMORY_REALLOCCALLBACK userrealloc, FMOD_MEMORY_FREECALLBACK userfree, FMOD_MEMORY_TYPE memtypeflags) { return cFMOD_Memory_Initialize(poolmem, poollen, useralloc, userrealloc, userfree, memtypeflags); }
FMOD_RESULT FMOD_Memory_GetStats(int *currentalloced, int *maxalloced, FMOD_BOOL blocking) { return cFMOD_Memory_GetStats(currentalloced, maxalloced, blocking); }
FMOD_RESULT FMOD_Debug_SetLevel(FMOD_DEBUGLEVEL level) { return cFMOD_Debug_SetLevel(level); }
FMOD_RESULT FMOD_Debug_GetLevel(FMOD_DEBUGLEVEL *level) { return cFMOD_Debug_GetLevel(level); }
FMOD_RESULT FMOD_File_SetDiskBusy(int busy) { return cFMOD_File_SetDiskBusy(busy); }
FMOD_RESULT FMOD_File_GetDiskBusy(int *busy) { return cFMOD_File_GetDiskBusy(busy); }
FMOD_RESULT FMOD_System_Create(FMOD_SYSTEM **system) { return cFMOD_System_Create(system); }
FMOD_RESULT FMOD_System_Release(FMOD_SYSTEM *system) { return cFMOD_System_Release(system); }
FMOD_RESULT FMOD_System_SetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output) { return cFMOD_System_SetOutput(system, output); }
FMOD_RESULT FMOD_System_GetOutput(FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output) { return cFMOD_System_GetOutput(system, output); }
FMOD_RESULT FMOD_System_GetNumDrivers(FMOD_SYSTEM *system, int *numdrivers) { return cFMOD_System_GetNumDrivers(system, numdrivers); }
FMOD_RESULT FMOD_System_GetDriverInfo(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid) { return cFMOD_System_GetDriverInfo(system, id, name, namelen, guid); }
FMOD_RESULT FMOD_System_GetDriverInfoW(FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid) { return cFMOD_System_GetDriverInfoW(system, id, name, namelen, guid); }
FMOD_RESULT FMOD_System_GetDriverCaps(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *controlpaneloutputrate, FMOD_SPEAKERMODE *controlpanelspeakermode) { return cFMOD_System_GetDriverCaps(system, id, caps, controlpaneloutputrate, controlpanelspeakermode); }
FMOD_RESULT FMOD_System_SetDriver(FMOD_SYSTEM *system, int driver) { return cFMOD_System_SetDriver(system, driver); }
FMOD_RESULT FMOD_System_GetDriver(FMOD_SYSTEM *system, int *driver) { return cFMOD_System_GetDriver(system, driver); }
FMOD_RESULT FMOD_System_SetHardwareChannels(FMOD_SYSTEM *system, int numhardwarechannels) { return cFMOD_System_SetHardwareChannels(system, numhardwarechannels); }
FMOD_RESULT FMOD_System_SetSoftwareChannels(FMOD_SYSTEM *system, int numsoftwarechannels) { return cFMOD_System_SetSoftwareChannels(system, numsoftwarechannels); }
FMOD_RESULT FMOD_System_GetSoftwareChannels(FMOD_SYSTEM *system, int *numsoftwarechannels) { return cFMOD_System_GetSoftwareChannels(system, numsoftwarechannels); }
FMOD_RESULT FMOD_System_SetSoftwareFormat(FMOD_SYSTEM *system, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod) { return cFMOD_System_SetSoftwareFormat(system, samplerate, format, numoutputchannels, maxinputchannels, resamplemethod); }
FMOD_RESULT FMOD_System_GetSoftwareFormat(FMOD_SYSTEM *system, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits) { return cFMOD_System_GetSoftwareFormat(system, samplerate, format, numoutputchannels, maxinputchannels, resamplemethod, bits); }
FMOD_RESULT FMOD_System_SetDSPBufferSize(FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers) { return cFMOD_System_SetDSPBufferSize(system, bufferlength, numbuffers); }
FMOD_RESULT FMOD_System_GetDSPBufferSize(FMOD_SYSTEM *system, unsigned int *bufferlength, int *numbuffers) { return cFMOD_System_GetDSPBufferSize(system, bufferlength, numbuffers); }
FMOD_RESULT FMOD_System_SetFileSystem(FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, FMOD_FILE_ASYNCREADCALLBACK userasyncread, FMOD_FILE_ASYNCCANCELCALLBACK userasynccancel, int blockalign) { return cFMOD_System_SetFileSystem(system, useropen, userclose, userread, userseek, userasyncread, userasynccancel, blockalign); }
FMOD_RESULT FMOD_System_AttachFileSystem(FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek) { return cFMOD_System_AttachFileSystem(system, useropen, userclose, userread, userseek); }
FMOD_RESULT FMOD_System_SetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) { return cFMOD_System_SetAdvancedSettings(system, settings); }
FMOD_RESULT FMOD_System_GetAdvancedSettings(FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings) { return cFMOD_System_GetAdvancedSettings(system, settings); }
FMOD_RESULT FMOD_System_SetSpeakerMode(FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode) { return cFMOD_System_SetSpeakerMode(system, speakermode); }
FMOD_RESULT FMOD_System_GetSpeakerMode(FMOD_SYSTEM *system, FMOD_SPEAKERMODE *speakermode) { return cFMOD_System_GetSpeakerMode(system, speakermode); }
FMOD_RESULT FMOD_System_SetCallback(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK callback) { return cFMOD_System_SetCallback(system, callback); }
FMOD_RESULT FMOD_System_SetPluginPath(FMOD_SYSTEM *system, const char *path) { return cFMOD_System_SetPluginPath(system, path); }
FMOD_RESULT FMOD_System_LoadPlugin(FMOD_SYSTEM *system, const char *filename, unsigned int *handle, unsigned int priority) { return cFMOD_System_LoadPlugin(system, filename, handle, priority); }
FMOD_RESULT FMOD_System_UnloadPlugin(FMOD_SYSTEM *system, unsigned int handle) { return cFMOD_System_UnloadPlugin(system, handle); }
FMOD_RESULT FMOD_System_GetNumPlugins(FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int *numplugins) { return cFMOD_System_GetNumPlugins(system, plugintype, numplugins); }
FMOD_RESULT FMOD_System_GetPluginHandle(FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle) { return cFMOD_System_GetPluginHandle(system, plugintype, index, handle); }
FMOD_RESULT FMOD_System_GetPluginInfo(FMOD_SYSTEM *system, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version) { return cFMOD_System_GetPluginInfo(system, handle, plugintype, name, namelen, version); }
FMOD_RESULT FMOD_System_SetOutputByPlugin(FMOD_SYSTEM *system, unsigned int handle) { return cFMOD_System_SetOutputByPlugin(system, handle); }
FMOD_RESULT FMOD_System_GetOutputByPlugin(FMOD_SYSTEM *system, unsigned int *handle) { return cFMOD_System_GetOutputByPlugin(system, handle); }
FMOD_RESULT FMOD_System_CreateDSPByPlugin(FMOD_SYSTEM *system, unsigned int handle, FMOD_DSP **dsp) { return cFMOD_System_CreateDSPByPlugin(system, handle, dsp); }
FMOD_RESULT FMOD_System_RegisterCodec(FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority) { return cFMOD_System_RegisterCodec(system, description, handle, priority); }
FMOD_RESULT FMOD_System_RegisterDSP(FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, unsigned int *handle) { return cFMOD_System_RegisterDSP(system, description, handle); }
FMOD_RESULT FMOD_System_Init(FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata) { return cFMOD_System_Init(system, maxchannels, flags, extradriverdata); }
FMOD_RESULT FMOD_System_Close(FMOD_SYSTEM *system) { return cFMOD_System_Close(system); }
FMOD_RESULT FMOD_System_Update(FMOD_SYSTEM *system) { return cFMOD_System_Update(system); }
FMOD_RESULT FMOD_System_Set3DSettings(FMOD_SYSTEM *system, float dopplerscale, float distancefactor, float rolloffscale) { return cFMOD_System_Set3DSettings(system, dopplerscale, distancefactor, rolloffscale); }
FMOD_RESULT FMOD_System_Get3DSettings(FMOD_SYSTEM *system, float *dopplerscale, float *distancefactor, float *rolloffscale) { return cFMOD_System_Get3DSettings(system, dopplerscale, distancefactor, rolloffscale); }
FMOD_RESULT FMOD_System_Set3DNumListeners(FMOD_SYSTEM *system, int numlisteners) { return cFMOD_System_Set3DNumListeners(system, numlisteners); }
FMOD_RESULT FMOD_System_Get3DNumListeners(FMOD_SYSTEM *system, int *numlisteners) { return cFMOD_System_Get3DNumListeners(system, numlisteners); }
FMOD_RESULT FMOD_System_Set3DListenerAttributes(FMOD_SYSTEM *system, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up) { return cFMOD_System_Set3DListenerAttributes(system, listener, pos, vel, forward, up); }
FMOD_RESULT FMOD_System_Get3DListenerAttributes(FMOD_SYSTEM *system, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up) { return cFMOD_System_Get3DListenerAttributes(system, listener, pos, vel, forward, up); }
FMOD_RESULT FMOD_System_Set3DRolloffCallback(FMOD_SYSTEM *system, FMOD_3D_ROLLOFFCALLBACK callback) { return cFMOD_System_Set3DRolloffCallback(system, callback); }
FMOD_RESULT FMOD_System_Set3DSpeakerPosition(FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float x, float y, FMOD_BOOL active) { return cFMOD_System_Set3DSpeakerPosition(system, speaker, x, y, active); }
FMOD_RESULT FMOD_System_Get3DSpeakerPosition(FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float *x, float *y, FMOD_BOOL *active) { return cFMOD_System_Get3DSpeakerPosition(system, speaker, x, y, active); }
FMOD_RESULT FMOD_System_SetStreamBufferSize(FMOD_SYSTEM *system, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype) { return cFMOD_System_SetStreamBufferSize(system, filebuffersize, filebuffersizetype); }
FMOD_RESULT FMOD_System_GetStreamBufferSize(FMOD_SYSTEM *system, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype) { return cFMOD_System_GetStreamBufferSize(system, filebuffersize, filebuffersizetype); }
FMOD_RESULT FMOD_System_GetVersion(FMOD_SYSTEM *system, unsigned int *version) { return cFMOD_System_GetVersion(system, version); }
FMOD_RESULT FMOD_System_GetOutputHandle(FMOD_SYSTEM *system, void **handle) { return cFMOD_System_GetOutputHandle(system, handle); }
FMOD_RESULT FMOD_System_GetChannelsPlaying(FMOD_SYSTEM *system, int *channels) { return cFMOD_System_GetChannelsPlaying(system, channels); }
FMOD_RESULT FMOD_System_GetHardwareChannels(FMOD_SYSTEM *system, int *numhardwarechannels) { return cFMOD_System_GetHardwareChannels(system, numhardwarechannels); }
FMOD_RESULT FMOD_System_GetCPUUsage(FMOD_SYSTEM *system, float *dsp, float *stream, float *geometry, float *update, float *total) { return cFMOD_System_GetCPUUsage(system, dsp, stream, geometry, update, total); }
FMOD_RESULT FMOD_System_GetSoundRAM(FMOD_SYSTEM *system, int *currentalloced, int *maxalloced, int *total) { return cFMOD_System_GetSoundRAM(system, currentalloced, maxalloced, total); }
FMOD_RESULT FMOD_System_GetNumCDROMDrives(FMOD_SYSTEM *system, int *numdrives) { return cFMOD_System_GetNumCDROMDrives(system, numdrives); }
FMOD_RESULT FMOD_System_GetCDROMDriveName(FMOD_SYSTEM *system, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen) { return cFMOD_System_GetCDROMDriveName(system, drive, drivename, drivenamelen, scsiname, scsinamelen, devicename, devicenamelen); }
FMOD_RESULT FMOD_System_GetSpectrum(FMOD_SYSTEM *system, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cFMOD_System_GetSpectrum(system, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT FMOD_System_GetWaveData(FMOD_SYSTEM *system, float *wavearray, int numvalues, int channeloffset) { return cFMOD_System_GetWaveData(system, wavearray, numvalues, channeloffset); }
FMOD_RESULT FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) { return cFMOD_System_CreateSound(system, name_or_data, mode, exinfo, sound); }
FMOD_RESULT FMOD_System_CreateStream(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound) { return cFMOD_System_CreateStream(system, name_or_data, mode, exinfo, sound); }
FMOD_RESULT FMOD_System_CreateDSP(FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, FMOD_DSP **dsp) { return cFMOD_System_CreateDSP(system, description, dsp); }
FMOD_RESULT FMOD_System_CreateDSPByType(FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp) { return cFMOD_System_CreateDSPByType(system, type, dsp); }
FMOD_RESULT FMOD_System_CreateChannelGroup(FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup) { return cFMOD_System_CreateChannelGroup(system, name, channelgroup); }
FMOD_RESULT FMOD_System_CreateSoundGroup(FMOD_SYSTEM *system, const char *name, FMOD_SOUNDGROUP **soundgroup) { return cFMOD_System_CreateSoundGroup(system, name, soundgroup); }
FMOD_RESULT FMOD_System_CreateReverb(FMOD_SYSTEM *system, FMOD_REVERB **reverb) { return cFMOD_System_CreateReverb(system, reverb); }
FMOD_RESULT FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel) { return cFMOD_System_PlaySound(system, channelid, sound, paused, channel); }
FMOD_RESULT FMOD_System_PlayDSP(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_DSP *dsp, FMOD_BOOL paused, FMOD_CHANNEL **channel) { return cFMOD_System_PlayDSP(system, channelid, dsp, paused, channel); }
FMOD_RESULT FMOD_System_GetChannel(FMOD_SYSTEM *system, int channelid, FMOD_CHANNEL **channel) { return cFMOD_System_GetChannel(system, channelid, channel); }
FMOD_RESULT FMOD_System_GetMasterChannelGroup(FMOD_SYSTEM *system, FMOD_CHANNELGROUP **channelgroup) { return cFMOD_System_GetMasterChannelGroup(system, channelgroup); }
FMOD_RESULT FMOD_System_GetMasterSoundGroup(FMOD_SYSTEM *system, FMOD_SOUNDGROUP **soundgroup) { return cFMOD_System_GetMasterSoundGroup(system, soundgroup); }
FMOD_RESULT FMOD_System_SetReverbProperties(FMOD_SYSTEM *system, const FMOD_REVERB_PROPERTIES *prop) { return cFMOD_System_SetReverbProperties(system, prop); }
FMOD_RESULT FMOD_System_GetReverbProperties(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop) { return cFMOD_System_GetReverbProperties(system, prop); }
FMOD_RESULT FMOD_System_SetReverbAmbientProperties(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop) { return cFMOD_System_SetReverbAmbientProperties(system, prop); }
FMOD_RESULT FMOD_System_GetReverbAmbientProperties(FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop) { return cFMOD_System_GetReverbAmbientProperties(system, prop); }
FMOD_RESULT FMOD_System_GetDSPHead(FMOD_SYSTEM *system, FMOD_DSP **dsp) { return cFMOD_System_GetDSPHead(system, dsp); }
FMOD_RESULT FMOD_System_AddDSP(FMOD_SYSTEM *system, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection) { return cFMOD_System_AddDSP(system, dsp, connection); }
FMOD_RESULT FMOD_System_LockDSP(FMOD_SYSTEM *system) { return cFMOD_System_LockDSP(system); }
FMOD_RESULT FMOD_System_UnlockDSP(FMOD_SYSTEM *system) { return cFMOD_System_UnlockDSP(system); }
FMOD_RESULT FMOD_System_GetDSPClock(FMOD_SYSTEM *system, unsigned int *hi, unsigned int *lo) { return cFMOD_System_GetDSPClock(system, hi, lo); }
FMOD_RESULT FMOD_System_GetRecordNumDrivers(FMOD_SYSTEM *system, int *numdrivers) { return cFMOD_System_GetRecordNumDrivers(system, numdrivers); }
FMOD_RESULT FMOD_System_GetRecordDriverInfo(FMOD_SYSTEM *system, int id, char *name, int namelen, FMOD_GUID *guid) { return cFMOD_System_GetRecordDriverInfo(system, id, name, namelen, guid); }
FMOD_RESULT FMOD_System_GetRecordDriverInfoW(FMOD_SYSTEM *system, int id, short *name, int namelen, FMOD_GUID *guid) { return cFMOD_System_GetRecordDriverInfoW(system, id, name, namelen, guid); }
FMOD_RESULT FMOD_System_GetRecordDriverCaps(FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency) { return cFMOD_System_GetRecordDriverCaps(system, id, caps, minfrequency, maxfrequency); }
FMOD_RESULT FMOD_System_GetRecordPosition(FMOD_SYSTEM *system, int id, unsigned int *position) { return cFMOD_System_GetRecordPosition(system, id, position); }
FMOD_RESULT FMOD_System_RecordStart(FMOD_SYSTEM *system, int id, FMOD_SOUND *sound, FMOD_BOOL loop) { return cFMOD_System_RecordStart(system, id, sound, loop); }
FMOD_RESULT FMOD_System_RecordStop(FMOD_SYSTEM *system, int id) { return cFMOD_System_RecordStop(system, id); }
FMOD_RESULT FMOD_System_IsRecording(FMOD_SYSTEM *system, int id, FMOD_BOOL *recording) { return cFMOD_System_IsRecording(system, id, recording); }
FMOD_RESULT FMOD_System_CreateGeometry(FMOD_SYSTEM *system, int maxpolygons, int maxvertices, FMOD_GEOMETRY **geometry) { return cFMOD_System_CreateGeometry(system, maxpolygons, maxvertices, geometry); }
FMOD_RESULT FMOD_System_SetGeometrySettings(FMOD_SYSTEM *system, float maxworldsize) { return cFMOD_System_SetGeometrySettings(system, maxworldsize); }
FMOD_RESULT FMOD_System_GetGeometrySettings(FMOD_SYSTEM *system, float *maxworldsize) { return cFMOD_System_GetGeometrySettings(system, maxworldsize); }
FMOD_RESULT FMOD_System_LoadGeometry(FMOD_SYSTEM *system, const void *data, int datasize, FMOD_GEOMETRY **geometry) { return cFMOD_System_LoadGeometry(system, data, datasize, geometry); }
FMOD_RESULT FMOD_System_GetGeometryOcclusion(FMOD_SYSTEM *system, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb) { return cFMOD_System_GetGeometryOcclusion(system, listener, source, direct, reverb); }
FMOD_RESULT FMOD_System_SetNetworkProxy(FMOD_SYSTEM *system, const char *proxy) { return cFMOD_System_SetNetworkProxy(system, proxy); }
FMOD_RESULT FMOD_System_GetNetworkProxy(FMOD_SYSTEM *system, char *proxy, int proxylen) { return cFMOD_System_GetNetworkProxy(system, proxy, proxylen); }
FMOD_RESULT FMOD_System_SetNetworkTimeout(FMOD_SYSTEM *system, int timeout) { return cFMOD_System_SetNetworkTimeout(system, timeout); }
FMOD_RESULT FMOD_System_GetNetworkTimeout(FMOD_SYSTEM *system, int *timeout) { return cFMOD_System_GetNetworkTimeout(system, timeout); }
FMOD_RESULT FMOD_System_SetUserData(FMOD_SYSTEM *system, void *userdata) { return cFMOD_System_SetUserData(system, userdata); }
FMOD_RESULT FMOD_System_GetUserData(FMOD_SYSTEM *system, void **userdata) { return cFMOD_System_GetUserData(system, userdata); }
FMOD_RESULT FMOD_System_GetMemoryInfo(FMOD_SYSTEM *system, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_System_GetMemoryInfo(system, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_Sound_Release(FMOD_SOUND *sound) { return cFMOD_Sound_Release(sound); }
FMOD_RESULT FMOD_Sound_GetSystemObject(FMOD_SOUND *sound, FMOD_SYSTEM **system) { return cFMOD_Sound_GetSystemObject(sound, system); }
FMOD_RESULT FMOD_Sound_Lock(FMOD_SOUND *sound, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2) { return cFMOD_Sound_Lock(sound, offset, length, ptr1, ptr2, len1, len2); }
FMOD_RESULT FMOD_Sound_Unlock(FMOD_SOUND *sound, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2) { return cFMOD_Sound_Unlock(sound, ptr1, ptr2, len1, len2); }
FMOD_RESULT FMOD_Sound_SetDefaults(FMOD_SOUND *sound, float frequency, float volume, float pan, int priority) { return cFMOD_Sound_SetDefaults(sound, frequency, volume, pan, priority); }
FMOD_RESULT FMOD_Sound_GetDefaults(FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority) { return cFMOD_Sound_GetDefaults(sound, frequency, volume, pan, priority); }
FMOD_RESULT FMOD_Sound_SetVariations(FMOD_SOUND *sound, float frequencyvar, float volumevar, float panvar) { return cFMOD_Sound_SetVariations(sound, frequencyvar, volumevar, panvar); }
FMOD_RESULT FMOD_Sound_GetVariations(FMOD_SOUND *sound, float *frequencyvar, float *volumevar, float *panvar) { return cFMOD_Sound_GetVariations(sound, frequencyvar, volumevar, panvar); }
FMOD_RESULT FMOD_Sound_Set3DMinMaxDistance(FMOD_SOUND *sound, float min, float max) { return cFMOD_Sound_Set3DMinMaxDistance(sound, min, max); }
FMOD_RESULT FMOD_Sound_Get3DMinMaxDistance(FMOD_SOUND *sound, float *min, float *max) { return cFMOD_Sound_Get3DMinMaxDistance(sound, min, max); }
FMOD_RESULT FMOD_Sound_Set3DConeSettings(FMOD_SOUND *sound, float insideconeangle, float outsideconeangle, float outsidevolume) { return cFMOD_Sound_Set3DConeSettings(sound, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT FMOD_Sound_Get3DConeSettings(FMOD_SOUND *sound, float *insideconeangle, float *outsideconeangle, float *outsidevolume) { return cFMOD_Sound_Get3DConeSettings(sound, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT FMOD_Sound_Set3DCustomRolloff(FMOD_SOUND *sound, FMOD_VECTOR *points, int numpoints) { return cFMOD_Sound_Set3DCustomRolloff(sound, points, numpoints); }
FMOD_RESULT FMOD_Sound_Get3DCustomRolloff(FMOD_SOUND *sound, FMOD_VECTOR **points, int *numpoints) { return cFMOD_Sound_Get3DCustomRolloff(sound, points, numpoints); }
FMOD_RESULT FMOD_Sound_SetSubSound(FMOD_SOUND *sound, int index, FMOD_SOUND *subsound) { return cFMOD_Sound_SetSubSound(sound, index, subsound); }
FMOD_RESULT FMOD_Sound_GetSubSound(FMOD_SOUND *sound, int index, FMOD_SOUND **subsound) { return cFMOD_Sound_GetSubSound(sound, index, subsound); }
FMOD_RESULT FMOD_Sound_GetSubSoundParent(FMOD_SOUND *sound, FMOD_SOUND **parentsound) { return cFMOD_Sound_GetSubSoundParent(sound, parentsound); }
FMOD_RESULT FMOD_Sound_SetSubSoundSentence(FMOD_SOUND *sound, int *subsoundlist, int numsubsounds) { return cFMOD_Sound_SetSubSoundSentence(sound, subsoundlist, numsubsounds); }
FMOD_RESULT FMOD_Sound_GetName(FMOD_SOUND *sound, char *name, int namelen) { return cFMOD_Sound_GetName(sound, name, namelen); }
FMOD_RESULT FMOD_Sound_GetLength(FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype) { return cFMOD_Sound_GetLength(sound, length, lengthtype); }
FMOD_RESULT FMOD_Sound_GetFormat(FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits) { return cFMOD_Sound_GetFormat(sound, type, format, channels, bits); }
FMOD_RESULT FMOD_Sound_GetNumSubSounds(FMOD_SOUND *sound, int *numsubsounds) { return cFMOD_Sound_GetNumSubSounds(sound, numsubsounds); }
FMOD_RESULT FMOD_Sound_GetNumTags(FMOD_SOUND *sound, int *numtags, int *numtagsupdated) { return cFMOD_Sound_GetNumTags(sound, numtags, numtagsupdated); }
FMOD_RESULT FMOD_Sound_GetTag(FMOD_SOUND *sound, const char *name, int index, FMOD_TAG *tag) { return cFMOD_Sound_GetTag(sound, name, index, tag); }
FMOD_RESULT FMOD_Sound_GetOpenState(FMOD_SOUND *sound, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, FMOD_BOOL *starving, FMOD_BOOL *diskbusy) { return cFMOD_Sound_GetOpenState(sound, openstate, percentbuffered, starving, diskbusy); }
FMOD_RESULT FMOD_Sound_ReadData(FMOD_SOUND *sound, void *buffer, unsigned int lenbytes, unsigned int *read) { return cFMOD_Sound_ReadData(sound, buffer, lenbytes, read); }
FMOD_RESULT FMOD_Sound_SeekData(FMOD_SOUND *sound, unsigned int pcm) { return cFMOD_Sound_SeekData(sound, pcm); }
FMOD_RESULT FMOD_Sound_SetSoundGroup(FMOD_SOUND *sound, FMOD_SOUNDGROUP *soundgroup) { return cFMOD_Sound_SetSoundGroup(sound, soundgroup); }
FMOD_RESULT FMOD_Sound_GetSoundGroup(FMOD_SOUND *sound, FMOD_SOUNDGROUP **soundgroup) { return cFMOD_Sound_GetSoundGroup(sound, soundgroup); }
FMOD_RESULT FMOD_Sound_GetNumSyncPoints(FMOD_SOUND *sound, int *numsyncpoints) { return cFMOD_Sound_GetNumSyncPoints(sound, numsyncpoints); }
FMOD_RESULT FMOD_Sound_GetSyncPoint(FMOD_SOUND *sound, int index, FMOD_SYNCPOINT **point) { return cFMOD_Sound_GetSyncPoint(sound, index, point); }
FMOD_RESULT FMOD_Sound_GetSyncPointInfo(FMOD_SOUND *sound, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype) { return cFMOD_Sound_GetSyncPointInfo(sound, point, name, namelen, offset, offsettype); }
FMOD_RESULT FMOD_Sound_AddSyncPoint(FMOD_SOUND *sound, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point) { return cFMOD_Sound_AddSyncPoint(sound, offset, offsettype, name, point); }
FMOD_RESULT FMOD_Sound_DeleteSyncPoint(FMOD_SOUND *sound, FMOD_SYNCPOINT *point) { return cFMOD_Sound_DeleteSyncPoint(sound, point); }
FMOD_RESULT FMOD_Sound_SetMode(FMOD_SOUND *sound, FMOD_MODE mode) { return cFMOD_Sound_SetMode(sound, mode); }
FMOD_RESULT FMOD_Sound_GetMode(FMOD_SOUND *sound, FMOD_MODE *mode) { return cFMOD_Sound_GetMode(sound, mode); }
FMOD_RESULT FMOD_Sound_SetLoopCount(FMOD_SOUND *sound, int loopcount) { return cFMOD_Sound_SetLoopCount(sound, loopcount); }
FMOD_RESULT FMOD_Sound_GetLoopCount(FMOD_SOUND *sound, int *loopcount) { return cFMOD_Sound_GetLoopCount(sound, loopcount); }
FMOD_RESULT FMOD_Sound_SetLoopPoints(FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype) { return cFMOD_Sound_SetLoopPoints(sound, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT FMOD_Sound_GetLoopPoints(FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype) { return cFMOD_Sound_GetLoopPoints(sound, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT FMOD_Sound_GetMusicNumChannels(FMOD_SOUND *sound, int *numchannels) { return cFMOD_Sound_GetMusicNumChannels(sound, numchannels); }
FMOD_RESULT FMOD_Sound_SetMusicChannelVolume(FMOD_SOUND *sound, int channel, float volume) { return cFMOD_Sound_SetMusicChannelVolume(sound, channel, volume); }
FMOD_RESULT FMOD_Sound_GetMusicChannelVolume(FMOD_SOUND *sound, int channel, float *volume) { return cFMOD_Sound_GetMusicChannelVolume(sound, channel, volume); }
FMOD_RESULT FMOD_Sound_SetMusicSpeed(FMOD_SOUND *sound, float speed) { return cFMOD_Sound_SetMusicSpeed(sound, speed); }
FMOD_RESULT FMOD_Sound_GetMusicSpeed(FMOD_SOUND *sound, float *speed) { return cFMOD_Sound_GetMusicSpeed(sound, speed); }
FMOD_RESULT FMOD_Sound_SetUserData(FMOD_SOUND *sound, void *userdata) { return cFMOD_Sound_SetUserData(sound, userdata); }
FMOD_RESULT FMOD_Sound_GetUserData(FMOD_SOUND *sound, void **userdata) { return cFMOD_Sound_GetUserData(sound, userdata); }
FMOD_RESULT FMOD_Sound_GetMemoryInfo(FMOD_SOUND *sound, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_Sound_GetMemoryInfo(sound, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_Channel_GetSystemObject(FMOD_CHANNEL *channel, FMOD_SYSTEM **system) { return cFMOD_Channel_GetSystemObject(channel, system); }
FMOD_RESULT FMOD_Channel_Stop(FMOD_CHANNEL *channel) { return cFMOD_Channel_Stop(channel); }
FMOD_RESULT FMOD_Channel_SetPaused(FMOD_CHANNEL *channel, FMOD_BOOL paused) { return cFMOD_Channel_SetPaused(channel, paused); }
FMOD_RESULT FMOD_Channel_GetPaused(FMOD_CHANNEL *channel, FMOD_BOOL *paused) { return cFMOD_Channel_GetPaused(channel, paused); }
FMOD_RESULT FMOD_Channel_SetVolume(FMOD_CHANNEL *channel, float volume) { return cFMOD_Channel_SetVolume(channel, volume); }
FMOD_RESULT FMOD_Channel_GetVolume(FMOD_CHANNEL *channel, float *volume) { return cFMOD_Channel_GetVolume(channel, volume); }
FMOD_RESULT FMOD_Channel_SetFrequency(FMOD_CHANNEL *channel, float frequency) { return cFMOD_Channel_SetFrequency(channel, frequency); }
FMOD_RESULT FMOD_Channel_GetFrequency(FMOD_CHANNEL *channel, float *frequency) { return cFMOD_Channel_GetFrequency(channel, frequency); }
FMOD_RESULT FMOD_Channel_SetPan(FMOD_CHANNEL *channel, float pan) { return cFMOD_Channel_SetPan(channel, pan); }
FMOD_RESULT FMOD_Channel_GetPan(FMOD_CHANNEL *channel, float *pan) { return cFMOD_Channel_GetPan(channel, pan); }
FMOD_RESULT FMOD_Channel_SetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo) { return cFMOD_Channel_SetDelay(channel, delaytype, delayhi, delaylo); }
FMOD_RESULT FMOD_Channel_GetDelay(FMOD_CHANNEL *channel, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo) { return cFMOD_Channel_GetDelay(channel, delaytype, delayhi, delaylo); }
FMOD_RESULT FMOD_Channel_SetSpeakerMix(FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) { return cFMOD_Channel_SetSpeakerMix(channel, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT FMOD_Channel_GetSpeakerMix(FMOD_CHANNEL *channel, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright) { return cFMOD_Channel_GetSpeakerMix(channel, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT FMOD_Channel_SetSpeakerLevels(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cFMOD_Channel_SetSpeakerLevels(channel, speaker, levels, numlevels); }
FMOD_RESULT FMOD_Channel_GetSpeakerLevels(FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cFMOD_Channel_GetSpeakerLevels(channel, speaker, levels, numlevels); }
FMOD_RESULT FMOD_Channel_SetInputChannelMix(FMOD_CHANNEL *channel, float *levels, int numlevels) { return cFMOD_Channel_SetInputChannelMix(channel, levels, numlevels); }
FMOD_RESULT FMOD_Channel_GetInputChannelMix(FMOD_CHANNEL *channel, float *levels, int numlevels) { return cFMOD_Channel_GetInputChannelMix(channel, levels, numlevels); }
FMOD_RESULT FMOD_Channel_SetMute(FMOD_CHANNEL *channel, FMOD_BOOL mute) { return cFMOD_Channel_SetMute(channel, mute); }
FMOD_RESULT FMOD_Channel_GetMute(FMOD_CHANNEL *channel, FMOD_BOOL *mute) { return cFMOD_Channel_GetMute(channel, mute); }
FMOD_RESULT FMOD_Channel_SetPriority(FMOD_CHANNEL *channel, int priority) { return cFMOD_Channel_SetPriority(channel, priority); }
FMOD_RESULT FMOD_Channel_GetPriority(FMOD_CHANNEL *channel, int *priority) { return cFMOD_Channel_GetPriority(channel, priority); }
FMOD_RESULT FMOD_Channel_SetPosition(FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype) { return cFMOD_Channel_SetPosition(channel, position, postype); }
FMOD_RESULT FMOD_Channel_GetPosition(FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype) { return cFMOD_Channel_GetPosition(channel, position, postype); }
FMOD_RESULT FMOD_Channel_SetReverbProperties(FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop) { return cFMOD_Channel_SetReverbProperties(channel, prop); }
FMOD_RESULT FMOD_Channel_GetReverbProperties(FMOD_CHANNEL *channel, FMOD_REVERB_CHANNELPROPERTIES *prop) { return cFMOD_Channel_GetReverbProperties(channel, prop); }
FMOD_RESULT FMOD_Channel_SetLowPassGain(FMOD_CHANNEL *channel, float gain) { return cFMOD_Channel_SetLowPassGain(channel, gain); }
FMOD_RESULT FMOD_Channel_GetLowPassGain(FMOD_CHANNEL *channel, float *gain) { return cFMOD_Channel_GetLowPassGain(channel, gain); }
FMOD_RESULT FMOD_Channel_SetChannelGroup(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup) { return cFMOD_Channel_SetChannelGroup(channel, channelgroup); }
FMOD_RESULT FMOD_Channel_GetChannelGroup(FMOD_CHANNEL *channel, FMOD_CHANNELGROUP **channelgroup) { return cFMOD_Channel_GetChannelGroup(channel, channelgroup); }
FMOD_RESULT FMOD_Channel_SetCallback(FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACK callback) { return cFMOD_Channel_SetCallback(channel, callback); }
FMOD_RESULT FMOD_Channel_Set3DAttributes(FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) { return cFMOD_Channel_Set3DAttributes(channel, pos, vel); }
FMOD_RESULT FMOD_Channel_Get3DAttributes(FMOD_CHANNEL *channel, FMOD_VECTOR *pos, FMOD_VECTOR *vel) { return cFMOD_Channel_Get3DAttributes(channel, pos, vel); }
FMOD_RESULT FMOD_Channel_Set3DMinMaxDistance(FMOD_CHANNEL *channel, float mindistance, float maxdistance) { return cFMOD_Channel_Set3DMinMaxDistance(channel, mindistance, maxdistance); }
FMOD_RESULT FMOD_Channel_Get3DMinMaxDistance(FMOD_CHANNEL *channel, float *mindistance, float *maxdistance) { return cFMOD_Channel_Get3DMinMaxDistance(channel, mindistance, maxdistance); }
FMOD_RESULT FMOD_Channel_Set3DConeSettings(FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume) { return cFMOD_Channel_Set3DConeSettings(channel, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT FMOD_Channel_Get3DConeSettings(FMOD_CHANNEL *channel, float *insideconeangle, float *outsideconeangle, float *outsidevolume) { return cFMOD_Channel_Get3DConeSettings(channel, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT FMOD_Channel_Set3DConeOrientation(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation) { return cFMOD_Channel_Set3DConeOrientation(channel, orientation); }
FMOD_RESULT FMOD_Channel_Get3DConeOrientation(FMOD_CHANNEL *channel, FMOD_VECTOR *orientation) { return cFMOD_Channel_Get3DConeOrientation(channel, orientation); }
FMOD_RESULT FMOD_Channel_Set3DCustomRolloff(FMOD_CHANNEL *channel, FMOD_VECTOR *points, int numpoints) { return cFMOD_Channel_Set3DCustomRolloff(channel, points, numpoints); }
FMOD_RESULT FMOD_Channel_Get3DCustomRolloff(FMOD_CHANNEL *channel, FMOD_VECTOR **points, int *numpoints) { return cFMOD_Channel_Get3DCustomRolloff(channel, points, numpoints); }
FMOD_RESULT FMOD_Channel_Set3DOcclusion(FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion) { return cFMOD_Channel_Set3DOcclusion(channel, directocclusion, reverbocclusion); }
FMOD_RESULT FMOD_Channel_Get3DOcclusion(FMOD_CHANNEL *channel, float *directocclusion, float *reverbocclusion) { return cFMOD_Channel_Get3DOcclusion(channel, directocclusion, reverbocclusion); }
FMOD_RESULT FMOD_Channel_Set3DSpread(FMOD_CHANNEL *channel, float angle) { return cFMOD_Channel_Set3DSpread(channel, angle); }
FMOD_RESULT FMOD_Channel_Get3DSpread(FMOD_CHANNEL *channel, float *angle) { return cFMOD_Channel_Get3DSpread(channel, angle); }
FMOD_RESULT FMOD_Channel_Set3DPanLevel(FMOD_CHANNEL *channel, float level) { return cFMOD_Channel_Set3DPanLevel(channel, level); }
FMOD_RESULT FMOD_Channel_Get3DPanLevel(FMOD_CHANNEL *channel, float *level) { return cFMOD_Channel_Get3DPanLevel(channel, level); }
FMOD_RESULT FMOD_Channel_Set3DDopplerLevel(FMOD_CHANNEL *channel, float level) { return cFMOD_Channel_Set3DDopplerLevel(channel, level); }
FMOD_RESULT FMOD_Channel_Get3DDopplerLevel(FMOD_CHANNEL *channel, float *level) { return cFMOD_Channel_Get3DDopplerLevel(channel, level); }
FMOD_RESULT FMOD_Channel_Set3DDistanceFilter(FMOD_CHANNEL *channel, FMOD_BOOL custom, float customLevel, float centerFreq) { return cFMOD_Channel_Set3DDistanceFilter(channel, custom, customLevel, centerFreq); }
FMOD_RESULT FMOD_Channel_Get3DDistanceFilter(FMOD_CHANNEL *channel, FMOD_BOOL *custom, float *customLevel, float *centerFreq) { return cFMOD_Channel_Get3DDistanceFilter(channel, custom, customLevel, centerFreq); }
FMOD_RESULT FMOD_Channel_GetDSPHead(FMOD_CHANNEL *channel, FMOD_DSP **dsp) { return cFMOD_Channel_GetDSPHead(channel, dsp); }
FMOD_RESULT FMOD_Channel_AddDSP(FMOD_CHANNEL *channel, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection) { return cFMOD_Channel_AddDSP(channel, dsp, connection); }
FMOD_RESULT FMOD_Channel_IsPlaying(FMOD_CHANNEL *channel, FMOD_BOOL *isplaying) { return cFMOD_Channel_IsPlaying(channel, isplaying); }
FMOD_RESULT FMOD_Channel_IsVirtual(FMOD_CHANNEL *channel, FMOD_BOOL *isvirtual) { return cFMOD_Channel_IsVirtual(channel, isvirtual); }
FMOD_RESULT FMOD_Channel_GetAudibility(FMOD_CHANNEL *channel, float *audibility) { return cFMOD_Channel_GetAudibility(channel, audibility); }
FMOD_RESULT FMOD_Channel_GetCurrentSound(FMOD_CHANNEL *channel, FMOD_SOUND **sound) { return cFMOD_Channel_GetCurrentSound(channel, sound); }
FMOD_RESULT FMOD_Channel_GetSpectrum(FMOD_CHANNEL *channel, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cFMOD_Channel_GetSpectrum(channel, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT FMOD_Channel_GetWaveData(FMOD_CHANNEL *channel, float *wavearray, int numvalues, int channeloffset) { return cFMOD_Channel_GetWaveData(channel, wavearray, numvalues, channeloffset); }
FMOD_RESULT FMOD_Channel_GetIndex(FMOD_CHANNEL *channel, int *index) { return cFMOD_Channel_GetIndex(channel, index); }
FMOD_RESULT FMOD_Channel_SetMode(FMOD_CHANNEL *channel, FMOD_MODE mode) { return cFMOD_Channel_SetMode(channel, mode); }
FMOD_RESULT FMOD_Channel_GetMode(FMOD_CHANNEL *channel, FMOD_MODE *mode) { return cFMOD_Channel_GetMode(channel, mode); }
FMOD_RESULT FMOD_Channel_SetLoopCount(FMOD_CHANNEL *channel, int loopcount) { return cFMOD_Channel_SetLoopCount(channel, loopcount); }
FMOD_RESULT FMOD_Channel_GetLoopCount(FMOD_CHANNEL *channel, int *loopcount) { return cFMOD_Channel_GetLoopCount(channel, loopcount); }
FMOD_RESULT FMOD_Channel_SetLoopPoints(FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype) { return cFMOD_Channel_SetLoopPoints(channel, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT FMOD_Channel_GetLoopPoints(FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype) { return cFMOD_Channel_GetLoopPoints(channel, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT FMOD_Channel_SetUserData(FMOD_CHANNEL *channel, void *userdata) { return cFMOD_Channel_SetUserData(channel, userdata); }
FMOD_RESULT FMOD_Channel_GetUserData(FMOD_CHANNEL *channel, void **userdata) { return cFMOD_Channel_GetUserData(channel, userdata); }
FMOD_RESULT FMOD_Channel_GetMemoryInfo(FMOD_CHANNEL *channel, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_Channel_GetMemoryInfo(channel, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_ChannelGroup_Release(FMOD_CHANNELGROUP *channelgroup) { return cFMOD_ChannelGroup_Release(channelgroup); }
FMOD_RESULT FMOD_ChannelGroup_GetSystemObject(FMOD_CHANNELGROUP *channelgroup, FMOD_SYSTEM **system) { return cFMOD_ChannelGroup_GetSystemObject(channelgroup, system); }
FMOD_RESULT FMOD_ChannelGroup_SetVolume(FMOD_CHANNELGROUP *channelgroup, float volume) { return cFMOD_ChannelGroup_SetVolume(channelgroup, volume); }
FMOD_RESULT FMOD_ChannelGroup_GetVolume(FMOD_CHANNELGROUP *channelgroup, float *volume) { return cFMOD_ChannelGroup_GetVolume(channelgroup, volume); }
FMOD_RESULT FMOD_ChannelGroup_SetPitch(FMOD_CHANNELGROUP *channelgroup, float pitch) { return cFMOD_ChannelGroup_SetPitch(channelgroup, pitch); }
FMOD_RESULT FMOD_ChannelGroup_GetPitch(FMOD_CHANNELGROUP *channelgroup, float *pitch) { return cFMOD_ChannelGroup_GetPitch(channelgroup, pitch); }
FMOD_RESULT FMOD_ChannelGroup_Set3DOcclusion(FMOD_CHANNELGROUP *channelgroup, float directocclusion, float reverbocclusion) { return cFMOD_ChannelGroup_Set3DOcclusion(channelgroup, directocclusion, reverbocclusion); }
FMOD_RESULT FMOD_ChannelGroup_Get3DOcclusion(FMOD_CHANNELGROUP *channelgroup, float *directocclusion, float *reverbocclusion) { return cFMOD_ChannelGroup_Get3DOcclusion(channelgroup, directocclusion, reverbocclusion); }
FMOD_RESULT FMOD_ChannelGroup_SetPaused(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused) { return cFMOD_ChannelGroup_SetPaused(channelgroup, paused); }
FMOD_RESULT FMOD_ChannelGroup_GetPaused(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *paused) { return cFMOD_ChannelGroup_GetPaused(channelgroup, paused); }
FMOD_RESULT FMOD_ChannelGroup_SetMute(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL mute) { return cFMOD_ChannelGroup_SetMute(channelgroup, mute); }
FMOD_RESULT FMOD_ChannelGroup_GetMute(FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL *mute) { return cFMOD_ChannelGroup_GetMute(channelgroup, mute); }
FMOD_RESULT FMOD_ChannelGroup_Stop(FMOD_CHANNELGROUP *channelgroup) { return cFMOD_ChannelGroup_Stop(channelgroup); }
FMOD_RESULT FMOD_ChannelGroup_OverrideVolume(FMOD_CHANNELGROUP *channelgroup, float volume) { return cFMOD_ChannelGroup_OverrideVolume(channelgroup, volume); }
FMOD_RESULT FMOD_ChannelGroup_OverrideFrequency(FMOD_CHANNELGROUP *channelgroup, float frequency) { return cFMOD_ChannelGroup_OverrideFrequency(channelgroup, frequency); }
FMOD_RESULT FMOD_ChannelGroup_OverridePan(FMOD_CHANNELGROUP *channelgroup, float pan) { return cFMOD_ChannelGroup_OverridePan(channelgroup, pan); }
FMOD_RESULT FMOD_ChannelGroup_OverrideReverbProperties(FMOD_CHANNELGROUP *channelgroup, const FMOD_REVERB_CHANNELPROPERTIES *prop) { return cFMOD_ChannelGroup_OverrideReverbProperties(channelgroup, prop); }
FMOD_RESULT FMOD_ChannelGroup_Override3DAttributes(FMOD_CHANNELGROUP *channelgroup, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) { return cFMOD_ChannelGroup_Override3DAttributes(channelgroup, pos, vel); }
FMOD_RESULT FMOD_ChannelGroup_OverrideSpeakerMix(FMOD_CHANNELGROUP *channelgroup, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) { return cFMOD_ChannelGroup_OverrideSpeakerMix(channelgroup, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT FMOD_ChannelGroup_AddGroup(FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP *group) { return cFMOD_ChannelGroup_AddGroup(channelgroup, group); }
FMOD_RESULT FMOD_ChannelGroup_GetNumGroups(FMOD_CHANNELGROUP *channelgroup, int *numgroups) { return cFMOD_ChannelGroup_GetNumGroups(channelgroup, numgroups); }
FMOD_RESULT FMOD_ChannelGroup_GetGroup(FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNELGROUP **group) { return cFMOD_ChannelGroup_GetGroup(channelgroup, index, group); }
FMOD_RESULT FMOD_ChannelGroup_GetParentGroup(FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP **group) { return cFMOD_ChannelGroup_GetParentGroup(channelgroup, group); }
FMOD_RESULT FMOD_ChannelGroup_GetDSPHead(FMOD_CHANNELGROUP *channelgroup, FMOD_DSP **dsp) { return cFMOD_ChannelGroup_GetDSPHead(channelgroup, dsp); }
FMOD_RESULT FMOD_ChannelGroup_AddDSP(FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp, FMOD_DSPCONNECTION **connection) { return cFMOD_ChannelGroup_AddDSP(channelgroup, dsp, connection); }
FMOD_RESULT FMOD_ChannelGroup_GetName(FMOD_CHANNELGROUP *channelgroup, char *name, int namelen) { return cFMOD_ChannelGroup_GetName(channelgroup, name, namelen); }
FMOD_RESULT FMOD_ChannelGroup_GetNumChannels(FMOD_CHANNELGROUP *channelgroup, int *numchannels) { return cFMOD_ChannelGroup_GetNumChannels(channelgroup, numchannels); }
FMOD_RESULT FMOD_ChannelGroup_GetChannel(FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNEL **channel) { return cFMOD_ChannelGroup_GetChannel(channelgroup, index, channel); }
FMOD_RESULT FMOD_ChannelGroup_GetSpectrum(FMOD_CHANNELGROUP *channelgroup, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cFMOD_ChannelGroup_GetSpectrum(channelgroup, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT FMOD_ChannelGroup_GetWaveData(FMOD_CHANNELGROUP *channelgroup, float *wavearray, int numvalues, int channeloffset) { return cFMOD_ChannelGroup_GetWaveData(channelgroup, wavearray, numvalues, channeloffset); }
FMOD_RESULT FMOD_ChannelGroup_SetUserData(FMOD_CHANNELGROUP *channelgroup, void *userdata) { return cFMOD_ChannelGroup_SetUserData(channelgroup, userdata); }
FMOD_RESULT FMOD_ChannelGroup_GetUserData(FMOD_CHANNELGROUP *channelgroup, void **userdata) { return cFMOD_ChannelGroup_GetUserData(channelgroup, userdata); }
FMOD_RESULT FMOD_ChannelGroup_GetMemoryInfo(FMOD_CHANNELGROUP *channelgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_ChannelGroup_GetMemoryInfo(channelgroup, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_SoundGroup_Release(FMOD_SOUNDGROUP *soundgroup) { return cFMOD_SoundGroup_Release(soundgroup); }
FMOD_RESULT FMOD_SoundGroup_GetSystemObject(FMOD_SOUNDGROUP *soundgroup, FMOD_SYSTEM **system) { return cFMOD_SoundGroup_GetSystemObject(soundgroup, system); }
FMOD_RESULT FMOD_SoundGroup_SetMaxAudible(FMOD_SOUNDGROUP *soundgroup, int maxaudible) { return cFMOD_SoundGroup_SetMaxAudible(soundgroup, maxaudible); }
FMOD_RESULT FMOD_SoundGroup_GetMaxAudible(FMOD_SOUNDGROUP *soundgroup, int *maxaudible) { return cFMOD_SoundGroup_GetMaxAudible(soundgroup, maxaudible); }
FMOD_RESULT FMOD_SoundGroup_SetMaxAudibleBehavior(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR behavior) { return cFMOD_SoundGroup_SetMaxAudibleBehavior(soundgroup, behavior); }
FMOD_RESULT FMOD_SoundGroup_GetMaxAudibleBehavior(FMOD_SOUNDGROUP *soundgroup, FMOD_SOUNDGROUP_BEHAVIOR *behavior) { return cFMOD_SoundGroup_GetMaxAudibleBehavior(soundgroup, behavior); }
FMOD_RESULT FMOD_SoundGroup_SetMuteFadeSpeed(FMOD_SOUNDGROUP *soundgroup, float speed) { return cFMOD_SoundGroup_SetMuteFadeSpeed(soundgroup, speed); }
FMOD_RESULT FMOD_SoundGroup_GetMuteFadeSpeed(FMOD_SOUNDGROUP *soundgroup, float *speed) { return cFMOD_SoundGroup_GetMuteFadeSpeed(soundgroup, speed); }
FMOD_RESULT FMOD_SoundGroup_SetVolume(FMOD_SOUNDGROUP *soundgroup, float volume) { return cFMOD_SoundGroup_SetVolume(soundgroup, volume); }
FMOD_RESULT FMOD_SoundGroup_GetVolume(FMOD_SOUNDGROUP *soundgroup, float *volume) { return cFMOD_SoundGroup_GetVolume(soundgroup, volume); }
FMOD_RESULT FMOD_SoundGroup_Stop(FMOD_SOUNDGROUP *soundgroup) { return cFMOD_SoundGroup_Stop(soundgroup); }
FMOD_RESULT FMOD_SoundGroup_GetName(FMOD_SOUNDGROUP *soundgroup, char *name, int namelen) { return cFMOD_SoundGroup_GetName(soundgroup, name, namelen); }
FMOD_RESULT FMOD_SoundGroup_GetNumSounds(FMOD_SOUNDGROUP *soundgroup, int *numsounds) { return cFMOD_SoundGroup_GetNumSounds(soundgroup, numsounds); }
FMOD_RESULT FMOD_SoundGroup_GetSound(FMOD_SOUNDGROUP *soundgroup, int index, FMOD_SOUND **sound) { return cFMOD_SoundGroup_GetSound(soundgroup, index, sound); }
FMOD_RESULT FMOD_SoundGroup_GetNumPlaying(FMOD_SOUNDGROUP *soundgroup, int *numplaying) { return cFMOD_SoundGroup_GetNumPlaying(soundgroup, numplaying); }
FMOD_RESULT FMOD_SoundGroup_SetUserData(FMOD_SOUNDGROUP *soundgroup, void *userdata) { return cFMOD_SoundGroup_SetUserData(soundgroup, userdata); }
FMOD_RESULT FMOD_SoundGroup_GetUserData(FMOD_SOUNDGROUP *soundgroup, void **userdata) { return cFMOD_SoundGroup_GetUserData(soundgroup, userdata); }
FMOD_RESULT FMOD_SoundGroup_GetMemoryInfo(FMOD_SOUNDGROUP *soundgroup, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_SoundGroup_GetMemoryInfo(soundgroup, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_DSP_Release(FMOD_DSP *dsp) { return cFMOD_DSP_Release(dsp); }
FMOD_RESULT FMOD_DSP_GetSystemObject(FMOD_DSP *dsp, FMOD_SYSTEM **system) { return cFMOD_DSP_GetSystemObject(dsp, system); }
FMOD_RESULT FMOD_DSP_AddInput(FMOD_DSP *dsp, FMOD_DSP *target, FMOD_DSPCONNECTION **connection) { return cFMOD_DSP_AddInput(dsp, target, connection); }
FMOD_RESULT FMOD_DSP_DisconnectFrom(FMOD_DSP *dsp, FMOD_DSP *target) { return cFMOD_DSP_DisconnectFrom(dsp, target); }
FMOD_RESULT FMOD_DSP_DisconnectAll(FMOD_DSP *dsp, FMOD_BOOL inputs, FMOD_BOOL outputs) { return cFMOD_DSP_DisconnectAll(dsp, inputs, outputs); }
FMOD_RESULT FMOD_DSP_Remove(FMOD_DSP *dsp) { return cFMOD_DSP_Remove(dsp); }
FMOD_RESULT FMOD_DSP_GetNumInputs(FMOD_DSP *dsp, int *numinputs) { return cFMOD_DSP_GetNumInputs(dsp, numinputs); }
FMOD_RESULT FMOD_DSP_GetNumOutputs(FMOD_DSP *dsp, int *numoutputs) { return cFMOD_DSP_GetNumOutputs(dsp, numoutputs); }
FMOD_RESULT FMOD_DSP_GetInput(FMOD_DSP *dsp, int index, FMOD_DSP **input, FMOD_DSPCONNECTION **inputconnection) { return cFMOD_DSP_GetInput(dsp, index, input, inputconnection); }
FMOD_RESULT FMOD_DSP_GetOutput(FMOD_DSP *dsp, int index, FMOD_DSP **output, FMOD_DSPCONNECTION **outputconnection) { return cFMOD_DSP_GetOutput(dsp, index, output, outputconnection); }
FMOD_RESULT FMOD_DSP_SetActive(FMOD_DSP *dsp, FMOD_BOOL active) { return cFMOD_DSP_SetActive(dsp, active); }
FMOD_RESULT FMOD_DSP_GetActive(FMOD_DSP *dsp, FMOD_BOOL *active) { return cFMOD_DSP_GetActive(dsp, active); }
FMOD_RESULT FMOD_DSP_SetBypass(FMOD_DSP *dsp, FMOD_BOOL bypass) { return cFMOD_DSP_SetBypass(dsp, bypass); }
FMOD_RESULT FMOD_DSP_GetBypass(FMOD_DSP *dsp, FMOD_BOOL *bypass) { return cFMOD_DSP_GetBypass(dsp, bypass); }
FMOD_RESULT FMOD_DSP_SetSpeakerActive(FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL active) { return cFMOD_DSP_SetSpeakerActive(dsp, speaker, active); }
FMOD_RESULT FMOD_DSP_GetSpeakerActive(FMOD_DSP *dsp, FMOD_SPEAKER speaker, FMOD_BOOL *active) { return cFMOD_DSP_GetSpeakerActive(dsp, speaker, active); }
FMOD_RESULT FMOD_DSP_Reset(FMOD_DSP *dsp) { return cFMOD_DSP_Reset(dsp); }
FMOD_RESULT FMOD_DSP_SetParameter(FMOD_DSP *dsp, int index, float value) { return cFMOD_DSP_SetParameter(dsp, index, value); }
FMOD_RESULT FMOD_DSP_GetParameter(FMOD_DSP *dsp, int index, float *value, char *valuestr, int valuestrlen) { return cFMOD_DSP_GetParameter(dsp, index, value, valuestr, valuestrlen); }
FMOD_RESULT FMOD_DSP_GetNumParameters(FMOD_DSP *dsp, int *numparams) { return cFMOD_DSP_GetNumParameters(dsp, numparams); }
FMOD_RESULT FMOD_DSP_GetParameterInfo(FMOD_DSP *dsp, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max) { return cFMOD_DSP_GetParameterInfo(dsp, index, name, label, description, descriptionlen, min, max); }
FMOD_RESULT FMOD_DSP_ShowConfigDialog(FMOD_DSP *dsp, void *hwnd, FMOD_BOOL show) { return cFMOD_DSP_ShowConfigDialog(dsp, hwnd, show); }
FMOD_RESULT FMOD_DSP_GetInfo(FMOD_DSP *dsp, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight) { return cFMOD_DSP_GetInfo(dsp, name, version, channels, configwidth, configheight); }
FMOD_RESULT FMOD_DSP_GetType(FMOD_DSP *dsp, FMOD_DSP_TYPE *type) { return cFMOD_DSP_GetType(dsp, type); }
FMOD_RESULT FMOD_DSP_SetDefaults(FMOD_DSP *dsp, float frequency, float volume, float pan, int priority) { return cFMOD_DSP_SetDefaults(dsp, frequency, volume, pan, priority); }
FMOD_RESULT FMOD_DSP_GetDefaults(FMOD_DSP *dsp, float *frequency, float *volume, float *pan, int *priority) { return cFMOD_DSP_GetDefaults(dsp, frequency, volume, pan, priority); }
FMOD_RESULT FMOD_DSP_SetUserData(FMOD_DSP *dsp, void *userdata) { return cFMOD_DSP_SetUserData(dsp, userdata); }
FMOD_RESULT FMOD_DSP_GetUserData(FMOD_DSP *dsp, void **userdata) { return cFMOD_DSP_GetUserData(dsp, userdata); }
FMOD_RESULT FMOD_DSP_GetMemoryInfo(FMOD_DSP *dsp, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_DSP_GetMemoryInfo(dsp, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_DSPConnection_GetInput(FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **input) { return cFMOD_DSPConnection_GetInput(dspconnection, input); }
FMOD_RESULT FMOD_DSPConnection_GetOutput(FMOD_DSPCONNECTION *dspconnection, FMOD_DSP **output) { return cFMOD_DSPConnection_GetOutput(dspconnection, output); }
FMOD_RESULT FMOD_DSPConnection_SetMix(FMOD_DSPCONNECTION *dspconnection, float volume) { return cFMOD_DSPConnection_SetMix(dspconnection, volume); }
FMOD_RESULT FMOD_DSPConnection_GetMix(FMOD_DSPCONNECTION *dspconnection, float *volume) { return cFMOD_DSPConnection_GetMix(dspconnection, volume); }
FMOD_RESULT FMOD_DSPConnection_SetLevels(FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cFMOD_DSPConnection_SetLevels(dspconnection, speaker, levels, numlevels); }
FMOD_RESULT FMOD_DSPConnection_GetLevels(FMOD_DSPCONNECTION *dspconnection, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cFMOD_DSPConnection_GetLevels(dspconnection, speaker, levels, numlevels); }
FMOD_RESULT FMOD_DSPConnection_SetUserData(FMOD_DSPCONNECTION *dspconnection, void *userdata) { return cFMOD_DSPConnection_SetUserData(dspconnection, userdata); }
FMOD_RESULT FMOD_DSPConnection_GetUserData(FMOD_DSPCONNECTION *dspconnection, void **userdata) { return cFMOD_DSPConnection_GetUserData(dspconnection, userdata); }
FMOD_RESULT FMOD_DSPConnection_GetMemoryInfo(FMOD_DSPCONNECTION *dspconnection, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_DSPConnection_GetMemoryInfo(dspconnection, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_Geometry_Release(FMOD_GEOMETRY *geometry) { return cFMOD_Geometry_Release(geometry); }
FMOD_RESULT FMOD_Geometry_AddPolygon(FMOD_GEOMETRY *geometry, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex) { return cFMOD_Geometry_AddPolygon(geometry, directocclusion, reverbocclusion, doublesided, numvertices, vertices, polygonindex); }
FMOD_RESULT FMOD_Geometry_GetNumPolygons(FMOD_GEOMETRY *geometry, int *numpolygons) { return cFMOD_Geometry_GetNumPolygons(geometry, numpolygons); }
FMOD_RESULT FMOD_Geometry_GetMaxPolygons(FMOD_GEOMETRY *geometry, int *maxpolygons, int *maxvertices) { return cFMOD_Geometry_GetMaxPolygons(geometry, maxpolygons, maxvertices); }
FMOD_RESULT FMOD_Geometry_GetPolygonNumVertices(FMOD_GEOMETRY *geometry, int index, int *numvertices) { return cFMOD_Geometry_GetPolygonNumVertices(geometry, index, numvertices); }
FMOD_RESULT FMOD_Geometry_SetPolygonVertex(FMOD_GEOMETRY *geometry, int index, int vertexindex, const FMOD_VECTOR *vertex) { return cFMOD_Geometry_SetPolygonVertex(geometry, index, vertexindex, vertex); }
FMOD_RESULT FMOD_Geometry_GetPolygonVertex(FMOD_GEOMETRY *geometry, int index, int vertexindex, FMOD_VECTOR *vertex) { return cFMOD_Geometry_GetPolygonVertex(geometry, index, vertexindex, vertex); }
FMOD_RESULT FMOD_Geometry_SetPolygonAttributes(FMOD_GEOMETRY *geometry, int index, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided) { return cFMOD_Geometry_SetPolygonAttributes(geometry, index, directocclusion, reverbocclusion, doublesided); }
FMOD_RESULT FMOD_Geometry_GetPolygonAttributes(FMOD_GEOMETRY *geometry, int index, float *directocclusion, float *reverbocclusion, FMOD_BOOL *doublesided) { return cFMOD_Geometry_GetPolygonAttributes(geometry, index, directocclusion, reverbocclusion, doublesided); }
FMOD_RESULT FMOD_Geometry_SetActive(FMOD_GEOMETRY *geometry, FMOD_BOOL active) { return cFMOD_Geometry_SetActive(geometry, active); }
FMOD_RESULT FMOD_Geometry_GetActive(FMOD_GEOMETRY *geometry, FMOD_BOOL *active) { return cFMOD_Geometry_GetActive(geometry, active); }
FMOD_RESULT FMOD_Geometry_SetRotation(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *forward, const FMOD_VECTOR *up) { return cFMOD_Geometry_SetRotation(geometry, forward, up); }
FMOD_RESULT FMOD_Geometry_GetRotation(FMOD_GEOMETRY *geometry, FMOD_VECTOR *forward, FMOD_VECTOR *up) { return cFMOD_Geometry_GetRotation(geometry, forward, up); }
FMOD_RESULT FMOD_Geometry_SetPosition(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *position) { return cFMOD_Geometry_SetPosition(geometry, position); }
FMOD_RESULT FMOD_Geometry_GetPosition(FMOD_GEOMETRY *geometry, FMOD_VECTOR *position) { return cFMOD_Geometry_GetPosition(geometry, position); }
FMOD_RESULT FMOD_Geometry_SetScale(FMOD_GEOMETRY *geometry, const FMOD_VECTOR *scale) { return cFMOD_Geometry_SetScale(geometry, scale); }
FMOD_RESULT FMOD_Geometry_GetScale(FMOD_GEOMETRY *geometry, FMOD_VECTOR *scale) { return cFMOD_Geometry_GetScale(geometry, scale); }
FMOD_RESULT FMOD_Geometry_Save(FMOD_GEOMETRY *geometry, void *data, int *datasize) { return cFMOD_Geometry_Save(geometry, data, datasize); }
FMOD_RESULT FMOD_Geometry_SetUserData(FMOD_GEOMETRY *geometry, void *userdata) { return cFMOD_Geometry_SetUserData(geometry, userdata); }
FMOD_RESULT FMOD_Geometry_GetUserData(FMOD_GEOMETRY *geometry, void **userdata) { return cFMOD_Geometry_GetUserData(geometry, userdata); }
FMOD_RESULT FMOD_Geometry_GetMemoryInfo(FMOD_GEOMETRY *geometry, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_Geometry_GetMemoryInfo(geometry, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT FMOD_Reverb_Release(FMOD_REVERB *reverb) { return cFMOD_Reverb_Release(reverb); }
FMOD_RESULT FMOD_Reverb_Set3DAttributes(FMOD_REVERB *reverb, const FMOD_VECTOR *position, float mindistance, float maxdistance) { return cFMOD_Reverb_Set3DAttributes(reverb, position, mindistance, maxdistance); }
FMOD_RESULT FMOD_Reverb_Get3DAttributes(FMOD_REVERB *reverb, FMOD_VECTOR *position, float *mindistance, float *maxdistance) { return cFMOD_Reverb_Get3DAttributes(reverb, position, mindistance, maxdistance); }
FMOD_RESULT FMOD_Reverb_SetProperties(FMOD_REVERB *reverb, const FMOD_REVERB_PROPERTIES *properties) { return cFMOD_Reverb_SetProperties(reverb, properties); }
FMOD_RESULT FMOD_Reverb_GetProperties(FMOD_REVERB *reverb, FMOD_REVERB_PROPERTIES *properties) { return cFMOD_Reverb_GetProperties(reverb, properties); }
FMOD_RESULT FMOD_Reverb_SetActive(FMOD_REVERB *reverb, FMOD_BOOL active) { return cFMOD_Reverb_SetActive(reverb, active); }
FMOD_RESULT FMOD_Reverb_GetActive(FMOD_REVERB *reverb, FMOD_BOOL *active) { return cFMOD_Reverb_GetActive(reverb, active); }
FMOD_RESULT FMOD_Reverb_SetUserData(FMOD_REVERB *reverb, void *userdata) { return cFMOD_Reverb_SetUserData(reverb, userdata); }
FMOD_RESULT FMOD_Reverb_GetUserData(FMOD_REVERB *reverb, void **userdata) { return cFMOD_Reverb_GetUserData(reverb, userdata); }
FMOD_RESULT FMOD_Reverb_GetMemoryInfo(FMOD_REVERB *reverb, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cFMOD_Reverb_GetMemoryInfo(reverb, memorybits, event_memorybits, memoryused, memoryused_details); }

/* PSP2-specific */

FMOD_RESULT FMOD_ChannelGroup_SetAudibilityFactor(FMOD_CHANNELGROUP *channelgroup, float factor) { return cFMOD_ChannelGroup_SetAudibilityFactor(channelgroup, factor); }
FMOD_RESULT FMOD_ChannelGroup_GetAudibilityFactor(FMOD_CHANNELGROUP *channelgroup, float *factor) { return cFMOD_ChannelGroup_GetAudibilityFactor(channelgroup, factor); }

/* CPP */

FMOD_RESULT F_API _ZN4FMOD6System7releaseEv(void *instance) { return cpp_ZN4FMOD6System7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System9setOutputE15FMOD_OUTPUTTYPE(void *instance, FMOD_OUTPUTTYPE output) { return cpp_ZN4FMOD6System9setOutputE15FMOD_OUTPUTTYPE(instance, output); }
FMOD_RESULT F_API _ZN4FMOD6System9getOutputEP15FMOD_OUTPUTTYPE(void *instance, FMOD_OUTPUTTYPE *output) { return cpp_ZN4FMOD6System9getOutputEP15FMOD_OUTPUTTYPE(instance, output); }
FMOD_RESULT F_API _ZN4FMOD6System13getNumDriversEPi(void *instance, int *numdrivers) { return cpp_ZN4FMOD6System13getNumDriversEPi(instance, numdrivers); }
FMOD_RESULT F_API _ZN4FMOD6System13getDriverInfoEiPciP9FMOD_GUID(void *instance, int id, char *name, int namelen, FMOD_GUID *guid) { return cpp_ZN4FMOD6System13getDriverInfoEiPciP9FMOD_GUID(instance, id, name, namelen, guid); }
FMOD_RESULT F_API _ZN4FMOD6System14getDriverInfoWEiPsiP9FMOD_GUID(void *instance, int id, short *name, int namelen, FMOD_GUID *guid) { return cpp_ZN4FMOD6System14getDriverInfoWEiPsiP9FMOD_GUID(instance, id, name, namelen, guid); }
FMOD_RESULT F_API _ZN4FMOD6System13getDriverCapsEiPjPiP16FMOD_SPEAKERMODE(void *instance, int id, FMOD_CAPS *caps, int *controlpaneloutputrate, FMOD_SPEAKERMODE *controlpanelspeakermode) { return cpp_ZN4FMOD6System13getDriverCapsEiPjPiP16FMOD_SPEAKERMODE(instance, id, caps, controlpaneloutputrate, controlpanelspeakermode); }
FMOD_RESULT F_API _ZN4FMOD6System9setDriverEi(void *instance, int driver) { return cpp_ZN4FMOD6System9setDriverEi(instance, driver); }
FMOD_RESULT F_API _ZN4FMOD6System9getDriverEPi(void *instance, int *driver) { return cpp_ZN4FMOD6System9getDriverEPi(instance, driver); }
FMOD_RESULT F_API _ZN4FMOD6System19setHardwareChannelsEi(void *instance, int numhardwarechannels) { return cpp_ZN4FMOD6System19setHardwareChannelsEi(instance, numhardwarechannels); }
FMOD_RESULT F_API _ZN4FMOD6System19setSoftwareChannelsEi(void *instance, int numsoftwarechannels) { return cpp_ZN4FMOD6System19setSoftwareChannelsEi(instance, numsoftwarechannels); }
FMOD_RESULT F_API _ZN4FMOD6System19getSoftwareChannelsEPi(void *instance, int *numsoftwarechannels) { return cpp_ZN4FMOD6System19getSoftwareChannelsEPi(instance, numsoftwarechannels); }
FMOD_RESULT F_API _ZN4FMOD6System17setSoftwareFormatEi17FMOD_SOUND_FORMATii18FMOD_DSP_RESAMPLER(void *instance, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod) { return cpp_ZN4FMOD6System17setSoftwareFormatEi17FMOD_SOUND_FORMATii18FMOD_DSP_RESAMPLER(instance, samplerate, format, numoutputchannels, maxinputchannels, resamplemethod); }
FMOD_RESULT F_API _ZN4FMOD6System17getSoftwareFormatEPiP17FMOD_SOUND_FORMATS1_S1_P18FMOD_DSP_RESAMPLERS1_(void *instance, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits) { return cpp_ZN4FMOD6System17getSoftwareFormatEPiP17FMOD_SOUND_FORMATS1_S1_P18FMOD_DSP_RESAMPLERS1_(instance, samplerate, format, numoutputchannels, maxinputchannels, resamplemethod, bits); }
FMOD_RESULT F_API _ZN4FMOD6System16setDSPBufferSizeEji(void *instance, unsigned int bufferlength, int numbuffers) { return cpp_ZN4FMOD6System16setDSPBufferSizeEji(instance, bufferlength, numbuffers); }
FMOD_RESULT F_API _ZN4FMOD6System16getDSPBufferSizeEPjPi(void *instance, unsigned int *bufferlength, int *numbuffers) { return cpp_ZN4FMOD6System16getDSPBufferSizeEPjPi(instance, bufferlength, numbuffers); }
FMOD_RESULT F_API _ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESA_i(void *instance, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, FMOD_FILE_ASYNCREADCALLBACK userasyncread, FMOD_FILE_ASYNCCANCELCALLBACK userasynccancel, int blockalign) { return cpp_ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESA_i(instance, useropen, userclose, userread, userseek, userasyncread, userasynccancel, blockalign); }
FMOD_RESULT F_API _ZN4FMOD6System16attachFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_E(void *instance, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek) { return cpp_ZN4FMOD6System16attachFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_E(instance, useropen, userclose, userread, userseek); }
FMOD_RESULT F_API _ZN4FMOD6System19setAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS(void *instance, FMOD_ADVANCEDSETTINGS *settings) { return cpp_ZN4FMOD6System19setAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS(instance, settings); }
FMOD_RESULT F_API _ZN4FMOD6System19getAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS(void *instance, FMOD_ADVANCEDSETTINGS *settings) { return cpp_ZN4FMOD6System19getAdvancedSettingsEP21FMOD_ADVANCEDSETTINGS(instance, settings); }
FMOD_RESULT F_API _ZN4FMOD6System14setSpeakerModeE16FMOD_SPEAKERMODE(void *instance, FMOD_SPEAKERMODE speakermode) { return cpp_ZN4FMOD6System14setSpeakerModeE16FMOD_SPEAKERMODE(instance, speakermode); }
FMOD_RESULT F_API _ZN4FMOD6System14getSpeakerModeEP16FMOD_SPEAKERMODE(void *instance, FMOD_SPEAKERMODE *speakermode) { return cpp_ZN4FMOD6System14getSpeakerModeEP16FMOD_SPEAKERMODE(instance, speakermode); }
FMOD_RESULT F_API _ZN4FMOD6System11setCallbackEPF11FMOD_RESULTP11FMOD_SYSTEM24FMOD_SYSTEM_CALLBACKTYPEPvS5_E(void *instance, FMOD_SYSTEM_CALLBACK callback) { return cpp_ZN4FMOD6System11setCallbackEPF11FMOD_RESULTP11FMOD_SYSTEM24FMOD_SYSTEM_CALLBACKTYPEPvS5_E(instance, callback); }
FMOD_RESULT F_API _ZN4FMOD6System13setPluginPathEPKc(void *instance, const char *path) { return cpp_ZN4FMOD6System13setPluginPathEPKc(instance, path); }
FMOD_RESULT F_API _ZN4FMOD6System10loadPluginEPKcPjj(void *instance, const char *filename, unsigned int *handle, unsigned int priority) { return cpp_ZN4FMOD6System10loadPluginEPKcPjj(instance, filename, handle, priority); }
FMOD_RESULT F_API _ZN4FMOD6System12unloadPluginEj(void *instance, unsigned int handle) { return cpp_ZN4FMOD6System12unloadPluginEj(instance, handle); }
FMOD_RESULT F_API _ZN4FMOD6System13getNumPluginsE15FMOD_PLUGINTYPEPi(void *instance, FMOD_PLUGINTYPE plugintype, int *numplugins) { return cpp_ZN4FMOD6System13getNumPluginsE15FMOD_PLUGINTYPEPi(instance, plugintype, numplugins); }
FMOD_RESULT F_API _ZN4FMOD6System15getPluginHandleE15FMOD_PLUGINTYPEiPj(void *instance, FMOD_PLUGINTYPE plugintype, int index, unsigned int *handle) { return cpp_ZN4FMOD6System15getPluginHandleE15FMOD_PLUGINTYPEiPj(instance, plugintype, index, handle); }
FMOD_RESULT F_API _ZN4FMOD6System13getPluginInfoEjP15FMOD_PLUGINTYPEPciPj(void *instance, unsigned int handle, FMOD_PLUGINTYPE *plugintype, char *name, int namelen, unsigned int *version) { return cpp_ZN4FMOD6System13getPluginInfoEjP15FMOD_PLUGINTYPEPciPj(instance, handle, plugintype, name, namelen, version); }
FMOD_RESULT F_API _ZN4FMOD6System17setOutputByPluginEj(void *instance, unsigned int handle) { return cpp_ZN4FMOD6System17setOutputByPluginEj(instance, handle); }
FMOD_RESULT F_API _ZN4FMOD6System17getOutputByPluginEPj(void *instance, unsigned int *handle) { return cpp_ZN4FMOD6System17getOutputByPluginEPj(instance, handle); }
FMOD_RESULT F_API _ZN4FMOD6System17createDSPByPluginEjPPNS_3DSPE(void *instance, unsigned int handle, void **dsp) { return cpp_ZN4FMOD6System17createDSPByPluginEjPPNS_3DSPE(instance, handle, dsp); }
FMOD_RESULT F_API _ZN4FMOD6System13registerCodecEP22FMOD_CODEC_DESCRIPTIONPjj(void *instance, FMOD_CODEC_DESCRIPTION *description, unsigned int *handle, unsigned int priority) { return cpp_ZN4FMOD6System13registerCodecEP22FMOD_CODEC_DESCRIPTIONPjj(instance, description, handle, priority); }
FMOD_RESULT F_API _ZN4FMOD6System11registerDSPEP20FMOD_DSP_DESCRIPTIONPj(void *instance, FMOD_DSP_DESCRIPTION *description, unsigned int *handle) { return cpp_ZN4FMOD6System11registerDSPEP20FMOD_DSP_DESCRIPTIONPj(instance, description, handle); }
FMOD_RESULT F_API _ZN4FMOD6System4initEijPv(void *instance, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata) { return cpp_ZN4FMOD6System4initEijPv(instance, maxchannels, flags, extradriverdata); }
FMOD_RESULT F_API _ZN4FMOD6System5closeEv(void *instance) { return cpp_ZN4FMOD6System5closeEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System6updateEv(void *instance) { return cpp_ZN4FMOD6System6updateEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System13set3DSettingsEfff(void *instance, float dopplerscale, float distancefactor, float rolloffscale) { return cpp_ZN4FMOD6System13set3DSettingsEfff(instance, dopplerscale, distancefactor, rolloffscale); }
FMOD_RESULT F_API _ZN4FMOD6System13get3DSettingsEPfS1_S1_(void *instance, float *dopplerscale, float *distancefactor, float *rolloffscale) { return cpp_ZN4FMOD6System13get3DSettingsEPfS1_S1_(instance, dopplerscale, distancefactor, rolloffscale); }
FMOD_RESULT F_API _ZN4FMOD6System17set3DNumListenersEi(void *instance, int numlisteners) { return cpp_ZN4FMOD6System17set3DNumListenersEi(instance, numlisteners); }
FMOD_RESULT F_API _ZN4FMOD6System17get3DNumListenersEPi(void *instance, int *numlisteners) { return cpp_ZN4FMOD6System17get3DNumListenersEPi(instance, numlisteners); }
FMOD_RESULT F_API _ZN4FMOD6System23set3DListenerAttributesEiPK11FMOD_VECTORS3_S3_S3_(void *instance, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up) { return cpp_ZN4FMOD6System23set3DListenerAttributesEiPK11FMOD_VECTORS3_S3_S3_(instance, listener, pos, vel, forward, up); }
FMOD_RESULT F_API _ZN4FMOD6System23get3DListenerAttributesEiP11FMOD_VECTORS2_S2_S2_(void *instance, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up) { return cpp_ZN4FMOD6System23get3DListenerAttributesEiP11FMOD_VECTORS2_S2_S2_(instance, listener, pos, vel, forward, up); }
FMOD_RESULT F_API _ZN4FMOD6System20set3DRolloffCallbackEPFfP12FMOD_CHANNELfE(void *instance, FMOD_3D_ROLLOFFCALLBACK callback) { return cpp_ZN4FMOD6System20set3DRolloffCallbackEPFfP12FMOD_CHANNELfE(instance, callback); }
FMOD_RESULT F_API _ZN4FMOD6System20set3DSpeakerPositionE12FMOD_SPEAKERffb(void *instance, FMOD_SPEAKER speaker, float x, float y, bool active) { return cpp_ZN4FMOD6System20set3DSpeakerPositionE12FMOD_SPEAKERffb(instance, speaker, x, y, active); }
FMOD_RESULT F_API _ZN4FMOD6System20get3DSpeakerPositionE12FMOD_SPEAKERPfS2_Pb(void *instance, FMOD_SPEAKER speaker, float *x, float *y, bool *active) { return cpp_ZN4FMOD6System20get3DSpeakerPositionE12FMOD_SPEAKERPfS2_Pb(instance, speaker, x, y, active); }
FMOD_RESULT F_API _ZN4FMOD6System19setStreamBufferSizeEjj(void *instance, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype) { return cpp_ZN4FMOD6System19setStreamBufferSizeEjj(instance, filebuffersize, filebuffersizetype); }
FMOD_RESULT F_API _ZN4FMOD6System19getStreamBufferSizeEPjS1_(void *instance, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype) { return cpp_ZN4FMOD6System19getStreamBufferSizeEPjS1_(instance, filebuffersize, filebuffersizetype); }
FMOD_RESULT F_API _ZN4FMOD6System10getVersionEPj(void *instance, unsigned int *version) { return cpp_ZN4FMOD6System10getVersionEPj(instance, version); }
FMOD_RESULT F_API _ZN4FMOD6System15getOutputHandleEPPv(void *instance, void **handle) { return cpp_ZN4FMOD6System15getOutputHandleEPPv(instance, handle); }
FMOD_RESULT F_API _ZN4FMOD6System18getChannelsPlayingEPi(void *instance, int *channels) { return cpp_ZN4FMOD6System18getChannelsPlayingEPi(instance, channels); }
FMOD_RESULT F_API _ZN4FMOD6System19getHardwareChannelsEPi(void *instance, int *numhardwarechannels) { return cpp_ZN4FMOD6System19getHardwareChannelsEPi(instance, numhardwarechannels); }
FMOD_RESULT F_API _ZN4FMOD6System11getCPUUsageEPfS1_S1_S1_S1_(void *instance, float *dsp, float *stream, float *geometry, float *update, float *total) { return cpp_ZN4FMOD6System11getCPUUsageEPfS1_S1_S1_S1_(instance, dsp, stream, geometry, update, total); }
FMOD_RESULT F_API _ZN4FMOD6System11getSoundRAMEPiS1_S1_(void *instance, int *currentalloced, int *maxalloced, int *total) { return cpp_ZN4FMOD6System11getSoundRAMEPiS1_S1_(instance, currentalloced, maxalloced, total); }
FMOD_RESULT F_API _ZN4FMOD6System17getNumCDROMDrivesEPi(void *instance, int *numdrives) { return cpp_ZN4FMOD6System17getNumCDROMDrivesEPi(instance, numdrives); }
FMOD_RESULT F_API _ZN4FMOD6System17getCDROMDriveNameEiPciS1_iS1_i(void *instance, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen) { return cpp_ZN4FMOD6System17getCDROMDriveNameEiPciS1_iS1_i(instance, drive, drivename, drivenamelen, scsiname, scsinamelen, devicename, devicenamelen); }
FMOD_RESULT F_API _ZN4FMOD6System11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cpp_ZN4FMOD6System11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(instance, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT F_API _ZN4FMOD6System11getWaveDataEPfii(void *instance, float *wavearray, int numvalues, int channeloffset) { return cpp_ZN4FMOD6System11getWaveDataEPfii(instance, wavearray, numvalues, channeloffset); }
FMOD_RESULT F_API _ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(void *instance, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, void **sound) { return cpp_ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(instance, name_or_data, mode, exinfo, sound); }
FMOD_RESULT F_API _ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(void *instance, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, void **sound) { return cpp_ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE(instance, name_or_data, mode, exinfo, sound); }
FMOD_RESULT F_API _ZN4FMOD6System9createDSPEP20FMOD_DSP_DESCRIPTIONPPNS_3DSPE(void *instance, FMOD_DSP_DESCRIPTION *description, void **dsp) { return cpp_ZN4FMOD6System9createDSPEP20FMOD_DSP_DESCRIPTIONPPNS_3DSPE(instance, description, dsp); }
FMOD_RESULT F_API _ZN4FMOD6System15createDSPByTypeE13FMOD_DSP_TYPEPPNS_3DSPE(void *instance, FMOD_DSP_TYPE type, void **dsp) { return cpp_ZN4FMOD6System15createDSPByTypeE13FMOD_DSP_TYPEPPNS_3DSPE(instance, type, dsp); }
FMOD_RESULT F_API _ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE(void *instance, const char *name, void **channelgroup) { return cpp_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE(instance, name, channelgroup); }
FMOD_RESULT F_API _ZN4FMOD6System16createSoundGroupEPKcPPNS_10SoundGroupE(void *instance, const char *name, void **soundgroup) { return cpp_ZN4FMOD6System16createSoundGroupEPKcPPNS_10SoundGroupE(instance, name, soundgroup); }
FMOD_RESULT F_API _ZN4FMOD6System12createReverbEPPNS_6ReverbE(void *instance, void **reverb) { return cpp_ZN4FMOD6System12createReverbEPPNS_6ReverbE(instance, reverb); }
FMOD_RESULT F_API _ZN4FMOD6System9playSoundE17FMOD_CHANNELINDEXPNS_5SoundEbPPNS_7ChannelE(void *instance, FMOD_CHANNELINDEX channelid, void *sound, bool paused, void **channel) { return cpp_ZN4FMOD6System9playSoundE17FMOD_CHANNELINDEXPNS_5SoundEbPPNS_7ChannelE(instance, channelid, sound, paused, channel); }
FMOD_RESULT F_API _ZN4FMOD6System7playDSPE17FMOD_CHANNELINDEXPNS_3DSPEbPPNS_7ChannelE(void *instance, FMOD_CHANNELINDEX channelid, void *dsp, bool paused, void **channel) { return cpp_ZN4FMOD6System7playDSPE17FMOD_CHANNELINDEXPNS_3DSPEbPPNS_7ChannelE(instance, channelid, dsp, paused, channel); }
FMOD_RESULT F_API _ZN4FMOD6System10getChannelEiPPNS_7ChannelE(void *instance, int channelid, void **channel) { return cpp_ZN4FMOD6System10getChannelEiPPNS_7ChannelE(instance, channelid, channel); }
FMOD_RESULT F_API _ZN4FMOD6System21getMasterChannelGroupEPPNS_12ChannelGroupE(void *instance, void **channelgroup) { return cpp_ZN4FMOD6System21getMasterChannelGroupEPPNS_12ChannelGroupE(instance, channelgroup); }
FMOD_RESULT F_API _ZN4FMOD6System19getMasterSoundGroupEPPNS_10SoundGroupE(void *instance, void **soundgroup) { return cpp_ZN4FMOD6System19getMasterSoundGroupEPPNS_10SoundGroupE(instance, soundgroup); }
FMOD_RESULT F_API _ZN4FMOD6System19setReverbPropertiesEPK22FMOD_REVERB_PROPERTIES(void *instance, const FMOD_REVERB_PROPERTIES *prop) { return cpp_ZN4FMOD6System19setReverbPropertiesEPK22FMOD_REVERB_PROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD6System19getReverbPropertiesEP22FMOD_REVERB_PROPERTIES(void *instance, FMOD_REVERB_PROPERTIES *prop) { return cpp_ZN4FMOD6System19getReverbPropertiesEP22FMOD_REVERB_PROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD6System26setReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES(void *instance, FMOD_REVERB_PROPERTIES *prop) { return cpp_ZN4FMOD6System26setReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD6System26getReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES(void *instance, FMOD_REVERB_PROPERTIES *prop) { return cpp_ZN4FMOD6System26getReverbAmbientPropertiesEP22FMOD_REVERB_PROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD6System10getDSPHeadEPPNS_3DSPE(void *instance, void **dsp) { return cpp_ZN4FMOD6System10getDSPHeadEPPNS_3DSPE(instance, dsp); }
FMOD_RESULT F_API _ZN4FMOD6System6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(void *instance, void *dsp, void **connection) { return cpp_ZN4FMOD6System6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(instance, dsp, connection); }
FMOD_RESULT F_API _ZN4FMOD6System7lockDSPEv(void *instance) { return cpp_ZN4FMOD6System7lockDSPEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System9unlockDSPEv(void *instance) { return cpp_ZN4FMOD6System9unlockDSPEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System11getDSPClockEPjS1_(void *instance, unsigned int *hi, unsigned int *lo) { return cpp_ZN4FMOD6System11getDSPClockEPjS1_(instance, hi, lo); }
FMOD_RESULT F_API _ZN4FMOD6System19getRecordNumDriversEPi(void *instance, int *numdrivers) { return cpp_ZN4FMOD6System19getRecordNumDriversEPi(instance, numdrivers); }
FMOD_RESULT F_API _ZN4FMOD6System19getRecordDriverInfoEiPciP9FMOD_GUID(void *instance, int id, char *name, int namelen, FMOD_GUID *guid) { return cpp_ZN4FMOD6System19getRecordDriverInfoEiPciP9FMOD_GUID(instance, id, name, namelen, guid); }
FMOD_RESULT F_API _ZN4FMOD6System20getRecordDriverInfoWEiPsiP9FMOD_GUID(void *instance, int id, short *name, int namelen, FMOD_GUID *guid) { return cpp_ZN4FMOD6System20getRecordDriverInfoWEiPsiP9FMOD_GUID(instance, id, name, namelen, guid); }
FMOD_RESULT F_API _ZN4FMOD6System19getRecordDriverCapsEiPjPiS2_(void *instance, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency) { return cpp_ZN4FMOD6System19getRecordDriverCapsEiPjPiS2_(instance, id, caps, minfrequency, maxfrequency); }
FMOD_RESULT F_API _ZN4FMOD6System17getRecordPositionEiPj(void *instance, int id, unsigned int *position) { return cpp_ZN4FMOD6System17getRecordPositionEiPj(instance, id, position); }
FMOD_RESULT F_API _ZN4FMOD6System11recordStartEiPNS_5SoundEb(void *instance, int id, void *sound, bool loop) { return cpp_ZN4FMOD6System11recordStartEiPNS_5SoundEb(instance, id, sound, loop); }
FMOD_RESULT F_API _ZN4FMOD6System10recordStopEi(void *instance, int id) { return cpp_ZN4FMOD6System10recordStopEi(instance, id); }
FMOD_RESULT F_API _ZN4FMOD6System11isRecordingEiPb(void *instance, int id, bool *recording) { return cpp_ZN4FMOD6System11isRecordingEiPb(instance, id, recording); }
FMOD_RESULT F_API _ZN4FMOD6System14createGeometryEiiPPNS_8GeometryE(void *instance, int maxpolygons, int maxvertices, void **geometry) { return cpp_ZN4FMOD6System14createGeometryEiiPPNS_8GeometryE(instance, maxpolygons, maxvertices, geometry); }
FMOD_RESULT F_API _ZN4FMOD6System19setGeometrySettingsEf(void *instance, float maxworldsize) { return cpp_ZN4FMOD6System19setGeometrySettingsEf(instance, maxworldsize); }
FMOD_RESULT F_API _ZN4FMOD6System19getGeometrySettingsEPf(void *instance, float *maxworldsize) { return cpp_ZN4FMOD6System19getGeometrySettingsEPf(instance, maxworldsize); }
FMOD_RESULT F_API _ZN4FMOD6System12loadGeometryEPKviPPNS_8GeometryE(void *instance, const void *data, int datasize, void **geometry) { return cpp_ZN4FMOD6System12loadGeometryEPKviPPNS_8GeometryE(instance, data, datasize, geometry); }
FMOD_RESULT F_API _ZN4FMOD6System20getGeometryOcclusionEPK11FMOD_VECTORS3_PfS4_(void *instance, const FMOD_VECTOR *listener, const FMOD_VECTOR *source, float *direct, float *reverb) { return cpp_ZN4FMOD6System20getGeometryOcclusionEPK11FMOD_VECTORS3_PfS4_(instance, listener, source, direct, reverb); }
FMOD_RESULT F_API _ZN4FMOD6System15setNetworkProxyEPKc(void *instance, const char *proxy) { return cpp_ZN4FMOD6System15setNetworkProxyEPKc(instance, proxy); }
FMOD_RESULT F_API _ZN4FMOD6System15getNetworkProxyEPci(void *instance, char *proxy, int proxylen) { return cpp_ZN4FMOD6System15getNetworkProxyEPci(instance, proxy, proxylen); }
FMOD_RESULT F_API _ZN4FMOD6System17setNetworkTimeoutEi(void *instance, int timeout) { return cpp_ZN4FMOD6System17setNetworkTimeoutEi(instance, timeout); }
FMOD_RESULT F_API _ZN4FMOD6System17getNetworkTimeoutEPi(void *instance, int *timeout) { return cpp_ZN4FMOD6System17getNetworkTimeoutEPi(instance, timeout); }
FMOD_RESULT F_API _ZN4FMOD6System11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD6System11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD6System11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD6System11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD6System13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD6System13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD6System14registerOutputEP23FMOD_OUTPUT_DESCRIPTIONPj(void *instance, FMOD_OUTPUT_DESCRIPTION *description, unsigned int *handle) { return cpp_ZN4FMOD6System14registerOutputEP23FMOD_OUTPUT_DESCRIPTIONPj(instance, description, handle); }
FMOD_RESULT F_API _ZN4FMOD6System16getCurrentOutputEPjPPvP15FMOD_OUTPUTTYPE(void *instance, unsigned int *handle, void **a2, FMOD_OUTPUTTYPE *type) { return cpp_ZN4FMOD6System16getCurrentOutputEPjPPvP15FMOD_OUTPUTTYPE(instance, handle, a2, type); }
FMOD_RESULT F_API _ZN4FMOD6System12createOutputEjPPvP15FMOD_OUTPUTTYPE(void *instance, unsigned int handle, void **a2, FMOD_OUTPUTTYPE *type) { return cpp_ZN4FMOD6System12createOutputEjPPvP15FMOD_OUTPUTTYPE(instance, handle, a2, type); }
FMOD_RESULT F_API _ZN4FMOD6System13hotswapOutputEjPv15FMOD_OUTPUTTYPE(void *instance, unsigned int handle, void *a2, FMOD_OUTPUTTYPE type) { return cpp_ZN4FMOD6System13hotswapOutputEjPv15FMOD_OUTPUTTYPE(instance, handle, a2, type); }
FMOD_RESULT F_API _ZN4FMOD6System11startOutputEv(void *instance) { return cpp_ZN4FMOD6System11startOutputEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6System10stopOutputEv(void *instance) { return cpp_ZN4FMOD6System10stopOutputEv(instance); }
FMOD_RESULT F_API _ZN4FMOD5Sound7releaseEv(void *instance) { return cpp_ZN4FMOD5Sound7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD5Sound15getSystemObjectEPPNS_6SystemE(void *instance, void **system) { return cpp_ZN4FMOD5Sound15getSystemObjectEPPNS_6SystemE(instance, system); }
FMOD_RESULT F_API _ZN4FMOD5Sound4lockEjjPPvS2_PjS3_(void *instance, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2) { return cpp_ZN4FMOD5Sound4lockEjjPPvS2_PjS3_(instance, offset, length, ptr1, ptr2, len1, len2); }
FMOD_RESULT F_API _ZN4FMOD5Sound6unlockEPvS1_jj(void *instance, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2) { return cpp_ZN4FMOD5Sound6unlockEPvS1_jj(instance, ptr1, ptr2, len1, len2); }
FMOD_RESULT F_API _ZN4FMOD5Sound11setDefaultsEfffi(void *instance, float frequency, float volume, float pan, int priority) { return cpp_ZN4FMOD5Sound11setDefaultsEfffi(instance, frequency, volume, pan, priority); }
FMOD_RESULT F_API _ZN4FMOD5Sound11getDefaultsEPfS1_S1_Pi(void *instance, float *frequency, float *volume, float *pan, int *priority) { return cpp_ZN4FMOD5Sound11getDefaultsEPfS1_S1_Pi(instance, frequency, volume, pan, priority); }
FMOD_RESULT F_API _ZN4FMOD5Sound13setVariationsEfff(void *instance, float frequencyvar, float volumevar, float panvar) { return cpp_ZN4FMOD5Sound13setVariationsEfff(instance, frequencyvar, volumevar, panvar); }
FMOD_RESULT F_API _ZN4FMOD5Sound13getVariationsEPfS1_S1_(void *instance, float *frequencyvar, float *volumevar, float *panvar) { return cpp_ZN4FMOD5Sound13getVariationsEPfS1_S1_(instance, frequencyvar, volumevar, panvar); }
FMOD_RESULT F_API _ZN4FMOD5Sound19set3DMinMaxDistanceEff(void *instance, float min, float max) { return cpp_ZN4FMOD5Sound19set3DMinMaxDistanceEff(instance, min, max); }
FMOD_RESULT F_API _ZN4FMOD5Sound19get3DMinMaxDistanceEPfS1_(void *instance, float *min, float *max) { return cpp_ZN4FMOD5Sound19get3DMinMaxDistanceEPfS1_(instance, min, max); }
FMOD_RESULT F_API _ZN4FMOD5Sound17set3DConeSettingsEfff(void *instance, float insideconeangle, float outsideconeangle, float outsidevolume) { return cpp_ZN4FMOD5Sound17set3DConeSettingsEfff(instance, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT F_API _ZN4FMOD5Sound17get3DConeSettingsEPfS1_S1_(void *instance, float *insideconeangle, float *outsideconeangle, float *outsidevolume) { return cpp_ZN4FMOD5Sound17get3DConeSettingsEPfS1_S1_(instance, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT F_API _ZN4FMOD5Sound18set3DCustomRolloffEP11FMOD_VECTORi(void *instance, FMOD_VECTOR *points, int numpoints) { return cpp_ZN4FMOD5Sound18set3DCustomRolloffEP11FMOD_VECTORi(instance, points, numpoints); }
FMOD_RESULT F_API _ZN4FMOD5Sound18get3DCustomRolloffEPP11FMOD_VECTORPi(void *instance, FMOD_VECTOR **points, int *numpoints) { return cpp_ZN4FMOD5Sound18get3DCustomRolloffEPP11FMOD_VECTORPi(instance, points, numpoints); }
FMOD_RESULT F_API _ZN4FMOD5Sound11setSubSoundEiPS0_(void *instance, int index, void *subsound) { return cpp_ZN4FMOD5Sound11setSubSoundEiPS0_(instance, index, subsound); }
FMOD_RESULT F_API _ZN4FMOD5Sound11getSubSoundEiPPS0_(void *instance, int index, void **subsound) { return cpp_ZN4FMOD5Sound11getSubSoundEiPPS0_(instance, index, subsound); }
FMOD_RESULT F_API _ZN4FMOD5Sound17getSubSoundParentEPPS0_(void *instance, void **parentsound) { return cpp_ZN4FMOD5Sound17getSubSoundParentEPPS0_(instance, parentsound); }
FMOD_RESULT F_API _ZN4FMOD5Sound19setSubSoundSentenceEPii(void *instance, int *subsoundlist, int numsubsounds) { return cpp_ZN4FMOD5Sound19setSubSoundSentenceEPii(instance, subsoundlist, numsubsounds); }
FMOD_RESULT F_API _ZN4FMOD5Sound7getNameEPci(void *instance, char *name, int namelen) { return cpp_ZN4FMOD5Sound7getNameEPci(instance, name, namelen); }
FMOD_RESULT F_API _ZN4FMOD5Sound9getLengthEPjj(void *instance, unsigned int *length, FMOD_TIMEUNIT lengthtype) { return cpp_ZN4FMOD5Sound9getLengthEPjj(instance, length, lengthtype); }
FMOD_RESULT F_API _ZN4FMOD5Sound9getFormatEP15FMOD_SOUND_TYPEP17FMOD_SOUND_FORMATPiS5_(void *instance, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits) { return cpp_ZN4FMOD5Sound9getFormatEP15FMOD_SOUND_TYPEP17FMOD_SOUND_FORMATPiS5_(instance, type, format, channels, bits); }
FMOD_RESULT F_API _ZN4FMOD5Sound15getNumSubSoundsEPi(void *instance, int *numsubsounds) { return cpp_ZN4FMOD5Sound15getNumSubSoundsEPi(instance, numsubsounds); }
FMOD_RESULT F_API _ZN4FMOD5Sound10getNumTagsEPiS1_(void *instance, int *numtags, int *numtagsupdated) { return cpp_ZN4FMOD5Sound10getNumTagsEPiS1_(instance, numtags, numtagsupdated); }
FMOD_RESULT F_API _ZN4FMOD5Sound6getTagEPKciP8FMOD_TAG(void *instance, const char *name, int index, FMOD_TAG *tag) { return cpp_ZN4FMOD5Sound6getTagEPKciP8FMOD_TAG(instance, name, index, tag); }
FMOD_RESULT F_API _ZN4FMOD5Sound12getOpenStateEP14FMOD_OPENSTATEPjPbS4_(void *instance, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, bool *starving, bool *diskbusy) { return cpp_ZN4FMOD5Sound12getOpenStateEP14FMOD_OPENSTATEPjPbS4_(instance, openstate, percentbuffered, starving, diskbusy); }
FMOD_RESULT F_API _ZN4FMOD5Sound8readDataEPvjPj(void *instance, void *buffer, unsigned int lenbytes, unsigned int *read) { return cpp_ZN4FMOD5Sound8readDataEPvjPj(instance, buffer, lenbytes, read); }
FMOD_RESULT F_API _ZN4FMOD5Sound8seekDataEj(void *instance, unsigned int pcm) { return cpp_ZN4FMOD5Sound8seekDataEj(instance, pcm); }
FMOD_RESULT F_API _ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE(void *instance, void *soundgroup) { return cpp_ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE(instance, soundgroup); }
FMOD_RESULT F_API _ZN4FMOD5Sound13getSoundGroupEPPNS_10SoundGroupE(void *instance, void **soundgroup) { return cpp_ZN4FMOD5Sound13getSoundGroupEPPNS_10SoundGroupE(instance, soundgroup); }
FMOD_RESULT F_API _ZN4FMOD5Sound16getNumSyncPointsEPi(void *instance, int *numsyncpoints) { return cpp_ZN4FMOD5Sound16getNumSyncPointsEPi(instance, numsyncpoints); }
FMOD_RESULT F_API _ZN4FMOD5Sound12getSyncPointEiPP14FMOD_SYNCPOINT(void *instance, int index, FMOD_SYNCPOINT **point) { return cpp_ZN4FMOD5Sound12getSyncPointEiPP14FMOD_SYNCPOINT(instance, index, point); }
FMOD_RESULT F_API _ZN4FMOD5Sound16getSyncPointInfoEP14FMOD_SYNCPOINTPciPjj(void *instance, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype) { return cpp_ZN4FMOD5Sound16getSyncPointInfoEP14FMOD_SYNCPOINTPciPjj(instance, point, name, namelen, offset, offsettype); }
FMOD_RESULT F_API _ZN4FMOD5Sound12addSyncPointEjjPKcPP14FMOD_SYNCPOINT(void *instance, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point) { return cpp_ZN4FMOD5Sound12addSyncPointEjjPKcPP14FMOD_SYNCPOINT(instance, offset, offsettype, name, point); }
FMOD_RESULT F_API _ZN4FMOD5Sound15deleteSyncPointEP14FMOD_SYNCPOINT(void *instance, FMOD_SYNCPOINT *point) { return cpp_ZN4FMOD5Sound15deleteSyncPointEP14FMOD_SYNCPOINT(instance, point); }
FMOD_RESULT F_API _ZN4FMOD5Sound7setModeEj(void *instance, FMOD_MODE mode) { return cpp_ZN4FMOD5Sound7setModeEj(instance, mode); }
FMOD_RESULT F_API _ZN4FMOD5Sound7getModeEPj(void *instance, FMOD_MODE *mode) { return cpp_ZN4FMOD5Sound7getModeEPj(instance, mode); }
FMOD_RESULT F_API _ZN4FMOD5Sound12setLoopCountEi(void *instance, int loopcount) { return cpp_ZN4FMOD5Sound12setLoopCountEi(instance, loopcount); }
FMOD_RESULT F_API _ZN4FMOD5Sound12getLoopCountEPi(void *instance, int *loopcount) { return cpp_ZN4FMOD5Sound12getLoopCountEPi(instance, loopcount); }
FMOD_RESULT F_API _ZN4FMOD5Sound13setLoopPointsEjjjj(void *instance, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype) { return cpp_ZN4FMOD5Sound13setLoopPointsEjjjj(instance, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT F_API _ZN4FMOD5Sound13getLoopPointsEPjjS1_j(void *instance, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype) { return cpp_ZN4FMOD5Sound13getLoopPointsEPjjS1_j(instance, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT F_API _ZN4FMOD5Sound19getMusicNumChannelsEPi(void *instance, int *numchannels) { return cpp_ZN4FMOD5Sound19getMusicNumChannelsEPi(instance, numchannels); }
FMOD_RESULT F_API _ZN4FMOD5Sound21setMusicChannelVolumeEif(void *instance, int channel, float volume) { return cpp_ZN4FMOD5Sound21setMusicChannelVolumeEif(instance, channel, volume); }
FMOD_RESULT F_API _ZN4FMOD5Sound21getMusicChannelVolumeEiPf(void *instance, int channel, float *volume) { return cpp_ZN4FMOD5Sound21getMusicChannelVolumeEiPf(instance, channel, volume); }
FMOD_RESULT F_API _ZN4FMOD5Sound13setMusicSpeedEf(void *instance, float speed) { return cpp_ZN4FMOD5Sound13setMusicSpeedEf(instance, speed); }
FMOD_RESULT F_API _ZN4FMOD5Sound13getMusicSpeedEPf(void *instance, float *speed) { return cpp_ZN4FMOD5Sound13getMusicSpeedEPf(instance, speed); }
FMOD_RESULT F_API _ZN4FMOD5Sound11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD5Sound11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD5Sound11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD5Sound11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD5Sound13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD5Sound13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD7Channel15getSystemObjectEPPNS_6SystemE(void *instance, void **system) { return cpp_ZN4FMOD7Channel15getSystemObjectEPPNS_6SystemE(instance, system); }
FMOD_RESULT F_API _ZN4FMOD7Channel4stopEv(void *instance) { return cpp_ZN4FMOD7Channel4stopEv(instance); }
FMOD_RESULT F_API _ZN4FMOD7Channel9setPausedEb(void *instance, bool paused) { return cpp_ZN4FMOD7Channel9setPausedEb(instance, paused); }
FMOD_RESULT F_API _ZN4FMOD7Channel9getPausedEPb(void *instance, bool *paused) { return cpp_ZN4FMOD7Channel9getPausedEPb(instance, paused); }
FMOD_RESULT F_API _ZN4FMOD7Channel9setVolumeEf(void *instance, float volume) { return cpp_ZN4FMOD7Channel9setVolumeEf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD7Channel9getVolumeEPf(void *instance, float *volume) { return cpp_ZN4FMOD7Channel9getVolumeEPf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD7Channel12setFrequencyEf(void *instance, float frequency) { return cpp_ZN4FMOD7Channel12setFrequencyEf(instance, frequency); }
FMOD_RESULT F_API _ZN4FMOD7Channel12getFrequencyEPf(void *instance, float *frequency) { return cpp_ZN4FMOD7Channel12getFrequencyEPf(instance, frequency); }
FMOD_RESULT F_API _ZN4FMOD7Channel6setPanEf(void *instance, float pan) { return cpp_ZN4FMOD7Channel6setPanEf(instance, pan); }
FMOD_RESULT F_API _ZN4FMOD7Channel6getPanEPf(void *instance, float *pan) { return cpp_ZN4FMOD7Channel6getPanEPf(instance, pan); }
FMOD_RESULT F_API _ZN4FMOD7Channel8setDelayE14FMOD_DELAYTYPEjj(void *instance, FMOD_DELAYTYPE delaytype, unsigned int delayhi, unsigned int delaylo) { return cpp_ZN4FMOD7Channel8setDelayE14FMOD_DELAYTYPEjj(instance, delaytype, delayhi, delaylo); }
FMOD_RESULT F_API _ZN4FMOD7Channel8getDelayE14FMOD_DELAYTYPEPjS2_(void *instance, FMOD_DELAYTYPE delaytype, unsigned int *delayhi, unsigned int *delaylo) { return cpp_ZN4FMOD7Channel8getDelayE14FMOD_DELAYTYPEPjS2_(instance, delaytype, delayhi, delaylo); }
FMOD_RESULT F_API _ZN4FMOD7Channel13setSpeakerMixEffffffff(void *instance, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) { return cpp_ZN4FMOD7Channel13setSpeakerMixEffffffff(instance, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT F_API _ZN4FMOD7Channel13getSpeakerMixEPfS1_S1_S1_S1_S1_S1_S1_(void *instance, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright) { return cpp_ZN4FMOD7Channel13getSpeakerMixEPfS1_S1_S1_S1_S1_S1_S1_(instance, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT F_API _ZN4FMOD7Channel16setSpeakerLevelsE12FMOD_SPEAKERPfi(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cpp_ZN4FMOD7Channel16setSpeakerLevelsE12FMOD_SPEAKERPfi(instance, speaker, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD7Channel16getSpeakerLevelsE12FMOD_SPEAKERPfi(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cpp_ZN4FMOD7Channel16getSpeakerLevelsE12FMOD_SPEAKERPfi(instance, speaker, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD7Channel18setInputChannelMixEPfi(void *instance, float *levels, int numlevels) { return cpp_ZN4FMOD7Channel18setInputChannelMixEPfi(instance, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD7Channel18getInputChannelMixEPfi(void *instance, float *levels, int numlevels) { return cpp_ZN4FMOD7Channel18getInputChannelMixEPfi(instance, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD7Channel7setMuteEb(void *instance, bool mute) { return cpp_ZN4FMOD7Channel7setMuteEb(instance, mute); }
FMOD_RESULT F_API _ZN4FMOD7Channel7getMuteEPb(void *instance, bool *mute) { return cpp_ZN4FMOD7Channel7getMuteEPb(instance, mute); }
FMOD_RESULT F_API _ZN4FMOD7Channel11setPriorityEi(void *instance, int priority) { return cpp_ZN4FMOD7Channel11setPriorityEi(instance, priority); }
FMOD_RESULT F_API _ZN4FMOD7Channel11getPriorityEPi(void *instance, int *priority) { return cpp_ZN4FMOD7Channel11getPriorityEPi(instance, priority); }
FMOD_RESULT F_API _ZN4FMOD7Channel11setPositionEjj(void *instance, unsigned int position, FMOD_TIMEUNIT postype) { return cpp_ZN4FMOD7Channel11setPositionEjj(instance, position, postype); }
FMOD_RESULT F_API _ZN4FMOD7Channel11getPositionEPjj(void *instance, unsigned int *position, FMOD_TIMEUNIT postype) { return cpp_ZN4FMOD7Channel11getPositionEPjj(instance, position, postype); }
FMOD_RESULT F_API _ZN4FMOD7Channel19setReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES(void *instance, const FMOD_REVERB_CHANNELPROPERTIES *prop) { return cpp_ZN4FMOD7Channel19setReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD7Channel19getReverbPropertiesEP29FMOD_REVERB_CHANNELPROPERTIES(void *instance, FMOD_REVERB_CHANNELPROPERTIES *prop) { return cpp_ZN4FMOD7Channel19getReverbPropertiesEP29FMOD_REVERB_CHANNELPROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD7Channel14setLowPassGainEf(void *instance, float gain) { return cpp_ZN4FMOD7Channel14setLowPassGainEf(instance, gain); }
FMOD_RESULT F_API _ZN4FMOD7Channel14getLowPassGainEPf(void *instance, float *gain) { return cpp_ZN4FMOD7Channel14getLowPassGainEPf(instance, gain); }
FMOD_RESULT F_API _ZN4FMOD7Channel15setChannelGroupEPNS_12ChannelGroupE(void *instance, void *channelgroup) { return cpp_ZN4FMOD7Channel15setChannelGroupEPNS_12ChannelGroupE(instance, channelgroup); }
FMOD_RESULT F_API _ZN4FMOD7Channel15getChannelGroupEPPNS_12ChannelGroupE(void *instance, void **channelgroup) { return cpp_ZN4FMOD7Channel15getChannelGroupEPPNS_12ChannelGroupE(instance, channelgroup); }
FMOD_RESULT F_API _ZN4FMOD7Channel11setCallbackEPF11FMOD_RESULTP12FMOD_CHANNEL25FMOD_CHANNEL_CALLBACKTYPEPvS5_E(void *instance, FMOD_CHANNEL_CALLBACK callback) { return cpp_ZN4FMOD7Channel11setCallbackEPF11FMOD_RESULTP12FMOD_CHANNEL25FMOD_CHANNEL_CALLBACKTYPEPvS5_E(instance, callback); }
FMOD_RESULT F_API _ZN4FMOD7Channel15set3DAttributesEPK11FMOD_VECTORS3_(void *instance, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) { return cpp_ZN4FMOD7Channel15set3DAttributesEPK11FMOD_VECTORS3_(instance, pos, vel); }
FMOD_RESULT F_API _ZN4FMOD7Channel15get3DAttributesEP11FMOD_VECTORS2_(void *instance, FMOD_VECTOR *pos, FMOD_VECTOR *vel) { return cpp_ZN4FMOD7Channel15get3DAttributesEP11FMOD_VECTORS2_(instance, pos, vel); }
FMOD_RESULT F_API _ZN4FMOD7Channel19set3DMinMaxDistanceEff(void *instance, float mindistance, float maxdistance) { return cpp_ZN4FMOD7Channel19set3DMinMaxDistanceEff(instance, mindistance, maxdistance); }
FMOD_RESULT F_API _ZN4FMOD7Channel19get3DMinMaxDistanceEPfS1_(void *instance, float *mindistance, float *maxdistance) { return cpp_ZN4FMOD7Channel19get3DMinMaxDistanceEPfS1_(instance, mindistance, maxdistance); }
FMOD_RESULT F_API _ZN4FMOD7Channel17set3DConeSettingsEfff(void *instance, float insideconeangle, float outsideconeangle, float outsidevolume) { return cpp_ZN4FMOD7Channel17set3DConeSettingsEfff(instance, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT F_API _ZN4FMOD7Channel17get3DConeSettingsEPfS1_S1_(void *instance, float *insideconeangle, float *outsideconeangle, float *outsidevolume) { return cpp_ZN4FMOD7Channel17get3DConeSettingsEPfS1_S1_(instance, insideconeangle, outsideconeangle, outsidevolume); }
FMOD_RESULT F_API _ZN4FMOD7Channel20set3DConeOrientationEP11FMOD_VECTOR(void *instance, FMOD_VECTOR *orientation) { return cpp_ZN4FMOD7Channel20set3DConeOrientationEP11FMOD_VECTOR(instance, orientation); }
FMOD_RESULT F_API _ZN4FMOD7Channel20get3DConeOrientationEP11FMOD_VECTOR(void *instance, FMOD_VECTOR *orientation) { return cpp_ZN4FMOD7Channel20get3DConeOrientationEP11FMOD_VECTOR(instance, orientation); }
FMOD_RESULT F_API _ZN4FMOD7Channel18set3DCustomRolloffEP11FMOD_VECTORi(void *instance, FMOD_VECTOR *points, int numpoints) { return cpp_ZN4FMOD7Channel18set3DCustomRolloffEP11FMOD_VECTORi(instance, points, numpoints); }
FMOD_RESULT F_API _ZN4FMOD7Channel18get3DCustomRolloffEPP11FMOD_VECTORPi(void *instance, FMOD_VECTOR **points, int *numpoints) { return cpp_ZN4FMOD7Channel18get3DCustomRolloffEPP11FMOD_VECTORPi(instance, points, numpoints); }
FMOD_RESULT F_API _ZN4FMOD7Channel14set3DOcclusionEff(void *instance, float directocclusion, float reverbocclusion) { return cpp_ZN4FMOD7Channel14set3DOcclusionEff(instance, directocclusion, reverbocclusion); }
FMOD_RESULT F_API _ZN4FMOD7Channel14get3DOcclusionEPfS1_(void *instance, float *directocclusion, float *reverbocclusion) { return cpp_ZN4FMOD7Channel14get3DOcclusionEPfS1_(instance, directocclusion, reverbocclusion); }
FMOD_RESULT F_API _ZN4FMOD7Channel11set3DSpreadEf(void *instance, float angle) { return cpp_ZN4FMOD7Channel11set3DSpreadEf(instance, angle); }
FMOD_RESULT F_API _ZN4FMOD7Channel11get3DSpreadEPf(void *instance, float *angle) { return cpp_ZN4FMOD7Channel11get3DSpreadEPf(instance, angle); }
FMOD_RESULT F_API _ZN4FMOD7Channel13set3DPanLevelEf(void *instance, float level) { return cpp_ZN4FMOD7Channel13set3DPanLevelEf(instance, level); }
FMOD_RESULT F_API _ZN4FMOD7Channel13get3DPanLevelEPf(void *instance, float *level) { return cpp_ZN4FMOD7Channel13get3DPanLevelEPf(instance, level); }
FMOD_RESULT F_API _ZN4FMOD7Channel17set3DDopplerLevelEf(void *instance, float level) { return cpp_ZN4FMOD7Channel17set3DDopplerLevelEf(instance, level); }
FMOD_RESULT F_API _ZN4FMOD7Channel17get3DDopplerLevelEPf(void *instance, float *level) { return cpp_ZN4FMOD7Channel17get3DDopplerLevelEPf(instance, level); }
FMOD_RESULT F_API _ZN4FMOD7Channel19set3DDistanceFilterEbff(void *instance, bool custom, float customLevel, float centerFreq) { return cpp_ZN4FMOD7Channel19set3DDistanceFilterEbff(instance, custom, customLevel, centerFreq); }
FMOD_RESULT F_API _ZN4FMOD7Channel19get3DDistanceFilterEPbPfS2_(void *instance, bool *custom, float *customLevel, float *centerFreq) { return cpp_ZN4FMOD7Channel19get3DDistanceFilterEPbPfS2_(instance, custom, customLevel, centerFreq); }
FMOD_RESULT F_API _ZN4FMOD7Channel10getDSPHeadEPPNS_3DSPE(void *instance, void **dsp) { return cpp_ZN4FMOD7Channel10getDSPHeadEPPNS_3DSPE(instance, dsp); }
FMOD_RESULT F_API _ZN4FMOD7Channel6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(void *instance, void *dsp, void **connection) { return cpp_ZN4FMOD7Channel6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(instance, dsp, connection); }
FMOD_RESULT F_API _ZN4FMOD7Channel9isPlayingEPb(void *instance, bool *isplaying) { return cpp_ZN4FMOD7Channel9isPlayingEPb(instance, isplaying); }
FMOD_RESULT F_API _ZN4FMOD7Channel9isVirtualEPb(void *instance, bool *isvirtual) { return cpp_ZN4FMOD7Channel9isVirtualEPb(instance, isvirtual); }
FMOD_RESULT F_API _ZN4FMOD7Channel13getAudibilityEPf(void *instance, float *audibility) { return cpp_ZN4FMOD7Channel13getAudibilityEPf(instance, audibility); }
FMOD_RESULT F_API _ZN4FMOD7Channel15getCurrentSoundEPPNS_5SoundE(void *instance, void **sound) { return cpp_ZN4FMOD7Channel15getCurrentSoundEPPNS_5SoundE(instance, sound); }
FMOD_RESULT F_API _ZN4FMOD7Channel11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cpp_ZN4FMOD7Channel11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(instance, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT F_API _ZN4FMOD7Channel11getWaveDataEPfii(void *instance, float *wavearray, int numvalues, int channeloffset) { return cpp_ZN4FMOD7Channel11getWaveDataEPfii(instance, wavearray, numvalues, channeloffset); }
FMOD_RESULT F_API _ZN4FMOD7Channel8getIndexEPi(void *instance, int *index) { return cpp_ZN4FMOD7Channel8getIndexEPi(instance, index); }
FMOD_RESULT F_API _ZN4FMOD7Channel7setModeEj(void *instance, FMOD_MODE mode) { return cpp_ZN4FMOD7Channel7setModeEj(instance, mode); }
FMOD_RESULT F_API _ZN4FMOD7Channel7getModeEPj(void *instance, FMOD_MODE *mode) { return cpp_ZN4FMOD7Channel7getModeEPj(instance, mode); }
FMOD_RESULT F_API _ZN4FMOD7Channel12setLoopCountEi(void *instance, int loopcount) { return cpp_ZN4FMOD7Channel12setLoopCountEi(instance, loopcount); }
FMOD_RESULT F_API _ZN4FMOD7Channel12getLoopCountEPi(void *instance, int *loopcount) { return cpp_ZN4FMOD7Channel12getLoopCountEPi(instance, loopcount); }
FMOD_RESULT F_API _ZN4FMOD7Channel13setLoopPointsEjjjj(void *instance, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype) { return cpp_ZN4FMOD7Channel13setLoopPointsEjjjj(instance, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT F_API _ZN4FMOD7Channel13getLoopPointsEPjjS1_j(void *instance, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype) { return cpp_ZN4FMOD7Channel13getLoopPointsEPjjS1_j(instance, loopstart, loopstarttype, loopend, loopendtype); }
FMOD_RESULT F_API _ZN4FMOD7Channel11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD7Channel11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD7Channel11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD7Channel11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD7Channel13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD7Channel13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup7releaseEv(void *instance) { return cpp_ZN4FMOD12ChannelGroup7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup15getSystemObjectEPPNS_6SystemE(void *instance, void **system) { return cpp_ZN4FMOD12ChannelGroup15getSystemObjectEPPNS_6SystemE(instance, system); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup9setVolumeEf(void *instance, float volume) { return cpp_ZN4FMOD12ChannelGroup9setVolumeEf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup9getVolumeEPf(void *instance, float *volume) { return cpp_ZN4FMOD12ChannelGroup9getVolumeEPf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup8setPitchEf(void *instance, float pitch) { return cpp_ZN4FMOD12ChannelGroup8setPitchEf(instance, pitch); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup8getPitchEPf(void *instance, float *pitch) { return cpp_ZN4FMOD12ChannelGroup8getPitchEPf(instance, pitch); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup14set3DOcclusionEff(void *instance, float directocclusion, float reverbocclusion) { return cpp_ZN4FMOD12ChannelGroup14set3DOcclusionEff(instance, directocclusion, reverbocclusion); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup14get3DOcclusionEPfS1_(void *instance, float *directocclusion, float *reverbocclusion) { return cpp_ZN4FMOD12ChannelGroup14get3DOcclusionEPfS1_(instance, directocclusion, reverbocclusion); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup9setPausedEb(void *instance, bool paused) { return cpp_ZN4FMOD12ChannelGroup9setPausedEb(instance, paused); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup9getPausedEPb(void *instance, bool *paused) { return cpp_ZN4FMOD12ChannelGroup9getPausedEPb(instance, paused); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup7setMuteEb(void *instance, bool mute) { return cpp_ZN4FMOD12ChannelGroup7setMuteEb(instance, mute); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup7getMuteEPb(void *instance, bool *mute) { return cpp_ZN4FMOD12ChannelGroup7getMuteEPb(instance, mute); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup4stopEv(void *instance) { return cpp_ZN4FMOD12ChannelGroup4stopEv(instance); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup14overrideVolumeEf(void *instance, float volume) { return cpp_ZN4FMOD12ChannelGroup14overrideVolumeEf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup17overrideFrequencyEf(void *instance, float frequency) { return cpp_ZN4FMOD12ChannelGroup17overrideFrequencyEf(instance, frequency); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup11overridePanEf(void *instance, float pan) { return cpp_ZN4FMOD12ChannelGroup11overridePanEf(instance, pan); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup24overrideReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES(void *instance, const FMOD_REVERB_CHANNELPROPERTIES *prop) { return cpp_ZN4FMOD12ChannelGroup24overrideReverbPropertiesEPK29FMOD_REVERB_CHANNELPROPERTIES(instance, prop); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup20override3DAttributesEPK11FMOD_VECTORS3_(void *instance, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel) { return cpp_ZN4FMOD12ChannelGroup20override3DAttributesEPK11FMOD_VECTORS3_(instance, pos, vel); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup18overrideSpeakerMixEffffffff(void *instance, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright) { return cpp_ZN4FMOD12ChannelGroup18overrideSpeakerMixEffffffff(instance, frontleft, frontright, center, lfe, backleft, backright, sideleft, sideright); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup8addGroupEPS0_(void *instance, void *group) { return cpp_ZN4FMOD12ChannelGroup8addGroupEPS0_(instance, group); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup12getNumGroupsEPi(void *instance, int *numgroups) { return cpp_ZN4FMOD12ChannelGroup12getNumGroupsEPi(instance, numgroups); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup8getGroupEiPPS0_(void *instance, int index, void **group) { return cpp_ZN4FMOD12ChannelGroup8getGroupEiPPS0_(instance, index, group); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup14getParentGroupEPPS0_(void *instance, void **group) { return cpp_ZN4FMOD12ChannelGroup14getParentGroupEPPS0_(instance, group); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup10getDSPHeadEPPNS_3DSPE(void *instance, void **dsp) { return cpp_ZN4FMOD12ChannelGroup10getDSPHeadEPPNS_3DSPE(instance, dsp); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(void *instance, void *dsp, void **connection) { return cpp_ZN4FMOD12ChannelGroup6addDSPEPNS_3DSPEPPNS_13DSPConnectionE(instance, dsp, connection); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup7getNameEPci(void *instance, char *name, int namelen) { return cpp_ZN4FMOD12ChannelGroup7getNameEPci(instance, name, namelen); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup14getNumChannelsEPi(void *instance, int *numchannels) { return cpp_ZN4FMOD12ChannelGroup14getNumChannelsEPi(instance, numchannels); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup10getChannelEiPPNS_7ChannelE(void *instance, int index, void **channel) { return cpp_ZN4FMOD12ChannelGroup10getChannelEiPPNS_7ChannelE(instance, index, channel); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(void *instance, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype) { return cpp_ZN4FMOD12ChannelGroup11getSpectrumEPfii19FMOD_DSP_FFT_WINDOW(instance, spectrumarray, numvalues, channeloffset, windowtype); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup11getWaveDataEPfii(void *instance, float *wavearray, int numvalues, int channeloffset) { return cpp_ZN4FMOD12ChannelGroup11getWaveDataEPfii(instance, wavearray, numvalues, channeloffset); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD12ChannelGroup11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD12ChannelGroup11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD12ChannelGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup19setAudibilityFactorEf(void *instance, float factor) { return cpp_ZN4FMOD12ChannelGroup19setAudibilityFactorEf(instance, factor); }
FMOD_RESULT F_API _ZN4FMOD12ChannelGroup19getAudibilityFactorEPf(void *instance, float *factor) { return cpp_ZN4FMOD12ChannelGroup19getAudibilityFactorEPf(instance, factor); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup7releaseEv(void *instance) { return cpp_ZN4FMOD10SoundGroup7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup15getSystemObjectEPPNS_6SystemE(void *instance, void **system) { return cpp_ZN4FMOD10SoundGroup15getSystemObjectEPPNS_6SystemE(instance, system); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup13setMaxAudibleEi(void *instance, int maxaudible) { return cpp_ZN4FMOD10SoundGroup13setMaxAudibleEi(instance, maxaudible); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup13getMaxAudibleEPi(void *instance, int *maxaudible) { return cpp_ZN4FMOD10SoundGroup13getMaxAudibleEPi(instance, maxaudible); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup21setMaxAudibleBehaviorE24FMOD_SOUNDGROUP_BEHAVIOR(void *instance, FMOD_SOUNDGROUP_BEHAVIOR behavior) { return cpp_ZN4FMOD10SoundGroup21setMaxAudibleBehaviorE24FMOD_SOUNDGROUP_BEHAVIOR(instance, behavior); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup21getMaxAudibleBehaviorEP24FMOD_SOUNDGROUP_BEHAVIOR(void *instance, FMOD_SOUNDGROUP_BEHAVIOR *behavior) { return cpp_ZN4FMOD10SoundGroup21getMaxAudibleBehaviorEP24FMOD_SOUNDGROUP_BEHAVIOR(instance, behavior); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup16setMuteFadeSpeedEf(void *instance, float speed) { return cpp_ZN4FMOD10SoundGroup16setMuteFadeSpeedEf(instance, speed); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup16getMuteFadeSpeedEPf(void *instance, float *speed) { return cpp_ZN4FMOD10SoundGroup16getMuteFadeSpeedEPf(instance, speed); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup9setVolumeEf(void *instance, float volume) { return cpp_ZN4FMOD10SoundGroup9setVolumeEf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup9getVolumeEPf(void *instance, float *volume) { return cpp_ZN4FMOD10SoundGroup9getVolumeEPf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup4stopEv(void *instance) { return cpp_ZN4FMOD10SoundGroup4stopEv(instance); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup7getNameEPci(void *instance, char *name, int namelen) { return cpp_ZN4FMOD10SoundGroup7getNameEPci(instance, name, namelen); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup12getNumSoundsEPi(void *instance, int *numsounds) { return cpp_ZN4FMOD10SoundGroup12getNumSoundsEPi(instance, numsounds); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup8getSoundEiPPNS_5SoundE(void *instance, int index, void **sound) { return cpp_ZN4FMOD10SoundGroup8getSoundEiPPNS_5SoundE(instance, index, sound); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup13getNumPlayingEPi(void *instance, int *numplaying) { return cpp_ZN4FMOD10SoundGroup13getNumPlayingEPi(instance, numplaying); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD10SoundGroup11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD10SoundGroup11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD10SoundGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD10SoundGroup13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD3DSP7releaseEv(void *instance) { return cpp_ZN4FMOD3DSP7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD3DSP15getSystemObjectEPPNS_6SystemE(void *instance, void **system) { return cpp_ZN4FMOD3DSP15getSystemObjectEPPNS_6SystemE(instance, system); }
FMOD_RESULT F_API _ZN4FMOD3DSP8addInputEPS0_PPNS_13DSPConnectionE(void *instance, void *target, void **connection) { return cpp_ZN4FMOD3DSP8addInputEPS0_PPNS_13DSPConnectionE(instance, target, connection); }
FMOD_RESULT F_API _ZN4FMOD3DSP14disconnectFromEPS0_(void *instance, void *target) { return cpp_ZN4FMOD3DSP14disconnectFromEPS0_(instance, target); }
FMOD_RESULT F_API _ZN4FMOD3DSP13disconnectAllEbb(void *instance, bool inputs, bool outputs) { return cpp_ZN4FMOD3DSP13disconnectAllEbb(instance, inputs, outputs); }
FMOD_RESULT F_API _ZN4FMOD3DSP6removeEv(void *instance) { return cpp_ZN4FMOD3DSP6removeEv(instance); }
FMOD_RESULT F_API _ZN4FMOD3DSP12getNumInputsEPi(void *instance, int *numinputs) { return cpp_ZN4FMOD3DSP12getNumInputsEPi(instance, numinputs); }
FMOD_RESULT F_API _ZN4FMOD3DSP13getNumOutputsEPi(void *instance, int *numoutputs) { return cpp_ZN4FMOD3DSP13getNumOutputsEPi(instance, numoutputs); }
FMOD_RESULT F_API _ZN4FMOD3DSP8getInputEiPPS0_PPNS_13DSPConnectionE(void *instance, int index, void **input, void **inputconnection) { return cpp_ZN4FMOD3DSP8getInputEiPPS0_PPNS_13DSPConnectionE(instance, index, input, inputconnection); }
FMOD_RESULT F_API _ZN4FMOD3DSP9getOutputEiPPS0_PPNS_13DSPConnectionE(void *instance, int index, void **output, void **outputconnection) { return cpp_ZN4FMOD3DSP9getOutputEiPPS0_PPNS_13DSPConnectionE(instance, index, output, outputconnection); }
FMOD_RESULT F_API _ZN4FMOD3DSP9setActiveEb(void *instance, bool active) { return cpp_ZN4FMOD3DSP9setActiveEb(instance, active); }
FMOD_RESULT F_API _ZN4FMOD3DSP9getActiveEPb(void *instance, bool *active) { return cpp_ZN4FMOD3DSP9getActiveEPb(instance, active); }
FMOD_RESULT F_API _ZN4FMOD3DSP9setBypassEb(void *instance, bool bypass) { return cpp_ZN4FMOD3DSP9setBypassEb(instance, bypass); }
FMOD_RESULT F_API _ZN4FMOD3DSP9getBypassEPb(void *instance, bool *bypass) { return cpp_ZN4FMOD3DSP9getBypassEPb(instance, bypass); }
FMOD_RESULT F_API _ZN4FMOD3DSP16setSpeakerActiveE12FMOD_SPEAKERb(void *instance, FMOD_SPEAKER speaker, bool active) { return cpp_ZN4FMOD3DSP16setSpeakerActiveE12FMOD_SPEAKERb(instance, speaker, active); }
FMOD_RESULT F_API _ZN4FMOD3DSP16getSpeakerActiveE12FMOD_SPEAKERPb(void *instance, FMOD_SPEAKER speaker, bool *active) { return cpp_ZN4FMOD3DSP16getSpeakerActiveE12FMOD_SPEAKERPb(instance, speaker, active); }
FMOD_RESULT F_API _ZN4FMOD3DSP5resetEv(void *instance) { return cpp_ZN4FMOD3DSP5resetEv(instance); }
FMOD_RESULT F_API _ZN4FMOD3DSP12setParameterEif(void *instance, int index, float value) { return cpp_ZN4FMOD3DSP12setParameterEif(instance, index, value); }
FMOD_RESULT F_API _ZN4FMOD3DSP12getParameterEiPfPci(void *instance, int index, float *value, char *valuestr, int valuestrlen) { return cpp_ZN4FMOD3DSP12getParameterEiPfPci(instance, index, value, valuestr, valuestrlen); }
FMOD_RESULT F_API _ZN4FMOD3DSP16getNumParametersEPi(void *instance, int *numparams) { return cpp_ZN4FMOD3DSP16getNumParametersEPi(instance, numparams); }
FMOD_RESULT F_API _ZN4FMOD3DSP16getParameterInfoEiPcS1_S1_iPfS2_(void *instance, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max) { return cpp_ZN4FMOD3DSP16getParameterInfoEiPcS1_S1_iPfS2_(instance, index, name, label, description, descriptionlen, min, max); }
FMOD_RESULT F_API _ZN4FMOD3DSP16showConfigDialogEPvb(void *instance, void *hwnd, bool show) { return cpp_ZN4FMOD3DSP16showConfigDialogEPvb(instance, hwnd, show); }
FMOD_RESULT F_API _ZN4FMOD3DSP7getInfoEPcPjPiS3_S3_(void *instance, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight) { return cpp_ZN4FMOD3DSP7getInfoEPcPjPiS3_S3_(instance, name, version, channels, configwidth, configheight); }
FMOD_RESULT F_API _ZN4FMOD3DSP7getTypeEP13FMOD_DSP_TYPE(void *instance, FMOD_DSP_TYPE *type) { return cpp_ZN4FMOD3DSP7getTypeEP13FMOD_DSP_TYPE(instance, type); }
FMOD_RESULT F_API _ZN4FMOD3DSP11setDefaultsEfffi(void *instance, float frequency, float volume, float pan, int priority) { return cpp_ZN4FMOD3DSP11setDefaultsEfffi(instance, frequency, volume, pan, priority); }
FMOD_RESULT F_API _ZN4FMOD3DSP11getDefaultsEPfS1_S1_Pi(void *instance, float *frequency, float *volume, float *pan, int *priority) { return cpp_ZN4FMOD3DSP11getDefaultsEPfS1_S1_Pi(instance, frequency, volume, pan, priority); }
FMOD_RESULT F_API _ZN4FMOD3DSP11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD3DSP11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD3DSP11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD3DSP11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD3DSP13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD3DSP13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD3DSP11getCPUUsageEPt(void *instance, unsigned short *usage) { return cpp_ZN4FMOD3DSP11getCPUUsageEPt(instance, usage); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection8getInputEPPNS_3DSPE(void *instance, void **input) { return cpp_ZN4FMOD13DSPConnection8getInputEPPNS_3DSPE(instance, input); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection9getOutputEPPNS_3DSPE(void *instance, void **output) { return cpp_ZN4FMOD13DSPConnection9getOutputEPPNS_3DSPE(instance, output); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection6setMixEf(void *instance, float volume) { return cpp_ZN4FMOD13DSPConnection6setMixEf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection6getMixEPf(void *instance, float *volume) { return cpp_ZN4FMOD13DSPConnection6getMixEPf(instance, volume); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection9setLevelsE12FMOD_SPEAKERPfi(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cpp_ZN4FMOD13DSPConnection9setLevelsE12FMOD_SPEAKERPfi(instance, speaker, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection9getLevelsE12FMOD_SPEAKERPfi(void *instance, FMOD_SPEAKER speaker, float *levels, int numlevels) { return cpp_ZN4FMOD13DSPConnection9getLevelsE12FMOD_SPEAKERPfi(instance, speaker, levels, numlevels); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD13DSPConnection11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD13DSPConnection11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD13DSPConnection13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD13DSPConnection13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }
FMOD_RESULT F_API _ZN4FMOD6Reverb7releaseEv(void *instance) { return cpp_ZN4FMOD6Reverb7releaseEv(instance); }
FMOD_RESULT F_API _ZN4FMOD6Reverb15set3DAttributesEPK11FMOD_VECTORff(void *instance, const FMOD_VECTOR *position, float mindistance, float maxdistance) { return cpp_ZN4FMOD6Reverb15set3DAttributesEPK11FMOD_VECTORff(instance, position, mindistance, maxdistance); }
FMOD_RESULT F_API _ZN4FMOD6Reverb15get3DAttributesEP11FMOD_VECTORPfS3_(void *instance, FMOD_VECTOR *position, float *mindistance, float *maxdistance) { return cpp_ZN4FMOD6Reverb15get3DAttributesEP11FMOD_VECTORPfS3_(instance, position, mindistance, maxdistance); }
FMOD_RESULT F_API _ZN4FMOD6Reverb13setPropertiesEPK22FMOD_REVERB_PROPERTIES(void *instance, const FMOD_REVERB_PROPERTIES *properties) { return cpp_ZN4FMOD6Reverb13setPropertiesEPK22FMOD_REVERB_PROPERTIES(instance, properties); }
FMOD_RESULT F_API _ZN4FMOD6Reverb13getPropertiesEP22FMOD_REVERB_PROPERTIES(void *instance, FMOD_REVERB_PROPERTIES *properties) { return cpp_ZN4FMOD6Reverb13getPropertiesEP22FMOD_REVERB_PROPERTIES(instance, properties); }
FMOD_RESULT F_API _ZN4FMOD6Reverb9setActiveEb(void *instance, bool active) { return cpp_ZN4FMOD6Reverb9setActiveEb(instance, active); }
FMOD_RESULT F_API _ZN4FMOD6Reverb9getActiveEPb(void *instance, bool *active) { return cpp_ZN4FMOD6Reverb9getActiveEPb(instance, active); }
FMOD_RESULT F_API _ZN4FMOD6Reverb11setUserDataEPv(void *instance, void *userdata) { return cpp_ZN4FMOD6Reverb11setUserDataEPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD6Reverb11getUserDataEPPv(void *instance, void **userdata) { return cpp_ZN4FMOD6Reverb11getUserDataEPPv(instance, userdata); }
FMOD_RESULT F_API _ZN4FMOD6Reverb13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(void *instance, unsigned int memorybits, unsigned int event_memorybits, unsigned int *memoryused, FMOD_MEMORY_USAGE_DETAILS *memoryused_details) { return cpp_ZN4FMOD6Reverb13getMemoryInfoEjjPjP25FMOD_MEMORY_USAGE_DETAILS(instance, memorybits, event_memorybits, memoryused, memoryused_details); }