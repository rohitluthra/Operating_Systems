//
// Created by Rohit Luthra on 12/24/20.
//

#ifndef OPERATING_SYSTEMS_COMMON_H
#define OPERATING_SYSTEMS_COMMON_H

#ifndef __common_h__
#define __common_h__

#include <sys/time.h>
#include <sys/stat.h>
#include <assert.h>

double GetTime() {
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) t.tv_sec + (double) t.tv_usec/1e6;
}

void Spin(int howlong) {
    double t = GetTime();
    while ((GetTime() - t) < (double) howlong)
        ; // do nothing in loop
}

#endif // __common_h__

#endif //OPERATING_SYSTEMS_COMMON_H
