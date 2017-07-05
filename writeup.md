**PID Controller Project**

The steps for the project:

* create PID controller
* tune PID parameters
* test solution on simulator

## 1. PID controller
Implementation of PID controller is quite straightforward. It's implemented in PIC.cpp and PID.h files.

PID controllers calculates a steering value based on Cross Track Error (CTE). It consists of three components - P, I, D.
* P component is aimed to compensate CTE. Larger error, greater steering in the direction opposite to the error.
* I component is needed to compensate permanent error in steering. It depends on integral of all CTE values measured before.
* D component is used to avoid overshooting by decreasing steering value as we going closer to the target. Depends on current and previous CTE values.

## 2. Tuning PID parameters
I used two methods: manual tuning and twiddle.

Twiddle is implemented in twiddle.cpp and twiddle.h files. If pid application is run with any argument it uses twiddle mode.

In that mode the application sets some PID parameters, measure error on first 200 steps, reset the simulator to the beginning of the track, update PID parameters and start measuring again.
The disadvantage of the method is it's performance, it tooks too much time if you start with parameters which are far from optimal.

Also Twiddle can converge in local optimum and don't find global one.

## 3. Tuning throttle and steering value boundaries
Also I tried to implement smarter throttling and steering.

Intuition says that we need to drive slower in turns and don't steer sharply with high speed.

The idea was to make throttle inverse to steering angle and steering maximum inverse to speed.

* After several experiments I decided to keep throttle constant just not as large as it was initially, because with variable throttle PID worked not as good as I expected. It seems that different parameters should be used for different speed.
* Steering value boundaries I separated on two cases: low speed (steering from -1 to 1) and high speed (steering from -0.5 to 0.5)

## 4. Testing
Tuned PID parameters, limited throttle and steering values are enough to drive the whole track very smoothely.


