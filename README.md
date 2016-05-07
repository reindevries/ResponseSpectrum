# ResponseSpectrum

A simple program that calculates the response spectrum given an accelerogram.

## Description

If the program is not provided with any arguments, it'll print the help message. This gives a description on how to use the program, the output is shown below.

```
Obtain the response spectrum for a given accelerogram.

ReponseSpectrum [-r response_spectrum] [-p periods] [-d damping_ratio]
                [-s timestep] [-n threads] ground_motion

  ground_motion      File name of the input accelerogram in CSV-format. If the
                     name contains spaces it should be put in quotes (").

  response_spectrum  File name of the output response spectrum in CSV-format. If
                     the name contains spaces it should be put in quotes (").
                     The default is the accelerogram file name appended with
                     "_rs" (excluding the extension).
  periods            File name of the periods to be used for the response
                     spectrum in CSV-format. If the name contains spaces it
                     should be put in quotes ("). The default is a number of
                     approximately log-normally spaced periods as commonly used.
  damping_ratio      The damping ratio to be used for the calculations, the
                     default is 0.05 (5%).
  timestep           The maximum timestep to be used for the calculations. Note
                     that the minimum is defined as dt = T / 10. The default
                     is set at 5e-4 s.
  threads            Specified the number of concurrent threads that is used for
                     the calculation of the response spectrum. The default is
                     the maximum number available on the system.

The unit of time is assumed to be in seconds (s) and the unit of acceleration
in metres per second squared (m/s^2). The output spectrum is the pseudo-
acceleration response spectrum.
```

## Compiling the code

The source code can be compiled with any C++11 compatible compiler. In the source directory two folders are located (VS2015 and GNU), which contain the project file for Microsoft Visual Studio (Express) 2015 and a makefile for the GNU C++ compiler, respectively. For the latter `cd` into the GNU directory and type `make`, this will build the application for your platform.

Note that in the release directory builds are available for Windows and Linux (Ubuntu platform), both 64-bit.

## License

This software uses the [GNU GPLv3](/LICENSE.md) license. In general terms it means that this license requires anyone who distributes the code, or a derivative work, to make the source available under the same terms (i.e. open-source software).
