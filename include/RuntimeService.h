#ifndef RUNTIME_SERVICE_H
#define RUNTIME_SERVICE_H

#include <cutils/log.h>
#include <pthread.h>
#include <stdlib.h>
#include <list>

#include "siren.h"
#include "IRuntimeService.h"

using namespace android;
using namespace std;

class RuntimeService : public BnRuntimeService{
	public:
		class VoiceMessage{
			public:
				void* buff;
				int length;
				siren_event_t event;
				int has_voice;
				int has_voiceprint;
				int has_sl;
				double sl_degree;

				~VoiceMessage(){
					free(buff);
				}
		};

		enum{
			SIREN_STATE_UNKNOW = 0,
			SIREN_STATE_AWAKE,
			SIREN_STATE_SLEEP,
		};
		int current_status = SIREN_STATE_UNKNOW;

		static char const* getServiceName(){
			return "runtime_service";
		}
		~RuntimeService();
		bool init();
		void set_siren_state(const int&);
		int get_siren_state();

		pthread_mutex_t *siren_mutex;
		pthread_cond_t *siren_cond;
		pthread_t siren_thread;

		list<VoiceMessage*> voice_queue;

	private:
};

void* siren_thread_loop(void*);

#endif // RUNTIME_SERVICE_H
