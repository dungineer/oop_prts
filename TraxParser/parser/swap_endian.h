#ifndef TRAXPARSER_SWAP_ENDIAN_H
#define TRAXPARSER_SWAP_ENDIAN_H


inline float swap_endian_float(const float val)
{
    float ret_val;
    char *val_ptr = (char *) &val;
    char *ret_val_ptr = (char *) &ret_val;

    ret_val_ptr[0] = val_ptr[3];
    ret_val_ptr[1] = val_ptr[2];
    ret_val_ptr[2] = val_ptr[1];
    ret_val_ptr[3] = val_ptr[0];

    return ret_val;
}

inline void swap_endian_float_array(float *ar, int n) {
    for (int i = 0; i < n; ++i) {
        *(ar + i) = swap_endian_float(*(ar + i));
    }
}

#endif //TRAXPARSER_SWAP_ENDIAN_H
