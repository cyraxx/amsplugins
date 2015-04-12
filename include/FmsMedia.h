/*----------------------------------------------------------------------------+
 |       ___     _       _                                                    |
 |      /   |   | |     | |                                                   |
 |     / /| | __| | ___ | |__   ___                                           |
 |    / /_| |/ _  |/ _ \|  _ \ / _ \                                          |
 |   / ___  | (_| | (_) | |_) |  __/                                          |
 |  /_/   |_|\__,_|\___/|____/ \___|                                          |
 |                                                                            |
 |                                                                            |
 |  ADOBE CONFIDENTIAL                                                        |
 |  __________________                                                        |
 |                                                                            |
 |  Copyright (c) 2003 - 2007, Adobe Systems Incorporated.                    |
 |  All rights reserved.                                                      |
 |                                                                            |
 |  NOTICE:  All information contained herein is, and remains the property    |
 |  of Adobe Systems Incorporated and its suppliers, if any. The intellectual |
 |  and technical concepts contained herein are proprietary to Adobe Systems  |
 |  Incorporated and its suppliers and may be covered by U.S. and Foreign     |
 |  Patents, patents in process, and are protected by trade secret or         |
 |  copyright law. Dissemination of this information or reproduction of this  |
 |  material is strictly forbidden unless prior written permission is         |
 |  obtained from Adobe Systems Incorporated.                                 |
 |                                                                            |
 |          Adobe Systems Incorporated       415.832.2000                     |
 |          601 Townsend Street              415.832.2020 fax                 |
 |          San Francisco, CA 94103                                           |
 |                                                                            |
 +----------------------------------------------------------------------------*/


#if !defined( FmsMedia_H )
#define  FmsMedia_H

// Media types handled by the server

/// Video codec type
static const int kVIDEO_CODEC = 0x1;

/// Audio codec type
static const int kAUDIO_CODEC = 0x4;

////////////////////////////////////////////////////////////////////////////////
// Audio Definitions
////////////////////////////////////////////////////////////////////////////////

// TODO: Should really make a constant for the location of the 
// audio description byte (ie, 0)

/// Audio Description Byte Bit Masks

/// Mask to get the format/codec from audio
static const unsigned char sndFormatMask = 0x0F;
/// Mask to get the compression settings from the audio
static const unsigned char sndCompressMask = 0xF0;

#define sndMono			 0x0 ///< Monaural channel sound.
#define sndStereo		 0x1 ///< Stereo channel sound.

#define snd8Bit			 0x0 ///< 8 bit sound.
#define	snd16Bit		 0x2 ///< 16 bit sound.

#define snd5K			 0<<2 ///< 5 kHz audio.
#define snd11K			 1<<2 ///< 11 kHz audio.
#define snd22K			 2<<2 ///< 22 kHz audio.
#define snd44K			 3<<2 ///< 44 kHz audio.

/// Audio types handled by the server
static const unsigned char snd5K8Mono		= 0x00;		
static const unsigned char snd5K8Stereo		= 0x01;
static const unsigned char snd5K16Mono		= 0x02;	
static const unsigned char snd5K16Stereo	= 0x03;
static const unsigned char snd11K8Mono		= 0x04;		
static const unsigned char snd11K8Stereo	= 0x05;		
static const unsigned char snd11K16Mono		= 0x06;		
static const unsigned char snd11K16Stereo	= 0x07;		
static const unsigned char snd22K8Mono		= 0x08;		
static const unsigned char snd22K8Stereo	= 0x09;		
static const unsigned char snd22K16Mono		= 0x0A;				
static const unsigned char snd22K16Stereo	= 0x0B;		
static const unsigned char snd44K8Mono		= 0x0C;				
static const unsigned char snd44K8Stereo	= 0x0D;		
static const unsigned char snd44K16Mono		= 0x0E;				
static const unsigned char snd44K16Stereo	= 0x0F;

