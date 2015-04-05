/*
 * Copyright (c) 2009 Lund University
 *
 * Written by Anton Cervin, Dan Henriksson and Martin Ohlin,
 * Department of Automatic Control LTH, Lund University, Sweden.
 *   
 * This file is part of TrueTime 2.0.
 *
 * TrueTime 2.0 is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * TrueTime 2.0 is distributed in the hope that it will be useful, but
 * without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TrueTime 2.0. If not, see <http://www.gnu.org/licenses/>
 */

// PID-control of a DC servo process.
//
// This example shows four ways to implement a periodic controller
// activity in TrueTime. The task implements a standard
// PID-controller to control a DC-servo process (2nd order system). 

#define S_FUNCTION_NAME controller_init_cpp

#include "ttkernel.cpp"

// PID data structure used in Implementations 1a, 2, and 3 below.
struct TaskData {
  double throttle, brake, old_distance1, old_distance2;
};

// Kernel data structure, for proper memory allocation and deallocation
struct KernelData {
  TaskData *d;       // not used in Implementation 2
  double *d2;        // only used in Implementation 2
  int *hdl_data;     // only used in Implementation 4
};

// calculate cruise control signal and update states
void cruise_command_calc(TaskData* data, double vel, double distance1, double distance2) {
    
    double  L = 5; //final desired spacing
    double h = 1; // time gap
    double lambda = 1;
    double gain_throttle = 0.036;
    double gain_brake = -0.54;
    double adjust_throttle = 1;
    double adjust_brake = 1;
    
    distance1 = -distance1;
    distance2 = -distance2;
    vel = 0.28 * vel;
    
    double distance1_dot = distance1 - data->old_distance1;
    double distance2_dot = distance2 - data->old_distance2;
    
    double e_dot1 = distance1_dot;
    double e_dot2 = distance2_dot;
    double delta1 = distance1 + L + h * vel;
    double leading_car_vel = vel - distance1_dot;
    double delta2 = distance2 + L + h * leading_car_vel;
    
    double candidate_accel1 = -1/h * (e_dot1 + lambda * delta1);
    double candidate_accel2 = -1/h * (e_dot2 + lambda * delta2);
    
    double candidate_throttle1;
    double candidate_brake1;
    double candidate_throttle2;
    double candidate_brake2;    
    
    if(candidate_accel1 > 0) {
        candidate_throttle1 = min(candidate_accel1 * gain_throttle, 1);
        candidate_brake1 = 0;
    } else {
        candidate_throttle1 = 0;
        candidate_brake1 = min(candidate_accel1 * gain_brake, 15);
    }
    
    if(candidate_accel2 > 0) {
        candidate_throttle2 = min(candidate_accel2 * gain_throttle, 1);
        candidate_brake2 = 0;
    }else {
        candidate_throttle2 = 0;
        candidate_brake2 = min(candidate_accel2 * gain_brake, 15);
    }
    
    if(candidate_throttle2 > 0) {
        candidate_brake1 = candidate_brake1 * adjust_brake;
    }
    
    if(candidate_brake2 > 0) {
        candidate_throttle1 = candidate_throttle1 * adjust_throttle;
    }
    
    data->throttle = candidate_throttle1;
    data->brake = candidate_brake1;
    data->old_distance1 = distance1;
    data->old_distance2 = distance2;

}


// ---- Cruise code function for Implementation 1 ----
double cruise_code(int seg, void* data) {
    
    double vel, distance1, distance2;
    TaskData* d = (TaskData*) data;
    
    switch (seg) {
        case 1:
                vel = ttAnalogIn(1);
                distance1 = ttAnalogIn(2);
                distance2 = ttAnalogIn(3);
                cruise_command_calc(d, vel, distance1, distance2);
                return 0.002;
        case 2:
                ttAnalogOut(1, d->throttle);
                ttAnalogOut(2, d->brake);
                return FINISHED;
    }
    
}


void init() {
  
  // Initialize TrueTime kernel
  ttInitKernel(prioDM);

  // Task attributes
  double starttime = 0.0;
  double period = 0.01;
  double deadline = period;

  TaskData *data = new TaskData;
  data->throttle = 0;  
  data->brake = 0; 
  data->old_distance1 = -ttAnalogIn(2);
  data->old_distance2 = -ttAnalogIn(3);


  ttCreatePeriodicTask("cruise_task", starttime, period, cruise_code, data);
    
}

void cleanup() {
  // This is called also in the case of an error
// 
//   KernelData *kd = (KernelData*)ttGetUserData();
// 
//   if (kd) {
//     delete kd->d;
//     delete kd->d2;
//     delete kd->hdl_data;
//     delete kd;
//   }
}
