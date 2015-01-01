/* defines namespace naudiodevice */

#pragma once

#include <windows.h>
#include <XAudio2.h>

namespace naudiodevice {
	class cvoicecallback : public IXAudio2VoiceCallback {
		public:
			HANDLE hbufferendevent;
			HANDLE hendevent;

			cvoicecallback() :
				hbufferendevent(CreateEvent(0, FALSE, FALSE, 0))
				,hendevent(CreateEvent(0, FALSE, FALSE, 0))
			{}

			~cvoicecallback() {
				CloseHandle(hendevent);
				CloseHandle(hbufferendevent);
			}

			//Called when the voice has just finished playing a contiguous audio stream.
			void OnStreamEnd() {
				SetEvent(hendevent);
			}

			//Unused methods are stubs
			void OnVoiceProcessingPassEnd() {}
			void OnVoiceProcessingPassStart(UINT32 SamplesRequired) {}
			void OnBufferEnd(void * pBufferContext) {
				SetEvent(hbufferendevent);
			}
			void OnBufferStart(void * pBufferContext) {}
			void OnLoopEnd(void * pBufferContext) {}
			void OnVoiceError(void * pBufferContext, HRESULT Error) {}
	};

	cvoicecallback voicecallback;
	IXAudio2 *xa2 = 0;
	IXAudio2MasteringVoice *mastervoice = 0;
	XAUDIO2_VOICE_DETAILS voicedetails;
	IXAudio2SourceVoice *sourcevoice = 0;

	bool init (
		unsigned int rate
	) {
		CoInitializeEx(0, COINIT_MULTITHREADED);
		HRESULT hr;
		hr = XAudio2Create(&xa2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (!FAILED(hr)) {
			hr = xa2->CreateMasteringVoice(&mastervoice, XAUDIO2_DEFAULT_CHANNELS, rate, 0, 0, 0);
			if (!FAILED(hr)) {
				mastervoice->GetVoiceDetails(&voicedetails);
				WAVEFORMATEX wfx;
				wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
				wfx.nChannels = voicedetails.InputChannels;
				wfx.nSamplesPerSec = voicedetails.InputSampleRate;
				wfx.nAvgBytesPerSec = sizeof(float) * voicedetails.InputChannels * voicedetails.InputSampleRate;
				wfx.nBlockAlign = sizeof(float) * voicedetails.InputChannels;
				wfx.wBitsPerSample = 32;
				wfx.cbSize = 0;
				hr = xa2->CreateSourceVoice(&sourcevoice, (WAVEFORMATEX*)&wfx, XAUDIO2_VOICE_NOSRC, 1.0f, &voicecallback, 0, 0);
				if (!FAILED(hr)) {
					sourcevoice->Start(0, 0);
					return true;
				}
				mastervoice = 0;
			}
			xa2->Release();
			xa2 = 0;
		}
		CoUninitialize();
		return false;
	}

	void free() {
		xa2->Release();
		xa2 = 0;
		mastervoice = 0;
		sourcevoice = 0;
		CoUninitialize();
	}

	void submitbuffer(float *buffer, unsigned int len, bool endofstream = false) {
		XAUDIO2_BUFFER xa2buf = {0};
		xa2buf.Flags = endofstream ? XAUDIO2_END_OF_STREAM : 0;
		xa2buf.AudioBytes = sizeof(float) * voicedetails.InputChannels * len;
		xa2buf.pAudioData = (BYTE*)buffer;
		sourcevoice->SubmitSourceBuffer(&xa2buf);
	}

	void waitonbuffers (
		unsigned int numbuffers
		,DWORD milliseconds // may be INFINITE
	) {
		XAUDIO2_VOICE_STATE state;
		while (sourcevoice->GetState(&state), state.BuffersQueued >= numbuffers - 1) {
			WaitForSingleObject(voicecallback.hbufferendevent, milliseconds);
		}
	}

	void waitonend(DWORD milliseconds) {
		WaitForSingleObject(voicecallback.hendevent, milliseconds);
	}
}