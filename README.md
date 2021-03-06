# easy-time
## A library for implementing equal-hour dates and times

Given a unix timestamp, latitude, and longitude, this library will tell you the time where there's 12 equal hours of the day and 12 equal hours of the night. There's still 60 minutes in an hour, and 60 seconds in a minute, etc. The duration of time that each second represents is just variable. With longer days, time moves slower. With shorter days, time moves quicker.

# Building

`make [all]` will do everything. `make debug` will do debug builds, and
`make release` will do release builds.

We also have `make clean` if you want that.

# Using

See the examples in the example-*/ directories
