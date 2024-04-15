void setup()
{

  pinMode(LED_PIN, OUTPUT);

  wifiSetup();
  rosNodeSetup();
  motorSetup();
}

void loop()
{
  if (nh.connected()) {
    digitalWrite(LED_PIN, HIGH);
    // Serial.println("Connected");
    // Say hello
    str_msg.data = hello;
    chatter.publish( &str_msg );
  } else {
    // Serial.println("Not Connected");
    digitalWrite(LED_PIN, LOW);
  }
  nh.spinOnce();
  // Loop exproximativly at 1Hz
  delay(100);
  // runMotor(true, -0.5);
  // runMotor(false, -0.5);
  // Serial.println(String(pwmL) + "\t" + String(pwmR));
  // runMotor(true, pwmL);
  // runMotor(false, pwmR);


}

void wheelVelCmdCb(const std_msgs::Float32MultiArray& wheel_velocities_command){
  Serial.println("Menerima velocity command\t" + String(wheel_velocities_command.data[0]/10.0) + "\t" + String(wheel_velocities_command.data[1]/10.0));
  pwmL = (float)wheel_velocities_command.data[0]/10.0;
  pwmR = (float)wheel_velocities_command.data[1]/10.0;
  runMotor(true, pwmL);
  runMotor(false, pwmR);


}