#include <opening/sample_opening.h>

SampleOpening::SampleOpening() {
    step = 0;
    end = 300;
    stop = false;
}

// turn out of the opponents way.
std::vector<int> SampleOpening::execute(SensorData input) {
    int output[] = {40, 60};
    if (step < end) {
        step++;
        return std::vector<int>(output, output + sizeof(output)/sizeof(int));
    } else {
        stop = true;
    }
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));

}

