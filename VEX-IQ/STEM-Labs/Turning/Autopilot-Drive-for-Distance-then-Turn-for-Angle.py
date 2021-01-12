from drivetrain import Drivetrain
from vexiq import Motor


class Autopilot:
    LEFT_MOTOR_PORT = 1
    LEFT_MOTOR_REVERSE_POLARITY = False

    RIGHT_MOTOR_PORT = 6
    RIGHT_MOTOR_REVERSE_POLARITY = True

    WHEEL_TRAVEL_MM = 200
    TRACK_MM = 176

    def __init__(self):
        self.drivetrain = \
            Drivetrain(
                Motor(
                    self.LEFT_MOTOR_PORT,   # port
                    self.LEFT_MOTOR_REVERSE_POLARITY   # switch_polarity
                ),   # left_motor
                Motor(
                    self.RIGHT_MOTOR_PORT,   # port
                    self.RIGHT_MOTOR_REVERSE_POLARITY   # switch_polarity
                ),   # right_motor
                self.WHEEL_TRAVEL_MM,   # wheel_travel_mm
                self.TRACK_MM   # track_mm
            )


if __name__ == 'TBD':
    AUTOPILOT = Autopilot()

    AUTOPILOT.drivetrain.drive_until(
        100,   # power
        304.8   # distance_mm (12 inches)
    )

    AUTOPILOT.drivetrain.turn_until(
        100,   # power
        90   # angle_deg: positive to turn left, negative to turn right
    )
