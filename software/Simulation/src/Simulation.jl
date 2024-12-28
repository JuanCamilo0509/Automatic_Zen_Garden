const zp, zn = 17, 51
const relation = zp / zn
const R = 5 # mm
const w1 = deg2rad(50) # rad/s
const w2 = 15 # deg/s

Fposition = (20, 10) # Final position (mm, deg)
function time_radious_motor(r)
  time_r = (r) / (w1 * R)
  return time_r
end
function time_angle_motor(theta)
  t_theta = theta / (relation * w2)
  return t_theta
end
function times(final_position)
  return (time_radious_motor(final_position[1]), time_angle_motor(final_position[2]))
end
result = times(Fposition)
println("Seconds")
println("Time to go to the target position:
        Radial Motor: $(result[1])
        Angular Motor: $(result[2])"
)
