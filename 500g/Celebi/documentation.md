notes
- robots can be as close as 10cm or as far as 70cm

todo:
- think about memory access speeds

strategy
0 (000): normal
1 (001): close swerve left
2 (010): medium swerve left
3 (011): long swerve left
4 (100): straight line
5 (101): close swerve right
6 (110): medium swerve right
7 (111): long swerve right

placement guide for swerve init
- medium length: place back right corner in area, 45 degrees
Monday 4/13
thoughts
- any way to electrically turn off distance sensors
- early break out of start sequence?
- trace edge on start?

goals
- line detection working
- clarify what max speed is
- start stategy
    - 3 modes

what is max speed:
1. write 100 to left, 200 to right
2. write 200 to left, 256 to right -> right didn't work
3. 255 is max


line detection:
first try
- forward speed seems good at 80
- on line detection: slight turn right as it goes off, 
- maybe there's a double detection? Where becaues it goes over, it sees it again. this isn't possible though
decreased backwards time to 100 ms
- doesn't get back over the line before turning
increased to 250ms
- goes over first thing
decreased speed to 60
turning right when going backwards
- testing full power backwards for motor power diff
cleaned wheels
- going back too much
decreased backwards time to 100 ms
- good, try 50
decreased backwards time to 50 ms
- 50 too small, hugs edge -> turned into new functino
trying start strategy
- stops a litte short
increasing start time to 150 ms
- doesn't turn enough
decreasing left power to 150
- doesn't turn enough w/45 degree angle
decrease left power to 100
- turns too much
cleaned wheels
- even shorter
increased left power to 120
- got ruler to aim for 10 cm, 30cm, and full width
left power 50 for short
- length okay, timer too long
short: 50, 100
- timer okay, length too short
short: 75, 100
- length still short
100 power
- good
move on to medium: (120, 150)
- about 2/3 of length, angle okay
try (110, 200)
- closer, still a little too short
try (100, 230)
- realized i was moving power wrong
(150, 230)
- distance good, not turned enough
(130, 230)
- still not turned enough
(120, 230)
- angle not enough
- increase turn radius
(100,250)
- good
check numbers for short with placement 
- sharper turning
(70, 100)
good
test long
- not turned enough, not long enough
(150, 300)
- timing okay, not turned enough
(150, 330)
- not long enough
(150, 340)
- turn more, little longer
(140, 360)
- good
(140,360)
- turn more
(130, 360)
- turn slightly more
(120, 360)
- good 


start time tests
base code
472
316
472
320
472
312
320
324
320
324
first cycle override
60
212
60
60
60
60
60
60
212 - fast
60
60
60
move motor writing to start
56
52
212
56
56
56
56
56
212
52
56
56
move out of loop
52
60
208
52
60
56
52
52
52
60
56
56
52

adding profiling to code segments

shared start module pin:
- serial monitor will read junk if things are not actually printed.
- fixed with String() wrapping prints


remove unused code

10,000 cycles:

Total program time: 3293836
Start to first motor write: 48
Time spent in poll sensors: 2489
Time spent in state update: 2448323
Time spent in motor update: 17367
3293836, 48, 2489, 2448323, 17367

adding types and const hpp
Total program time: 3291816
Start to first motor write: 52
Time spent in poll sensors: 2520
Time spent in state update: 324563
Time spent in motor update: 3801
3291816, 52, 2520, 324563, 3801

optimizing algorithms


figure out why default is charing

add right side to start tuning, generally turns more so can increase speed



Total program time: 3526856
Start to first motor write: 48
Time spent in poll sensors: 2520
Time spent in state update: 3611429
        Time spent in attack pattern (almost all) 121440
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 41500
        Time spent updating world: 80024
Time spent in motor update: 14155
3526856, 48, 2520, 3611429, 14155


right first


Total program time: 3516288
Start to first motor write: 56
Time spent in poll sensors: 2511
Time spent in state update: 561283
        Time spent in attack pattern (almost all) 120220
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 60980
        Time spent updating world: 80448
Time spent in motor update: 4390
3516288, 56, 2511, 561283, 4390

change datatypes to shorts whereever possible

Total program time: 3448572
Start to first motor write: 52
Time spent in poll sensors: 2483
Time spent in state update: 3249860
        Time spent in attack pattern (almost all) 122300
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 40328
        Time spent updating world: 41640
Time spent in motor update: 23527
3448572, 52, 2483, 3249860, 23527

Total program time: 3374976
Start to first motor write: 52
Time spent in poll sensors: 2489
Time spent in state update: 1714823
        Time spent in attack pattern (almost all) 0
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 0
        Time spent updating world: 43652
Time spent in motor update: 4849
3374976, 52, 2489, 1714823, 4849

Total program time: 3448568
Start to first motor write: 52
Time spent in poll sensors: 2482
Time spent in state update: 2742502
        Time spent in attack pattern (almost all) 122136
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 40908
        Time spent updating world: 41636
Time spent in motor update: 4980
3448568, 52, 2482, 2742502, 4980

Total program time: 3442456
Start to first motor write: 52
Time spent in poll sensors: 2508
Time spent in state update: 3132012
        Time spent in attack pattern (almost all) 32100
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 10500
        Time spent updating world: 42512
Time spent in motor update: 5046
3442456, 52, 2508, 3132012, 5046

Total program time: 3448564
Start to first motor write: 52
Time spent in poll sensors: 2483
Time spent in state update: 461762
        Time spent in attack pattern (almost all) 122300
        Time spent in draw circle: 0
        Time spend in attack forward: 0
        Time spent in turn towards: 40336
        Time spent updating world: 41636
Time spent in motor update: 5636
3448564, 52, 2483, 461762, 5636 

right wheel lags