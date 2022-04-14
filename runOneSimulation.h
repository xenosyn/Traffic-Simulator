#pragma once
#ifndef __RUNONESIM__
#define __RUNONESIM__ 1

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <sys/time.h>
#include "Queue.h"

extern float* runOneSimulation(float,float,int,int);

#endif