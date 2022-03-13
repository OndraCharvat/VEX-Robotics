###############################################################################
# Hãy hoàn thiện hàm interact_with_controller_button                          #
# ở khu vực ĐỊNH NGHĨA CÁC HÀM                                                #
# để hoàn thiện chương trình Python cho phiên bản nâng cao                    #
# của trò chơi Thi Phản Xạ Nhanh                                              #
###############################################################################


"""
TRÒ CHƠI THI PHẢN XẠ NHANH:
PHIÊN BẢN NÂNG CAO VỚI CONTROLLER
=================================
Trò chơi này yêu cầu mô hình Slick có gắn thêm Motors & Sensors
và Controller được kết nối với Brain qua dây cắm hoặc sóng radio
"""


# NHẬP CÁC ĐỐI TƯỢNG TỪ THƯ VIỆN
# ==============================

from vex import (
    Brain, Motor, Bumper, Colorsensor, Controller, Gyro, Sonar, Touchled,
    Ports, FadeType, DEGREES, MM
)
from random import randint
from timer import Timer


# CÁC HẰNG SỐ
# ===========

# thời gian chơi mỗi vòng (tính bằng giây)
PLAY_TIME_IN_SECONDS = 120


# KHỞI TẠO CÁC BỘ PHẬN ROBOT
# ==========================

# khởi tạo brain
brain = Brain()

# khởi tạo các motor
motor_1 = Motor(Ports.PORT1, True)   # reverse=True: đảo ngược chiều xoay
motor_6 = Motor(Ports.PORT6)
motor_7 = Motor(Ports.PORT7, True)   # reverse=True: đảo ngược chiều xoay
motor_12 = Motor(Ports.PORT12)

# khởi tạo các bumper switch
bumper_9 = Bumper(Ports.PORT9)
bumper_10 = Bumper(Ports.PORT10)

# khởi tạo sensor cảm nhận màu sắc
color_sensor = Colorsensor(Ports.PORT2)

# sensor cảm nhận phương hướng
gyro = Gyro(Ports.PORT3)

# khởi tạo sensor cảm nhận khoảng cách
distance_sensor = Sonar(Ports.PORT4)

# khởi tạo các đèn LED cảm nhận chạm
touch_led_8 = Touchled(Ports.PORT8)
touch_led_8.brightness(100)
touch_led_8.default_fade(FadeType.OFF)

touch_led_11 = Touchled(Ports.PORT11)
touch_led_11.brightness(100)
touch_led_11.default_fade(FadeType.OFF)

# khởi tạo bộ điều khiển từ xa
ctl = Controller()


# ĐỊNH NGHĨA CÁC HÀM
# ==================

# tương tác với một motor nhất định
def interact_with_motor(motor, port_number):
    brain.screen.print_line(3, 'Motor ' + str(port_number) + ': turn 60 deg!')

    # lấy vị trí quay hiện tại của motor
    current_rotation = motor.rotation(DEGREES)

    # chờ tới khi motor quay tới vị trí mới
    # lệch khỏi vị trí cũ ít nhất 60 độ
    while abs(motor.rotation(DEGREES) - current_rotation) < 60:
        pass

    brain.screen.print_line(3, 'Motor ' + str(port_number) + ' turned')


# tương tác với một bumper nhất định
def interact_with_bumper(bumper, port_number):
    brain.screen.print_line(3, 'Bumper ' + str(port_number) + ': press!')

    # chờ tới khi bumper được bấm
    while not bumper.pressing():
        pass

    brain.screen.print_line(3, 'Bumper ' + str(port_number) + ' pressed')


# tương tác với gyro ở cổng 3
def interact_with_gyro_3():
    brain.screen.print_line(3, 'Gyro 3: turn 60 deg!')

    # lấy vị trí quay hiện tại của gyro
    current_rotation = gyro.rotation(DEGREES)

    # chờ tới khi gyro quay tới vị trí mới
    # lệch khỏi vị trí cũ ít nhất 60 độ
    while abs(gyro.rotation(DEGREES) - current_rotation) < 60:
        pass

    brain.screen.print_line(3, 'Gyro 3 turned')


# tương tác với distance sensor ở cổng 4
def interact_with_distance_sensor_4():
    brain.screen.print_line(3, 'Distance Sensor 4: near!')

    # chờ tới khi có một vật lại gần distance sensor
    # trong phạm vi 10cm (100mm)
    while distance_sensor.distance(MM) > 100:
        pass

    brain.screen.print_line(3, 'Distance Sensor 4 near')


