notes
- robots can be as close as 10cm or as far as 70cm

strategy
0: normal
1: close swerve
2: medium swerve
3: long swerve
4: straight line
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