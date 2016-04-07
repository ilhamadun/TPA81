/**
 * TPA81 Thermopile Array Library For Arduino
 * 
 * Copyright (c) 2016 Ilham Imaduddin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include "Arduino.h"
#include "Wire.h"
#include "TPA81.h"

// Constructors ////////////////////////////////////////////////////////////////

/**
 * Initialize object with TPA81's I2C default address.
 * Use this if you haven't change the address.
 */
TPA81::TPA81()
{
	address = 0xD0 >> 1;
}

/**
 * Initialize object with TPA81 custon I2C address.
 *
 * The TPA81 can be set to any of eight I2C addresses:
 * 0xD0, 0xD2, 0xD4, 0xD6, 0xD8, 0xDA, 0xDC, 0xDE
 * 
 * The factory default shipped address is 0xD0.
 *
 * @param	addr	TPA81 I2C address
 */
TPA81::TPA81(uint8_t addr)
{
	setup(addr);
}

void TPA81::setup(uint8_t addr)
{
	// Check if address is valid
	if (((addr & 0xF0) == 0xD0) && ((addr & 0x0F) % 2 == 0)) {
		address = addr >> 1;
	} else {
		// Fallback to default address
		address = 0xD0 >> 1;
	}
}

/**
 * Send Command To TPA81
 * 
 * @param 	cmd 	TPA81 register number
 */
void TPA81::sendCommand(uint8_t cmd)
{
	Wire.beginTransmission(address);
	Wire.write(cmd);
	Wire.endTransmission();
}

/**
 * Read single data from TPA81
 * 
 * @return 	data
 */
int TPA81::receiveData()
{
	Wire.requestFrom(address, 1);

	long start = millis();
	while (Wire.available() < 1) {
		if (millis() - start > 5)
			return 0;
	}

	return Wire.read();
}

void TPA81::changeAddress(uint8_t addr)
{
	Wire.beginTransmission(address);
	Wire.write(0);
	Wire.write(0xA0);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(0);
	Wire.write(0xAA);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(0);
	Wire.write(0xA5);
	Wire.endTransmission();

	Wire.beginTransmission(address);
	Wire.write(0);
	Wire.write(addr);
	Wire.endTransmission();

	address = addr >> 1;
}

/**
 * Read ambient temperature
 * 
 * @return 	ambient temperature
 */
int TPA81::getAmbient()
{
	sendCommand(AMBIENT);
	return receiveData();
}

/**
 * Read temperature from a certain point
 * 
 * @param  	point 	point number, 1 to 8
 * @return 			point temperature
 */
int TPA81::getPoint(uint8_t point)
{
	if (point < 1 && point > 8) {
		return 0;
	}

	sendCommand(POINT_BASE + point - 1);
	return receiveData();
}

/**
 * Read ambient and all temperature points
 * 
 * @param  points 	point temperature buffer
 * @return        	ambient temperature
 */
int TPA81::getAll(int points[])
{
	sendCommand(AMBIENT);

	Wire.requestFrom(address, (int) 9);

	long start = millis();
	while (Wire.available() < 9) {
		if (millis() - start > 10)
			return 0;
	}

	int ambient = Wire.read();
	for (int i = 0; i < 8; i++)
	{
		points[i] = Wire.read();
	}

	return ambient;
}