namespace fms
{
namespace codecs
{

/// Samples per second for 5Khz
static const unsigned int k5KhzSampleRate = 5000;
/// Samples per second for 8Khz
static const unsigned int k8KhzSampleRate = 8000;
/// Samples per second for 11Khz
static const unsigned int k11KhzSampleRate = 11000;
/// Samples per second for 16Khz
static const unsigned int k16KhzSampleRate = 16000;
/// Samples per second for 22Khz
static const unsigned int k22KhzSampleRate = 22000;
/// Samples per second for 44Khz
static const unsigned int k44KhzSampleRate = 44000;

} //::fms::codecs
} //::fms


/// Sound codec format values; must match values used in Flash Player.
static const unsigned char sndCompressNone		= 0x00;	///< No audio.
static const unsigned char sndCompressADPCM		= 0x10;	///< ADPCM audio.
static const unsigned char sndCompressMP3		= 0x20;	///< MP3 audio.
static const unsigned char sndCompressNoneI		= 0x30;	///< Intel audio.
static const unsigned char sndCompressNelly16	= 0x40;	///< Nelly 16Khz audio
static const unsigned char sndCompressNelly8	= 0x50;	///< Nelly 8K audio.
static const unsigned char sndCompressNelly		= 0x60;	///< Nelly audio
static const unsigned char sndCompressG711A		= 0x70;	///< G711 A-law audio.
static const unsigned char sndCompressG711U		= 0x80;	///< G711 U-law audio.
static const unsigned char sndCompressUnused	= 0x90;	///< Not used.
static const unsigned char sndCompressAAC		= 0xA0;	///< AAC audio
static const unsigned char sndCompressSpeex		= 0xB0;	///< Speex audio

/// Update this each time a codec is added
static const unsigned char sndCompressMax		= sndCompressSpeex; 

/// Number of audio transcoders needed (one per codec). 
/// Used for vector size allocation.
static const unsigned int kNumAudioTranscoderTypes = ( sndCompressMax >> 4 ) + 1;

/// Bit field for supported audio formats.
static const unsigned int SUPPORT_SND_NONE		= 0x0001; ///< No audio.
static const unsigned int SUPPORT_SND_ADPCM		= 0x0002; ///< ADPCM
static const unsigned int SUPPORT_SND_MP3		= 0x0004; ///< MP3
static const unsigned int SUPPORT_SND_INTEL		= 0x0008; ///< Intel audio.

/// 0x0200 used to be used by FlashPlayer 9 to indicate it supported
/// Nelly16, but it would actually send audio a sndCompress byte (0x90)
/// that did not correspond to its support bit. This bit seems to have once
/// been used for a codec that never made it into a released flash player,
/// so we're using it for Nelly16. That way old FMS versions that don't check
/// the support bit and FP9 players that worked before continue to work.
static const unsigned int SUPPORT_SND_NELLY16	= 0x0010; ///< Nelly 16K audio

static const unsigned int SUPPORT_SND_NELLY8	= 0x0020; ///< Nelly 8K audio.
static const unsigned int SUPPORT_SND_NELLY		= 0x0040; ///< Nelly 
static const unsigned int SUPPORT_SND_G711A		= 0x0080; ///< G711 A-law audio
static const unsigned int SUPPORT_SND_G711U		= 0x0100; ///< G711 U-law audio
static const unsigned int SUPPORT_SND_UNUSED	= 0x0200; ///< Unused
static const unsigned int SUPPORT_SND_AAC		= 0x0400; ///< AAC audio
static const unsigned int SUPPORT_SND_SPEEX		= 0x0800; ///< Speex audio

/// Update this each time a codec is added.
static const unsigned int SUPPORT_SND_ALL		= 0x0FFF; ///< All audio

// TODO: This arg should really be a U8, but for some reason
// people are calling this with U16 all over the place
inline static unsigned short getSupportSndBit(unsigned short format) { return (1 << (format >> 4)); }

