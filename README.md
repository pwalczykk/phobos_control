# phobos_control

Software to control rover, developed for ground station.

Packages description:

    # rover_keyboard_teleop  

    control of rover/model with keyboard:

        [q, w, e, r, t, y] - [manipulator joint 0-4] ++
        [a, s, d, f, g, h] - [manipulator joint 0-4] --

        [y] - [gripper] ++
        [h] - [gripper] --

        [u] - [gripper] infinite{++}
        [j] - [gripper] infinite{--}

        [i] - [tower camera yaw] ++
        [k] - [tower camera yaw] --

        [o] - [tower camera pitch] ++
        [l] - [tower camera pitch] --

    # rover_rqt_teleop

    control manipulator with GUI sliders
    requires rqt_reconfigure to work:

        $ rosrun rover_rqt_teleop rover_rqt_teleop
        $ rosrun rqt_reconfigure rqt_reconfigure
