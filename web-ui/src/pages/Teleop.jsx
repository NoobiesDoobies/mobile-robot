import React from "react";
import { useState, useEffect } from "react";
import { Joystick } from 'react-joystick-component';
import ROSLIB from 'roslib';

import Config from '../scripts/Config';

const Teleop = () => {
    const [twistCommand, setTwistCommand] = useState({ linear: [0, 0], angular: 0 });
    const [ros, setRos] = useState(new ROSLIB.Ros());
    const [timer, setTimer] = useState(null);


    useEffect(() => {
        const initRosConnection = () => {
            console.log("Connecting to ROS");
            ros.on("connection", () => {
                console.log("Connected to ROS");
                clearTimeout(timer);
            });
    
            ros.on("close", () => {
                console.log("Disconnected from ROS");
                setTimer(setTimeout(() => {
                    try {
                        console.log("connecting")
                        ros.connect(`ws://${Config.ROSBRIDGE_SERVER_IP}:${Config.ROSBRIDGE_SERVER_PORT}`)
                    } catch (e) {
                        console.error(e)
                    }
                }
                    , Config.RECONNECTION_TIMER));
            });
    
            ros.on("error", (error) => {
                console.log("Error connecting to ROS: ", error);
            });
    
            try {
                ros.connect(`ws://${Config.ROSBRIDGE_SERVER_IP}:${Config.ROSBRIDGE_SERVER_PORT}`)
            } catch (e) {
                console.error(e)
            }
        }
        initRosConnection();
    }, [])


    useEffect(() => {
        const twistCommandPub = new ROSLIB.Topic({
            ros: ros,
            name: Config.TWIST_COMMAND_TOPIC,
            messageType: Config.TWIST_COMMAND_TOPIC_MESSAGE_TYPE
        });

        const twistCommandMsg = new ROSLIB.Message({
            linear: { x: twistCommand.linear[0], y: twistCommand.linear[1], z: 0 },
            angular: { x: 0, y: 0, z: twistCommand.angular }
        });

        twistCommandPub.publish(twistCommandMsg);

        // const testPub = new ROSLIB.Topic({
        //     ros: ros,
        //     name: "/test",
        //     messageType: "std_msgs/String"
        // });

        // const testMsg = new ROSLIB.Message({
        //     data: "Hello World"
        // });

        // testPub.publish(testMsg);

    }, [twistCommand])


    const onStop = () => {
        setTwistCommand({ linear: [0, 0], angular: 0 });
    }

    const onMove = (e) => {
        console.log(e);
        setTwistCommand({ linear: [e.y, e.x], angular: 0 });
    }

    return (
        <div className="">
            <Joystick size={100} baseColor="#000000" stickColor="#FFFFFF" move={onMove} stop={onStop} />
        </div>


    );
}

export default Teleop;