// Audio codec header lengths
static const unsigned char kAACHeaderSize			= 2;
static const unsigned char kSpeexHeaderSize			= 1;
static const unsigned char kMP3HeaderSize			= 1;
static const unsigned char kNellyMoserHeaderSize	= 1;

////////////////////////////////////////////////////////////////////////////////
// Video Definitions
////////////////////////////////////////////////////////////////////////////////

// TODO: Should really make a constant for the location of the 
// video description byte (ie, 0)

/// Video Description Byte Bit Masks

/// Mask for video's codec type
#define VIDEO_CODEC_MASK 0x0F 
/// Mask for video frame type
#define FRAME_TYPE_MASK	 0xF0

/// Supported Video Codecs.
/// NOTE: must match values used in Flash Player.
/// These are also used as vector indexes for transcoders.
#define VIDEO_CODEC_UNUSED		0x00	///< Not used.
#define VIDEO_CODEC_JPEG		0x01	///< Jpeg video.
#define VIDEO_CODEC_SORENSON	0x02	///< Sorenson
#define VIDEO_CODEC_HOMEBREW	0x03	///< Screenshare
#define VIDEO_CODEC_VP6			0x04	///< VP6 video.
#define VIDEO_CODEC_VP6ALPHA	0x05	///< VP6 w/Alpha
#define VIDEO_CODEC_HOMEBREW_V2	0x06	///< Screenshare V2
#define VIDEO_CODEC_H264		0x07	///< H264 video

/// Update this each time a codec is added.
#define VIDEO_CODEC_MAX			VIDEO_CODEC_H264

/// Number of video transcoders needed (one per codec). 
/// Used for vector size allocation.
static const unsigned int kNumVideoTranscoderTypes = VIDEO_CODEC_MAX + 1;

/// Bit field for supported video formats.

/// Unused video codec
static const unsigned int SUPPORT_VID_UNUSED	= 1 << VIDEO_CODEC_UNUSED;
/// Support Jpeg video.
static const unsigned int SUPPORT_VID_JPEG		= 1 << VIDEO_CODEC_JPEG;
/// Support Sorenson video.
static const unsigned int SUPPORT_VID_SORENSON	= 1 << VIDEO_CODEC_SORENSON;
/// Support Homebrew video.
static const unsigned int SUPPORT_VID_HOMEBREW	= 1 << VIDEO_CODEC_HOMEBREW;
/// Support VP6 video.
static const unsigned int SUPPORT_VID_VP6		= 1 << VIDEO_CODEC_VP6;
/// Support VP6 Alpha video.
static const unsigned int SUPPORT_VID_VP6ALPHA	= 1 << VIDEO_CODEC_VP6ALPHA;
/// Support Homebrew V2 video.
static const unsigned int SUPPORT_VID_HOMEBREWV2= 1 << VIDEO_CODEC_HOMEBREW_V2;
/// Support H264 Video
static const unsigned int SUPPORT_VID_H264		= 1 << VIDEO_CODEC_H264;

// Update this each time a codec is added.
static const unsigned int SUPPORT_VID_ALL = 0x00FF;	/// Support all videos.

// TODO: This arg should really be a U8, but for some reason
// people are calling this with U16 all over the place
inline static unsigned short getSupportVidBit(unsigned short format) { return (1 << (format)); }

/// Supported Video Frame Types
#define FRAME_TYPE_KEY			0x10	///< Keyframe
#define FRAME_TYPE_I			0x20	///< Intermediate frame
#define FRAME_TYPE_D			0x30	///< Sorenson disposible frame
#define FRAME_TYPE_GENKEY		0x40	///< Generated keyframe for server seeking
#define FRAME_TYPE_INFO			0x50	///< Video information or command	

// Video codec header lengths
static const unsigned char kH263CodecHeaderSize			= 1; /// Sorenson
static const unsigned char kVP6CodecHeaderSize			= 2;
static const unsigned char kAVCCodecHeaderSize			= 5;

#endif	// !defined( FmsMedia_H )
