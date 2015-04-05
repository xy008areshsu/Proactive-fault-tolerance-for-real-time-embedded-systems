function [exectime, data] = cruise_code_2(seg, data)
switch seg
 case 1
  vel = ttAnalogIn(1); 
  distance1 = ttAnalogIn(2); 
  distance2 = ttAnalogIn(3); 
  data = cruise_command_calc(data, vel, distance1, distance2); 
  exectime = 0.002;
 case 2
  ttAnalogOut(1, data.throttle);
  ttAnalogOut(2, data.brake);
  exectime = -1;
end
