# This example will draw a circle using the red pen


from vexcode import *


class VexRobot:
    def main(self):
        pen.move(DOWN)
        pen.set_pen_color(RED)
        for repeat_count in range(36):
            drivetrain.drive_for(FORWARD, 30, MM)
            drivetrain.turn_for(RIGHT, 10, DEGREES)
            # Brief wait needed at the end of loops for optimal performance
            wait(5, MSEC)
        pen.move(UP)
        drivetrain.drive_for(FORWARD, 300, MM)

        stop_project()


VEX_ROBOT = VexRobot()

vr_thread(VEX_ROBOT.main())
