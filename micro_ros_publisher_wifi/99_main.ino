void setup(){
  Serial.begin(115200);
  while (!Serial)
  delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("serial began");

  micro_ros_setup();
  mpu_6050_setup();
}

void loop(){
  RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
  msg.data++;

  // RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  
  delay(100);

  // /* Get new sensor events with the readings */
  // sensors_event_t a, g, temp;
  // mpu.getEvent(&a, &g, &temp);

  // static float acceleration_x = 0, acceleration_y = 0;
  // if(abs(a.acceleration.x) > 0.1){
  //   acceleration_x = a.acceleration.x;
  // } else {acceleration_x = 0;}
  // if(abs(a.acceleration.y) > 0.4){
  //   acceleration_y = a.acceleration.y;
  // } else {acceleration_y = 0;}



  // /* Print out the values */
  // Serial.print("Acceleration X: ");
  // Serial.print(acceleration_x);
  // Serial.print(", Y: ");
  // Serial.print(acceleration_y);
  // Serial.print(", Z: ");
  // Serial.print(a.acceleration.z);
  // Serial.println(" m/s^2");

  // // Compensate gyro drift by integrating gyroscope data
  // static float last_time = millis();
  // float dt = (millis() - last_time) / 1000.0; // Time since last loop iteration in seconds
  // last_time = millis();

  // static float velocity_x = 0, velocity_y = 0;
  // static float position_x = 0, position_y = 0;

  // velocity_x += acceleration_x * dt;
  // velocity_y += acceleration_y * dt;

  // position_x += velocity_x * dt;
  // position_y += velocity_y * dt;

  // Serial.print("dt: ");
  // Serial.print(dt);
  // Serial.print(", position X: ");
  // Serial.print(position_x);
  // Serial.print(", Y: ");
  // Serial.print(position_y);
  // Serial.println(" m");

  // Serial.print("dt: ");
  // Serial.print(dt);
  // Serial.print(", velocity X: ");
  // Serial.print(velocity_x);
  // Serial.print(", Y: ");
  // Serial.print(velocity_y);
  // Serial.println(" m/s");
  // // Serial.print("Rotation X: ");
  // // Serial.print(g.gyro.x);
  // // Serial.print(", Y: ");
  // // Serial.print(g.gyro.y);
  // // Serial.print(", Z: ");
  // // Serial.print(g.gyro.z);
  // // Serial.println(" rad/s");

  // // Serial.print("Temperature: ");
  // // Serial.print(temp.temperature);
  // // Serial.println(" degC");

}