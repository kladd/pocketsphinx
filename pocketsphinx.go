package pocketsphinx

/*
#cgo pkg-config: pocketsphinx sphinxbase
const char *ps_transcribe_file(const char *);
*/
import "C"

/*
#include "pocketsphinx.c"
*/

// TranscribeFile transcribes an audio file using pocketsphinx
func TranscribeFile(path string) string {
	return C.GoString(C.ps_transcribe_file(C.CString(path)))
}