# tương tác với một touch LED nhất định
def interact_with_touch_led(touch_led, port_number):
    brain.screen.print_line(3, 'TouchLED ' + str(port_number) + ': press!')

    # nhấp nháy một màu ngẫu nhiên
    touch_led.blink_hue(randint(1, 13))

    # chờ tới khi touch LED được chạm vào
    while not touch_led.pressing():
        pass

    brain.screen.print_line(3, 'TouchLED ' + str(port_number) + ' pressed')

    # tắt đèn LED
    touch_led.off()


###############################################################################
# Hãy hoàn thiện hàm interact_with_controller_button dưới đây.                #
#                                                                             #
# Chú ý: giữ nguyên (không thay đổi bất kỳ ký tự nào) dòng định nghĩa hàm     #
#   `def interact_with_controller_button(controller_button, button_name):`    #
###############################################################################

# tương tác với một controller button nhất định
def interact_with_controller_button(controller_button, button_name):
    ###########################################################################
    # Đầu tiên, in ra ở dòng số 3 của Brain một câu                           #
    # "Ctl <giá trị biến button_name>: press!",                               #
    # ví dụ như khi biến button_name = "E Down" thì in                        #
    # "Ctl E Down: press!"                                                    #
    #                                                                         #
    # Chú ý in chuỗi ký tự thật chính xác như chỉ dẫn trên!                   #
    ###########################################################################
    brain.screen.print_line(3, 'Ctl ' + button_name + ': press!')

    ###########################################################################
    # Tiếp theo, dùng vòng lặp `while not ...: pass`                          #
    # để chờ tới khi phím được biểu thị bởi biến <controller_button> được bấm #
    ###########################################################################
    while not controller_button.pressing():
        pass

    ###########################################################################
    # Cuối cùng, in ra ở dòng số 3 của Brain một câu                          #
    # "Ctl <giá trị biến button_name> pressed",                               #
    # ví dụ như khi biến button_name = "E Down" thì in                        #
    # "Ctl E Down pressed"                                                    #
    #                                                                         #
    # Chú ý in chuỗi ký tự thật chính xác như chỉ dẫn trên!                   #
    ###########################################################################
    brain.screen.print_line(3, 'Ctl ' + button_name + ' pressed')


# CHƯƠNG TRÌNH CHÍNH
# ==================

while True:
    # điểm số bắt đầu từ 0
    score = 0

    # tạo và kích hoạt đồng hồ tính giờ
    timer = Timer()
    timer.start()

    # bắt đầu chơi
    elapsed_time = 0

    while elapsed_time <= PLAY_TIME_IN_SECONDS:
        brain.screen.print_line(1,
                                'Score: ' + str(score) + ', ' +
                                'Time: ' + str(elapsed_time))

        # chơi âm thanh ngẫu nhiên trong lúc trò chơi diễn ra
        brain.sound.play_wave(randint(0, 15))

        scenario = randint(1, 20)

        if scenario == 1:
            interact_with_motor(motor_1, 1)

        elif scenario == 2:
            continue

        elif scenario == 3:
            interact_with_gyro_3()

        elif scenario == 4:
            interact_with_distance_sensor_4()

        elif scenario == 6:
            interact_with_motor(motor_6, 6)

        elif scenario == 7:
            interact_with_motor(motor_7, 7)

        elif scenario == 8:
            interact_with_touch_led(touch_led_8, 8)

        elif scenario == 9:
            interact_with_bumper(bumper_9, 9)

        elif scenario == 10:
            interact_with_bumper(bumper_10, 10)

        elif scenario == 11:
            interact_with_touch_led(touch_led_11, 11)

        elif scenario == 12:
            interact_with_motor(motor_12, 12)

        elif scenario == 13:
            interact_with_controller_button(ctl.buttonEUp, 'E Up')

        elif scenario == 14:
            interact_with_controller_button(ctl.buttonEDown, 'E Down')

        elif scenario == 15:
            interact_with_controller_button(ctl.buttonFUp, 'F Up')

        elif scenario == 16:
            interact_with_controller_button(ctl.buttonFDown, 'F Down')

        elif scenario == 17:
            interact_with_controller_button(ctl.buttonLUp, 'L Up')

        elif scenario == 18:
            interact_with_controller_button(ctl.buttonLDown, 'L Down')

        elif scenario == 19:
            interact_with_controller_button(ctl.buttonRUp, 'R Up')

        elif scenario == 20:
            interact_with_controller_button(ctl.buttonRDown, 'R Down')

        elapsed_time = timer.elapsed_time()
        if elapsed_time <= PLAY_TIME_IN_SECONDS:
            score += 1

    brain.screen.print_line(3, 'Press CHECK to Replay...')
    while not brain.buttonCheck.pressing():
        pass
