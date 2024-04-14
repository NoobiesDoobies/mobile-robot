void rosNodeSetup(){
    // Set the connection to rosserial socket server
  nh.getHardware()->setConnection(server, serverPort);
  Serial.println("Server: " + String(server) + " port: " + String(serverPort));
  nh.initNode();

  // Another way to get IP
  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());

  // Start to be polite
  nh.advertise(chatter);
  nh.subscribe(wheel_vel_sub);

}

