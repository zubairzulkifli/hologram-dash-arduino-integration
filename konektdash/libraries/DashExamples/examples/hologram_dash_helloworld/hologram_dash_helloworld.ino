/* Hologram Dash Hello World
*
* Purpose: This program demonstrates interactive serial mode,
* a mechanism for performing cable replacement serial passthrough
* over cellular to the cloud. This example works out-of-the-box
* with zero configuration.
*
* License: Copyright (c) 2017 Konekt, Inc. All Rights Reserved.
*
* Released under the MIT License (MIT)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*
*/

void setup() {
  SerialUSB.begin(9600); /* USB UART */
  Serial2.begin(9600); /* TTL UART */
  SerialUSB.println("Hologram Dash Hello World Example Started!");
  SerialCloud.begin(115200); /* Hologram Cloud */
  SerialCloud.println("Hello, World!"); /* one-time message */
  //NOTE: SerialCloud has been deprecated and will be removed in a future version.
  //      Migrate to HologramCloud which provides additional functionality.
  //      See the hologram_dash_cloud example for details.
}

void loop() {
  char currChar;
  /* we don't loop sending data, since we don't want to eat up
   * a lot of data on our SIM! */

  /* the code here will pass data between Cloud<-->UART */

  while (SerialUSB.available()) {
    SerialCloud.write(SerialUSB.read());
  }

  while (Serial2.available()) {
    SerialCloud.write(Serial2.read());
  }

  while (SerialCloud.available()) {
    currChar = (char)SerialCloud.read();
    SerialUSB.write(currChar);
    Serial2.write(currChar);
  }

  delay(5);
}
