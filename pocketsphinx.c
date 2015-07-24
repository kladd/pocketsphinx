
#include "pocketsphinx.h"
#define MODELDIR "/usr/local/Cellar/cmu-pocketsphinx/HEAD/share/pocketsphinx/model"

const char*
ps_transcribe_file(const char* path)
{
	FILE *fh;
	const char *hyp, *uttid;

	int rv;
	int16 buf[512];
	int32 score;

	ps_decoder_t *ps;
	cmd_ln_t *config;

	config = cmd_ln_init(
		NULL, ps_args(), TRUE,
		"-hmm", MODELDIR "/en-us/en-us",
		"-lm", MODELDIR "/en-us/en-us.lm.bin",
		"-dict", MODELDIR "/en-us/cmudict-en-us.dict",
		NULL
	);

	ps = ps_init(config);
	fh = fopen(path, "rb");
	rv = ps_start_utt(ps);

	while (!feof(fh)) {
		size_t nsamp;
		nsamp = fread(buf, 2, 512, fh);
		rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
	}

	rv = ps_end_utt(ps);
	hyp = ps_get_hyp(ps, &score);

	fclose(fh);
	ps_free(ps);
	cmd_ln_free_r(config);

	return hyp;
}
