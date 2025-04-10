#include <stdio.h> 
#include <stdint.h>

void init_midiNoteToFrameMap(uint64_t midiNoteToFrameMap[]) {

	for (int i = 0; i < 128; i++) midiNoteToFrameMap[i] = UINT64_MAX;

    // Wake Me Up
    midiNoteToFrameMap[1] = 0; 
    midiNoteToFrameMap[2] = 1500;
    midiNoteToFrameMap[3] = 3000; 
    midiNoteToFrameMap[4] = UINT64_MAX; 

    // TMTYH
    midiNoteToFrameMap[5] = 4505; 
    midiNoteToFrameMap[6] = 6001;
    midiNoteToFrameMap[7] = 7501; 
    midiNoteToFrameMap[7] = 7501;

    // Shine a light   
    midiNoteToFrameMap[9] = 9002; 
    midiNoteToFrameMap[10] = 10502;
    midiNoteToFrameMap[11] = UINT64_MAX; 
    midiNoteToFrameMap[12] = UINT64_MAX;

    // Queen 
    midiNoteToFrameMap[13] = 12003; 
    midiNoteToFrameMap[14] = 13503;
    midiNoteToFrameMap[15] = UINT64_MAX; 
    midiNoteToFrameMap[16] = UINT64_MAX;

    // OldMAn 
    midiNoteToFrameMap[17] = 15004; 
    midiNoteToFrameMap[18] = 16504;
    midiNoteToFrameMap[19] = 18003; 
    midiNoteToFrameMap[20] = UINT64_MAX;

    // Burning Game 
    midiNoteToFrameMap[21] = 19505; 
    midiNoteToFrameMap[22] = 21005;
    midiNoteToFrameMap[23] = 22505; 
    midiNoteToFrameMap[24] = UINT64_MAX;

    // Brother 
    midiNoteToFrameMap[25] = 24006; 
    midiNoteToFrameMap[26] = 25509;
    midiNoteToFrameMap[27] = 27007; 
    midiNoteToFrameMap[28] = 28507;

    // Bullshit 
    midiNoteToFrameMap[29] = 30007; 
    midiNoteToFrameMap[30] = 31508;
    midiNoteToFrameMap[31] = 33008; 
    midiNoteToFrameMap[32] = 34508;

    // Dear Friend 
    midiNoteToFrameMap[33] = 36009; 
    midiNoteToFrameMap[34] = 37509;
    midiNoteToFrameMap[35] = 39009; 
    midiNoteToFrameMap[36] = UINT64_MAX;

    // Government 
    midiNoteToFrameMap[37] = 40509; 
    midiNoteToFrameMap[38] = 42010;
    midiNoteToFrameMap[39] = 43510; 
    midiNoteToFrameMap[40] = 45010;

    // Loaded Gun 
    midiNoteToFrameMap[41] = 46510; 
    midiNoteToFrameMap[42] = 48011;
    midiNoteToFrameMap[43] = 49511; 
    midiNoteToFrameMap[44] = UINT64_MAX;

    // Man 
    midiNoteToFrameMap[45] = 51011; 
    midiNoteToFrameMap[46] = 52512;
    midiNoteToFrameMap[47] = UINT64_MAX; 
    midiNoteToFrameMap[48] = UINT64_MAX;

    // GraveYard 
    midiNoteToFrameMap[49] = 54012; midiNoteToFrameMap[50] = 55512;
    midiNoteToFrameMap[51] = 60013; midiNoteToFrameMap[52] = UINT64_MAX;

    // HushHush 
    midiNoteToFrameMap[53] = 60013; 
    midiNoteToFrameMap[54] = 61513;
    midiNoteToFrameMap[55] = 63013; 
    midiNoteToFrameMap[56] = 64513;

    // Rather 
    midiNoteToFrameMap[57] = 66014; midiNoteToFrameMap[58] = 67514;
    midiNoteToFrameMap[59] = 69014; midiNoteToFrameMap[60] = UINT64_MAX;

    // Im Rolling 
    midiNoteToFrameMap[61] = 70514; 
    midiNoteToFrameMap[62] = 72014;
    midiNoteToFrameMap[63] = UINT64_MAX; 
    midiNoteToFrameMap[64] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[65] = UINT64_MAX; 
    midiNoteToFrameMap[66] = UINT64_MAX;
    midiNoteToFrameMap[67] = UINT64_MAX; 
    midiNoteToFrameMap[68] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[69] = UINT64_MAX; midiNoteToFrameMap[70] = UINT64_MAX;
    midiNoteToFrameMap[71] = UINT64_MAX; midiNoteToFrameMap[72] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[73] = UINT64_MAX; 
    midiNoteToFrameMap[75] = UINT64_MAX;
    midiNoteToFrameMap[76] = UINT64_MAX; 
    midiNoteToFrameMap[77] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[78] = UINT64_MAX; 
    midiNoteToFrameMap[79] = UINT64_MAX;
    midiNoteToFrameMap[80] = UINT64_MAX; 
    midiNoteToFrameMap[81] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[82] = UINT64_MAX; 
    midiNoteToFrameMap[83] = UINT64_MAX;
    midiNoteToFrameMap[84] = UINT64_MAX; 
    midiNoteToFrameMap[85] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[86] = UINT64_MAX; 
    midiNoteToFrameMap[87] = UINT64_MAX;
    midiNoteToFrameMap[88] = UINT64_MAX; 
    midiNoteToFrameMap[89] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[90] = UINT64_MAX; 
    midiNoteToFrameMap[91] = UINT64_MAX;
    midiNoteToFrameMap[92] = UINT64_MAX; 
    midiNoteToFrameMap[93] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[94] = UINT64_MAX; 
    midiNoteToFrameMap[95] = UINT64_MAX;
    midiNoteToFrameMap[96] = UINT64_MAX; 
    midiNoteToFrameMap[97] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[98] = UINT64_MAX; 
    midiNoteToFrameMap[99] = UINT64_MAX;
    midiNoteToFrameMap[100] = UINT64_MAX; 
    midiNoteToFrameMap[101] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[102] = UINT64_MAX; 
    midiNoteToFrameMap[103] = UINT64_MAX;
    midiNoteToFrameMap[104] = UINT64_MAX; 
    midiNoteToFrameMap[105] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[106] = UINT64_MAX; 
    midiNoteToFrameMap[107] = UINT64_MAX;
    midiNoteToFrameMap[108] = UINT64_MAX; 
    midiNoteToFrameMap[109] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[110] = UINT64_MAX; 
    midiNoteToFrameMap[111] = UINT64_MAX;
    midiNoteToFrameMap[112] = UINT64_MAX; 
    midiNoteToFrameMap[113] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[114] = UINT64_MAX; 
    midiNoteToFrameMap[115] = UINT64_MAX;
    midiNoteToFrameMap[116] = UINT64_MAX; 
    midiNoteToFrameMap[117] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[118] = UINT64_MAX; 
    midiNoteToFrameMap[119] = UINT64_MAX;
    midiNoteToFrameMap[120] = UINT64_MAX; 
    midiNoteToFrameMap[121] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[122] = UINT64_MAX; 
    midiNoteToFrameMap[123] = UINT64_MAX;
    midiNoteToFrameMap[124] = UINT64_MAX; 
    midiNoteToFrameMap[125] = UINT64_MAX;

    // Titre 
    midiNoteToFrameMap[126] = UINT64_MAX; 
    midiNoteToFrameMap[127] = UINT64_MAX;
}
