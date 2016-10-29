\ pwm experiment
\ needs core.fs
cr cr reset

\ include ../flib/timer-stm32l0.fs
\ include ../flib/pwm-stm32l0.fs

\ pins PA0..3 are assumed to have LEDs attached

$00002222 PA0 io-base GPIO.AFRL + !
omode-pp pa0 io-mode!
omode-pp pa1 io-mode!
omode-pp pa2 io-mode!
omode-pp pa3 io-mode!

: go  \ various duty cycles at 2 Hz
  2 PA0 +pwm   500 PA0 pwm
  2 PA1 +pwm  3500 PA1 pwm
  2 PA2 +pwm  6500 PA2 pwm
  2 PA3 +pwm  9500 PA3 pwm ;

cr go