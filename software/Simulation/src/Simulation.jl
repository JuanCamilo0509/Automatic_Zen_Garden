# const angleStepMc = 5.625 / 64 # Deg/steps with micro steps control
const angleStep = 5.625 # Deg/steps

const zp, zn = 17, 45
const relation = zp / zn
const R = 5 # mm
const w1 = 5 # deg/s
const w2 = 10 # deg/s
const timesAngleStep = (angleStep / w1, angleStep / w2) # The time between steps to get the require angular velocity for each motor.

Iposition = (10, 4) # Initial position (mm, deg)
Fposition = (30, 10) # Final position (mm, deg)
function times(Iposition, Fposition)
  r = Fposition[1] - Iposition[1] # Delta r
  time_r = (r) / (w1 * R)
  theta = Fposition[2] - Iposition[2] # Delta theta
  t_theta = theta / (relation * w2)
  return (time_r, t_theta)
end
result = times(Iposition, Fposition)
println("Time to go to the target position:\nRadial Motor: $(result[1])\nAngular Motor: $(result[2])\n")
println("Time by step:\nRadial Motor: $(timesAngleStep[1])\nAngular Motor: $(timesAngleStep[2])")
