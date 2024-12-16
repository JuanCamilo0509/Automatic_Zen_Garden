# TODO: Find the time to change between pins to create a constant velocity in the motor.
# const unitStep = 5.625 / 64 # Deg/steps

const zp, zn = 17, 45
const relation = zp / zn
const R = 5 # mm
const w1 = 2 # deg/s
const w2 = 1 # deg/s
Iposition = (0, 0) # Initial position (mm, deg)
Fposition = (30, 10) # Final position (mm, deg)
function times(Iposition, Fposition)
  r = Fposition[1] - Iposition[1] # Delta r
  time_r = (r) / (w2 * R)
  theta = Fposition[2] - Iposition[2] # Delta theta
  t_theta = theta / (relation * w1)
  return (time_r, t_theta)
end
println(times(Iposition, Fposition))
