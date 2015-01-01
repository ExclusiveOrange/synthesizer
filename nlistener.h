/* defines namespace nlistener

Room for improvement:

The current implementation of interaural time delay applies a distance
appropriate delay to each ear.
A more efficient approach is to find the minimum delay of all ears; adjust
the source time by that minimum delay; create delay lines with relative
delays.


*/

#pragma once

#include <xaudio2.h> // this is a big problem because it only works on Windows

namespace nlistener {
	const double speedofsound = 343.2; // meters per second
	const double rspeedofsound = 1.0 / speedofsound;

	struct sear {
		double x, y; // in meters
		struct {
			double angle;
			double magnitude;
		} ideal, spread, occluded;
		void set(
			double _x
			, double _y
			, double ideal_angle
			, double ideal_magnitude
			, double spread_angle
			, double spread_magnitude
			, double occluded_angle
			, double occluded_magnitude
			) {
			x = _x; y = _y;
			ideal.angle = ideal_angle; ideal.magnitude = ideal_magnitude;
			spread.angle = spread_angle; spread.magnitude = spread_magnitude;
			occluded.angle = occluded_angle; occluded.magnitude = occluded_magnitude;
		}
	};

	class clistener {
	public:
		ninstance::sinstance *instance;
		int channels;
		nfilter::cdelay *delays;
		double *mags;
		double time;
		double duration;
		bool expired; // this is set when time >= instance->duration

		clistener() {
			instance = 0;
			delays = 0;
			mags = 0;
		}
		~clistener() {
			free();
		}

		void free() {
			delete instance;
			instance = 0;
			delete[] delays;
			delays = 0;
			delete[] mags;
			mags = 0;
		}

		bool init(
			int channels
			, sear *ears
			, double time // initial time: the source always begins at 0.0
			, ninstance::sinstance *instance // this clistener assumes ownership and will free
			, double x // in meters
			, double y // in meters
			, double mindistance
			) {
			free();
			mags = new double[ channels ];
			if( mags ) {
				delays = new nfilter::cdelay[ channels ];
				if( delays ) {
					unsigned int mindelay = 0xffffffff;
					unsigned int maxdelay = 0;
					unsigned int idelays[ XAUDIO2_MAX_AUDIO_CHANNELS ];
					for( int c = 0; c < channels; ++c ) {
						sear *ear = ears + c;
						double rx = x - ear->x;
						double ry = y - ear->y;
						double angle = modpi( abs( atan2( rx, ry ) - ear->ideal.angle ) );
						if( angle <= ear->spread.angle ) {
							double s = angle / ear->spread.angle;
							mags[ c ] = ( 1.0 - s ) * ear->ideal.magnitude + s * ear->spread.magnitude;
						} else {
							angle -= ear->spread.angle;
							if( angle <= ear->occluded.angle ) {
								double s = angle / ear->occluded.angle;
								mags[ c ] = ( 1.0 - s ) * ear->spread.magnitude + s * ear->occluded.magnitude;
							} else mags[ c ] = ear->occluded.magnitude;
						}
						double distance = sqrt( rx * rx + ry * ry );
						idelays[ c ] = (int)( distance * rspeedofsound * nregister::rate );
						mindelay = idelays[ c ] < mindelay ? idelays[ c ] : mindelay;
						maxdelay = idelays[ c ] > maxdelay ? idelays[ c ] : maxdelay;
						mags[ c ] *= distance <= mindistance ? 1.0 : mindistance / distance;
					}
					for( int c = 0; c < channels; ++c ) {
						delays[ c ].set( idelays[ c ] - mindelay );
					}
					this->instance = instance;
					this->channels = channels;
					this->time = time;
					duration = instance->filterduration + (double)( maxdelay - mindelay ) * nregister::rrate;
					expired = false;
					return true;
					delete[] delays;
					delays = 0;
				}
				delete[] mags;
				mags = 0;
			}
			return false;
		}

		void listen(
			double *output // add to: all of channel 0, then all of channel 1, etc.
			) {
			instance->render( time );
			for( int c = 0; c < channels; ++c ) {
				// NOTE: the delay filter and addprod consume a significant amount of time here
				// maybe there is a faster way to do this - perhaps by combining the delay and addprod
				delays[ c ].filter( nregister::localreg[ 1 ], nregister::localreg[ 0 ], nregister::len );
				nlowlevel::addprod( output + c * nregister::len, nregister::len, nregister::localreg[ 1 ], mags[ c ] );
			}
			time += nregister::duration;
			if( time >= duration ) expired = true;
			//expired = (time += nregister::duration) >= duration ? true : false;
		}
	};
}