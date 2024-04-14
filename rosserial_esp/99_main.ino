void setup()
{


  wifiSetup();
  rosNodeSetup();
  motorSetup();
}

void loop()
{
  if (nh.connected()) {
    Serial.println("Connected");
    // Say hello
    str_msg.data = hello;
    chatter.publish( &str_msg );
  } else {
    // Serial.println("Not Connected");
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(100);
  runMotor(true, -0.5);
  runMotor(false, -0.5);

}

void wheelVelCmdCb(const std_msgs::Float32MultiArray& wheel_velocities_command){
  Serial.println("Menerima velocity command\t" + String(wheel_velocities_command.data[0]) );
  runMotor(true, (float)wheel_velocities_command.data[0]/10.0);
  runMotor(false, (float)wheel_velocities_command.data[1]/10.0);

}