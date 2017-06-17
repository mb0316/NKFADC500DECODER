#include "FADC500Decoder.h"

void NKFADC500DECODER_BIN(TString datafile)
{
	FADC500Decoder decoder;
	decoder.Decoder(datafile);
}
