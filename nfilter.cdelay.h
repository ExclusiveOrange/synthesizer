/* defines nfilter::cdelay class */

#pragma once

#include <memory.h>

namespace nfilter {
	class cdelay : public cfilter {
		protected:
			double *line;
			int len;
			int cursor;

		public:
			cdelay() {
				line = 0;
				len = 0;
				cursor = 0;
			}

			virtual ~cdelay() {
				free();
			}

			virtual void filter (
				double *dest
				,const double *src
				,const int len
			) {
				if (!line) return; // try to remove this check
				
				if (len >= this->len) { // block is larger than delay line
					ncircularbuffer::unwrap(dest, line, this->len, cursor);
					memcpy(dest + this->len, src, sizeof(double) * (len - this->len));
					ncircularbuffer::wrap(line, src + (len - this->len), this->len, cursor);
				} else { // block is smaller than delay line
					cursor = ncircularbuffer::unwrap_partial(dest, line, this->len, cursor, len);
					cursor = ncircularbuffer::wrap_partial(line, src, this->len, cursor, len);
				}				
			}

			virtual int getdelay() {
				return line ? len : 0;
			}

			void free() {
				delete line;
				line = 0;
			}

			void set(int len) {
				free();
				if (len < 1) len = 1;
				if ((line = (double*)calloc(len, sizeof(double)))) {
					this->len = len;
					cursor = 0;
				}
			}
	};
}