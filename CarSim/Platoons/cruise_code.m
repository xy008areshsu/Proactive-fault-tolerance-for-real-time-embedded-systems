function [exectime, data] = cruise_code(seg, data)
switch seg
 case 1 
  inp(1) = ttAnalogIn(1);
  inp(2) = ttAnalogIn(2);
  inp(3) = ttAnalogIn(3);
  outp = ttCallBlockSystem(3, inp, 'active_cruise_CTG');
  data.throttle = outp(1);
  data.brake = outp(2);
  exectime = outp(3);
 case 2
  ttAnalogOut(1, data.throttle);
  ttAnalogOut(2, data.brake);
  exectime = -1;
end
