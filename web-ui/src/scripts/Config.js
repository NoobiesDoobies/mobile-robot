// Function to get the local IP address
async function getLocalIPAddress() {
  // Create a temporary RTCPeerConnection object
  const rtcPeerConnection = new RTCPeerConnection({ iceServers: [] });

  // Create a promise to resolve when the local IP address is found
  const ipAddressPromise = new Promise(resolve => {
      // Add an empty ICE candidate to trigger the ICE candidate gathering process
      rtcPeerConnection.createDataChannel('');
      rtcPeerConnection.createOffer().then(offer => {
          // Extract the local IP address from the SDP offer
          const regex = /candidate:.+ (\S+) \d+ typ/;
          const ipAddress = offer.sdp.match(regex)[1];
          resolve(ipAddress);
      });
  });

  // Close the RTCPeerConnection
  rtcPeerConnection.close();

  // Return the promise containing the local IP address
  return ipAddressPromise;
}

const Config = {
  ROSBRIDGE_SERVER_IP: "192.168.0.64",
  ROSBRIDGE_SERVER_PORT: "9090",
  RECONNECTION_TIMER: 3000,
  IMAGE_RAW_TOPIC: "/vision/color_mask",
  IMAGE_STREAM_SERVER_PORT: "8080",
  HSV_CONFIG_TOPIC: "/vision/color_mask/hsv_config",
  HSV_CONFIG_TOPIC_MESSAGE_TYPE: "std_msgs/Int32MultiArray",
  POSE_TOPIC: "amcl_pose",
  POSE_TOPIC_MESSAGE_TYPE: "geometry_msgs/PoseWithCovarianceStamped",
  TWIST_COMMAND_TOPIC: "/cmd_vel",
  TWIST_COMMAND_TOPIC_MESSAGE_TYPE: "geometry_msgs/Twist",
};

export default Config;
