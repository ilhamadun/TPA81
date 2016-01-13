TPA81 Library For Arduino
=========================

The TPA81 library allows an Arduino to read the TPA81 sensor. The TPA81 is a thermopile array detecting infra-red in the 2um-22um range. This is the wavelength of radiant heat. It has a array of eight thermopiles arranged in a row. The TPA81 can measure the temperature of 8 adjacent points simultaneously. The typical field of view of the TPA81 is 41° by 6° making each of the eight pixels 5.12° by 6°.

The TPA81 can also control a servo to pan the module and build up a thermal image.

## Installation
1. Click **Download ZIP**
2. Install the library, click `Sketch > Include Library > Add .ZIP Library...` on Arduino IDE

## Usage
First you need to include the Wire library. It is required to make the TPA81 works. You'll need to begin the Wire library with `Wire.begin()` in the setup function.

Begin the TPA81 library by creating a new instance:
```c++
TPA81 tpa;
```

The you can start reading the sensor. Here's how to read the ambient temperature:
```c++
int ambient = tpa.getAmbient()
```

And here's how to read the temperature in a specific point, where `i` is the point number between **1 and 8**:
```c++
int point = tpa.getPoint(i);
```

You can read all temperature points with this code:
```c++
int points[8];
for (int i = 1; i <= 8; i++)
{
    points[i] = tpa.getPoint(i);
}
```

To see how the library works, try the example.

## License
The TPA81 library is open source and licensed under the [MIT license](http://opensource.org/licenses/MIT).
