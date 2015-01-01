/* defines nfilter::ciir class

NOTE: filters are going to require a considerable re-write to cull Intel stuff, good luck!

requires:
	<ipp.h>
	have called init_intel()

*/

#pragma once

namespace nfilter {
	class ciir : public cfilter {
		protected:
			static const int order = 3; // 1 to 12
			static const IppsIIRFilterType type = ippChebyshev1; // ippButterworth, ippChebyshev1
			IppsIIRState_64f *state;

		public:
			ciir() {
				state = 0;
			}

			virtual ~ciir() {
				free();
			}

			virtual void filter (
				double *dest
				,const double *src
				,const int len
			) {
				ippsIIR_64f(src, dest, len, state);
			}

			virtual int getdelay() {
				return state ? order * 2 : 0;
			}

			void free() {
				ippsIIRFree_64f(state);
				state = 0;
			}

			void highpass(const double rfreq) {
				double taps[2 * (order + 1)];
				free();
				if (ippStsNoErr == ippsIIRGenHighpass_64f(rfreq, 0.5, order, taps, type)) {
					ippsIIRInitAlloc_64f(&state, taps, order, 0);
				}
			}

			void lowpass(const double rfreq) {
				double taps[2 * (order + 1)];
				free();
				if (ippStsNoErr == ippsIIRGenLowpass_64f(rfreq, 0.5, order, taps, type)) {
					ippsIIRInitAlloc_64f(&state, taps, order, 0);
				}
			}
	};
}