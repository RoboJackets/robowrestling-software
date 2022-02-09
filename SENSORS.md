## Sensor Documentation
NOTE: All information is a summerization that may go out of date. For up to date information please refer to the most recent robot designs and bill of materials.

### Sensor Details

#### Distance Sensor
1. Description: A senser that determines the distance to another object. Used to locate opposing robot.
2. Output: Serial packet of length 9. Distance value in Centimeters is ((byteArray[3] << 8) | (byteArray[2] << 0)).
3. Positioning: 6 sensors placed along the front face facing at angles from forward [-10, -5, 0, 0, 5, 10] degrees(left to right). 
4. [Datasheet](https://cdn.sparkfun.com/assets/2/b/0/3/8/TFmini_Plus-01-A02-Datasheet_EN.pdf)

#### Line Sensor
1. Description: A sensor that determines the light intensity. Used to check the arena boundries.
2. Output: A boolean value based on the expression sensorReading >= lineThreshold where lineThreshold is an integer between 0 and 255.
3. Positioning: 2 sensors placed under the plow at the front facing the floor.
4. [Datasheet](https://cdn.sparkfun.com/assets/2/b/0/3/8/TFmini_Plus-01-A02-Datasheet_EN.pdf)

#### Motor Decoder
1. Description: A sensor that determines the velocity of a motor.
2. Output: Unknown
3. Positioning: 2 sensors, 1 per motor. 
4. Datasheet: MISSING

#### IMU
1. Description: A sensor that combines a 3-axis accelerometer, 3-axis gyroscope, and 3-axis compass. Used to measure acceleration and rotational acceleration.
2. Output: A floating value that can be read from an IMU object for the target sub-sensor[axis].
3. Positioning: 1 Senser place on the primary control circuit.
4. [Datasheet](https://invensense.tdk.com/wp-content/uploads/2016/06/DS-000189-ICM-20948-v1.3.pdf?ref_disty=digikey)

### How to Read
Current sensor readings are stored in the Sensor Data struct located in `lib/sensor_struct.h`.

The struct contains fields:
1. `std::vector<double> dist_buffer_` : Stores all distance sensor reads
2. `std::vector<int> line_buffer_` : Stores both line sensor reads
3. `std::vector<int> encoder_buffer_` : Stores both motor encoder reads
4. `double x_accel_` : Stores the x-axis of the accelerometer
5. `double y_accel_` : Stores the y-axis of the accelerometer
6. `double z_gyro_` : Stores the z-axis of the gyroscope
*\*buffers store data in the order of physical left to right

### Simulation
Simulated sensors are individual classes stored in `/simulator/src/simulator/sensors/`. They are configured onto a robot using a robot handler which defines the positions of the sensors and handles creating the Sensor Data struct for a read action.
