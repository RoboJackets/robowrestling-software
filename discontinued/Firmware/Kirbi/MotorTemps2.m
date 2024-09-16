timer = 0;
time = 0;
dt = .001;
stop = false;
while stop == false
current = readcurrent(time);
K = calculateK(current);
while K > 1
    ton = calculate_ton(K);
    if timer >= ton 
        stop = true;
        break;
    end
    timer = timer + dt;
    time = time + dt;
    %pause(dt);
    current = readcurrent(time);
    K = calculateK(current);
end
time = time + dt;
end
time
timer

function K = calculateK(current)
r1 = 2.3;
r2 = 7.28;
IN = 4.12;
K = current / IN * sqrt(r1/(r1 + r2));
end

function ton = calculate_ton(K)
tw = 42.2;
ton = tw * log(K^2/(K^2 - 1));
end

function current = readcurrent(time)
if time < .1
    current = 0;
else
    current = 600 * exp(-(time - .1));
    if current < 10
        current = 10;
    end
end
end
    