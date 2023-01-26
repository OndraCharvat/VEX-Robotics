# In this example the robot will turn right 
# if it detects an object closer than 400mm


from vexcode import *


class VexRobot:
    def main(self):
        while True:
            # This if statement is used to turn 
            # the robot if it reaches near the walls.
            if distance.get_distance(MM) < 400:
                drivetrain.turn(RIGHT)
                brain.print(distance.get_distance(MM))
                brain.new_line()
            else:
                drivetrain.drive(FORWARD)
            # Brief wait at the end of every loop for optimal performance
            wait(5, MSEC)
            
        stop_project()


VEX_ROBOT = VexRobot()

vr_thread(VEX_ROBOT.main())
