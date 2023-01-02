typedef struct rep_record {
	uint16_t key;
	uint16_t last;
} rep_record;

uint16_t rep_interval = 120;
rep_record rep_buffer[16];

void rep_tick(void)
{
	for(int i = 0; i < 16; ++i) if(rep_buffer[i].key) {
		if(timer_elapsed(rep_buffer[i].last) > rep_interval) {
			tap_code(rep_buffer[i].key);
			rep_buffer[i].last = timer_read();
		}
	}
}

void rep_change(uint16_t key, uint8_t trigger)
{
	if(trigger) {
		tap_code(key);
		for(int i = 0; i < 16; ++i) if(!rep_buffer[i].key) {
			rep_buffer[i].key = key;
			rep_buffer[i].last = timer_read();
			break;
		}
	} else {
		for(int i = 0; i < 16; ++i) if(rep_buffer[i].key == key) {
			rep_buffer[i].key = 0;
		}
	}
}
