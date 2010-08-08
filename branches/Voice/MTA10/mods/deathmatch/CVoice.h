/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/deathmatch/logic/CVoice.h
*  PURPOSE:     Header for voice class
*  DEVELOPERS:  Philip Farquharson <philip@philipfarquharson.co.uk>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __CVOICE_H
#define __CVOICE_H


#define VOICE_BUFFER_LENGTH             200000
#define VOICE_FREQUENCY                 44100
#define VOICE_SAMPLE_SIZE               2

#define FRAME_OUTGOING_BUFFER_COUNT 100
#define FRAME_INCOMING_BUFFER_COUNT 100

// Uncomment this to hear yourself speak locally (Voice is still encoded & decoded to simulate network transmission)
//#define VOICE_DEBUG_LOCAL_PLAYBACK

#include <speex/speex.h>
#include <portaudio/portaudio.h>

class CVoice
{
public:
                                        CVoice                      ( void );
                                        ~CVoice                     ( void );

                                        enum eVoiceState
                                        {
                                            VOICESTATE_AWAITING_INPUT = 0,
                                            VOICESTATE_RECORDING,
                                            VOICESTATE_RECORDING_LAST_PACKET,
                                        };

                                        enum eSampleRate
                                        {
                                            SAMPLERATE_NARROWBAND = 8000,
                                            SAMPLERATE_WIDEBAND = 16000,
                                            SAMPLERATE_ULTRAWIDEBAND = 32000
                                        };

                                        enum eServerSampleRate
                                        {
                                            SERVERSAMPLERATE_NARROWBAND = 0,
                                            SERVERSAMPLERATE_WIDEBAND,
                                            SERVERSAMPLERATE_ULTRAWIDEBAND
                                        };

    void                                Init                        ( bool bEnabled, unsigned int uiServerSampleRate );
    void                                DeInit                      ( void );

    void                                SendFrame                   ( const void* inputBuffer );
    void                        ReceiveFrame                ( void* outputBuffer );  

    bool                                IsEnabled                   ( void )                        { return m_bEnabled; }

    void                                DecodeAndBuffer             (char* pBuffer, unsigned int bytesWritten);

    void                                DoPulse                     ( void );

    void                                UpdatePTTState              ( unsigned int uiState );

private:  
    bool                                m_bEnabled;
    eVoiceState                         m_VoiceState;
    eSampleRate                         m_SampleRate;

    PortAudioStream*                    m_pAudioStream;

    void*                               m_pSpeexEncoderState;
    void*                               m_pSpeexDecoderState;

    char*                               m_pOutgoingBuffer;
    int                                 m_iSpeexOutgoingFrameSampleCount;
    unsigned int                        m_uiOutgoingReadIndex;
    unsigned int                        m_uiOutgoingWriteIndex;
    bool                                m_bIsSendingVoiceData;
    bool                                m_bBufferOutput;
    bool                                m_bCopiedOutputBufferToBufferedOutput;

    char*                               m_pIncomingBuffer;
    int                                 m_iSpeexIncomingFrameSampleCount;
    unsigned int                        m_uiIncomingReadIndex;
    unsigned int                        m_uiIncomingWriteIndex;

    unsigned long                       m_ulTimeOfLastSend;

    unsigned int                        m_uiBufferSizeBytes;
    float*                              m_pBufferedOutput;
    unsigned int                        m_uiBufferedOutputCount;
    bool                                m_bZeroBufferedOutput;
    bool                                m_bCopiedOutgoingBufferToBufferedOutput;

    const SpeexMode*                    getSpeexModeFromSampleRate      ( void );
    eSampleRate                         convertServerSampleRate         ( unsigned int uiServerSampleRate );
};
#endif
