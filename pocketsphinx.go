package pocketsphinx

/*
#cgo pkg-config: pocketsphinx sphinxbase
#include "pocketsphinx.c"
*/
import "C"

// TranscribeFile transcribes an audio file using pocketsphinx
func TranscribeFile(path string) string {
	return C.GoString(C.ps_transcribe_file(C.CString(path)))
}
