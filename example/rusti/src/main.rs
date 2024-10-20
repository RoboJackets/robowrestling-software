//! The starter code slowly blinks the LED and sets up
//! USB logging. It periodically logs messages over USB.
//!
//! Despite targeting the Teensy 4.0, this starter code
//! should also work on the Teensy 4.1 and Teensy MicroMod.
//! You should eventually target your board! See inline notes.
//!
//! This template uses [RTIC v2](https://rtic.rs/2/book/en/)
//! for structuring the application.

#![no_std]
#![no_main]

use teensy4_panic as _;

#[rtic::app(device = teensy4_bsp, peripherals = true)]
mod app {
    use bsp::board;
    use bsp::{
        hal::gpio,
        pins,
    };
    use teensy4_bsp as bsp;

    use imxrt_log as logging;

    // If you're using a Teensy 4.1 or MicroMod, you should eventually
    // change 't40' to 't41' or micromod, respectively.
    use board::t41 as my_board;

    use rtic_monotonics::systick::{Systick, *};

    struct MotorController<H, L, E> {
        high: gpio::Output<H>,
        low: gpio::Output<L>,
        enable: gpio::Output<E>
    }

    /// There are no resources shared across tasks.
    #[shared]
    struct Shared {}

    /// These resources are local to individual tasks.
    #[local]
    struct Local {
        /// The LED on pin 13.
        led: board::Led,
        /// A poller to control USB logging.
        poller: logging::Poller,
        left_motor: MotorController<pins::t41::P1, pins::t41::P2, pins::t41::P5>,
        right_motor: MotorController<pins::t41::P3, pins::t41::P4, pins::t41::P6>,
    }

    #[init]
    fn init(cx: init::Context) -> (Shared, Local) {
        let board::Resources {
            mut gpio1,
            mut gpio2,
            mut gpio4,
            pins,
            usb,
            ..
        } = my_board(cx.device);

        let led = board::led(&mut gpio2, pins.p13);
        let poller = logging::log::usbd(usb, logging::Interrupts::Enabled).unwrap();

        let left_motor = MotorController {
            high:   gpio1.output(pins.p1),
            low:    gpio4.output(pins.p2),
            enable: gpio4.output(pins.p5),
        };
        let right_motor = MotorController {
            high:   gpio4.output(pins.p3),
            low:    gpio4.output(pins.p4),
            enable: gpio2.output(pins.p6),
        };

        Systick::start(
            cx.core.SYST,
            board::ARM_FREQUENCY,
            rtic_monotonics::create_systick_token!(),
        );

        blink::spawn().unwrap();
        (Shared {}, Local { led, poller, left_motor, right_motor })
    }

    #[task(local = [led, left_motor, right_motor])]
    async fn blink(cx: blink::Context) {
        let blink::LocalResources { led, left_motor, right_motor, .. } = cx.local;
        let mut count = 0u8;

        left_motor.high.set();
        left_motor.low.clear();
        left_motor.enable.set();

        right_motor.high.set();
        right_motor.low.clear();
        right_motor.enable.set();

        led.set();

        loop {
            Systick::delay(1000.millis()).await;
            if count >= 5 {
                log::warn!("Stopped!");
                left_motor.enable.clear();
                right_motor.enable.clear();
                led.toggle();
            } else {
                //cx.local.led.toggle();
                log::info!("Switch!");

                left_motor.high.toggle();
                left_motor.low.toggle();
                right_motor.high.toggle();
                right_motor.low.toggle();

                led.toggle();
                count += 1;
            }
        }
    }

    #[task(binds = USB_OTG1, local = [poller])]
    fn log_over_usb(cx: log_over_usb::Context) {
        cx.local.poller.poll();
    }
}
