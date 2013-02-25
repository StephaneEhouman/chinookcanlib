#include "chinookpack.h"



//static int chinookpack_unpack
//
//static int chinookpack_pack_int
//
//
//
//
//static int chinookpack_pack_float

//     +--------+--------+--------+--------+--------+
//     |  0xca  |XXXXXXXX|XXXXXXXX|XXXXXXXX|XXXXXXXX|
//     +--------+--------+--------+--------+--------+
//     => big-endian IEEE 754 single precision floating point number XXXXXXXX_XXXXXXXX_XXXXXXXX_XXXXXXXX
//
//
//static int chinookpack_pack_raw
//    +--------+--------
//    |101XXXXX|...N bytes
//    +--------+--------
//    => 000XXXXXX (=N) bytes of raw bytes.
//
//static int chinookpack_pack_raw_body


//static int chinookpack_pack_nil
//     +--------+
//     |  0xc0  |
//     +--------+
//static int chinookpack_pack_true
//     +--------+
//     |  0xc3  |
//     +--------+
//static int chinookpack_pack_false
//     +--------+
//     |  0xc2  |
//     +--------+
