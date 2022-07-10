# FMOD-PSV
FMOD interface for PS Vita homebrew. FMOD version is 4.44.56

Supports hardware acceleration based on SceNgs and SceAudiodec. Supports Vita-specific formats and DSP effects.

#Installation
1. Download ```UnitySetup-Playstation-Vita-Support-for-Editor-2018.3.0a2.exe```, open it as archive and extract ```$INSTDIR$_59_``` folder
2. Unfself ```PSP2Player_Mono.self``` and patch it with .delta file using xdelta
3. Make fself out of result of step 2
4. Get ```pthread.suprx``` from ```Media/Modules```

For usage example refer to fmodInterfaceTest.
